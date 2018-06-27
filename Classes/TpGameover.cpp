#include"cocos2d.h"
#include"TpGameover.h"
#include "Playscene2.h"
#include "Hellotetris.h"
#include "ui/Cocosgui.h"
#include <string>
#include<fstream>
#include<vector>
#include <algorithm>
using namespace std;
USING_NS_CC;

void TpGameover::update(float mt) {
	times += mt;
	if (times > 4) Director::getInstance()->replaceScene(Hellotetris::create());
}

void TpGameover::getfinals(int i1, int i2) {
	player1score = i1;
	player2score = i2;
}

bool TpGameover::init() {
	auto background = Sprite::create("BG.png");
	if (background != nullptr) {
		background->setPosition(Vec2(512, 384));
		this->addChild(background);
	}
	auto size = Director::getInstance()->getVisibleSize();

	auto win = Label::create("Player " + to_string((player1score < player2score) + 1) + " win the game !!", "Maiandra GD", 48);
	win->setPosition(Vec2(size.width / 2, size.height / 2 + 100));
	this->addChild(win);

	auto p1 = Label::create("Player1's score : " + to_string(player1score), "Maiandra GD", 32);
	p1->setPosition(Vec2(size.width / 2, size.height / 2 - 50));
	this->addChild(p1);

	auto p2 = Label::create("Player2's score : " + to_string(player2score), "Maiandra GD", 32);
	p2->setPosition(Vec2(size.width / 2, size.height / 2 - 125));
	this->addChild(p2);

	auto button4 = ui::Button::create("Back.png", "Back-1.png", "Back-1.png");
	button4->setPosition(Vec2(size.width - button4->getCustomSize().width, 0 + button4->getCustomSize().height));
	button4->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: {
			Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f, Hellotetris::create()));
			break;
		}
		}
	});
	this->addChild(button4, 1);

	this->scheduleUpdate();

	return true;
}