/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/composerdialog.h"

#include <QBoxLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QScrollArea>
#include <QScrollBar>

#include "components/packcombo.h"
#include "generator/generator.h"
#include "generator/prompt.h"

namespace aijika {

ComposerDialog::ComposerDialog(QWidget *parent, AppGlobals &globals)
    : QDialog{parent},
      globals{globals},
      generator{new CardGenerator{this, globals.settings}},
      prompts{LoadPromptsFromResources()},
      main_layout{new QFormLayout{this}},
      prompt_combo{new QComboBox{this}},
      keywords_input{new QTextEdit{this}},
      button_layout{new QHBoxLayout{nullptr}},
      generate_button{new QPushButton{"生成预览", this}},
      cancel_button{new QPushButton{"清空预览", this}},
      generated_layout{new QStackedLayout{(QWidget *)nullptr}},
      generated_area{new QScrollArea{this}},
      generated_list{new QListWidget{this}},
      error_label{new QLabel{this}},
      pack_combo{new PackCombo{this, globals}},
      bottom_button_layout{new QHBoxLayout{nullptr}},
      confirm_button{new QPushButton{"保存", this}},
      leave_button{new QPushButton{"取消", this}} {
  setWindowTitle("创建卡片");

  main_layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
  main_layout->setFormAlignment(Qt::AlignLeft);
  main_layout->setLabelAlignment(Qt::AlignRight);

  main_layout->addRow("模板：", prompt_combo);
  main_layout->addRow("关键词：", keywords_input);
  button_layout->addWidget(generate_button);
  button_layout->addWidget(cancel_button);
  main_layout->addRow(" ", button_layout);
  main_layout->addRow("生成结果：", generated_layout);
  generated_layout->addWidget(generated_area);
  generated_layout->addWidget(error_label);
  generated_area->setWidget(generated_list);
  main_layout->addRow("所属卡组：", pack_combo);
  bottom_button_layout->addWidget(confirm_button);
  bottom_button_layout->addWidget(leave_button);
  main_layout->addRow(" ", bottom_button_layout);

  prompt_combo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  pack_combo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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

  ShowError("无卡片");
}

void ComposerDialog::Generate() {
  Prompt *prompt;
  prompt_id_t id = prompt_combo->currentData().toInt();
  for (auto &p : prompts) {
    if (p.id == id) {
      prompt = &p;
      break;
    }
  }
  generator->Generate(*prompt, keywords_input->toPlainText());

  ShowError("正在生成……");
  cancel_button->setEnabled(true);
}

void ComposerDialog::Cancel() {
  // 点击cancel就清空
  generator->Abort();
  generated_list->clear();

  ShowError("无卡片");
}

void ComposerDialog::Confirm() {
  auto pack = pack_combo->GetPack();
  if (pack == nullptr) {
    QMessageBox::information(this, "生成卡片", "请选择卡组。");
    return;
  }

  for (auto &card : this->generated_cards) {
    globals.db.AddCard(card, *pack);
  }

  close();
}

void ComposerDialog::ShowResults(CardStemList cards) {
  generated_layout->setCurrentWidget(generated_area);
  cancel_button->setEnabled(true);
  confirm_button->setEnabled(true);

  // 用一个列表显示新生成的卡片.
  generated_cards = cards;  // 记录一下生成的卡片, 或许有用.
  generated_list->clear();  // 清空当前列表中显示的卡片.

  for (auto &card : cards) {
    generated_list->addItem(card.Details());
  }
}

void ComposerDialog::ShowError(QString message) {
  generated_layout->setCurrentWidget(error_label);
  cancel_button->setEnabled(false);
  confirm_button->setEnabled(false);

  // 清空当前列表中显示的卡片.
  generated_cards.clear();
  generated_list->clear();

  // 用一个 label 显示错误信息
  error_label->setText(message);
}

}  // namespace aijika
