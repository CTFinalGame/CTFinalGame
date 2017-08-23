#ifndef _WATER_EFFECT_H
#define _WATER_EFFECT_H_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"

#include "../BaseObject.h"
#include "../../FrameWork/IComponent.h"
#include "../../Objects/Object/Explosion.h"
#include "../Bullets/Item.h"
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