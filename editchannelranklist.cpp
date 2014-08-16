#include "editchannelranklist.h"
#include "ui_editchannelranklist.h"
#include <QInputDialog>
#include <QDebug>

EditChannelRankList::EditChannelRankList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditChannelRankList) {
    ui->setupUi(this);
}

EditChannelRankList::~EditChannelRankList() {
    delete ui;
}

void EditChannelRankList::setup(QString label, QStringList list, int mode, int index) {
    if (list.size())
        this->ui->listWidget->addItems(list);
    this->ui->label->setText(label);
    this->mode = mode;
    this->index = index;
}

void EditChannelRankList::on_pushButton_clicked() {
    QStringList items;
    for (int i = 0; i < this->ui->listWidget->count(); i++)
        items.append(this->ui->listWidget->item(i)->text());
    this->mainwin->setRankList(items, this->mode, this->index);
    this->hide();
}

void EditChannelRankList::on_pushButton_2_clicked() {
    this->ui->listWidget->addItem(QInputDialog::getText(this, "Enter username", "Please enter a username.", QLineEdit::Normal, "gskw"));
}

void EditChannelRankList::on_pushButton_3_clicked() {
    qDeleteAll(this->ui->listWidget->selectedItems());
}
