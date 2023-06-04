/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLabel>
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

  QHBoxLayout *top_layout;
  QLabel *choosepack_text;
  PackCombo *pack_combo;
  QPushButton *add_pack_button;

  QHBoxLayout *pack_toolbar_layout;
  QPushButton *rename_pack_button;
  QPushButton *remove_pack_button;
  /* QPushButton *export_pack_button; */
  /* QPushButton *import_pack_button; */

  QListWidget *card_list;

  QCheckBox *details_check;

  QHBoxLayout *card_toolbar_layout;
  QPushButton *compose_card_button;
  QPushButton *edit_card_button;
  QPushButton *remove_card_button;

 public:
  /// 初始化管理卡片窗口.
  explicit ManagerWindow(AppGlobals &globals);

  /// 获取选中的卡片.
  Card *GetCard();

 private slots:
  /// 添加卡组.
  void AddPack();

  /// 重命名卡组.
  void RenamePack();

  /// 删除卡组.
  void RemovePack();

  /// 接收 QListWidget 的信号, 切换所选卡片.
  void ChangeItem(QListWidgetItem *item);

 public slots:
  /// 接收 CardDatabase 的信号, 更新卡片信息.
  /// 只在 card 为当前列表中的卡片时有效.
  void UpdateCard(Card &card);

  /// 设置界面状态, 使界面显示指定卡组及其中卡片列表.
  /// 接收 PackCombo 的信号, 切换所选卡组.
  void ChangePack();

  /// 接收 PackCombo 的信号, 更新卡组信息.
  void UpdatePack();
};

}  // namespace aijika
