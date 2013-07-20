#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MyTouchLayer:public CCLayer
{
public:
	static CCScene* scene();
	bool init();
	CREATE_FUNC(MyTouchLayer);
	void registerWithTouchDispatcher();
	bool MyTouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void MyTouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void MyTouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void action51(CCObject* sender);
	void action52(CCObject* sender);
	void action53(CCObject* sender);
	void action54(CCObject* sender);
	void previous(CCObject* sender);
	void next(CCObject* sender);
	MyTouchLayer(void);
	~MyTouchLayer(void);
};

