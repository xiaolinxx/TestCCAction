#include "MyTouchLayer.h"
#include "cocos2d.h"
#include "AnimationLayer.h"
#include "MyTiledMapLayer.h"
USING_NS_CC;

CCScene* MyTouchLayer::scene(){
	CCScene* scene=CCScene::create();
	MyTouchLayer* layer=MyTouchLayer::create();
	scene->addChild(layer);
	return scene;
}
bool MyTouchLayer::init(){
	if(!CCLayer::init()){
		return false;
	}

	//让当前层接受触摸
	this->setTouchEnabled(true);
	//注册 自动调用该对象的registerWithTouchDispatcher()方法

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	CCMenuItemFont* item1 = CCMenuItemFont::create("touch1", this, menu_selector(MyTouchLayer::action51));
	CCMenuItemFont* item2 = CCMenuItemFont::create("touch2", this, menu_selector(MyTouchLayer::action52));
	CCMenuItemFont* item3 = CCMenuItemFont::create("touch3", this, menu_selector(MyTouchLayer::action53));
	CCMenuItemFont* item4 = CCMenuItemFont::create("touch4", this, menu_selector(MyTouchLayer::action54));
	CCMenu* menu = CCMenu::create(item1,item2,item3,item4,NULL);
	menu->alignItemsVertically(); 
	menu->setPosition(ccp(winSize.width-50,200));
	this->addChild(menu);


	CCMenuItemFont* startItem=CCMenuItemFont::create("previous",this,menu_selector(MyTouchLayer::previous));
	CCMenuItemFont* nextItem=CCMenuItemFont::create("next",this,menu_selector(MyTouchLayer::next));
	CCMenu* prevMenu=CCMenu::create(startItem,nextItem,NULL);
	prevMenu->setPosition(ccp(winSize.width-400,200));
	prevMenu->alignItemsVertically();
	this->addChild(prevMenu);

	CCSprite* sprite=CCSprite::create("grossini_dance_01.png");
	this->addChild(sprite,0,0);
	sprite->setPosition(ccp(winSize.width/2,winSize.height/2));


	return true;
}

void MyTouchLayer::registerWithTouchDispatcher(){
	CCDirector* diretor=CCDirector::sharedDirector();
	//添加单点触摸代理 三个参数说明，实现触摸的对象，优先级数值越大，优先级越低;是否吞噬，吞噬的作用就是优先级高的触摸事件不往下传。
	//注意：优先级可以为负数
	//注意：CCMenu的优先级是-128
	diretor->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool MyTouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	//注意，CCPoint是屏幕坐标系，不是OpenGl坐标系，屏幕坐标系原点是在左上角
	//所以需要转换成OpenGL坐标
	//cocos2d里面是没有getLocation()封装方法的，所以必须要进行转换
// 	CCPoint touchPoint=pTouch->getLocationInView();
// 	touchPoint=CCDirector::sharedDirector()->convertToGL(touchPoint);

	CCPoint touchPoint=pTouch->getLocation();

	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	//sprite->setPosition(touchPoint);
	//注意：如果返回false，后面的touchend ，touchmoved都不会去实现，所以，这里适用于对触摸区域判断，是否符合要求。

	//判断触摸是否在精灵上，如果不在精灵上，就不去拖拽
	CCRect rect=sprite->boundingBox();//返回节点大小
	if(rect.containsPoint(touchPoint)){//rect不是对象，用.调用方法
		return true;
	}
	return false;
}

void MyTouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){

	CCLOG("this ccTouchMoved");
	//得到执行该方法之前手指位置的坐标
	CCPoint point0=pTouch->getPreviousLocation();
	CCPoint touchPoint=pTouch->getLocation();
	//两个坐标做减法，得到v2指向v1的向量
	CCPoint movePoint=ccpSub(touchPoint,point0);
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	sprite->setPosition(ccpAdd(sprite->getPosition(),movePoint));
}

void MyTouchLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	CCLOG("this ccTouchEnded");
}
void MyTouchLayer::action51(CCObject* sender){
	CCLOG("this action51");
}

void MyTouchLayer::action52(CCObject* sender){
	CCLOG("this action52");
}

void MyTouchLayer::action53(CCObject* sender){
	CCLOG("this action53");
}

void MyTouchLayer::action54(CCObject* sender){
	CCLOG("this action54");
}

void MyTouchLayer::previous(CCObject* sender){
	CCDirector::sharedDirector()->replaceScene(AnimationLayer::scene());
	CCLOG("this previous");
}
void MyTouchLayer::next(CCObject* sender){
	CCDirector::sharedDirector()->replaceScene(MyTiledMapLayer::scene());
	CCLOG("this next");
}



MyTouchLayer::MyTouchLayer(void)
{
}


MyTouchLayer::~MyTouchLayer(void)
{
}
