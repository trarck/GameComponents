#ifndef __AnimationComponent_H__
#define __AnimationComponent_H__

#include "cocos2d.h"

NS_CC_BEGIN

class AnimationComponent : public Component
{
public:
	AnimationComponent();
	~AnimationComponent();
	//extend from parent
	virtual bool init();  
	virtual CCObject* getOwner();
	virtual setOwner(CCObject* owner);
	//for myself
	CCAction* moveAction();
	void moveActoin(CCAction* action);

	CCArray* actionArray();
	void actionArray(CCArray* actionArray);

	CCDictionary* animations();
	void animations(CCDictionary* animations);

	bool initWithConfigFile(CCString*  file);

	CCObject* animationForName(CCString* name);
	CCAction* actionForName(CCString* name);
	CCAction* actionForName(CCString* name ,int index);
	CCAction* actionForName(CCString* name ,CCString* key);

	CCArray* actionListForName(CCString* name);
	CCDictionary* actionMapForName(CCString* name);

	void addAction(CCAction* action, CCString* name);
	void addActionList(CCArray* actionList ,CCString* name);
	void addActionMap(CCDictionary* actionMap,CCString* name);
	void addAnimation(CCObject* animation ,CCString* name);
	void removeAnimationNamed(CCString* name);

	static CCArray* eightDirectionActionListWithFile(CCString* file ,int frameCount ,CGSize frameSize ,float delay);
	static CCArray* eightDirectionActionListWithDir(CCString* file ,int frameCount ,CGSize frameSize ,float delay);
private:
	CCDictionary* m_animations;
};

NS_CC_END

#endif // __AnimationComponent_H__
