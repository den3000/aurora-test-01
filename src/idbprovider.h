#ifndef IDBPROVIDER_H
#define IDBPROVIDER_H

// TODO: use connection names

struct IDbProvider {
    virtual void openDb() = 0;
    virtual void closeDb() = 0;
};

#endif // IDBPROVIDER_H
