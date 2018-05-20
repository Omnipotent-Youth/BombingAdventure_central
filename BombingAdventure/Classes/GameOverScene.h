#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
	/* create game over scene */
	static cocos2d::Scene* createScene();

	/* initializer */
	virtual bool init();

	/* menu call back function */
	virtual void menuCallBack(cocos2d::Ref* pSender);

	CREATE_FUNC(GameOverScene);
};

#endif //_GAME_OVER_SCENE_H_
