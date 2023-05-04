/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QJsonObject>
#include <QList>
#include <QString>

#include "generator/openai.h"
#include "model/card.h"

namespace aijika {

/// Prompt 的唯一标识符类型.
using prompt_id_t = int;

/// 对话的模板, 对应一种卡片题型.
struct Prompt {
  /// 唯一标识符.
  prompt_id_t id;
  /// 名称.
  QString label;
  /// 对话中的 system 消息. 见
  /// https://platform.openai.com/docs/api-reference/chat/create#chat/create-role
  QString system;
  /// 题型的样例, 用于生成对话消息.
  QList<CardStem> examples;

  /// 初始化空模板.
  explicit Prompt() = default;
  /// 从 JSON 对象 obj 初始化模板.
  explicit Prompt(QJsonObject const &obj);

  /// 将模板填充到指定的对话请求 request, 每则消息最多含 batch 个样例.
  void ToMessages(ApiRequest &request, int batch) const;
};

/// 从程序的 resources/prompts.json 文件读取模板列表.
QList<Prompt> LoadPromptsFromResources();

}  // namespace aijika
