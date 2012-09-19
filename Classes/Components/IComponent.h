#ifndef __IComponent_H__
#define __IComponent_H__

#include "cocos2d.h"

NS_CC_BEGIN

typedef CCObject GameEntity;

class IComponent : public CCObject
{
public:
    virtual bool init();  
    
    virtual bool registerEvents();
	
	virtual GameEntity* getOwner();
	virtual void setOwner(GameEntity* owner);
};

NS_CC_END

#endif // __IComponent_H__
