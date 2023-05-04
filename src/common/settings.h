/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QDataStream>
#include <QFont>
#include <QObject>
#include <QString>

namespace aijika {

/// 可供选择的卡片字体.
enum struct PredefinedFont {
  old_style,     // Old style 字体.
  transitional,  // Transitional 字体.
  neo_grotesk,   // Neo-Grotesk 字体.
  geometric,     // Geometric 字体.
  humanistic,    // Humanistic 字体.
};

/// 可供选择的卡片颜色主题.
enum struct PredefinedTheme {
  white,   // 白底黑字.
  yellow,  // 黄底黑字.
  grey,    // 灰底白字.
  black,   // 黑底白字.
};

/// 程序的设置, 与设置文件关联.
class AppSettings : public QObject {
  Q_OBJECT;

 public:
  // 显示设置

  /// 卡片界面的字体. 默认为 humanistic.
  PredefinedFont font_family;
  /// 卡片界面的字号. 默认为 14.
  int font_size;
  /// 卡片界面的颜色主题. 默认为 yellow.
  PredefinedTheme theme;

  // 学习设置

  // API 设置

  /// OpenAI API 的 URL. 默认为 "https://api.openai.com/v1/chat/completions".
  QString api_url;
  /// OpenAI API 的密钥.
  QString api_key;
  /// OpenAI API 的 model 参数. 默认为 "gpt-3.5-turbo".
  QString api_model;

  /// 初始化默认设置.
  explicit AppSettings();

  /// 由 font_family 和 font_size 生成 QFont.
  QFont font() const;

  /// 将 settings 序列化到数据流 out.
  friend QDataStream &operator<<(QDataStream &out, AppSettings const &settings);
  /// 从数据流 in 反序列化 settings.
  friend QDataStream &operator>>(QDataStream &in, AppSettings &settings);

 signals:
  /// 显示设置更新时发出的信号.
  void appearance_updated();
  /// 学习设置更新时发出的信号.
  void learning_updated();
  /// API 设置更新时发出的信号.
  void api_updated();
};

}  // namespace aijika
