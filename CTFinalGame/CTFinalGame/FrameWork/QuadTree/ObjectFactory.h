#ifndef __OBJECT_READER__
#define __OBJECT_READER__

#include "../define.h"
#include "../../Objects/Enemies/Rifleman.h"
//#include "../objects/Enemies/ObjectCreator.h"
#include "../../Objects/BaseObject.h"
#include "../../Objects/Enemies/RockCreator.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();
	static map<string, BaseObject*>* getMapObjectFromFile(const string path);
private:
	static BaseObject* getObjectById(eID id, int x, int y, int width, int height, int dir);
	static BaseObject* getLand(eID id, int x, int y, int width, int height, int dir);
	static BaseObject* getRifleMan(eID id, int x, int y);
	static BaseObject* getSoldier(int x, int y, int dir, int canShoot);
	static BaseObject* getRedCannon(int x, int y);
	static BaseObject* getWallTurret(int x, int y);
	static BaseObject* getAirCraft(eID id, int x, int y);
	static BaseObject* getBossStage1(int x, int y, int height);
	//static BaseObject* getCreator(xml_node node);
	static BaseObject* getBridge(int x, int y);
	static BaseObject* getFalcon(eID id, int x, int y);	
	static BaseObject* getRockFly(int x, int y, int width);
	static BaseObject* getRockFall(int x, int y);
	static BaseObject* getScubaSoldier(int x, int y);
	static BaseObject* getFire(int x, int y);
	static BaseObject* getBossStage3(int x, int y);
};

#endif // !__OBJECT_READER__
