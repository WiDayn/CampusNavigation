﻿#include "Logger.h"
#include "ColorUtils.h"
#include "ImgUtils.h"
#include<graphics.h>
#include<windows.h>
#include<iostream>
#include<conio.h>
#include<cstdio>
#include<cmath>
#include<queue>
#include<thread>
#define DIS_PERCENT 1.2
#define WALK_PERCENT 65
#define INF 0x3f3f3f3f
#define ARRAY_SIZE 2333
using namespace std;
int W, H;
unsigned int unWidth = 0, unHeight = 0;
const int N = 1;
const double sqrt2 = sqrt(2.0);
IMAGE Map;
int spot[ARRAY_SIZE][ARRAY_SIZE], lu[ARRAY_SIZE][ARRAY_SIZE], vis[ARRAY_SIZE][ARRAY_SIZE];
double dis[ARRAY_SIZE][ARRAY_SIZE];
string lastInf;
bool selected = false;

void mapToSpot()
{
	memset(spot, 0, sizeof(spot));
	memset(lu, 0, sizeof(lu));
	for (int i = 1; i <= unWidth; ++i) {
		for (int j = 1; j <= unHeight; ++j) {
			if (ColorUtils::isTarget(i, j)) spot[i / N + 1][j / N + 1]++;
		}
	}
	W = unWidth / N; H = unHeight / N;
	for (int i = 1; i <= W; ++i)
		for (int j = 1; j <= H; ++j)
			if (spot[i][j] > N * N / 2)lu[i][j] = 1;
}
struct dian
{
	int x, y;
	double dis_from, dis_to;
	friend bool operator <(const dian& a, const dian& b)
	{
		return a.dis_from + a.dis_to > b.dis_from + b.dis_to;
	}
}from[ARRAY_SIZE][ARRAY_SIZE];
priority_queue<dian>q;
int dx[10] = { 0,-1,-1,1,1,-1,0,0,1 };
int dy[10] = { 0,-1,1,-1,1,0,-1,1,0 };
void bfs(int X1, int Y1, int X2, int Y2)
{
	while (!q.empty()) q.pop();
	memset(from, 0, sizeof(from));
	memset(vis, 0, sizeof(vis));
	dian now, to; double tmp_dis; now.x = X1; now.y = Y1; now.dis_from = 0;

	for (int i = 1; i <= W; ++i)
		for (int j = 1; j <= H; ++j) dis[i][j] = INF;
	dis[now.x][now.y] = 0;
	q.push(now);
	bool flag = false;

	while (!q.empty() && !flag)
	{
		now = q.top(); q.pop();
		if (vis[now.x][now.y])continue; vis[now.x][now.y] = 1;
		setfillcolor(RGB(255, 0, 0));
		solidcircle(now.x * N, now.y * N, 1);
		for (int i = 1; i <= 8; ++i)
		{
			to.x = now.x + dx[i]; to.y = now.y + dy[i];
			if (i <= 4)tmp_dis = now.dis_from + sqrt2;
			else tmp_dis = now.dis_from + 1;
			if (to.x < 1 || W < to.x || to.y < 1 || H < to.y || lu[to.x][to.y] == 0 || dis[to.x][to.y] <= tmp_dis)continue;
			dis[to.x][to.y] = tmp_dis; to.dis_from = tmp_dis;
			setfillcolor(RGB(0, 255, 0));//
			solidcircle(to.x * N, to.y * N, 1);//

			to.dis_to = sqrt((double)(X2 - to.x) * (X2 - to.x) + (Y2 - to.y) * (Y2 - to.y));
			from[to.x][to.y] = now;
			q.push(to);
			if (to.x == X2 && to.y == Y2) flag = true;
		}
	}
	now.x = X2; now.y = Y2;
	int prepts[5000] = { 0 };
	int precnt = 0;
	int disCount = 0;
	while (now.x != X1 || now.y != Y1)
	{
		prepts[precnt++] = now.x * N;
		prepts[precnt++] = now.y * N;
		// solidcircle(now.x * N, now.y * N, 2);
		now = from[now.x][now.y];
		disCount++;
	}
	Logger::logSuccess("距离约为:" + to_string(int(disCount / DIS_PERCENT * 100) / 100.0) + "米，步行约要" + to_string(int((disCount / DIS_PERCENT) / WALK_PERCENT * 100) / 100) + "分钟");
	double lastk[100] = { 0 };
	int lastx = 0, lasty = 0;
	int pts[5000] = { 0 };
	int cnt = 0;
	for (int i = 0; i < precnt; i += 10) {
		double avgk = 0;
		for (int i = 0; i < min(cnt / 2, 100); i++) avgk += lastk[i];
		avgk /= min(cnt / 2, 100);
		if (prepts[i + 1] == lasty) {
			if (avgk > INF / 2) {
				continue;
			}
		}
		if (abs(prepts[i + 1] != lasty && (prepts[i] - lastx) / (prepts[i + 1] - lasty) - avgk) < 0.1) {
			continue;
		}
		lastx = prepts[i];
		lasty = prepts[i + 1];
		if (prepts[i + 1] != lasty) {
			lastk[(cnt / 2) % 100] = prepts[i + 1] != lasty && (prepts[i] - lastx) / (prepts[i + 1] - lasty);
		}
		else {
			lastk[(cnt / 2) % 100] = INF;
		}
		pts[cnt++] = prepts[i];
		pts[cnt++] = prepts[i + 1];
	}
	pts[cnt++] = X1, pts[cnt++] = Y1;
	//for (int i = 0; i < cnt; i += 2) {
	//	solidcircle(pts[i], pts[i + 1], 2);
	//}

	putimage(0, 0, &Map);
	setlinecolor(RGB(0, 0, 255));
	polyline((POINT*)pts, cnt / 2);
}

