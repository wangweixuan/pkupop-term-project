/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QFormLayout>
#include <QWidget>

#include "common/globals.h"

namespace aijika {

/// 设置窗口.
class SettingsWindow : public QWidget {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  QFormLayout *main_layout;

 public:
  explicit SettingsWindow(AppGlobals &globals);
};

}  // namespace aijika
