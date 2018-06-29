#pragma once
#ifndef __Gameoverscene_H__
#define __Gameoverscene_H__
#include "cocos2d.h"

USING_NS_CC;
	
static int finalscore = 0;
static int finalspeed = 0;


class Gameoverscene :public Scene {
public:
	CREATE_FUNC(Gameoverscene);
	virtual bool init();
	static void getfinal(int i, int j);						
	virtual void update(float mt);							
	void output();											//文件读取（排行榜）
private: 
	double exittime = 0;									//记录自动回到主界面时间				
	Label * yourscore;										
	Label * yourrank;
	Sprite * youloss;										//标题
	int rank = 0;											//排名

};

#endif // !__Gameoverscene.h
