#include "Action2Layer.h"
#include "cocos2d.h"
#include "Action1Layer.h"
#include "ActionFunCallLayer.h"
USING_NS_CC;

CCScene* Action2Layer::scene(){
	CCScene* scene=CCScene::create();
	Action2Layer* layer=Action2Layer::create();
	scene->addChild(layer);
	return scene;
}

bool Action2Layer::init(){
	if(!CCLayer::init()){
		return false;
	}
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();


	CCMenuItemFont* item1 = CCMenuItemFont::create("go21", this, menu_selector(Action2Layer::action21));
	CCMenuItemFont* item2 = CCMenuItemFont::create("go22", this, menu_selector(Action2Layer::action22));
	CCMenuItemFont* item3 = CCMenuItemFont::create("go23", this, menu_selector(Action2Layer::action23));
	CCMenuItemFont* item4 = CCMenuItemFont::create("go24", this, menu_selector(Action2Layer::action24));
	CCMenu* menu = CCMenu::create(item1,item2,item3,item4,NULL);
	menu->alignItemsVertically(); 
	menu->setPosition(ccp(winSize.width-50,200));
	this->addChild(menu);


	CCMenuItemFont* startItem=CCMenuItemFont::create("previous",this,menu_selector(Action2Layer::previous));
	CCMenuItemFont* nextItem=CCMenuItemFont::create("next",this,menu_selector(Action2Layer::next));
	CCMenu* prevMenu=CCMenu::create(startItem,nextItem,NULL);
	prevMenu->alignItemsVertically();
	prevMenu->setPosition(ccp(winSize.width-400,200));
	this->addChild(prevMenu);

	CCSprite* sprite=CCSprite::create("Target.png");
	this->addChild(sprite,0,0);
	sprite->setPosition(ccp(winSize.width/2,winSize.height/2));

	CCLabelTTF* label=CCLabelTTF::create("its label","Arial",20);
	label->setPosition(ccp(240,180));
	this->addChild(label);

	return true;
}
//±ßÒÆ¶¯±ßÐý×ª
void Action2Layer::action21(CCObject* sender)
{
	CCLOG("%s","its action21");
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	
	CCMoveTo* moveto=CCMoveTo::create(2.0f,ccp(480,320));
	CCRotateBy* rotateby=CCRotateBy::create(2.0f,360);

	CCFiniteTimeAction* spawn=CCSpawn::create(moveto,rotateby,NULL);
	
	CCRepeat* re=CCRepeat::create(spawn,2);

	CCSpeed* speed=CCSpeed::create(re,2.0f);
	sprite->runAction(speed);
}

void Action2Layer::action22(CCObject* sender)
{
	

	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);

	CCMoveTo* moveto=CCMoveTo::create(2.0f,ccp(100,100));
	CCRotateBy* rotateby=CCRotateBy::create(2.0f,360);
	CCFiniteTimeAction* spawn=CCSpawn::create(moveto,rotateby,NULL);

	sprite->runAction(spawn);

	


	CCFollow* follow=CCFollow::create(sprite);

	this->runAction(follow);
	CCLOG("%s","its move function");
}
void Action2Layer::action23(CCObject* sender)

{
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	
	CCMoveTo* moveto=CCMoveTo::create(2.0f,ccp(480,320));
	CCRotateBy* rotateby=CCRotateBy::create(2.0f,360);

	CCFiniteTimeAction* spawn=CCSpawn::create(moveto,rotateby,NULL);
	
	CCRepeat* re=CCRepeat::create(spawn,2);

	CCSpeed* speed=CCSpeed::create(re,2.0f);
	speed->setTag(1);
	sprite->runAction(speed);


	this->schedule(schedule_selector(Action2Layer::doTimer),0.5f);
	CCLOG("%s","action23");
}
void Action2Layer::action24(CCObject* sender)
{
	CCLOG("%s","its move function");
}

void Action2Layer::doTimer(float ft)
{
	CCNode* node=this->getChildByTag(0);
	CCAction* action=node->getActionByTag(1);
	if(action!=NULL){
		CCSpeed* speed=(CCSpeed*)action;
		speed->setSpeed(CCRANDOM_0_1()*2);
	}
	

}

void Action2Layer::previous(CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(Action1Layer::scene());
}

void Action2Layer::next(CCObject* sender)
{
	CCDirector::sharedDirector()->replaceScene(ActionFunCallLayer::scene());
}

Action2Layer::Action2Layer(void)
{
	
}


Action2Layer::~Action2Layer(void)
{
}
