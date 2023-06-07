/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/editordialog.h"

#include <QMessageBox>

namespace aijika {

EditorDialog::EditorDialog(QWidget *parent, AppGlobals &globals, Card *card,
                           CardPack *pack)
    : QDialog{parent},
      globals{globals},
      card_id{card->id},
      pack_id{pack->id},
      main_layout{new QFormLayout{this}},
      keyword_edit{new QLineEdit{this}},
      front_edit{new QTextEdit{this}},
      back_edit{new QTextEdit{this}},
      repetition_label{new QLabel{this}},
      time_created_label{new QLabel{this}},
      time_reviewed_label{new QLabel{this}},
      time_due_label{new QLabel{this}},
      button_layout{new QHBoxLayout{nullptr}},
      save_button{new QPushButton{"保存", this}},
      cancel_button{new QPushButton{"取消", this}} {
  setWindowTitle("编辑卡片");

  // 布局
  main_layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
  main_layout->setFormAlignment(Qt::AlignLeft);
  main_layout->setLabelAlignment(Qt::AlignRight);

  main_layout->addRow("关键词：", keyword_edit);
  main_layout->addRow("正面：", front_edit);
  main_layout->addRow("背面：", back_edit);
  main_layout->addRow("复习次数：", repetition_label);
  main_layout->addRow("创建时间：", time_created_label);
  main_layout->addRow("最近复习：", time_reviewed_label);
  main_layout->addRow("下次复习：", time_due_label);

  button_layout->addWidget(save_button);
  button_layout->addWidget(cancel_button);
  main_layout->addRow(" ", button_layout);

  QString date_format{"yyyy 年 M 月 d 日 h:mm"};
  keyword_edit->setText(card->keyword);
  front_edit->setPlainText(card->question);
  back_edit->setPlainText(card->answer);
  repetition_label->setText(QString::number(card->repetition));
  time_created_label->setText(card->time_created.toString(date_format));
  if (card->repetition == 0) {
    time_reviewed_label->setText("未复习");
  } else {
    time_reviewed_label->setText(card->time_reviewed.toString(date_format));
  }
  time_due_label->setText(card->time_due.toString(date_format));
  if (card->IsDue()) {
    time_due_label->setText(time_due_label->text() + " (已到期)");
  }

  connect(save_button, &QPushButton::clicked, this, &EditorDialog::Save);
  connect(cancel_button, &QPushButton::clicked, this, &EditorDialog::close);
}

void EditorDialog::Save() {
  auto pack = globals.db.FindPack(pack_id);
  if (pack == nullptr) {
    QMessageBox::information(this, "编辑卡片", "卡组已删除。");
    close();
    return;
  }
  auto card = pack->FindCard(card_id);
  if (card == nullptr) {
    QMessageBox::information(this, "编辑卡片", "卡片已删除。");
    close();
    return;
  }

  CardStem stem{keyword_edit->text(), front_edit->toPlainText(),
                back_edit->toPlainText()};
  globals.db.EditCard(stem, *card);
  close();
}

}  // namespace aijika
