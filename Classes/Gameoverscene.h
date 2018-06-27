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
	void output();
private: 
	double exittime = 0;
	Label * yourscore;
	Label * yourrank;
	Sprite * youloss;
	int rank = 0;

};

#endif // !__Gameoverscene.h
