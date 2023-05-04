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

void ManagerWindow::InvalidatePack(CardPack &pack) {
  // TODO: unimplemented
  (void)pack;
}

void ManagerWindow::InvalidateList() {
  // TODO: unimplemented
}

}  // namespace aijika
