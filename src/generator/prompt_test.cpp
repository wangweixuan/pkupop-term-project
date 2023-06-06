/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "generator/prompt.h"

#include <gtest/gtest.h>

#include "generator/openai.h"
#include "model/card.h"

namespace aijika {
namespace {

TEST(CardStemListTest, Encode) {
  CardStemList list;
  EXPECT_EQ(list.Encode(), "[]");

  list << CardStem{"k", "q", "a"};
  EXPECT_EQ(list.Encode(), R"([["k","q","a"]])");

  list << CardStem{"\"k\"\"", "q\n\t\n", "<a></a>"};
  EXPECT_EQ(list.Encode(),
            R"([["k","q","a"],["\"k\"\"","q\n\t\n","<a></a>"]])");
}

TEST(CardStemListTest, Decode) {
  CardStemList list;
  list.Decode("[]");
  EXPECT_EQ(list.size(), 0);

  list.clear();
  list.Decode(R"([["k","q","a"]])");
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list[0].keyword, "k");
  EXPECT_EQ(list[0].question, "q");
  EXPECT_EQ(list[0].answer, "a");

  list.clear();
  list.Decode(R"([["k","q","a"],["\"k\"\"","q\n\t\n","<a></a>"]])");
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list[1].keyword, "\"k\"\"");
  EXPECT_EQ(list[1].question, "q\n\t\n");
  EXPECT_EQ(list[1].answer, "<a></a>");
}

TEST(PromptTest, ToMessages) {
  Prompt prompt;
  prompt.system = "s";
  prompt.examples << CardStem{"k", "q", "a"}
                  << CardStem{"\"k\"\"", "q\n\t\n", "<a></a>"};

  ApiRequest request;
  request.SetModel("gpt-3.5-turbo");
  prompt.ToMessages(request, 2);

  EXPECT_EQ(
      request.Build(),
      R"({"messages":[{"content":"s","role":"system"},{"content":"k\n\"k\"\"","role":"user"},{"content":"[[\"k\",\"q\",\"a\"],[\"\\\"k\\\"\\\"\",\"q\\n\\t\\n\",\"<a></a>\"]]","role":"assistant"}],"model":"gpt-3.5-turbo"})");
}

TEST(PromptTest, LoadFromData) {
  QByteArray contents{R"([
    {
      "id": 101,
      "label": "a1",
      "system": "s1",
      "examples": [
        {
          "keyword": "k1",
          "question": "q1",
          "answer": "a1"
        },
        {
          "keyword": "k2",
          "question": "q2",
          "answer": "a2"
        }
      ]
    },
    {
      "id": 102,
      "label": "a2",
      "system": "s2",
      "examples": [
        {
          "keyword": "k3",
          "question": "q3",
          "answer": "a3"
        }
      ]
    }
  ])"};
  auto prompts = LoadPromptsFromData(contents);

  EXPECT_EQ(prompts.size(), 2);
  EXPECT_EQ(prompts[0].id, 101);
  EXPECT_EQ(prompts[0].label, "a1");
  EXPECT_EQ(prompts[0].examples.size(), 2);
  EXPECT_EQ(prompts[0].examples[0].keyword, "k1");
  EXPECT_EQ(prompts[0].examples[1].answer, "a2");
  EXPECT_EQ(prompts[1].system, "s2");
  EXPECT_EQ(prompts[1].examples.size(), 1);
}

TEST(PromptTest, LoadFromResources) {
  auto prompts = LoadPromptsFromResources();

  EXPECT_EQ(prompts[0].id, 101);
  EXPECT_EQ(prompts[0].label, "英译中");
}

}  // namespace
}  // namespace aijika
