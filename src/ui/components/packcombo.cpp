/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/components/packcombo.h"

#include <QtDebug>

#include "model/pack.h"

namespace aijika {

// 构造函数
PackCombo::PackCombo(QWidget *parent, AppGlobals &globals)
    : QComboBox(parent), globals(globals) {
  // 设置QComboBox属性
  setToolTip("选择卡组");

  connect(&globals.db, &CardDatabase::pack_updated, this,
          &PackCombo::UpdatePack);
  connect(&globals.db, &CardDatabase::list_updated, this,
          &PackCombo::UpdateList);
  connect(this, &QComboBox::currentIndexChanged, this, &PackCombo::ChangeIndex);

  SetList();

  int index = findData(globals.db.last_visited_pack);
  if (index == -1) {
    setCurrentIndex(0);
    return;
  }
  setCurrentIndex(index);
}

void PackCombo::SetList() {
  clear();

  // 添加无卡组选项
  addItem("(无卡组)", -1);

  // 将所有卡组加入QComboBox
  for (auto const &pack : globals.db.packs) {
    addItem(pack.label, pack.id);
  }
}

// 获取所选卡组
CardPack *PackCombo::GetPack() {
  pack_id_t pack_id = currentIndex() == -1 ? -1 : currentData().toInt();

  if (pack_id == -1) {
    return nullptr;
  }
  return globals.db.FindPack(pack_id);
}

// 设置所选卡组
void PackCombo::SetPack(CardPack *pack) {
  if (pack == nullptr) {
    setCurrentIndex(0);
    return;
  }
  int index = findData(pack->id);
  if (index == -1) {  // 保险，防止调用了没有的pack;
    setCurrentIndex(0);
    qWarning() << "PackCombo SetPack: not found";
    return;
  }
  setCurrentIndex(index);
}

void PackCombo::SetLastVisited() {
  globals.db.last_visited_pack = currentData().toInt();
}

// 更新卡组信息
void PackCombo::UpdatePack(CardPack &pack) {
  int index = findData(pack.id);
  if (index == -1) {
    qWarning() << "PackCombo UpdatePack: not found";
    return;
  }

  setItemText(index, pack.label);

  if (index == currentIndex()) {
    emit pack_updated(pack);
  }
}

// 更新卡组列表
void PackCombo::UpdateList() {
  pack_id_t old_pack = currentIndex() == -1 ? -1 : currentData().toInt();

  SetList();

  // 重新设置选中项
  int index = findData(old_pack);
  if (index == -1) {
    setCurrentIndex(0);
    return;
  }
  setCurrentIndex(index);
}

void PackCombo::ChangeIndex(int index) {
  pack_id_t new_pack_id = itemData(index).toInt();

  // 如果选中卡组发生变化，则更新卡组信息
  CardPack *new_pack =
      (new_pack_id == -1) ? nullptr : globals.db.FindPack(new_pack_id);
  emit pack_changed(new_pack);
}

}  // namespace aijika
