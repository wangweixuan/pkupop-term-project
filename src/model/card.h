/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QDataStream>
#include <QDateTime>
#include <QString>

namespace aijika {

/// 卡片的实际内容. 可用于初始化卡片.
struct CardStem {
  /// 关键词.
  QString keyword;
  /// 问题文本.
  QString question;
  /// 答案文本.
  QString answer;
};

/// 用户对卡片记忆程度的分级. 用于间隔重复算法.
enum struct UserQuality {
  again=4,  // 完全忘记.
  hard=3,
  good=2,
  easy=1,  // 完全掌握.
};

/// Card 的唯一标识符类型.
using card_id_t = int;

/// 卡片.
struct Card {
  /// 唯一标识符. 应在同一 CardDatabase 中无重复.
  card_id_t id;
  /// 关键词.
  QString keyword;
  /// 问题文本.
  QString question;
  /// 答案文本.
  QString answer;
  /// 创建时间.
  QDateTime time_created;
  /// 最近复习时间.
  QDateTime time_reviewed;
  /// 下次需复习时间.
  QDateTime time_due;

  // 用于间隔重复算法的属性

  /// 已经复习的次数.
  int repetition;
  /// 复习的间隔.
  int interval;
  /// 容易因数.
  double easiness;

  /// 初始化空卡片.
  explicit Card();
  /// 以 stem 为内容初始化卡片.
  explicit Card(CardStem const &stem);

  /// 根据用户对卡片的分级 quality, 更新用于间隔重复算法的各个属性.
  void Update(UserQuality quality);

  /// 将 card 序列化到数据流 out.
  friend QDataStream &operator<<(QDataStream &out, Card const &card);
  /// 从数据流 in 反序列化 card.
  friend QDataStream &operator>>(QDataStream &in, Card &card);

};

}  // namespace aijika
