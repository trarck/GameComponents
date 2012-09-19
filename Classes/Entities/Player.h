#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "GameEntity.h"

NS_CC_BEGIN

class Player : public GameEntity {
public:
    Player();
    ~Player();
    
    virtual void setupComponents();

private:

};

NS_CC_END

#endif //__Player_H__
