#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QTime>
#include <QInputDialog>

#include "modifydirdialog.h"
#include "ui_modifydirdialog.h"
#include "authenticationinfo.h"
#include "baninfo.h"
#include "channelinfo.h"
#include "editchannelranklist.h"


ModifyDirDialog::ModifyDirDialog(QWidget *parent, QString path) :
    QMainWindow(parent),
    ui(new Ui::ModifyDirDialog) {
        ui->setupUi(this);
        this->path = path;
        this->setupTabs();
    }

ModifyDirDialog::~ModifyDirDialog() {
    delete ui;
}

void ModifyDirDialog::setupTabs() {
    this->ignorePasswordChange = false;

    QFile authfile(this->path + "/auth.rbxca");
    QFile banfile(this->path + "/bans.rbxcb");
    QFile chanfile(this->path + "/chan.rbxcc");
    authfile.open(QIODevice::ReadOnly | QIODevice::Text);
    banfile.open(QIODevice::ReadOnly | QIODevice::Text);
    chanfile.open(QIODevice::ReadOnly | QIODevice::Text);



    QString authcontent;
    authcontent = authfile.readAll();
    authfile.close();

    QStringList authinfo = authcontent.split("\n");
    QList<AuthenticationInfo> autharray;
    int i;
    for (i = 0; i < authinfo.size() - 1; i++)
        if (!authinfo[i].isEmpty())
            autharray.append(*(new AuthenticationInfo(authinfo[i])));
    this->ui->tableWidget->setRowCount(i - 1);
    for (i = 0; i < autharray.size() - 1; i++) {
        this->currai.append(autharray.at(i));
        this->ui->tableWidget->setItem(i, 0, new QTableWidgetItem(autharray.at(i).getUsername()));
        this->ui->tableWidget->setItem(i, 1, new QTableWidgetItem(autharray.at(i).getPasswordHash()));
        this->ui->tableWidget->setItem(i, 2, new QTableWidgetItem(autharray.at(i).getROBLOXUsername()));
        this->ui->tableWidget->setItem(i, 3, new QTableWidgetItem(autharray.at(i).getVerificationCode()));
        this->ui->tableWidget->setItem(i, 4, new QTableWidgetItem(autharray.at(i).isVerifiedString()));
    }
    connect(this->ui->tableWidget, SIGNAL(cellChanged(int,int)), this, SLOT(handleAuthDataChange(int,int)));

    QString bancontent;
    bancontent = banfile.readAll();
    banfile.close();

    QStringList baninfo = bancontent.split("\n");
    QList<BanInfo> banarray;
    for (i = 0; i < baninfo.size(); i++)
        if (!baninfo[i].isEmpty())
            banarray.append(*(new BanInfo(baninfo[i] + "\n")));
    this->ui->tableWidget_3->setRowCount(i - 1);
    for (i = 0; i < baninfo.size() - 1; i++) {
        this->currbi.append(banarray.at(i));
        this->ui->tableWidget_3->setItem(i, 0, new QTableWidgetItem(banarray.at(i).getUsername()));
        this->ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(banarray.at(i).getReason()));
    }
    connect(this->ui->tableWidget_3, SIGNAL(cellChanged(int, int)), this, SLOT(handleBanDataChange(int, int)));


    QString chancontent;
    chancontent = chanfile.readAll();
    chanfile.close();

    QStringList chaninfo;
    QString chaninfobuffer;
    int count = 0;
    for (i = 0; i < chancontent.length(); i++) {
        if (count == 4 && chancontent.at(i) == '|') {
            chaninfobuffer += QString("|");
            chaninfo.append(chaninfobuffer);
            chaninfobuffer = QString("");
            count = 0;
        }
        else if (chancontent.at(i) == '|') {
            count++;
            chaninfobuffer += QString("|");
        }
        else
            chaninfobuffer += QString(chancontent.at(i));
    }

    QList<ChannelInfo> chanarray;
    for (i = 0; i < chaninfo.size(); i++)
        if (!chaninfo.isEmpty())
            chanarray.append(*(new ChannelInfo(chaninfo[i])));
    this->ui->tableWidget_2->setRowCount(chaninfo.size());
    for (i = 0; i < chaninfo.size(); i++) {
        this->ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(chanarray.at(i).getName()));
        /*this->currchanlist.append(chanarray.at(i).getName());
        this->curroplist.append(chanarray.at(i).getOperatorList().join("-"));
        this->currwhitelist.append(chanarray.at(i).getWhiteList().join("-"));
        this->currblacklist.append(chanarray.at(i).getBlackList().join("-"));
        this->currmutelist.append(chanarray.at(i).getMuteList().join("-"));*/
        this->currci.append(chanarray[i]);
        this->ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem("..."));
        this->ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem("..."));
        this->ui->tableWidget_2->setItem(i, 3, new QTableWidgetItem("..."));
        this->ui->tableWidget_2->setItem(i, 4, new QTableWidgetItem("..."));
    }
    connect(this->ui->tableWidget_2, SIGNAL(cellClicked(int, int)), this, SLOT(handleCellDblClick(int, int)));
    connect(this->ui->tableWidget_2, SIGNAL(cellChanged(int, int)), this, SLOT(handleChanNameChange(int, int)));
}

