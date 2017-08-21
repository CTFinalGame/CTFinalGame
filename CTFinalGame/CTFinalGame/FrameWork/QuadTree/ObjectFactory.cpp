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
		return getBossStage1(x, y, height);
	case ROCKFLY:
		return getRockFly(x, y, width);
	case ROCKFALL:
		return getRockFall(x, y);
	case SCUBASOLDIER:
		return getScubaSoldier(x, y);
	case FIRE:
		return getFire(x, y);
	case SHADOW_BEAST:
		return getBossStage3(x, y);
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
	eStatus _status = eStatus::NORMAL;
	if (id == RIFLEMAN)
	{
		y -= 20;
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

BaseObject* ObjectFactory::getBossStage1(int x, int y, int height)
{
	auto boss = new Boss(GVector2(x, y-height), height);
	boss->init();
	return boss;
}

BaseObject* ObjectFactory::getRockFall(int x, int y)
{
	//auto rockfall = new RockFall(GVector2(x + 32, y - 32));
	auto rockfall = new RockCreator(GVector2(x + 32, y - 32));
	rockfall->init();
	return rockfall;
}

BaseObject* ObjectFactory::getScubaSoldier(int x, int y)
{
	auto scubasoldier = new ScubaSoldier(GVector2(x+32, y-8));
	scubasoldier->init();
	return scubasoldier;
}

BaseObject* ObjectFactory::getFire(int x, int y)
{
	y -= 8 * SCALE_FACTOR;
	auto fire = new Fire(GVector2(x, y));
	fire->init();
	return fire;
}

BaseObject* ObjectFactory::getRockFly(int x, int y, int width)
{
	x -= 32;
	width += 64;
	y -= 32;

	auto rockfly = new RockFly(GVector2(x, y), GVector2(x + width, y));
	rockfly->init();
	return rockfly;
}

BaseObject* ObjectFactory::getBossStage3(int x, int y)
{
	auto shadowbeast = new ShadowBeast(GVector2(x, y));
	shadowbeast->init();
	return shadowbeast;
}
