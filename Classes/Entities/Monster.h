#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "GameEntity.h"

NS_CC_BEGIN

class Monster : public GameEntity {
public:
    Monster();
    ~Monster();
    
    virtual void setupComponents();

};

NS_CC_END

#endif //__Player_H__
