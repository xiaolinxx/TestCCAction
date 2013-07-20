#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Action1Layer:public CCLayer
{
public:
	static CCScene* scene();
	bool init();
	void move(CCObject* sender);
	void go1(CCObject* sender);
	void go2(CCObject* sender);
	void go3(CCObject* sender);
	void go4(CCObject* sender);
	void go5(CCObject* sender);
	void go6(CCObject* sender);
	void go7(CCObject* sender);
	CREATE_FUNC(Action1Layer);
	Action1Layer(void);
	~Action1Layer(void);
};

