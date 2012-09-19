//
//  ComponentEntity.h
//  GameComponents
//
//  Created by duanhouhai on 12-9-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef __Component_Entity_h__
#define __Component_Entity_h__

#include "cocos2d.h"
#include "Component.h"


NS_CC_BEGIN

class ComponentEntity:public CCObject
{
public:
    
    ComponentEntity();
    ~ComponentEntity();
    
    virtual void setupComponents();
    
    void addComponent(Component* component);
    void addComponent(Component* component,const char* name);
protected:
    CCDictionary* m_components;

};

NS_CC_END


#endif //__Component_Entity_h__
