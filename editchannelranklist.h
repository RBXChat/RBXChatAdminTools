#ifndef EDITCHANNELRANKLIST_H
#define EDITCHANNELRANKLIST_H

#include <QDialog>
#include "modifydirdialog.h"

namespace Ui {
class EditChannelRankList;
}

class EditChannelRankList : public QDialog
{
    Q_OBJECT

public:
    explicit EditChannelRankList(QWidget *parent = 0);
    ~EditChannelRankList();

    void setup(QString label, QStringList list, int mode, int index);
    ModifyDirDialog* mainwin;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::EditChannelRankList *ui;
    int mode;
    int index;
};

#endif // EDITCHANNELRANKLIST_H
