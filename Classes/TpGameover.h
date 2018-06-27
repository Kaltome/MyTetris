#pragma once
#pragma once
#ifndef __TpGameover_H__
#define __TpGameover_H__
#include "cocos2d.h"
USING_NS_CC;

static int player1score;
static int player2score;

class TpGameover :public Scene {
public:
	CREATE_FUNC(TpGameover);
	virtual bool init();
	virtual void update(float mt);
	static void getfinals(int i1, int i2);
private:
	double times = 0;

};


#endif