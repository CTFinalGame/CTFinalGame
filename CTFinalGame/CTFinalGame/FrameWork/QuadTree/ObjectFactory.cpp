#include "ObjectFactory.h"

ObjectFactory::ObjectFactory()
{

}

ObjectFactory::~ObjectFactory()
{

}

map<string, BaseObject*>* ObjectFactory::getMapObjectFromFile(const string path)
{
	map<string, BaseObject*>* listobject = new map<string, BaseObject*>();
	ifstream myfile(path);
	while (!myfile.eof())
	{
		string stt;
		int id, x, y, width, height, type, dir= 0;
		eID enumID;
		myfile >> stt;
		myfile >> id;
		myfile >> x;
		myfile >> y;
		myfile >> width;
		myfile >> height;
		myfile >> dir;
		type = 0;
		//if (id == 12)
		//{
		//	type = 0;
		//}
		//else if (id==100)
		//{
		//	type = 1;
		//}

		try
		{
			enumID = (eID)id;
		}
		catch (exception e)
		{
			continue;
		}
		BaseObject* obj = getObjectById(enumID, x, y, width, height, type, dir);
		if (obj != NULL)
			(*listobject)[stt] = obj;
	}
	return listobject;
}

BaseObject* ObjectFactory::getObjectById(eID id, int x, int y, int width, int height, int type, int dir)
{
	switch (id)
	{
	case REDCANNON:
		return getRedCannon(x, y);
	case SOLDIER:
		return getSoldier(x, y, type, dir, 0);
	case FALCON:
		//return getFalcon(node);
	case AIRCRAFT:
		//return getAirCraft(node);
	case RIFLEMAN:
		return getRifleMan(id, x, y);
	case RIFLEMANHIDDEN:
		return getRifleMan(id, x, y);
	case BRIDGE:
		return getBridge(x, y);
	case LAND:
		return getLand(id, x, y, width, height, type, dir);
	case LANDWATER:
		return getLand(id, x, y, width, height, type, dir);
	case WALL_TURRET:
		return getWallTurret(x, y);
	case CREATOR:
		//return getCreator(node);
	case BOSS_STAGE1:
		//return getGreatWall(node);
	case ROCKFLY:
		//return getRockFly(node);
	case ROCKFALL:
		//return getRockFall(node);
	case SCUBASOLDIER:
		//return getScubaSoldier(node);
	case FIRE:
		//return getFire(node);
	case SHADOW_BEAST:
		//return getShadowBeast(node);
	default:
		return nullptr;
		break;
	}
	return nullptr;
}

BaseObject* ObjectFactory::getLand(eID id, int x, int y, int width, int height, int type, int dir)
{
	eDirection direction;
	eLandType typeLand;
	bool canJumpDown=false;
	typeLand = (eLandType)type;
	if (id == LAND)
	{
		typeLand = eLandType::GRASS;
	}
	else	if (id == LANDWATER)
	{
		typeLand = eLandType::WATER;
	}

	direction = (eDirection)dir;

	if (typeLand == GRASS)
	{
		canJumpDown = true;
	}

	auto land = new Land(x, y, width, height, direction, typeLand);
	land->init();
	land->enableJump(canJumpDown);

	return land;
}

BaseObject* ObjectFactory::getRifleMan(eID id, int x, int y)
{
	eStatus _status = eStatus::NORMAL;
	if (id == RIFLEMANHIDDEN)
	{
		_status = eStatus::HIDDEN;
	}
	
	auto rifleMan = new Rifleman(_status, GVector2(x, y));
	rifleMan->init();

	return rifleMan;
}

BaseObject * ObjectFactory::getSoldier(int x, int y, int type, int dir, int canShoot)
{
	eStatus status;
	bool _canShoot = false;

	status = eStatus::RUNNING;

	if (canShoot == 1)
	{
		_canShoot = true;
	}

	auto soldier = new Soldier(status, GVector2(x, y), dir, _canShoot);
	soldier->init();

	return soldier;
}

BaseObject * ObjectFactory::getRedCannon(int x, int y)
{
	eStatus status = eStatus::WAITING; 
	auto cannon = new Cannon(status, GVector2(x +32, y-32));
	cannon->init();

	return cannon;
}

BaseObject * ObjectFactory::getWallTurret(int x, int y)
{
	eStatus status = eStatus::WAITING;
	auto cannon = new WallTurret(status, GVector2(x + 32, y - 32));
	cannon->init();

	return cannon;
}

BaseObject* ObjectFactory::getBridge(int x, int y)
{
	// X Cộng 16 Y Trừ 16 vì gameobject set origin là center
	auto bridge = new Bridge(GVector2(x + 16, y - 16));
	bridge->init();

	return bridge;
}
