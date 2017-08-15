﻿#include "Bill.h"
#include "../../FrameWork/Scene/PlayScene.h"
Bill::Bill(int life) : BaseObject(eID::BILL)
{
	_canJumpDown = true;
	_lifeNum = life;
}
Bill::~Bill()
{

}

void Bill::init()
{
	__hook(&InputController::__eventkeyPressed, _input, &Bill::onKeyPressed);
	__hook(&InputController::__eventkeyReleased, _input, &Bill::onKeyReleased);

	_sprite = SpriteManager::getInstance()->getSprite(eID::BILL);
	_sprite->setFrameRect(SpriteManager::getInstance()->getSourceRect(eID::BILL, "normal_01"));
	_sprite->setZIndex(1.0f);
	auto movement = new Movement(GVector2(0, 0), GVector2(0, 0), _sprite);
	_componentList["Movement"] = movement;
	_componentList["Gravity"] = new Gravity(GVector2(0, -GRAVITY), movement);
	auto collisionBody = new CollisionBody(this);
	_componentList["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Bill::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Bill::onCollisionEnd);

	_animations[eStatus::NORMAL] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL]->addFrameRect(eID::BILL, "normal_01", NULL);

	_animations[eStatus::NORMAL | eStatus::SHOOTING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::NORMAL | eStatus::SHOOTING]->addFrameRect(eID::BILL, "normal_01", "normal_02", NULL);

	_animations[eStatus::RUNNING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::RUNNING]->addFrameRect(eID::BILL, "run_01", "run_02", "run_03", "run_04", "run_05", "run_06", NULL);

	_animations[eStatus::JUMPING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::JUMPING]->addFrameRect(eID::BILL, "jump_01", "jump_02", "jump_03", NULL);

	_animations[eStatus::FALLING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::FALLING]->addFrameRect(eID::BILL, "run_03", NULL);

	_animations[eStatus::LAYING_DOWN] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LAYING_DOWN]->addFrameRect(eID::BILL, "lay_down_01", NULL);

	_animations[eStatus::LOOKING_UP] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP]->addFrameRect(eID::BILL, "shot_up_01", NULL);

	_animations[eStatus::LOOKING_UP | eStatus::SHOOTING] = new Animation(_sprite, 0.1f);
	_animations[eStatus::LOOKING_UP | eStatus::SHOOTING]->addFrameRect(eID::BILL, "shot_up_01", "shot_up_02", NULL);

	_animations[eStatus::LOOKING_UP | eStatus::RUNNING] = new Animation(_sprite, 0.12f);
	_animations[eStatus::LOOKING_UP | eStatus::RUNNING]->addFrameRect(eID::BILL, "run_shot_up_01", "run_shot_up_02", "run_shot_up_03", NULL);

	_animations[eStatus::LAYING_DOWN | eStatus::RUNNING] = new Animation(_sprite, 0.12f);
	_animations[eStatus::LAYING_DOWN | eStatus::RUNNING]->addFrameRect(eID::BILL, "run_shot_down_01", "run_shot_down_02", "run_shot_down_03", NULL);

	_animations[eStatus::SHOOTING | eStatus::RUNNING] = new Animation(_sprite, 0.12f);
	_animations[eStatus::SHOOTING | eStatus::RUNNING]->addFrameRect(eID::BILL, "run_shot_01", "run_shot_02", "run_shot_03", "run_shot_01", "run_shot_02", "run_shot_03", NULL);

	_animations[eStatus::SWIMING] = new Animation(_sprite, 0.2f, false);
	_animations[eStatus::SWIMING]->addFrameRect(eID::BILL, "swim_begin", "diving", "swimming", "swimming_01", NULL);
	_animations[eStatus::SWIMING]->animateFromTo(0, 2, false);

	_animations[eStatus::DIVING] = new Animation(_sprite, 0.2f, false);
	_animations[eStatus::DIVING]->addFrameRect(eID::BILL, "swim_begin", "diving", "diving_01", NULL);
	_animations[eStatus::DIVING]->animateFromTo(0, 1, false);

	_animations[eStatus::SWIMING | RUNNING | SHOOTING] = new Animation(_sprite, 0.2f, false);
	_animations[eStatus::SWIMING | RUNNING | SHOOTING]->addFrameRect(eID::BILL, "swim_begin", "swimming_shot", "swimming_shot_01", NULL);
	_animations[eStatus::SWIMING | RUNNING | SHOOTING]->animateFromTo(0, 1, false);

	_animations[eStatus::SWIMING | SHOOTING] = new Animation(_sprite, 0.2f, false);
	_animations[eStatus::SWIMING | SHOOTING]->addFrameRect(eID::BILL, "swim_begin", "swimming_shot", "swimming_shot_01", NULL);
	_animations[eStatus::SWIMING | SHOOTING]->animateFromTo(0, 1, false);

	_animations[eStatus::SWIMING | RUNNING | LOOKING_UP | SHOOTING] = new Animation(_sprite, 0.2f, false);
	_animations[eStatus::SWIMING | RUNNING | LOOKING_UP | SHOOTING]->addFrameRect(eID::BILL, "swim_begin", "swimming_shotup", "swimming_shotup_01", NULL);
	_animations[eStatus::SWIMING | RUNNING | LOOKING_UP | SHOOTING]->animateFromTo(0, 1, false);

	_animations[eStatus::SWIMING | LOOKING_UP | SHOOTING] = new Animation(_sprite, 0.2f, false);
	_animations[eStatus::SWIMING | LOOKING_UP | SHOOTING]->addFrameRect(eID::BILL, "swim_begin", "swimming_shotup_stand", "swimming_shotup_stand_01", NULL);
	_animations[eStatus::SWIMING | LOOKING_UP | SHOOTING]->animateFromTo(0, 1, false);

	_animations[eStatus::DYING] = new Animation(_sprite, 0.2f, false);
	_animations[eStatus::DYING]->addFrameRect(eID::BILL, "dead_01", "dead_02", "dead_03", "dead_04", NULL);

	this->setOrigin(GVector2(0.5f, 0.0f));
	this->setStatus(eStatus::FALLING);

	// create stopWatch
	_stopWatch = new StopWatch();
	_shootAnimateStopWatch = new StopWatch();
	_shootStopWatch = new StopWatch();


	_isHolding = false;

	this->resetValues();
	// UI
	// tạo ở đây cho dễ cập nhật khi chết, khỏi trỏ lung tung
	_lifeUI = new LifeUI(GVector2(20, 30), this->getLifeNumber());
	_lifeUI->init();
}

