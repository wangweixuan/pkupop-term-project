/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/generator.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <utility>

#include "generator/openai.h"
#include "generator/prompt.h"
#include "model/card.h"

namespace aijika {

CardGenerator::CardGenerator(QObject *parent, AppSettings &settings)
    : QObject{parent},
      mgr{new ApiManager{this}},
      settings{settings},
      prompts{LoadPromptsFromResources()} {
  connect(mgr, &ApiManager::response, this, &CardGenerator::ApiResponse);
  connect(mgr, &ApiManager::error, this, &CardGenerator::ApiError);
  connect(&settings, &AppSettings::api_updated, this,
          &CardGenerator::UpdateApiSettings);
  UpdateApiSettings();
}

void CardGenerator::Generate(Prompt const &prompt, QString keywords) {
  ApiRequest request;
  prompt.ToMessages(request, keywords.count('\n') + 1);

  request.SetModel(settings.api_model);
  request.AddMessage(ApiRequest::Role::user, keywords);

  mgr->Send(request);
}

void CardGenerator::ApiResponse(QString content) {
  QJsonParseError err;
  auto document = QJsonDocument::fromJson(content.toUtf8(), &err);
  if (document.isNull()) {
    emit error("生成器错误\n请重试\n\n详细信息：" + err.errorString());
    return;
  }
  if (!document.isArray()) {
    emit error("生成器错误\n请重试\n\n详细信息：格式错误");
    return;
  }

  CardStemList cards;
  for (auto elem : document.array()) {
    if (!elem.isArray()) continue;  // robustness
    auto element = elem.toArray();
    if (element.size() != 3) continue;  // robustness
    CardStem card;
    card.keyword = element[0].toString();
    card.question = element[1].toString();
    card.answer = element[2].toString();
    if (!card.keyword.size() || !card.question.size() || !card.answer.size())
      continue;  // robustness
    cards << std::move(card);
  }
  emit generated(std::move(cards));
}

void CardGenerator::ApiError(QString message) {
  emit error(std::move(message));
}

void CardGenerator::UpdateApiSettings() {
  mgr->api_base_url = settings.api_base_url;
  mgr->api_key = settings.api_key;
}

void CardGenerator::Abort() { mgr->Abort(); }

}  // namespace aijika
