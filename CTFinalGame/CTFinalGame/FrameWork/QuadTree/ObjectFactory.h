#ifndef __OBJECT_READER__
#define __OBJECT_READER__

#include "../define.h"
#include "../../Objects/Enemies/Rifleman.h"
//#include "../objects/Enemies/ObjectCreator.h"
#include "../../Objects/BaseObject.h"
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
	static BaseObject* getObjectById(eID id, int x, int y, int width, int height, int type, int dir);
	static BaseObject* getLand(eID id, int x, int y, int width, int height, int type, int dir);
	static BaseObject* getRifleMan(int x, int y, int status);
	static BaseObject* getSoldier(int x, int y, int status, int dir, int canShoot);
	static BaseObject* getRedCannon(int x, int y);
	static BaseObject* getWallTurret(int x, int y);
	//static BaseObject* getAirCraft(xml_node node);
	//static BaseObject* getCreator(xml_node node);
	static BaseObject* getBridge(int x, int y);
	//static BaseObject* getFalcon(xml_node node);
	//static BaseObject* getGreatWall(xml_node node);
	//static BaseObject* getRockFly(xml_node node);
	//static BaseObject* getRockFall(xml_node node);
	//static BaseObject* getScubaSoldier(xml_node node);
	//static BaseObject* getFire(xml_node node);
	//static BaseObject* getShadowBeast(xml_node node);


	static map<string, string> getObjectProperties(eID id, int x, int y, int width, int height, int type, int dir);
};

#endif // !__OBJECT_READER__