void Bill::update(float deltatime)
{
	// đang protect thì đếm xuống
	if (_protectTime > 0)
	{
		_protectTime -= deltatime;
	}
	this->checkPosition();

	this->updateStatus(deltatime);

	this->updateCurrentAnimateIndex();

	_animations[_currentAnimateIndex]->update(deltatime);
	// update component để sau cùng để sửa bên trên sau đó nó cập nhật đúng
	// Huỷ các bullet đã hết hiệu lực.
	this->deleteBullet();
	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		it->second->update(deltatime);
	}
	for (auto bullet : _listBullets)
	{
		bullet->update(deltatime);
	}
}

void Bill::resetValues()
{
	this->setScale(SCALE_FACTOR);
	_preObject = nullptr;
	_protectTime = PROTECT_TIME;
	//_touchKill = false;
	_movingSpeed = BILL_MOVE_SPEED;
	_currentGun = eBulletType::NORMAL_BULLET;
	this->setMaxBullet(MAX_BULLET);
	this->setShootSpeed(SHOOT_SPEED);

	for (auto animate : _animations)
	{
		animate.second->setColorFlash(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void Bill::updateInput(float dt)
{
	if (this->isInStatus(eStatus::DYING))
		return;
	if (_input->isKeyDown(DIK_Z))
	{
		if (_isHolding)
		{
			if (((_currentGun & R_BULLET) == R_BULLET || (_currentGun & M_BULLET) == M_BULLET) && _stopWatch->isStopWatch(_shootSpeed))
			{
				this->addStatus(eStatus::SHOOTING);
				shoot();
				_stopWatch->restart();
				_shootAnimateStopWatch->restart();
			}
		}
		// delay animate shooting
	}
	if (_shootAnimateStopWatch->isStopWatch(400))
	{
		this->removeStatus(eStatus::SHOOTING);
	}

}

void Bill::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	_animations[_currentAnimateIndex]->draw(spriteHandle, viewport);

	for (auto it = _listBullets.begin(); it != _listBullets.end(); it++)
	{
		(*it)->draw(spriteHandle, viewport);
	}
	// DRAW Life
	_lifeUI->draw(spriteHandle, viewport);
}

void Bill::release()
{
	for (auto it = _animations.begin(); it != _animations.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_animations.clear();

	for (auto it = _componentList.begin(); it != _componentList.end(); it++)
	{
		SAFE_DELETE(it->second);
	}
	_componentList.clear();

	SAFE_DELETE(_sprite);
	SAFE_DELETE(_lifeUI);
	this->unhookinputevent();

}

void Bill::unhookinputevent()
{
	if (_input != nullptr)
		__unhook(_input);

}
void Bill::onKeyPressed(KeyEventArg* key_event)
{
	if (this->isInStatus(eStatus::DYING))
		return;
	switch (key_event->_key)
	{
	case DIK_X:
	{

				  if (!this->isInStatus(eStatus::LAYING_DOWN) || this->isInStatus(eStatus::MOVING_LEFT) || this->isInStatus(eStatus::MOVING_RIGHT))
				  {
					  if (!this->isInStatus(eStatus::SWIMING))
						  this->jump();
				  }
				  else
				  {
					  if (_canJumpDown &&!this->isInStatus(eStatus::JUMPING) && !this->isInStatus(eStatus::FALLING))
					  {
						  this->removeStatus(eStatus::SHOOTING);
						  this->addStatus(eStatus::JUMPING);
						  this->addStatus(eStatus::FALLING);
					  }

				  }
				  break;
	}
	case DIK_LEFT:
	{
					 if (this->isInStatus(eStatus::DIVING))
						 return;

					 this->removeStatus(eStatus::MOVING_RIGHT);
					 this->addStatus(eStatus::MOVING_LEFT);

					 break;
	}
	case DIK_RIGHT:
	{
					  if (this->isInStatus(eStatus::DIVING))
						  return;

					  this->removeStatus(eStatus::MOVING_LEFT);
					  this->addStatus(eStatus::MOVING_RIGHT);
					  break;
	}
	case DIK_DOWN:
	{
					 if (!this->isInStatus(eStatus::SWIMING))
					 {
						 this->removeStatus(eStatus::LOOKING_UP);
						 this->addStatus(eStatus::LAYING_DOWN);
					 }
					 else
					 {
						 this->addStatus(eStatus::DIVING);
						 this->removeStatus(eStatus::MOVING_LEFT);
						 this->removeStatus(eStatus::MOVING_RIGHT);
					 }

					 break;
	}
	case DIK_UP:
	{
				   // không có TH nằm mà bắn lên
				   if (!this->isInStatus(eStatus::LAYING_DOWN))
					   this->addStatus(eStatus::LOOKING_UP);

				   break;
	}
	case DIK_Z:
	{
				  if (this->isInStatus(eStatus::DIVING))
					  return;


				  /*this->addStatus(eStatus::SHOOTING);
				  shoot();*/
				  {
					  auto time = 85;

					  switch (_currentGun)
					  {
					  case NORMAL_BULLET:
						  time = 85;
						  break;
					  case L_BULLET:
						  time = 200;
						  break;
					  case F_BULLET:
						  time = 250;
						  break;
					  case S_BULLET:
						  time = 200;
						  break;
					  default:
						  break;
					  }

					  if (_shootStopWatch->isTimeLoop(time))
					  {
						  this->addStatus(eStatus::SHOOTING);
						  shoot();
						  _shootAnimateStopWatch->restart();
					  }
				  }

				  _isHolding = true;
				  _stopWatch->restart();

				  break;
	}
	case DIK_M:
	{
				  changeBulletType(eAirCraftType::M);
				  break;
	}
	case DIK_S:
	{
				  changeBulletType(eAirCraftType::S);
				  break;
	}
	case DIK_F:
	{
				  changeBulletType(eAirCraftType::F);
				  break;
	}
	case DIK_L:
	{
				  _lifeNum++;
				  _lifeUI->setLifeNumber(_lifeNum);
				  break;
	}
	default:
		break;
	}
}

void Bill::onKeyReleased(KeyEventArg * key_event)
{
	if (this->isInStatus(eStatus::DYING))
		return;

	switch (key_event->_key)
	{
	case DIK_RIGHT:
	{
					  this->removeStatus(eStatus::MOVING_RIGHT);
					  break;
	}
	case DIK_LEFT:
	{
					 this->removeStatus(eStatus::MOVING_LEFT);
					 break;
	}
	case DIK_DOWN:
	{
					 this->removeStatus(eStatus::LAYING_DOWN);
					 this->removeStatus(eStatus::DIVING);
					 break;
	}
	case DIK_UP:
	{
				   this->removeStatus(eStatus::LOOKING_UP);
				   break;
	}
	case DIK_Z:
	{
				  //  this->removeStatus(eStatus::SHOOTING);
				  _isHolding = false;
				  break;

	}
	default:
		break;
	}
}
void Bill::checkPosition()
{
	if (this->isInStatus(eStatus::DYING))
		return;

	auto viewport = SceneManager::getInstance()->getCurrentScene()->getViewport();
	GVector2 viewport_position = viewport->getPositionWorld();

	if (this->getPositionY() < viewport_position.y - WINDOW_HEIGHT)
	{
		if (_status != eStatus::DYING)
			_status = eStatus::DYING;

		if (_protectTime > 0)
			_protectTime = 0;

		this->die();
	}
}

void Bill::standing()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(0, 0));
	this->removeStatus(eStatus::JUMPING);
	this->removeStatus(eStatus::FALLING);
}

void Bill::moveLeft()
{
	// viewport
	auto viewport = SceneManager::getInstance()->getCurrentScene()->getViewport();
	GVector2 viewportPosition = viewport->getPositionWorld();
	float billPositionX = this->getPositionX();
	auto halfwidth = this->getSprite()->getFrameWidth() * this->getSprite()->getOrigin().x;
	// Không cho đi vượt cạnh trái
	if (billPositionX + halfwidth - _movingSpeed * 0.33 <= viewportPosition.x) // hard code
	{
		this->setPositionX(viewportPosition.x + halfwidth);
		return;
	}
	if (this->getScale().x > 0)
		this->setScaleX(this->getScale().x * (-1));

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(-_movingSpeed, move->getVelocity().y));
}

