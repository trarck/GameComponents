#include "CCCompleteMessageManager.h"
#include "GameEntity.h"

NS_CC_BEGIN

//guid通常由服务端生成建议从1000000开始，有时候客户端也需要一些临时的对象，guid由客户端生成从0-10000000

GameEntity::GameEntity()
:m_guid(0)
{
    CCLOG("GameEntity create");
}

GameEntity::~GameEntity()
{
    CCLOG("GameEntity destroy");
}

bool GameEntity::init()
{
    m_guid=m_uID;
	return true;
}

bool GameEntity::init(int guid)
{
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

void GameEntity::registerMessage(MessageType type,SEL_MessageHandler handle , CCObject* sender)
{
    CCCompleteMessageManager::sharedCompleteMessageManager()->registerReceiver(this,handle,type,sender);
}

void GameEntity::unregisterMessage(MessageType type ,SEL_MessageHandler handle ,CCObject* sender)
{
    CCCompleteMessageManager::sharedCompleteMessageManager()->removeReceiver(this,handle,type,sender);
}

void GameEntity::sendMessage(MessageType type ,CCObject* receiver ,CCDictionary* data)
{
    CCCompleteMessageManager::sharedCompleteMessageManager()->dispatchMessageWithType(type,this,receiver,data);
}


//void GameEntity::setupComponents()
//{
//	CCLOG("GameEntity::setupComponent");
//}

//void GameEntity::addComponent(Component* component)
//{
//    m_components->setObject(component, component->getName());
//}
//
//void GameEntity::addComponent(Component* component,const char* name)
//{
//    CCLOG("addComponent component named %s",name);
//    m_components->setObject(component, name);
//}

NS_CC_END
