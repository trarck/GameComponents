#ifndef __AnimationComponent_H__
#define __AnimationComponent_H__

#include "cocos2d.h"
#include "Component.h"
#include "GameEntity.h"

NS_CC_BEGIN

class AnimationComponent : public Component
{
public:
	AnimationComponent();
	~AnimationComponent();
	//extend from parent
	virtual bool init();  

	//for myself
	CCAction* moveAction();
	void moveActoin(CCAction* action);

	CCArray* actionArray();
	void actionArray(CCArray* actionArray);

	CCDictionary* animations();
	void animations(CCDictionary* animations);

	bool initWithFile(const std::string&  file);
    bool initWithData(CCDictionary* data);

	CCObject* animationForName(const std::string& name);
	CCAction* actionForName(const std::string& name);
	CCAction* actionForName(const std::string& name ,int index);
	CCAction* actionForName(const std::string& name ,const std::string& key);

	CCArray* actionListForName(const std::string& name);
	CCDictionary* actionMapForName(const std::string& name);

	void addAction(CCAction* action, const std::string& name);
	void addActionList(CCArray* actionList ,const std::string& name);
	void addActionMap(CCDictionary* actionMap,const std::string& name);
	void addAnimation(CCObject* animation ,const std::string& name);
	void removeAnimationNamed(const std::string& name);

	static CCArray* eightDirectionActionListWithFile(const char* file ,int frameCount ,CCSize frameSize ,float delay);
	static CCArray* eightDirectionActionListWithDir(const char* file ,int frameCount ,CCSize frameSize ,float delay);
protected:
	CCDictionary* m_animations;
};

NS_CC_END

#endif // __AnimationComponent_H__
