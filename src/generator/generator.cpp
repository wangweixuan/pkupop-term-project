/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/generator.h"

namespace aijika {

CardGenerator::CardGenerator(QObject *parent)
    : QObject{parent}, mgr{*new ApiManager{parent}} {}

void CardGenerator::Generate(Prompt const &prompt, QString keywords) {
  // TODO: unimplemented
  (void)prompt, (void)keywords;
}

void CardGenerator::Abort() { mgr.Abort(); }

void CardGenerator::ApiResponse(QString content) {
  // TODO: unimplemented
  (void)content;
}

void CardGenerator::ApiError(QString message) {
  // TODO: unimplemented
  (void)message;
}

}  // namespace aijika
