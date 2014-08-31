#include "MovingGrassTestScene.h"


// ====================================
// CMovingGrassTest
// ====================================
CMovingGrassTest::CMovingGrassTest()
{
	m_pSprite = NULL;
	m_nTimeUniformLocation = -1;
	m_fTotalTime = 0.0f;

	ShowEffect();
}

CMovingGrassTest::~CMovingGrassTest()
{
}

void CMovingGrassTest::ShowEffect()
{
	// 1
	Size size = Director::getInstance()->getWinSize();

	Sprite* pSprite = Sprite::create("grass.png");
	pSprite->setPosition(ccp(size.width / 2, size.height / 2));
	this->addChild(pSprite);

	// 2
	const GLchar* fragmentSource = (GLchar*)CCString::createWithContentsOfFile(FileUtils::getInstance()->fullPathFromRelativeFile("CSEGrass.fsh", "./Resources"))->getCString();

	GLProgram* glProgram = new GLProgram();
	//glProgram->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, fragmentSource);
	glProgram->initWithVertexShaderByteArray(ccPositionTextureColor_noMVP_vert, fragmentSource);
	pSprite->setShaderProgram(glProgram);

	pSprite->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	pSprite->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	pSprite->getShaderProgram()->link();
	pSprite->getShaderProgram()->updateUniforms();

	m_pSprite = pSprite;
	
	// 3
	m_nTimeUniformLocation = glGetUniformLocation(pSprite->getShaderProgram()->getProgram(), "u_time");

	// 4
	this->schedule(schedule_selector(CMovingGrassTest::UpdateGrassLocation));

	// 5
	pSprite->getShaderProgram()->use();

}

void CMovingGrassTest::backCallback(Ref* sender)
{
	ShowEffect();
}

void CMovingGrassTest::nextCallback(Ref* sender)
{
	ShowEffect();
}

std::string CMovingGrassTest::title() const
{
	return "Moving Grass Effect Test";
}

void CMovingGrassTest::restartCallback(Ref* sender)
{
	ShowEffect();
}

void CMovingGrassTest::UpdateGrassLocation(float _fDT)
{
	m_fTotalTime += _fDT;
	if (m_pSprite != NULL)
	{
		m_pSprite->getShaderProgram()->use();
	}
	glUniform1f(m_nTimeUniformLocation, m_fTotalTime);
}


// ====================================
// CMovingGrassTestScene
// ====================================
void CMovingGrassTestScene::runThisTest()
{
	auto layer = CMovingGrassTest::create();
	this->addChild(layer);

	Director::getInstance()->replaceScene(this);
}
