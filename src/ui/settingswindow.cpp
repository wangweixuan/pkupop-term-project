/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/settingswindow.h"

namespace aijika {

SettingsWindow::SettingsWindow(AppGlobals &globals)
    : QWidget{nullptr}, globals{globals} {
  setWindowTitle("设置");

  // TODO: layout unimplemented
}

}  // namespace aijika
