/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/settingswindow.h"

#include "common/settings.h"

namespace aijika {

SettingsWindow::SettingsWindow(AppGlobals& globals)
    : QWidget{nullptr},
      globals{globals},
      main_layout{new QVBoxLayout{this}},
      appearance_group{new QGroupBox{"外观设置", this}},
      appearance_layout{new QFormLayout{appearance_group}},
      font_family_box{new QComboBox{this}},
      font_size_box{new QSpinBox{this}},
      theme_group{new QButtonGroup{this}},
      theme_layout{new QHBoxLayout{nullptr}},
      theme_buttons{new QRadioButton{this}, new QRadioButton{this},
                    new QRadioButton{this}, new QRadioButton{this}},
      api_group{new QGroupBox{"API 设置", this}},
      api_layout{new QFormLayout{api_group}},
      api_base_url_edit{new QComboBox{this}},
      api_key_edit{new QLineEdit{this}},
      api_model_edit{new QComboBox{this}} {
  setWindowTitle("设置");

  appearance_layout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
  appearance_layout->setFormAlignment(Qt::AlignLeft);
  appearance_layout->setLabelAlignment(Qt::AlignRight);
  for (int i = 0; i < 5; ++i) {
    font_family_box->addItem(k_predefined_font_names[i], i);
  }
  appearance_layout->addRow("字体：", font_family_box);
  appearance_layout->addRow("字号：", font_size_box);
  for (int i = 0; i < 4; ++i) {
    theme_buttons[i]->setText(k_predefined_theme_names[i]);
    theme_group->addButton(theme_buttons[i], i);
    theme_layout->addWidget(theme_buttons[i]);
  }
  appearance_layout->addRow("主题：", theme_layout);
  main_layout->addWidget(appearance_group);

  main_layout->addSpacing(10);

  api_layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
  api_layout->setFormAlignment(Qt::AlignLeft);
  api_layout->setLabelAlignment(Qt::AlignRight);
  api_layout->addRow("网址：", api_base_url_edit);
  api_layout->addRow("密钥：", api_key_edit);
  api_layout->addRow("模型：", api_model_edit);
  main_layout->addWidget(api_group);

  font_family_box->setCurrentIndex(
      font_family_box->findData(int(globals.settings.font_family)));
  font_size_box->setValue(globals.settings.font_size);
  theme_buttons[int(globals.settings.theme)]->setChecked(true);

  api_base_url_edit->setEditable(true);
  api_base_url_edit->setInsertPolicy(QComboBox::NoInsert);
  for (auto value : k_predefined_api_base_url) {
    api_base_url_edit->addItem(value);
  }
  api_base_url_edit->setCurrentText(globals.settings.api_base_url);
  api_key_edit->setText(globals.settings.api_key);
  api_model_edit->setEditable(true);
  api_model_edit->setInsertPolicy(QComboBox::NoInsert);
  for (auto value : k_predefined_api_model) {
    api_model_edit->addItem(value);
  }
  api_model_edit->setCurrentText(globals.settings.api_model);

  connect(font_family_box, &QComboBox::currentIndexChanged, [&]() {
    globals.settings.SetFontFamily(font_family_box->currentData().toInt());
  });
  connect(font_size_box, &QSpinBox::valueChanged,
          [&](int value) { globals.settings.SetFontSize(value); });
  connect(theme_group, &QButtonGroup::idClicked,
          [&](int id) { globals.settings.SetTheme(id); });
  connect(api_base_url_edit, &QComboBox::currentTextChanged,
          [&](QString const& text) { globals.settings.SetApiBaseUrl(text); });
  connect(api_key_edit, &QLineEdit::textChanged,
          [&](QString const& text) { globals.settings.SetApiKey(text); });
  connect(api_model_edit, &QComboBox::currentTextChanged,
          [&](QString const& text) { globals.settings.SetApiModel(text); });
}

}  // namespace aijika
