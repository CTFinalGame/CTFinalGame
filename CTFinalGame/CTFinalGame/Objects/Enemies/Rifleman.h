﻿#ifndef _RIFLEMAN_H
#define _RIFLEMAN_H

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/IComponent.h"
#include "../../FrameWork/Scene/PlayScene.h"
#include "../Enemies/BaseEnemy.h"
#include "../../FrameWork/GameTime.h"
#include "../../FrameWork/StopWatch.h"
#include "../Object/Explosion.h"
#include "../../FrameWork/Collision/CollisionBody.h"
using namespace std;

#define RIFLEMAN_HITPOINT 1
#define RIFLEMAN_SCORE 500
#define RIFLEMAN_SHOOTING_DELAY 250.0f
#define RIFLEMAN_BULLET_BURST_DELAY 3050.0f
#define RIFLEMAN_ANIMATION_SPEED 0.4755f

class Rifleman : public BaseEnemy
{
public:
	/*
	@status: NORMAL cho lính đứng bắn, HIDDEN cho lính núp
	@pos: vị trí
	@x, y: tọa độ của pos
	*/
	Rifleman(eStatus status, GVector2 pos);
	Rifleman(eStatus status, float x, float y);
	~Rifleman();

	void init();
	void update(float);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	float getShootingAngle();
	void setShootingAngle(double);
	void die();
	void shoot();
	void onCollisionBegin(CollisionEventArg*);
	void onCollisionEnd(CollisionEventArg*);
	float checkCollision(BaseObject*, float);
	IComponent* getComponent(string);

private:
	map<string, IComponent*> _listComponent;
	map<int, Animation*> _animations;
	BaseObject *_explosion;
	float _shootingAngle;
	StopWatch *_stopwatch;
	StopWatch *_loopwatch;
	StopWatch *_shootingWatch;
	void calculateShootingAngle();
	void calculatingShootingDirection();
	void changeShootingStance();
};
#endif