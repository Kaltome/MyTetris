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
	Ctrlsquare cplayer;				//��ң�һ����
	int speedup = 15;				//��������ģʽ
	Sprite* square[24][10];			//����˹���龫��
	Sprite* next[4][4];				//��һ�����龫��
	double time = 0;				//��Ϸʱ��
	double pretime = 0;				//������������ʱ��
	int ispause = 1;				//��¼��ͣ

};
#endif // !__Playscene_H__
