#include "MyTiledMapLayer.h"
#include "cocos2d.h"
#include "MyTouchLayer.h"
#include "NinjLayer.h"
#include <iostream>  
#include <string>  
#include <vector>  
using namespace std; 
USING_NS_CC;
CCScene* MyTiledMapLayer::scene(){
	CCScene* scene=CCScene::create();
	MyTiledMapLayer* layer=MyTiledMapLayer::create();
	scene->addChild(layer);
	return scene;
}

bool MyTiledMapLayer::init(){
	if(!CCLayer::init()){
		return false;
	}
	map=CCTMXTiledMap::create("map.tmx");
	//
	this->addChild(map);
	mapLayer=map->layerNamed("mapLayer");
	objLayer=map->objectGroupNamed("objLayer");
	//让当前层接受触摸
	this->setTouchEnabled(true);
	//注册 自动调用该对象的registerWithTouchDispatcher()方法

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();

	CCMenuItemFont* item1 = CCMenuItemFont::create("map1", this, menu_selector(MyTiledMapLayer::action1));
	CCMenuItemFont* item2 = CCMenuItemFont::create("map2", this, menu_selector(MyTiledMapLayer::action2));
	CCMenuItemFont* item3 = CCMenuItemFont::create("map3", this, menu_selector(MyTiledMapLayer::action3));
	CCMenuItemFont* item4 = CCMenuItemFont::create("map4", this, menu_selector(MyTiledMapLayer::action4));
	CCMenu* menu = CCMenu::create(item1,item2,item3,item4,NULL);
	menu->alignItemsVertically(); 
	menu->setPosition(ccp(winSize.width-50,200));
	this->addChild(menu);


	CCMenuItemFont* startItem=CCMenuItemFont::create("previous",this,menu_selector(MyTiledMapLayer::previous));
	CCMenuItemFont* nextItem=CCMenuItemFont::create("next",this,menu_selector(MyTiledMapLayer::next));
	CCMenu* prevMenu=CCMenu::create(startItem,nextItem,NULL);
	prevMenu->setPosition(ccp(winSize.width-400,200));
	prevMenu->alignItemsVertically();
	this->addChild(prevMenu);

	CCSprite* sprite=CCSprite::create("Player.png");
	this->addChild(sprite,0,0);
	sprite->setPosition(ccp(winSize.width/2,winSize.height/2));


	return true;
}

void MyTiledMapLayer::registerWithTouchDispatcher(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}

bool MyTiledMapLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	CCPoint touchPoint=pTouch->getLocation();
	
	CCPoint mapPoint=this->changeCCPoint2MapPoint(touchPoint);
	

	//获得，当前触摸点对应块的GId
	int gid=mapLayer->tileGIDAt(mapPoint);
	CCLOG("%0.2f,%0.2f gid=%02d",mapPoint.x,mapPoint.y,gid);
	CCDictionary* dic=map->propertiesForGID(gid);

	//根据从字典里取值 ,取得是地图瓦片里存储的值。
	if(dic){
	int isPlant=((CCString*)dic->objectForKey("isPlant"))->intValue();
	}

	CCDictionary* objDic=objLayer->objectNamed("Start");
	int x=((CCString*)objDic->objectForKey("x"))->intValue();
	int y=((CCString*)objDic->objectForKey("y"))->intValue();

	//这里的xy是地图上某个对象的OpenGL坐标
	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	sprite->setPosition(ccp(x,y));

	//点击water对象，在该对象上添加一个target精灵
	CCDictionary* waterDic=objLayer->objectNamed("Water");
	int x1=((CCString*)waterDic->objectForKey("x"))->intValue();
	int y1=((CCString*)waterDic->objectForKey("y"))->intValue();
	int w1=((CCString*)waterDic->objectForKey("width"))->intValue();
	int h1=((CCString*)waterDic->objectForKey("height"))->intValue();
	CCRect rect=CCRect(x1,y1,w1,h1);
	if(rect.containsPoint(touchPoint)){
		CCSprite* sprite=CCSprite::create("Target.png");
		this->addChild(sprite);
		sprite->setPosition(touchPoint);
	}

	//遍历对象层里的所有对象
// 	CCArray* array=objLayer->getObjects();
// 	CCObject* obj=NULL;
// 	CCARRAY_FOREACH(array,obj){
// 
// 	}
	return true;
}

