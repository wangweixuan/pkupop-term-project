/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/openai.h"

#include <QNetworkRequest>

namespace aijika {

ApiRequest::ApiRequest() {
  // TODO: unimplemented
}

void ApiRequest::SetModel(QString model) {
  // TODO: unimplemented
  (void)model;
}

void ApiRequest::AddMessage(QString role, QString content) {
  // TODO: unimplemented
  (void)role, (void)content;
}

ApiManager::ApiManager(QObject *parent)
    : mgr{*new QNetworkAccessManager(parent)}, current_reply{nullptr} {}

void ApiManager::Send(ApiRequest const &request) {
  // TODO: unimplemented
  (void)request;
}

void ApiManager::Abort() {
  // TODO: unimplemented
}

void ApiManager::FinishReply(QNetworkReply *reply) {
  // TODO: unimplemented
  (void)reply;
}

}  // namespace aijika
