/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "common/settings.h"

namespace aijika {

AppSettings::AppSettings() {
  // TODO: unimplemented
}

QFont AppSettings::font() const {
  // TODO: unimplemented
  return {};
}

QDataStream &operator<<(QDataStream &out, AppSettings const &settings) {
  // TODO: unimplemented
  (void)settings;
  return out;
}

QDataStream &operator>>(QDataStream &in, AppSettings &settings) {
  // TODO: unimplemented
  (void)settings;
  return in;
}

}  // namespace aijika
