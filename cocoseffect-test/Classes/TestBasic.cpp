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

	// create macro ���� layer�� ���� autorelease�� �������� layer�� ���� relase�ϸ� �ȵȴ�.
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
