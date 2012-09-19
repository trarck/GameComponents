#ifndef __Component_H__
#define __Component_H__

#include "cocos2d.h"
#include "CCMessage.h"

NS_CC_BEGIN

//typedef CCObject GameEntity;

class Component : public CCObject
{
public:
    Component();
    ~Component();
    
    virtual bool init(void);  
    
    virtual bool registerMessages();
    virtual bool registerOwnerMessages();
    virtual void handleMessage(CCMessage* message);
	virtual void cleanupMessages();
    //使用GameEntity也没有意义，具体还要使用强制类型转换
    //弱连接
	CCObject* getOwner();
	void setOwner(CCObject* owner);
    
//    GameEntity* getOwner();
//	void setOwner(GameEntity* owner);
    
    const char* getName();
    void setName(const char* name);
protected:
    CCObject* m_owner;
    std::string m_name;
};

NS_CC_END

#endif // __Component_H__
