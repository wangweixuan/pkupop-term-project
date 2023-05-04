/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/studywindow.h"

#include "ui/managerwindow.h"
#include "ui/settingswindow.h"

namespace aijika {

StudyWindow::StudyWindow(AppGlobals &globals)
    : QWidget{nullptr},
      globals{globals},
      main_layout{new QVBoxLayout(this)},
      toolbar_layout{new QHBoxLayout(nullptr)},
      pack_combo{new QComboBox(this)},
      compose_button{new QPushButton(this)},
      edit_button{new QPushButton(this)},
      manage_button{new QPushButton(this)},
      settings_button{new QPushButton(this)},
      card_widget{new QWidget(this)},
      card_layout{new QVBoxLayout(nullptr)},
      question_label{new QLabel(this)},
      answer_label{new QLabel(this)},
      show_answer_button{new QPushButton(this)},
      quality_layout{new QHBoxLayout(nullptr)},
      quality_buttons{new QPushButton(this), new QPushButton(this),
                      new QPushButton(this), new QPushButton(this)},
      statusbar_label{new QLabel(this)} {
  setWindowTitle("学习卡片");

  // 顶部工具栏
  main_layout->addLayout(toolbar_layout);

  toolbar_layout->addWidget(pack_combo);

  toolbar_layout->addWidget(compose_button);
  compose_button->setText("创建卡片");

  toolbar_layout->addWidget(edit_button);
  edit_button->setText("编辑卡片");

  toolbar_layout->addWidget(manage_button);
  manage_button->setText("管理卡片");
  connect(manage_button, &QPushButton::clicked, [&globals]() {
    auto window = new ManagerWindow(globals);
    window->show();
  });

  toolbar_layout->addWidget(settings_button);
  settings_button->setText("设置");
  connect(settings_button, &QPushButton::clicked, [&globals]() {
    auto window = new SettingsWindow(globals);
    window->show();
  });

  // 卡片
  main_layout->addWidget(card_widget, /* stretch */ 1);
  card_widget->setLayout(card_layout);

  card_layout->addWidget(question_label);
  question_label->setText("这是问题");

  card_layout->addWidget(answer_label);
  answer_label->setText("这是答案 (应该隐藏)");

  card_layout->addWidget(show_answer_button);
  show_answer_button->setText("显示答案");

  // 卡片反馈
  main_layout->addLayout(quality_layout);

  quality_layout->addWidget(quality_buttons[0]);
  quality_buttons[0]->setText("忘了");

  quality_layout->addWidget(quality_buttons[1]);
  quality_buttons[1]->setText("忘了");

  quality_layout->addWidget(quality_buttons[2]);
  quality_buttons[2]->setText("忘了");

  quality_layout->addWidget(quality_buttons[3]);
  quality_buttons[3]->setText("记得");

  // 底部状态栏
  main_layout->addWidget(statusbar_label);
  statusbar_label->setText("还有 1 张卡片要复习");

  SetPack(globals.db.FindPack(globals.db.last_visited_pack));
}

void StudyWindow::SetCard(Card *card) {
  // TODO: unimplemented
  current_card = card;
  if (card == nullptr) {
    // 特殊情况
  }
}

void StudyWindow::SetPack(CardPack *pack) {
  // TODO: unimplemented
  current_pack = pack;
  if (pack == nullptr) {
    // 特殊情况
    SetCard(nullptr);
    return;
  }
  SetCard(pack->ChooseCard(ReviewOption::random));
}

void StudyWindow::UpdateAppearance() {
  // TODO: unimplemented
}

void StudyWindow::InvalidatePack(CardPack &pack) {
  // TODO: unimplemented
  (void)pack;
}

void StudyWindow::InvalidateList() {
  // TODO: unimplemented
}

}  // namespace aijika
