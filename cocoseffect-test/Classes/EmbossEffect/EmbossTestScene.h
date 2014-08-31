
#ifndef __EMBOSS_TEST_SCENE_H__
#define __EMBOSS_TEST_SCENE_H__

#include "cocos2d.h"
#include "../TestBasic.h"
#include "../BaseTest.h"

USING_NS_CC;

class CEmbossTest : public BaseTest
{
public:
	CEmbossTest();
	~CEmbossTest();

	void ShowEffect();

public:
	void restartCallback(Ref* sender);
	void nextCallback(Ref* sender);
	void backCallback(Ref* sender);
	virtual std::string title() const override;

	CREATE_FUNC(CEmbossTest);

};


class CEmbossTestScene : public TestScene
{
public:
	virtual void runThisTest();
};


#endif // __EMBOSS_TEST_SCENE_H__