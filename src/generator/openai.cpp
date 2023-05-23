/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/openai.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QNetworkRequest>
#include <QUrl>
#include <QtDebug>

namespace aijika {

ApiRequest::ApiRequest() {
  json["model"] = "gpt-3.5-turbo";  // 默认值
  json["messages"] = QJsonArray{};
  // 其他参数暂不需要
}

void ApiRequest::SetModel(QString const &model) { json["model"] = model; }

void ApiRequest::AddMessage(Role role, QString const &content) {
  QJsonObject message;
  switch (role) {
    case Role::system:
      message["role"] = "system";
      break;
    case Role::user:
      message["role"] = "user";
      break;
    case Role::assistant:
      message["role"] = "assistant";
  }
  message["content"] = content;

  json["messages"] = (json["messages"].toArray() << message);
}

QByteArray ApiRequest::Build() const {
  QJsonDocument document{json};
  return document.toJson(QJsonDocument::Compact);
}

ApiManager::ApiManager(QObject *parent)
    : QObject{parent},
      mgr{new QNetworkAccessManager{this}},
      current_reply{nullptr},
      api_base_url{"https://api.openai.com"} {
  connect(mgr, &QNetworkAccessManager::finished, this,
          &ApiManager::FinishReply);
}

void ApiManager::Send(ApiRequest const &request) {
  if (current_reply) return;

  QUrl url{api_base_url + "/v1/chat/completions"};
  QNetworkRequest headers{url};
  if (api_key.size()) {
    headers.setRawHeader("Authorization", ("Bearer " + api_key).toUtf8());
  }
  headers.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  qDebug() << "Request:" << url;

  current_reply = mgr->post(headers, request.Build());
}

void ApiManager::Abort() {
  auto reply = current_reply;
  if (reply) reply->abort();
}

void ApiManager::FinishReply(QNetworkReply *reply) {
  current_reply = nullptr;
  reply->deleteLater();

  qDebug() << "Response:" << reply->url() << reply->error();

  // TODO: make error messages more clear
  // https://platform.openai.com/docs/guides/error-codes/api-errors
  if (reply->error()) {
    emit error(QVariant::fromValue(reply->error()).toString());
    return;
  }
  if (auto content_type =
          reply->header(QNetworkRequest::ContentTypeHeader).toString();
      content_type != "application/json") {
    emit error("Unexpected content type from server: " + content_type);
    return;
  }

  auto body = reply->readAll();
  if (!body.size()) {
    emit error("Empty response from server");
    return;
  }

  qDebug() << "Response body:" << body;

  QJsonParseError err;
  auto document = QJsonDocument::fromJson(body, &err);
  if (document.isNull()) {
    emit error("Response is not valid JSON: " + err.errorString());
    return;
  }

  if (document.object()["error"].isObject()) {
    emit error("API error: " +
               document.object()["error"].toObject()["message"].toString());
    return;
  }

  auto message = document.object()["choices"]
                     .toArray()[0]
                     .toObject()["message"]
                     .toObject()["content"];
  if (!message.isString()) {
    emit error("API format error: expected string");
    return;
  }

  emit response(message.toString());
}

}  // namespace aijika
