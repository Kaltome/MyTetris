#pragma once
#ifndef __Playscene2_H__
#define __Playscene2_H__
#include "cocos2d.h"
#include "Shape.h"
#include "Square.h"
USING_NS_CC;

static double ddownspeed;
static double dorispeed;

class Playscene2 : public Scene {
public:
	CREATE_FUNC(Playscene2);
	virtual bool init();
	virtual void update1(float mt1);
	virtual void update2(float mt2);
	void controlkeyevent1();
	void controlkeyevent2();
	static void getdspeed(double i);
	int  addscore(Ctrlsquare& cplayer);
	void reset(Ctrlsquare& cplayer);
	void cleanrow(Ctrlsquare& cplayer,int crow);
	void rotate(Ctrlsquare& cplayer);
	bool checkgemeover(Ctrlsquare& cplayer);
	bool checkhit(Ctrlsquare& cplayer);
	void checkleft(Ctrlsquare& cplayer);				//¼ì²éÓë×ó±ßÇ½±ÚÓÐÎÞÅö×²
	void checkright(Ctrlsquare& cplayer);
	void checkup(Ctrlsquare& cplayer);
	bool checkdown(Ctrlsquare& cplayer);
private:
	Ctrlsquare player1;
	Ctrlsquare player2;
	double downspeed1;
	double downspeed2;
	int speedup = 15;
	Sprite* square1[24][10];
	Sprite* square2[24][10];
	Sprite* next1[4][4];
	Sprite* next2[4][4];
	double pretime1 = 0;
	double pretime2 = 0;	
	bool isgameover1 = 0;
	bool isgameover2 = 0;
	double time = 0;
	int ispause = 1;
};

#endif