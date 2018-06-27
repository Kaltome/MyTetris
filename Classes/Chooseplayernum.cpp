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

bool Choosenum::init() {
	
	auto background = Sprite::create("BG.png");
	if (background != nullptr) {
		background->setPosition(Vec2(512, 384));
		this->addChild(background);
	}

	auto size = Director::getInstance()->getVisibleSize();

	auto ntitle = Sprite::create("Title.png");
	ntitle->setPosition(Vec2(size.width / 2, size.height / 2 + 150));
	this->addChild(ntitle);

	auto button1 = ui::Button::create("Single-player  Mode.png", "Single-player  Mode-1.png", "Single-player  Mode-1.png");
	button1->setPosition(Vec2(size.width / 2, size.height / 2 - 120));
	button1->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: {
			Director::getInstance()->replaceScene(Playscene::create());
			break;
		}
		}
	});
	this->addChild(button1, 1);

	auto button2 = ui::Button::create("Two-player  Mode.png", "Two-player  Mode-1.png", "Two-player  Mode-1.png");
	button2->setPosition(Vec2(size.width / 2, size.height / 2 - 250));
	button2->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: {
			Director::getInstance()->replaceScene(Playscene2::create());
			break;
		}
		}
	});
	this->addChild(button2, 1);

	auto button4 = ui::Button::create("Back.png", "Back-1.png", "Back-1.png");
	button4->setPosition(Vec2(size.width - button4->getCustomSize().width, 0 + button4->getCustomSize().height));
	button4->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: {
			Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f, Choose::create()));
			break;
		}
		}
	});
	this->addChild(button4, 1);
	return true;
}