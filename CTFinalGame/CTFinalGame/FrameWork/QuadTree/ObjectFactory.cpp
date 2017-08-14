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
		int id, x, y, width, height, dir= 0;
		eID enumID;
		myfile >> stt;
		myfile >> id;
		myfile >> x;
		myfile >> y;
		myfile >> width;
		myfile >> height;
		myfile >> dir;

		try
		{
			enumID = (eID)id;
		}
		catch (exception e)
		{
			continue;
		}
		BaseObject* obj = getObjectById(enumID, x, y, width, height, dir);
		if (obj != NULL)
			(*listobject)[stt] = obj;
	}
	return listobject;
}

BaseObject* ObjectFactory::getObjectById(eID id, int x, int y, int width, int height, int dir)
{
	switch (id)
	{
	case REDCANNON:
		return getRedCannon(x, y);
	case SOLDIER:
		return getSoldier(x, y, dir, 0);
	case FALCON_B:
		return getFalcon(id, x, y);
	case FALCON_F:
		return getFalcon(id, x, y);
	case FALCON_L:
		return getFalcon(id, x, y);
	case FALCON_M:
		return getFalcon(id, x, y);
	case FALCON_R:
		return getFalcon(id, x, y);
	case FALCON_S:
		return getFalcon(id, x, y);
	case AIRCRAFT_B:
		return getAirCraft(id, x, y);
	case AIRCRAFT_F:
		return getAirCraft(id, x, y);
	case AIRCRAFT_L:
		return getAirCraft(id, x, y);
	case AIRCRAFT_M:
		return getAirCraft(id, x, y);
	case AIRCRAFT_R:
		return getAirCraft(id, x, y);
	case AIRCRAFT_S:
		return getAirCraft(id, x, y);
	case RIFLEMAN:
		return getRifleMan(id, x, y);
	case RIFLEMANHIDDEN:
		return getRifleMan(id, x, y);
	case BRIDGE:
		return getBridge(x, y);
	case LAND:
		return getLand(id, x, y, width, height, dir);
	case LANDWATER:
		return getLand(id, x, y, width, height, dir);
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

BaseObject* ObjectFactory::getLand(eID id, int x, int y, int width, int height, int dir)
{
	eDirection direction;
	eLandType typeLand;
	bool canJumpDown=false;

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
	eStatus _status;
	if (id == RIFLEMAN)
	{
		_status = eStatus::NORMAL;
	}
	if (id == RIFLEMANHIDDEN)
	{
		_status = eStatus::HIDDEN;
	}
	
	auto rifleMan = new Rifleman(_status, GVector2(x, y));
	rifleMan->init();

	return rifleMan;
}

BaseObject * ObjectFactory::getSoldier(int x, int y, int dir, int canShoot)
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
	auto wallturret = new WallTurret(status, GVector2(x + 32, y - 32));
	wallturret->init();

	return wallturret;
}

BaseObject* ObjectFactory::getBridge(int x, int y)
{
	// X Cộng 16 Y Trừ 16 vì gameobject set origin là center
	auto bridge = new Bridge(GVector2(x + 16, y - 16));
	bridge->init();

	return bridge;
}

BaseObject * ObjectFactory::getAirCraft(eID id, int x, int y)
{
	GVector2 pos, hVeloc, ampl;
	float freq;
	eAirCraftType type;

	pos.x = x;
	pos.y = y;

	// type
	if (id == AIRCRAFT_B)
	{
		type = eAirCraftType::B;
	}
	else if (id == AIRCRAFT_F)
	{
		type = eAirCraftType::F;
	}
	else if (id == AIRCRAFT_L)
	{
		type = eAirCraftType::L;
	}
	else if (id == AIRCRAFT_M)
	{
		type = eAirCraftType::M;
	}
	else if (id == AIRCRAFT_R)
	{
		type = eAirCraftType::R;
	}
	else
	{
		type = eAirCraftType::S;
	}

	// ampl
	ampl = AIRCRAFT_AMPLITUDE;

	// hVeloc
	hVeloc = AIRCRAFT_HORIZONTAL_VELOC;

	// freq
	freq = AIRCRAFT_FREQUENCY;

	auto airCraft = new AirCraft(pos, hVeloc, ampl, freq, type);

	airCraft->init();

	return airCraft;
}

BaseObject* ObjectFactory::getFalcon(eID id, int x, int y)
{
	int type;

	if (id==FALCON_B)
	{
		type = eAirCraftType::R;
	}
	else if (id == FALCON_F)
	{
		type = eAirCraftType::F;
	}
	else if (id == FALCON_L)
	{
		type = eAirCraftType::L;
	}
	else if (id == FALCON_M)
	{
		type = eAirCraftType::M;
	}
	else if (id == FALCON_R)
	{
		type = eAirCraftType::R;
	}
	else
	{
		type = eAirCraftType::S;
	}
	auto falcon = new Falcon(GVector2(x + 32, y - 32), (eAirCraftType)type);

	falcon->init();
	return falcon;
}