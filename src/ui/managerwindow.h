/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "common/globals.h"
#include "model/card.h"
#include "model/pack.h"
#include "ui/components/packcombo.h"

namespace aijika {

/// 管理卡片窗口.
class ManagerWindow : public QWidget {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  QVBoxLayout *main_layout;

  QHBoxLayout *pack_toolbar_layout;
  QPushButton *add_pack_button;
  QPushButton *edit_pack_button;
  QPushButton *remove_pack_button;
  QPushButton *export_pack_button;
  QPushButton *import_pack_button;

  PackCombo *pack_combo;

  QHBoxLayout *card_toolbar_layout;
  QPushButton *compose_card_button;
  QPushButton *edit_card_button;
  QPushButton *remove_card_button;

  QListWidget *card_list;

 public:
  /// 初始化管理卡片窗口.
  explicit ManagerWindow(AppGlobals &globals);

  /// 设置界面状态, 使界面显示指定卡组及其中卡片列表.
  /// pack 应匹配当前 pack_combo 所选的卡组, 或为 nullptr.
  void SetPack(CardPack *pack);

 public slots:
  /// 接收 CardDatabase 的信号, 更新卡片信息.
  /// 只在 card 为当前列表中的卡片时有效.
  void UpdateCard(Card &card);

  /// 接收 PackCombo 的信号, 切换所选卡组.
  /// 另见 SetPack().
  void ChangePack(CardPack *pack);

  /// 接收 PackCombo 的信号, 更新卡组信息.
  /// 另见 SetPack().
  void UpdatePack(CardPack &pack);
};

}  // namespace aijika
