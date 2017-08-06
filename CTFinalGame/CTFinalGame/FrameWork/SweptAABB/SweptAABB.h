#pragma once

#include <math.h>
#include <limits>
#include "d3d9.h"
using namespace std;

enum DIR
{
	DIR_NONE = 0,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_TOP,
	DIR_BOTTOM
};

struct Box
{
	float x, y;
	float width, height;

	float vx, vy;

	Box(){}

	Box(float x, float y, float w, float h, float vx = 0.0f, float vy = 0.0f)
	{
		this->x = x;
		this->y = y;

		width = w;
		height = h;

		this->vx = vx;
		this->vy = vy;
	}
};

// tao mot khong gian boi doi tuong cung van toc
static Box GetSweptBroadPhaseBox(Box b)
{
	Box broadphasebox(0, 0, 0, 0);

	broadphasebox.x = b.vx > 0 ? b.x : (b.x + b.vx);
	broadphasebox.y = b.vy > 0 ? b.y : b.y + b.vy;
	broadphasebox.width = abs(b.vx) + b.width; // lấy độ lớn vx + width
	broadphasebox.height = abs(b.vy) + b.height; // lấy độ lớn vy + height

	return broadphasebox;
}


// kiểm tra vật có nằm ngoài vùng
// kiểm tra va chạm khi chưa có vận tốc
static DIR AABB(Box box1, Box box2)
{
	float l = box2.x - (box1.x + box1.width);
	float r = box1.x - (box2.x + box2.width);
	float t = box2.y - (box1.y + box1.height);
	float b = box1.y - (box2.y + box2.height);

	// check that there was a collision
	if (l >= 0 || r >= 0 || t >= 0 || b >= 0)
		return DIR::DIR_NONE;


	// co va cham khong can biet va cham ben nao
	if (t < 0) return DIR::DIR_TOP;
	if (l < 0) return DIR::DIR_LEFT;
	if (r < 0) return DIR::DIR_RIGHT;
	if (b < 0) return DIR::DIR_BOTTOM;
}

// thuat toan xet va cham
static float SweptAABB(Box box1, Box box2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry; // gần nhất theo trục x và y
	float xInvExit, yInvExit; // xa nhất theo truc x và y

	// tìm khoảng cách gần nhất và xa nhất giữa các cạnh 2 hình
	// InvEntry là khoảng cách gần nhất, InvExit là khoảng cách xa nhất
	// hệ quy chiếu (y - hướng xuống, x - sang phải)
	if (box1.vx > 0.0f)
	{
		xInvEntry = box2.x - (box1.x + box1.width); // xInvEntry > 0 => DIR_LEFT
		xInvExit = (box2.x + box2.width) - box1.x;
	}
	else
	{
		xInvEntry = (box2.x + box2.width) - box1.x; // xInvEntry < 0 => DIR_RIGHT
		xInvExit = box2.x - (box1.x + box1.width);
	}

	if (box1.vy > 0.0f)
	{
		yInvEntry = box2.y - (box1.y + box1.height);
		yInvExit = (box2.y + box2.height) - box1.y;
	}
	else
	{
		yInvEntry = (box2.y + box2.height) - box1.y;
		yInvExit = box2.y - (box1.y + box1.height);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (box1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / box1.vx; // xEntry < 1.0f thì va chạm <=> box1.vx > xInvEntry
		xExit = xInvExit / box1.vx;
	}

	if (box1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = (float)yInvEntry / box1.vy; // yEntry < 1.0f thì va chạm <=> box1.vy > yEntry
		yExit = (float)yInvExit / box1.vy;
	}

	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry); // tìm xem thời gian va chạm lâu nhất theo trục x hoặc y
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry >= 1.0f || yEntry >= 1.0f)
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0.0f) // DIR_RIGHT
			{
				normalx = 1.0f;
				normaly = 0.0f;
			}
			else // DIR_LEFT
			{
				normalx = -1.0f;
				normaly = 0.0f;
			}
		}
		else
		{
			if (yInvEntry < 0.0f) // bot
			{
				normalx = 0.0f;
				normaly = 1.0f;
			}
			else // DIR_TOP
			{
				normalx = 0.0f;
				normaly = -1.0f;
			}
		}

		// return the time of collision
		return entryTime;
	}
}