﻿#include "utils.h"

// hệ decac
bool isRectangleIntersected(RECT rect1, RECT rect2)
{
	float left = rect1.left - rect2.right;
	float top = rect1.top - rect2.bottom;
	float right = rect1.right - rect2.left;
	float bottom = rect1.bottom - rect2.top;


	if (left > 0 || right < 0 || top < 0 || bottom > 0)
		return false;

	return true;
}
