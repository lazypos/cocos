#ifndef __CCONTROLLAYER_H__
#define __CCONTROLLAYER_H__
#include "cocos2d.h"
#include "CGameLayer.h"
USING_NS_CC;

class CCControlLayer : public CCLayer
{
public:
	CREATE_FUNC(CCControlLayer);
	void		set_gamelayer(CCGameLayer* ly);

private:
	bool		init();
	bool		ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void		ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

private:
	CCGameLayer* pGamelayer;
};

#endif