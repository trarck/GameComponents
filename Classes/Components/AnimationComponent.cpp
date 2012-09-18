#include "AnimationComponent.h"


NS_CC_BEGIN

AnimationComponent::AnimationComponent()
:m_animations(NULL)
{
	CCLOG("AnimationComponent create");
}

AnimationComponent::~AnimationComponent()
{
	CCLOG("AnimationComponent destroy");
	CC_SAFE_RELEASE(m_animations);
}


bool AnimationComponent::init()
{
	m_animations=new CCDictionary();
	return true;
}

bool initWithConfigFile(const std::string& file)
{
	init();
	return true;
}

-(id) initWithConfigData(CCDictionary* data)
{
	init();
	return true;
}

CCObject* animationForName(const std::string& name)
{
	return m_animations->objectForKey(name);
}

CCAction* actionForName(const std::string& name)
{
	return m_animations->objectForKey(name);
}

CCAction* actionForName(const std::string& name ,int index)
{
	return ((CCArray*)(m_animations->objectForKey(name)))->objectAtIndex(index);
}

CCAction* actionForName(const std::string& name ,const std::string& key)
{
	return ((CCDictionary*)(m_animations->objectForKey(name)))->objectForKey(key);
}

CCArray* actionListForName(const std::string& name)
{
	return (CCArray*)(m_animations->objectForKey(name));
}

CCDictionary* actionMapForName(const std::string& name)
{
	return (CCDictionary*)m_animations->objectForKey(name);
}

void addAnimation(CCObject* animation,const std::string&  name)
{
	m_animations->setObject(animation ,name);
}

void addAction(CCAction* action ,const std::string& name)
{
	m_animations->setObject(action ,name);
}

void addActionList(CCArray* actionList ,const std::string& name)
{
	m_animations->setObject(actionList ,name);
}

void addActionMap(CCDictionary* actionMap ,const std::string& name)
{
	m_animations->setObject(actionMap ,name);
}

void removeAnimationNamed(const std::string& name)
{
	m_animations->removeObjectForKey(name);
}

CCArray* eightDirectionActionListWithFile(const char* file ,int frameCount ,CCSize frameSize ,float delay)
{
	CCTexture2D *texture=CCTextureCache::sharedTextureCache()->addImage(file);
	
	CCArray* actions=new CCArray();
	actions->initWithCapacity(8);
	//move action
	for (int i=0; i<8; i++) {
		CCArray* animFrames=new CCArray();
		animFrames->initWithCapacity(8);
		for (int j=0; j<frameCount; j++) {
			CCSpriteFrame *frame=CCSpriteFrame::createWithTexture(texture ,CCRectMake(j*frameSize.width, i*frameSize.height, frameSize.width, frameSize.height));
			animFrames->addObject(frame);
		}
		CCAnimation *animation=CCAnimation::createWithSpriteFrames(animFrames,delay);
		CCAnimate *animate= CCAnimate::create(animation);
		CCSequence *seq=CCSequence::create(animate,NULL);
		actions->addObject(CCRepeatForever::create(seq));
		animFrames->release();
	}
	return actions;
}

CCArray* eightDirectionActionListWithDir(const char* dir ,int frameCount ,CCSize frameSize ,float delay)
{
	CCArray *actions=new CCArray();
	actions->initWithCapacity(8);
	
	//move action
	char str[255] = {0};
	for (int i=0; i<8; i++) {
		CCArray* animFrames=new CCArray();
		animFrames->initWithCapacity(frameCount);
		for (int j=0; j<frameCount; j++) {
			sprintf(str,"%s/%02d%03d.png",dir,i,j);
			animation->addSpriteFrameWithFileName(str);
		}
		//animation.delay=delay;
		CCAnimate *animate=[CCAnimate actionWithDuration:frameCount*delay animation:animation restoreOriginalFrame:YES];
		CCSequence *seq=[CCSequence actions:animate,nil];
		[actions addObject:[CCRepeatForever actionWithAction:seq]];
	}
	return actions;
}


NS_CC_END
