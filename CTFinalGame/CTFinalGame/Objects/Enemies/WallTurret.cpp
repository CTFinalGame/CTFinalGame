﻿#include"WallTurret.h"



WallTurret::WallTurret(eStatus status, GVector2 position) :BaseEnemy(eID::WALL_TURRET)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::WALL_TURRET);
	_sprite->setFrameRect(0, 0, 32, 32);
	this->setPosition(position);
	this->setStatus(status);
	this->setWTStatus(eWT_Status::WT_NORMAL);
}

WallTurret::WallTurret(eStatus status, float x, float y) :BaseEnemy(eID::WALL_TURRET)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::WALL_TURRET);
	_sprite->setFrameRect(0, 0, 32, 32);
	GVector2 pos(x, y);
	this->setPosition(pos);
	this->setStatus(status);
	this->setWTStatus(eWT_Status::WT_NORMAL);

}
WallTurret::WallTurret(eWT_Status wtstatus, GVector2 position) :BaseEnemy(eID::WALL_TURRET)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::WALL_TURRET);
	_sprite->setFrameRect(0, 0, 32, 32);
	this->setPosition(position);
	this->setWTStatus(wtstatus);
}
WallTurret::WallTurret(eWT_Status wtstatus, float x, float y) :BaseEnemy(eID::WALL_TURRET)
{
	_sprite = SpriteManager::getInstance()->getSprite(eID::WALL_TURRET);
	_sprite->setFrameRect(0, 0, 32, 32);
	GVector2 pos(x, y);
	this->setPosition(pos);
	this->setWTStatus(wtstatus);
}
WallTurret::~WallTurret()
{

}
void WallTurret::init()
{

	this->setScale(SCALE_FACTOR);

	_animation[WT_APPEAR] = new Animation(_sprite, WALL_TURRET_APPEAR_SPEED);
	_animation[WT_APPEAR]->addFrameRect(eID::WALL_TURRET, "appear_01", "appear_02", "appear_03", "appear_04", "appear_05", "appear_06", NULL);
	_animation[WT_APPEAR]->setLoop(false);

	_animation[WT_CLOSE] = new Animation(_sprite, WALL_TURRET_APPEAR_SPEED);
	_animation[WT_CLOSE]->addFrameRect(eID::WALL_TURRET, "appear_06", "appear_05", "appear_04", "appear_03", "appear_02", "appear_01", NULL);
	_animation[WT_CLOSE]->setLoop(false);

	_animation[WT_NORMAL] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_NORMAL]->addFrameRect(eID::WALL_TURRET, "normal_01", "normal_02", "normal_03", NULL);
	_animation[WT_NORMAL | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_NORMAL | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "normal_01", NULL);

	_animation[WT_LEFT_60] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_LEFT_60]->addFrameRect(eID::WALL_TURRET, "left_60_01", "left_60_02", "left_60_03", NULL);
	_animation[WT_LEFT_60 | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_LEFT_60 | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "left_60_01", NULL);

	_animation[WT_LEFT_30] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_LEFT_30]->addFrameRect(eID::WALL_TURRET, "left_30_01", "left_30_02", "left_30_03", NULL);
	_animation[WT_LEFT_30 | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_LEFT_30 | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "left_30_01", NULL);

	_animation[WT_UP] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_UP]->addFrameRect(eID::WALL_TURRET, "up_01", "up_02", "up_03", NULL);
	_animation[WT_UP | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_UP | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "up_01", NULL);

	_animation[WT_RIGHT_30] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_RIGHT_30]->addFrameRect(eID::WALL_TURRET, "right_30_01", "right_30_02", "right_30_03", NULL);
	_animation[WT_RIGHT_30 | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_RIGHT_30 | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "right_30_01", NULL);

	_animation[WT_RIGHT_60] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_RIGHT_60]->addFrameRect(eID::WALL_TURRET, "right_60_01", "right_60_02", "right_60_03", NULL);
	_animation[WT_RIGHT_60 | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_RIGHT_60 | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "right_60_01", NULL);

	_animation[WT_RIGHT] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_RIGHT]->addFrameRect(eID::WALL_TURRET, "right_90_01", "right_90_02", "right_90_03", NULL);
	_animation[WT_RIGHT | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_RIGHT | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "right_90_01", NULL);

	_animation[WT_RIGHT_120] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_RIGHT_120]->addFrameRect(eID::WALL_TURRET, "right_120_01", "right_120_02", "right_120_03", NULL);
	_animation[WT_RIGHT_120 | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_RIGHT_120 | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "right_120_01", NULL);

	_animation[WT_RIGHT_150] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_RIGHT_150]->addFrameRect(eID::WALL_TURRET, "right_150_01", "right_150_02", "right_150_03", NULL);
	_animation[WT_RIGHT_150 | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_RIGHT_150 | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "right_150_01", NULL);

	_animation[WT_DOWN] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_DOWN]->addFrameRect(eID::WALL_TURRET, "down_01", "down_02", "down_03", NULL);
	_animation[WT_DOWN | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_DOWN | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "down_01", NULL);

	_animation[WT_LEFT_150] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_LEFT_150]->addFrameRect(eID::WALL_TURRET, "left_150_01", "left_150_02", "left_150_03", NULL);
	_animation[WT_LEFT_150 | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_LEFT_150 | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "left_150_01", NULL);

	_animation[WT_LEFT_120] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_LEFT_120]->addFrameRect(eID::WALL_TURRET, "left_120_01", "left_120_02", "left_120_03", NULL);
	_animation[WT_LEFT_120 | WT_SHOOTING] = new Animation(_sprite, WALL_TURRET_ANIMATION_SPEED);
	_animation[WT_LEFT_120 | WT_SHOOTING]->addFrameRect(eID::WALL_TURRET, "left_120_01", NULL);


	_explosion = NULL;
	_stopwatch = new StopWatch();
	_loopwatch1 = new StopWatch();
	this->setHitpoint(WALL_TURRET_HITPOINT);
	this->setScore(WALL_TURRET_SCORE);

}
void WallTurret::update(float deltatime)
{
	if (!isRange())
	{
		this->setWTStatus(eWT_Status::WT_CLOSE);
	}
	this->rangeAttack();
	this->checkIfOutofScreen();

	if (this->getHitpoint() <= 0)
	{
		if (_explosion == NULL)
			initExplosion();
		else {
			updateExplosion(deltatime);
			if (this->_explosion->getStatus() == eStatus::DESTROY)
				this->setStatus(DESTROY);
		}
	}

	if (this->getStatus() == eStatus::DESTROY || checkClose==true)
		return;

	if (!_animation[WT_CLOSE]->isAnimate()&&this->isRange())
	{
		if (_loopwatch1->isTimeLoop(800.0f))
		{
			calculateBillangle();
		}

		if (_billAngle >= -105 && _billAngle < -75)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_NORMAL);
			_shootingAngle = -90;
		}
		else if (_billAngle >= -75 && _billAngle < -45)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_LEFT_60);
			_shootingAngle = -60;
		}
		else if (_billAngle >= -45 && _billAngle < -15)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_LEFT_30);
			_shootingAngle = -30;
		}
		else if (_billAngle >= -15 && _billAngle < 15)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_UP);
			_shootingAngle = 0;
		}
		else if (_billAngle >= 15 && _billAngle < 45)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_RIGHT_30);
			_shootingAngle = 30;
		}
		else if (_billAngle >= 45 && _billAngle < 75)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_RIGHT_60);
			_shootingAngle = 60;
		}
		else if (_billAngle >= 75 && _billAngle < 105)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_RIGHT);
			_shootingAngle = 90;
		}
		else if (_billAngle >= 105 && _billAngle < 135)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_RIGHT_120);
			_shootingAngle = 120;
		}
		else if (_billAngle >= 135 && _billAngle < 165)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_RIGHT_150);
			_shootingAngle = 150;
		}

		else if (_billAngle >= 165 || _billAngle < -165)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_DOWN);
			_shootingAngle = 180;
		}
		else if (_billAngle >= -165 && _billAngle < -135)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_LEFT_150);
			_shootingAngle = -150;
		}

		else if (_billAngle >= -135 && _billAngle < -105)
		{
			this->setScale(SCALE_FACTOR);
			this->setWTStatus(WT_LEFT_120);
			_shootingAngle = -120;
		}
		this->addStatus(eWT_Status::WT_SHOOTING);
	}


	if (_stopwatch->isStopWatch(WALL_TURRET_SHOOTING_DELAY))
	{
		if (this->isInStatus(WT_SHOOTING))
		{
			shoot();
		}
		_stopwatch->restart();
	}

	_animation[this->getWT_Status()]->update(deltatime);
}
void WallTurret::draw(LPD3DXSPRITE spritehandle, Viewport* viewport)
{
	if (_explosion != NULL)
		_explosion->draw(spritehandle, viewport);

	if (this->getStatus() == eStatus::DESTROY)
		return;
	if (this->getHitpoint() > 0 && this->getStatus() != eStatus::WAITING)
	{

		this->_sprite->render(spritehandle, viewport);
		_animation[this->getWT_Status()]->draw(spritehandle, viewport);
	}
}
void WallTurret::release()
{
	for (auto ani : _animation)
	{
		delete ani.second;
	}
	_animation.clear();

	if (_explosion != NULL)
		this->_explosion->release();
	SAFE_DELETE(_explosion);
	SAFE_DELETE(this->_sprite);
}


