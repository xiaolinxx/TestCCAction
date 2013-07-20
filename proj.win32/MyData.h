#pragma once
#include "cocos2d.h"
USING_NS_CC;
class MyData
{
public:
	CCArray* bulletArray;
public:
	static MyData* shareMyData();
	void init();
	MyData(void);
	~MyData(void);
};

