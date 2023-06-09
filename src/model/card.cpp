/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "model/card.h"

#include <cmath>

namespace aijika {

QString CardStem::Details() const {
  auto line2 = QString{question}.replace('\r', ' ').replace('\n', ' ');
  auto line3 = QString{answer}.replace('\r', ' ').replace('\n', ' ');
  return QString{"%1\n正面：%2\n背面：%3"}.arg(keyword, line2, line3);
}

Card::Card()
    : id(-1),
      keyword(""),
      question(""),
      answer(""),
      time_created(QDateTime::currentDateTime()),
      time_reviewed(time_created),
      time_due(time_created),
      repetition(0),
      interval(1),
      easiness(2.5) {}

Card::Card(CardStem const &stem)
    : id(-1),
      keyword(stem.keyword),
      question(stem.question),
      answer(stem.answer),
      time_created(QDateTime::currentDateTime()),
      time_reviewed(time_created),
      time_due(time_created),
      repetition(0),
      interval(1),
      easiness(2.5) {}

Card &Card::operator=(CardStem const &stem) {
  keyword = stem.keyword;
  question = stem.question;
  answer = stem.answer;
  return *this;
}

QString Card::Summary() const {
  if (IsDue()) {
    return keyword + " (需复习)";
  }
  return keyword;
}

QString Card::Details() const {
  return CardStem{Summary(), question, answer}.Details();
}

bool Card::IsDue() const { return time_due <= QDateTime::currentDateTime(); }

void Card::Update(UserQuality quality) {
  if (quality == UserQuality::again) {
    easiness = std::max(1.3, easiness - 0.2);
    interval = 1;
  } else {
    int value = int(quality);
    easiness += 0.1 - value * (0.08 + value * 0.02);
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
