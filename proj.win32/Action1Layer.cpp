#include "Action1Layer.h"
#include "Action2Layer.h"
#include "HelloWorldScene.h"
USING_NS_CC;
CCScene* Action1Layer::scene(){
	CCScene* scene=CCScene::create();
	Action1Layer* layer=Action1Layer::create();
	scene->addChild(layer);
	return scene;
}
bool Action1Layer::init(){
	if(!CCLayer::init()){
		return false;
	}
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	//显示文本信息
// 	CCLabelTTF* labelttf=CCLabelTTF::create("start","Excellentia",25,CCSize(100,100),kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
// 	this->addChild(labelttf);
// 	this->setPosition(winSize.width/2,winSize.height/2);
// 
// 	const char* str=labelttf->getString();
// 	CCLOG("str=%s",str);

	CCMenuItemFont* item1 = CCMenuItemFont::create("CCPlace", this, menu_selector(Action1Layer::go1));
	CCMenuItemFont* item2 = CCMenuItemFont::create("CCFlipX", this, menu_selector(Action1Layer::go2));
	CCMenuItemFont* item3 = CCMenuItemFont::create("moveto", this, menu_selector(Action1Layer::go3));
	CCMenuItemFont* item4 = CCMenuItemFont::create("moveby", this, menu_selector(Action1Layer::go4));
	CCMenuItemFont* item5 = CCMenuItemFont::create("rotateby", this, menu_selector(Action1Layer::go5));
	CCMenuItemFont* item6 = CCMenuItemFont::create("repeat", this, menu_selector(Action1Layer::go6));
	CCMenuItemFont* item7 = CCMenuItemFont::create("jumpby", this, menu_selector(Action1Layer::go7));
	CCMenu* menu = CCMenu::create(item1,item2,item3,item4,item5,item6,item7,NULL);
	menu->alignItemsVertically(); 
	menu->setPosition(ccp(winSize.width-50,200));
	this->addChild(menu);



	CCMenuItemFont* startItem=CCMenuItemFont::create("start");
	CCMenuItemFont* stopItem=CCMenuItemFont::create("stop");
	CCMenuItemToggle* toggle=CCMenuItemToggle::createWithTarget(this,menu_selector(Action1Layer::move),startItem,stopItem,NULL);
	CCMenu* toggleMenu=CCMenu::create(toggle,NULL);
	toggleMenu->setPosition(ccp(winSize.width-400,200)); 
	this->addChild(toggleMenu);

	CCSprite* sprite=CCSprite::create("Target.png");
	this->addChild(sprite,0,0);
	sprite->setPosition(ccp(winSize.width/2,winSize.height/2));
	return true;
}
void Action1Layer::move(CCObject* sender)
{
	CCMenuItemToggle* toggle=(CCMenuItemToggle*)sender;
	if(toggle->getSelectedIndex()==0){

		CCLOG("its start");
	}else if(toggle->getSelectedIndex()==1){
		CCDirector::sharedDirector()->replaceScene(Action2Layer::scene());
	}
}

void Action1Layer::go1(CCObject* sender)
{
	
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	
	CCPlace* action=CCPlace::create(ccp(100,100));
	sprite->runAction(action);

// 	CCMenuItemToggle* toggle=(CCMenuItemToggle*)sender;
// 	if(toggle->getSelectedIndex()==0){
// 		
// 		CCLOG("its start");
// 	}else if(toggle->getSelectedIndex()==1){
// 		CCDirector::sharedDirector()->replaceScene(Action2Layer::scene());
// 		CCTransitionScene* reScene=CCTransitionFade::create(2.0f,HelloWorld::scene(),ccc3(25,200,200));
// 		CCDirector::sharedDirector()->replaceScene(reScene);

// 		CCTransitionScene* reScene=CCTransitionFade::create(2.0f,HelloWorld::scene(),ccRED);
// 		CCDirector::sharedDirector()->pushScene(reScene);
		// 要返回改场景，只需要在对应场景中添加动作，写该方法：
	    //CCDirector::sharedDirector()->popScene();
// 		CCLog("its stop");
// 	}
}
void Action1Layer::go2(CCObject* sender){
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);

	CCFlipX* action=CCFlipX::create(true);
	sprite->runAction(action);
}

void Action1Layer::go3(CCObject* sender){
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);

	CCMoveTo* moveto=CCMoveTo::create(2.0f,ccp(480,320));
	sprite->runAction(moveto);

}

void Action1Layer::go4(CCObject* sender){
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);

	CCMoveBy* move=CCMoveBy::create(1.0f,ccp(50,50));
	sprite->runAction(move);

}

void Action1Layer::go5(CCObject* sender){
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);

	CCRotateBy* rotateby=CCRotateBy::create(2.0f,360);
	sprite->runAction(rotateby);

}

void Action1Layer::go6(CCObject* sender){
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);

	CCRotateBy* rotateby=CCRotateBy::create(2.0f,360);
	CCRepeat* repeat=CCRepeat::create(rotateby,3);
	sprite->runAction(repeat);

}

void Action1Layer::go7(CCObject* sender){
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	//                                   向x往右跳200，高度30，跳3次
	CCJumpBy* jump=CCJumpBy::create(2.0f,ccp(200,0),30,3);
	//CCRepeat* repeat=CCRepeat::create(rotateby,3);
	sprite->runAction(jump);

}

Action1Layer::Action1Layer(void)
{
}


Action1Layer::~Action1Layer(void)
{
}
