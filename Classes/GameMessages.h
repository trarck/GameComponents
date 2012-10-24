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
    ANIMATION,
    CHANGE_ANIMATION,
    //attack
    ATTACK,
    SET_ATTACK_TARGET,
    AUTO_ATTACK,
    DIE,
    //move
    MOVE_TO,
    MOVE_DIRECTION,
    MOVE_DIRECTION_TO,
    MOVE_DIRECTION_STOP
};



#endif //__Game_Message_h__
