#include "AutoAttackComponent.h"
#include "CCMessageManager.h"
#include "GameMessages.h"

NS_CC_BEGIN

AutoAttackComponent::AutoAttackComponent()
:m_attackSpeed(2)
{
    CCLOG("AutoAttackComponent create");
    m_name="AutoAttackComponent";
}

AutoAttackComponent::~AutoAttackComponent()
{
    CCLOG("AutoAttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool AutoAttackComponent::init()
{
    CCLOG("AutoAttackComponent init");
    return true;
}

void AutoAttackComponent::handleMessage(CCMessage *message)
{
        
    GameEntity* target;
    
    switch(message->getType()){
            
		case AUTO_ATTACK:
            target=(GameEntity*)message->getObjectData();
            if(target){
                setTarget(target);
            }
			attack();
			break;
        default:
            AttackComponent::handleMessage(message);
            break;
	}

}

bool AutoAttackComponent::registerMessages()
{
    
//    bool ret= AttackComponent::registerMessages();
    
    CCMessageManager::defaultManager()->registerReceiver(m_owner, message_selector(AttackComponent::handleMessage), SET_ATTACK_TARGET, NULL,this);
    
    CCMessageManager::defaultManager()->registerReceiver(m_owner, message_selector(AttackComponent::handleMessage), AUTO_ATTACK, NULL,this);

    
    return true;

}


void AutoAttackComponent::attack()
{
    CCLOG("AutoAttackComponent::startAttack");
	if (m_target) {
        CCDirector* director = CCDirector::sharedDirector();
        CCScheduler* pScheduler = director->getScheduler();
        pScheduler->scheduleSelector(schedule_selector(AutoAttackComponent::updateAttack),this, m_attackSpeed, false);
	}
}

void AutoAttackComponent::stopAttack()
{
    CCLOG("AutoAttackComponent::stopAttack");
    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* pScheduler = director->getScheduler();
    pScheduler->unscheduleSelector(schedule_selector(AutoAttackComponent::updateAttack),this);
}

void AutoAttackComponent::updateAttack(float delta)
{
    CCLOG("AutoAttackComponent::updateAttack");
	//check attack stop
	/*
	 1.target die
	 2.if use skill, mp less then the skill requirement

	 */
	int targetHp=m_target->getHp();
    CCLOG("current target hp %d after attack %d",targetHp,targetHp-1);
    m_target->setHp(targetHp-1);
}

void AutoAttackComponent::didTargetDie()
{
    stopAttack();
}

float AutoAttackComponent::getAttackSpeed()
{
	return m_attackSpeed;
}

void AutoAttackComponent::setAttackSpeed(float attackSpeed)
{
	m_attackSpeed=attackSpeed;
}

NS_CC_END

