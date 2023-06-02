/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QDialog>
#include <QList>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>
#include <QLayout>

#include "common/globals.h"
#include "generator/generator.h"
#include "generator/prompt.h"
#include "model/pack.h"
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

  PackCombo *pack_combo;

          /// 关键词输入框.
  QTextEdit *keywords_input;

          /// "生成" 按钮.
  QPushButton *generate_button;
  /// "取消" 按钮.
  QPushButton *cancel_button;
  /// "确认" 按钮.
  QPushButton *confirm_button;
  /// "退出" 按钮
  QPushButton *leave_button;

  ///布局
  QVBoxLayout *Layoutmain;
  QHBoxLayout *LayoutH[6];

  ///生成文本,滚动界面
  QScrollArea *generate_text;

  ///生成界面
  QListWidget *generate_list;


          ///文字标签
  QLabel *question_label;
  QLabel *keywords_label;
  QLabel *generate_label;
  QLabel *error_label;


 public:
  explicit ComposerDialog(QWidget *parent, AppGlobals &globals);

  void SetPack(CardPack *pack);

 signals:
  void updatepack();

 public slots:
  /// 接收 CardGenerator 的信号, 表示卡片生成完成.
  void ShowResults(CardStemList cards);

          /// 接收 CardGenerator 的信号, 表示卡片生成失败.
  void ShowError(QString message);
};

}  // namespace aijika
