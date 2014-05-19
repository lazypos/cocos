#include "CControlLayer.h"


bool CCControlLayer::init()
{
	setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	return true;
}

bool CCControlLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCSprite *hero = (CCSprite*)(pGamelayer->getChildByTag(110));
	if (!pGamelayer->mLost)
	{
		CCRect hrect = hero->boundingBox();
		CCPoint p = pTouch->getLocation();
		if (hrect.containsPoint(p))
			pGamelayer->mOnTouch = true;
		else
			pGamelayer->mOnTouch = false;
	}
	else // 重新开始
	{
		pGamelayer->mRstart = true;
	}
	return true;
}

void CCControlLayer::set_gamelayer( CCGameLayer* ly )
{
	pGamelayer = ly;
}

void CCControlLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (pGamelayer->mOnTouch && !pGamelayer->mLost)
	{
		CCSprite *hero = (CCSprite*)(pGamelayer->getChildByTag(110));
		hero->setPosition(pTouch->getLocation());
	}
}

