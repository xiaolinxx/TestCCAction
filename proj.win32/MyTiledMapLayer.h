#pragma once
#include "cocos2d.h"
#include <iostream>  
#include <string>  
#include <vector>  
using namespace std; 
USING_NS_CC;
class MyTiledMapLayer:public CCLayer
{
public:
	CCTMXTiledMap* map;
	CCTMXLayer* mapLayer;
	CCTMXObjectGroup* objLayer;

public:
	static CCScene* scene();
	bool init();
	CREATE_FUNC(MyTiledMapLayer);
	void action1(CCObject* sender);
	void action2(CCObject* sender);
	void action3(CCObject* sender);
	void action4(CCObject* sender);
	void MyTiledMapLayer::registerWithTouchDispatcher();
	bool MyTiledMapLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void previous(CCObject* sender);
	void next(CCObject* sender);
	vector<string> splitEx(const string& src, string separate_character);
	CCPoint changePointStr2CCPoint(const string& src);
	MyTiledMapLayer(void);
	~MyTiledMapLayer(void);
	CCPoint changeCCPoint2MapPoint( CCPoint touchPoint ) ;

};