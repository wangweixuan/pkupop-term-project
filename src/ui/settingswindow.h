/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QBoxLayout>
#include <QButtonGroup>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QWidget>

#include "common/globals.h"

namespace aijika {

/// 设置窗口.
class SettingsWindow : public QWidget {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  QVBoxLayout *main_layout;

  QGroupBox *appearance_group;
  QFormLayout *appearance_layout;
  QComboBox *font_family_box;
  QSpinBox *font_size_box;
  QButtonGroup *theme_group;
  QHBoxLayout *theme_layout;
  QRadioButton *theme_buttons[4];

  QGroupBox *learning_group;
  QFormLayout *learning_layout;
  QComboBox *review_box;
  QHBoxLayout *schedule_layout;
  QPushButton *advance_button;
  QPushButton *postpone_button;

  QGroupBox *api_group;
  QFormLayout *api_layout;
  QComboBox *api_base_url_edit;
  QLineEdit *api_key_edit;
  QComboBox *api_model_edit;

 public:
  explicit SettingsWindow(AppGlobals &globals);
};

}  // namespace aijika
