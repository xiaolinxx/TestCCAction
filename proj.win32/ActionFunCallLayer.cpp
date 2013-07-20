#include "ActionFunCallLayer.h"
#include "cocos2d.h"
#include "Action2Layer.h"
#include "AnimationLayer.h"
USING_NS_CC;

CCScene* ActionFunCallLayer::scene(){
	CCScene* scene=CCScene::create();
	ActionFunCallLayer* layer=ActionFunCallLayer::create();
	scene->addChild(layer);
	return scene;

}

bool ActionFunCallLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();


	CCMenuItemFont* item1 = CCMenuItemFont::create("CCCallFunc", this, menu_selector(ActionFunCallLayer::action31));
	CCMenuItemFont* item2 = CCMenuItemFont::create("CCCallFuncN", this, menu_selector(ActionFunCallLayer::action32));
	CCMenuItemFont* item3 = CCMenuItemFont::create("CCCallFuncND", this, menu_selector(ActionFunCallLayer::action33));
	CCMenuItemFont* item4 = CCMenuItemFont::create("CCCallFuncO", this, menu_selector(ActionFunCallLayer::action34));
	CCMenu* menu = CCMenu::create(item1,item2,item3,item4,NULL);
	menu->alignItemsVertically(); 
	menu->setPosition(ccp(winSize.width-50,200));
	this->addChild(menu);


	CCMenuItemFont* startItem=CCMenuItemFont::create("previous",this,menu_selector(ActionFunCallLayer::previous));
	CCMenuItemFont* nextItem=CCMenuItemFont::create("next",this,menu_selector(ActionFunCallLayer::next));
	CCMenu* prevMenu=CCMenu::create(startItem,nextItem,NULL);
	prevMenu->setPosition(ccp(winSize.width-400,200));
	prevMenu->alignItemsVertically();
	this->addChild(prevMenu);

	CCSprite* sprite=CCSprite::create("Target.png");
	this->addChild(sprite,0,0);
	sprite->setPosition(ccp(winSize.width/2,winSize.height/2));

	return true;
}

void ActionFunCallLayer::action31(CCObject* sender){
	CCLOG("this action31");
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);

	CCMoveTo* moveto=CCMoveTo::create(2.0f,ccp(480,320));
	CCRotateBy* rotateby=CCRotateBy::create(2.0f,360);

	CCFiniteTimeAction* spawn=CCSpawn::create(moveto,rotateby,NULL);

	CCRepeat* re=CCRepeat::create(spawn,2);
	
	CCSpeed* speed=CCSpeed::create(re,2.0f);

	
	
	//CCCallFunc
	CCCallFunc* func=CCCallFunc::create(this,callfunc_selector(ActionFunCallLayer::call1));
	//这里要注意，CCSequence的create方法不接受speedAction，
	CCFiniteTimeAction* sequence=CCSequence::create(re,func,NULL);

	sprite->runAction(sequence);
}

void ActionFunCallLayer::action32(CCObject* sender){
	CCLOG("this action32");
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);

	CCMoveTo* moveto=CCMoveTo::create(2.0f,ccp(480,320));
	CCRotateBy* rotateby=CCRotateBy::create(2.0f,360);

	CCFiniteTimeAction* spawn=CCSpawn::create(moveto,rotateby,NULL);

	CCRepeat* re=CCRepeat::create(spawn,2);

	CCSpeed* speed=CCSpeed::create(re,2.0f);



	//CCCallFunc
	//CCCallFunc* func=CCCallFunc::create(this,callfunc_selector(ActionFunCallLayer::call1));
	CCCallFuncN* funcN=CCCallFuncN::create(this,callfuncN_selector(ActionFunCallLayer::call2));
	//这里要注意，CCSequence的create方法不接受speedAction，
	CCFiniteTimeAction* sequence=CCSequence::create(re,funcN,NULL);

	sprite->runAction(sequence);
}

