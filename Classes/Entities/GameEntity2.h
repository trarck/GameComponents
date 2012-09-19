#ifndef __Game_Entity2_H__
#define __Game_Entity2_H__

#include "cocos2d.h"
#include "CCMessage.h"
#include "CCMessageHandler.h"
#include "ComponentEntity.h"

NS_CC_BEGIN

//class Component;

class GameEntity : public ComponentEntity {
public:
    
    GameEntity();
    ~GameEntity();
    
    bool init();
    bool init(int guid);
    
    int guid();
    void guid(int guid);
    
    void registerMessage(MessageType type,SEL_MessageHandler handle , CCObject* sender);
    void unregisterMessage(MessageType type ,SEL_MessageHandler handle ,CCObject* sender);
    void sendMessage(MessageType type ,CCObject* receiver ,CCDictionary* data);
    
    //components
//    virtual void setupComponents();
//    void addComponent(Component* component);
//    void addComponent(Component* component,const char *name);
protected:
	int m_guid;//game object id
//    CCDictionary* m_components;
};

NS_CC_END

//+(int) guid;
#endif //__Game_Entity2_H__