void Bill::moveRight()
{
	if (this->getScale().x < 0)
		this->setScaleX(this->getScale().x * (-1));

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(_movingSpeed, move->getVelocity().y));
}

void Bill::jump()
{
	if (this->isInStatus(eStatus::JUMPING) || this->isInStatus(eStatus::FALLING))
		return;

	this->addStatus(eStatus::JUMPING);

	//if (!this->isInStatus(eStatus::LAYING_DOWN))

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(move->getVelocity().x, BILL_JUMP_VEL));


	auto g = (Gravity*)this->_componentList["Gravity"];
	g->setGravity(GVector2(0, -GRAVITY));
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void Bill::layDown()
{
	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(0, move->getVelocity().y));
}

void Bill::falling()
{
	auto gravity = (Gravity*)this->_componentList["Gravity"];
	gravity->setStatus(eGravityStatus::FALLING__DOWN);
}


void Bill::revive()
{
	auto viewportPos = SceneManager::getInstance()->getCurrentScene()->getViewport()->getPositionWorld();

	if (auto scene = dynamic_cast<PlayScene*>(SceneManager::getInstance()->getCurrentScene()))
	{
		this->setPosition(viewportPos.x, WINDOW_HEIGHT);
	}
	else
	{
		this->setPosition(viewportPos.x + WINDOW_WIDTH / 2, viewportPos.y - WINDOW_HEIGHT / 2);
	}

	// reset value
	this->setStatus(eStatus::JUMPING);
	this->resetValues();

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(100, 0));

	// trừ mạng
	this->setLifeNumber(_lifeNum - 1);

	// cập nhật UI
	_lifeUI->setLifeNumber(_lifeNum);
}

