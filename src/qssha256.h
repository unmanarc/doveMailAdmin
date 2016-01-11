#ifndef QSSHA256_H
#define QSSHA256_H

#include <QString>

#define SSHA256_SALT_SIZE 4

class QSSHA256
{
public:
    QSSHA256();
    QString genSSHA256Password(const QString & password);
};

#endif // QSSHA256_H
