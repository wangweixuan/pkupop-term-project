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
  json["model"] = "";
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
      current_reply{nullptr} {
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

  auto payload = request.Build();

  qDebug() << "Request:" << url;
  qDebug() << "Request body:" << payload;

  current_reply = mgr->post(headers, payload);
}

void ApiManager::Abort() {
  auto reply = current_reply;
  if (reply) reply->abort();
}

void ApiManager::FinishReply(QNetworkReply *reply) {
  current_reply = nullptr;
  reply->deleteLater();

  qDebug() << "Response:" << reply->url() << reply->error();

  if (auto content_type =
          reply->header(QNetworkRequest::ContentTypeHeader).toString();
      !content_type.startsWith("application/json")) {
    // Note that 'application/json; charset=utf-8' is acceptable content type
    if (auto err = reply->error(); err != QNetworkReply::NoError) {
      emit error(
          "网络错误\n请检查“API 设置”中的网址，以及您的网络环境\n\n详细信息：" +
          QVariant::fromValue(err).toString());
      return;
    }

    emit error("服务器异常\n请重试\n\n详细信息：" + content_type);
    return;
  }

  auto body = reply->readAll();

  qDebug() << "Response body:" << body;

  QJsonParseError err;
  auto document = QJsonDocument::fromJson(body, &err);
  if (document.isNull()) {
    emit error("服务器异常\n请重试\n\n详细信息：" + err.errorString());
    return;
  }

  // https://platform.openai.com/docs/guides/error-codes/api-errors
  if (document.object()["error"].isObject()) {
    auto message = document.object()["error"].toObject()["message"].toString();
    if (message.isEmpty()) {
      message = document.object()["error"].toObject()["code"].toString();
    }
    emit error("服务器错误\n请检查“API 设置”中的密钥和模型\n\n详细信息：" +
               message);
    return;
  }

  auto message = document.object()["choices"]
                     .toArray()[0]
                     .toObject()["message"]
                     .toObject()["content"];
  if (!message.isString()) {
    emit error("服务器异常\n请重试\n\n详细信息：格式错误");
    return;
  }

  emit response(message.toString());
}

}  // namespace aijika
