/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QDataStream>
#include <QList>
#include <QString>

#include "generator/prompt.h"
#include "model/card.h"

namespace aijika {

/// Card 的唯一标识符类型.
using pack_id_t = int;

/// 如何选择待复习卡片.
enum struct ReviewOption {
  last_reviewed,  /// 选择最久未复习的卡片.
  due_date,       /// 选择最早到期的卡片.
  random,         /// 随机选择卡片.
};

/// 卡组, 即卡片列表.
struct CardPack {
  /// 唯一标识符. 应在同一 CardDatabase 中无重复.
  pack_id_t id;

  /// 名称.
  QString label;

  /// 卡片列表.
  QList<Card> cards;

  /// 最近使用的 Prompt.
  prompt_id_t last_prompt;

  /// 查找卡片.
  Card *FindCard(card_id_t id);

  /// 根据复习方案 opt, 选出一张待复习的卡片.
  /// 如果没有卡片需要复习, 返回 nullptr.
  Card *ChooseCard(ReviewOption opt);

  /// 根据复习方案 opt, 统计待复习卡片的数量.
  int CountCards(ReviewOption opt) const;
  /// 统计卡片的总数.
  int CountTotalCards() const;

  /// 将 pack 序列化到数据流 out.
  friend QDataStream &operator<<(QDataStream &out, CardPack const &pack);
  /// 从数据流 in 反序列化 pack.
  friend QDataStream &operator>>(QDataStream &in, CardPack &pack);
};

}  // namespace aijika
