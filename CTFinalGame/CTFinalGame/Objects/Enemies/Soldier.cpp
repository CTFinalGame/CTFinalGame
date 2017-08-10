#include "Soldier.h"
Soldier::Soldier(eStatus status, GVector2 pos, int direction) : BaseEnemy(eID::SOLDIER) {
	_sprite = SpriteManager::getInstance()->getSprite(eID::SOLDIER);
	GVector2 v(direction * SOLDIER_SPEED, 0);
	GVector2 a(0, 0);
	_divingSprite = SpriteManager::getInstance()->getSprite(eID::BILL);
	_divingSprite->setFrameRect(0, 0, 17.0f, 15.0f);
	_divingSprite->setScale(SCALE_FACTOR);
	_divingSprite->setOrigin(GVector2(0.5f, 0.0f));
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(pos);
	this->setScale(SCALE_FACTOR);
	this->setScaleX(-direction * SCALE_FACTOR);
	this->_canShoot = false;
}

Soldier::Soldier(eStatus status, float x, float y, int direction) : BaseEnemy(eID::SOLDIER) {
	_sprite = SpriteManager::getInstance()->getSprite(eID::SOLDIER);
	GVector2 pos(x, y);
	GVector2 v(direction * SOLDIER_SPEED, 0);
	GVector2 a(0, 0);
	_divingSprite = SpriteManager::getInstance()->getSprite(eID::BILL);
	_divingSprite->setFrameRect(0, 0, 17.0f, 15.0f);
	_divingSprite->setScale(SCALE_FACTOR);
	_divingSprite->setOrigin(GVector2(0.5f, 0.0f));
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(pos);
	this->setScale(SCALE_FACTOR);
	this->setScaleX(-direction * SCALE_FACTOR);
	this->_canShoot = false;
}

Soldier::Soldier(eStatus status, GVector2 pos, int direction, bool shoot) : BaseEnemy(eID::SOLDIER) {
	_sprite = SpriteManager::getInstance()->getSprite(eID::SOLDIER);
	GVector2 v(direction * SOLDIER_SPEED, 0);
	GVector2 a(0, 0);
	_divingSprite = SpriteManager::getInstance()->getSprite(eID::BILL);
	_divingSprite->setFrameRect(0, 0, 17.0f, 15.0f);
	_divingSprite->setScale(SCALE_FACTOR);
	_divingSprite->setOrigin(GVector2(0.5f, 0.0f));
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(pos);
	this->setScale(SCALE_FACTOR);
	this->setScaleX(-direction * SCALE_FACTOR);
	this->_canShoot = shoot;
}

Soldier::Soldier(eStatus status, float x, float y, int direction, bool shoot) : BaseEnemy(eID::SOLDIER) {
	_sprite = SpriteManager::getInstance()->getSprite(eID::SOLDIER);
	GVector2 pos(x, y);
	GVector2 v(direction * SOLDIER_SPEED, 0);
	GVector2 a(0, 0);
	_divingSprite = SpriteManager::getInstance()->getSprite(eID::BILL);
	_divingSprite->setFrameRect(0, 0, 17.0f, 15.0f);
	_divingSprite->setScale(SCALE_FACTOR);
	_divingSprite->setOrigin(GVector2(0.5f, 0.0f));
	this->_listComponent.insert(pair<string, IComponent*>("Movement", new Movement(a, v, this->_sprite)));
	this->setStatus(status);
	this->setPosition(pos);
	this->setScale(SCALE_FACTOR);
	this->setScaleX(-direction * SCALE_FACTOR);
	this->_canShoot = shoot;
}

Soldier::~Soldier() {}

