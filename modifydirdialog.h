#ifndef MODIFYDIRDIALOG_H
#define MODIFYDIRDIALOG_H

#include <QMainWindow>
#include "authenticationinfo.h"
#include "baninfo.h"
#include "channelinfo.h"

namespace Ui {
class ModifyDirDialog;
}

class ModifyDirDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModifyDirDialog(QWidget *parent = 0, QString path = "");
    ~ModifyDirDialog();

    void setRankList(QStringList list, int rank, int index);

    QString path;

private:
    Ui::ModifyDirDialog *ui;
    void setupTabs();

    QString randomString();

    bool ignorePasswordChange;

    QList<AuthenticationInfo> currai;
    QList<BanInfo> currbi;
    QList<ChannelInfo> currci;


private slots:
    void handleCellDblClick(int row, int col);
    void handleChanNameChange(int row, int col);
    void handleAuthDataChange(int row, int col);
    void handleBanDataChange(int row, int col);


    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // MODIFYDIRDIALOG_H
