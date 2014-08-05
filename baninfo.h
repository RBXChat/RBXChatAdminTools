#ifndef BANINFO_H
#define BANINFO_H
#include <QString>

class BanInfo
{
public:
    BanInfo(QString constructorstr);

    QString getUsername() const;
    QString getReason() const;

    void setUsername(QString username);
    void setReason(QString reason);

    void operator=(BanInfo* copyclass);
private:
    QString username;
    QString reason;
};

#endif // BANINFO_H
