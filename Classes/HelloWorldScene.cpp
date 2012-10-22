#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Player.h"
#include "GameMessages.h"
#include "CCMessageManager.h"
#include "AttackComponent.h"

#include "AutoAttackComponent.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(screenSize.width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...
    Player* player=new Player();
    CCLOG("player count=%d",player->retainCount());
    player->init();
    CCLOG("player count=%d",player->retainCount());
    player->setupComponents();
    CCLOG("player count=%d",player->retainCount());
    
    player->setPosition(ccp(screenSize.width/2, screenSize.height/2));
    
//    this->addChild(player->view());
    this->addChild(player);
    
    CCDictionary* data=new CCDictionary();
    data->setObject(CCString::create("idle"), "name");
    data->setObject(CCInteger::create(0), "direction");
    
    CCLOG("set begin action");
    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, player,data);
    CCLOG("set begin action after");
    
    
    GameEntity* target=new GameEntity();
    target->setHp(10);
    
//    player->sendMessage(SET_ATTACK_TARGET, NULL, target);
    
    CCLOG("send attack message");
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(ATTACK, NULL, player,target);
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(ATTACK, NULL, player,target);
    
    for(int i=0;i<1;i++){
        CCMessageManager::defaultManager()->dispatchMessageWithType(ATTACK, NULL, player);
    }
    
//    AttackComponent* attackComponent=(AttackComponent*)player->getComponent("AttackComponent");
    
    target->release();
    player->release();
    
//    player->removeFromParentAndCleanup(true);

    
//    CCLOG("attackComponent count=%d",attackComponent->retainCount());
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    this->removeAllChildrenWithCleanup(true);
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
