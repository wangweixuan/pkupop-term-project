/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/studywindow.h"

#include "ui/managerwindow.h"
#include "ui/settingswindow.h"
#include "ui/composerdialog.h"
#include "ui/editordialog.h"

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
    globals.RestoreDatabase();
    setWindowTitle("学习卡片");

    // 顶部工具栏
    main_layout->addLayout(toolbar_layout);

    toolbar_layout->addWidget(pack_combo);

    toolbar_layout->addWidget(compose_button);
    connect(compose_button, &QPushButton::clicked, [this,&globals]() {
      auto window = new ComposerDialog{this,globals};
      window->show();
    });

    toolbar_layout->addWidget(edit_button);
    connect(edit_button, &QPushButton::clicked, [this,&globals]() {
      auto window = new EditorDialog{this,globals};
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
    question_label->setText("这是问题");

    card_layout->addWidget(answer_label);
    answer_label->setTextFormat(Qt::TextFormat::PlainText);
    answer_label->setText("这是答案 (应该隐藏)");

    card_layout->addWidget(show_answer_button);

    // 卡片反馈
    main_layout->addLayout(quality_layout);

    quality_layout->addWidget(quality_buttons[0]);

    quality_layout->addWidget(quality_buttons[1]);

    quality_layout->addWidget(quality_buttons[2]);

    quality_layout->addWidget(quality_buttons[3]);

    // 底部状态栏
    main_layout->addWidget(statusbar_label);
    statusbar_label->setText("还有 1 张卡片要复习");

    connect(&globals.settings, &AppSettings::appearance_updated, this,
          &StudyWindow::UpdateAppearance);
    connect(&globals.db, &CardDatabase::card_updated, this,
          &StudyWindow::UpdateCard);
    connect(pack_combo, &PackCombo::pack_changed, this, &StudyWindow::ChangePack);
    connect(pack_combo, &PackCombo::pack_updated, this, &StudyWindow::UpdatePack);

    UpdateAppearance();

    SetPack(pack_combo->GetPack());
    }

void StudyWindow::SetCard(Card *card) {
    // TODO: unimplemented
    if (card == nullptr) {
    // 特殊情况
      question_label->setText("暂无卡片");
      answer_label->setText("");
      show_answer_button->setEnabled(false);
      statusbar_label->setText("没有卡片可以复习");
      return;
    }
    // 更新文本内容和按钮状态
    question_label->setText(card->question);
    answer_label->setText("");
    show_answer_button->setEnabled(true);

    // 更新底部状态栏
    int review_count = 1;
    QString review_text = review_count == 1 ? "还有 1 张卡片要复习" :
    QString{"还有 %1 张卡片要复习"}.arg(review_count);
    statusbar_label->setText(review_text);

    // 更新卡片 ID
    card_id = card->id;
    }

void StudyWindow::SetPack(CardPack *pack) {
    // TODO: unimplemented
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

void StudyWindow::UpdateCard(Card &card) {
    if (card.id != card_id) return;
    // TODO: unimplemented
    // 更新底部状态栏
    int review_count = 1;
    QString review_text = review_count == 1 ? "还有 1 张卡片要复习" :
    QString{"还有 %1 张卡片要复习"}.arg(review_count);
    statusbar_label->setText(review_text);
    }

void StudyWindow::ChangePack(CardPack *pack) {
    // TODO: unimplemented
    SetPack(pack);
    }

void StudyWindow::UpdatePack(CardPack &pack) {
    // TODO: unimplemented
    (void)pack;
    }

    }  // namespace aijika
