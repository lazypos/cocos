#include "CEnemyLayer.h"

void CCEnemyLayer::set_gamelayer( CCGameLayer* ly )
{
	pGamelayer = ly;
}

bool CCEnemyLayer::init()
{
	mQQ = new CCArray;
	mWinSize = CCDirector::sharedDirector()->getWinSize();
	this->scheduleUpdate();
	this->schedule(schedule_selector(CCEnemyLayer::ccb_create_enemy), 1);
	return true;
}

void CCEnemyLayer::ccb_create_enemy( float dt )
{
	if (pGamelayer->mLost)
		return;

	CCSprite *hero = (CCSprite*)(pGamelayer->getChildByTag(110));
	CCPoint	phero = hero->getPosition();

	CCSpriteFrame *sp	= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bulle");
	for (int i=0; i<4; i++)
	{
		CCSprite *enemy = CCSprite::createWithSpriteFrame(sp);
		enemy->setScale(0.5f);

		CCPoint pEnemy;
		if (i==0)
			pEnemy.setPoint(0, CCRANDOM_0_1()*mWinSize.height);
		else if (i==1)
			pEnemy.setPoint(CCRANDOM_0_1()*mWinSize.width, mWinSize.height);
		else if (i==2)
			pEnemy.setPoint(mWinSize.width, CCRANDOM_0_1()*mWinSize.height);
		else
			pEnemy.setPoint(CCRANDOM_0_1()*mWinSize.width, 0);

		enemy->setPosition(pEnemy);
		pGamelayer->mLevel -= 0.1f;
		enemy->runAction(CCMoveBy::create(pGamelayer->mLevel, get_stop_point(pEnemy, phero)));
		this->addChild(enemy);

		pGamelayer->mArrayEnemy->addObject(enemy);
	}
}

CCPoint CCEnemyLayer::get_stop_point( CCPoint& p1, CCPoint& p2 )
{
	float px = 0, py = 0;
	float key = (p2.y - p1.y)/(p2.x - p1.x); 
	if (p1.x == 0)
	{
		float y = key*(mWinSize.width+100);
		if (abs(y) > mWinSize.height+100)
		{
			py = (py>0 ? mWinSize.height+100 : -mWinSize.height-100);
			px = y / key;
		}
		else
		{
			py = y;
			px = mWinSize.width+100;
		}	
	}
	else if (p1.y == mWinSize.height)
	{
		float x = (-mWinSize.height-100)/key;
		if (abs(x) > mWinSize.width+100)
		{
			px = (px>0 ? mWinSize.width+100 : -mWinSize.width-100);
			py = px * key;
		}
		else
		{
			px = x;
			py = -mWinSize.height-100;
		}
	}
	else if (p1.x == mWinSize.width)
	{
		float y = (-mWinSize.width-100)*key;
		if (abs(y) > mWinSize.height)
		{
			py = (py>0 ? mWinSize.height+100 : -mWinSize.height-100);
			px = y / key;
		}
		else
		{
			py = y;
			px = -mWinSize.width-100;
		}
	}
	else
	{
		float x = (mWinSize.height+100)/key;
		if (abs(x) > mWinSize.width)
		{
			px = (px>0 ? mWinSize.width+100 : -mWinSize.width-100);
			py = px * key;
		}
		else
		{
			px = x;
			py = mWinSize.height+100;
		}
	}
	return ccp(px, py);
}

void CCEnemyLayer::remove_enemy()
{
	CCObject *obj;
	CCARRAY_FOREACH(pGamelayer->mArrayEnemy, obj)
	{
		CCSprite* p = (CCSprite*)obj;
		if (p->getPositionX()<0 || p->getPositionX()>mWinSize.width
			|| p->getPositionY()<0 || p->getPositionY()>mWinSize.height)
		{
			pGamelayer->mArrayEnemy->removeObject(obj);
		}
	}
}

void CCEnemyLayer::update( float delta )
{
	if (pGamelayer->mLost)
	{
		this->removeAllChildren();
		return;
	}

	CCSprite *hero = (CCSprite*)(pGamelayer->getChildByTag(110));
	CCRect hrect = hero->boundingBox();
	CCArray *arrtemp = new CCArray;
	arrtemp->addObjectsFromArray(pGamelayer->mArrayEnemy);
	CCObject *obj;
	CCARRAY_FOREACH(arrtemp, obj)
	{
		CCSprite* p = (CCSprite*)obj;
		if (hrect.intersectsRect(p->boundingBox()))
		{
			pGamelayer->mLost = true;
			hero->setVisible(false);
			p->setVisible(false);
			CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("boom");
			CCSprite *Boom = CCSprite::create();
			Boom->setPosition(hero->getPosition());
			pGamelayer->addChild(Boom);
			Boom->setTag(250);
			Boom->runAction(CCAnimate::create(animation));
			break;
		}
	}
	arrtemp->removeAllObjects();
	delete arrtemp;
	remove_enemy();
}

