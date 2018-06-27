#include"cocos2d.h"
#include"Choose.h"
#include "Playscene.h"
#include "Playscene2.h"
#include "Chooseplayernum.h"
#include "Hellotetris.h"
#include "ui/Cocosgui.h"
#include <string>
using namespace std;
USING_NS_CC;

bool Choose::init() {
	auto background = Sprite::create("BG.png");
	if (background != nullptr) {
		background->setPosition(Vec2(512, 384));
		this->addChild(background);
	}

	auto size = Director::getInstance()->getVisibleSize();

	auto ctitle = Sprite::create("Title.png");
	ctitle->setPosition(Vec2(size.width / 2, size.height / 2 + 150));
	this->addChild(ctitle);

	auto button1 = ui::Button::create("Naive.png", "Naive-1.png", "Naive-1.png");
	button1->setPosition(Vec2(size.width / 2, size.height / 2 - 75));
	button1->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
			case ui::Widget::TouchEventType::ENDED: {
			Director::getInstance()->replaceScene(Choosenum::create());
			Playscene::getspeed(1);
			Playscene2::getdspeed(1);
			break; 
			}
		}
	});
	this->addChild(button1, 1);

	auto button2 = ui::Button::create("Normal.png", "Normal-1.png", "Normal-1.png");
	button2->setPosition(Vec2(size.width / 2, size.height / 2 - 175));
	button2->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: {
			Director::getInstance()->replaceScene(Choosenum::create());
			Playscene::getspeed(2);
			Playscene2::getdspeed(2);
			break;
		}
		}
	});
	this->addChild(button2, 1);

	auto button3 = ui::Button::create("Hard.png", "Hard-1.png", "Hard-1.png");
	button3->setPosition(Vec2(size.width / 2, size.height / 2 - 275));
	button3->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: {
			Director::getInstance()->replaceScene(Choosenum::create());
			Playscene::getspeed(3);
			Playscene2::getdspeed(3);
			break;
		}
		}
	});
	this->addChild(button3, 1);

	auto button4 = ui::Button::create("Back.png", "Back-1.png", "Back-1.png");
	button4->setPosition(Vec2(size.width - button4->getCustomSize().width, 0+ button4->getCustomSize().height ));
	button4->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: {
			Director::getInstance()->replaceScene(Hellotetris::create());
			break;
		}
		}
	});
	this->addChild(button4, 1);

	return true;
}