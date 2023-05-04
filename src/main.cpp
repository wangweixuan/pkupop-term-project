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

  AppGlobals globals;

  StudyWindow window{globals};
  window.show();

  return app.exec();
}
