/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "model/card.h"

namespace aijika {

Card::Card() {
  // TODO: unimplemented
}

Card::Card(CardStem const &stem) {
  // TODO: unimplemented
  (void)stem;
}

void Card::Update(UserQuality quality) {
  // TODO: unimplemented
  (void)quality;
}

QDataStream &operator<<(QDataStream &out, Card const &card) {
  // TODO: unimplemented
  (void)card;
  return out;
}

QDataStream &operator>>(QDataStream &in, Card &card) {
  // TODO: unimplemented
  (void)card;
  return in;
}

}  // namespace aijika