// Từ thuộc tính currentGun mà chọn loại đoạn trả về thích hợp
void Bill::die()
{
	if (_protectTime > 0)
		return;
	if (this->isInStatus(eStatus::DIVING))
		return;

	if (!this->isInStatus(eStatus::DYING)){
		this->setStatus(eStatus::DYING);
	}

	auto move = (Movement*)this->_componentList["Movement"];
	move->setVelocity(GVector2(-BILL_MOVE_SPEED * (this->getScale().x / SCALE_FACTOR), BILL_JUMP_VEL));

	auto g = (Gravity*)this->_componentList["Gravity"];
	g->setStatus(eGravityStatus::FALLING__DOWN);
}

void Bill::swimming()
{
	this->removeStatus(eStatus::FALLING);
	this->addStatus(eStatus::SWIMING);

	_animations[eStatus::SWIMING]->animateFromTo(2, 3, true);
	_animations[eStatus::SWIMING]->setTimeAnimate(0.2f);

	_animations[eStatus::DIVING]->animateFromTo(1, 2, true);
	_animations[eStatus::DIVING]->setTimeAnimate(0.2f);

	_animations[eStatus::SWIMING | SHOOTING]->animateFromTo(1, 2, true);
	_animations[eStatus::SWIMING | SHOOTING]->setTimeAnimate(0.2f);

	_animations[eStatus::SWIMING | RUNNING | SHOOTING]->animateFromTo(1, 2, true);
	_animations[eStatus::SWIMING | RUNNING | SHOOTING]->setTimeAnimate(0.2f);

	_animations[eStatus::SWIMING | RUNNING | SHOOTING | LOOKING_UP]->animateFromTo(1, 2, true);
	_animations[eStatus::SWIMING | RUNNING | SHOOTING | LOOKING_UP]->setTimeAnimate(0.2f);

	_animations[eStatus::SWIMING | LOOKING_UP | SHOOTING]->animateFromTo(1, 2, true);
	_animations[eStatus::SWIMING | LOOKING_UP | SHOOTING]->setTimeAnimate(0.2f);

	{
		// cập nhật animate
		if (this->isInStatus(eStatus::LAYING_DOWN))
		{
			this->removeStatus(eStatus::LAYING_DOWN);
			this->removeStatus(eStatus::MOVING_LEFT);
			this->removeStatus(eStatus::MOVING_RIGHT);

			this->setStatus(eStatus::DIVING);
			this->addStatus(eStatus::SWIMING);

			_animations[eStatus::DIVING]->restart();
		}
		else if (this->isInStatus(eStatus(MOVING_LEFT | LOOKING_UP | SHOOTING)) || this->isInStatus(eStatus(MOVING_RIGHT | LOOKING_UP | SHOOTING)))
		{
			_animations[eStatus::SWIMING | RUNNING | SHOOTING | LOOKING_UP]->restart();
		}
		else if ((this->isInStatus(eStatus(MOVING_LEFT | SHOOTING)) || this->isInStatus(eStatus(MOVING_RIGHT | SHOOTING))))
		{
			_animations[eStatus::SWIMING | RUNNING | SHOOTING]->restart();
		}
		else if (this->isInStatus(eStatus(LOOKING_UP | SHOOTING)))
		{
			_animations[eStatus::SWIMING | LOOKING_UP | SHOOTING]->restart();
		}
		else if (this->isInStatus(eStatus(SHOOTING)))
		{
			_animations[eStatus::SWIMING | SHOOTING]->restart();
		}
		else
		{
			_animations[eStatus::SWIMING]->restart();
		}
	}
}
void Bill::setStatus(eStatus status)
{
	// lặn / đang được bảo vệ  ko có chết
	if ((status & eStatus::DYING) == eStatus::DYING && (this->isInStatus(eStatus::DIVING) || _protectTime > 0))
		return;

	_status = status;
}

