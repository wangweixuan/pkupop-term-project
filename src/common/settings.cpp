/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "common/settings.h"

#include <QString>
#include <QtDebug>

#include "model/pack.h"

namespace aijika {

namespace {
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

constexpr char const *k_font_family_names[5]{
    "Old style", "Transitional", "Neo-Grotesk", "Geometric", "Humanistic"};

constexpr char const *k_theme_names[4]{"白色", "纸张", "灰暗", "夜间"};

constexpr char const *k_review_names[3]{"最久未复习卡片", "最早到期卡片",
                                        "随机卡片"};

constexpr char const *k_well_known_api_base_urls[2]{"https://api.openai.com",
                                                    "http://localhost:8080"};

constexpr char const *k_well_known_api_models[3]{"gpt-3.5-turbo", "gpt-4",
                                                 "gpt-4-32k"};

template <size_t n>
QStringList ToList(char const *const (&strings)[n]) {
  QStringList list;
  for (size_t i = 0; i < n; ++i) {
    list << strings[i];
  }
  return list;
}
}  // namespace

AppSettings::AppSettings()
    : QObject{nullptr},
      font_family{PredefinedFont::humanistic},
      font_size{14},
      theme{PredefinedTheme::yellow},
      review{ReviewOption::due_date},
      api_base_url{k_well_known_api_base_urls[0]},
      api_key{},
      api_model{k_well_known_api_models[0]} {}

QString AppSettings::StyleSheet() const {
  return QString{
      "QFrame, QPushButton { font-family: %1; font-size: %2pt; "
      "background-color: %3; color: %4; border: none; }"
      "QLabel { padding: 5px %2px; }"
      "QSplitter:handle { background-color: %4 }"}
      .arg(k_font_families[int(font_family)], QString::number(font_size),
           k_background_colors[int(theme)], k_colors[int(theme)]);
}

QStringList AppSettings::PredefinedFonts() const {
  return ToList(k_font_family_names);
}

QStringList AppSettings::PredefinedThemes() const {
  return ToList(k_theme_names);
}

QStringList AppSettings::ReviewOptions() const {
  return ToList(k_review_names);
}

QStringList AppSettings::WellKnownApiBaseUrls() const {
  return ToList(k_well_known_api_base_urls);
}

QStringList AppSettings::WellKnownApiModels() const {
  return ToList(k_well_known_api_models);
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

void AppSettings::SetReview(int which) {
  auto value = static_cast<ReviewOption>(which);
  if (value == review) return;
  review = value;
  emit learning_updated();
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
             << settings.review << settings.api_base_url << settings.api_key
             << settings.api_model;
}

QDataStream &operator>>(QDataStream &in, AppSettings &settings) {
  return in >> settings.font_family >> settings.font_size >> settings.theme >>
         settings.review >> settings.api_base_url >> settings.api_key >>
         settings.api_model;
}

}  // namespace aijika
