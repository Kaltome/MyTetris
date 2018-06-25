#pragma once
#ifndef __Hellotetris_H__
#define __Hellotetris_H__
#include "cocos2d.h"
USING_NS_CC;

class Hellotetris :public Scene {
public:
	CREATE_FUNC(Hellotetris);
	virtual bool init();
private:
	Sprite * title;
};

#endif // !_Hellotetris_H__
