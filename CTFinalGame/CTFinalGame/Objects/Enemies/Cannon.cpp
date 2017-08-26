#include"Cannon.h"

Cannon::Cannon(eStatus status, GVector2 position) :BaseEnemy(eID::REDCANNON)
{
		_sprite = SpriteManager::getInstance()->getSprite(eID::REDCANNON);

		_sprite->setFrameRect(0, 0, 32, 32);
		this->setPosition(position);
		this->setStatus(status);
		this->setWTStatus(eWT_Status::WT_NORMAL);
}

Cannon::Cannon(eStatus status, float x, float y) :BaseEnemy(eID::REDCANNON)
{
		_sprite = SpriteManager::getInstance()->getSprite(eID::REDCANNON);
		_sprite->setFrameRect(0, 0, 32, 32);
		GVector2 pos(x, y);
		this->setPosition(pos);
		this->setStatus(status);
		this->setWTStatus(eWT_Status::WT_NORMAL);
}
Cannon::Cannon(eWT_Status wtstatus, GVector2 position) :BaseEnemy(eID::REDCANNON)
{
		_sprite = SpriteManager::getInstance()->getSprite(eID::REDCANNON);
		_sprite->setFrameRect(0, 0, 32, 32);
		this->setPosition(position);
		this->setWTStatus(wtstatus);
}
Cannon::Cannon(eWT_Status wtstatus, float x, float y) :BaseEnemy(eID::REDCANNON)
{
		_sprite = SpriteManager::getInstance()->getSprite(eID::REDCANNON);
		_sprite->setFrameRect(0, 0, 32, 32);
		GVector2 pos(x, y);
		this->setPosition(pos);
		this->setWTStatus(wtstatus);
}
Cannon::~Cannon()
{

}
void Cannon::init()
{

	this->setScale(SCALE_FACTOR);

	_animation[WT_APPEAR] = new Animation(_sprite, CANNON_APPEAR_SPEED);
	_animation[WT_APPEAR]->addFrameRect(eID::REDCANNON, "appear_01", "appear_02", "appear_03", "appear_04", "appear_05", "appear_06", NULL);
	_animation[WT_APPEAR]->setLoop(false);

	_animation[WT_CLOSE] = new Animation(_sprite, CANNON_APPEAR_SPEED);
	_animation[WT_CLOSE]->addFrameRect(eID::REDCANNON, "appear_06", "appear_05", "appear_04", "appear_03", "appear_02", "appear_01", NULL);
	_animation[WT_CLOSE]->setLoop(false);

	_animation[WT_NORMAL] = new Animation(_sprite, CANNON_ANIMATION_SPEED);
	_animation[WT_NORMAL]->addFrameRect(eID::REDCANNON, "run_01", "run_02", "run_03", NULL);

	_animation[WT_NORMAL | WT_SHOOTING] = new Animation(_sprite, CANNON_ANIMATION_SPEED);
	_animation[WT_NORMAL | WT_SHOOTING]->addFrameRect(eID::REDCANNON, "run_01", "run_02","run_03", NULL);

	_animation[WT_LEFT_60] = new Animation(_sprite, CANNON_ANIMATION_SPEED);
	_animation[WT_LEFT_60]->addFrameRect(eID::REDCANNON, "run_04", "run_05", "run_06", NULL);

	_animation[WT_LEFT_60 | WT_SHOOTING] = new Animation(_sprite, CANNON_ANIMATION_SPEED);
	_animation[WT_LEFT_60 | WT_SHOOTING]->addFrameRect(eID::REDCANNON, "run_04","run_05","run_06", NULL);

	_animation[WT_LEFT_30] = new Animation(_sprite, CANNON_ANIMATION_SPEED);
	_animation[WT_LEFT_30]->addFrameRect(eID::REDCANNON, "run_07", "run_08", "run_09", NULL);

	_animation[WT_LEFT_30 | WT_SHOOTING] = new Animation(_sprite, CANNON_ANIMATION_SPEED);
	_animation[WT_LEFT_30 | WT_SHOOTING]->addFrameRect(eID::REDCANNON,"run_07", "run_08", "run_09", NULL);

	_explosion = NULL;
	_stopwatch = new StopWatch();
	_loopwatch2 = new StopWatch();
	this->setHitpoint(CANNON_HITPOINT);
	this->setScore(CANNON_SCORE);
}
void Cannon::update(float deltatime)
{
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
	if (this->getStatus() == eStatus::DESTROY)
		return;
	if (_animation[WT_APPEAR]->isAnimate() == true)
	{
		_billAngle = -90;
	}

	if (_animation[WT_CLOSE]->isAnimate() == false)
	{
			this->setStatus(eStatus::DESTROY);	
	}
	if (!_animation[WT_APPEAR]->isAnimate() && this->isRange())
	{	
			if (_loopwatch2->isTimeLoop(2000.0f))
			{
				calculateBillangle();
			}
			if ((_billAngle >= -90 && _billAngle < -75))
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
			else if (_billAngle >= -45 && _billAngle < 0)
			{
				this->setScale(SCALE_FACTOR);
				this->setWTStatus(WT_LEFT_30);
				_shootingAngle = -30;
			}
		this->addStatus(eWT_Status::WT_SHOOTING);
	}
		if (this->getWT_Status() != eWT_Status::WT_APPEAR && this->getWT_Status() != eWT_Status::WT_CLOSE)
		{
			if (bullet >= 3)
			{
				bullet = 0;
				delay1 = CANNON_SHOOTING_DELAY;
				this->removeStatus(SHOOTING);
			}
			if (_stopwatch->isTimeLoop(delay1))
			{
				this->addStatus(SHOOTING);
				shoot();
				bullet++;
				delay1 = 300.0f;
			}
		}
	

	_animation[this->getWT_Status()]->update(deltatime);
}
void Cannon::draw(LPD3DXSPRITE spritehandle, Viewport* viewport)
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
void Cannon::release()
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


