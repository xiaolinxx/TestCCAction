#include "AnimationLayer.h"
#include "cocos2d.h"
#include "ActionFunCallLayer.h"
#include "MyTouchLayer.h"
USING_NS_CC;

CCScene* AnimationLayer::scene(){
	CCScene* scene=CCScene::create();
	AnimationLayer* layer=AnimationLayer::create();
	scene->addChild(layer);
	return scene;
}

bool AnimationLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	CCMenuItemFont* item1 = CCMenuItemFont::create("type1", this, menu_selector(AnimationLayer::action41));
	CCMenuItemFont* item2 = CCMenuItemFont::create("type2", this, menu_selector(AnimationLayer::action42));
	CCMenuItemFont* item3 = CCMenuItemFont::create("type3", this, menu_selector(AnimationLayer::action43));
	CCMenuItemFont* item4 = CCMenuItemFont::create("type4", this, menu_selector(AnimationLayer::action44));
	CCMenu* menu = CCMenu::create(item1,item2,item3,item4,NULL);
	menu->alignItemsVertically(); 
	menu->setPosition(ccp(winSize.width-50,200));
	this->addChild(menu);


	CCMenuItemFont* startItem=CCMenuItemFont::create("previous",this,menu_selector(AnimationLayer::previous));
	CCMenuItemFont* nextItem=CCMenuItemFont::create("next",this,menu_selector(AnimationLayer::next));
	CCMenu* prevMenu=CCMenu::create(startItem,nextItem,NULL);
	prevMenu->setPosition(ccp(winSize.width-400,200));
	prevMenu->alignItemsVertically();
	this->addChild(prevMenu);

	CCSprite* sprite=CCSprite::create("grossini_dance_01.png");
	this->addChild(sprite,0,0);
	sprite->setPosition(ccp(winSize.width/2,winSize.height/2));

	
	return true;
}

void AnimationLayer::action41(CCObject* sender){
	CCLOG("this action41");
	//���ַ�ʽ��������Դ��һ�㲻����ô�ã�ֻ����ѧϰ��⶯���á�

	//����ÿ��֡����һ����С�ģ�����CCRect��һ��������
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	CCSize size=sprite->getContentSize();
	CCRect rect=CCRect(0,0,size.width,size.height);

	CCAnimation* animation=CCAnimation::create();
	for(int i=1;i<=14;i++){
 		CCString* fileName=CCString::createWithFormat("grossini_dance_%02d.png",i);
// 		CCSpriteFrame* frame=CCSpriteFrame::create(fileName->getCString(),rect);
// 		animation->addSpriteFrame(frame);
		//����2��ȼ�����һ��
		animation->addSpriteFrameWithFileName(fileName->getCString());
	}
	animation->setDelayPerUnit(0.1f);
	animation->setLoops(-1);//�ظ�ִ��

	CCAnimate* animate=CCAnimate::create(animation);

	sprite->runAction(animate);


}

void AnimationLayer::action42(CCObject* sender){
	CCLOG("this action42");
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	CCTextureCache* textureCache=CCTextureCache::sharedTextureCache();
	CCTexture2D* texture=textureCache->addImage("grossini_dance_atlas.png");

		CCAnimation* animation=CCAnimation::create();
	//ͼƬ����ԭ���������Ͻ�
	for(int i=0;i<5;i++){
		CCRect rect=CCRect(85*i,0,85,121);//85,121��Щ��ֵ��������
// 		CCSpriteFrame* frame=CCSpriteFrame::createWithTexture(texture,rect);
// 		animation->addSpriteFrame(frame);
		animation->addSpriteFrameWithTexture(texture,rect);
	}
	animation->setDelayPerUnit(0.1f);//����֡����ʱ��������ã���Ȼ���Ქ��
	animation->setLoops(-1);//�ظ�ִ��
	CCAnimate* animate=CCAnimate::create(animation);

	sprite->runAction(animate);
	
}

void AnimationLayer::action43(CCObject* sender){
	CCLOG("this action43");
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	CCAnimation* animation=CCAnimation::create();

	CCSpriteFrameCache* frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("grossini.plist");
	for(int i=1;i<15;i++){
		CCString* fileName=CCString::createWithFormat("grossini_dance_%02d.png",i);
		CCSpriteFrame* frame=frameCache->spriteFrameByName(fileName->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.1f);//����֡����ʱ��������ã���Ȼ���Ქ��
	animation->setLoops(-1);//�ظ�ִ��

	CCAnimationCache* animationCache=CCAnimationCache::sharedAnimationCache();
	animationCache->addAnimation(animation,"Z");//���԰Ѷ����洢�����������´ε��á�

	CCAnimate* animate=CCAnimate::create(animationCache->animationByName("Z"));//��������ȥ�Ҵ洢�����Ķ���
	sprite->runAction(animate);
	

	
}

void AnimationLayer::action44(CCObject* sender){
	CCLOG("this action44");
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	CCAnimation* animation=CCAnimation::create();

	CCSpriteFrameCache* frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("type4/grossini.plist");
	frameCache->addSpriteFramesWithFile("type4/grossini_blue.plist");
	frameCache->addSpriteFramesWithFile("type4/grossini_gray.plist");

	CCAnimationCache* animationCache=CCAnimationCache::sharedAnimationCache();
	animationCache->addAnimationsWithFile("type4/animations.plist");

	CCAnimate* animate=CCAnimate::create(animationCache->animationByName("dance_2"));//���������type4/animations.plist�ж���
	sprite->runAction(animate);

}

void AnimationLayer::previous(CCObject* sender){
	CCDirector::sharedDirector()->replaceScene(ActionFunCallLayer::scene());
	CCLOG("this previous");
}
void AnimationLayer::next(CCObject* sender){
	CCLOG("this next");
	CCDirector::sharedDirector()->replaceScene(MyTouchLayer::scene());
}


AnimationLayer::AnimationLayer(void)
{
}


AnimationLayer::~AnimationLayer(void)
{
}
