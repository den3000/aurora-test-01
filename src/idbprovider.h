#ifndef IDBPROVIDER_H
#define IDBPROVIDER_H

// TODO: use connection names

struct IDbProvider {
    virtual void connectToDBs() = 0;
    virtual void disconnectFromDBs() = 0;
};

#endif // IDBPROVIDER_H
