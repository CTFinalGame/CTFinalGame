#ifndef __WATER_EFFECT_H__
#define __WATER_EFFECT_H__

#include "../../FrameWork/Scene/PlayScene.h"

using namespace std;

class WaterEffect : public BaseObject
{
public:
	WaterEffect(GVector2 position);
	~WaterEffect();

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