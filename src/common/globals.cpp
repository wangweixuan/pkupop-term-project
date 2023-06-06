/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "common/globals.h"

#include <QDataStream>
#include <QDir>
#include <QStandardPaths>
#include <QString>
#include <QtDebug>

#include "common/settings.h"

namespace aijika {

using Loc = QStandardPaths::StandardLocation;

QString GetFile(QString const &fileName, Loc loc) {
  QDir dir{QStandardPaths::writableLocation(loc)};
  dir.mkpath(".");
  return dir.absoluteFilePath(fileName);
}

AppGlobals::AppGlobals(QObject *parent)
    : QObject{parent},
      settings_file{GetFile("settings.bin", Loc::AppConfigLocation)},
      db_file{GetFile("db.bin", Loc::AppDataLocation)} {
  connect(&settings, &AppSettings::appearance_updated, this,
          &AppGlobals::SaveSettings);
  connect(&settings, &AppSettings::learning_updated, this,
          &AppGlobals::SaveSettings);
  connect(&settings, &AppSettings::api_updated, this,
          &AppGlobals::SaveSettings);
  connect(&db, &CardDatabase::card_updated, this, &AppGlobals::SaveDatabase);
  connect(&db, &CardDatabase::pack_updated, this, &AppGlobals::SaveDatabase);
  connect(&db, &CardDatabase::list_updated, this, &AppGlobals::SaveDatabase);
}

void AppGlobals::SaveSettings() {
  qDebug() << "Save settings:" << settings_file.fileName();

  settings_file.open(QFile::WriteOnly);
  QDataStream out{&settings_file};
  out << settings;
  settings_file.close();
}

void AppGlobals::RestoreSettings() {
  if (!settings_file.exists()) return;
  qDebug() << "Restore settings:" << settings_file.fileName();

  settings_file.open(QFile::ReadOnly);
  QDataStream in{&settings_file};
  in >> settings;
  settings_file.close();
}

void AppGlobals::SaveDatabase() {
  qDebug() << "Save database:" << db_file.fileName();

  db_file.open(QFile::WriteOnly);
  QDataStream out{&db_file};
  out << db;
  db_file.close();
}

void AppGlobals::RestoreDatabase() {
  if (!db_file.exists()) return;
  qDebug() << "Restore database:" << db_file.fileName();

  db_file.open(QFile::ReadOnly);
  QDataStream in{&db_file};
  in >> db;
  db_file.close();
}

}  // namespace aijika