void ActionFunCallLayer::action33(CCObject* sender){
	CCLOG("this action33");
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);

	CCMoveTo* moveto=CCMoveTo::create(2.0f,ccp(480,320));
	CCRotateBy* rotateby=CCRotateBy::create(2.0f,360);

	CCFiniteTimeAction* spawn=CCSpawn::create(moveto,rotateby,NULL);

	CCRepeat* re=CCRepeat::create(spawn,2);

	CCSpeed* speed=CCSpeed::create(re,2.0f);



	//CCCallFunc
	//CCCallFunc* func=CCCallFunc::create(this,callfunc_selector(ActionFunCallLayer::call1));
	//CCCallFuncN* funcN=CCCallFuncN::create(this,callfuncN_selector(ActionFunCallLayer::call2));
	int num=10;
	CCCallFuncND* funcnd=CCCallFuncND::create(this,callfuncND_selector(ActionFunCallLayer::call3),(void*)num);
	//这里要注意，CCSequence的create方法不接受speedAction，
	CCFiniteTimeAction* sequence=CCSequence::create(re,funcnd,NULL);

	sprite->runAction(sequence);
}

void ActionFunCallLayer::action34(CCObject* sender){
	CCLOG("this action34");
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);

	CCMoveTo* moveto=CCMoveTo::create(2.0f,ccp(480,320));
	CCRotateBy* rotateby=CCRotateBy::create(2.0f,360);

	CCFiniteTimeAction* spawn=CCSpawn::create(moveto,rotateby,NULL);

	CCRepeat* re=CCRepeat::create(spawn,2);

	CCSpeed* speed=CCSpeed::create(re,2.0f);

	CCLabelTTF* label=CCLabelTTF::create("hellococos","Arial",30);
	this->addChild(label);
	label->setPosition(ccp(240,280));

	//CCCallFunc
	//CCCallFunc* func=CCCallFunc::create(this,callfunc_selector(ActionFunCallLayer::call1));
	//CCCallFuncN* funcN=CCCallFuncN::create(this,callfuncN_selector(ActionFunCallLayer::call2));
	int num=10;
	CCCallFuncO* funco=CCCallFuncO::create(this,callfuncO_selector(ActionFunCallLayer::call4),label);
	//这里要注意，CCSequence的create方法不接受speedAction，
	CCFiniteTimeAction* sequence=CCSequence::create(re,funco,NULL);

	sprite->runAction(sequence);
}

void ActionFunCallLayer::previous(CCObject* sender){
	CCDirector::sharedDirector()->replaceScene(Action2Layer::scene());
	CCLOG("this previous");
}

void ActionFunCallLayer::next(CCObject* sender){
	CCDirector::sharedDirector()->replaceScene(AnimationLayer::scene());
	
	CCLOG("this next");
}

void ActionFunCallLayer::call1(){
	CCLOG("this call1");
}
void ActionFunCallLayer::call2(CCNode* node){
	CCSprite* sprite=(CCSprite*)node;
	sprite->removeFromParentAndCleanup(true);
	//这是讲精灵从层里面移除，一样可以达到这个效果，true参数表示移除的时候同时移除节点的动作。
	//this->removeChild(sprite,true);
	CCLOG("this call2");
}

void ActionFunCallLayer::call3(CCNode* node,void *data){
	int num=(int)data;
	CCSprite* sprite=(CCSprite*)node;
	sprite->removeFromParentAndCleanup(true);
	//这是讲精灵从层里面移除，一样可以达到这个效果，true参数表示移除的时候同时移除节点的动作。
	//this->removeChild(sprite,true);
	CCLOG("this call3,data:%i",num);
}
void ActionFunCallLayer::call4(CCObject* data){
	CCLabelTTF* label=(CCLabelTTF*)data;
	label->setColor(ccRED);
	CCLOG("this call4,data:%s",label->getString());

}
ActionFunCallLayer::ActionFunCallLayer(void)
{
}


ActionFunCallLayer::~ActionFunCallLayer(void)
{
}
