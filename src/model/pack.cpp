/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "model/pack.h"

#include <QRandomGenerator>
#include <cmath>

namespace aijika {

Card *CardPack::FindCard(card_id_t id) {
  for (auto &card : cards) {
    if (card.id == id) {
      return &card;
    }
  }
  return nullptr;
}

Card *CardPack::ChooseCard(ReviewOption opt) {
  QList<Card *> candidates;
  QDateTime now = QDateTime::currentDateTime();
  for (auto &card : cards) {
    if (card.time_due <= now) {
      candidates.append(&card);
    }
  }
  if (candidates.empty()) {
    return nullptr;
  }
  if (opt == ReviewOption::random) {
    return candidates[QRandomGenerator::global()->bounded(candidates.size())];
  }
  Card *chosen = candidates[0];
  for (int i = 1; i < candidates.size(); i++) {
    if (opt == ReviewOption::last_reviewed) {
      if (candidates[i]->time_reviewed > chosen->time_reviewed) {
        chosen = candidates[i];
      }
    } else if (opt == ReviewOption::due_date) {
      if (candidates[i]->time_due > chosen->time_due) {
        chosen = candidates[i];
      }
    }
  }

  return chosen;
}

int CardPack::CountCards(ReviewOption opt) const {
  (void)opt;
  QDateTime now = QDateTime::currentDateTime();
  int count = 0;
  for (auto const &card : cards) {
    if (card.time_due <= now) {
      count++;
    }
  }
  return count;
}

int CardPack::CountTotalCards() const { return cards.size(); }

QDataStream &operator<<(QDataStream &out, CardPack const &pack) {
  out << pack.id;
  out << pack.label;
  out << pack.cards;
  out << pack.last_prompt;
  return out;
}

QDataStream &operator>>(QDataStream &in, CardPack &pack) {
  in >> pack.id;
  in >> pack.label;
  /* pack.cards.clear(); */
  in >> pack.cards;
  in >> pack.last_prompt;
  return in;
}

}  // namespace aijika
