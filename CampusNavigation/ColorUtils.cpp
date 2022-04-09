/*****************************************************************//**
 * \file   ColorUtils.cpp
 * \author WiDAYN
 * \date   10 April 2022
 *********************************************************************/
#include "ColorUtils.h"

bool ColorUtils::isWhite(COLORREF col)
{
	int r = GetRValue(col);
	int g = GetGValue(col);
	int b = GetBValue(col);
	if (r > 240 && g > 240 && b > 240) {
		std::cout << "White\n";
		return true;
	}
	else {
		std::cout << "Not White\n";
		return false;
	}
}
