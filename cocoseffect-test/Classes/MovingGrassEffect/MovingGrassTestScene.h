#ifndef __MOVING_GRASS_TEST_SCENE_H__
#define __MOVING_GRASS_TEST_SCENE_H__

#include "cocos2d.h"
#include "../TestBasic.h"
#include "../BaseTest.h"

USING_NS_CC;

class CMovingGrassTest : public BaseTest
{
public:
	CMovingGrassTest();
	~CMovingGrassTest();

	void ShowEffect();

public:
	void restartCallback(Ref* sender);
	void nextCallback(Ref* sender);
	void backCallback(Ref* sender);
	virtual std::string title() const override;

	CREATE_FUNC(CMovingGrassTest);


public:
	void UpdateGrassLocation(float _fDT);

private:
	Sprite*	m_pSprite;
	int		m_nTimeUniformLocation;
	float	m_fTotalTime;
};


class CMovingGrassTestScene : public TestScene
{
public:
	virtual void runThisTest();
};


#endif // __NOISE_GRASS_TEST_SCENE_H__