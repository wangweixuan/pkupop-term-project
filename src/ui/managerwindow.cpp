/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/managerwindow.h"

namespace aijika {

ManagerWindow::ManagerWindow(AppGlobals &globals)
    : QWidget{nullptr}, globals{globals} {
  setWindowTitle("管理卡片");

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

void ManagerWindow::ChangePack(CardPack *pack) {
  // TODO: unimplemented
  (void)pack;
}

void ManagerWindow::UpdatePack(CardPack &pack) {
  // TODO: unimplemented
  (void)pack;
}

}  // namespace aijika
