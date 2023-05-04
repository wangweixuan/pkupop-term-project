/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/prompt.h"

namespace aijika {

Prompt::Prompt(QJsonObject const& obj) {
  // TODO: unimplemented
  (void)obj;
}

void Prompt::ToMessages(ApiRequest& request, int batch) const {
  // TODO: unimplemented
  (void)request, (void)batch;
}

QList<Prompt> LoadPromptsFromResources() {
  // TODO: unimplemented
  return {};
}

}  // namespace aijika
