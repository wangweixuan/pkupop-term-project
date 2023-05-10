/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/openai.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QNetworkRequest>
#include <QUrl>

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
      current_reply{nullptr} {
  connect(mgr, &QNetworkAccessManager::finished, this,
          &ApiManager::FinishReply);
}

void ApiManager::Send(ApiRequest const &request) {
  if (current_reply) return;

  QUrl url{api_base_url + "/v1/chat/completions"};
  QNetworkRequest headers{url};
  headers.setRawHeader("Authorization", ("Bearer: " + api_key).toUtf8());
  headers.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

  current_reply = mgr->post(headers, request.Build());
}

void ApiManager::Abort() {
  auto reply = current_reply;
  if (reply) reply->abort();
}

void ApiManager::FinishReply(QNetworkReply *reply) {
  current_reply = nullptr;
  // TODO: unimplemented
  reply->deleteLater();
}

}  // namespace aijika
