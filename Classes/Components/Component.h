#ifndef __Component_H__
#define __Component_H__

#include "cocos2d.h"

class Component : public cocos2d::CCLayer
{
public:
    virtual bool init();  
    virtual CCObject* getOwner();
    virtual setOwner(CCObject* owner);
};

#endif // __Component_H__
