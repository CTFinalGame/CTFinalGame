#ifndef __QNODE_H__
#define __QNODE_H__

#include "../define.h"
#include "../../Objects/BaseObject.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class QNode
{
private:
	RECT _bound;
	string _id;
	int _level;
	QNode* _parent;
	QNode* _childs[4];
	vector <string> _listObject;


public:
	QNode();
	QNode(string id, int level, RECT bound, QNode* parent);
	void insertObject(string name);
	RECT getBound();
	string getId();
	int getLevel();
	QNode* getParent();
	void setParent(QNode* parent);
	QNode** getChilds();
	void setChilds(QNode* nodes[4]);
	bool isLeaf();
	static int checkLevel(string id);

	vector<string> getAllObject();

	static string substringID(string id, int index, int length);

	static void loadChild(string id, int level, int x, int y, int width, int height, QNode* parent);
	static QNode* loadQuadTree(const string path);
	static QNode* initNode(string id, int level, int x, int y, int width, int height);
	static void getListNode(QNode* rootNode, const string path);
	/*
	L?y object mà bound ?è lên
	@bound: hcn
	@botleft: b?ng true n?u hcn tính theo bot-left, false là top-left
	thêm ?? kh?i m?t công chuy?n bên ngoài
	*/
	vector<string> GetActiveObject(RECT bound, bool botleft = false);
	void fetchActiveObject(RECT bound);
	static vector<string> ActiveObject;

	/*
	Kiểm tra hai hình chữ nhật có chồng lên nhau không.
	Dùng trong hệ top left
	*/
	bool isIntersectd(RECT rect1, RECT rect2);
	/*
	* Kiểm tra rect1 có chứa rect2 không.
	* @return: true nếu rect1 chứa rect2
	*/
	bool isContains(RECT rect1, RECT rect2);

	~QNode();
};



#endif // !__QNODE_H__

