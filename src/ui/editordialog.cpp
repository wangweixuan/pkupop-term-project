/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/editordialog.h"

namespace aijika {

EditorDialog::EditorDialog(QWidget *parent, AppGlobals &globals)
    : QDialog{parent},
      globals{globals},
      pack_list{new PackCombo{this, globals}},
      choosecard_text{new QLabel{"选择卡片:", this}},
      choosepack_text{new QLabel{"选择卡组", this}},
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
      card_list{new QListWidget{this}} {
  setWindowTitle("编辑卡片");

  /// 布局
  /// 大小调整
  keyword_edit->setFixedHeight(40);
  front_edit->setFixedHeight(60);
  back_edit->setFixedHeight(60);
  pack_list->setFixedWidth(300);
  /// 加入布局
  hori_layout[0]->addWidget(choosepack_text);
  hori_layout[0]->addWidget(pack_list);
  hori_layout[1]->addWidget(choosecard_text);
  hori_layout[1]->addWidget(card_list);
  hori_layout[2]->addWidget(keyword_text);
  hori_layout[2]->addWidget(keyword_edit);
  hori_layout[3]->addWidget(front_text);
  hori_layout[3]->addWidget(front_edit);
  hori_layout[4]->addWidget(back_text);
  hori_layout[4]->addWidget(back_edit);
  /// 布局调整
  hori_layout[1]->setAlignment(Qt::AlignLeft);
  hori_layout[2]->setAlignment(Qt::AlignLeft);
  hori_layout[2]->setSpacing(20);
  hori_layout[3]->setSpacing(30);
  hori_layout[4]->setSpacing(30);

  main_layout->addLayout(hori_layout[0]);
  main_layout->addLayout(hori_layout[1]);
  main_layout->addLayout(hori_layout[2]);
  main_layout->addLayout(hori_layout[3]);
  main_layout->addLayout(hori_layout[4]);

  /// 在card_list中加入card，以keyword作为索引
  qDebug() << pack_list->currentIndex();
  if (pack_list->GetPack() == nullptr) {
  } else {
    if (pack_list->currentIndex() >= 0 &&
        pack_list->currentIndex() < globals.db.incremental_pack_id) {
      card_list->show();
      card_list->clear();
      for (auto &cardd : pack_list->GetPack()->cards) {
        card_list->addItem(cardd.keyword);
      }
    }
  }

  // TODO: 不确定 editor dialog 是否需要切换卡组的功能
  // 这里暂未更改
  connect(pack_list, &PackCombo ::currentIndexChanged, this,
          &EditorDialog::changecard);

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

void EditorDialog::changecard() {
  qDebug() << pack_list->currentIndex();
  card_list->show();
  card_list->clear();
  for (auto &cardd : pack_list->GetPack()->cards) {
    card_list->addItem(cardd.keyword);
  }
}

}  // namespace aijika