RECT Bill::getBounding()
{
	int offset = 10;

	RECT bound = _sprite->getBounding();

	if (!this->isInStatus(eStatus::JUMPING) || !this->isInStatus(eStatus::SWIMING))
	{
		if ((_currentAnimateIndex & LOOKING_UP) == LOOKING_UP)
		{
			bound.top -= offset * 2.0f;
		}
		else
		{
			bound.top -= offset;
		}

		if (this->getScale().x > 0)
		{
			bound.right -= offset;
			bound.left += offset * 0.2f;
		}
		else
		{
			bound.left += offset;
			bound.right -= offset * 0.2f;
		}
	}

	return bound;
}

GVector2 Bill::getVelocity()
{
	auto move = (Movement*)this->_componentList["Movement"];
	return move->getVelocity();
}

void Bill::updateStatus(float dt)
{
	if (this->isInStatus(eStatus::DYING))
	{
		if (_lifeNum < 0)
		{
			// thua cnmr
			return;
		}

		// còn mạng thì hồi sinh
		if (_reviveStopWatch == nullptr)
			_reviveStopWatch = new StopWatch();

		if (!_animations[eStatus::DYING]->isAnimate() && _reviveStopWatch->isStopWatch(REVIVE_TIME))
		{
			this->revive();
			SAFE_DELETE(_reviveStopWatch);
		}

		return;
	}

	if ((this->getStatus() & eStatus::MOVING_LEFT) == eStatus::MOVING_LEFT)
	{
		this->moveLeft();
	}
	else if ((this->getStatus() & eStatus::MOVING_RIGHT) == eStatus::MOVING_RIGHT)
	{
		this->moveRight();
	}
	else if ((this->getStatus() & eStatus::LAYING_DOWN) == eStatus::LAYING_DOWN)
	{
		this->layDown();
	}
	else if ((this->getStatus() & eStatus::FALLING) == eStatus::FALLING)
	{
		this->falling();
	}
	else if ((this->getStatus() & eStatus::JUMPING) != eStatus::JUMPING)
	{
		this->standing();
	}
}

void Bill::updateCurrentAnimateIndex()
{
	// _currentAnimateIndex là key của animate thôi nên có một số bị dư, nếu dùng chung status
	// vậy cần convert lại tương ứng với key trong animate

	if (this->isInStatus(eStatus::SHOOTING) && !this->isInStatus(eStatus::SWIMING) && (this->isInStatus(eStatus::LOOKING_UP) || this->isInStatus(eStatus::LAYING_DOWN)) && (this->isInStatus(eStatus::MOVING_LEFT) || this->isInStatus(eStatus::MOVING_RIGHT)))
	{
		// đang di chuyển mà shoot
		// animate ko có shooting nên bỏ nó ra
		_currentAnimateIndex = (eStatus)(this->getStatus() & ~(eStatus::SHOOTING));
	}
	else if (this->isInStatus(eStatus::LAYING_DOWN) && this->isInStatus(eStatus::SHOOTING) && !this->isInStatus(eStatus::FALLING))
	{
		// đang nằm và bắn
		// và ko có đang nhảy, thì animate NẰM thôi
		if (!this->isInStatus(eStatus::JUMPING))
			_currentAnimateIndex = eStatus::LAYING_DOWN;
		else
			_currentAnimateIndex = eStatus::JUMPING;
	}
	else
	{
		// trường hợp còn lại gán luôn
		_currentAnimateIndex = this->getStatus();
	}

	if ((_currentAnimateIndex & eStatus::FALLING) == eStatus::FALLING)
	{
		_currentAnimateIndex = eStatus::FALLING;

	}

	if ((_currentAnimateIndex & eStatus::HOLDING) == eStatus::HOLDING)
	{
		// không có animate HOLDING nên bỏ nó ra
		_currentAnimateIndex = (eStatus)(_currentAnimateIndex & ~(eStatus::HOLDING));
	}

	if ((_currentAnimateIndex & eStatus::MOVING_LEFT) == eStatus::MOVING_LEFT || ((_currentAnimateIndex & eStatus::MOVING_RIGHT) == eStatus::MOVING_RIGHT))
	{
		// animate move left/right xài cung 1 animate là running nên cũng bỏ nó ra
		_currentAnimateIndex = (eStatus)(_currentAnimateIndex & ~(eStatus::MOVING_LEFT | MOVING_RIGHT));
		_currentAnimateIndex = (eStatus)(_currentAnimateIndex | eStatus::RUNNING);
	}

	if ((_currentAnimateIndex & eStatus::JUMPING) == eStatus::JUMPING)
	{
		// nếu jump thì chỉ vẽ jump thôi
		_currentAnimateIndex = eStatus::JUMPING;
	}

	// đang bơi
	if ((_currentAnimateIndex & eStatus::SWIMING) == eStatus::SWIMING)
	{
		if ((_currentAnimateIndex & eStatus::SHOOTING) != eStatus::SHOOTING)
		{
			_currentAnimateIndex = eStatus::SWIMING;
		}

		if (this->isInStatus(eStatus::DIVING))
		{
			_currentAnimateIndex = eStatus::DIVING;
		}
	}

	// chết
	if (this->isInStatus(eStatus::DYING))
	{
		_currentAnimateIndex = eStatus::DYING;
	}
}

