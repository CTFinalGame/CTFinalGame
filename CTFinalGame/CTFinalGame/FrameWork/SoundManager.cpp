

#include "SoundManager.h"

SoundManager* SoundManager::_instance;

SoundManager* SoundManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new SoundManager();
	}
	return _instance;
}

void SoundManager::loadSound(HWND hWnd)
{
	// Khởi tạo CSoundManager.
	DirectSound_Init(hWnd);

	CSound* sound = nullptr;

	sound = LoadSound("Resource//sound//BG_Map1.wav");
	_listSound[eSoundId::BACKGROUND_STAGE1] = sound;

	sound = LoadSound("Resource//sound//BG_Map2.wav");
	_listSound[eSoundId::BACKGROUND_STAGE2] = sound;

	sound = LoadSound("Resource//sound//BG_Map3.wav");
	_listSound[eSoundId::BACKGROUND_STAGE3] = sound;

	sound = LoadSound("Resource//sound//Attack_Cannon.wav");
	_listSound[eSoundId::ATTACK_CANNON] = sound;

	sound = LoadSound("Resource//sound//Base_Bullet.wav");
	_listSound[eSoundId::BASE_BULLET_FIRE] = sound;

	sound = LoadSound("Resource//sound//FBullet.wav");
	_listSound[eSoundId::FBULLET_FIRE] = sound;

	sound = LoadSound("Resource//sound//SBullet.wav");
	_listSound[eSoundId::SBULLET_FIRE] = sound;

	sound = LoadSound("Resource//sound//MBullet.wav");
	_listSound[eSoundId::MBULLET_FIRE] = sound;

	sound = LoadSound("Resource//sound//LBullet.wav");
	_listSound[eSoundId::LBULLET_FIRE] = sound;

	sound = LoadSound("Resource//sound//Boom.wav");
	_listSound[eSoundId::BOOM] = sound;

	sound = LoadSound("Resource//sound//Boss_1.wav");
	_listSound[eSoundId::BOSS_SOUNG1] = sound;

	sound = LoadSound("Resource//sound//Dead.wav");
	_listSound[eSoundId::DEAD] = sound;

	sound = LoadSound("Resource//sound//Destroy_Boss.wav");
	_listSound[eSoundId::DESTROY_BOSS] = sound;

	sound = LoadSound("Resource//sound//Destroy_Bridge.wav");
	_listSound[eSoundId::DESTROY_BRIDGE] = sound;

	sound = LoadSound("Resource//sound//Destroy_Enemy.wav");
	_listSound[eSoundId::DESTROY_ENEMY] = sound;

	sound = LoadSound("Resource//sound//Bridge_Burn.wav");
	_listSound[eSoundId::BRIDGE_BURN] = sound;

	sound = LoadSound("Resource//sound//Eat_Item.wav");
	_listSound[eSoundId::EAT_ITEM] = sound;

	sound = LoadSound("Resource//sound//Enemy_Attack.wav");
	_listSound[eSoundId::ENEMY_ATTACK] = sound;

	sound = LoadSound("Resource//sound//Game_Over.wav");
	_listSound[eSoundId::GAME_OVER] = sound;

	sound = LoadSound("Resource//sound//GoBoss.wav");
	_listSound[eSoundId::GAMEOVER_BOSS] = sound;

	sound = LoadSound("Resource//sound//Intro.wav");
	_listSound[eSoundId::INTRO] = sound;

	sound = LoadSound("Resource//sound//Jump.wav");
	_listSound[eSoundId::JUMP_SOUND] = sound;

	sound = LoadSound("Resource//sound//Pass_Boss.wav");
	_listSound[eSoundId::PASS_BOSS] = sound;

	sound = LoadSound("Resource//sound//WinGame.wav");
	_listSound[eSoundId::WINGAME] = sound;
}

bool SoundManager::IsPlaying(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		return sound->IsSoundPlaying();
	}
	return false;
}

void SoundManager::Play(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		PlaySound(sound);
		this->currentSound = sound;
	}
}
void SoundManager::PlayLoop(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		sound->Play(0, DSBPLAY_LOOPING);
	}
}
void SoundManager::Stop(eSoundId soundid)
{
	auto sound = _listSound[soundid];
	if (sound != nullptr)
	{
		StopSound(sound);
	}
}

SoundManager::SoundManager()
{
	currentSound = nullptr;
}

SoundManager::~SoundManager()
{
}