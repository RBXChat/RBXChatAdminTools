#ifndef CHANNELINFO_H
#define CHANNELINFO_H
#include <QString>
#include <QStringList>

class ChannelInfo
{
public:
    ChannelInfo(QString constructorstr);

    QString getName() const;
    QStringList getOperatorList() const;
    QStringList getWhiteList() const;
    QStringList getBlackList() const;
    QStringList getMuteList() const;

    void setName(QString name);
    void setOperatorList(QStringList oplist);
    void setWhiteList(QStringList whitelist);
    void setBlackList(QStringList blacklist);
    void setMuteList(QStringList mutelist);

    void operator=(ChannelInfo* copyclass);
private:
    QString name;
    QStringList oplist;
    QStringList whitelist;
    QStringList blacklist;
    QStringList mutelist;
};

#endif // CHANNELINFO_H