void WallTurret::setStatus(eStatus status)
{
	if (_status != status)
		_status = status;
}
void WallTurret::setWTStatus(eWT_Status wtstatus)
{
	if (_wtstatus != wtstatus)
		_wtstatus = wtstatus;
}

eWT_Status WallTurret::getWT_Status()
{
	return this->_wtstatus;
}

void WallTurret::initExplosion()
{
	_explosion = new Explosion(2);
	_explosion->init();
	_explosion->setScale(SCALE_FACTOR);
	((Explosion*)_explosion)->setPosition(this->_sprite->getPosition());
}
void WallTurret::updateExplosion(float deltatime)
{
	_explosion->update(deltatime);
}
void WallTurret::addStatus(eStatus status)
{
	this->setStatus(eStatus(this->getStatus() | status));
}
void WallTurret::addStatus(eWT_Status wtstatus)
{
	this->setWTStatus(eWT_Status(this->getWT_Status() | wtstatus));
}

void WallTurret::removeStatus(eStatus status)
{
	this->setStatus(eStatus(this->getWT_Status() & ~status));
}
void WallTurret::removeStatus(eWT_Status wtstatus)
{
	this->setWTStatus(eWT_Status(this->getWT_Status() & ~wtstatus));
}

bool WallTurret::isInStatus(eStatus status)
{
	return (this->getStatus() & status) == status;
}
bool WallTurret::isInStatus(eWT_Status wtstatus)
{
	return (this->getWT_Status() & wtstatus) == wtstatus;
}

