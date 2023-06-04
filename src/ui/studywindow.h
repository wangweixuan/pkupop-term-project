/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QSplitter>
#include <QStackedLayout>
#include <QWidget>

#include "common/globals.h"
#include "model/card.h"
#include "model/pack.h"
#include "ui/components/packcombo.h"

namespace aijika {

/// 学习窗口, 主窗口.
class StudyWindow : public QWidget {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  QVBoxLayout *main_layout;

  QHBoxLayout *toolbar_layout;
  PackCombo *pack_combo;
  QPushButton *compose_button;
  QPushButton *edit_button;
  QPushButton *manage_button;
  QPushButton *settings_button;

  QSplitter *card_splitter;
  QScrollArea *question_area;
  QLabel *question_label;
  QWidget *answer_container;
  QStackedLayout *answer_container_layout;
  QScrollArea *answer_area;
  QLabel *answer_label;
  QPushButton *show_answer_button;

  QButtonGroup *quality_group;
  QHBoxLayout *quality_layout;
  QPushButton *quality_buttons[4];

  QLabel *statusbar_label;

  /// 当前显示卡片的唯一标识符.
  /// 没有卡片时, 为 -1.
  card_id_t card_id;

 public:
  /// 初始化学习窗口.
  explicit StudyWindow(AppGlobals &globals);

  /// 通过 card_id 获取当前显示的卡片. 没有卡片时, 返回 nullptr.
  Card *GetCard();

  /// 设置 card_id 及界面状态, 使界面显示指定卡片.
  /// card 应在当前所选的卡组中, 或为 nullptr.
  void SetCard(Card *card);

 public slots:
  /// 接收 AppSettings 的信号, 更新界面显示设置.
  void UpdateAppearance();

  /// 接收 CardDatabase 的信号, 更新卡片信息.
  /// 只在 card 为当前显示的卡片时有效.
  /// 另见 SetCard().
  void UpdateCard(Card &card);

  /// 设置界面状态, 使界面显示指定卡组及其中合适的卡片.
  /// 接收 PackCombo 的信号, 切换所选卡组或更新卡组信息.
  void ChangePack();
};

}  // namespace aijika