eDirection Bill::getAimingDirection()
{
	eDirection direction;

	if (this->getScale().x < 0)
		direction = eDirection::LEFT;
	else
		direction = eDirection::RIGHT;

	if (this->isInStatus(eStatus::FALLING))
		return direction;

	if (this->isInStatus(eStatus::LOOKING_UP))
	{
		if (_input->getInstance()->isKeyDown(DIK_LEFT) || _input->getInstance()->isKeyDown(DIK_RIGHT))
			direction = (eDirection)(direction | eDirection::TOP);
		else
			direction = eDirection::TOP;
	}
	else if (this->isInStatus(eStatus::LAYING_DOWN))
	{
		if (_input->getInstance()->isKeyDown(DIK_LEFT) || _input->getInstance()->isKeyDown(DIK_RIGHT))
			direction = (eDirection)(direction | eDirection::BOTTOM);
		else if (this->isInStatus(eStatus::JUMPING))
			direction = eDirection::BOTTOM;
	}

	return direction;
}

float Bill::getMovingSpeed()
{
	return _movingSpeed;
}

void safeCheckCollision(BaseObject* activeobj, BaseObject* passiveobj, float dt)
{
	if (activeobj != nullptr && passiveobj != nullptr)
	{
		activeobj->checkCollision(passiveobj, dt);
	}
}
void Bill::onCollisionBegin(CollisionEventArg * collision_arg)
{
	eID objectID = collision_arg->_otherObject->getId();
	switch (objectID)
	{
	case AIRCRAFT:
		break;
	case eID::LAND:
	case eID::BRIDGE:
	{

						break;
	}
	case eID::RIFLEMAN:
	case eID::SOLDIER:
	case eID::REDCANNON:
	case eID::WALL_TURRET:
	default:
		break;
	}
}