void Cannon::setStatus(eStatus status)
{
	if (_status != status)
		_status = status;
}
void Cannon::setWTStatus(eWT_Status wtstatus)
{
	if (_wtstatus != wtstatus)
		_wtstatus = wtstatus;
}

eWT_Status Cannon::getWT_Status()
{
	return this->_wtstatus;
}

void Cannon::initExplosion()
{
	_explosion = new Explosion(2);
	_explosion->init();
	_explosion->setScale(SCALE_FACTOR);
	((Explosion*)_explosion)->setPosition(this->_sprite->getPosition());
}
void Cannon::updateExplosion(float deltatime)
{
	_explosion->update(deltatime);
}
void Cannon::addStatus(eStatus status)
{
	this->setStatus(eStatus(this->getStatus() | status));
}
void Cannon::addStatus(eWT_Status wtstatus)
{
	this->setWTStatus(eWT_Status(this->getWT_Status() | wtstatus));
}

void Cannon::removeStatus(eStatus status)
{
	this->setStatus(eStatus(this->getWT_Status() & ~status));
}
void Cannon::removeStatus(eWT_Status wtstatus)
{
	this->setWTStatus(eWT_Status(this->getWT_Status() & ~wtstatus));
}

bool Cannon::isInStatus(eStatus status)
{
	return (this->getStatus() & status) == status;
}
bool Cannon::isInStatus(eWT_Status wtstatus)
{
	return (this->getWT_Status() & wtstatus) == wtstatus;
}

void Cannon::setBillAngle(float angle)
{
	this->_billAngle = angle;
}

float Cannon::getBillAngle()
{
	return _billAngle;
}
void Cannon::setShootingAngle(float angle)
{
	this->_shootingAngle = angle;
}

float Cannon::getShootingAngle()
{
	return _shootingAngle;
}


void Cannon::shoot()
{
	float angle = this->getShootingAngle();

	auto pos = this->getPosition();


	if (this->isInStatus(WT_NORMAL))
	{
		pos.x -= this->getSprite()->getFrameWidth()/2;
	}
	else if (this->isInStatus(WT_LEFT_30))
	{
		pos.x -= 8 * abs(this->getSprite()->getScale().x);
		pos.y += this->getSprite()->getFrameHeight() / 2;
	}
	else if (this->isInStatus(WT_LEFT_60))
	{
		pos.x -= 14 * abs(this->getSprite()->getScale().x);
		pos.y += 9 * abs(this->getSprite()->getScale().x);
	}

	
	BulletManager::insertBullet(new Bullet(pos, (eBulletType)(ENEMY_BULLET | NORMAL_BULLET), angle));
}
void Cannon::calculateBillangle()
{
	auto bill = ((PlayScene*)SceneManager::getInstance()->getCurrentScene())->getBill();
	float dx = this->getPosition().x - bill->getPosition().x;
	float dy = this->getPosition().y - (bill->getPosition().y + bill->getSprite()->getFrameHeight() / 2);

		if (dx > 0 && dy < 0)
			_billAngle = -atan(dx / abs(dy)) * 180 / PI;
		else if (dx<0 && dy<0)
			_billAngle = -30;
		else _billAngle = -90;
}
void Cannon::rangeAttack()
{
	auto viewport = ((PlayScene*)SceneManager::getInstance()->getCurrentScene())->getViewport();
	RECT screenBound = viewport->getBounding();
	RECT thisBound = BaseObject::getBounding();
	if (screenBound.left>thisBound.left || screenBound.bottom>thisBound.bottom)
	{
		this->setWTStatus(eWT_Status::WT_CLOSE);
		this->setStatus(eStatus::HIDDEN);
	}
	else if (viewport->isContains(thisBound))
	{
		this->setWTStatus(eWT_Status::WT_APPEAR);
		this->setStatus(eStatus::HIDDEN);
	}
}
bool Cannon::isRange()
{
	auto viewport = ((PlayScene*)SceneManager::getInstance()->getCurrentScene())->getViewport();
	RECT screenBound = viewport->getBounding();
	RECT thisBound = BaseObject::getBounding();

	if (screenBound.left > thisBound.left || screenBound.bottom > thisBound.bottom)
	{
		return false;
	}
	return true;
}
void Cannon::checkIfOutofScreen()
{
	auto viewport = ((PlayScene*)SceneManager::getInstance()->getCurrentScene())->getViewport();
	RECT screenBound = viewport->getBounding();
	RECT thisBound = BaseObject::getBounding();

	if (thisBound.right < screenBound.left || thisBound.top < screenBound.bottom)
	{
		this->setStatus(eStatus::DESTROY);
	}
}