void ModifyDirDialog::handleCellDblClick(int row, int col) {
    if (col > 0) { // Ignore when the user doubleclicks the channel name
        EditChannelRankList* d = new EditChannelRankList();
        d->setup((col == 1) ? "Operators:" : (col == 2) ? "Whitelist:" : (col == 3) ? "Blacklist:" : "Muted:", (col == 1) ? this->currci[row].getOperatorList() : (col == 2) ? this->currci[row].getWhiteList() : (col == 3) ? this->currci[row].getBlackList() : this->currci[row].getMuteList(), col - 1, row);
        d->mainwin = this;
        d->show();
    }
}

void ModifyDirDialog::setRankList(QStringList list, int rank, int index) {
    switch (rank) {
        case 0:
            this->currci[index].setOperatorList(list);
            break;
        case 1:
            this->currci[index].setWhiteList(list);
            break;
        case 2:
            this->currci[index].setBlackList(list);
            break;
        case 3:
            this->currci[index].setMuteList(list);
            break;
        default:
            break;
    }
}

void ModifyDirDialog::on_pushButton_clicked() {
    QFile chanfile(this->path + "/chan.rbxcc");
    chanfile.open(QIODevice::WriteOnly);
    QString writetochan = "";
    for (int i = 0; i < this->currci.size(); i++)
        writetochan += this->currci[i].getName() + "|" + this->currci[i].getOperatorList().join("-") + "|" + this->currci[i].getWhiteList().join("-") + "|" + this->currci[i].getBlackList().join("-") + "|" + this->currci[i].getMuteList().join("-") + "|";
    chanfile.write(writetochan.toStdString().c_str());
    chanfile.close();

    QFile authfile(this->path + "/auth.rbxca");
    authfile.open(QIODevice::WriteOnly);
    QString writetoauth = "";
    for (int i = 0; i < this->currai.size(); i++)
        writetoauth += this->currai[i].getUsername() + "|" + this->currai[i].getPasswordHash() + "|" + this->currai[i].getROBLOXUsername() + "|" + this->currai[i].getVerificationCode() + "|" + this->currai[i].isVerifiedString() + "\n";
    authfile.write(writetoauth.toStdString().c_str());
    authfile.close();

    QFile banfile(this->path + "/bans.rbxcb");
    banfile.open(QIODevice::WriteOnly);
    QString writetoban = "";
    for (int i = 0; i < this->currbi.size(); i++)
        writetoban += this->currbi[i].getUsername() + "|" + this->currbi[i].getReason() + "\n";
    banfile.write(writetoban.toStdString().c_str());
    banfile.close();


    QMessageBox::information(this, "Saved", "Saving done!", NULL);
}

void ModifyDirDialog::on_pushButton_2_clicked() {
    this->currai.append(*(new AuthenticationInfo(QInputDialog::getText(this, "Username?", "Please enter an username", QLineEdit::Normal, "muffinman99") + "|||false\n")));
    this->ui->tableWidget->setRowCount(this->currai.size());
    this->ui->tableWidget->setItem(this->currai.size() - 1, 0, new QTableWidgetItem(this->currai[this->currai.size() - 1].getUsername()));
    this->ignorePasswordChange = true; // We don't want a popup about invalid passwords
    this->ui->tableWidget->setItem(this->currai.size() - 1, 1, new QTableWidgetItem(""));
    this->ui->tableWidget->setItem(this->currai.size() - 1, 2, new QTableWidgetItem(""));
    this->ui->tableWidget->setItem(this->currai.size() - 1, 3, new QTableWidgetItem(""));
    this->ui->tableWidget->setItem(this->currai.size() - 1, 4, new QTableWidgetItem("false"));
}