void Bill::onCollisionEnd(CollisionEventArg * collision_event)
{
	eID objectID = collision_event->_otherObject->getId();

	switch (objectID)
	{
	case AIRCRAFT:
		break;
	case eID::LAND:
	{
					  if (_preObject == collision_event->_otherObject)
					  {
						  // hết chạm với land là fall chứ ko có jump
						  this->removeStatus(eStatus::JUMPING);
						  _preObject = nullptr;
					  }
					  break;
	}
	case eID::BRIDGE:
		break;
	default:
		break;
	}
}
float Bill::checkCollision(BaseObject * object, float dt)
{
	if (object->getStatus() == eStatus::DESTROY || this->isInStatus(eStatus::DYING))
		return 0.0f;
	if (this == object)
		return 0.0f;

	auto collisionBody = (CollisionBody*)_componentList["CollisionBody"];
	eID objectId = object->getId();
	eDirection direction;
	if (objectId == eID::BOSS_STAGE1 &&  collisionBody->checkCollision(object, direction, dt, false))
	{
		if (direction == eDirection::LEFT)
		{
			float moveX, moveY;
			if (collisionBody->isColliding(object, moveX, moveY, dt))
			{
				collisionBody->updateTargetPosition(object, direction, false, GVector2(moveX, moveY));
			}
		}
		else
		{
			return 0.0;
		}
	}
	else
		// nếu ko phải là nhảy xuống, mới dừng gravity
	if (!this->isInStatus(eStatus(eStatus::JUMPING | eStatus::FALLING)) && collisionBody->checkCollision(object, direction, dt, false))
	{
		// kt coi chổ đứng có cho nhảy xuống ko
		if (objectId == eID::LAND || objectId ==eID::ROCKFLY)
		{

			auto land = (Land*)object;
			eLandType preType = land->getType();
			_canJumpDown = land->canJump();
			// lấy type của preObject
			if (_preObject != nullptr && _preObject->getId() == eID::LAND)
			{
				preType = ((Land*)_preObject)->getType();
			}

			if (land->getType() == eLandType::WATER)
			{
				// nếu trước đó không phải là nước thì mới cho bơi
				if (preType == eLandType::BRIDGELAND || preType == eLandType::GRASS || _preObject == nullptr)
				{
					// swim
					this->swimming();
				}

			}

			else if (this->isInStatus(eStatus::SWIMING))
			{
				if (direction == eDirection::TOP)
				{

					this->removeStatus(eStatus::SWIMING);
					this->removeStatus(eStatus::DIVING);
					this->setPositionY(object->getBounding().top);
				}
			}
			// nếu chạm top mà trừ trường hợp nhảy lên vận tốc rớt xuống nhỏ hơn 200
			if (direction == eDirection::TOP && !(this->getVelocity().y > -200 && this->isInStatus(eStatus::JUMPING)))
			{

				// vận tốc lớn hơn 200 hướng xuống => cho trường hợp nhảy từ dưới lên
				// xử lý đặc biệt, Collision body update position bt ko được
				// khi vào đây mới update position cho nó
				float moveX, moveY;
				if (collisionBody->isColliding(object, moveX, moveY, dt))
				{
						// vận tốc lớn hơn 200 hướng xuống => cho trường hợp nhảy từ dưới lên
						// xử lý đặc biệt, Collision body update position bt ko được
						// khi vào đây mới update position cho nó
						float moveX, moveY;
					if (collisionBody->isColliding(object, moveX, moveY, dt))
					{
						//this->setPositionY(object->getBounding().top);

						collisionBody->updateTargetPosition(object, direction, false, GVector2(moveX, moveY));
					}
				}

				auto gravity = (Gravity*)this->_componentList["Gravity"];
				gravity->setStatus(eGravityStatus::SHALLOWED);

				this->standing();

				_preObject = object;
			}
		}
		else{
			_canJumpDown = false;
		}
	}
	else if (_preObject == object)
	{
		// kiểm tra coi nhảy hết qua cái land cũ chưa
		// để gọi event end.
		collisionBody->checkCollision(object, dt, false);

		auto gravity = (Gravity*)this->_componentList["Gravity"];
		gravity->setStatus(eGravityStatus::FALLING__DOWN);

		if (!this->isInStatus(eStatus::JUMPING) && !this->isInStatus(eStatus::FALLING))
		{
			this->addStatus(eStatus::FALLING);
		}
	}
	if (objectId != eID::LAND && objectId)
	{
		for (auto it = _listBullets.begin(); it != _listBullets.end(); it++)
		{

			if (objectId == eID::ROCKCREATOR)
			{
				//safeCheckCollision((*it), ((RockCreator*)object)->getRock(), dt);

			}
			if (objectId == eID::SHADOW_BEAST)
			{
				/*safeCheckCollision((*it), ((ShadowBeast*)object)->getLeftArm(), dt);
				safeCheckCollision((*it), ((ShadowBeast*)object)->getRigtArm(), dt);
				safeCheckCollision((*it), ((ShadowBeast*)object)->getMouth(), dt);*/
			}
			else if (objectId == eID::BOSS_STAGE1)
			{
				safeCheckCollision((*it), ((Boss*)object)->getGun1(), dt);
				safeCheckCollision((*it), ((Boss*)object)->getGun2(), dt);
				safeCheckCollision((*it), ((Boss*)object)->getShield(), dt);
				safeCheckCollision((*it), ((Boss*)object)->getRifleMan(), dt);
			}
			else if (objectId == eID::CREATOR)
			{
				//auto children = ((ObjectCreator*)object)->getObjects();
				/*for (auto child : children)
				{
				safeCheckCollision((*it), child, dt);
				}*/
			}
			else
			{
				(*it)->checkCollision(object, dt);
			}
		}
	}
	return 0.0f;
}

void Bill::shoot()
{
	if (this->isInStatus(eStatus::DIVING))
		return;

	float angle = 0.0f;
	auto direction = getAimingDirection();
	auto pos = this->getPosition() + GVector2(0, this->getSprite()->getFrameHeight() / 2);

	if (this->isInStatus(eStatus::LAYING_DOWN))
	{
		pos.y -= 5 * this->getScale().y;
	}

	if (direction == eDirection::TOP)
	{
		angle = TOP_SHOOT_ANGLE;
		pos.x += 5 * this->getScale().x;
		pos.y += this->getSprite()->getFrameHeight() / 3;
	}
	else if (direction == (eDirection::TOP | eDirection::RIGHT))
	{
		angle = TOPRIGHT_SHOOT_ANGLE;
		pos.x += this->getSprite()->getFrameWidth() / 3;
		pos.y += 14 * this->getScale().y;
	}
	else if (direction == (eDirection::TOP | eDirection::LEFT))
	{
		angle = TOPLEFT_SHOOT_ANGLE;
		pos.x -= this->getSprite()->getFrameWidth() / 3;
		pos.y += 14 * this->getScale().y;
	}
	else if (direction == eDirection::LEFT)
	{
		angle = LEFT_SHOOT_ANGLE;
		pos.x -= this->getSprite()->getFrameWidth() / 3;
		pos.y += 5 * this->getScale().y;
	}
	else if (direction == eDirection::RIGHT)
	{
		angle = RIGHT_SHOOT_ANGLE;
		pos.x += this->getSprite()->getFrameWidth() / 3;
		pos.y += 5 * this->getScale().y;
	}
	else if (direction == (eDirection::BOTTOM | eDirection::RIGHT))
	{
		angle = BOTRIGHT_SHOOT_ANGLE;
		pos.x += this->getSprite()->getFrameWidth() / 3;
		pos.y += 5 * this->getScale().y;
	}
	else if (direction == (eDirection::BOTTOM | eDirection::LEFT))
	{
		angle = BOTLEFT_SHOOT_ANGLE;
		pos.x -= this->getSprite()->getFrameWidth() / 3;
		pos.y += 5 * this->getScale().y;
	}
	else if (direction == eDirection::BOTTOM)
	{
		angle = 180.0f;
	}

	if (this->isInStatus(eStatus::SWIMING))
		pos.y -= 8 * this->getScale().y;


	Bullet* bullet = this->getBulletFromGun(pos, angle);

	if (bullet == nullptr)
		return;

	//_listBullets.push_back(new Bullet(pos,(eBulletType)(BILL_BULLET | NORMAL_BULLET),angle));		// normalbullet -> hardcode


	_listBullets.push_back(bullet);		// normalbullet -> hardcode
	_listBullets.back()->init();


}

