/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include <gtest/gtest.h>

#include <QCoreApplication>
#include <QTimer>

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);

  QCoreApplication app{argc, argv};
  app.setOrganizationName("PKU POP Test");
  app.setApplicationName("Aijika Test");

  QTimer::singleShot(0, [&app]() { app.exit(RUN_ALL_TESTS()); });

  return app.exec();
}
