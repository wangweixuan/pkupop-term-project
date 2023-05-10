/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QByteArray>
#include <QList>
#include <QString>

#include "generator/openai.h"
#include "model/card.h"

namespace aijika {

/// 一组卡片内容.
class CardStemList : public QList<CardStem> {
 public:
  /// 将一组卡片内容编码成字符串.
  QByteArray Encode() const;

  /// 从字符串解码出一组卡片内容.
  void Decode(QByteArray const &content);
};

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
  CardStemList examples;

  /// 将模板填充到指定的对话请求 request.
  void ToMessages(ApiRequest &request) const;
};

/// 从程序的 resources/prompts.json 文件读取模板列表.
QList<Prompt> LoadPromptsFromResources();

/// 从 JSON 文件内容读取模板列表.
QList<Prompt> LoadPromptsFromData(QByteArray const &data);

}  // namespace aijika
