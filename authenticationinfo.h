#ifndef AUTHENTICATIONINFO_H
#define AUTHENTICATIONINFO_H

#include <QString>

class AuthenticationInfo
{
public:
    AuthenticationInfo(QString constructorstr);

    QString getUsername() const;
    QString getPasswordHash() const;
    QString getROBLOXUsername() const;
    QString getVerificationCode() const;
    bool isVerified() const;
    QString isVerifiedString() const;

    void setUsername(QString username);
    void setPasswordHash(QString passwordhash);
    void setROBLOXUsername(QString rblxun);
    void setVerificationCode(QString vercode);
    void setIsVerified(bool isverified);
    void setIsVerifiedString(QString isverified);

    void operator=(AuthenticationInfo* copyclass);
private:
    QString username;
    QString passwordhash;
    QString rblxun;
    QString vercode;
    bool isverified;
};

#endif // AUTHENTICATIONINFO_H
