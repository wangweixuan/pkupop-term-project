/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QComboBox>
#include <QDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QList>
#include <QListWidget>
#include <QPushButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QStackedLayout>
#include <QTextEdit>
#include <QWidget>

#include "common/globals.h"
#include "generator/generator.h"
#include "generator/prompt.h"
#include "ui/components/packcombo.h"

namespace aijika {

/// 创建卡片对话框.
class ComposerDialog : public QDialog {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  /// 使用的卡片生成器.
  CardGenerator *generator;

  /// 卡片模版列表.
  QList<Prompt> prompts;

  /// 生成的卡片列表.
  CardStemList generated_cards;

  /// 布局
  QFormLayout *main_layout;

  /// 模板选择框.
  QComboBox *prompt_combo;

  /// 关键词输入框.
  QTextEdit *keywords_input;

  QHBoxLayout *button_layout;
  /// "生成预览" 按钮.
  QPushButton *generate_button;
  /// "清空预览" 按钮.
  QPushButton *cancel_button;

  QStackedLayout *generated_layout;
  /// 生成文本, 滚动界面
  QScrollArea *generated_area;
  /// 生成界面
  QListWidget *generated_list;
  /// 错误标签
  QLabel *error_label;

  /// 卡组选择框.
  PackCombo *pack_combo;

  QHBoxLayout *bottom_button_layout;
  /// "保存" 按钮.
  QPushButton *confirm_button;
  /// "取消" 按钮
  QPushButton *leave_button;

 public:
  explicit ComposerDialog(QWidget *parent, AppGlobals &globals);

 private slots:
  void Generate();

  void Cancel();

  void Confirm();

 public slots:
  /// 接收 CardGenerator 的信号, 表示卡片生成完成.
  void ShowResults(CardStemList cards);

  /// 接收 CardGenerator 的信号, 表示卡片生成失败.
  void ShowError(QString message);
};

}  // namespace aijika
