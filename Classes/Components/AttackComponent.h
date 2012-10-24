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
    virtual bool init();
    
    virtual bool registerMessages();
    virtual void handleMessage(CCMessage* message);
    virtual void cleanupMessages();
    
    virtual void attack();
    virtual void attackWithSkillId(int skillId);
    
    virtual void didTargetDie();
    //property
    
    
    virtual void setTarget(GameEntity* target);
    GameEntity* getTarget();
    
protected:
    GameEntity* m_target;
};

NS_CC_END

#endif //__Attack_Component_H__
