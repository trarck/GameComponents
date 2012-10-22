#include "Player.h"
#include "AnimationComponent.h"

#include "AttackComponent.h"
#include "GameMessages.h"
#include "AutoAttackComponent.h"


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
    
    //animation
    
    AnimationComponent* animationComponent=new AnimationComponent();
    animationComponent->init();
    animationComponent->setOwner(this);
    
    
    //move animation
    animationComponent->addActionList(
                                      AnimationComponent::eightDirectionActionListWithDir("characters/2/0", 10, CCSizeMake(62, 91), 0.15f, "%s/%02d%03d.png"), 
                                      "idle");
    
    animationComponent->addActionList(
                            AnimationComponent::eightDirectionActionListWithDir("characters/2/1", 8, CCSizeMake(74, 93), 0.1f, "%s/%02d%03d.png"), 
                            "move");
    
    animationComponent->registerMessages();
    
    addComponent(animationComponent);
    animationComponent->release();
    
//    CCDictionary* data=new CCDictionary();
//    data->setObject(CCString::create("idle"), "name");
//    data->setObject(CCInteger::create(0), "direction");
//    
//    CCLOG("set begin action");
//    sendMessage(CHANGE_ANIMATION, this, data);
//    CCLOG("set begin action after");
    //attack
    
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
    
    //auto attack
    AutoAttackComponent* autoAttackComponent=new AutoAttackComponent();
    autoAttackComponent->init();
    autoAttackComponent->setOwner(this);
    autoAttackComponent->registerMessages();
    addComponent(autoAttackComponent);
    autoAttackComponent->release();

}

NS_CC_END
