#ifndef SERVERPARAMS_H
#define SERVERPARAMS_H

#include <QString>

struct serverParams
{
    bool operator==(const serverParams & x) const
    {
        return x.serverName == serverName;
    }

    QString serverName;
    uint16_t port;
    QString dbhost,user,pass,dbname;
};

inline uint qHash(const serverParams& x)
{
    return qHash(x.serverName);
}


#endif // SERVERPARAMS_H
