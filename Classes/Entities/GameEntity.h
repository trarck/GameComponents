#ifndef __Game_Entity_H__
#define __Game_Entity_H__

#include "cocos2d.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"
#include "Component.h"

NS_CC_BEGIN

//class Component;

class GameEntity : public CCSprite {
public:
    
    GameEntity();
    ~GameEntity();
    
    bool init();
    bool init(int guid);
    
    int guid();
    void guid(int guid);
    
    virtual CCSprite* view();
    virtual void view(CCSprite* view);
    
    void registerMessage(MessageType type,SEL_MessageHandler handle , CCObject* sender);
    void unregisterMessage(MessageType type ,SEL_MessageHandler handle ,CCObject* sender);
//    void sendMessage(MessageType type ,CCObject* receiver ,CCDictionary* data);
    void sendMessage(MessageType type ,CCObject* receiver ,CCObject* data);
    void sendMessage(MessageType type ,CCObject* receiver);
    
	void cleanupMessages();
    virtual void cleanup();
    
    //components
    virtual void setupComponents();
    void addComponent(Component* component){
        CCLOG("addComponent component named %s",component->getName());
        m_components->setObject(component, component->getName());
    };
    void addComponent(Component* component,const char *name){
        CCLOG("addComponent component named %s",name);
        m_components->setObject(component, name);
    };
    Component* getComponent(const char *name){
        return (Component*) m_components->objectForKey(name);
    };

    void setHp(int hp);
    int getHp();
    
protected:
	int m_guid;//game object id
    CCDictionary* m_components;
    
    unsigned int m_hp;
    
//    CCSprite* m_view;
};

NS_CC_END

//+(int) guid;
#endif //__Game_Entity_H__
