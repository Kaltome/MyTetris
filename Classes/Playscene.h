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
	void rotate();					
	bool checkhit();
	void checkleft();				
	void checkright();
	void checkup();
	bool checkdown();

private:
	Ctrlsquare cplayer;				//玩家（一名）
	int speedup = 15;				//加速下落模式
	Sprite* square[24][10];			//俄罗斯方块精灵
	Sprite* next[4][4];				//下一个方块精灵
	double time = 0;				//游戏时长
	double pretime = 0;				//两次下落间隔的时间
	int ispause = 1;				//记录暂停

};
#endif // !__Playscene_H__
