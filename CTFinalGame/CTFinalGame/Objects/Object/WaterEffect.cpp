﻿#include "WaterEffect.h"

WaterEffect::WaterEffect(GVector2 position) : BaseObject(eID::WATEREFFECT)
{
	this->_beginPosition = position;
}


WaterEffect::~WaterEffect() {

};

void WaterEffect::init()
{
	this->_sprite = SpriteManager::getInstance()->getSprite(eID::WATEREFFECT);
	this->_sprite->setScale(SCALE_FACTOR);
	this->_sprite->setPosition(this->_beginPosition);
	_animations = new Animation(_sprite, 0.12f);
	_animations->addFrameRect(eID::WATEREFFECT, "water_01", "water_02", "water_03", NULL);
}


void WaterEffect::checkifOutofScreen()
{
	if (this->getStatus() != eStatus::NORMAL)
		return;
	auto viewport = ((PlayScene*)SceneManager::getInstance()->getCurrentScene())->getViewport();
	RECT screenBound = viewport->getBounding();
	RECT thisBound = this->getBounding();
	GVector2 position = this->getPosition();
	if (thisBound.right < screenBound.left)
	{
		this->setStatus(eStatus::DESTROY);
	}
}

void WaterEffect::update(float deltatime)
{
	checkifOutofScreen();
	auto status = this->getStatus();

	switch (status)
	{
	case DESTROY:
		return;
	case NORMAL:
	{
		Viewport* viewport = ((PlayScene*)SceneManager::getInstance()->getCurrentScene())->getViewport();
		RECT screenBound = viewport->getBounding();
		GVector2 viewportposition = viewport->getPositionWorld();
		if (BaseObject::getBounding().right > screenBound.right || BaseObject::getBounding().top < viewportposition.y - WINDOW_HEIGHT)
		{
			break;
		}
		if (this->getBounding().right > screenBound.right)
		{
			break;
		}
		_animations->update(deltatime);
		break;
	}
	
	default:
		break;
	}
}


void WaterEffect::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{

	if (this->getStatus() == eStatus::DESTROY)
		return;

	if (this->getStatus() == eStatus::NORMAL)
		_animations->draw(spriteHandle, viewport);

}

void WaterEffect::release()
{
	SAFE_DELETE(this->_animations);
	SAFE_DELETE(this->_sprite);
}


