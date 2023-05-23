/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "common/globals.h"

#include <gtest/gtest.h>

#include "common/settings.h"

namespace aijika {
namespace {

TEST(GlobalsTest, SaveRestore) {
  {
    AppGlobals globals;
    globals.RestoreDatabase();

    globals.settings.font_size = 42;
    globals.SaveSettings();
  }
  {
    AppGlobals globals;

    globals.db.last_visited_pack = 17;
    globals.SaveDatabase();
  }
  {
    AppGlobals globals;
    globals.RestoreSettings();

    EXPECT_EQ(globals.settings.font_size, 42);
  }
}

}  // namespace
}  // namespace aijika