CCPoint MyTiledMapLayer::changeCCPoint2MapPoint( CCPoint touchPoint ) 
{
	int x=touchPoint.x/map->getTileSize().width;
	//注意map->getMapSize() 就是获得map是几乘几 ，所以map->getMapSize().height 就是mapy轴上有几块
	int y=(map->getMapSize().height*map->getTileSize().height - touchPoint.y)/
		map->getTileSize().height;
	return ccp(x,y);
}
void MyTiledMapLayer::action1(CCObject* sender){
	CCLOG("WayPoints1!");
	//通过读取对象属性的方式获得路径点，需要修改tmx文件
	CCDictionary* waterDic=objLayer->objectNamed("WayPoints");

	
	int x1=((CCString*)waterDic->objectForKey("x"))->intValue();
	int y1=((CCString*)waterDic->objectForKey("y"))->intValue();
	CCLOG("WayPoints2!");
	if(waterDic){
		CCLOG("WayPoints exist!");
	}else{
		CCLOG("WayPoints is null!");
	}
	//CCString* points=CCString::create("a b c");
	CCString* points=(CCString*)waterDic->objectForKey("points");
	
	CCLOG("this action :%s",points->getCString());
	vector<string> strs=splitEx(points->getCString()," ");
	
	CCArray* actionArray=CCArray::create();
	CCMoveTo* moveto=CCMoveTo::create(1.0f,ccp(x1,y1));
	actionArray->addObject(moveto);

	CCLOG("get orig location:%i,%i",x1,y1);

	CCSprite* sprite=(CCSprite*)this->getChildByTag(0);
	CCPoint oriPoint=CCPoint(x1,y1+sprite->getContentSize().height);
	for (  int i = 0; i < strs.size(); i++)    
	{    
		//打出来的点是相对坐标
		CCLOG("this points[%i] :%s",i,strs[i].c_str());
		CCPoint p=changePointStr2CCPoint(strs[i].c_str());
		//与原始坐标相加，得出位移坐标，相加是不对的。
		//CCPoint targetPoint=ccpAdd(oriPoint,p);
		CCLOG("get target location:%f,%f",oriPoint.x+p.x,oriPoint.y+p.y);
		CCMoveTo* moveby=CCMoveTo::create(1.0f,CCPoint(oriPoint.x+p.x,oriPoint.y+p.y));
		actionArray->addObject(moveby);
	}    
	CCSequence* sq=CCSequence::create(actionArray);

	sprite->runAction(sq);
}
CCPoint MyTiledMapLayer::changePointStr2CCPoint(const string& src){
	vector<string> strs=splitEx(src,",");
	return CCPoint(atof(strs[0].c_str()),atof(strs[1].c_str()));
}

vector<string> MyTiledMapLayer::splitEx(const string& src, string separate_character)  
{  
	vector<string> strs;  

	int separate_characterLen = separate_character.size();//分割字符串的长度,这样就可以支持如“,,”多字符串的分隔符  
	int lastPosition = 0,index = -1;  
	while (-1 != (index = src.find(separate_character,lastPosition)))  
	{  
		strs.push_back(src.substr(lastPosition,index - lastPosition));  
		lastPosition = index + separate_characterLen;  
	}  
	string lastString = src.substr(lastPosition);//截取最后一个分隔符后的内容  
	if (!lastString.empty())  
		strs.push_back(lastString);//如果最后一个分隔符后还有内容就入队  
	return strs;  
}  

void MyTiledMapLayer::action2(CCObject* sender){
	CCDictionary* waterDic=objLayer->objectNamed("triangle");
	int x1=((CCString*)waterDic->objectForKey("x"))->intValue();
	int y1=((CCString*)waterDic->objectForKey("y"))->intValue();
	CCSprite* s1=CCSprite::create("Projectile.png");
	this->addChild(s1);
	s1->setPosition(ccp(x1,y1));
	CCString* points=(CCString*)waterDic->objectForKey("points");
	vector<string> strs=splitEx(points->getCString()," ");
	CCArray* actionArray=CCArray::create();

	CCPoint oriPoint=CCPoint(x1,y1);
	for (  int i = 0; i < strs.size(); i++)    
	{    
		//打出来的点是相对坐标
		CCLOG("this points[%i] :%s",i,strs[i].c_str());
		CCPoint p=changePointStr2CCPoint(strs[i].c_str());
		//与原始坐标相加，得出位移坐标，相加是不对的。
		//CCPoint targetPoint=ccpAdd(oriPoint,p);
		CCLOG("get target location:%f,%f",oriPoint.x+p.x,oriPoint.y+p.y);

		CCSprite* s2=CCSprite::create("Projectile.png");
		this->addChild(s2);
		s2->setPosition(ccp(oriPoint.x+p.x,oriPoint.y+p.y));
	}
	CCLOG("this action2");
}
void MyTiledMapLayer::action3(CCObject* sender){
	CCLOG("this action3");
}
void MyTiledMapLayer::action4(CCObject* sender){
	CCLOG("this action4");
}

void MyTiledMapLayer::previous(CCObject* sender){
	CCDirector::sharedDirector()->replaceScene(MyTouchLayer::scene());
	CCLOG("this previous");
}
void MyTiledMapLayer::next(CCObject* sender){
	CCDirector::sharedDirector()->replaceScene(NinjLayer::scene());
	CCLOG("this next");
	
}



MyTiledMapLayer::MyTiledMapLayer(void)
{
}


MyTiledMapLayer::~MyTiledMapLayer(void)
{
}
