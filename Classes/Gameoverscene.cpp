#include"cocos2d.h"
#include"Gameoverscene.h"
#include "Playscene.h"
#include "Hellotetris.h"
#include <string>
using namespace std;
USING_NS_CC;

void Gameoverscene::update(float mt) {
	exittime += mt;
	if(exittime > 5) 	Director::getInstance()->replaceScene(Hellotetris::create());
}

 void Gameoverscene::getfinalscore(int i) {
	finalscore = i;
}

bool Gameoverscene::init() {
	auto background = Sprite::create("BG.png");
	if (background != nullptr) {
		background->setPosition(Vec2(512, 384));
		this->addChild(background);
	}

	auto size = Director::getInstance()->getVisibleSize();
	youloss = Sprite::create("Youloss.png");
	youloss->setPosition(Vec2(size.width / 2, size.height / 2 + 100));
	this->addChild(youloss);

	yourscore = Label::create("Your score : " + to_string(finalscore), "Maiandra GD", 36);
	yourscore->setPosition(Vec2(size.width / 2, size.height / 2 - 50));
	this->addChild(yourscore);

	this->scheduleUpdate();

	
	return true;
}