﻿#pragma once
#ifndef __MAP_H__
#define __MAP_H__
#include "TileSet.h"
#include <istream>
#include <sstream>
#include "../Animation.h"

class Map
{
private:
	int _framewidth;	// độ rộng một frame (độ rộng của tile)
	int _frameheight;	// độ cao một frame (độ cao của tile)

						// Kích thước map tính theo số ô Tile.
	GVector2 _mapSize;
	int mapID;
	Sprite* _testSp;
	Animation* _animationTests;
	// Ma trận Tile id.
	// Id trong ma trận này được so sánh với Id của Tile trong TileSet.listTile
	int** _mapIndex;

	// Chứa list tile.
	TileSet* _tileSet;
	static void getMapData(string path, int** &matrix, GVector2&mapSize);
	static vector<string> splitString(const string & input, char seperate);

public:
	bool co = false;
	void draw(LPD3DXSPRITE, Viewport*);
	void release();
	void updateTest(float dt);
	void drawTest(LPD3DXSPRITE, Viewport*);
	/*
	Load dữ liệu từ một file xml.
	path: file tiledmap xml được định nghĩa cấu trúc sẵn.
	eID: sprite id được đăng kí ở sprite manager.
	*/
	static Map* LoadMapFromFile(const string path, eID spriteId);

	/*
	Lấy kich thước map.
	*/
	GVector2 getWorldSize();
	Map(int mapID);
	~Map();
};

#endif __MAP_H_