#pragma once
#ifndef __Square_H__
#define __Square_H__
#include "cocos2d.h"
#include "Shape.h"
USING_NS_CC;

class Ctrlsquare :public Shape {
public:
	int score = 0;			//��ҷ���
	Sprite* gameoverbg;		//�����Ϸ������ʾͼƬ
	Label* scorelabel;		//������ǩ
	Label* scoretitle;		//������ǩ
	int cleanedrows = 0;	//������������
	bool isshow[24][10];	//��һ��۵ķ���
	bool nextshow[4][4];	//��һ���������ʾ
	int controlx = 3;		//��ҿ��Ƶķ���ĺ�����
	int controly = 0;		//��ҿ��Ƶķ����������
	int cnum;				//��ҿ��Ƶķ��������
	int snum;				//�����һ�����������
	bool isloss = 0;		//��¼�Ƿ�����
};

#endif // !__Square_H__

