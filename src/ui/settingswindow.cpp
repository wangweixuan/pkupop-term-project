/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/settingswindow.h"

#include <QDesktopServices>
#include <QMessageBox>
#include <QUrl>

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

      learning_group{new QGroupBox{"学习设置", this}},
      learning_layout{new QFormLayout{learning_group}},
      review_box{new QComboBox{this}},
      schedule_layout{new QHBoxLayout{nullptr}},
      advance_button{new QPushButton{"提前进度", this}},
      postpone_button{new QPushButton{"延后进度", this}},

      api_group{new QGroupBox{"API 设置", this}},
      api_layout{new QFormLayout{api_group}},
      api_base_url_edit{new QComboBox{this}},
      api_key_edit{new QLineEdit{this}},
      api_model_edit{new QComboBox{this}},

      about_layout{new QHBoxLayout{nullptr}},
      about_button{new QPushButton{"关于 AI 记卡", this}},
      repo_button{new QPushButton{"项目主页", this}} {
  setWindowTitle("设置");

  appearance_layout->setFieldGrowthPolicy(QFormLayout::FieldsStayAtSizeHint);
  appearance_layout->setFormAlignment(Qt::AlignLeft);
  appearance_layout->setLabelAlignment(Qt::AlignRight);
  int i = 0;
  for (auto const& name : globals.settings.PredefinedFonts()) {
    font_family_box->addItem(name, i);
    ++i;
  }
  appearance_layout->addRow("字体：", font_family_box);
  appearance_layout->addRow("字号：", font_size_box);
  i = 0;
  for (auto const& name : globals.settings.PredefinedThemes()) {
    theme_buttons[i]->setText(name);
    theme_group->addButton(theme_buttons[i], i);
    theme_layout->addWidget(theme_buttons[i]);
    ++i;
  }
  appearance_layout->addRow("主题：", theme_layout);
  main_layout->addWidget(appearance_group);

  main_layout->addSpacing(10);

  learning_layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
  learning_layout->setFormAlignment(Qt::AlignLeft);
  learning_layout->setLabelAlignment(Qt::AlignRight);
  review_box->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  i = 0;
  for (auto const& name : globals.settings.ReviewOptions()) {
    review_box->addItem(name, i);
    ++i;
  }
  learning_layout->addRow("顺序：", review_box);
  schedule_layout->addWidget(advance_button);
  schedule_layout->addWidget(postpone_button);
  learning_layout->addRow("调整：", schedule_layout);
  main_layout->addWidget(learning_group);

  main_layout->addSpacing(10);

  api_layout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
  api_layout->setFormAlignment(Qt::AlignLeft);
  api_layout->setLabelAlignment(Qt::AlignRight);
  api_layout->addRow("网址：", api_base_url_edit);
  api_layout->addRow("密钥：", api_key_edit);
  api_layout->addRow("模型：", api_model_edit);
  main_layout->addWidget(api_group);

  about_layout->addWidget(about_button);
  about_layout->addWidget(repo_button);
  main_layout->addLayout(about_layout);

  font_family_box->setCurrentIndex(
      font_family_box->findData(int(globals.settings.font_family)));
  font_size_box->setValue(globals.settings.font_size);
  theme_buttons[int(globals.settings.theme)]->setChecked(true);

  review_box->setCurrentIndex(
      review_box->findData(int(globals.settings.review)));

  api_base_url_edit->setEditable(true);
  api_base_url_edit->setInsertPolicy(QComboBox::NoInsert);
  for (auto const& value : globals.settings.WellKnownApiBaseUrls()) {
    api_base_url_edit->addItem(value);
  }
  api_base_url_edit->setCurrentText(globals.settings.api_base_url);
  api_key_edit->setText(globals.settings.api_key);
  api_model_edit->setEditable(true);
  api_model_edit->setInsertPolicy(QComboBox::NoInsert);
  for (auto const& value : globals.settings.WellKnownApiModels()) {
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

  connect(review_box, &QComboBox::currentIndexChanged, [&]() {
    globals.settings.SetReview(review_box->currentData().toInt());
  });
  connect(advance_button, &QPushButton::clicked, [&]() {
    globals.db.AdvanceAll();
    QMessageBox::information(this, "调整进度",
                             "所有卡片的到期时间已提前一天。");
  });
  connect(postpone_button, &QPushButton::clicked, [&]() {
    globals.db.PostponeAll();
    QMessageBox::information(this, "调整进度",
                             "所有卡片的到期时间已延后一天。");
  });

  connect(api_base_url_edit, &QComboBox::currentTextChanged,
          [&](QString const& text) { globals.settings.SetApiBaseUrl(text); });
  connect(api_key_edit, &QLineEdit::textChanged,
          [&](QString const& text) { globals.settings.SetApiKey(text); });
  connect(api_model_edit, &QComboBox::currentTextChanged,
          [&](QString const& text) { globals.settings.SetApiModel(text); });

  connect(about_button, &QPushButton::clicked, [&]() {
    QMessageBox::information(
        this, "关于 AI 记卡",
        "《AI 记卡》是北京大学《程序设计实习》课程的大作业。"
        "本程序基于 Qt 开发。\n\n"
        "作者：Wang Weixuan, Hou Xusen, Zheng Shiqi\n\n"
        "发行日期：2023 年 6 月\n\n"
        "许可证：Apache-2.0\n\n"
        "项目主页：https://github.com/wangweixuan/pkupop-term-project");
  });
  connect(repo_button, &QPushButton::clicked, [&]() {
    QDesktopServices::openUrl(
        QUrl{"https://github.com/wangweixuan/pkupop-term-project"});
  });
}

}  // namespace aijika
