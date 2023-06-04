/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QComboBox>

#include "common/globals.h"
#include "model/pack.h"

namespace aijika {

/// 选择卡组菜单.
class PackCombo : public QComboBox {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  bool is_updating_list;

 public:
  explicit PackCombo(QWidget *parent, AppGlobals &globals);

  /// 设置卡组列表.
  void SetList();

  /// 获取所选卡组. 没有卡组时, 返回 nullptr.
  CardPack *GetPack();

  /// 设置所选卡组. pack 可为 nullptr.
  void SetPack(CardPack *pack);

  /// 设置 CardDatabase 中的上次访问卡组.
  void SetLastVisited();

 private slots:
  /// 接收 CardDatabase 的信号, 更新卡组信息.
  void UpdatePack(CardPack &pack);

  /// 接收 CardDatabase 的信号, 更新卡组列表.
  void UpdateList();

  /// 接收 QComboBox 的信号, 切换卡组.
  void ChangeIndex(int index);

 signals:
  /// 切换卡组时发出的信号. pack 可为 nullptr.
  void pack_changed(CardPack *pack);

  /// 所选卡组发生更新时发出的信号.
  void pack_updated(CardPack &pack);
};

}  // namespace aijika
