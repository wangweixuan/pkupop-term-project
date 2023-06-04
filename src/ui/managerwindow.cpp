/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/managerwindow.h"

#include <QInputDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QtDebug>

#include "model/database.h"
#include "ui/components/packcombo.h"
#include "ui/composerdialog.h"
#include "ui/editordialog.h"

namespace aijika {

ManagerWindow::ManagerWindow(AppGlobals &globals)
    : QWidget{nullptr},
      globals{globals},
      main_layout{new QVBoxLayout{this}},
      top_layout{new QHBoxLayout{nullptr}},
      pack_toolbar_layout{new QVBoxLayout{nullptr}},
      add_pack_button{new QPushButton{"添加卡组", this}},
      rename_pack_button{new QPushButton{"重命名", this}},
      remove_pack_button{new QPushButton{"删除卡组", this}},
      pack_combo{new PackCombo{this, globals}},
      card_toolbar_layout{new QHBoxLayout{nullptr}},
      compose_card_button{new QPushButton{"创建卡片", this}},
      // export_pack_button{new QPushButton{" ",this}},
      // import_pack_button{new QPushButton{" ",this}},

      edit_card_button{new QPushButton{"编辑卡片", this}},
      remove_card_button{new QPushButton{"删除卡片", this}},
      choosepack_text{new QLabel{"选择卡组", this}},
      card_list{new QListWidget{this}} {
  setWindowTitle("管理卡片");
  pack_toolbar_layout->addWidget(add_pack_button);
  pack_toolbar_layout->addWidget(rename_pack_button);
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

  connect(&globals.db, &CardDatabase::card_updated, this,
          &ManagerWindow::UpdateCard);
  connect(pack_combo, &PackCombo::pack_updated, this,
          &ManagerWindow::UpdatePack);
  connect(pack_combo, &PackCombo::pack_changed, this,
          &ManagerWindow::ChangePack);

  connect(add_pack_button, &QPushButton::clicked, this,
          &ManagerWindow::AddPack);
  connect(rename_pack_button, &QPushButton::clicked, this,
          &ManagerWindow::RenamePack);
  connect(remove_pack_button, &QPushButton::clicked, this,
          &ManagerWindow::RemovePack);

  connect(card_list, &QListWidget::currentItemChanged, this,
          &ManagerWindow::ChangeItem);
  connect(compose_card_button, &QPushButton::clicked, this, [&globals]() {
    auto dialog = new ComposerDialog{0, globals};
    dialog->show();
  });
  connect(edit_card_button, &QPushButton::clicked, this, [&globals, this]() {
    if (card_list->currentItem() == NULL) {
      QMessageBox::information(this, "编辑卡片", "请选择卡片.");
      return;
    }
    int cardid = card_list->currentItem()->data(0).toInt();
    auto dialog =
        new EditorDialog{0, globals, pack_combo->GetPack()->FindCard(cardid),
                         pack_combo->GetPack()};
    dialog->show();
  });
  connect(remove_card_button, &QPushButton::clicked, this, [&globals, this]() {
    if (card_list->currentItem() == NULL) {
      QMessageBox::information(this, "删除卡片", "请选择卡片.");
      return;
    }
    globals.db.RemoveCard(card_list->currentItem()->data(0).toInt(),
                          *pack_combo->GetPack());
  });
  ChangeItem(nullptr);
  // TODO: 实现编辑卡片
  // connect(compose_card_button,&QPushButton::clicked,[globals]);
}

void ManagerWindow::SetPack(CardPack *pack) {
  card_list->clear();
  if (pack == nullptr) {
    return;
  }

  for (auto &card : pack->cards) {
    // TODO: 给 item 绑定 data (即 card.id), 这样就能知道当前选择的卡片了
    QListWidgetItem *item = new QListWidgetItem(card.keyword, card_list);
    item->setData(0, card.id);
    card_list->addItem(item);
  }
}

void ManagerWindow::UpdateCard(Card &card) {
  // TODO: unimplemented
  (void)card;
}

void ManagerWindow::ChangePack(CardPack *pack) { SetPack(pack); }

void ManagerWindow::UpdatePack(CardPack &pack) {
  // TODO: 记录当前选中的 card, 并在刷新列表后尝试选中原来的 card
  SetPack(&pack);
}

void ManagerWindow::AddPack() {
  // TODO: 用对话框实现添加卡组.
  QString text =
      QInputDialog::getText(this, "packname_input", "请输入新创建卡组名称:");
  globals.db.AddPack(text);
}

void ManagerWindow::RenamePack() {
  auto pack = pack_combo->GetPack();
  if (pack == nullptr) {
    qWarning() << "ManagerWindow RenamePack: no pack";
    QMessageBox::information(this, "Error", "请选择卡组.");
    return;
  }
  QString text = QInputDialog::getText(this, "Rename", "请重命名:");
  globals.db.RenamePack(text, *pack);

  // TODO: 用对话框实现重命名
}

void ManagerWindow::RemovePack() {
  auto pack = pack_combo->GetPack();
  if (pack == nullptr) {
    qWarning() << "ManagerWindow RemovePack: no pack";
    return;
  }
  globals.db.RemovePack(pack->id);
}

void ManagerWindow::ChangeItem(QListWidgetItem *item) {
  // TODO: unimplemented
  if (item == nullptr) {
    edit_card_button->setEnabled(false);
    remove_card_button->setEnabled(false);
  }

  edit_card_button->setEnabled(true);
  remove_card_button->setEnabled(true);
}

}  // namespace aijika
