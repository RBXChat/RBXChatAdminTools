#include <QDebug>
#include "authenticationinfo.h"

AuthenticationInfo::AuthenticationInfo(QString constructorstr) {
    QString unbuffer, pwbuffer, emailbuffer, vercodebuffer, verifiedbuffer;
    QChar c;
    int mode = 0;
    for (int i = 0; i < constructorstr.length(); i++) {
        c = constructorstr.at(i);
        //qDebug() << c;
        if (c == '|') {
            if (mode == 0) {
                this->username = unbuffer;
                mode = 1;
                //qDebug() << "unsep " << unbuffer;
                unbuffer = QString("");
            }
            else if (mode == 1) {
                this->passwordhash = pwbuffer;
                mode = 2;
                //qDebug() << "pwsep " << pwbuffer;
                pwbuffer = QString("");
            }
            else if (mode == 2) {
                this->rblxun = emailbuffer;
                mode = 3;
                //qDebug() << "emsep " << emailbuffer;
                emailbuffer = QString("");
            }
            else if (mode == 3) {
                this->vercode = vercodebuffer;
                mode = 4;
                //qDebug() << "vcsep " << vercodebuffer;
                vercodebuffer = QString("");
            }
        }
        else if (c == '\n') {
            this->isverified = (verifiedbuffer == "true") ? true : false;
            mode = 0;
            //qDebug() << "versep" << verifiedbuffer;
            verifiedbuffer = QString("");
        }
        else
            if (mode == 1)
                pwbuffer += QString(c);
            else if (mode == 2)
                emailbuffer += QString(c);
            else if (mode == 3)
                vercodebuffer += QString(c);
            else if (mode == 4)
                verifiedbuffer += QString(c);
            else
                unbuffer += QString(c);
        //cout << "gen" << endl;
    }
}

void AuthenticationInfo::operator=(AuthenticationInfo* copyclass) {
    this->username = copyclass->username;
    this->passwordhash = copyclass->passwordhash;
    this->rblxun = copyclass->rblxun;
    this->vercode = copyclass->vercode;
    this->isverified = copyclass->isverified;
};




QString AuthenticationInfo::getUsername() const {
    return this->username;
}
QString AuthenticationInfo::getPasswordHash() const {
    return this->passwordhash;
}
QString AuthenticationInfo::getROBLOXUsername() const {
    return this->rblxun;
}
QString AuthenticationInfo::getVerificationCode() const {
    return this->vercode;
}
bool AuthenticationInfo::isVerified() const {
    return this->isverified;
}


void AuthenticationInfo::setUsername(QString username) {
    this->username = username;
}
void AuthenticationInfo::setPasswordHash(QString passwordhash) {
    this->passwordhash = passwordhash;
}
void AuthenticationInfo::setROBLOXUsername(QString rblxun) {
    this->rblxun = rblxun;
}
void AuthenticationInfo::setVerificationCode(QString vercode) {
    this->vercode = vercode;
}
void AuthenticationInfo::setIsVerified(bool isverified) {
    this->isverified = isverified;
}
void AuthenticationInfo::setIsVerifiedString(QString isverified) {
    this->isverified = (isverified == "true") ? true : false;
}

QString AuthenticationInfo::isVerifiedString() const {
    return (this->isverified) ? "true" : "false";
}
