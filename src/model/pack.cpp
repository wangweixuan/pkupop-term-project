/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "model/pack.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

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
    if (card.time_reviewed.daysTo(now) >= card.interval) {
      candidates.append(&card);
    }
  }
  if (candidates.empty()) {
    return nullptr;
  }
  if (opt == ReviewOption::random) {
    std::srand(std::time(nullptr));
    int i = std::rand() % candidates.size();
    return candidates[i];
  }
  Card *chosen = candidates[0];
  for (int i = 1; i < candidates.size(); i++) {
    if (opt == ReviewOption::last_reviewed) {
      if (candidates[i]->time_reviewed.daysTo(now) >
          chosen->time_reviewed.daysTo(now)) {
        chosen = candidates[i];
      }
    } else if (opt == ReviewOption::due_date) {
      if (candidates[i]->time_due < chosen->time_due) {
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
  for (auto &card : cards) {
    if (card.time_reviewed.daysTo(now) >= card.interval) {
      count++;
    }
  }
  return count;
}

int CardPack::CountTotalCards() const { return cards.size(); }

QDataStream &operator<<(QDataStream &out, CardPack const &pack) {
  out << pack.id;
  out << pack.label;
  int tmp = pack.cards.size();
  out << tmp;
  out << pack.cards;
  out << pack.last_prompt;
  return out;
}

QDataStream &operator>>(QDataStream &in, CardPack &pack) {
  int n;
  in >> pack.id;
  in >> pack.label;
  in >> n;
  pack.cards.clear();
  in >> pack.cards;
  in >> pack.last_prompt;
  return in;
}

}  // namespace aijika
