/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include <QApplication>
#include <QMessageBox>

#include "common/globals.h"
#include "ui/studywindow.h"

int main(int argc, char *argv[]) {
  using namespace aijika;

  QApplication app{argc, argv};
  app.setOrganizationName("PKU POP");
  app.setApplicationName("Aijika");
  app.setApplicationDisplayName("AI 记卡");

  AppGlobals globals{&app};
  globals.RestoreSettings();
  globals.RestoreDatabase();

  StudyWindow window{globals};
  window.show();

  if (globals.db.packs.isEmpty()) {
    QMessageBox::information(
        &window, "AI 记卡",
        "欢迎使用《AI 记卡》！\n\n"
        "您可以在“管理卡片”窗口中添加卡组及卡片。"
        "在使用 AI 服务生成卡片前，您需要在设置中填写 API 网址及密钥。\n\n"
        "在“学习卡片”窗口中，您可以选择卡组，浏览和学习其中的卡片。"
        "程序将根据您的反馈，自动安排复习方案。\n\n"
        "祝您使用愉快！");
  }

  return app.exec();
}