void ModifyDirDialog::handleChanNameChange(int row, int col) {
    if (col == 0) // Ignore if the user changes the "..." cells
        this->currci[row].setName(this->ui->tableWidget_2->item(row, col)->text());
}

void ModifyDirDialog::handleAuthDataChange(int row, int col) {
    if (this->ignorePasswordChange) {
        this->ignorePasswordChange = false;
        return;
    }
    if (col == 0) // username
        this->currai[row].setUsername(this->ui->tableWidget->item(row, col)->text());
    else if (col == 1) { // password (hash)
        this->ignorePasswordChange = true;
        if (this->ui->authEncrypt->checkState()) {
            this->currai[row].setPasswordHash(QString(QCryptographicHash::hash((this->ui->tableWidget->item(row, col)->text().toLatin1()),QCryptographicHash::Md5).toHex()));
            this->ui->tableWidget->item(row, col)->setText(QString(QCryptographicHash::hash((this->ui->tableWidget->item(row, col)->text().toLatin1()),QCryptographicHash::Md5).toHex()));
        }
        else {
            if (!QRegExp("[0-9a-fA-F]{32}").exactMatch(this->ui->tableWidget->item(row, col)->text())) {
                QMessageBox::critical(this, "Error", "The MD5 hash you entered is invalid!", NULL, NULL);
                this->ui->tableWidget->item(row, col)->setText(this->currai[row].getPasswordHash());
            }
            else
                this->currai[row].setPasswordHash(this->ui->tableWidget->item(row, col)->text());
        }
    }
    else if (col == 2) // roblox username
        this->currai[row].setROBLOXUsername(this->ui->tableWidget->item(row, col)->text());
    else if (col == 3) { // verification code
        if (this->ui->autoGen->checkState()) {
            QString generated = this->randomString();
            this->currai[row].setVerificationCode(generated);
            this->ui->tableWidget->item(row, col)->setText(generated);
        }
        else
            this->currai[row].setVerificationCode(this->ui->tableWidget->item(row, col)->text());
    }
    else if (col == 4) // is verified
        this->currai[row].setIsVerifiedString(this->ui->tableWidget->item(row, col)->text());
}

void ModifyDirDialog::handleBanDataChange(int row, int col) {
    if (col == 0) // username
        this->currbi[row].setUsername(this->ui->tableWidget_3->item(row, col)->text());
    else
        this->currbi[row].setReason(this->ui->tableWidget_3->item(row, col)->text());
}

QString ModifyDirDialog::randomString() {
    QString base;
    int i;
    for (i = 0x21; i < 0x7F; i++)
        if ((char) i != '|' || (char) i != '\"')
            base += QChar(i);
    QString ret = "RBXC-";
    qsrand((uint)QTime::currentTime().msec());
    for (i = 0; i < 10; i++) {
        int rand = qrand() % ((base.length()) - 0) + 0;
        ret += base.at(rand);
    }
    return ret;
}

void ModifyDirDialog::on_pushButton_3_clicked() {
    this->currci.append(*(new ChannelInfo(QInputDialog::getText(this, "Channel name?", "Please enter a channel name", QLineEdit::Normal, "#clans") + "||||")));
    this->ui->tableWidget_2->setRowCount(this->currci.size());
    this->ui->tableWidget_2->setItem(this->currci.size() - 1, 0, new QTableWidgetItem(this->currci[this->currci.size() - 1].getName()));
    this->ui->tableWidget_2->setItem(this->currci.size() - 1, 1, new QTableWidgetItem("..."));
    this->ui->tableWidget_2->setItem(this->currci.size() - 1, 2, new QTableWidgetItem("..."));
    this->ui->tableWidget_2->setItem(this->currci.size() - 1, 3, new QTableWidgetItem("..."));
    this->ui->tableWidget_2->setItem(this->currci.size() - 1, 4, new QTableWidgetItem("..."));
}

void ModifyDirDialog::on_pushButton_4_clicked() {
    this->currbi.append(*(new BanInfo(QInputDialog::getText(this, "Username?", "Please enter the username of the user to ban.", QLineEdit::Normal, "JuliusColesV2") + "|\n")));
    this->ui->tableWidget_3->setRowCount(this->currbi.size());
    this->ui->tableWidget_3->setItem(this->currbi.size() - 1, 0, new QTableWidgetItem(this->currbi[this->currbi.size() - 1].getUsername()));
    this->ui->tableWidget_3->setItem(this->currci.size() - 1, 1, new QTableWidgetItem(""));
}
