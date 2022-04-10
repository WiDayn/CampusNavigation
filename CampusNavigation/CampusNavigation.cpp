/*****************************************************************//**
 * \file   CampusNavigation.cpp
 * \author WiDAYN
 * \date   10 April 2022
 *********************************************************************/
#include "ColorUtils.h"
#include "ImgUtils.h"
#include "Logger.h"
#include <iostream>
#include <easyx.h>
#include <graphics.h>
#include <windows.h>

int main()
{
	Logger::logSuccess("123");
	Logger::logFail("123");
	Logger::logInfo("123");
	Logger::logWarn("123");

	unsigned int unWidth = 0, unHeight = 0;

	ImgUtils::GetPicWidthHeight("./开发阶段地图.png", &unWidth, &unHeight);

	initgraph(unWidth, unHeight, EW_SHOWCONSOLE);
	IMAGE img;
	loadimage(&img, _T("./开发阶段地图.png"));
	putimage(0, 0, &img);
	while (1) {
		MOUSEMSG m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			ColorUtils::isWhite(m.x, m.y);
			setfillcolor(RED);
			solidcircle(m.x, m.y, 3);
			break;
		}
	}
}