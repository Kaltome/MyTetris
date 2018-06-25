#pragma once
#ifndef __Gameoverscene_H__
#define __Gameoverscene_H__
#include "cocos2d.h"

USING_NS_CC;
	
static int finalscore = 0;

class Gameoverscene :public Scene {
public:
	CREATE_FUNC(Gameoverscene);
	virtual bool init();
	static void getfinalscore(int i);
	virtual void update(float mt);
private: 
	double exittime = 0;
	Label * yourscore;
	Sprite * youloss;

};

#endif // !__Gameoverscene.h
