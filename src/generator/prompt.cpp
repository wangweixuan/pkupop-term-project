/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/prompt.h"

namespace aijika {

void Prompt::ToMessages(ApiRequest &request) const {
  // TODO: unimplemented
  (void)request;
}

QList<Prompt> LoadPromptsFromResources() {
  // TODO: unimplemented
  return {};
}

QString EncodeCardStems(QList<CardStem> const &cards) {
  // TODO: unimplemented
  (void)cards;
  return "";
}

QList<CardStem> DecodeCardStems(QString const &content) {
  // TODO: unimplemented
  (void)content;
  return {};
}

}  // namespace aijika
