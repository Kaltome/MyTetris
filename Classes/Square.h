#pragma once
#ifndef __Square_H__
#define __Square_H__
#include "cocos2d.h"
#include "Shape.h"
USING_NS_CC;

class Ctrlsquare :public Shape {
public:
	int score = 0;			//玩家分数
	Sprite* gameoverbg;		//玩家游戏结束显示图片
	Label* scorelabel;		//分数标签
	Label* scoretitle;		//分数标签
	int cleanedrows = 0;	//玩家清除的行数
	bool isshow[24][10];	//玩家积累的方块
	bool nextshow[4][4];	//下一个方块的显示
	int controlx = 3;		//玩家控制的方块的横坐标
	int controly = 0;		//玩家控制的方块的纵坐标
	int cnum;				//玩家控制的方块的种类
	int snum;				//玩家下一个方块的种类
	bool isloss = 0;		//记录是否死亡
};

#endif // !__Square_H__

