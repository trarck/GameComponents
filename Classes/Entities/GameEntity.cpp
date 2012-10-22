#include "CCMessageManager.h"
#include "GameEntity.h"
#include "GameMessages.h"

NS_CC_BEGIN

//guid通常由服务端生成建议从1000000开始，有时候客户端也需要一些临时的对象，guid由客户端生成从0-10000000

GameEntity::GameEntity()
:m_guid(0)
//,m_view(NULL)
{
    CCLOG("GameEntity create");
    m_components=new CCDictionary();
}

GameEntity::~GameEntity()
{
    CCLOG("GameEntity destroy");
    
//    CC_SAFE_RELEASE(m_view);
    
    CCDictElement* pElement = NULL;
    CCDICT_FOREACH(m_components,pElement){
        Component* component=(Component*)pElement->getObject();
        component->cleanupMessages();
    }
    CC_SAFE_RELEASE(m_components);
    
}

bool GameEntity::init()
{
    CCLOG("GameEntity init");
    CCSprite::init();
    m_guid=m_uID;
//    m_view=new CCSprite();
//    m_view->init();
	return true;
}

bool GameEntity::init(int guid)
{
    init();
    m_guid=guid;
	return true;
}


int GameEntity::guid()
{
    return m_guid;
}

void GameEntity::guid(int guid)
{
    m_guid=guid;
}

CCSprite* GameEntity::view()
{
    return this;
}

void GameEntity::view(CCSprite* view)
{
//    CC_SAFE_RETAIN(view);
//    CC_SAFE_RELEASE(m_view);
//    m_view=view;
}

void GameEntity::cleanup(){
    CCSprite::cleanup();
    cleanupMessages();
}


void GameEntity::registerMessage(MessageType type,SEL_MessageHandler handle , CCObject* sender)
{
    CCMessageManager::defaultManager()->registerReceiver(this,handle,type,sender);
}

void GameEntity::unregisterMessage(MessageType type ,SEL_MessageHandler handle ,CCObject* sender)
{
    CCMessageManager::defaultManager()->removeReceiver(this,type,sender,handle);
}

//void GameEntity::sendMessage(MessageType type ,CCObject* receiver ,CCDictionary* data)
//{
//    CCMessageManager::defaultManager()->dispatchMessageWithType(type,this,receiver,data);
//}

void GameEntity::sendMessage(MessageType type ,CCObject* receiver ,CCObject* data)
{
    CCMessageManager::defaultManager()->dispatchMessageWithType(type,this,receiver,data);
}

void GameEntity::sendMessage(MessageType type ,CCObject* receiver)
{
    CCMessageManager::defaultManager()->dispatchMessageWithType(type,this,receiver);
}

void GameEntity::cleanupMessages()
{
    CCMessageManager::defaultManager()->removeReceiver(this);
}

void GameEntity::setupComponents()
{
	CCLOG("GameEntity::setupComponent");
}
//
//inline void GameEntity::addComponent(Component* component)
//{
//    m_components->setObject(component, component->getName());
//}
//
//inline void GameEntity::addComponent(Component* component,const char* name)
//{
//    CCLOG("addComponent component named %s",name);
//    m_components->setObject(component, name);
//}


void GameEntity::setHp(int hp)
{
    if(hp<=0){
        hp=0;
        sendMessage(DIE,NULL);
    }
    m_hp=hp;
}

int GameEntity::getHp()
{
    return m_hp;
}

NS_CC_END
