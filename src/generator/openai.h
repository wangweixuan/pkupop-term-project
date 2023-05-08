/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QString>
#include <QStringList>

namespace aijika {

/// 通过 OpenAI API 生成对话的请求.
/// 见 https://platform.openai.com/docs/api-reference/chat/create
class ApiRequest {
 public:
  /// 对话消息的角色.
  enum struct Role {
    system,
    user,
    assistant,
  };

  /// 请求体 JSON.
  QJsonObject json;

  /// 请求体中的字符串列表.
  QStringList strings;

  /// 初始化空请求.
  explicit ApiRequest();

  /// 设置要使用的 model.
  void SetModel(QString model);

  /// 添加对话消息作为上文.
  void AddMessage(Role role, QString content);
};

/// 包装了 OpenAI API 的服务.
class ApiManager : public QObject {
  Q_OBJECT;

 private:
  /// 访问网络的服务.
  QNetworkAccessManager *mgr;

  /// 当前的网络会话.
  QNetworkReply *current_reply;

 public:
  /// OpenAI API 的 base URL.
  QString api_base_url;
  /// OpenAI API 的密钥.
  QString api_key;

  /// 初始化 API 服务, 以 parent 为所有者.
  explicit ApiManager(QObject *parent);

  /// 从 request 生成并发送对话请求.
  /// 响应后, 发出 response 或 error 信号.
  void Send(ApiRequest const &request);

  /// 终止当前请求.
  /// 终止后, 发出 response 或 error 信号.
  void Abort();

 private slots:
  /// 接收来自 QNetworkAccessManager 的响应.
  void FinishReply(QNetworkReply *reply);

 signals:
  /// 对话生成成功时发出的信号.
  void response(QString content);

  /// 对话生成失败时发出的信号.
  void error(QString message);
};

}  // namespace aijika
