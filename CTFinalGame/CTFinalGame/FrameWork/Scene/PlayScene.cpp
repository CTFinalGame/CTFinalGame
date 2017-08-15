#include "PlayScene.h"
#if _DEBUG
#include <time.h>
#endif

 
PlayScene::PlayScene()
{
	_viewport = new Viewport(0, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
} 

PlayScene::~PlayScene()
{
	delete _viewport;
	_viewport = nullptr;
}

bool PlayScene::init()
{

	
	/*auto _soldier = new Soldier(eStatus::RUNNING, GVector2(300, 240), -1);
	_soldier->init();	
	_listobject.push_back(_soldier);
	auto _soldier1 = new Soldier(eStatus::RUNNING, GVector2(800, 240), -1);
	_soldier1->init();
	_listobject.push_back(_soldier1);
	*/
	//auto wallTurret = new Cannon(eStatus::NORMAL, 300, 300, 1);
	//wallTurret->init();
	////_listobject.push_back(wallTurret);

	//auto cannon = new Cannon(eStatus::NORMAL, 400, 200, 2);
	//cannon->init();
	////_listobject.push_back(cannon);

     background =  Map::LoadMapFromFile("Resource//Map//map1.txt", eID::MAP1);
	 _bulletmanager = new BulletManager();
	 _bulletmanager->init();

	/* auto boss = new Boss(GVector2(400, 140), 100);
	 boss->init();
	 _listobject.push_back(boss);*/

	/* auto fifleman = new Rifleman(eStatus::NORMAL, 580, 60);
	fifleman->init();
	_listobject.push_back(fifleman);
	
	auto fifleman1 = new Rifleman(eStatus::HIDDEN, 700, 300);
	fifleman1->init();
	_listobject.push_back(fifleman1);
	
	 auto bire = new Bridge(GVector2(1550,230));
	 bire->init();
	 _listobject.push_back(bire);	*/

	 //auto land = new Land(50, 240, 1450, 20, eDirection::ALL, eLandType::GRASS);
	 //land->init();
	 //_listobject.push_back(land);
	 //auto falon = new Falcon(650,140,eAirCraftType::S);
	 //falon->init();
	 //_listobject.push_back(falon);
	 //auto landbottom = new Land(320, 170, 200, 20, eDirection::ALL, eLandType::GRASS);
	 //landbottom->init();
	 //_listobject.push_back(landbottom);
	 //auto water = new Land(0, 40, 1500, 20, eDirection::ALL, eLandType::WATER);
	 //water->init();
	 //_listobject.push_back(water);
	 //auto landwater = new Land(550,60, 200, 20, eDirection::ALL, eLandType::GRASS);
	 //landwater->init();
	 //_listobject.push_back(landwater);
	 ////Tao airCraft
	 //GVector2 pos(50, 300), hVeloc = AIRCRAFT_HORIZONTAL_VELOC, ampl = AIRCRAFT_AMPLITUDE;
	 //float freq = AIRCRAFT_FREQUENCY;
	 //eAirCraftType type = S;
	 //auto airCraft = new AirCraft(pos, hVeloc / 2, ampl, freq, type);

	 //airCraft->init();
	 //_listobject.push_back(airCraft);
	 auto bill = new Bill(1);
	 bill->init();
	 bill->setPosition(200, 500);
	 this->_bill = bill;
	 _listControlObject.push_back(bill);
	 _listobject.push_back(bill);

	 map<string, BaseObject*>* maptemp = ObjectFactory::getMapObjectFromFile("Resource//Map//a_ob.txt");
	 this->_mapobject.insert(maptemp->begin(), maptemp->end());

	 _root = QNode::loadQuadTree("Resource//Map//a_quadtree.txt");
	// auto scenarioBoss_Viewport = new Scenario("BossViewport");
	// __hook(&Scenario::update, scenarioBoss_Viewport, &PlayScene::bossScene_Viewport);
	// auto scenarioBossSound = new Scenario("BossSound");
	 //__hook(&Scenario::update, scenarioBossSound, &PlayScene::playBossStage1Sound);
	// _director = new ScenarioManager();
	// _director->insertScenario(scenarioBossSound);
	// _director->insertScenario(scenarioBoss_Viewport);
	 flagbossScenario = false;
	return true;
}
void PlayScene::updateInput(float dt)
{
	for (IControlable* obj : _listControlObject)
	{
		obj->updateInput(dt);
	}
}

void PlayScene::update(float dt)
{
	// id của đối tượng, được get trong vòng lặp duyệt đối tượng.
	eID objectID;
	if (this->checkGameLife() == true)
		return;
	if (_bill->isInStatus(eStatus::DYING) == false)
	{
		this->updateViewport(_bill);
	}
	//// IMPORTANT

	/*
	*		Hiện tại chúng ta có 2 danh sách object.
			Một là _listobject chứa các đối tượng hoạt động rộng. không thể đưa vào quadtree
			Hai là _mapobject chứa các đối tượng đã được đưa vào quadtree. 
			Ta có một listobject phụ là _active_object để chứ các object sẽ được update, draw ở mỗi frame. được clear ở đầu hàm update.

			Quá trình update gồm các bước.
				- Kiểm tra và đối tượng hết hiệu lực (Status = Destroy) từ frame trước			(Bước 1)
				- Clear danh sách _active_object của frame trước, chuẩn bị cho vòng lặp mới.	(Bước 2)
				- Tìm các tên của đối tượng đã được lưu trong quadtree.							(Bước 3)
				- Từ danh sách tên ở bước trên, add các đối tượng có tên tương ứng với _mapobject vào _active_object	(Bước 4)
				- Add danh sách các đối tượng trong _listobject vào _active_object.										(Bước 5)
				- Kiểm tra va chạm chéo giữa các đối tượng trong _active_object. Nếu có n đối tượng, thi có n * n lần kiểm tra va chạm..	(Bước 6)
				- update các đối tượng trong _active_object																(Bước 7)

			Vẽ:
				- Chỉ vẽ các đối tượng có trong _active_object.
	*/

	GVector2 viewport_position = _viewport->getPositionWorld();
	RECT viewport_in_transform = _viewport->getBounding();

	// Hàm getlistobject của quadtree yêu cầu truyền vào một hình chữ nhật theo hệ top left, nên cần tính lại khung màn hình
	RECT screen;
	// left right không đổi dù hệ top-left hay hệ bot-left
	screen.left = viewport_in_transform.left;
	screen.right = viewport_in_transform.right;
    //screen.top = viewport_position.y;
	/*screen.top = this->background->getWorldSize().y - viewport_position.y;
	screen.bottom = screen.top + _viewport->getHeight();*/
	screen.bottom = 0;
	screen.top = screen.bottom + background->getWorldSize().y;
	// getlistobject

	// [Bước 1]
	this->destroyobject();

	// [Bước 2]
	_active_object.clear();

	// [Bước 3]
	auto listobjectname = _root->GetActiveObject(screen);

	// [Bước 4]
	for (auto name : listobjectname)
	{
	    auto obj = _mapobject.find(name);
		if (obj == _mapobject.end() || obj._Ptr == nullptr)
			continue;
		_active_object.push_back(obj->second);
	}

	// [Bước 5]
	_active_object.insert(_active_object.end(), _listobject.begin(), _listobject.end());
	// [Bước 6]
	for (BaseObject* obj : _active_object)
	{
		// một vài trạng thái không cần thiết phải check hàm va chạm
		if (obj == nullptr || obj->isInStatus(eStatus::DESTROY) || obj->getId() == eID::LAND || 
			obj->getId() == eID::WALL_TURRET || obj->getId() == eID::REDCANNON || obj->getId() == eID::ROCKFLY)
			continue;

		for (BaseObject* passiveobj : _active_object)
		{
			if (passiveobj == nullptr || passiveobj == obj || passiveobj->isInStatus(eStatus::DESTROY))
				continue;
			obj->checkCollision(passiveobj, dt);
		}
	}

	if (_bulletmanager != nullptr)
	{
		_bulletmanager->checkCollision(_bill, dt);
		_bulletmanager->update(dt);
	}

	// [Bước 7]
	for (BaseObject* obj : _active_object)
	{
		obj->update(dt);
	}
	this->ScenarioMoveViewport(dt);
}
void PlayScene::draw(LPD3DXSPRITE spriteHandle)
{
	background->draw(spriteHandle, _viewport);
	for (BaseObject* object : _active_object)
	{
		object->draw(spriteHandle,_viewport);
	}
	_bulletmanager->draw(spriteHandle, _viewport);
}

void PlayScene::release()
{
	for (auto object : _listobject)
	{
		object->release();
		SAFE_DELETE(object);
	}
	background->release();

}
void PlayScene::killbossScene_Bill(float deltatime, bool& isFinish)
{
	auto bill = (Bill*)_bill;


	if (bill->getBounding().left < _viewport->getBounding().right)
	{
		/*if (bill->getPositionX() < 6448)
		bill->forceMoveRight();
		else
		{
		if (bill->getPositionX() < 6500)
		bill->forceJump();
		}*/
	}
	else
	{
		/*bill->unforceMoveRight();
		bill->unforceJump();
		bill->removeGravity();*/
	}
}
void PlayScene::bossScene_Viewport(float dt, bool& finish)
{
	GVector2 current_position = _viewport->getPositionWorld();
	GVector2 worldsize = this->background->getWorldSize();

	current_position.x += BILL_MOVE_SPEED * dt / 1000;
	if (current_position.x + WINDOW_WIDTH > worldsize.x)
	{
		current_position.x = worldsize.x - WINDOW_WIDTH;
		finish = true;
		_viewport->setPositionWorld(current_position);
		return;
	}
	_viewport->setPositionWorld(current_position);
	if (_bill->getBounding().left < current_position.x)
	{
		GVector2 curPos = _bill->getPosition();
		curPos.x = current_position.x + (_bill->getSprite()->getFrameWidth() >> 1);
		_bill->setPosition(curPos);
	}
	finish = false;
}
void PlayScene::ScenarioMoveViewport(float deltatime)
{
	if (_director == nullptr)
		return;

	if (((Bill*)_bill)->getPositionX() > 100)
	{
		flagbossScenario = true;
	}
	if (flagbossScenario == true)
	{
		this->_director->update(deltatime);
		if (this->_director->isFinish() == true)
		{
			SAFE_DELETE(_director);
		}
	}
}
void PlayScene::ScenarioKillBoss(float deltatime)
{
	if (_directorKillBoss == nullptr)
		return;
	auto boss = getObject(eID::BOSS_STAGE1);
	//if ((SoundManager::getInstance()->IsPlaying(eSoundId::DESTROY_BOSS) == false) && boss != nullptr && boss->isInStatus(eStatus::DYING) == true)
	if (true)
	{
		this->_directorKillBoss->update(deltatime);
		if (this->_directorKillBoss->isFinish() == true)
		{
			SAFE_DELETE(_directorKillBoss);
			//chuyển scene
			/*auto play = new BeginPlayScene(Score::getScore(), ((Bill*)_bill)->getLifeNumber(), 3);
			SceneManager::getInstance()->replaceScene(play);*/
		}
	}
}
bool PlayScene::checkGameLife()
{
	if (((Bill*)_bill)->getLifeNumber() < 0)
	{
		auto gameoverScene = new GameOverScene(20, 1);
		SceneManager::getInstance()->replaceScene(gameoverScene);
		return true;
	}
	return false;
}
BaseObject* PlayScene::getObject(eID id)
{
	if (id == eID::BILL)
		return getBill();
	eID objectID;
	if (_active_object.size() == 0)
	{
		return nullptr;
	}
	for (BaseObject* object : _active_object)
	{
		objectID = object->getId();
		if (objectID == id)
			return object;
	}
	return nullptr;
}

void PlayScene::destroyobject()
{
	for (auto object : _listobject)
	{
		if (object->getStatus() == eStatus::DESTROY)	// kiểm tra nếu là destroy thì loại khỏi list
		{
			object->release();
			// http://www.cplusplus.com/reference/algorithm/remove/
			auto rs1 = std::remove(_listobject.begin(), _listobject.end(), object);
			_listobject.pop_back();			// sau khi remove thì còn một phần tử cuối cùng vôi ra. giống như dịch mảng. nên cần bỏ nó đi

			//https://msdn.microsoft.com/en-us/library/cby9kycs.aspx (dynamic_cast) 
			// loại khỏi list control
			vector<IControlable*>::iterator icontrol = find(_listControlObject.begin(), _listControlObject.end(), dynamic_cast<IControlable*>(object));
			if (icontrol != _listControlObject.end())
			{
				auto rs2 = std::remove(_listControlObject.begin(), _listControlObject.end(), (*icontrol));
				_listControlObject.pop_back();
			}

			delete object;
			break;		// sau pop_back phần tử đi thì list bị thay đồi, nên vòng for-each không còn nguyên trạng nữa. -> break (mỗi frame chỉ remove được 1 đối tượng)
		}
	}
	for (auto name : QNode::ActiveObject)
	{
		auto object = _mapobject.find(name);
		if (object == _mapobject.end() || object._Ptr == nullptr)
			continue;
		if (object->second->getStatus() == eStatus::DESTROY)	// kiểm tra nếu là destroy thì loại khỏi list
		{
			//if (dynamic_cast<BaseEnemy*> (object->second) != nullptr)
			//{
			//	SoundManager::getInstance()->Play(eSoundId::DESTROY_ENEMY);
			//}
			object->second->release();
			delete object->second;
			object->second = NULL;
			_mapobject.erase(name);

		}
	}
}

void PlayScene::updateViewport(BaseObject* objTracker)
{
	//	// Vị trí hiện tại của viewport. 
	GVector2 current_position = _viewport->getPositionWorld();
	//GVector2 worldsize = GVector2(208, 14);
	GVector2 worldsize = this->background->getWorldSize();
	// Bám theo object.
	GVector2 new_position = GVector2(max(objTracker->getPositionX() - 260, 0), WINDOW_HEIGHT);		// 200 khoảng cách tối đa giữa object và map -> hardcode

	//#if(!_DEBUG)
	// Không cho đi ngược
	if (new_position.x < current_position.x)
	{
		new_position.x = current_position.x;
	}
	//#endif

	// Không cho đi quá map.
	if (new_position.x + WINDOW_WIDTH > worldsize.x)
	{
		new_position.x = worldsize.x - WINDOW_WIDTH;
	}

	_viewport->setPositionWorld(new_position);
}

Bill* PlayScene::getBill()
{
	return (Bill*)this->_bill;
}