#pragma once
#ifndef __Playscene_H__
#define __Playscene_H__
#include "cocos2d.h"
#include "Shape.h"
USING_NS_CC;

static double downspeed = 1.8;

class Playscene : public Scene{
public:
	CREATE_FUNC(Playscene);
	virtual bool init();
	virtual void update(float mt);
	void controlkeyevent();
	int  addscore();
	void cleanrow(int crow);
	void reset();
	void resetisshow();
	void rotate();					//旋转图形
	bool checkhit();
	void checkleft();				//检查与左边墙壁有无碰撞
	void checkright();
	void checkup();
	bool checkdown();

private:
	int speedup = 15;
	int score = 0;
	Label* scorelabel;
	int cleanrows = 0;
	Sprite* square[24][10];			//俄罗斯方块
	bool isshow[24][10];			//确定要显示那个方块
	Sprite* next[4][4];				//显示下一个的方块
	bool nextshow[4][4];			//显示下一个方块
	int controlx = 3;				//确定移动方块的横坐标
	int controly = 0;				//控制方块下落
	double time = 0;
	double pretime = 0;
	double downspeed = 1.8;

	Shape cshape; int cnum;			//控制的方块
	int snum;						//显示的下一个方块

};


#endif // !__Playscene_H__
