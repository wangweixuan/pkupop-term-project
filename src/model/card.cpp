/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "model/card.h"

#include <cmath>

namespace aijika {

Card::Card()
    : id(-1),
      keyword(""),
      question(""),
      answer(""),
      time_created(QDateTime::currentDateTime()),
      time_reviewed(QDateTime::currentDateTime()),
      time_due(QDateTime::currentDateTime()),
      repetition(0),
      interval(1),
      easiness(2.5) {}

Card::Card(CardStem const &stem)
    : id(-1),
      keyword(stem.keyword),
      question(stem.question),
      answer(stem.answer),
      time_created(QDateTime::currentDateTime()),
      time_reviewed(QDateTime::currentDateTime()),
      time_due(QDateTime::currentDateTime().addDays(1)),
      repetition(0),
      interval(0),
      easiness(2.5) {}

void Card::Update(UserQuality qualityy) {
  int quality = int(qualityy);
  interval = 1;
  if (qualityy == UserQuality::again) {
    easiness = std::max(1.3, easiness - 0.2);
    interval = 1;
  } else {
    easiness += 0.1 - quality * (0.08 + quality * 0.02);
    easiness = std::max(1.3, easiness);
    interval = std::round(interval * easiness);
  }
  repetition++;
  time_reviewed = QDateTime::currentDateTime();
  time_due = time_reviewed.addDays(interval);
}

QDataStream &operator<<(QDataStream &out, Card const &card) {
  out << card.id;
  out << card.keyword;
  out << card.question;
  out << card.answer;
  out << card.time_created;
  out << card.time_reviewed;
  out << card.time_due;
  out << card.repetition;
  out << card.interval;
  out << card.easiness;
  return out;
}

QDataStream &operator>>(QDataStream &in, Card &card) {
  in >> card.id;
  in >> card.keyword;
  in >> card.question;
  in >> card.answer;
  in >> card.time_created;
  in >> card.time_reviewed;
  in >> card.time_due;
  in >> card.repetition;
  in >> card.interval;
  in >> card.easiness;
  return in;
}

}  // namespace aijika
