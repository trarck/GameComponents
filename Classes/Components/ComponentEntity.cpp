//
//  ComponentEntity.cpp
//  GameComponents
//
//  Created by duanhouhai on 12-9-19.
//

#include "ComponentEntity.h"


NS_CC_BEGIN

ComponentEntity::ComponentEntity()
{
    CCLOG("ComponentEntity create");
    m_components=new CCDictionary();
}

ComponentEntity::~ComponentEntity()
{
    CCLOG("ComponentEntity destroy");
    CC_SAFE_RELEASE(m_components);
}

void ComponentEntity::setupComponents()
{
    
}

void ComponentEntity::addComponent(Component* component)
{
    CCLOG("addComponent component named %s",component->getName());
    m_components->setObject(component, component->getName());
}

void ComponentEntity::addComponent(Component* component,const char* name)
{
    CCLOG("addComponent component named %s",name);
    m_components->setObject(component, name);
}

NS_CC_END