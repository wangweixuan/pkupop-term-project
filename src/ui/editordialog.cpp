/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/editordialog.h"

#include "generator/generator.h"

namespace aijika {

EditorDialog::EditorDialog(QWidget *parent, AppGlobals &globals, Card *card,
                           CardPack *pack)
    : QDialog{parent},
      globals{globals},
      card_id(card->id),
      pack_id(pack->id),
      keyword_text{new QLabel{"关键词:", this}},
      front_text{new QLabel{"正面:", this}},
      back_text{new QLabel{"反面:", this}},
      keyword_edit{new QTextEdit{this}},
      front_edit{new QTextEdit{this}},
      back_edit{new QTextEdit{this}},
      main_layout{new QVBoxLayout{this}},
      hori_layout{new QHBoxLayout{nullptr}, new QHBoxLayout{nullptr},
                  new QHBoxLayout{nullptr}, new QHBoxLayout{nullptr},
                  new QHBoxLayout{nullptr}, new QHBoxLayout{nullptr}},
      save_button{new QPushButton{"保存", this}},
      cancel_button{new QPushButton{"取消", this}} {
  setWindowTitle("编辑卡片");

  /// 布局
  /// 大小调整
  keyword_edit->setFixedHeight(40);
  front_edit->setFixedHeight(60);
  back_edit->setFixedHeight(60);
  /// 加入布局
  hori_layout[0]->addWidget(keyword_text);
  hori_layout[0]->addWidget(keyword_edit);
  hori_layout[1]->addWidget(front_text);
  hori_layout[1]->addWidget(front_edit);
  hori_layout[2]->addWidget(back_text);
  hori_layout[2]->addWidget(back_edit);
  hori_layout[3]->addWidget(save_button);
  hori_layout[3]->addWidget(cancel_button);
  /// 布局调整

  hori_layout[0]->setAlignment(Qt::AlignLeft);
  hori_layout[0]->setSpacing(20);
  hori_layout[1]->setSpacing(30);
  hori_layout[2]->setSpacing(30);

  main_layout->addLayout(hori_layout[0]);
  main_layout->addLayout(hori_layout[1]);
  main_layout->addLayout(hori_layout[2]);
  main_layout->addLayout(hori_layout[3]);
  main_layout->addLayout(hori_layout[4]);
  keyword_edit->setText(card->keyword);
  front_edit->setText(card->question);
  back_edit->setText(card->answer);

  connect(save_button, &QPushButton::clicked, this,
          [&globals, this, card, pack]() {
            CardStem stem;
            stem.keyword = keyword_edit->toPlainText();
            stem.question = front_edit->toPlainText();
            stem.answer = back_edit->toPlainText();
            globals.db.editcard(stem, card, *pack);
            this->close();
          });
  connect(cancel_button, &QPushButton::clicked, this, &EditorDialog::close);
  // TODO: layout unimplemented
}

void EditorDialog::SetCard(Card &card) {
  // TODO: unimplemented

  (void)card;
}

void EditorDialog::SetPack(CardPack &pack) {
  // TODO: unimplemented
  (void)pack;
}

}  // namespace aijika
