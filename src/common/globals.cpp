/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "common/globals.h"

#include <QDir>
#include <QStandardPaths>
#include <QtDebug>

namespace aijika {

using Loc = QStandardPaths::StandardLocation;

QString GetFile(QString const &fileName, Loc loc) {
  QDir dir{QStandardPaths::writableLocation(loc)};
  dir.mkpath(".");
  return dir.absoluteFilePath(fileName);
}

AppGlobals::AppGlobals()
    : settings_file{GetFile("settings.json", Loc::AppConfigLocation)},
      db_file{GetFile("db.json", Loc::AppDataLocation)} {}

void AppGlobals::SaveSettings() {
  // TODO: unimplemented
  qDebug() << "Save settings:" << settings_file.fileName();
}

void AppGlobals::RestoreSettings() {
  // TODO: unimplemented
  qDebug() << "Restore settings:" << settings_file.fileName();
}

void AppGlobals::SaveDatabase() {
  // TODO: unimplemented
  qDebug() << "Save database:" << db_file.fileName();
}

void AppGlobals::RestoreDatabase() {
  // TODO: unimplemente
  qDebug() << "Restore database:" << db_file.fileName();
}

}  // namespace aijika
