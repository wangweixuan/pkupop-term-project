/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/prompt.h"

#include <QFile>
#include <QIODevice>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QStringList>
#include <QtDebug>
#include <algorithm>

namespace aijika {

CardStemList::CardStemList(QList<CardStem> const &list) : QList{list} {}

QByteArray CardStemList::Encode() const {
  QJsonArray array;
  for (auto &card : *this) {
    QJsonArray element;
    element << card.keyword << card.question << card.answer;
    array << element;
  }
  QJsonDocument document{array};
  return document.toJson(QJsonDocument::Compact);
}

void CardStemList::Decode(QByteArray const &content) {
  auto document = QJsonDocument::fromJson(content);

  for (auto elem : document.array()) {
    auto element = elem.toArray();
    CardStem card;
    card.keyword = element[0].toString();
    card.question = element[1].toString();
    card.answer = element[2].toString();
    *this << std::move(card);
  }
}

void Prompt::ToMessages(ApiRequest &request, qsizetype batch) const {
  using Role = ApiRequest::Role;

  request.AddMessage(Role::system, system);

  for (qsizetype i = 0; i < examples.size(); i += batch) {
    CardStemList slice{
        examples.sliced(i, std::min(examples.size() - i, batch))};

    QStringList keywords;
    for (auto const &ex : slice) {
      keywords << ex.keyword;
    }
    request.AddMessage(Role::user, keywords.join('\n'));

    request.AddMessage(Role::assistant, slice.Encode());
  }
}

QList<Prompt> LoadPromptsFromResources() {
  QFile file{":/resources/prompts.json"};
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qCritical() << "Open prompts from resources:" << file.error();
    return {};
  }
  auto contents = file.readAll();
  file.close();

  return LoadPromptsFromData(contents);
}

QList<Prompt> LoadPromptsFromData(QByteArray const &data) {
  QJsonParseError err;
  auto document = QJsonDocument::fromJson(data, &err);
  if (document.isNull()) {
    qCritical() << "Parse prompts from resources:" << err.errorString();
    return {};
  }

  QList<Prompt> prompts;
  for (auto obj : document.array()) {
    auto object = obj.toObject();
    Prompt prompt;
    prompt.id = object["id"].toInt();
    prompt.label = object["label"].toString();
    prompt.system = object["system"].toString();
    for (auto ex : object["examples"].toArray()) {
      auto example = ex.toObject();
      CardStem card;
      card.keyword = example["keyword"].toString();
      card.question = example["question"].toString();
      card.answer = example["answer"].toString();
      prompt.examples << std::move(card);
    }
    prompts << std::move(prompt);
  }
  return prompts;
}

}  // namespace aijika
