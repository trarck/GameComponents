#ifndef __Manual_Attack_Component_H__
#define __Manual_Attack_Component_H__

#include "cocos2d.h"
#include "AttackComponent.h"
#include "GameEntity.h"

NS_CC_BEGIN


class ManualAttackComponent : public AttackComponent 
{
public:
    ManualAttackComponent();
    ~ManualAttackComponent();
    virtual bool init();
    
    
    //property
};

NS_CC_END

#endif //__Manual_Attack_Component_H__
