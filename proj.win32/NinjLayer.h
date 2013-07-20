#pragma once
#include "cocos2d.h"
#include "MyData.h"
USING_NS_CC;
class NinjLayer:public CCLayerColor
{
public:
	CCSize winSize;
	MyData* data;
public:
	static CCScene* scene();
	bool init();
	CREATE_FUNC(NinjLayer);
	void addMonster(float dt);
	void registerWithTouchDispatcher();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void fire(CCPoint touPoint);
	void remove(CCNode* obj);
	void previous(CCObject* sender);
	void next(CCObject* sender);
	NinjLayer(void);
	~NinjLayer(void);
};

