#ifndef RULESSCENE_H
#define RULESSCENE_H

#include "cocos2d.h"

class RulesScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void menuPopBack(cocos2d::Ref* pSender);

	CREATE_FUNC(RulesScene);
};


#endif
