#ifndef __Component_H__
#define __Component_H__

#include "cocos2d.h"

NS_CC_BEGIN

class Component : public CCObject
{
public:
    virtual bool init();  
	
	virtual CCObject* getOwner();
	virtual setOwner(CCObject* owner);
};

NS_CC_END

#endif // __Component_H__
