/**************************************************************

						欢迎界面

***************************************************************/
#include"Hellotetris.h"
#include "cocos2d.h"
#include "ui/Cocosgui.h"
#include "Playscene.h"
#include "Choose.h"
#include "Scorelist.h"
USING_NS_CC;

bool Hellotetris::init() {
	//背景，开始游戏按钮，退出按钮，排行榜按钮
	auto background = Sprite::create("BG.png");
	if (background != nullptr) {
		background->setPosition(Vec2(512, 384));
		this->addChild(background);
	} 

	auto size = Director::getInstance()->getVisibleSize();																							//获取游戏界面大小

	title = Sprite::create("Title.png");																											//标题（精灵创建）
	title->setPosition(Vec2(size.width/2, size.height/2 + 150));																					//设置位置
	this->addChild(title);																															//添加到场景

	auto button1 = ui::Button::create("Start.png", "Start-1.png", "Start-1.png");																	//按钮创建
	button1->setPosition(Vec2(size.width/2, size.height/2-75));
	button1->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {																	//按钮监听
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3f,Choose::create()));			//切换场景动效
			break;
		}
	});
	this->addChild(button1, 3);

	auto button2 = ui::Button::create("Exit.png", "Exit-1.png", "Exit-1.png");
	button2->setPosition(Vec2(size.width / 2, size.height / 2 - 275));
	button2->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: Director::getInstance()->end();																		//退出游戏
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