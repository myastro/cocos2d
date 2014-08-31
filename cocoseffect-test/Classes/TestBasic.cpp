#include "testBasic.h"
#include "HelloWorldScene.h"
//#include "extensions/cocos-ext.h"
//#include "cocostudio/CocoStudio.h"

TestScene::TestScene(bool bPortrait, bool physics/* = false*/)
{
    if (physics)
    {
#if CC_USE_PHYSICS
        TestScene::initWithPhysics();
#else
        Scene::init();
#endif
    }
    else
    {
        Scene::init();
    }
}

void testScene_callback(Ref *sender )
{
    auto scene = Scene::create();

	// create macro 내에 layer에 대한 autorelease가 있음으로 layer을 따로 relase하면 안된다.
#if 1
	auto layer = HelloWorld::create();
	scene->addChild(layer);
#else
	auto layer = new HelloWorld;
	layer->init();
    scene->addChild(layer);
    layer->release();
#endif

    Director::getInstance()->replaceScene(scene);

    //cocostudio::ArmatureDataManager::destroyInstance();
}

void TestScene::onEnter()
{
    Scene::onEnter();

    //add the menu item for back to main menu
    TTFConfig ttfConfig("fonts/arial.ttf", 20);
    auto label = Label::createWithTTF(ttfConfig,"MainMenu");

    auto menuItem = MenuItemLabel::create(label, testScene_callback );
    auto menu = Menu::create(menuItem, nullptr);

    menu->setPosition( Vec2::ZERO );
    menuItem->setPosition( Vec2( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );

    addChild(menu, 1);
}
