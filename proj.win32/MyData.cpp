#include "MyData.h"
#include "cocos2d.h"
USING_NS_CC;
static MyData* data=NULL;
MyData* MyData::shareMyData(){
	if(!data){
		data=new MyData();
		data->init();
	}
	return data;
}

void MyData::init(){
	//CCArray::create() ����������������Ҫ�ֶ��ͷ�
	bulletArray=new CCArray();
}

MyData::MyData(void)
{
}


MyData::~MyData(void)
{
	delete bulletArray;
	delete data;
}
