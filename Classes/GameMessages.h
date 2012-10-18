//
//  GameMessage.h
//  GameComponents
//
//  Created by duanhouhai on 12-9-19.
//

#ifndef __Game_Messages_h__
#define __Game_Messages_h__

#include "CCMessage.h"

enum GameMessage
{
    ALL=0,
    //attack
    ATTACK=10,
    SET_ATTACK_TARGET=11,
    AUTO_ATTACK=12,
    DIE=20
};



#endif //__Game_Message_h__
