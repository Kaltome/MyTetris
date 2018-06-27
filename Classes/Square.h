#pragma once
#ifndef __Square_H__
#define __Square_H__
#include "cocos2d.h"
#include "Shape.h"
USING_NS_CC;


class Ctrlsquare :public Shape {
public:
	int score = 0;
	Sprite* gameoverbg;
	Label* scorelabel;
	Label* scoretitle;
	int cleanedrows = 0;
	bool isshow[24][10];
	bool nextshow[4][4];
	int controlx = 3;
	int controly = 0;
	int cnum;
	int snum;
};

#endif // !__Square_H__

