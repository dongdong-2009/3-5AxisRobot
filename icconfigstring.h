#ifndef ICCONFIGSTRING_H
#define ICCONFIGSTRING_H

#include <QString>

class ICConfigString
{
public:

    enum {
        kCS_Global_Speed,
        KCS_User_Changed,
    };


    ICConfigString();

    static QString ConfigString(int configID);

};

#endif // ICCONFIGSTRING_H