void Bill::deleteBullet()
{
	for (auto bullet : _listBullets)
	{
		if (bullet->getStatus() == eStatus::DESTROY)	// kiểm tra nếu là destroy thì loại khỏi list
		{
			bullet->release();
			// http://www.cplusplus.com/reference/algorithm/remove/
			auto rs1 = std::remove(_listBullets.begin(), _listBullets.end(), bullet);
			_listBullets.pop_back();			// sau khi remove thì còn một phần tử cuối cùng vôi ra. giống như dịch mảng. nên cần bỏ nó đi

			delete bullet;
			break;		// sau pop_back phần tử đi thì list bị thay đổi, nên vòng for-each không còn nguyên trạng nữa. -> break (mỗi frame chỉ remove được 1 đối tượng)
		}
	}
}

// Từ thuộc tính currentGun mà chọn loại đoạn trả về thích hợp
Bullet* Bill::getBulletFromGun(GVector2 position, float angle)
{
	Bullet* bullet = nullptr;
	if ((_currentGun & NORMAL_BULLET) == NORMAL_BULLET)
	{
		if (_listBullets.size() >= _maxBullet)
			return nullptr;

		bullet = new Bullet(position, (eBulletType)(BILL_BULLET | NORMAL_BULLET), angle);
		SoundManager::getInstance()->Play(eSoundId::BASE_BULLET_FIRE);
	}
	else if ((_currentGun & M_BULLET) == M_BULLET)
	{
		if (_listBullets.size() >= _maxBullet)
			return nullptr;

		bullet = new MBullet(position, angle);
		SoundManager::getInstance()->Play(eSoundId::MBULLET_FIRE);

	}
	else if ((_currentGun & S_BULLET) == S_BULLET)
	{
		if (_listBullets.size() >= _maxBullet)
			return nullptr;

		bullet = new SBullet(position, angle);
		SoundManager::getInstance()->Play(eSoundId::SBULLET_FIRE);
	}
	else if ((_currentGun & F_BULLET) == F_BULLET)
	{
		if (_listBullets.size() >= _maxBullet)
			return nullptr;

		bullet = new FBullet(position, angle);
		SoundManager::getInstance()->Play(eSoundId::FBULLET_FIRE);
	}

	return bullet;
}

void Bill::setMaxBullet(int number)
{
	if (number != _maxBullet)
		_maxBullet = number;
}

int Bill::getMaxBullet()
{
	return _maxBullet;
}
int Bill::getLifeNumber()
{
	return _lifeNum;
}
void Bill::setLifeNumber(int number)
{
	if (number != _lifeNum)
		_lifeNum = number;
}
void Bill::setShootSpeed(float speed)
{
	if (speed != _shootSpeed)
		_shootSpeed = speed;
}

float Bill::getShootSpeed()
{
	return _shootSpeed;
}
void Bill::changeBulletType(eAirCraftType type)
{
	SoundManager::getInstance()->Play(eSoundId::EAT_ITEM);
	switch (type)
	{
	case L:
		this->_currentGun = eBulletType::L_BULLET;
		this->setMaxBullet(-1);

		break;
	case B:
		_protectTime = 12000;
		break;
	case F:
		this->_currentGun = eBulletType::F_BULLET;
		this->setMaxBullet(2);

		break;
	case S:
		this->_currentGun = eBulletType::S_BULLET;
		this->setMaxBullet(2);

		break;
	case M:
		this->_currentGun = eBulletType::M_BULLET;
		this->setMaxBullet(6);

		break;
	case R:
		if (this->_currentGun != eBulletType::L_BULLET)
		{
			this->_currentGun = eBulletType(this->_currentGun | eBulletType::R_BULLET);
			// this->setMaxBullet(-1);
			this->setShootSpeed(SHOOT_SPEED);
		}

		break;
	default:
		break;
	}
}