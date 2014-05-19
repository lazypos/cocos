#ifndef __CCENEMYLAYER_H__
#define __CCENEMYLAYER_H__
#include "cocos2d.h"
#include "CGameLayer.h"
USING_NS_CC;

class CCEnemyLayer : public CCLayer
{
public:
	CREATE_FUNC(CCEnemyLayer);
	void		set_gamelayer(CCGameLayer* ly);

private:
	bool		init();
	void		ccb_create_enemy(float dt);
	CCPoint		get_stop_point(CCPoint& p1, CCPoint& p2);
	void		remove_enemy();
	void		update(float delta);

private:
	CCGameLayer* pGamelayer;
	CCSize		 mWinSize;
	CCArray*	 mQQ;
};

#endif