void Soldier::init()
{

	this->setHitpoint(SOLDIER_HITPOINT);
	auto collisionBody = new CollisionBody(this);
	_listComponent["CollisionBody"] = collisionBody;

	__hook(&CollisionBody::onCollisionBegin, collisionBody, &Soldier::onCollisionBegin);
	__hook(&CollisionBody::onCollisionEnd, collisionBody, &Soldier::onCollisionEnd);


	this->_listComponent.insert(pair<string, IComponent*>("Gravity", new Gravity(GVector2(0, -ENEMY_GRAVITY), (Movement*)(this->getComponent("Movement")))));
	_animations[RUNNING] = new Animation(_sprite, 0.15f);
	_animations[RUNNING]->addFrameRect(eID::SOLDIER, "run_01", "run_02", "run_03", "run_04", "run_05", "run_06", NULL);
		
	_animations[JUMPING] = new Animation(_sprite, 0.15f);
	_animations[JUMPING]->addFrameRect(eID::SOLDIER, "jump_01", NULL);

	_animations[FALLING] = new Animation(_sprite, 0.15f);
	_animations[FALLING]->addFrameRect(eID::SOLDIER, "jump_01", NULL);

	_animations[LAYING_DOWN] = new Animation(_sprite, 0.15f);
	_animations[LAYING_DOWN]->addFrameRect(eID::SOLDIER, "lay_down_01", NULL);

	_animations[DYING] = new Animation(_sprite, 0.15f);
	_animations[DYING]->addFrameRect(eID::SOLDIER, "die_01", NULL);

	_animations[DIVING] = new Animation(_divingSprite, 0.15f, false);
	_animations[DIVING]->addFrameRect(eID::BILL, "swim_begin", "diving", "swim_begin", NULL);
	_stopwatch = new StopWatch();
	_loopwatch = new StopWatch();
	_shoot = new StopWatch();
	_checkShoot = new StopWatch();
}

void Soldier::draw(LPD3DXSPRITE spritehandle, Viewport* viewport)
{
	if (_explosion != NULL)
		_explosion->draw(spritehandle, viewport);
	if (this->getStatus() == eStatus::DESTROY || this->getStatus() == eStatus::WAITING || this->getStatus() == eStatus::BURST)
		return;

	_animations[this->getStatus()]->draw(spritehandle, viewport);

}

void Soldier::release()
{
	for (auto component : _listComponent)
	{
		delete component.second;
	}
	_listComponent.clear();
	if (this->_explosion != NULL)
		this->_explosion->release();
	SAFE_DELETE(this->_explosion);
	SAFE_DELETE(this->_sprite);
}

IComponent* Soldier::getComponent(string componentName)
{
	return _listComponent.find(componentName)->second;
}

void Soldier::update(float deltatime)
{
	if (_explosion != NULL)
		_explosion->update(deltatime);

	if (this->getStatus() == eStatus::BURST)
	{
		if (_explosion == nullptr)
		{
			auto pos = this->getPosition();
			_explosion = new Explosion(1);
			_explosion->init();
			_explosion->setScale(SCALE_FACTOR);
			_explosion->setPosition(pos);
		}
		else if (_explosion->getStatus() == eStatus::DESTROY)
		{
			this->setStatus(eStatus::DESTROY);
		}
		return;
	}

	if (this->getStatus() == eStatus::DIVING)
	{
		if (_animations[DIVING]->getIndex() == 2)
		{
			this->setStatus(eStatus::DESTROY);
		}
	}

	if (this->getStatus() == DESTROY || this->getStatus() == WAITING)
		return;

	Gravity *gravity = (Gravity*)this->getComponent("Gravity");
	Movement *movement = (Movement*)this->getComponent("Movement");

	if (this->getHitpoint() <= 0 && this->getStatus() != DYING)
	{
		this->setStatus(eStatus::DYING);
		this->die();
	}

	if (this->getStatus() == eStatus::DYING) {

		if (_stopwatch->isStopWatch(200))
		{
			movement->setVelocity(GVector2(0, 0));
			this->setStatus(eStatus::BURST);
			return;
		}
	}

	if (this->getStatus() == eStatus::BURST)
	{
		if (_explosion == nullptr)
		{
			auto pos = this->getPosition();
			_explosion = new Explosion(1);
			_explosion->init();
			_explosion->setScale(SCALE_FACTOR);
			_explosion->setPosition(pos);
		}
		else if (_explosion->getStatus() == eStatus::DESTROY)
		{
			this->setStatus(eStatus::DESTROY);
		}
	}
	for (auto it : _listComponent)
	{
		it.second->update(deltatime);
	}

	if (this->getStatus() != DESTROY)
		_animations[this->getStatus()]->update(deltatime);
}
void Soldier::onCollisionBegin(CollisionEventArg* collision_eventt) {
	eID objectID = collision_eventt->_otherObject->getId();
	switch (objectID)
	{
	case eID::BILL:
	{
					  if (collision_eventt->_otherObject->isInStatus(eStatus::DYING) == false)
					  {
						  collision_eventt->_otherObject->setStatus(eStatus::DYING);
						  ((Bill*)collision_eventt->_otherObject)->die();
					  }
					  break;
	}
	default:
		break;
	}
}

