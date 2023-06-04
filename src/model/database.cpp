/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "model/database.h"

namespace aijika {

CardDatabase::CardDatabase()
    : QObject(nullptr),
      incremental_pack_id(0),
      incremental_card_id(0),
      last_visited_pack(-1) {}

CardPack *CardDatabase::FindPack(pack_id_t id) {
  for (auto &pack : packs) {
    if (pack.id == id) {
      return &pack;
    }
  }
  return nullptr;
}

void CardDatabase::AddPack(QString const &label) {
  CardPack pack = {incremental_pack_id++, label, QList<Card>(), -1};
  packs.append(pack);
  emit list_updated();
}

void CardDatabase::RenamePack(QString const &label, CardPack &pack) {
  pack.label = label;
  emit list_updated();
}

void CardDatabase::RemovePack(pack_id_t pack) {
  packs.erase(std::remove_if(packs.begin(), packs.end(),
                             [=](CardPack &p) { return p.id == pack; }),
              packs.end());
  emit list_updated();
}

void CardDatabase::AddCard(CardStem const &stem, CardPack &pack) {
  Card card(stem);
  card.id = incremental_card_id++;
  pack.cards.append(card);
  emit pack_updated(pack);
}

void CardDatabase::EditCard(CardStem const &stem, Card &card) {
  card = stem;
  emit card_updated(card);
}

void CardDatabase::RemoveCard(card_id_t card, CardPack &pack) {
  pack.cards.erase(std::remove_if(pack.cards.begin(), pack.cards.end(),
                                  [=](Card &c) { return c.id == card; }),
                   pack.cards.end());
  emit pack_updated(pack);
}

QDataStream &operator<<(QDataStream &out, CardDatabase const &db) {
  out << db.packs;
  out << db.incremental_pack_id;
  out << db.incremental_card_id;
  out << db.last_visited_pack;
  return out;
}

QDataStream &operator>>(QDataStream &in, CardDatabase &db) {
  /* db.packs.clear(); */
  in >> db.packs;
  in >> db.incremental_pack_id;
  in >> db.incremental_card_id;
  in >> db.last_visited_pack;
  return in;
}

}  // namespace aijika
