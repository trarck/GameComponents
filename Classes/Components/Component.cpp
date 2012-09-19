#include "Component.h"

NS_CC_BEGIN

Component::Component()
:m_owner(NULL)
,m_name("Component")
{
    CCLOG("Component create");
}

Component::~Component()
{
    CCLOG("Component destroy");
//    CC_SAFE_RELEASE(m_owner);
}

bool Component::init(void)
{
    CCLOG("Component init");
    return true;
}

void Component::handleMessage(CCMessage *message)
{
    CCLOG("Component::startAttack");
}

bool Component::registerMessages()
{
    CCLOG("Component::registerMessages");
    
    return true;
}

bool Component::registerOwnerMessages()
{
    CCLOG("Component::registerOwnerMessages");
  
    return true;
}

void Component::cleanupMessages()
{
    CCLOG("Component::cleanupMessages");
}

CCObject* Component::getOwner()
{
    return m_owner;
}

void Component::setOwner(CCObject* owner)
{
//    CC_SAFE_RETAIN(owner);
//    CC_SAFE_RELEASE(m_owner);
    m_owner=owner;
}

const char* Component::getName()
{
    return m_name.c_str();
}

void Component::setName(const char* name)
{
    m_name=name;
}

NS_CC_END
