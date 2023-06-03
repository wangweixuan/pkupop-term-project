/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include <QApplication>

#include "common/globals.h"
#include "ui/studywindow.h"

int main(int argc, char *argv[]) {
  using namespace aijika;

  QApplication app{argc, argv};
  app.setOrganizationName("PKU POP");
  app.setApplicationName("Aijika");
  app.setApplicationDisplayName("AI 记卡");

  AppGlobals globals{&app};

  CardStem card1{"apple", "Which fruit is red, round and juicy?", "Apple."};
  CardStem card2{"dog", "What domesticated animal is a man's best friend?",
                 "Dog."};
  CardStem card3{
      "python",
      "What is the name of the programming language with an animal name?",
      "Python."};
  CardStem card4{"math", "What subject studies numbers and their properties?",
                 "Mathematics."};
  CardStem card5{"guitar",
                 "What musical instrument is often used in rock music?",
                 "Guitar."};
  CardStem card6{"tea", "What drink is commonly consumed in China and Britain?",
                 "Tea."};
  CardStem card7{"jupiter", "What is the largest planet in the solar system?",
                 "Jupiter."};
  CardStem card8{"apple", "What fruit did Isaac Newton discover gravity with?",
                 "Apple."};
  CardStem card9{"leonardo", "What was the first name of da Vinci?",
                 "Leonardo."};
  CardStem card10{
      "samsung",
      "What company is the largest smartphone manufacturer in the world?",
      "Samsung."};
  CardStem card11{"dog", "What animal is Lassie?", "Dog."};
  CardStem card12{"python",
                  "What popular programming language was named after a British "
                  "comedy group?",
                  "Python."};
  CardStem card13{"soccer", "What sport is called football in most countries?",
                  "Soccer."};

  globals.db.AddPack("测试集1");
  globals.db.AddPack("测试集2");
  globals.db.AddPack("测试集3");

  globals.db.AddCard(card1, globals.db.packs[0]);
  globals.db.AddCard(card2, globals.db.packs[0]);
  globals.db.AddCard(card3, globals.db.packs[0]);
  globals.db.AddCard(card4, globals.db.packs[1]);
  globals.db.AddCard(card5, globals.db.packs[1]);
  globals.db.AddCard(card6, globals.db.packs[1]);
  globals.db.AddCard(card7, globals.db.packs[1]);
  globals.db.AddCard(card8, globals.db.packs[2]);
  globals.db.AddCard(card9, globals.db.packs[2]);
  globals.db.AddCard(card10, globals.db.packs[2]);
  globals.db.AddCard(card11, globals.db.packs[2]);
  globals.db.AddCard(card12, globals.db.packs[2]);
  globals.db.AddCard(card13, globals.db.packs[2]);

  globals.SaveDatabase();

  StudyWindow window{globals};
  window.show();
  return app.exec();
}
