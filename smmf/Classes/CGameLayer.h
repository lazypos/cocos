#ifndef __CGAMELAYER_SCENE_H__
#define __CGAMELAYER_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class CCGameLayer : public CCLayer
{
public:
	CCGameLayer();
	~CCGameLayer();
	static CCScene* scene();

private:
	CREATE_FUNC(CCGameLayer);

	bool		init();
	void		update(float delta);

public:
	bool				mLost;
	CCSize				mWinSize;
	CCArray				*mArrayEnemy;
	bool				mOnTouch;
	float				mLevel;
	float				m_time;
	CCPoint				mNextPoint;
	bool				mRstart;
};

#endif