#include "EmbossTestScene.h"


// ====================================
// CEmbossTest
// ====================================
CEmbossTest::CEmbossTest()
{
	ShowEffect();
}

CEmbossTest::~CEmbossTest()
{
}

void CEmbossTest::ShowEffect()
{
	// 1
	Size size = Director::getInstance()->getWinSize();

	Sprite* pSprite = Sprite::create("HelloWorld.png");
	pSprite->setPosition(ccp(size.width / 2, size.height / 2));
	this->addChild(pSprite);

	// 2
	const GLchar* fragmentSource = (GLchar*)CCString::createWithContentsOfFile(FileUtils::getInstance()->fullPathFromRelativeFile("CSEEmboss.fsh", "./Resources"))->getCString();

	GLProgram* glProgram = new GLProgram();
	//glProgram->initWithVertexShaderByteArray(ccPositionTextureA8Color_vert, fragmentSource);
	glProgram->initWithVertexShaderByteArray(ccPositionTextureColor_noMVP_vert, fragmentSource);
	pSprite->setShaderProgram(glProgram);

	pSprite->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	pSprite->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	pSprite->getShaderProgram()->link();
	pSprite->getShaderProgram()->updateUniforms();

	// 3
	pSprite->getShaderProgram()->use();

}

void CEmbossTest::backCallback(Ref* sender)
{
	ShowEffect();
}

void CEmbossTest::nextCallback(Ref* sender)
{
	ShowEffect();
}

std::string CEmbossTest::title() const
{
	return "Emboss Effect Test";
}

void CEmbossTest::restartCallback(Ref* sender)
{
	ShowEffect();
}


// ====================================
// CEmbossTestScene
// ====================================
void CEmbossTestScene::runThisTest()
{
	auto layer = CEmbossTest::create();
	this->addChild(layer);

	Director::getInstance()->replaceScene(this);
}
