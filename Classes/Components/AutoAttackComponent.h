#ifndef __Auto_Attack_Component_H__
#define __Auto_Attack_Component_H__

#include "cocos2d.h"
#include "GameEntity.h"

#include "AttackComponent.h"

NS_CC_BEGIN


class AutoAttackComponent : public AttackComponent 
{
public:
    AutoAttackComponent();
    ~AutoAttackComponent();
    virtual bool init();
    
    virtual bool registerMessages();
    virtual void handleMessage(CCMessage* message);
    
    virtual void attack();
    virtual void didTargetDie();
    
    void stopAttack();
    void updateAttack(float delta);
    
    //property
    
    float getAttackSpeed();
    void setAttackSpeed(float attackSpeed);
protected:
    float m_attackSpeed;
};

NS_CC_END

#endif //__Auto_Attack_Component_H__
