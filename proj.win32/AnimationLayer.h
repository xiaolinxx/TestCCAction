#pragma once
#include "cocos2d.h"
USING_NS_CC;
class AnimationLayer:public CCLayer
{
public:
	static CCScene* scene();
	bool init();
	CREATE_FUNC(AnimationLayer);
	void action41(CCObject* sender);
	void action42(CCObject* sender);
	void action43(CCObject* sender);
	void action44(CCObject* sender);
	void previous(CCObject* sender);
	void next(CCObject* sender);
	AnimationLayer(void);
	~AnimationLayer(void);
};

