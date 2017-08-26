﻿//#include "stdafx.h"
#include "Map.h"
#include "../Scene/Scene.h"

void Map::release()
{
}

Map::Map(int mapid)
{
	mapID = mapid;
	_mapIndex = NULL;
	_testSp = SpriteManager::getInstance()->getSprite(eID::WATERFALLEFFECT);
	_testSp->setScale(2.0f);
	_animationTests = new Animation(_testSp, 0.12f);
	_animationTests->addFrameRect(eID::WATERFALLEFFECT, "waterfall_01", "waterfall_02", NULL);
}


Map::~Map()
{
}

void Map::draw(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	RECT screenRectEx =
	{
		viewport->getPositionWorld().x,
		viewport->getPositionWorld().y,
		viewport->getPositionWorld().x + viewport->getWidth(),
		viewport->getPositionWorld().y - viewport->getHeight()
	};	// top lớn hơn bottom (sử dụng hệ toạ độ đề các)

	int iBegin = max(screenRectEx.left / _framewidth, 0);
	int iEnd = min(screenRectEx.right / _framewidth + 1, _mapSize.x);
	int jBegin = _mapSize.y - min(screenRectEx.top / _frameheight + 1, _mapSize.y);
	int jEnd = _mapSize.y - max(screenRectEx.bottom / _frameheight, 0);
	// uncomment this block to view How viewport work with tile map => TO KNOW IT IS NOT ONLY A PICTURE :D
	/*
	int iBegin = max(screenRectEx.left / _framewidth, 0) + 1;
	int iEnd = min(screenRectEx.right / _framewidth,  _mapSize.x) ;
	int jBegin = _mapSize.y - min(screenRectEx.top / _frameheight, _mapSize.y) + 1;
	int jEnd =_mapSize.y - max(screenRectEx.bottom / _frameheight, 0);*/

	GVector2 pos;

	for (int i = iBegin; i < iEnd; i++)
	{
		for (int j = jBegin; j < jEnd; j++)
		{
			if(mapID==39){
			if (this->_mapIndex[j][i] == 8 || this->_mapIndex[j][i] == 13 || this->_mapIndex[j][i] == 28 || this->_mapIndex[j][i] == 61 || this->_mapIndex[j][i] == 62 || this->_mapIndex[j][i] == 75 || this->_mapIndex[j][i] == 76)
			{

				GVector2 position = GVector2(i * _framewidth, (_mapSize.y - j - 1) * _frameheight + 16);
				_testSp->setPosition(position);
				_animationTests->draw(spriteHandle, viewport);
			}
			else
			{
				pos.x = i * _framewidth;
				pos.y = (_mapSize.y - j - 1) * _frameheight;				// nếu có viewport 
				this->_tileSet->draw(spriteHandle, this->_mapIndex[j][i], pos, viewport);
			}
			}
			else
			{
				pos.x = i * _framewidth;
				pos.y = (_mapSize.y - j - 1) * _frameheight;				// nếu có viewport 
				this->_tileSet->draw(spriteHandle, this->_mapIndex[j][i], pos, viewport);
			}
		}
	}
	this->co = true;

}

GVector2 Map::getWorldSize()
{
	GVector2 result;
	result.x = this->_mapSize.x * this->_framewidth;
	result.y = this->_mapSize.y * this->_frameheight;
	return result;
}
/*
đọc thông tin map gồm:
- kích thước frame (rộng cao của tile)
- kích thước map theo số tile (vd: 200tile x 12tile)
- ma trận _mapIndex (chứa index của tile trong tileSet)
- mảng TileSet chứa list của tile info
13:53 - 28/7/2017
*/
Map* Map::LoadMapFromFile(const string path, eID spriteId)
{
	Map* map = new Map((int)spriteId);
	getMapData(path, map->_mapIndex, map->_mapSize);
	map->_tileSet = new TileSet(spriteId);
	map->_tileSet->loadListTiles();
	map->_framewidth = 32;
	map->_frameheight = 32;
	return map;
}

//get TileID
//2:22 - 27/7/2017
void Map::getMapData(string path, int ** &matrix, GVector2 &mapSize)
{
	//ifstream infile(L"Resources\\Map\\map1.txt");
	ifstream infile(path);
	int lineNumber = 0;
	string line;
	int index;
	int totalHorizontal, totalVertical;
	while (getline(infile, line))
	{
		istringstream iss(line);
		if (lineNumber == 0)
		{
			if (!(iss >> totalHorizontal >> totalVertical))
			{
				break;
			}
			mapSize.x = totalHorizontal;
			mapSize.y = totalVertical;

			matrix = new int*[totalVertical];
			for (int i = 0; i < totalVertical; i++)
				matrix[i] = new int[totalHorizontal];
		}
		else
		{
			vector<string> temp = splitString(line, ',');
			for (int i = 0; i < totalHorizontal; i++)
			{
				index = atoi(temp[i].c_str());
				matrix[lineNumber - 1][i] = index;
			}
			temp.clear();
		}
		lineNumber++;
	}
	infile.close();
}

vector<string> Map::splitString(const string & input, char seperate)
{
	vector<string> output;
	std::stringstream ss(input);

	string item;

	while (std::getline(ss, item, seperate))
	{
		output.push_back(item);
	}

	return output;
}
void Map::updateTest(float dt) {
	_animationTests->update(dt);
	int a = this->_animationTests->getIndex();
}
void Map::drawTest(LPD3DXSPRITE spriteHandle, Viewport* viewport)
{
	int a = this->_animationTests->getIndex();
	this->_animationTests->draw(spriteHandle, viewport);
	//this->draw(spriteHandle, viewport);
}