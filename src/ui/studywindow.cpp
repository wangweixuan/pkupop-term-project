/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */
#include "ui/studywindow.h"

#include <QMessageBox>

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
      card_widget{new QWidget{this}},
      card_layout{new QVBoxLayout{nullptr}},
      question_label{new QLabel{this}},
      answer_label{new QLabel{this}},
      show_answer_button{new QPushButton{"显示答案", this}},
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
  connect(compose_button, &QPushButton::clicked, [this, &globals]() {
    auto window = new ComposerDialog{this, globals};
    window->show();
  });

  toolbar_layout->addWidget(edit_button);
  connect(edit_button, &QPushButton::clicked, [this, &globals]() {
    if (GetCard() == nullptr) {
      QMessageBox::information(this, "编辑卡片", "请选择卡片.");
      return;
    }
    auto window =
        new EditorDialog{0, globals, GetCard(), pack_combo->GetPack()};
    window->show();
  });
  toolbar_layout->addWidget(manage_button);
  connect(manage_button, &QPushButton::clicked, [&globals]() {
    auto window = new ManagerWindow{globals};
    window->show();
  });

  toolbar_layout->addWidget(settings_button);
  connect(settings_button, &QPushButton::clicked, [&globals]() {
    auto window = new SettingsWindow{globals};
    window->show();
  });

  // 卡片
  main_layout->addWidget(card_widget, /* stretch */ 1);
  card_widget->setLayout(card_layout);

  card_layout->addWidget(question_label);
  question_label->setTextFormat(Qt::TextFormat::PlainText);

  card_layout->addWidget(answer_label);
  answer_label->setTextFormat(Qt::TextFormat::PlainText);
  answer_label->hide();

  card_layout->addWidget(show_answer_button);

  // 卡片反馈
  main_layout->addLayout(quality_layout);

  quality_layout->addWidget(quality_buttons[0]);

  quality_layout->addWidget(quality_buttons[1]);

  quality_layout->addWidget(quality_buttons[2]);

  quality_layout->addWidget(quality_buttons[3]);

  // 底部状态栏
  main_layout->addWidget(statusbar_label);

  connect(&globals.settings, &AppSettings::appearance_updated, this,
          &StudyWindow::UpdateAppearance);
  connect(&globals.db, &CardDatabase::card_updated, this,
          &StudyWindow::UpdateCard);
  connect(pack_combo, &PackCombo::pack_changed, this, &StudyWindow::ChangePack);
  connect(pack_combo, &PackCombo::pack_updated, this, &StudyWindow::UpdatePack);

  connect(show_answer_button, &QPushButton::clicked, answer_label,
          &QLabel::show);

  for (int i = 0; i < 4; i++) {
    connect(quality_buttons[i], &QPushButton::clicked, [this, i]() {
      Card *tmp = GetCard();
      UserQuality quality = static_cast<UserQuality>(4 - i);
      tmp->Update(quality);
      emit this->globals.db.card_updated(*tmp);
      SetPack(pack_combo->GetPack());
    });
  }

  UpdateAppearance();

  SetPack(pack_combo->GetPack());
}

Card *StudyWindow::GetCard() {
  auto pack = pack_combo->GetPack();
  if (pack == nullptr) return nullptr;

  return pack->FindCard(card_id);
}

void StudyWindow::SetCard(Card *card) {
  if (card == nullptr) {
    // 特殊情况
    card_id = -1;
    qDebug() << "StudyWindow SetCard: no card";
    question_label->setText("暂无卡片");
    answer_label->hide();
    show_answer_button->setEnabled(false);
    return;
  }

  card_id = card->id;
  // 更新文本内容和按钮状态
  question_label->setText(card->question);
  answer_label->setText(card->answer);
  answer_label->hide();
  show_answer_button->setEnabled(true);

  qDebug() << card->answer;
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
  auto style_sheet = globals.settings.StyleSheet();
  question_label->setStyleSheet(style_sheet);
  answer_label->setStyleSheet(style_sheet);
}

void StudyWindow::UpdateCard(Card &card) {
  if (card.id != card_id) return;

  SetCard(&card);
}

void StudyWindow::ChangePack(CardPack *pack) { SetPack(pack); }

void StudyWindow::UpdatePack(CardPack &pack) { SetPack(&pack); }

}  // namespace aijika
