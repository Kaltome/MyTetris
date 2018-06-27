#pragma once
#ifndef __Playscene_H__
#define __Playscene_H__
#include "cocos2d.h"
#include "Shape.h"
#include "Square.h"
USING_NS_CC;

static double downspeed;
static double orispeed;

class Playscene : public Scene{
public:
	CREATE_FUNC(Playscene);
	virtual bool init();
	virtual void update(float mt);
	static void getspeed(double i);
	void controlkeyevent();
	int  addscore();
	void cleanrow(int crow);
	void reset();
	void rotate();					//旋转图形
	bool checkhit();
	void checkleft();				//检查与左边墙壁有无碰撞
	void checkright();
	void checkup();
	bool checkdown();

private:
	Ctrlsquare cplayer;
	int speedup = 15;
	//int score = 0;
	//Label* scorelabel;
	//int cleanedrows = 0;
	Sprite* square[24][10];			//俄罗斯方块
	//bool isshow[24][10];			//确定要显示那个方块
	Sprite* next[4][4];				//显示下一个的方块
	//bool nextshow[4][4];			//显示下一个方块
	//int controlx = 3;				//确定移动方块的横坐标
	//int controly = 0;				//控制方块下落
	double time = 0;
	double pretime = 0;
	int ispause = 1;
	//Shape cshape; 
	//int cnum;			//控制的方块
	//int snum;						//显示的下一个方块

};


#endif // !__Playscene_H__
