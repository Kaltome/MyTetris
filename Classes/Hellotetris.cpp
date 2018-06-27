#include"Hellotetris.h"
#include "cocos2d.h"
#include "ui/Cocosgui.h"
#include "Playscene.h"
#include "Choose.h"
#include "Scorelist.h"
USING_NS_CC;

bool Hellotetris::init() {
	auto background = Sprite::create("BG.png");
	if (background != nullptr) {
		background->setPosition(Vec2(512, 384));
		this->addChild(background);
	} 

	auto size = Director::getInstance()->getVisibleSize();

	title = Sprite::create("Title.png");
	title->setPosition(Vec2(size.width/2, size.height/2 + 150));
	this->addChild(title);

	auto button1 = ui::Button::create("Start.png", "Start-1.png", "Start-1.png");
	button1->setPosition(Vec2(size.width/2, size.height/2-75));
	button1->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f,Choose::create()));
			break;
		}
	});
	this->addChild(button1, 3);

	auto button2 = ui::Button::create("Exit.png", "Exit-1.png", "Exit-1.png");
	button2->setPosition(Vec2(size.width / 2, size.height / 2 - 275));
	button2->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: Director::getInstance()->end();
			break;
		}
	});
	this->addChild(button2, 3);


	auto button3 = ui::Button::create("score list.png", "score list.png", "score list.png");
	button3->setPosition(Vec2(size.width / 2, size.height / 2 - 175));
	button3->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f, Scorelist::create()));
			break;
		}
	});
	this->addChild(button3, 3);

	return true;
}