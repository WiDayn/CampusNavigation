#include <iostream>
#include <easyx.h>
#include <graphics.h>
#include "ImgUtils.h"

int main()
{
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
			COLORREF col = getpixel(m.x, m.y);
			int r = GetRValue(col);
			int g = GetGValue(col);
			int b = GetBValue(col);
			if (r > 240 && g > 240 && b > 240) {
				std::cout << "White\n";
			}
			else {
				std::cout << "Not White\n";
			}

			setfillcolor(RED);
			solidcircle(m.x, m.y, 3);
			break;
		}
	}
}