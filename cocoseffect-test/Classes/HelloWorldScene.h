#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

//enum ENUM_EFFECT_TEST_MODE
//{
//	eMinEffect=0, 
//	eColorRampEffect,
//	eEmbosEffect,
//	eNoiseGrassEffect,
//	eNosieEffect,
//	eVignettEffect,
//	eBoxBlurEffect,
//	eGaussianBlurEffect,
//	eDethOfFieldBlurEffect,
//	eSilhoutteEdgeEffect,
//	eSepiaFilter,
//	eRedBlueEyeEffect,
//	//eAmbientOcclusionEffect,
//
//	eMaxEffect,
//
//};

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();
	virtual ~HelloWorld();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void menuClickCallback(cocos2d::Object *pSender);

private:
	Vec2	m_beginePos;
	Menu*	m_pItemMenu;
	bool	m_bExitThread;

};

#endif // __HELLOWORLD_SCENE_H__
