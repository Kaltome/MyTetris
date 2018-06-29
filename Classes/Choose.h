//选择难度场景（下落速度）

#pragma once
#ifndef __Choose_H__
#define __Choose_H__
#include "cocos2d.h"
#include "Playscene.h"
USING_NS_CC;

class Choose : public Scene {
public:
	CREATE_FUNC(Choose);
	virtual bool init();

};

#endif