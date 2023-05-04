/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "common/globals.h"
#include "model/card.h"
#include "model/pack.h"

namespace aijika {

/// 学习窗口, 主窗口.
class StudyWindow : public QWidget {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  QVBoxLayout *main_layout;

  QHBoxLayout *toolbar_layout;
  QComboBox *pack_combo;
  QPushButton *compose_button;
  QPushButton *edit_button;
  QPushButton *manage_button;
  QPushButton *settings_button;

  QWidget *card_widget;
  QVBoxLayout *card_layout;
  QLabel *question_label;
  QLabel *answer_label;
  QPushButton *show_answer_button;

  QHBoxLayout *quality_layout;
  QPushButton *quality_buttons[4];

  QLabel *statusbar_label;

  card_id_t current_card_id;
  pack_id_t current_pack_id;
  Card *current_card;
  CardPack *current_pack;

 public:
  explicit StudyWindow(AppGlobals &globals);

  void SetCard(Card *card);
  void SetPack(CardPack *pack);

 public slots:
  void UpdateAppearance();

  void InvalidatePack(CardPack &pack);
  void InvalidateList();
};

}  // namespace aijika
