/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include "common/globals.h"
#include "model/card.h"
#include "model/pack.h"

namespace aijika {

/// 编辑卡片对话框.
class EditorDialog : public QDialog {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  card_id_t card_id;
  pack_id_t pack_id;

  /// 卡组选择，关键词，正面，背面编辑框

  QFormLayout *main_layout;

  QLineEdit *keyword_edit;
  QTextEdit *front_edit;
  QTextEdit *back_edit;

  QLabel *repetition_label;
  QLabel *time_created_label;
  QLabel *time_reviewed_label;
  QLabel *time_due_label;

  QHBoxLayout *button_layout;
  /// 保存按钮
  QPushButton *save_button;
  /// 取消按钮
  QPushButton *cancel_button;

 public:
  explicit EditorDialog(QWidget *parent, AppGlobals &globals, Card *card,
                        CardPack *pack);

 private slots:
  void Save();
};

}  // namespace aijika
