#pragma once
#include "cocos2d.h"
USING_NS_CC;
class ActionFunCallLayer:public CCLayer
{
public:
	static CCScene* scene();
	bool init();
	CREATE_FUNC(ActionFunCallLayer);
	void action31(CCObject* sender);
	void action32(CCObject* sender);
	void action33(CCObject* sender);
	void action34(CCObject* sender);
	void previous(CCObject* sender);
	void next(CCObject* sender);
	void call1();
	void call2(CCNode* node);
	void call3(CCNode* node,void* data);
	void call4(CCObject* obj); 
	ActionFunCallLayer(void);
	~ActionFunCallLayer(void);
};

