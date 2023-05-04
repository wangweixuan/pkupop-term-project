/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "model/database.h"

namespace aijika {

CardPack *CardDatabase::FindPack(pack_id_t id) {
  // TODO: unimplemented
  (void)id;
  return nullptr;
}

void CardDatabase::AddPack(QString const &label) {
  // TODO: unimplemented
  (void)label;
}

void CardDatabase::RemovePack(pack_id_t pack) {
  // TODO: unimplemented
  (void)pack;
}

void CardDatabase::AddCard(CardStem const &stem, CardPack &pack) {
  // TODO: unimplemented
  (void)stem, (void)pack;
}

void CardDatabase::RemoveCard(card_id_t card, CardPack &pack) {
  // TODO: unimplemented
  (void)card, (void)pack;
}

QDataStream &operator<<(QDataStream &out, CardDatabase const &db) {
  // TODO: unimplemented
  (void)db;
  return out;
}

QDataStream &operator>>(QDataStream &in, CardDatabase &db) {
  // TODO: unimplemented
  (void)db;
  return in;
}

}  // namespace aijika
