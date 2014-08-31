
#include "HelloWorldScene.h"
//#include "BaseScene.h"
#include "ColorRampEffect/ColorRampTestScene.h"
#include "EmbossEffect/EmbossTestScene.h"
#include "MovingGrassEffect/MovingGrassTestScene.h"

USING_NS_CC;


typedef struct _Controller
{
	const char *pStrTestName;
	std::function<TestScene*()> callback;
} Controller;

Controller g_EffectTest[] =
{
	{ "ColorRampEffect", []()	{ return new CColorRampTestScene(); } },
	{ "EmbossEffect", []()		{ return new CEmbossTestScene(); } },
	{ "MovingGrassEffect", []() { return new CMovingGrassTestScene(); } },

};

static int  g_nTestCount = sizeof(g_EffectTest) / sizeof(g_EffectTest[0]);
static Vec2 g_tCurPos = Vec2::ZERO;

#define LINE_SPACE 40

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	//auto layer = new HelloWorld;//HelloWorld::create();
	//layer->init();
	//layer->autorelease();
	auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::HelloWorld()
{
	m_beginePos = Vec2::ZERO;
	m_pItemMenu = NULL;
	m_bExitThread = false;
}

HelloWorld::~HelloWorld()
{
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

	/////////////////////////////
	// 3. Make the Menu List

	// add menu items for effect tests
	TTFConfig ttfConfig("fonts/arial.ttf", 24);
	m_pItemMenu = Menu::create();
	for (int i = 0; i < g_nTestCount; ++i)
	{
		auto label = Label::createWithTTF(ttfConfig, g_EffectTest[i].pStrTestName);
		auto menuItem = MenuItemLabel::create(label, CC_CALLBACK_1(HelloWorld::menuClickCallback, this));

		menuItem->setPosition( Vec2( VisibleRect::center().x, (VisibleRect::top().y - (i + 1) * LINE_SPACE) ) );
		m_pItemMenu->addChild(menuItem, i + 10000);
	}

	m_pItemMenu->setContentSize( Size(VisibleRect::getVisibleRect().size.width, (g_nTestCount + 1) * LINE_SPACE) );
	m_pItemMenu->setPosition(g_tCurPos);
	
	this->addChild(m_pItemMenu);


	



	//auto pMenuItem1 = MenuItemFont::create(g_EffectTest[0], CC_CALLBACK_1(HelloWorld::OnClickMenu, this));
	//pMenuItem1->setColor(Color3B(255, 0, 0));

	//auto pMenuItem2 = MenuItemFont::create("Menu-2", CC_CALLBACK_1(HelloWorld::OnClickMenu, this));
	//pMenuItem2->setColor(Color3B(0, 255, 0));

	//pMenuItem1->setTag(eColorRampEffect);
	//pMenuItem2->setTag(eEmbosEffect);

	//// 6 - make the menu
	//auto pMenu = Menu::create(pMenuItem1, pMenuItem2, NULL);

	//// 7 - 
	//pMenu->alignItemsVertically();
	//
	//// 8 - add the menu into the layer
	//this->addChild(pMenu);



 //   /////////////////////////////
 //   // 3. add your codes below...

 //   // add a label shows "Hello World"
 //   // create and initialize a label
 //   
 //   auto label = LabelTTF::create("Hello World", "Arial", 24);
 //   
 //   // position the label on the center of the screen
 //   label->setPosition(Vec2(origin.x + visibleSize.width/2,
 //                           origin.y + visibleSize.height - label->getContentSize().height));

 //   // add the label as a child to this layer
 //   this->addChild(label, 1);

 //   // add "HelloWorld" splash screen"
 //   auto sprite = Sprite::create("HelloWorld.png");

 //   // position the sprite on the center of the screen
 //   sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

 //   // add the sprite as a child to this layer
 //   this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuClickCallback(cocos2d::Object *pSender)
{
	auto pMenuItem = (MenuItem*)pSender;
	int idx = pMenuItem->getLocalZOrder() - 10000;
	auto scene = g_EffectTest[idx].callback();

	if (scene)
	{
		scene->runThisTest();
		scene->release();
	}
}