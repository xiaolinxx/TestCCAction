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

	//�õ�ǰ����ܴ���
	this->setTouchEnabled(true);
	//ע�� �Զ����øö����registerWithTouchDispatcher()����

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
	//��ӵ��㴥������ ��������˵����ʵ�ִ����Ķ������ȼ���ֵԽ�����ȼ�Խ��;�Ƿ����ɣ����ɵ����þ������ȼ��ߵĴ����¼������´���
	//ע�⣺���ȼ�����Ϊ����
	//ע�⣺CCMenu�����ȼ���-128
	diretor->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool MyTouchLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	//ע�⣬CCPoint����Ļ����ϵ������OpenGl����ϵ����Ļ����ϵԭ���������Ͻ�
	//������Ҫת����OpenGL����
	//cocos2d������û��getLocation()��װ�����ģ����Ա���Ҫ����ת��
// 	CCPoint touchPoint=pTouch->getLocationInView();
// 	touchPoint=CCDirector::sharedDirector()->convertToGL(touchPoint);

	CCPoint touchPoint=pTouch->getLocation();

	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	//sprite->setPosition(touchPoint);
	//ע�⣺�������false�������touchend ��touchmoved������ȥʵ�֣����ԣ����������ڶԴ��������жϣ��Ƿ����Ҫ��

	//�жϴ����Ƿ��ھ����ϣ�������ھ����ϣ��Ͳ�ȥ��ק
	CCRect rect=sprite->boundingBox();//���ؽڵ��С
	if(rect.containsPoint(touchPoint)){//rect���Ƕ�����.���÷���
		return true;
	}
	return false;
}

void MyTouchLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){

	CCLOG("this ccTouchMoved");
	//�õ�ִ�и÷���֮ǰ��ָλ�õ�����
	CCPoint point0=pTouch->getPreviousLocation();
	CCPoint touchPoint=pTouch->getLocation();
	//�����������������õ�v2ָ��v1������
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
