#include "ManualAttackComponent.h"
#include "CCMessageManager.h"
#include "GameMessages.h"

NS_CC_BEGIN

ManualAttackComponent::ManualAttackComponent()
{
    CCLOG("ManualAttackComponent create");
    m_name="ManualAttackComponent";
}

ManualAttackComponent::~ManualAttackComponent()
{
    CCLOG("ManualAttackComponent destroy");
    CC_SAFE_RELEASE(m_target);
}

bool ManualAttackComponent::init()
{
    CCLOG("ManualAttackComponent init");
    return true;
}

NS_CC_END

