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
	void rotate();					//��תͼ��
	bool checkhit();
	void checkleft();				//��������ǽ��������ײ
	void checkright();
	void checkup();
	bool checkdown();

private:
	int speedup = 15;
	int score = 0;
	Label* scorelabel;
	int cleanrows = 0;
	Sprite* square[24][10];			//����˹����
	bool isshow[24][10];			//ȷ��Ҫ��ʾ�Ǹ�����
	Sprite* next[4][4];				//��ʾ��һ���ķ���
	bool nextshow[4][4];			//��ʾ��һ������
	int controlx = 3;				//ȷ���ƶ�����ĺ�����
	int controly = 0;				//���Ʒ�������
	double time = 0;
	double pretime = 0;
	double downspeed = 1.8;

	Shape cshape; int cnum;			//���Ƶķ���
	int snum;						//��ʾ����һ������

};


#endif // !__Playscene_H__
