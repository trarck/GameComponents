#include "AttackComponent.h"
#include "CCMessageManager.h"
#include "GameMessages.h"

NS_CC_BEGIN

AttackComponent::AttackComponent()
:m_target(NULL),
m_attackSpeed(2)
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

	switch(message->getType()){
		
		case ATTACK:
			startAttack();
			break;
		case DIE:
			stopAttack();
			break;

	}
}

bool AttackComponent::registerMessages()
{
    CCLOG("AttackComponent::registerMessages");
    
    CCMessageManager::defaultManager()->registerReceiver(this, message_selector(AttackComponent::handleMessage), ATTACK, m_owner);
    
    return true;
}

void AttackComponent::cleanupMessages()
{
    CCMessageManager::defaultManager()->removeReceiver(this);
}



void AttackComponent::startAttack()
{
    CCLOG("AttackComponent::startAttack");
	if (m_target) {
        CCDirector* director = CCDirector::sharedDirector();
        CCScheduler* pScheduler = director->getScheduler();
        pScheduler->scheduleSelector(schedule_selector(AttackComponent::updateAttack),this, m_attackSpeed, false);
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
	//check attack stop
	/*
	 1.target die
	 2.if use skill, mp less then the skill requirement

	 */
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

	CCMessageManager::defaultManager()->registerReceiver(this, message_selector(AttackComponent::handleMessage), DIE, m_target);
}

float AttackComponent::getAttackSpeed()
{
	return m_attackSpeed;
}

void AttackComponent::setAttackSpeed(float attackSpeed)
{
	m_attackSpeed=attackSpeed;
}

NS_CC_END

