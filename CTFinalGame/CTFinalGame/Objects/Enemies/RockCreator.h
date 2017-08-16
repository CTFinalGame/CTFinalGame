

#ifndef __ROCK_CREATOR__
#define __ROCK_CREATOR__

#include "../../FrameWork/StopWatch.h"
#include "../BaseObject.h"
#include "../../FrameWork/Scene/Stage3.h"

class RockCreator : public BaseObject
{
public:
	RockCreator(GVector2 position);
	~RockCreator();

	void init();
	void update(float deltatime);
	void draw(LPD3DXSPRITE spriteHandle, Viewport* viewport);
	void release();
	RECT getBounding() override;
	float checkCollision(BaseObject * object, float dt);
	BaseObject* getRock();
private:
	GVector2 _position;
	BaseObject* _rockInstance;
	StopWatch* _stopwatch;
};

#endif // !__ROCK_CREATOR__
