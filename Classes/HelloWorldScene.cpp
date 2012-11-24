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
    
    CCMenuItemLabel *pRunItem=CCMenuItemLabel::create(CCLabelTTF::create("run", "Arial", 20),
                                                      this, 
                                                      menu_selector(HelloWorld::menuRunCallback));
    pRunItem->setPosition(ccp(screenSize.width-100,20));
    
    CCMenuItemLabel *pStopItem=CCMenuItemLabel::create(CCLabelTTF::create("stop", "Arial", 20),
                                                      this, 
                                                      menu_selector(HelloWorld::menuStopCallback));
    pStopItem->setPosition(ccp(screenSize.width-200,20));
    
    CCMenuItemLabel *pMoveToItem=CCMenuItemLabel::create(CCLabelTTF::create("moveTo", "Arial", 20),
                                                       this, 
                                                       menu_selector(HelloWorld::menuMoveToCallback));
    pMoveToItem->setPosition(ccp(screenSize.width-300,20));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem,pRunItem,pStopItem,pMoveToItem, NULL);
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
    
    m_player=player;
    
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

void HelloWorld::menuRunCallback(CCObject* pSender)
{
//    CCDictionary* data=new CCDictionary();
//    data->setObject(CCString::create("move"), "name");
//    data->setObject(CCInteger::create(3), "direction");
//    
//    CCLOG("set begin action");
//    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_player,data);
//    CCLOG("set begin action after");
    
    CCInteger* degree=CCInteger::create(45);
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_DIRECTION, NULL, m_player,degree);

}

void HelloWorld::menuStopCallback(CCObject* pSender)
{
//    CCDictionary* data=new CCDictionary();
//    data->setObject(CCString::create("idle"), "name");
//    data->setObject(CCInteger::create(0), "direction");
//    
//    CCLOG("set begin action");
//    CCMessageManager::defaultManager()->dispatchMessageWithType(CHANGE_ANIMATION, NULL, m_player,data);
//    CCLOG("set begin action after");

    
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_DIRECTION_STOP, NULL, m_player);
}

void HelloWorld::menuMoveToCallback(CCObject* pSender)
{
   
    
    CCSize screenSize= CCDirector::sharedDirector()->getWinSize();
    CCPoint to=ccp(screenSize.width/2+50,screenSize.height/2+50);
    
    CCMessageManager::defaultManager()->dispatchMessageWithType(MOVE_TO, NULL, m_player,&to);
    
}
