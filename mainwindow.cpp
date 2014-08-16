#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "modifydirdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_openDialog_clicked() {
    this->ui->fileLine->setText(QFileDialog::getExistingDirectory(this, tr("Open Directory..."), ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void MainWindow::on_loadDir_clicked() {
    QFile checkAuth(this->ui->fileLine->text() + "/auth.rbxca");
    QFile checkChan(this->ui->fileLine->text() + "/chan.rbxcc");
    QFile checkBan(this->ui->fileLine->text() + "/bans.rbxcb");
    bool success = true;
    if (!checkAuth.exists()) {
        success = false;
        qDebug() << "auth doesnt exist";
    }
    if (!checkChan.exists()) {
        success = false;
        qDebug() << this->ui->fileLine->text() + "/chan.rxbcc";
    }
    if (!checkBan.exists()) {
        success = false;
        qDebug() << "ban doesnt exist";
    }
    //qDebug() << success;
    if (!success)
        QMessageBox::warning(this, "Invalid path", "The directory you gave does not contain the following files:\nauth.rbxca\nchan.rbxcc\nbans.rbxcb");
    else {
        this->hide();
        ModifyDirDialog* diropenedwin = new ModifyDirDialog(0, this->ui->fileLine->text());
        diropenedwin->show();
    }
}
