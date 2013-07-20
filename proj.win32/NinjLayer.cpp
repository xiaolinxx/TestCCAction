#include "NinjLayer.h"
#include "cocos2d.h"
#include "MyTiledMapLayer.h"
#include "Monster.h"
#include "MyData.h"
#define HERO 0
USING_NS_CC;

CCScene* NinjLayer::scene(){
	CCScene* scene=CCScene::create();
	NinjLayer* layer=NinjLayer::create();
	scene->addChild(layer);
	return scene;
}

bool NinjLayer::init(){
	if(!CCLayerColor::initWithColor(ccc4(255,255,255,255))){
		return false;
	}

	data=MyData::shareMyData();
	//初始化全局变量
	 winSize=CCDirector::sharedDirector()->getWinSize();
	 //开启触摸
	 this->setTouchEnabled(true);
	CCSprite* hero=CCSprite::create("Player.png");
	

	this->addChild(hero,0,HERO);
	hero->setPosition(ccp(hero->getContentSize().width/2,winSize.height/2));

	this->schedule(schedule_selector(NinjLayer::addMonster),0.8f);
// 	CCMenuItemFont* startItem=CCMenuItemFont::create("previous",this,menu_selector(NinjLayer::previous));
// 	CCMenuItemFont* nextItem=CCMenuItemFont::create("next",this,menu_selector(NinjLayer::next));
// 	CCMenu* prevMenu=CCMenu::create(startItem,nextItem,NULL);
// 	prevMenu->setPosition(ccp(winSize.width-400,200));
// 	prevMenu->alignItemsVertically();
// 	this->addChild(prevMenu);
	return true;
}

void NinjLayer::addMonster(float dt){
	Monster* monster=Monster::create();
	this->addChild(monster);
	//取值a~b之间，ran*(b-a)+a a=m.h/2 b=w.h-m.h/2
	float y=CCRANDOM_0_1()*(winSize.height - monster->getContentSize().height)+monster->getContentSize().height/2;
	monster->setPosition(ccp(winSize.width,y));
}


void NinjLayer::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool NinjLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	CCPoint touchPoint=pTouch->getLocation();
	//发射炮弹
	this->fire(touchPoint);
	return true;
}

void NinjLayer::fire(CCPoint touPoint){
	CCSprite* hero=(CCSprite*)this->getChildByTag(HERO);
	CCSprite* bullet=CCSprite::create("Projectile.png");
	this->addChild(bullet);

	data->bulletArray->addObject(bullet);
	bullet->setPosition(hero->getPosition());

	//矢量 方向从v2到v1，从hero到触摸点 ，但是长度可能很短，比如ccp(1,0)
	CCPoint approchPoint=ccpSub(touPoint,bullet->getPosition());
	CCPoint movePoint=ccpMult(approchPoint,winSize.width);//不改变方向，增加矢量的长度

	//运动持续时间，应该是路程除以速度
	float s=ccpLength(movePoint);
	float time=s/180 ;//速度是恒定的
	CCMoveBy* moveby=CCMoveBy::create(time,movePoint);
	CCRotateBy* reotateBy=CCRotateBy::create(1.0f,360);
	
	CCRepeat* repeatF=CCRepeat::create(reotateBy,-1);

	CCFiniteTimeAction* spawn=CCSpawn::create(moveby,repeatF,NULL);
	//CCCallFuncN* callfun=CCCallFuncN::create(this,callfuncN_selector(NinjLayer::remove));
	//CCFiniteTimeAction* sqaction=CCSequence::create(repeatF,callfun,NULL);
	bullet->runAction(spawn);
}

void NinjLayer::remove(CCNode* sender){
	//这里sender就是子弹
	data->bulletArray->removeObject(sender);
	sender->removeFromParentAndCleanup(true);

}
void NinjLayer::previous(CCObject* sender){
	CCDirector::sharedDirector()->replaceScene(MyTiledMapLayer::scene());
	CCLOG("this previous");
}
void NinjLayer::next(CCObject* sender){
	CCLOG("this next");

}
NinjLayer::NinjLayer(void)
{
}


NinjLayer::~NinjLayer(void)
{
}
