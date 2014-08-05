#include "channelinfo.h"
#include <QDebug>

ChannelInfo::ChannelInfo(QString constructorstr) {
    QStringList elements = constructorstr.split("|");
    qDebug() << constructorstr;
    this->name = elements[0];
    if (elements[1].length())
        this->oplist = elements[1].split("-");
    if (elements[2].length())
        this->whitelist = elements[2].split("-");
    if (elements[3].length())
        this->blacklist = elements[3].split("-");
    if (elements[4].length())
        this->mutelist = elements[4].split("-");
}



QString ChannelInfo::getName() const {
    return this->name;
}
QStringList ChannelInfo::getOperatorList() const {
    return this->oplist;
}
QStringList ChannelInfo::getWhiteList() const {
    return this->whitelist;
}
QStringList ChannelInfo::getBlackList() const {
    return this->blacklist;
}
QStringList ChannelInfo::getMuteList() const {
    return this->mutelist;
}


void ChannelInfo::setName(QString name) {
    this->name = name;
}
void ChannelInfo::setOperatorList(QStringList oplist) {
    this->oplist = oplist;
}
void ChannelInfo::setWhiteList(QStringList whitelist) {
    this->whitelist = whitelist;
}
void ChannelInfo::setBlackList(QStringList blacklist) {
    this->blacklist = blacklist;
}
void ChannelInfo::setMuteList(QStringList mutelist) {
    this->mutelist = mutelist;
}

void ChannelInfo::operator=(ChannelInfo* copyclass) {
    this->name = copyclass->name;
    this->oplist = copyclass->oplist;
    this->whitelist = copyclass->whitelist;
    this->blacklist = copyclass->blacklist;
    this->mutelist = copyclass->mutelist;
}
