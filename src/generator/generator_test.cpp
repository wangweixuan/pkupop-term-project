/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/generator.h"

#include <gtest/gtest.h>

#include <QEventLoop>
#include <QObject>
#include <QString>
#include <QtGlobal>

#include "common/settings.h"
#include "generator/prompt.h"

namespace aijika {
namespace {

TEST(GeneratorTest, DISABLED_Generate) {
  AppSettings settings{};
  auto api_base_url = qEnvironmentVariable("OPENAI_BASE_URL");
  auto api_key = qEnvironmentVariable("OPENAI_API_KEY");
  if (api_base_url.size()) {
    settings.api_base_url = api_base_url;
  }
  if (api_key.size()) {
    settings.api_key = api_key;
  }
  CardGenerator gen{nullptr, settings};

  auto prompts = LoadPromptsFromResources();

  QEventLoop loop;

  QObject::connect(&gen, &CardGenerator::generated,
                   [&loop](CardStemList cards) {
                     EXPECT_EQ(cards.size(), 2);
                     EXPECT_EQ(cards[0].keyword, "hello");
                     EXPECT_EQ(cards[1].keyword, "world");
                     loop.quit();
                   });
  QObject::connect(&gen, &CardGenerator::error, [&loop](QString message) {
    ADD_FAILURE() << message.toStdString();
    loop.quit();
  });

  gen.Generate(prompts[0], "hello\nworld");

  loop.exec();
}

}  // namespace
}  // namespace aijika
