/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/composerdialog.h"

#include <QBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QScrollArea>
#include <QScrollBar>

#include "generator/generator.h"
#include "generator/prompt.h"

namespace aijika {

ComposerDialog::ComposerDialog(QWidget *parent, AppGlobals &globals)
    : QDialog{parent},
      globals{globals},
      generator{new CardGenerator{this, globals.settings}},
      prompts{LoadPromptsFromResources()},
      pack_combo{new PackCombo{this, globals}},
      prompt_combo{new QComboBox{this}},
      keywords_input{new QTextEdit{this}},
      generate_button{new QPushButton{"生成", this}},
      cancel_button{new QPushButton{"取消", this}},
      confirm_button{new QPushButton{"确认", this}},
      leave_button{new QPushButton{"退出", this}},

      main_layout{new QVBoxLayout{this}},
      hori_layout{new QHBoxLayout{nullptr}, new QHBoxLayout{nullptr},
                  new QHBoxLayout{nullptr}, new QHBoxLayout{nullptr},
                  new QHBoxLayout{nullptr}, new QHBoxLayout{nullptr}},

      generate_text{new QScrollArea{this}},

      generate_list{new QListWidget{generate_text}},

      question_label{new QLabel{"模板:", this}},
      keywords_label{new QLabel{"关键词:", this}},
      generate_label{new QLabel{"生成结果:", this}},
      error_label{new QLabel{"生成出错啦", this}} {
  setWindowTitle("创建卡片");

  generate_text->setFixedSize(300, 200);
  generate_text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);  // 滚动条
  generate_text->setWidget(generate_list);
  generate_list->setGeometry(0, 0, 300, 1200);  // 主要是设置长宽，xy意义不大

  hori_layout[1]->addWidget(question_label);
  hori_layout[1]->addWidget(prompt_combo);
  hori_layout[2]->addWidget(keywords_label);
  hori_layout[2]->addWidget(keywords_input);
  hori_layout[3]->addWidget(generate_button);
  hori_layout[3]->addWidget(cancel_button);
  hori_layout[4]->addWidget(generate_label);
  hori_layout[4]->addWidget(generate_text);
  hori_layout[5]->addWidget(confirm_button);
  hori_layout[5]->addWidget(leave_button);

  hori_layout[1]->setAlignment(Qt::AlignLeft);
  hori_layout[1]->setSpacing(18);
  hori_layout[2]->setAlignment(Qt::AlignHCenter);
  hori_layout[3]->setAlignment(Qt::AlignHCenter);
  hori_layout[4]->setAlignment(Qt::AlignHCenter);
  hori_layout[5]->setAlignment(Qt::AlignRight);
  prompt_combo->setFixedSize(150, 30);

  main_layout->addLayout(hori_layout[1]);
  main_layout->addLayout(hori_layout[2]);
  main_layout->addLayout(hori_layout[3]);
  main_layout->addLayout(hori_layout[4]);
  main_layout->addLayout(hori_layout[5]);

  error_label->hide();
  error_label->setAlignment(Qt::AlignCenter);

  connect(generator, &CardGenerator::generated, this,
          &ComposerDialog::ShowResults);
  connect(generator, &CardGenerator::error, this, &ComposerDialog::ShowError);

  connect(generate_button, &QPushButton::clicked, this,
          &ComposerDialog::Generate);
  connect(cancel_button, &QPushButton::clicked, this, &ComposerDialog::Cancel);
  connect(confirm_button, &QPushButton::clicked, this,
          &ComposerDialog::Confirm);
  connect(leave_button, &QPushButton::clicked, this, &ComposerDialog::close);

  for (auto const &prompt : prompts) {
    prompt_combo->addItem(prompt.label, prompt.id);
  }
}

void ComposerDialog::Generate() {
  auto const &prompt = prompts[prompt_combo->currentIndex()];
  generator->Generate(prompt, keywords_input->toPlainText());
}

void ComposerDialog::Cancel() {
  // 点击cancel就清空
  generator->Abort();
  generate_list->clear();
}

void ComposerDialog::Confirm() {
  auto pack = pack_combo->GetPack();
  if (pack == nullptr) {
    QMessageBox::information(this, "生成卡片", "请选择卡组.");
    return;
  }

  for (auto &card : this->generated_cards) {
    globals.db.AddCard(card, *pack);
  }

  close();
}

void ComposerDialog::ShowResults(CardStemList cards) {
  error_label->hide();

  // 用一个列表显示新生成的卡片.
  generate_list->show();
  generated_cards = cards;  // 记录一下生成的卡片, 或许有用.

  generate_list->clear();  // 清空当前列表中显示的卡片.

  for (auto &card : cards) {
    // 将卡片转换成一个字符串.
    auto s = QStringList{"关键词: ",    card.keyword, "\n正面: ",
                         card.question, "\n背面: ",   card.answer}
                 .join("");
    // 将字符串添加到列表.
    generate_list->addItem(s);
  }
}

void ComposerDialog::ShowError(QString message) {
  // 清空当前列表中显示的卡片.
  generated_cards.clear();
  generate_list->hide();

  // 用一个 label 显示错误信息
  error_label->setText(message);
  error_label->show();
}

}  // namespace aijika
