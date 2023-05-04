/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/editordialog.h"

namespace aijika {

EditorDialog::EditorDialog(QWidget *parent, AppGlobals &globals)
    : QDialog{parent}, globals{globals} {
  setWindowTitle("编辑卡片");

  // TODO: layout unimplemented
}

void EditorDialog::SetCard(Card *card) {
  // TODO: unimplemented
  (void)card;
}

void EditorDialog::SetPack(CardPack *pack) {
  // TODO: unimplemented
  (void)pack;
}

void EditorDialog::InvalidatePack(CardPack &pack) {
  // TODO: unimplemented
  (void)pack;
}

void EditorDialog::InvalidateList() {
  // TODO: unimplemented
}

}  // namespace aijika
