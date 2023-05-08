/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/components/packcombo.h"

namespace aijika {

PackCombo::PackCombo(QWidget *parent, AppGlobals &globals)
    : QComboBox{parent}, globals{globals} {}

CardPack *PackCombo::GetPack() {
  // TODO: unimplemented
  return nullptr;
}

void PackCombo::SetPack(CardPack *pack) {
  // TODO: unimplemented
  (void)pack;
}

void PackCombo::UpdatePack(CardPack &pack) {
  // TODO: unimplemented
  (void)pack;
}

void PackCombo::UpdateList() {
  // TODO: unimplemented
}

}  // namespace aijika
