#include "QNode.h"

// Thần phần static phải khởi tạo lại ở file.cpp.
vector<string> QNode::ActiveObject;
QNode::QNode()
{
}
QNode::QNode(string id, int level, RECT bound, QNode* parent)
{
	this->_id = id;
	this->_level = level;
	this->_bound = bound;
	this->_parent = parent;
	for (int i = 0; i < 4; i++)
	{
		_childs[i] = NULL;
	}
}

void QNode::insertObject(BaseObject* baseobject)
{
	//this->_listOject.push_back(baseobject);
}

void QNode::insertObject(string objectname)
{
	this->_listObject.push_back(objectname);
}

RECT QNode::getBound()
{
	return _bound;
}
string QNode::getId()
{
return _id;
}
int QNode::getLevel()
{
	return _level;
}
QNode* QNode::getParent()
{
	return _parent;
}
void QNode::setParent(QNode* parent)
{
	this->_parent = parent;
}
vector<string> QNode::getAllObject()
{
	return	_listObject;
}

bool QNode::isLeaf()
{
	if (this->_childs[0] == NULL)
		return true;
	return false;
}

QNode* QNode::loadQuadTree(const string path)
{
	QNode* node = nullptr;
	// Mở file và đọc
	ifstream myfile(path);
	string id, objectID;
	int level, x, y, width, height;
	myfile >> id;
	myfile >> x;
	myfile >> y;
	myfile >> width;
	myfile >> height;
	if (id == "0")
	{
		level = 0;
	}
	else{
		level = checkLevel(id);
	}
	node = initNode(id, level, x, y, width, height);
	getListNode(node);
	//loadChild(id, level, x, y, width, height, node);
	return node;
}
int QNode::checkLevel(string id)
{
	int level;
	int length = id.length();
	if (id == "0")
	{
		level = 0;
	}
	else if (length == 2)
	{
		level = 1;
	}
	else if (length == 4)
	{
		level = 2;
	}
	else if (length == 6)
	{
		level = 3;
	}
	else if (length == 8)
	{
		level = 4;
	}
	return level;
}
QNode* QNode::initNode(string id, int level, int x, int y, int width, int height)
{
	RECT bound;
	bound.left = x;
	bound.bottom = y;
	bound.top = bound.bottom + height;
	bound.right = bound.left + width;
	
	QNode* qnode = new QNode(id, level, bound, NULL);
	return qnode;
}

void QNode::loadChild(string id, int level, int x, int y, int width, int height, QNode* parent)
{
	QNode* child[4] = { NULL };

}

void QNode::getListNode(QNode* rootNode)
{

	QNode* nodechild[4] = { NULL };
	vector<QNode*> list;
	ifstream myfile("Resource//Map//a_quadtree.txt");
	int check = 0;
	string objectId;
	int count = 0;
	while (!myfile.eof())
	{
		count++;
		QNode* temp = new QNode();
		
		if (check == 0)
		{
			myfile >> temp->_id;
		}
		else
		{
			temp->_id = objectId;
			check = 0;
		}
		float x, y, width, height;
		temp->_level = checkLevel(temp->_id);
		/*myfile >> temp->_bound.left;
		myfile >> temp->_bound.bottom;
		myfile >> temp->_bound.right;
		myfile >> temp->_bound.top;*/
		myfile >> x;
		myfile >> y;
		myfile >> width;
		myfile >> height;
		myfile >> objectId;


		temp->_bound.left = x;
		temp->_bound.bottom = y;
		temp->_bound.right = x + width;
		temp->_bound.top = y + height; 
		bool checkObject = false;
		if (objectId.find(',') != string::npos)
		{
			checkObject = true;
		}
		if (checkObject)
		{
			stringstream object(objectId);
			string item;
			while (getline(object, item, ','))
			{
				temp->_listObject.push_back(item);
			}
		}
		else
		{
			check = 1;
		}
		list.push_back(temp);
		//if (count != 1)
		//{
		//	
		//}
		
	}
	if (rootNode->_id == "0")
	{
		for each(QNode* child in list)
		{
				if (child->_id.length() == 2)
				{
					child->setParent(rootNode);
					if (child->_id == "00")
					{
						nodechild[0] = child;
					}
					else if (child->_id == "01")
					{
						nodechild[1] = child;
					}
					else if (child->_id == "10")
					{
						nodechild[2] = child;
					}
					else
					{
						nodechild[3] = child;
					}
					rootNode->setChilds(nodechild);
				}
		}
	}
	for each (QNode* node in list)
	{
		if (node->_id != "0")
		{
			for each(QNode* child in list)
			{
				if (substringID(child->_id, 0, node->_id.length()) == node->_id && child->_id.length() == node->_id.length() + 2)
				{
					child->setParent(node);
					if (substringID(child->_id, node->_id.length(), 2) == "00")
					{
						nodechild[0] = child;
					}
					else if (substringID(child->_id, node->_id.length(), 2) == "01")
					{
						nodechild[1] = child;
					}
					else if (substringID(child->_id, node->_id.length(), 2) == "10")
					{
						nodechild[2] = child;
					}
					else
					{
						nodechild[3] = child;
					}
					node->setChilds(nodechild);
				}
			}		
		}
		
	}
}

void QNode::setChilds(QNode* nodes[4])
{
	for (int i = 0; i < 4; i++)
	{
		this->_childs[i] = nodes[i];
	}
}

string QNode::substringID(string id, int index, int length)
{
	string rs="";
	rs = id.substr(index, length);
	return rs;
}

vector<string> QNode::GetActiveObject(RECT bound, bool botleft)
{
	if (botleft)
	{
		// đổi từ bot-left sang top-left
		bound.bottom = WINDOW_HEIGHT - bound.bottom;
		bound.top = WINDOW_HEIGHT - bound.top;
	}

	QNode::ActiveObject.clear();
	this->fetchActiveObject(bound);
	return QNode::ActiveObject;
}
bool QNode::isContains(RECT rect1, RECT rect2)
{
	float left = rect1.left - rect2.left;
	float top = rect1.top - rect2.top;
	float right = rect1.right - rect2.right;
	float bottom = rect1.bottom - rect2.bottom;

	if (left * right > 0)
	{
		return false;
	}
	if (top * bottom > 0)
	{
		return false;
	}
	return true;
}

// hệ top-left
bool QNode::isIntersectd(RECT rect1, RECT rect2)
{
	float left = rect1.left - rect2.right;
	float top = rect1.bottom - rect2.top;
	float right = rect1.right - rect2.left;
	float bottom = rect1.top - rect2.bottom;

	//  Có chồng lên nhau khi
	//  left < 0 && right > 0 && top > 0 && bottom < 0
	//
	if (left > 0 || right < 0 || top > 0 || bottom < 0)
		return false;

	return true;
}
void QNode::fetchActiveObject(RECT bound)
{
	if (isContains(this->_bound, bound) || isIntersectd(this->_bound, bound) || isContains(bound, this->_bound))
	{
		
		if (this->isLeaf())
		{
			
			for (string obj : _listObject)
			{
				auto it = std::find(ActiveObject.begin(), ActiveObject.end(), obj);
				if (it == ActiveObject.end() || it._Ptr == nullptr)
				{
					ActiveObject.push_back(obj);
				}
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				_childs[i]->fetchActiveObject(bound);
			}
		}
	}
}

QNode::~QNode()
{
	for (int i = 0; i < 4; i++)
	{
		SAFE_DELETE(_childs[i]);
	}
}