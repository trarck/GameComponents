#ifndef __Attack_Component_H__
#define __Attack_Component_H__

#include "cocos2d.h"
#include "Component.h"
#include "GameEntity.h"

NS_CC_BEGIN


class AttackComponent : public Component 
{
public:
    AttackComponent();
    ~AttackComponent();
    bool init();
    
    virtual bool registerMessages();
    virtual bool registerOwnerMessages();
    virtual void handleMessage(CCMessage* message);
    virtual void cleanupMessages();
    
    void startAttack();
    void stopAttack();
    void updateAttack(float delta);
    void attackWithSkillId(int skillId);
    
    //property
    
    GameEntity* getTarget();
    void setTarget(GameEntity* target);
    
    float getAttackSpeed();
    void setAttackSpeed(float attackSpeed);
private:
    GameEntity* m_target;
    float m_attackSpeed;
};

NS_CC_END

#endif //__Attack_Component_H__
