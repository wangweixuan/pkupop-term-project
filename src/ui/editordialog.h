/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QListWidget>
#include <QTextEdit>
#include <QWidget>

#include "common/globals.h"
#include "model/card.h"
#include "model/pack.h"
#include "ui/components/packcombo.h"

namespace aijika {

/// 编辑卡片对话框.
class EditorDialog : public QDialog {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  card_id_t card_id;
  pack_id_t pack_id;

  /// 卡组选择，关键词，正面，背面编辑框
  PackCombo *pack_list;
  QLabel *choosecard_text;
  QLabel *choosepack_text;

  QLabel *keyword_text;
  QLabel *front_text;
  QLabel *back_text;

  QTextEdit *keyword_edit;
  QTextEdit *front_edit;
  QTextEdit *back_edit;

  QVBoxLayout *main_layout;
  QHBoxLayout *hori_layout[6];

  /// 卡组的列表
  QListWidget *card_list;

  /// 保存按钮
  QPushButton *save;

  /// 取消按钮
  QPushButton *cancel;

 public:
  explicit EditorDialog(QWidget *parent, AppGlobals &globals);

  void SetCard(Card &card);

  void SetPack(CardPack &pack);

 public slots:
  void changecard();
};

}  // namespace aijika
