#include"Hellotetris.h"
#include "cocos2d.h"
#include "ui/Cocosgui.h"
#include "Playscene.h"
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
		case ui::Widget::TouchEventType::ENDED: Director::getInstance()->replaceScene(Playscene::create());
			break;
		}
	});
	this->addChild(button1, 3);



	return true;
}