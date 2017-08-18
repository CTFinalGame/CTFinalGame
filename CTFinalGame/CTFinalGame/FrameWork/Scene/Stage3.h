
#ifndef __STAGE3_H__
#define __STAGE3_H__

#include "../../FrameWork/Sprite.h"
#include "../../FrameWork/SpriteManager.h"
#include "../../FrameWork/Scene/SceneManager.h"
#include "../../FrameWork/Animation.h"
#include "../../FrameWork/Scenario.h"
#include "../Map/Map.h"
#include "../QuadTree/QNode.h"

#include "../../Objects/Enemies/Cannon.h"
#include "../../Objects/Enemies/Soldier.h"
#include "../../Objects/Enemies/Rifleman.h"
#include "../../Objects/Enemies/WallTurret.h"
#include "../../Objects/BaseObject.h"
#include "../../Objects/Object/Bill.h"
#include "../../Objects/Bullets/BulletManager.h"
#include "../../Objects/Bullets/AirCraft.h"
#include "../../Objects/Bullets/Falcon.h"
#include "../../Objects/Object/Land.h"
#include "../../Objects/Enemies/RockFall.h"
#include "../../Objects/Enemies/ScubaSoldier.h"
#include "../../Objects//Object/RockFly.h"
#include "../../Objects/Enemies/Fire.h"

#include "../../FrameWork/Map/Map.h"

#include "Scene.h"

//#define BOSS_STAGE3_VIEWPORT_ANCHOR 

using namespace std;
US_FRAMEWORK
ACTOR_SCENARIO	
class Stage3 : public Scene
{
public:
	Stage3(int billlife);
	~Stage3();

	bool init() override;
	void updateInput(float dt) override;
	void update(float dt) override;
	void draw(LPD3DXSPRITE spriteHandle) override;
	void release() override;


	void setViewport(Viewport* viewport);
	//static Viewport* getViewport();

	// Trả về một đối tượng theo id.
	// id: kiểu enum eID, định danh một đối tượng.
	// return: đối tượng cần tìm.
	BaseObject* getObject(eID id);

	// Lấy đối tượng bill.
	Bill* getBill();
private:
	void destroyobject();				// kiển tra nếu object hết hạn sử dụng thì phá huỷ đối tượng
	//Text* _text;
	int _restBill;
	// Danh sách đối tượng dùng để tạo quadtree.
	map <string, BaseObject*> _mapobject;

	// Danh sách các đối tượng hoạt động rộng không thể đưa vào quadtree.
	// (Ví dụ main character)
	vector<BaseObject*> _listobject;

	// Danh sách đối tượng nằm trong vùng active.
	// Mỗi vòng lặp sẽ được kiểm tra chỉnh sửa tại update, và sử dụng lại tại draw.
	vector<BaseObject*>   _active_object;

	vector<IControlable*> _listControlObject;
	Map* background;

	// quadtree
	QNode* _root;
	// Trỏ đến bill, một số đối tượng cần truyền bill vào để xử lý, lấy ở đây.
	BaseObject* _bill; 

	void updateViewport(BaseObject* objTracker);


	bool flagbossScenario;
	ScenarioManager* _director;
	ScenarioManager* _directorKillBoss;
	bool _flagCredit;
	void killbossScene_Bill(float deltatime, bool& isFinish);
	void bossScene_Viewport(float dt, bool& finish);
	void playPassBossSound(float dt, bool& finish);
	void playBossStage1Sound(float dt, bool& finish);
	// Xử lý kéo màn hình khi gặp bốt.
	void ScenarioMoveViewport(float deltatime);
	
	// Xử lý thằng bill tự đi sau khi giết boss
	void ScenarioKillBoss(float deltatime);

	bool checkGameLife();
	//Credit* _credit;
};

#endif // !__STAGE3_H__
