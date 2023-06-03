/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/managerwindow.h"

#include "model/database.h"
#include "ui/composerdialog.h"
#include "ui/editordialog.h"

namespace aijika {

ManagerWindow::ManagerWindow(AppGlobals &globals)
    : QWidget{nullptr},
      globals{globals},
      main_layout{new QVBoxLayout{this}},
      choosepack_text{new QLabel{"选择卡组", this}},
      pack_combo{new PackCombo{this, globals}},
      pack_toolbar_layout{new QVBoxLayout{this}},
      add_pack_button{new QPushButton{"添加卡组", this}},
      edit_pack_button{new QPushButton{"重命名", this}},
      remove_pack_button{new QPushButton{"删除卡组", this}},
      top_layout{new QHBoxLayout{this}},
      card_list{new QListWidget{this}},
      // export_pack_button{new QPushButton{" ",this}},
      // import_pack_button{new QPushButton{" ",this}},

      card_toolbar_layout{new QHBoxLayout{this}},
      compose_card_button{new QPushButton{"增加卡片", this}},
      edit_card_button{new QPushButton{"编辑卡片", this}},
      remove_card_button{new QPushButton{"删除卡片", this}}

{
  setWindowTitle("管理卡片");
  pack_toolbar_layout->addWidget(add_pack_button);
  pack_toolbar_layout->addWidget(edit_pack_button);
  pack_toolbar_layout->addWidget(remove_pack_button);
  top_layout->addWidget(choosepack_text);
  top_layout->addWidget(pack_combo);
  top_layout->addLayout(pack_toolbar_layout);

  card_toolbar_layout->addWidget(compose_card_button);
  card_toolbar_layout->addWidget(edit_card_button);
  card_toolbar_layout->addWidget(remove_card_button);

  main_layout->addLayout(top_layout);
  main_layout->addWidget(card_list);
  main_layout->addLayout(card_toolbar_layout);

  // set
  pack_combo->setFixedWidth(200);

  for (int i = 0; i < globals.db.incremental_pack_id; i++) {
    if (globals.db.FindPack(i) == nullptr) continue;
    pack_combo->addItem(globals.db.FindPack(i)->label,
                        globals.db.FindPack(i)->id);
  }
  /// 在pack_combo中加入pack，以名字作为索引
  if (pack_combo->GetPack() == nullptr) {
  } else {
    if (pack_combo->currentIndex() >= 0 &&
        pack_combo->currentIndex() < globals.db.incremental_pack_id) {
      card_list->show();
      card_list->clear();
      for (auto &cardd : pack_combo->GetPack()->cards) {
        card_list->addItem(cardd.keyword);
      }
    }
  }
  connect(pack_combo, &PackCombo ::currentIndexChanged, this,
          &ManagerWindow::ChangePack);

  /// 添加卡组
  connect(add_pack_button, &QPushButton::clicked, [&globals]() {
    auto dialog = new ComposerDialog{0, globals};
    dialog->show();
  });
  connect(&globals.db, &CardDatabase::list_updated, this,
          &ManagerWindow::UpdatePack);

  /// 重命名
  connect(edit_pack_button, &QPushButton::clicked, [&globals]() {
    auto dialog = new EditorDialog{0, globals};
    dialog->show();
  });

  /// 删除
  connect(remove_pack_button, &QPushButton::clicked, this,
          &ManagerWindow::RemovePack);

  /// 增加卡片
  // connect(compose_card_button,&QPushButton::clicked,[globals]);

  // TODO: layout unimplemented
}

void ManagerWindow::SetPack(CardPack *pack) {
  // TODO: unimplemented
  (void)pack;
}

void ManagerWindow::UpdateCard(Card &card) {
  // TODO: unimplemented
  (void)card;
}

void ManagerWindow::ChangePack() {
  // TODO: unimplemented
  qDebug() << "no!!!!!1";
  card_list->show();
  card_list->clear();
  if (pack_combo->GetPack()) {
    for (auto &cardd : pack_combo->GetPack()->cards) {
      card_list->addItem(cardd.keyword);
    }
  }
}

void ManagerWindow::UpdatePack() {
  // TODO: unimplemented
  disconnect(pack_combo, &PackCombo ::currentIndexChanged, this,
             &ManagerWindow::ChangePack);
  pack_combo->clear();
  connect(pack_combo, &PackCombo ::currentIndexChanged, this,
          &ManagerWindow::ChangePack);
  pack_combo->show();
  qDebug() << globals.db.incremental_pack_id;
  for (int i = 0; i < globals.db.incremental_pack_id; ++i) {
    qDebug() << "i:" << i;
    if (globals.db.FindPack(i) == nullptr) continue;
    qDebug() << "i:" << i;
    pack_combo->addItem(globals.db.FindPack(i)->label,
                        globals.db.FindPack(i)->id);
  }
}

void ManagerWindow::RemovePack() {
  qDebug() << pack_combo->currentData().toInt() << "   !";
  globals.db.RemovePack(pack_combo->currentData().toInt());
}
}  // namespace aijika
