/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/generator.h"

namespace aijika {

CardGenerator::CardGenerator(QObject *parent, AppSettings &settings)
    : QObject{parent},
      mgr{new ApiManager{this}},
      settings{settings},
      prompts{LoadPromptsFromResources()} {
  connect(&settings, &AppSettings::api_updated, this,
          &CardGenerator::UpdateApiSettings);
  UpdateApiSettings();
}

void CardGenerator::Generate(Prompt const &prompt, QString keywords) {
  // TODO: unimplemented
  (void)prompt, (void)keywords;
}

void CardGenerator::ApiResponse(QString content) {
  // TODO: unimplemented
  (void)content;
}

void CardGenerator::ApiError(QString message) {
  // TODO: unimplemented
  (void)message;
}

void CardGenerator::UpdateApiSettings() {
  mgr->api_base_url = settings.api_base_url;
  mgr->api_key = settings.api_key;
}

void CardGenerator::Abort() { mgr->Abort(); }

}  // namespace aijika
