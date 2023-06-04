/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/managerwindow.h"

#include <QInputDialog>
#include <QListWidgetItem>
#include <QtDebug>

#include "model/card.h"
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
      choosepack_text{new QLabel{"卡组：", this}},
      pack_combo{new PackCombo{this, globals}},
      add_pack_button{new QPushButton{"添加", this}},
      pack_toolbar_layout{new QHBoxLayout{nullptr}},
      rename_pack_button{new QPushButton{"重命名", this}},
      remove_pack_button{new QPushButton{"删除卡组", this}},
      // export_pack_button{new QPushButton{" ",this}},
      // import_pack_button{new QPushButton{" ",this}},
      card_list{new QListWidget{this}},
      details_check{new QCheckBox{"显示详细信息", this}},
      card_toolbar_layout{new QHBoxLayout{nullptr}},
      compose_card_button{new QPushButton{"创建卡片", this}},
      edit_card_button{new QPushButton{"编辑卡片", this}},
      remove_card_button{new QPushButton{"删除卡片", this}} {
  setWindowTitle("管理卡片");
  top_layout->addWidget(choosepack_text);
  top_layout->addWidget(pack_combo);
  top_layout->addWidget(add_pack_button);
  pack_toolbar_layout->addWidget(rename_pack_button);
  pack_toolbar_layout->addWidget(remove_pack_button);

  pack_combo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  card_toolbar_layout->addWidget(compose_card_button);
  card_toolbar_layout->addWidget(edit_card_button);
  card_toolbar_layout->addWidget(remove_card_button);

  main_layout->addLayout(top_layout);
  main_layout->addLayout(pack_toolbar_layout);
  main_layout->addWidget(card_list);
  main_layout->addWidget(details_check);
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

  connect(details_check, &QCheckBox::stateChanged, this,
          &ManagerWindow::ChangePack);
  connect(card_list, &QListWidget::currentItemChanged, this,
          &ManagerWindow::ChangeItem);
  connect(compose_card_button, &QPushButton::clicked, this, [&]() {
    pack_combo->SetLastVisited();
    auto dialog = new ComposerDialog{this, globals};
    dialog->show();
  });
  connect(edit_card_button, &QPushButton::clicked, this, [&]() {
    auto card = GetCard();
    if (card == nullptr) {
      qWarning() << "ManagerWindow EditCard: no card";
      return;
    }
    auto dialog = new EditorDialog{this, globals, card, pack_combo->GetPack()};
    dialog->show();
  });
  connect(remove_card_button, &QPushButton::clicked, this, [&]() {
    auto card = GetCard();
    if (card == nullptr) {
      qWarning() << "ManagerWindow RemoveCard: no card";
      return;
    }
    globals.db.RemoveCard(card->id, *pack_combo->GetPack());
  });

  ChangePack();
  ChangeItem(nullptr);
}

void ManagerWindow::ChangePack() {
  auto pack = pack_combo->GetPack();

  card_list->clear();
  if (pack == nullptr) {
    rename_pack_button->setEnabled(false);
    remove_pack_button->setEnabled(false);
    return;
  }

  bool details = details_check->isChecked();
  rename_pack_button->setEnabled(true);
  remove_pack_button->setEnabled(true);
  for (auto &card : pack->cards) {
    auto text = details ? card.Details() : card.Summary();
    QListWidgetItem *item = new QListWidgetItem(text, card_list);
    item->setData(QListWidgetItem::UserType, card.id);
    card_list->addItem(item);
  }
}

Card *ManagerWindow::GetCard() {
  auto item = card_list->currentItem();
  auto pack = pack_combo->GetPack();
  if (item == nullptr || pack == nullptr) {
    return nullptr;
  }
  int card_id = item->data(QListWidgetItem::UserType).toInt();
  return pack->FindCard(card_id);
}

void ManagerWindow::UpdateCard(Card &card) {
  (void)card;
  UpdatePack();
}

void ManagerWindow::UpdatePack() {
  int old_row = card_list->currentRow();
  ChangePack();
  card_list->setCurrentRow(old_row);
}

void ManagerWindow::AddPack() {
  bool is_ok;
  QString text = QInputDialog::getText(this, "添加卡组", "请输入新卡组名称：",
                                       QLineEdit::Normal, "新卡组", &is_ok);
  if (!is_ok || text.isEmpty()) return;
  globals.db.AddPack(text);
}

void ManagerWindow::RenamePack() {
  auto pack = pack_combo->GetPack();
  if (pack == nullptr) {
    qWarning() << "ManagerWindow RenamePack: no pack";
    return;
  }
  bool is_ok;
  QString text = QInputDialog::getText(
      this, "重命名", QString{"请输入卡组“%1”的新名称："}.arg(pack->label),
      QLineEdit::Normal, pack->label, &is_ok);
  if (!is_ok || text.isEmpty()) return;
  globals.db.RenamePack(text, *pack);
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
  if (item == nullptr) {
    edit_card_button->setEnabled(false);
    remove_card_button->setEnabled(false);
    return;
  }

  edit_card_button->setEnabled(true);
  remove_card_button->setEnabled(true);
}

}  // namespace aijika
