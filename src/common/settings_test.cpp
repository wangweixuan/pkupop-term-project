/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "common/settings.h"

#include <gtest/gtest.h>

namespace aijika {
namespace {

TEST(SettingsTest, StyleSheet) {
  AppSettings settings;

  EXPECT_EQ(settings.StyleSheet(),
            "QFrame { font-family: 'Optima, Candara, 'Noto Sans', "
            "source-sans-pro, '黑体', sans-serif' ; font-size: 14 ; "
            "background-color: #f9f4e9 ; color: #000000 ; }");
}

}  // namespace
}  // namespace aijika
