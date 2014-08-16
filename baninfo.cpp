#include "baninfo.h"
#include <QDebug>

BanInfo::BanInfo(QString constructorstr) {
    QString unbuffer, reasonbuffer;
    int i, mode = 0;
    QChar c;
    for (i = 0; i < constructorstr.length(); i++) {
        c = constructorstr.at(i);
        if (c == '|') {
            this->username = unbuffer;
            mode = 1;
            unbuffer = QString("");
        }
        else if (c == '\n') {
            this->reason = reasonbuffer;
            //qDebug() << "reason" << reasonbuffer;
            mode = 0;
            reasonbuffer = QString("");
        }
        else
            if (!mode)
               unbuffer += QString(c);
            else
                reasonbuffer += QString(c);
    }
}

QString BanInfo::getUsername() const {
    return this->username;
}
QString BanInfo::getReason() const {
    return this->reason;
}


void BanInfo::setUsername(QString username) {
    this->username = username;
}
void BanInfo::setReason(QString reason) {
    this->reason = reason;
}



void BanInfo::operator=(BanInfo* copyclass) {
    this->username = copyclass->username;
    this->reason = copyclass->reason;
}
