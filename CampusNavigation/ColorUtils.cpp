/*****************************************************************//**
 * \file   ColorUtils.cpp
 * \author WiDAYN
 * \date   10 April 2022
 *********************************************************************/
#include "ColorUtils.h"

bool ColorUtils::isTarget(int x, int y)
{
	COLORREF col = getpixel(x, y);
	int r = GetRValue(col);
	int g = GetGValue(col);
	int b = GetBValue(col);
	if (r > 240 && g > 240 && b > 240) {
		return true;
	}
	else {
		return false;
	}
}
