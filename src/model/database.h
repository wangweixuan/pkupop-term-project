/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QDataStream>
#include <QList>
#include <QObject>
#include <QString>

#include "model/card.h"
#include "model/pack.h"

namespace aijika {

/// 卡片数据库, 即卡组列表.
class CardDatabase : public QObject {
  Q_OBJECT;

 public:
  /// 卡组列表.
  QList<CardPack> packs;

  /// 可以分配给 CardPack 的唯一标识符. 单调增长.
  pack_id_t incremental_pack_id;

  /// 可以分配给 Card 的唯一标识符. 单调增长.
  card_id_t incremental_card_id;

  /// 最近访问的卡组.
  pack_id_t last_visited_pack;

  /// 初始化空数据库.
  explicit CardDatabase();

  /// 查找指定的卡组.
  CardPack *FindPack(pack_id_t pack);

  /// 创建以 label 为名称的卡组.
  void AddPack(QString const &label);
  /// 卡组重命名
  void RenamePack(QString const &label, CardPack &pack);
  /// 移除指定的卡组.
  void RemovePack(pack_id_t pack);

  /// 在指定的卡组中, 创建以 stem 为内容的卡片.
  void AddCard(CardStem const &stem, CardPack &pack);

  /// 在指定的卡组中，重新编辑卡片
  void editcard(CardStem const &stem, Card *card, CardPack &pack);

  /// 在指定的卡组中, 移除指定的卡片.
  void RemoveCard(card_id_t card, CardPack &pack);

  /// 将 db 序列化到数据流 out.
  friend QDataStream &operator<<(QDataStream &out, CardDatabase const &db);
  /// 从数据流 in 反序列化 db.
  friend QDataStream &operator>>(QDataStream &in, CardDatabase &db);

 signals:
  /// 特定卡片发生更新时发出的信号.
  void card_updated(Card &card);
  /// 特定卡组中卡片列表发生更新时发出的信号.
  void pack_updated(CardPack &pack);
  /// 卡组列表发生更新时发出的信号.
  void list_updated();
};

}  // namespace aijika
