#pragma once
#include "cocos2d.h"
#include "MyData.h"
USING_NS_CC;
class Monster:public CCSprite
{
public:
	MyData* data;
	CCSize winSize;
public:
	bool init();
	CREATE_FUNC(Monster);
	void move(float dt);
	void remove(float dt);
	void update(float dt);
	Monster(void);
	~Monster(void);
};

