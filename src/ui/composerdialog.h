/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <QDialog>

#include "common/globals.h"
#include "model/pack.h"

namespace aijika {

/// 创建卡片对话框.
class ComposerDialog : public QDialog {
  Q_OBJECT;

 private:
  AppGlobals &globals;

  pack_id_t current_pack_id;
  CardPack *current_pack;

 public:
  explicit ComposerDialog(QWidget *parent, AppGlobals &globals);

  void SetPack(CardPack *pack);

 public slots:
  void InvalidateList();
};

}  // namespace aijika
