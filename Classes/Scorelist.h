#pragma once
#pragma once
#ifndef __Scoreist_H__
#define __Scoreist_H__
#include "cocos2d.h"
#include "Playscene.h"
#include <vector>
using namespace std;
USING_NS_CC;

class Scorelist : public Scene {
public:
	CREATE_FUNC(Scorelist);
	virtual bool init();
private:
	vector<Label*> list;
};

#endif