#include "CGameLayer.h"
#include "resource.h"
#include "CControlLayer.h"
#include "CEnemyLayer.h"

CCGameLayer::CCGameLayer()
{
	mOnTouch = false;
	mLost = false;
	mLevel = 5.0;
	m_time = 0;
	mRstart = false;
}

CCGameLayer::~CCGameLayer()
{
	if (mArrayEnemy)
	{
		mArrayEnemy->removeAllObjects();
		delete mArrayEnemy;
	}
}


CCScene* CCGameLayer::scene()
{
	CCScene * pScene = NULL;
	do 
	{
		pScene = CCScene::create();
		CC_BREAK_IF(!pScene);

		CCLayer* pLayer = CCGameLayer::create();
		CC_BREAK_IF(!pLayer);

		pScene->addChild(pLayer);

	} while (0);
	return pScene;
}

bool CCGameLayer::init()
{
	if ( !CCLayer::init() )
		return false;
	mWinSize = CCDirector::sharedDirector()->getWinSize();

	//< ±³¾°
	CCSprite *pback = CCSprite::create("609002.jpg");
	pback->setPosition(ccp(mWinSize.width/2, mWinSize.height/2));
	this->addChild(pback, -1);

	//< ·ÖÊý
	CCLabelBMFont *mTime = CCLabelBMFont::create("0.0", "arial-14.fnt");
	mTime->setScale(1.2f);
	mTime->setColor(ccc3(255,255,255));
	mTime->setAlignment(kCCTextAlignmentRight);
	mTime->setPosition(mWinSize.width-50, mWinSize.height-10);
	this->addChild(mTime, 1000, 100);

	//< ×Óµ¯
	mArrayEnemy = new CCArray;
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("body600013_Ani.plist");
 	CCTexture2D * p2d = CCTextureCache::sharedTextureCache()->addImage("green_edit.png");
 	CCSpriteFrame * psf = CCSpriteFrame::createWithTexture(p2d,CCRect(0,0,28,28));
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFrame(psf, "bulle");

	//< Ó¢ÐÛ
	CCSprite *hero = CCSprite::create("RobotState4.png");
	hero->setPosition(ccp(mWinSize.width/2, mWinSize.height/2));
	hero->setTag(110);
	this->addChild(hero);

	//< ±¬Õ¨
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Boom.plist");
	CCArray *animFrames = CCArray::create();
	char str[64] = {0};
	for (int i = 1; i < 7; ++i)
	{
		sprintf(str, "Boom_%02d.png", i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "boom");
	
	//< game over
	CCLabelTTF * lb = CCLabelTTF::create("", "fonts/arial.ttf", 30);
	lb->setPosition(ccp(mWinSize.width/2, mWinSize.height/2));
	lb->setVisible(false);
	this->addChild(lb, 100, 200);

	//< ¿ØÖÆ²ã
	CCControlLayer *cLayer = CCControlLayer::create();
	cLayer->set_gamelayer(this);
	this->addChild(cLayer);

	CCEnemyLayer* enemylayer = CCEnemyLayer::create();
	enemylayer->set_gamelayer(this);
	this->addChild(enemylayer);

	this->scheduleUpdate();
	return true;
}

void CCGameLayer::update( float dt )
{
	CCSprite *hero = (CCSprite*)(this->getChildByTag(110));
	if (mLost && !mRstart)
	{
		CCLabelTTF * lb = (CCLabelTTF*)(this->getChildByTag(200));
		char rst[128] = {0};
		sprintf(rst, "Game Over\nTime: %.1f \nwww.dagouge.com", m_time);
		lb->setString(rst);
		lb->setVisible(true);
		return;
	}

	if (mRstart)
	{
		CCLabelTTF * lb = (CCLabelTTF*)(this->getChildByTag(200));
		lb->setVisible(false);
		mLevel = 5.0;
		hero->setPosition(ccp(mWinSize.width/2, mWinSize.height/2));
		hero->setVisible(true);
		CCLabelBMFont *socer = (CCLabelBMFont*)(this->getChildByTag(100));
		m_time = 0;
		socer->setString("0.0");
		mOnTouch = false;
		CCSprite* boom = (CCSprite*)(this->getChildByTag(250));
		this->removeChildByTag(250);

		CCObject *obj;
		CCARRAY_FOREACH(mArrayEnemy, obj)
		{
			CCSprite* p = (CCSprite*)obj;
			p->setVisible(false);
		}
		mArrayEnemy->removeAllObjects();
		mRstart = false;
		mLost = false;
	}

	m_time += dt;
	char buf[20];
	sprintf(buf, "%.1f", m_time);
	CCLabelBMFont *socer = (CCLabelBMFont*)(this->getChildByTag(100));
	socer->setString(buf);
}