void WallTurret::setBillAngle(float angle)
{
	this->_billAngle = angle;
}

float WallTurret::getBillAngle()
{
	return _billAngle;
}
void WallTurret::setShootingAngle(float angle)
{
	this->_shootingAngle = angle;
}

float WallTurret::getShootingAngle()
{
	return _shootingAngle;
}


RECT WallTurret::getBounding()
{
	auto baseBound = BaseObject::getBounding();
	baseBound.left += 7 * this->getScale().x;
	baseBound.right -= 7 * this->getScale().x;
	baseBound.top -= 7 * this->getScale().y;
	baseBound.bottom += 7 * this->getScale().y;
	return baseBound;
}
void WallTurret::shoot()
{
	float angle = this->getShootingAngle();
	//float mx = this->getPosition().x;
	//float my = this->getPosition().y;

	auto pos = this->getPosition();

	//auto pos = this->getPosition() - GVector2(0, this->getSprite()->getFrameHeight()/2);

	if (this->isInStatus(WT_NORMAL))
	{
		pos.x -= this->getSprite()->getFrameWidth() / 2;
	}
	if (this->isInStatus(WT_UP))
	{
		pos.y += this->getSprite()->getFrameHeight() / 2;
	}
	if (this->isInStatus(WT_RIGHT))
	{
		pos.x += this->getSprite()->getFrameWidth() / 2;
	}
	if (this->isInStatus(WT_DOWN))
	{
		pos.y -= this->getSprite()->getFrameHeight() / 2;
	}
	else if (this->isInStatus(WT_RIGHT_30))
	{
		pos.x += 8 * abs(this->getSprite()->getScale().x);
		pos.y += this->getSprite()->getFrameHeight() / 2;
	}
	else if (this->isInStatus(WT_LEFT_30))
	{
		pos.x -= 8 * abs(this->getSprite()->getScale().x);
		pos.y += this->getSprite()->getFrameHeight() / 2;
	}
	else if (this->isInStatus(WT_RIGHT_60))
	{
		pos.x += 14 * abs(this->getSprite()->getScale().x);
		pos.y += 9 * abs(this->getSprite()->getScale().x);
	}
	else if (this->isInStatus(WT_LEFT_60))
	{
		pos.x -= 14 * abs(this->getSprite()->getScale().x);
		pos.y += 9 * abs(this->getSprite()->getScale().x);
	}
	else if (this->isInStatus(WT_RIGHT_120))
	{
		pos.x += 14 * abs(this->getSprite()->getScale().x);
		pos.y -= 9 * abs(this->getSprite()->getScale().x);
	}
	else if (this->isInStatus(WT_LEFT_120))
	{
		pos.x -= 14 * abs(this->getSprite()->getScale().x);
		pos.y -= 9 * abs(this->getSprite()->getScale().x);
	}
	else if (this->isInStatus(WT_RIGHT_150))
	{
		pos.x += 8 * abs(this->getSprite()->getScale().x);
		pos.y -= this->getSprite()->getFrameHeight() / 2;
	}
	else if (this->isInStatus(WT_LEFT_150))
	{
		pos.x -= 8 * abs(this->getSprite()->getScale().x);
		pos.y -= this->getSprite()->getFrameHeight() / 2;
	}
	BulletManager::insertBullet(new Bullet(pos, (eBulletType)(ENEMY_BULLET | NORMAL_BULLET), angle));
}
void WallTurret::calculateBillangle()
{
	auto bill = ((PlayScene*)SceneManager::getInstance()->getCurrentScene())->getBill();
	float dx = this->getPosition().x - bill->getPosition().x;
	float dy = this->getPosition().y - (bill->getPosition().y + bill->getSprite()->getFrameHeight() / 2);
	if (dx > 0 && dy < 0)
		_billAngle = -atan(dx / (abs(dy))) * 180 / PI;
	else if (dx < 0 && dy < 0)
		_billAngle = atan(abs(dx) / abs(dy)) * 180 / PI;
	else if (dx>0 && dy>0)
		_billAngle = atan(dx / dy) * 180 / PI - 180;
	else if (dx<0 && dy>0)
		_billAngle = -atan(abs(dx) / dy) * 180 / PI + 180;
}
void WallTurret::rangeAttack()
{
	auto viewport = ((PlayScene*)SceneManager::getInstance()->getCurrentScene())->getViewport();
	RECT screenBound = viewport->getBounding();
	RECT thisBound = BaseObject::getBounding();
	if (screenBound.left>thisBound.left || screenBound.bottom>thisBound.bottom)
	{
		checkClose = true;
	}
	else if (viewport->isContains(thisBound))
	{
		checkClose = false;	
	}
	this->setWTStatus(eWT_Status::WT_CLOSE);
	this->setStatus(eStatus::HIDDEN);
}
bool WallTurret::isRange()
{
	auto viewport = ((PlayScene*)SceneManager::getInstance()->getCurrentScene())->getViewport();
	RECT screenBound = viewport->getBounding();
	RECT thisBound = BaseObject::getBounding();

	if (screenBound.right - thisBound.right <= 5 && screenBound.bottom==0 || screenBound.top - thisBound.top <=30 && screenBound.left==0)
	{
		return false;
	}
	return true;
}
void WallTurret::checkIfOutofScreen()
{
	auto viewport = ((PlayScene*)SceneManager::getInstance()->getCurrentScene())->getViewport();
	RECT screenBound = viewport->getBounding();
	RECT thisBound = BaseObject::getBounding();

	if (thisBound.right < screenBound.left || thisBound.top < screenBound.bottom)
	{
		this->setStatus(eStatus::DESTROY);
	}
}