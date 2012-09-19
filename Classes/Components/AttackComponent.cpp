#include "AttackComponent.h"
#include "CCCompleteMessageManager.h"
#include "GameMessages.h"

NS_CC_BEGIN

AttackComponent::AttackComponent()
:m_target(NULL)
{
    CCLOG("AttackComponent create");
    m_name="AttackComponent";
}

AttackComponent::~AttackComponent()
{
    CCLOG("AttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool AttackComponent::init()
{
    CCLOG("AttackComponent init");
    return true;
}

void AttackComponent::handleMessage(CCMessage *message)
{
    CCLOG("AttackComponent::handleMessage");
    CCLOG("get message %d",message->getType());
}

bool AttackComponent::registerMessages()
{
    CCLOG("AttackComponent::registerMessages");
    
    return true;
}

bool AttackComponent::registerOwnerMessages()
{
    CCLOG("AttackComponent::registerOwnerMessages");
    CCAssert(m_owner!=NULL, "the owner is null for registerOwnerMessages");
    
    CCCompleteMessageManager::sharedCompleteMessageManager()->registerReceiver(this, message_selector(AttackComponent::handleMessage), ATTACK, NULL);
    
    return true;
}

void AttackComponent::cleanupMessages()
{
    CCCompleteMessageManager::sharedCompleteMessageManager()->removeReceiver(this);
}



void AttackComponent::startAttack()
{
    CCLOG("AttackComponent::startAttack");
	if (m_target) {
        CCDirector* director = CCDirector::sharedDirector();
        CCScheduler* pScheduler = director->getScheduler();
        pScheduler->scheduleSelector(schedule_selector(AttackComponent::updateAttack),this, 2, false);
	}
}

void AttackComponent::stopAttack()
{
    CCLOG("AttackComponent::stopAttack");
    CCDirector* director = CCDirector::sharedDirector();
    CCScheduler* pScheduler = director->getScheduler();
    pScheduler->unscheduleSelector(schedule_selector(AttackComponent::updateAttack),this);
}

void AttackComponent::updateAttack(float delta)
{
    CCLOG("AttackComponent::updateAttack");
	//--m_target.hp;
}

void AttackComponent::attackWithSkillId(int skillId)
{
	//if (m_target!=nil) {
	//		//攻击动作
	//		//攻击效果
	//	}
}

GameEntity* AttackComponent::getTarget()
{
    return m_target;
}

void AttackComponent::setTarget(GameEntity* target)
{
    CC_SAFE_RETAIN(target);
    CC_SAFE_RELEASE(m_target);
    m_target=target;
}

NS_CC_END

