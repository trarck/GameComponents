#include "Monster.h"
#include "AttackComponent.h"
#include "GameMessages.h"

NS_CC_BEGIN

//guid通常由服务端生成建议从1000000开始，有时候客户端也需要一些临时的对象，guid由客户端生成从0-10000000

Monster::Monster()
{
    CCLOG("Monster create");
}

Monster::~Monster()
{
    CCLOG("Monster destroy");
}

void Monster::setupComponents()
{

}

NS_CC_END
