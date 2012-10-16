#include "Player.h"
#include "AttackComponent.h"
#include "GameMessages.h"

NS_CC_BEGIN

//guid通常由服务端生成建议从1000000开始，有时候客户端也需要一些临时的对象，guid由客户端生成从0-10000000

Player::Player()
{
    CCLOG("Player create");
}

Player::~Player()
{
    CCLOG("Player destroy");
}

void Player::setupComponents()
{
	CCLOG("Player::setupComponent");
    
    AttackComponent* attackComponent=new AttackComponent();
    CCLOG("attackComponent count=%d",attackComponent->retainCount());
    attackComponent->init();
    attackComponent->setOwner(this);
    CCLOG("attackComponent count=%d",attackComponent->retainCount());
    attackComponent->registerMessages();
    CCLOG("attackComponent count=%d",attackComponent->retainCount());
    
    addComponent(attackComponent);
    CCLOG("attackComponent count=%d",attackComponent->retainCount());
    
   
    attackComponent->release();
    CCLOG("attackComponent count=%d",attackComponent->retainCount());
}

NS_CC_END
