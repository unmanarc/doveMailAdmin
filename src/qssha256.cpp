/**
 *  @author  Aaron Mizrachi (aaron@unmanarc.com)
 *  @date    29/12/2016
 *  @version 1.0
 *
 *  @brief Dovecot Mail Administration
 *
 *  @section DESCRIPTION
 *
 *  This is a little program to organize your emails on
 *  your private email server (dovecot+postfix+mysql based)
 *
 *  If you need support or any new features please feel free
 *  to contact me.
 *
 *  Telegram: @unmanarc
 *  Email:    aaron@unmanarc.com
 *  Github:   /unmanarc
 *  Web:      https://www.unmanarc.com/
 *
 */
#include "qssha256.h"
#include <QCryptographicHash>
#include <QDebug>
#include <random>


QSSHA256::QSSHA256()
{

}

QString QSSHA256::genSSHA256Password(const QString &password)
{
    QCryptographicHash chash(QCryptographicHash::Sha256);
    char salt[SSHA256_SALT_SIZE];

    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> dist(0, 255.0);
    for (unsigned int i=0;i<SSHA256_SALT_SIZE;i++)
    {
        salt[i]=dist(mt);
    }

    chash.addData(password.toStdString().c_str(), password.toStdString().size());
    chash.addData(salt,SSHA256_SALT_SIZE);

    QByteArray saltedHash = chash.result();
    saltedHash.append(salt,SSHA256_SALT_SIZE);

    return "{SSHA256}" + QString().fromStdString(saltedHash.toBase64().toStdString());
}
