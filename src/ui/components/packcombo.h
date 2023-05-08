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

  pack_id_t pack_id;

 public:
  explicit PackCombo(QWidget *parent, AppGlobals &globals);

  /// 获取所选卡组. 没有卡组时, 返回 nullptr.
  CardPack *GetPack();

  /// 设置所选卡组. pack 可为 nullptr.
  void SetPack(CardPack *pack);

 private slots:
  /// 接收 CardDatabase 的信号, 更新卡组信息.
  void UpdatePack(CardPack &pack);

  /// 接收 CardDatabase 的信号, 更新卡组列表.
  void UpdateList();

 signals:
  /// 切换卡组时发出的信号. pack 可为 nullptr.
  void pack_changed(CardPack *pack);

  /// 所选卡组发生更新时发出的信号.
  void pack_updated(CardPack &pack);
};

}  // namespace aijika
