#include "Monster.h"
#include "cocos2d.h"
#include "MyData.h"
USING_NS_CC;

bool Monster::init(){

	if(!CCSprite::initWithFile("ZhouZhou.png")){
		return false;
	}
	winSize=CCDirector::sharedDirector()->getWinSize();
	data=MyData::shareMyData();
	//
	CCRotateBy* rotateBy=CCRotateBy::create(1.0f,360);
	CCRepeat* re=CCRepeat::create(rotateBy,-1);
	this->runAction(re);
	this->schedule(schedule_selector(Monster::move));

	this->scheduleUpdate();
	
	this->schedule(schedule_selector(Monster::remove));
	return true;
}
void Monster::move(float dt){
	this->setPosition(ccpAdd(this->getPosition(),ccp(-2,0)));//
}
//��ײ���
void Monster::update(float dt){
	CCObject* obj=NULL;
	CCObject* tempObj=NULL;
	CCArray* tempArray=new CCArray();
	CCARRAY_FOREACH(data->bulletArray,obj){
		CCSprite* bullet=(CCSprite*)obj;
		//����ӵ�������Ļ�ˣ�ֱ���Ƴ�
		if(bullet->getPosition().x>winSize.width+bullet->getContentSize().width/2){
			tempArray->addObject(bullet);
		}
		//��ǰ����������ӵ�������ײ���
		if(this->boundingBox().intersectsRect(bullet->boundingBox())){//�ж����������Ƿ��ཻ
			this->removeFromParentAndCleanup(true);
			bullet->removeFromParentAndCleanup(true);
			data->bulletArray->removeObject(obj);
		}
	}
	CCARRAY_FOREACH(tempArray,tempObj){
		CCSprite* bullet=(CCSprite*)tempObj;
		bullet->removeFromParentAndCleanup(true);
		data->bulletArray->removeObject(tempObj);
	}
	delete tempArray;
}
void Monster::remove(float dt){
	if(this->getPosition().x<-this->getContentSize().width/2){
		this->removeFromParentAndCleanup(true);
	}
}



Monster::Monster(void)
{
	
}


Monster::~Monster(void)
{
}