void Soldier::onCollisionEnd(CollisionEventArg* collision_event) {
	if (this->getStatus() == eStatus::DESTROY)
		return;
	eID objectID = collision_event->_otherObject->getId();
	switch (objectID)
	{
	case eID::LAND:
	case eID::BRIDGE:
		break;
	default:
		break;
	}
}


float Soldier::checkCollision(BaseObject * object, float dt)
{
	if (this->getStatus() == eStatus::DESTROY || this->getStatus() == eStatus::DIVING || this->isInStatus(eStatus::DYING) || this->isInStatus(eStatus::BURST))
		return 0.0f;

	auto collisionBody = (CollisionBody*)_listComponent["CollisionBody"];
	eID objectId = object->getId();
	eDirection direction;
	if (objectId == eID::LAND)
	{
		eLandType land = ((Land*)object)->getType();

		if (collisionBody->checkCollision(object, direction, dt))
		{
			if (land == eLandType::GRASS || land == eLandType::BRIDGELAND)
			{
				bool flagend = false;
				if (direction == eDirection::TOP && this->getVelocity().y < 0)
				{
					auto gravity = (Gravity*)this->_listComponent["Gravity"];
					auto movement = (Movement*)this->_listComponent["Movement"];
					movement->setVelocity(GVector2(movement->getVelocity().x, 0));
					gravity->setStatus(eGravityStatus::SHALLOWED);

					if (this->getStatus() != eStatus::SHOOTING)
						this->setStatus(eStatus::RUNNING);
					prevObject = object;
				}
			}
			else if (land == eLandType::WATER)
			{
				auto gravity = (Gravity*)this->_listComponent["Gravity"];
				auto movement = (Movement*)this->_listComponent["Movement"];

				gravity->setStatus(eGravityStatus::SHALLOWED);
				movement->setVelocity(VECTOR2ZERO);

				this->setStatus(DIVING);
				this->setPositionY(object->getPositionY());
				_divingSprite->setPosition(this->getPosition());
			}
		}
		else if (prevObject == object)
		{
			auto gravity = (Gravity*)this->_listComponent["Gravity"];
			gravity->setStatus(eGravityStatus::FALLING__DOWN);

			int chance = rand() % 5;
			if (chance == 0)
			{
				jump();
				auto gravity = (Gravity*)this->_listComponent["Gravity"];
				gravity->setStatus(eGravityStatus::FALLING__DOWN);
			}
			else
			{
				Movement* movement = (Movement*)this->getComponent("Movement");
				movement->setVelocity(GVector2(-movement->getVelocity().x, movement->getVelocity().y));
				this->setScaleX(-this->getScale().x);
			}

			prevObject = nullptr;
		}
	}
	else
	{

		collisionBody->checkCollision(object, dt, false);

	}
	return 0.0f;

}
void Soldier::setPosition(GVector2 pos)
{
	_sprite->setPosition(pos);
}
void Soldier::changeDirection()
{

	_sprite->setScaleX(-this->getScale().x);
	Movement *movement = (Movement*)this->getComponent("Movement");
	movement->setVelocity(GVector2(-movement->getVelocity().x, 0));
}
void Soldier::jump()
{
	this->setStatus(FALLING);
	Movement *move = (Movement*)this->getComponent("Movement");
	move->setVelocity(GVector2(move->getVelocity().x, SOLDIER_JUMP_VELOCITY));
}

GVector2 Soldier::getVelocity()
{
	auto move = (Movement*)this->_listComponent["Movement"];
	return move->getVelocity();
}

void Soldier::die() {
	Gravity *gravity = (Gravity*)this->getComponent("Gravity");
	gravity->setStatus(eGravityStatus::SHALLOWED);
	Movement *movement = (Movement*)this->getComponent("Movement");
	movement->setVelocity(GVector2(0, 200));
}

void Soldier::shoot()
{
	float angle = -90 * this->getScale().x / 2;
	auto pos = this->getPosition();
	if (this->isInStatus(SHOOTING))
	{
		pos.x += this->getScale().x < 0 ? this->getSprite()->getFrameWidth() / 2 : -this->getSprite()->getFrameWidth() / 2;
		pos.y += this->getSprite()->getFrameHeight() / 4.5;
	}
	else if (this->isInStatus(LAYING_DOWN))
	{
		pos.x += this->getScale().x < 0 ? this->getSprite()->getFrameWidth() / 2 : -this->getSprite()->getFrameWidth() / 2;
		pos.y -= this->getSprite()->getFrameHeight() / 4.5;
	}
}
