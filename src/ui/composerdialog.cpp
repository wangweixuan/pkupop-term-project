#include "ui/composerdialog.h"
#include "generator/generator.h"
#include "generator/prompt.h"

#include <QtDebug>
#include <QListWidget>
#include <qapplication.h>
#include <QScrollArea>
#include <QScrollBar>
#include <QBoxLayout>
#include <iostream>

namespace aijika {

ComposerDialog::ComposerDialog(QWidget *parent, AppGlobals &globals)
    : QDialog{parent},
      globals{globals},
      generator{new CardGenerator{this, globals.settings}},
      prompts{LoadPromptsFromResources()},
      pack_combo{new PackCombo{this,globals}},
      keywords_input{new QTextEdit{this}},
      generate_button{new QPushButton{"生成", this}},
      cancel_button{new QPushButton{"取消", this}},
      confirm_button{new QPushButton{"确认", this}},
      leave_button{new QPushButton{"退出",this}},

      Layoutmain{new QVBoxLayout{this}},
      LayoutH{new QHBoxLayout{nullptr},new QHBoxLayout{nullptr},new QHBoxLayout{nullptr},
              new QHBoxLayout{nullptr},new QHBoxLayout{nullptr},new QHBoxLayout{nullptr}},

      generate_text{new QScrollArea{this}},

      generate_list{new QListWidget{generate_text}},

      question_label{new QLabel{"模板:",this}},
      keywords_label{new QLabel{"关键词:",this}},
      generate_label{new QLabel{"生成结果：",this}},
      error_label{new QLabel{"生成出错啦",parent}}

{

  setWindowTitle("创建卡片");

  pack_combo->setFixedSize(120,20);
  pack_combo->addItem(prompts[0].label);
  generate_text->setFixedSize(300,200);
  generate_text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);//滚动条
  generate_text->setWidget(generate_list);
  generate_list->setGeometry(0, 0, 300, 1200);//主要是设置长宽，xy意义不大


  LayoutH[1]->addWidget(question_label);
  LayoutH[1]->addWidget(pack_combo);
  LayoutH[2]->addWidget(keywords_label);
  LayoutH[2]->addWidget(keywords_input);
  LayoutH[3]->addWidget(generate_button);
  LayoutH[3]->addWidget(cancel_button);
  LayoutH[4]->addWidget(generate_label);
  LayoutH[4]->addWidget(generate_text);
  LayoutH[5]->addWidget(confirm_button);
  LayoutH[5]->addWidget(leave_button);

  LayoutH[1]->setAlignment(Qt::AlignLeft);
  LayoutH[1]->setSpacing(18);
  LayoutH[2]->setAlignment(Qt::AlignHCenter);
  LayoutH[3]->setAlignment(Qt::AlignHCenter);
  LayoutH[4]->setAlignment(Qt::AlignHCenter);
  LayoutH[5]->setAlignment(Qt::AlignRight);
  pack_combo->setFixedSize(150,30);

  Layoutmain->addLayout(LayoutH[1]);
  Layoutmain->addLayout(LayoutH[2]);
  Layoutmain->addLayout(LayoutH[3]);
  Layoutmain->addLayout(LayoutH[4]);
  Layoutmain->addLayout(LayoutH[5]);
  error_label->setWindowTitle("error");
  error_label->setFont (QFont ("Arial", 20));
  error_label->setAlignment(Qt::AlignCenter);






          // TODO: unimplemented



  connect(generator, &CardGenerator::generated, this,
          &ComposerDialog::ShowResults);
  connect(generator, &CardGenerator::error, this, &ComposerDialog::ShowError);

  connect(generate_button, &QPushButton::clicked, [this]() {
    generator->Generate(prompts[pack_combo->currentIndex()], keywords_input->toPlainText());
  });
  connect(cancel_button, &QPushButton::clicked,
          [this]() { generator->Abort();generate_list->clear();});//点击cancel就清空
  connect(confirm_button, &QPushButton::clicked,
          [this]() {
            QString title;
            for (auto &card : this->generated_cards) {
              title+=card.keyword;
              title+=" ";
            }
            if(this->generated_cards.size()!=0){
              this->globals.db.AddPack(title);
              for(auto &card :this->generated_cards){
                this->globals.db.AddCard(card,*(this->globals.db.FindPack(this->globals.db.incremental_pack_id - 1)));
              }

              this->close();
            }
          });
  connect(leave_button, &QPushButton::clicked,
          [this]() { this->close(); });
}

void ComposerDialog::SetPack(CardPack *pack) { pack_combo->SetPack(pack); }

void ComposerDialog::ShowResults(CardStemList cards) {
  // TODO: 用一个列表显示新生成的卡片

  generate_list->show();
  generated_cards = cards;  // 记录一下生成的卡片, 或许有用.

  generate_list->clear();  // 清空当前列表中显示的卡片.

  for (auto &card : cards) {
    // 将卡片转换成一个字符串.
    auto s = QStringList{"关键词: ",    card.keyword, "\n正面: ",
          card.question, "\n背面: ",   card.answer}
                                           .join("");
      // 将字符串添加到列表.
    generate_list->addItem(s);
  }
}

void ComposerDialog::ShowError(QString message) {
     // 清空当前列表中显示的卡片.
  generated_cards.clear();

   // 用一个 label 显示错误信息
  error_label->setText(message);
  error_label->show();

}

}  // namespace aijika
