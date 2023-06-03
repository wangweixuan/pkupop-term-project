/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "common/settings.h"

#include <QStringList>

namespace aijika {

AppSettings::AppSettings()
    : QObject{nullptr},
      font_family{PredefinedFont::humanistic},
      font_size{14},
      theme{PredefinedTheme::yellow},
      api_base_url{"https://api.openai.com"},
      api_key{},
      api_model{"gpt-3.5-turbo"} {}

namespace predefined_styles {
// Taken from https://github.com/system-fonts/modern-font-stacks
// Copyright 2023 contributors
// Licensed under CC0
constexpr char const *k_font_families[5]{
    /* old style */
    "'Iowan Old Style', 'Palatino Linotype', 'URW Palladio L', P052, '楷体', "
    "serif",
    /* transitional */
    "font-family: Charter, 'Bitstream Charter', 'Sitka Text', Cambria, '宋体', "
    "serif",
    /* neo_grotesk */
    "Inter, Roboto, 'Helvetica Neue', 'Arial Nova', 'Nimbus Sans', Arial, "
    "'黑体', sans-serif",
    /* geometric */
    "Avenir, 'Avenir Next LT Pro', Montserrat, Corbel, 'URW Gothic', "
    "source-sans-pro, '黑体', sans-serif",
    /* humanistic */
    "'Optima, Candara, 'Noto Sans', source-sans-pro, '黑体', sans-serif'"};

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

  QStringList parts{"QFrame { font-family:",
                    k_font_families[int(font_family)],
                    "; font-size:",
                    QString::number(font_size),
                    "; background-color:",
                    k_background_colors[int(theme)],
                    "; color:",
                    k_colors[int(theme)],
                    "; }"};
  return parts.join(" ");
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
