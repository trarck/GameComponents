#ifndef __MoveComponent_H__
#define __MoveComponent_H__

#include "cocos2d.h"
#include "Component.h"
NS_CC_BEGIN

typedef enum  {
	MoveStop=0,
	MoveStart,
	MoveWillStop,
	MoveContinue,
} MoveState;

class MoveComponent : public Component{

public:

	bool initWithSpeed(float speed);

	CCPoint movingCoordinate();

	void preparePath();

	void calcDirection();
	void setDirection(float dirX ,float dirY);
	void setDirection(CCPoint dir);

	void moveWithDirection(float dirX ,float dirY);
	void moveWithDirection(CCPoint dir);
	void moveWithPaths(CCArray* paths);
	void moveWithPaths(CCArray* paths, int fromIndex);

	bool beforeMove();
	bool beforeMovePath();
	void startMove();
	void continueMoveWithPaths(bool *paths);
	void continueMoveWithDirection(CCPoint dir);
	void stopMove();
	void updateDirection(ccTime delta);
	void updatePath(ccTime delta);

	void updateMoveAnimation();
	void didMoveStop();
	void didHit(CCPoint location);

	float getSpeed();
	void setSpeed(float speed);

	int getPathIndex();
	void setPathIndex(int pathIndex);

	CCArray* getCurrentPaths();
	void setCurrentPaths(CCArray* currentPaths);

	CCArray* getNextPaths();
	void setNextPaths(CCArray* nextPaths);

	MoveState getMoveState();
	void setMoveState(MoveState moveState);

	CCPoint getDirection();
	void setDirection(CCPoint direction);

	CCPoint getTo();
	void setTo(CCPoint to);

protected:
	//移动相关
	int pathIndex_;
	float speed_;
	float directionX_,directionY_;//float 可以使用CCPoint.
	CCPoint direction_;
	CCPoint to_;
	CCPoint nextDirection_;
	CCPoint lastDirection_;
	
	int fromIndex_;
	CCArray *currentPaths_;
	CCArray *nextPaths_;
	BOOL moving_;
	BOOL inStep;
	MoveState moveState_;
	
	SEL updateStep_;
}

NS_CC_END

#endif //__MoveComponent_H__
