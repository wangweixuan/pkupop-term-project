/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "model/pack.h"

namespace aijika {

Card *CardPack::FindCard(card_id_t id) {
  // TODO: unimplemented
  (void)id;
  return nullptr;
}

Card *CardPack::ChooseCard(ReviewOption opt) {
  // TODO: unimplemented
  (void)opt;
  return nullptr;
}

QDataStream &operator<<(QDataStream &out, CardPack const &pack) {
  // TODO: unimplemented
  (void)pack;
  return out;
}

QDataStream &operator>>(QDataStream &in, CardPack &pack) {
  // TODO: unimplemented
  (void)pack;
  return in;
}

}  // namespace aijika
