#ifndef __WATERFALL_EFFECT_H__
#define __WATERFALL_EFFECT_H__

#include "../../FrameWork/Scene/PlayScene.h"

using namespace std;

class WaterFallEffect : public BaseObject
{
public:
	WaterFallEffect(GVector2 position);
	~WaterFallEffect();

	// Các phương thức kế thừa từ BaseObject.
	void init() override;
	void update(float deltatime) override;
	void draw(LPD3DXSPRITE, Viewport*) override;
	void release() override;
	void checkifOutofScreen();

private:

	Animation* _animations;

	GVector2	_beginPosition;

};
#endif