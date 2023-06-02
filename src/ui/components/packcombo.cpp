/* Aijika, a PKU POP term project
 * Copyright 2023 Wang Weixuan, Hou Xusen, Zheng Shiqi
 * SPDX-License-Identifier: Apache-2.0 */

#include "ui/components/packcombo.h"
#include <QDebug>

namespace aijika {

// 构造函数
PackCombo::PackCombo(QWidget *parent, AppGlobals &globals)
    : QComboBox(parent), globals(globals), pack_id(-1) {
    // 设置QComboBox属性
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QFont font;
    font.setPointSize(10);
    setFont(font);
    setStyleSheet(
        "QComboBox::drop-down {border: none; background-color: transparent; "
        "image:url(:/resources/icon.icns); width: 20px;} "//这里需要一个向下箭头的icon
        "QComboBox::down-arrow {image: none;}");
    setToolTip(tr("Select a card pack"));

    // 添加无卡组选项
    addItem(tr("(None)"), -1);
    setCurrentIndex(0);

    // 将所有卡组加入QComboBox
    QList<CardPack> packs = globals.db.packs;
    for (const CardPack &pack : packs) {
        addItem(pack.label, static_cast<int>(pack.id));
    }

    // 连接信号和槽
    connect(&globals.db, &CardDatabase::pack_updated, this, &PackCombo::UpdatePack);
    connect(&globals.db, &CardDatabase::list_updated, this, &PackCombo::UpdateList);
    connect(this, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [&](int index) {
        pack_id_t new_pack_id = itemData(index).toInt();
        if (new_pack_id != pack_id) {
            // 如果选中卡组发生变化，则更新卡组信息
            CardPack *new_pack = (new_pack_id == -1) ? nullptr : globals.db.FindPack(new_pack_id);
            qDebug("pack_changed信号发出");
            qDebug()<<new_pack_id<<count();
            emit pack_changed(new_pack);
        }
    });//根据pack在组件QComboBox中的index选择pack，通过pack_changed信号调用了SetPack函数。
    connect(this,&PackCombo::pack_changed,this,&PackCombo::SetPack);
}

// 获取所选卡组
CardPack *PackCombo::GetPack() {
    qDebug()<<"getpack被调用了，此时pack_id="<<pack_id;
    if (pack_id == -1) {
        return nullptr;
    } else {
        return globals.db.FindPack(pack_id);
    }
}

// 设置所选卡组
void PackCombo::SetPack(CardPack *pack) {

    if (pack == nullptr){
        pack_id=-1;
        setCurrentIndex(0);
        return;
    }
    int index = findData(static_cast<int>(pack->id));
    if (index == -1){
        pack_id=-1;
        setCurrentIndex(0);
        qDebug()<<"调用的pack不在PackCombo中或者非法调用nullptr";
        return;
    }//保险，防止调用了没有的pack;
    pack_id=pack->id;
    setCurrentIndex(index);//比packs多一个null；
}

// 更新卡组信息
void PackCombo::UpdatePack(CardPack &pack) {
    int index = findData(static_cast<int>(pack.id));
    if (index != -1) {
        setItemText(index, pack.label);
    }
    qDebug("pack_updated信号发出");
    emit pack_updated(pack);
}

// 更新卡组列表
void PackCombo::UpdateList() {
    clear(); // 先清空QComboBox
    addItem(tr("(None)"), -1);
    QList<CardPack> packs = globals.db.packs;
    for (const CardPack &pack : packs) {
        addItem(pack.label, static_cast<int>(pack.id));
    }
    // 重新设置选中项
    pack_id=globals.db.last_visited_pack;
    int index = findData(static_cast<int>(pack_id));
    setCurrentIndex(index);
}

}  // namespace aijika