ExMessage m1, m2, m3;
void watch() {
	if (!selected) {
		cin >> m1.x >> m1.y;
		cin >> m2.x >> m2.y;
		selected = true;
	}
}

void showMouse() {
	while (1) {
		ExMessage m;
		if (peekmessage(&m)) {
			setfillcolor(BLACK);
			solidrectangle(0, 0, 170, 30);
			setfillcolor(RGB(255, 0, 0));
			string ch = "Mouse: " + to_string(m.x) + ' ' + to_string(m1.y);
			if (ColorUtils::isTarget(m.x, m.y)) {
				ch += " Yes";
			}
			else {
				ch += " No";
			}
			int num = MultiByteToWideChar(0, 0, ch.c_str(), -1, NULL, 0);
			wchar_t* wide = new wchar_t[num];
			MultiByteToWideChar(0, 0, ch.c_str(), -1, wide, num);
			outtextxy(0, 0, wide);
		}
	}
}

int main()
{
	Logger::log("欢迎使用校园路径规划与步行行程预计系统!");
	Logger::log("===============================");
	ImgUtils::GetPicWidthHeight("./Map.png", &unWidth, &unHeight);
	initgraph(unWidth, unHeight, EW_SHOWCONSOLE);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_BEVEL, 3);
	loadimage(&Map, _T(".\\Map.png"));
	putimage(0, 0, &Map);
	Logger::logInfo("预处理地图中...");
	mapToSpot();
	Logger::logSuccess("加载完毕！可以开始选点了!");
	thread mouse(showMouse);
	mouse.detach();
	while (1) {
		selected = false;
		setfillcolor(RGB(255, 0, 0));
		thread input(watch);
		input.detach();
		while (!selected)
		{
			if (peekmessage(&m1)) {
				if (m1.message == WM_LBUTTONDOWN && ColorUtils::isTarget(m1.x, m1.y)) {
					solidcircle(m1.x, m1.y, 4);
					if (m1.ctrl != true) break;
				}
			}
		}
		lastInf = "第一个点的坐标为: " + to_string(m1.x);
		lastInf += "  " + to_string(m1.y);
		Logger::logInfo(lastInf);
		while (!selected)
		{
			if (peekmessage(&m2)) {
				if (m2.message == WM_LBUTTONDOWN && ColorUtils::isTarget(m2.x, m2.y)) {
					solidcircle(m2.x, m2.y, 4);
					selected = true;
					break;
				}
			}
		}
		lastInf = "第二个点的坐标为: " + to_string(m2.x);
		lastInf += "  " + to_string(m2.y);
		Logger::logInfo(lastInf);

		double dur;
		clock_t start, end;
		start = clock();
		Logger::logInfo("Starting A*...");
		bfs(m1.x / N + 1, m1.y / N + 1, m2.x / N + 1, m2.y / N + 1);
		end = clock();
		dur = (double)(end - start);
		Logger::logSuccess("Use Time: " + to_string(dur / CLOCKS_PER_SEC));
		while (1)
		{
			if (peekmessage(&m3)) {
				if (m3.message == WM_LBUTTONDOWN) {
					break;
				}
			}
		}
		putimage(0, 0, &Map);
	}
	return 0;
}