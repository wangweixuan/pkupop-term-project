/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QFile>
#include <QObject>

#include "common/settings.h"
#include "model/database.h"

namespace aijika {

/// 程序的全局状态.
class AppGlobals : public QObject {
  Q_OBJECT;

 public:
  /// 程序的设置文件.
  QFile settings_file;
  /// 程序的数据库文件.
  QFile db_file;
  /// 程序的全局设置.
  AppSettings settings;
  /// 程序的全局数据库.
  CardDatabase db;

  /// 初始化全局状态. 应在初始化前设置 QCoreApplication 的 organizationName 和
  /// applicationName 属性.
  explicit AppGlobals(QObject *parent);

 public slots:
  /// 保存设置到文件.
  void SaveSettings();
  /// 从文件读取设置.
  void RestoreSettings();

  /// 保存数据库到文件.
  void SaveDatabase();
  /// 从文件读取数据库.
  void RestoreDatabase();
};

}  // namespace aijika
