
#ifndef __COLOR_RAMP_TEST_SCENE_H__
#define __COLOR_RAMP_TEST_SCENE_H__

#include "cocos2d.h"
#include "../TestBasic.h"
#include "../BaseTest.h"

USING_NS_CC;

class CColorRampTest : public BaseTest
{
public:
	CColorRampTest();
	~CColorRampTest();

	void ShowEffect();

public:
	void restartCallback(Ref* sender);
	void nextCallback(Ref* sender);
	void backCallback(Ref* sender);
	virtual std::string title() const override;

	CREATE_FUNC(CColorRampTest);

private:
	int	m_nColorRampUniformLocation;	// 1
	CCTexture2D* m_pColorRampTexture;	// 2
};


class CColorRampTestScene : public TestScene
{
public:
	virtual void runThisTest();
};


#endif // __COLOR_RAMP_TEST_SCENE_H__