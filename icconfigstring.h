#ifndef ICCONFIGSTRING_H
#define ICCONFIGSTRING_H

#include <QString>

class ICConfigString
{
public:

    enum {
        kCS_Global_Speed,
        kCS_User_Changed,
        kCS_Mold_Changed,

        kCS_SIG_Fixture1,
        kCS_SIG_Fixture2,
        kCS_SIG_Fixture3,
        kCS_SIG_Fixture4,
        kCS_SIG_IMM_Stop,
        kCS_SIG_Z_Move_Pos,
        kCS_SIG_Origin,
        kCS_SIG_Y_Origin_Pos,
        kCS_SIG_Hor_Standby,
        kCS_SIG_CM_Limit,
        kCS_SIG_SEDoor,
        kCS_SIG_Press,
        kCS_SIG_Mid_Mold,
        kCS_SIG_EJE_Linked,
        kCS_SIG_Auto,

    };


    ICConfigString();

    static QString ConfigString(int configID);

};

#endif // ICCONFIGSTRING_H
