#include "ColorRampTestScene.h"


// ====================================
// CColorRampTest
// ====================================
CColorRampTest::CColorRampTest()
{
	ShowEffect();
}

CColorRampTest::~CColorRampTest()
{
}

void CColorRampTest::ShowEffect()
{
	// 1
	Size size = Director::getInstance()->getWinSize();

	Sprite* pSprite = Sprite::create("HelloWorld.png");
	pSprite->setPosition(ccp(size.width / 2, size.height / 2));
	this->addChild(pSprite);

	// 2
	const GLchar* fragmentSource = (GLchar*)CCString::createWithContentsOfFile(FileUtils::getInstance()->fullPathFromRelativeFile("CSEColorRamp.fsh", "./Resources"))->getCString();

	GLProgram* glProgram = new GLProgram();
	//glProgram->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, fragmentSource);
	glProgram->initWithVertexShaderByteArray(ccPositionTextureColor_noMVP_vert, fragmentSource);
	pSprite->setShaderProgram(glProgram);

	pSprite->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	pSprite->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	pSprite->getShaderProgram()->link();
	pSprite->getShaderProgram()->updateUniforms();

	// 3
	m_nColorRampUniformLocation = glGetUniformLocation(pSprite->getShaderProgram()->getProgram(), "u_colorRampTexture");
	glUniform1i(m_nColorRampUniformLocation, 1);

	// 4
	m_pColorRampTexture = TextureCache::getInstance()->addImage("colorRamp.png");
	m_pColorRampTexture->setAliasTexParameters();

	// 5
	pSprite->getShaderProgram()->use();
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_pColorRampTexture->getName());
	glActiveTexture(GL_TEXTURE0);

}

void CColorRampTest::backCallback(Ref* sender)
{
	ShowEffect();
}

void CColorRampTest::nextCallback(Ref* sender)
{
	ShowEffect();
}

std::string CColorRampTest::title() const
{
	return "Color Ramp Effect Test";
}

void CColorRampTest::restartCallback(Ref* sender)
{
	ShowEffect();
}


// ====================================
// CColorRampTestScene
// ====================================
void CColorRampTestScene::runThisTest()
{
	auto layer = CColorRampTest::create();
	this->addChild(layer);

	Director::getInstance()->replaceScene(this);
}
