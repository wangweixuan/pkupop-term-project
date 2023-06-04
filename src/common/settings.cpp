/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "common/settings.h"

#include <QString>
#include <QtDebug>

namespace aijika {

AppSettings::AppSettings()
    : QObject{nullptr},
      font_family{PredefinedFont::humanistic},
      font_size{14},
      theme{PredefinedTheme::yellow},
      api_base_url{k_predefined_api_base_url[0]},
      api_key{},
      api_model{k_predefined_api_model[0]} {}

namespace predefined_styles {
// Taken from https://github.com/system-fonts/modern-font-stacks
// Copyright 2023 contributors
// Licensed under CC0
constexpr char const *k_font_families[5]{
    /* old style */
    "'Iowan Old Style', 'Palatino Linotype', 'URW Palladio L', P052, STKaiti, "
    "'楷体', serif",
    /* transitional */
    "Charter, 'Bitstream Charter', 'Sitka Text', Cambria, '宋体', serif",
    /* neo_grotesk */
    "Inter, Roboto, 'Helvetica Neue', 'Arial Nova', 'Nimbus Sans', Arial, "
    "'黑体', sans-serif",
    /* geometric */
    "Avenir, 'Avenir Next LT Pro', Montserrat, Corbel, 'URW Gothic', "
    "source-sans-pro, '黑体', sans-serif",
    /* humanistic */
    "Optima, Candara, 'Noto Sans', source-sans-pro, STKaiti, '楷体', "
    "sans-serif"};

constexpr char const *k_background_colors[4]{/* white */
                                             "#fcfcfc",
                                             /* yellow */
                                             "#f9f4e9",
                                             /* grey */
                                             "#5c5c5f",
                                             /* black */
                                             "#171717"};

constexpr char const *k_colors[4]{/* white */
                                  "#000000",
                                  /* yellow */
                                  "#000000",
                                  /* grey */
                                  "#dfdfdf",
                                  /* black */
                                  "#bebebe"};
}  // namespace predefined_styles

QString AppSettings::StyleSheet() const {
  using namespace predefined_styles;

  return QString{
      "QFrame, QPushButton { font-family: %1; font-size: %2pt; "
      "background-color: %3; color: %4; border: none; }"
      "QLabel { padding: 5px %2px; }"
      "QSplitter:handle { background-color: %4 }"}
      .arg(k_font_families[int(font_family)], QString::number(font_size),
           k_background_colors[int(theme)], k_colors[int(theme)]);
}

void AppSettings::SetFontFamily(int which) {
  auto value = static_cast<PredefinedFont>(which);
  if (value == font_family) return;
  font_family = value;
  emit appearance_updated();
}

void AppSettings::SetFontSize(int value) {
  if (value < 8) {
    value = 8;
  } else if (value > 32) {
    value = 32;
  }
  if (value == font_size) return;
  font_size = value;
  emit appearance_updated();
}

void AppSettings::SetTheme(int which) {
  auto value = static_cast<PredefinedTheme>(which);
  if (value == theme) return;
  theme = value;
  emit appearance_updated();
}

void AppSettings::SetApiBaseUrl(QString const &value) {
  if (value == api_base_url) return;
  api_base_url = value;
  emit api_updated();
}

void AppSettings::SetApiKey(QString const &value) {
  if (value == api_key) return;
  api_key = value;
  emit api_updated();
}

void AppSettings::SetApiModel(QString const &value) {
  if (value == api_model) return;
  api_model = value;
  emit api_updated();
}

QDataStream &operator<<(QDataStream &out, AppSettings const &settings) {
  return out << settings.font_family << settings.font_size << settings.theme
             << settings.api_base_url << settings.api_key << settings.api_model;
}

QDataStream &operator>>(QDataStream &in, AppSettings &settings) {
  return in >> settings.font_family >> settings.font_size >> settings.theme >>
         settings.api_base_url >> settings.api_key >> settings.api_model;
}

}  // namespace aijika
