/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/composerdialog.h"

namespace aijika {

ComposerDialog::ComposerDialog(QWidget *parent, AppGlobals &globals)
    : QDialog{parent}, globals{globals} {
  setWindowTitle("创建卡片");

  // TODO: layout unimplemented
}

void ComposerDialog::SetPack(CardPack *pack) {
  // TODO: unimplemented
  (void)pack;
}

void ComposerDialog::InvalidateList() {
  // TODO: unimplemented
}

}  // namespace aijika
