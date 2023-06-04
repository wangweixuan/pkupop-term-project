/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "common/settings.h"

#include <gtest/gtest.h>

namespace aijika {
namespace {

TEST(SettingsTest, StyleSheet) {
  AppSettings settings;

  EXPECT_EQ(
      settings.StyleSheet(),
      "QFrame, QPushButton { font-family: Optima, Candara, 'Noto Sans', "
      "source-sans-pro, STKaiti, '楷体', sans-serif; font-size: 14pt; "
      "background-color: #f9f4e9; color: #000000; border: none; }QLabel { "
      "padding: 5px 14px; }QSplitter:handle { background-color: #000000 }");
}

}  // namespace
}  // namespace aijika
