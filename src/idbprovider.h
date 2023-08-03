#ifndef IDBPROVIDER_H
#define IDBPROVIDER_H

class IDbProvider {
public:
    virtual void openDb() = 0;
    virtual void closeDb() = 0;
};

#endif // IDBPROVIDER_H
