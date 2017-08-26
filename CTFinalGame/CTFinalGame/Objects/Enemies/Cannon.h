#pragma once
#ifndef __CANNON_H__
#define __CANNON_H__

#include "../../FrameWork/Animation.h"
#include "../../FrameWork/StopWatch.h"
#include "../../FrameWork/Scene/PlayScene.h"
//#include "../Bullets/Bullet.h"
#include "../../FrameWork/Collision/CollisionBody.h"
#include "../../FrameWork/IComponent.h"
#include "../Object/Explosion.h"
#include "../Enemies/BaseEnemy.h"
#include "../Bullets/BulletManager.h"

#define CANNON_HITPOINT 8
#define CANNON_SCORE 500
#define CANNON_SHOOTING_DELAY 2000.0f
#define CANNON_ANIMATION_SPEED 0.33f
#define CANNON_APPEAR_SPEED 0.08f

#define PI 3.14159265

using namespace std;
class Cannon :public BaseEnemy
{
public:
	Cannon(eStatus status, GVector2 pos);
	Cannon(eStatus status, float x, float y);
	Cannon(eWT_Status wtstatus, GVector2 pos);
	Cannon(eWT_Status wtstatus, float x, float y);

	~Cannon();

	void init();
	void update(float);
	void draw(LPD3DXSPRITE, Viewport*);
	void release();

	void setBillAngle(float);
	float getBillAngle();
	void setShootingAngle(float);
	float getShootingAngle();

	void setStatus(eStatus);
	void setWTStatus(eWT_Status);
	eWT_Status getWT_Status();
	void shoot();
	void checkIfOutofScreen();
private:
	map<int, Animation*> _animation;
	float _shootingAngle;
	float _billAngle;
	eWT_Status _wtstatus;
	BaseObject* _explosion;
	list<Bullet*> _listBullet;
	StopWatch* _stopwatch;

	void initExplosion();
	void updateExplosion(float);

	void addStatus(eStatus);
	void addStatus(eWT_Status);
	void removeStatus(eStatus);
	void removeStatus(eWT_Status);
	bool isInStatus(eStatus);
	bool isInStatus(eWT_Status);
	void calculateBillangle();
	void rangeAttack();
	bool isRange();

	StopWatch* _loopwatch2;
	int bullet = 0;
	float delay1;
};
#endif
