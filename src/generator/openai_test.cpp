/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/openai.h"

#include <gtest/gtest.h>

#include <QEventLoop>
#include <QObject>
#include <QString>
#include <QtGlobal>

namespace aijika {
namespace {

ApiRequest ExampleRequest() {
  using Role = ApiRequest::Role;

  ApiRequest request;
  request.SetModel("gpt-3.5-turbo");
  request.AddMessage(Role::user, "Say hello, World!");
  request.AddMessage(Role::assistant, "Hello, World!");
  request.AddMessage(Role::user, "Say hello, Aijika!");

  return request;
}

TEST(OpenAiTest, BuildRequest) {
  auto request = ExampleRequest();

  EXPECT_EQ(
      request.Build(),
      R"({"messages":[{"content":"Say hello, World!","role":"user"},{"content":"Hello, World!","role":"assistant"},{"content":"Say hello, Aijika!","role":"user"}],"model":"gpt-3.5-turbo"})");
}

TEST(OpenAiTest, DISABLED_SendRequest) {
  ApiManager mgr{nullptr};
  auto api_base_url = qEnvironmentVariable("OPENAI_BASE_URL");
  auto api_key = qEnvironmentVariable("OPENAI_API_KEY");
  if (api_base_url.size()) {
    mgr.api_base_url = api_base_url;
  }
  if (api_key.size()) {
    mgr.api_key = api_key;
  }

  auto request = ExampleRequest();

  QEventLoop loop;

  QObject::connect(&mgr, &ApiManager::response, [&loop](QString content) {
    EXPECT_EQ(content, "Hello, Aijika!");
    loop.quit();
  });
  QObject::connect(&mgr, &ApiManager::error, [&loop](QString message) {
    ADD_FAILURE() << message.toStdString();
    loop.quit();
  });

  mgr.Send(request);

  loop.exec();
}

}  // namespace
}  // namespace aijika
