/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QDialog>

#include "common/globals.h"
#include "model/card.h"
#include "model/pack.h"

namespace aijika {

/// 编辑卡片对话框.
class EditorDialog : public QDialog {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  card_id_t current_card_id;
  pack_id_t pack_id_t;
  Card *current_card;
  CardPack *current_pack;

 public:
  explicit EditorDialog(QWidget *parent, AppGlobals &globals);

  void SetCard(Card *card);
  void SetPack(CardPack *pack);

 public slots:
  void InvalidatePack(CardPack &pack);
  void InvalidateList();
};

}  // namespace aijika
