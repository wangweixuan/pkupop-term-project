/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QComboBox>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "common/globals.h"
#include "model/pack.h"

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

  QComboBox *pack_combo;

  QHBoxLayout *card_toolbar_layout;
  QPushButton *compose_card_button;
  QPushButton *edit_card_button;
  QPushButton *remove_card_button;

  QListWidget *card_list;

  pack_id_t current_pack_id;
  CardPack *current_pack;

 public:
  explicit ManagerWindow(AppGlobals &globals);

  void SetPack(CardPack *pack);

 public slots:
  void InvalidatePack(CardPack &pack);
  void InvalidateList();
};

}  // namespace aijika
