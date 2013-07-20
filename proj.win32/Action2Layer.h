#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Action2Layer:public CCLayer
{
public:
	static CCScene* scene();
	bool init();
	CREATE_FUNC(Action2Layer);
	void action21(CCObject* sender);
	void action22(CCObject* sender);
	void action23(CCObject* sender);
	void action24(CCObject* sender);
	void doTimer(float ft);
	void previous(CCObject* sender);
	void next(CCObject* sender);
	Action2Layer(void);
	~Action2Layer(void);
};

