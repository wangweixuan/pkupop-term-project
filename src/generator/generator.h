/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QList>
#include <QObject>
#include <QString>

#include "common/settings.h"
#include "generator/openai.h"
#include "generator/prompt.h"

namespace aijika {

/// 生成卡片的服务.
class CardGenerator : public QObject {
  Q_OBJECT;

 private:
  /// 包装了 OpenAI API 的服务.
  ApiManager *mgr;

  /// 网络设置.
  AppSettings &settings;

 public:
  /// 卡片模板列表.
  QList<Prompt> prompts;

  /// 初始化生成服务, 以 parent 为所有者.
  explicit CardGenerator(QObject *parent, AppSettings &settings);

  /// 发出请求, 使用指定的 prompt 和 keywords (每行一个关键词) 生成卡片.
  /// 生成后, 发出 generated 或 error 信号.
  void Generate(Prompt const &prompt, QString keywords);

 private slots:
  /// 接收来自 ApiManager 的数据.
  void ApiResponse(QString content);

  /// 接收来自 ApiManager 的错误报告.
  void ApiError(QString message);

  /// 通过 settings 更新网络设置.
  void UpdateApiSettings();

 public slots:
  /// 终止当前请求.
  /// 终止后, 发出 generated 或 error 信号.
  void Abort();

 signals:
  /// 卡片生成成功时发出的信号.
  void generated(CardStemList cards);

  /// 卡片生成失败时发出的信号.
  void error(QString message);
};

}  // namespace aijika
