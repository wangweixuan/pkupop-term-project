/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */
#include "ui/studywindow.h"

#include <QtDebug>

#include "model/card.h"
#include "ui/composerdialog.h"
#include "ui/editordialog.h"
#include "ui/managerwindow.h"
#include "ui/settingswindow.h"

namespace aijika {

StudyWindow::StudyWindow(AppGlobals &globals)
    : QWidget{nullptr},
      globals{globals},
      main_layout{new QVBoxLayout{this}},
      toolbar_layout{new QHBoxLayout{nullptr}},
      pack_combo{new PackCombo{this, globals}},
      compose_button{new QPushButton{"创建卡片", this}},
      edit_button{new QPushButton{"编辑卡片", this}},
      manage_button{new QPushButton{"管理卡片", this}},
      settings_button{new QPushButton{"设置", this}},
      card_splitter{new QSplitter{Qt::Vertical, this}},
      question_area{new QScrollArea{card_splitter}},
      question_label{new QLabel{this}},
      answer_container{new QWidget{card_splitter}},
      answer_container_layout{new QStackedLayout{answer_container}},
      answer_area{new QScrollArea{nullptr}},
      answer_label{new QLabel{this}},
      show_answer_button{new QPushButton{"显示答案", nullptr}},
      quality_group{new QButtonGroup{this}},
      quality_layout{new QHBoxLayout{nullptr}},
      quality_buttons{
          new QPushButton{"重来", this}, new QPushButton{"困难", this},
          new QPushButton{"良好", this}, new QPushButton{"简单", this}},
      statusbar_label{new QLabel{this}},
      card_id{-1} {
  setWindowTitle("学习卡片");

  // 顶部工具栏
  main_layout->addLayout(toolbar_layout);

  toolbar_layout->addWidget(pack_combo);

  toolbar_layout->addWidget(compose_button);
  connect(compose_button, &QPushButton::clicked, [&]() {
    pack_combo->SetLastVisited();
    auto window = new ComposerDialog{this, globals};
    window->show();
  });

  toolbar_layout->addWidget(manage_button);
  connect(manage_button, &QPushButton::clicked, [&]() {
    pack_combo->SetLastVisited();
    auto window = new ManagerWindow{globals};
    window->show();
  });

  toolbar_layout->addWidget(edit_button);
  connect(edit_button, &QPushButton::clicked, [&]() {
    if (GetCard() == nullptr) {
      qWarning() << "StudyWindow EditButton: no card";
      return;
    }
    auto window =
        new EditorDialog{0, globals, GetCard(), pack_combo->GetPack()};
    window->show();
  });

  toolbar_layout->addWidget(settings_button);
  connect(settings_button, &QPushButton::clicked, [&globals]() {
    auto window = new SettingsWindow{globals};
    window->show();
  });

  // 卡片
  main_layout->addWidget(card_splitter, /* stretch */ 1);
  card_splitter->setChildrenCollapsible(false);
  card_splitter->setHandleWidth(3);

  question_area->setAlignment(Qt::AlignCenter);
  question_area->setWidgetResizable(true);
  question_area->setWidget(question_label);
  question_label->setAlignment(Qt::AlignCenter);
  question_label->setTextFormat(Qt::MarkdownText);
  question_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
  question_label->setCursor(Qt::IBeamCursor);
  question_label->setWordWrap(true);

  answer_area->setAlignment(Qt::AlignCenter);
  answer_area->setWidgetResizable(true);
  answer_area->setWidget(answer_label);
  answer_label->setAlignment(Qt::AlignCenter);
  answer_label->setTextFormat(Qt::MarkdownText);
  answer_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
  answer_label->setCursor(Qt::IBeamCursor);
  answer_label->setWordWrap(true);
  answer_container_layout->setContentsMargins(0, 0, 0, 0);
  answer_container_layout->addWidget(answer_area);
  answer_container_layout->addWidget(show_answer_button);

  // 卡片反馈
  main_layout->addLayout(quality_layout);

  quality_buttons[0]->setStyleSheet(
      "QPushButton { border: none; min-height: 30px; }"
      "QPushButton:enabled { background-color: #e53935; color: #000000; }"
      "QPushButton:pressed { background-color: #d32f2f; }");
  quality_buttons[1]->setStyleSheet(
      "QPushButton { border: none; min-height: 30px; }"
      "QPushButton:enabled { background-color: #fbc02d; color: #000000; }"
      "QPushButton:pressed { background-color: #f9a825; }");
  quality_buttons[2]->setStyleSheet(
      "QPushButton { border: none; min-height: 30px; }"
      "QPushButton:enabled { background-color: #0288d1; color: #fefefe; }"
      "QPushButton:pressed { background-color: #0277bd; }");
  quality_buttons[3]->setStyleSheet(
      "QPushButton { border: none; min-height: 30px; }"
      "QPushButton:enabled { background-color: #388e3c; color: #fefefe; }"
      "QPushButton:pressed { background-color: #2e7d32 }");
  for (int i = 0; i < 4; ++i) {
    quality_group->addButton(quality_buttons[i], i);
    quality_layout->addWidget(quality_buttons[i]);
  }

  // 底部状态栏
  main_layout->addWidget(statusbar_label);

  connect(&globals.settings, &AppSettings::appearance_updated, this,
          &StudyWindow::UpdateAppearance);
  connect(&globals.db, &CardDatabase::card_updated, this,
          &StudyWindow::UpdateCard);
  connect(pack_combo, &PackCombo::pack_changed, this, &StudyWindow::ChangePack);
  connect(pack_combo, &PackCombo::pack_updated, this, &StudyWindow::UpdatePack);

  connect(show_answer_button, &QPushButton::clicked,
          [&]() { answer_container_layout->setCurrentWidget(answer_area); });

  connect(quality_group, &QButtonGroup::idClicked, [this](int i) {
    Card *tmp = GetCard();
    if (tmp == nullptr) return;

    UserQuality quality = static_cast<UserQuality>(4 - i);
    tmp->Update(quality);
    emit this->globals.db.card_updated(*tmp);
    SetPack(pack_combo->GetPack());
  });

  UpdateAppearance();

  SetPack(pack_combo->GetPack());
}

Card *StudyWindow::GetCard() {
  auto pack = pack_combo->GetPack();
  if (pack == nullptr) return nullptr;

  return pack->FindCard(card_id);
}

void StudyWindow::SetCard(Card *card) {
  answer_container_layout->setCurrentWidget(show_answer_button);

  if (card == nullptr) {
    // 特殊情况
    card_id = -1;
    question_label->setText("无卡片");
    answer_label->setText("No card");
    edit_button->setEnabled(false);
    for (auto &button : quality_buttons) {
      button->setEnabled(false);
    }
    return;
  }

  // 更新文本内容和按钮状态
  card_id = card->id;
  question_label->setText(card->question);
  answer_label->setText(card->answer);
  edit_button->setEnabled(true);
  for (auto &button : quality_buttons) {
    button->setEnabled(true);
  }
}

void StudyWindow::SetPack(CardPack *pack) {
  if (pack == nullptr) {
    // 特殊情况
    SetCard(nullptr);
    statusbar_label->setText("没有选择卡组");
    return;
  }

  SetCard(pack->ChooseCard(ReviewOption::random));

  int review_count = pack->CountCards(ReviewOption::random),
      total_count = pack->CountTotalCards();
  QString review_text;
  if (total_count == 0) {
    review_text = "卡组中没有卡片";
  } else if (review_count == 0) {
    review_text = "卡片都复习完啦";
  } else {
    review_text = QString{"还有 %1 张卡片要复习"}.arg(review_count);
  }
  statusbar_label->setText(review_text);
}

void StudyWindow::UpdateAppearance() {
  card_splitter->setStyleSheet(globals.settings.StyleSheet());
}

void StudyWindow::UpdateCard(Card &card) {
  if (card.id != card_id) return;

  SetCard(&card);
}

void StudyWindow::ChangePack(CardPack *pack) { SetPack(pack); }

void StudyWindow::UpdatePack(CardPack &pack) { SetPack(&pack); }

}  // namespace aijika
