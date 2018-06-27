#include "Scorelist.h"
#include"cocos2d.h"
#include "Playscene.h"
#include "Hellotetris.h"
#include <string>
#include<fstream>
#include<vector>
#include <algorithm>
#include "ui/Cocosgui.h"
using namespace std;
USING_NS_CC;
ifstream inn("Scoreslist.txt", ifstream::in);

 bool Scorelist::init() {
	 int scores = 0;
	 auto x = 600;
	 int i = 0;
	 auto size = Director::getInstance()->getVisibleSize();

	 auto background = Sprite::create("BG.png");
	 if (background != nullptr) {
		 background->setPosition(Vec2(512, 384));
		 this->addChild(background);
	 }

	 while(inn >> scores) {
		 list.push_back(Label::create(to_string(scores), "Maiandra GD", 56));
		 list[i]->setPosition(Vec2(size.width / 2, x));
		 this->addChild(list[i]);
		 i++;
		 x -= 80;
	 }

	 auto button2 = ui::Button::create("Exit.png", "Exit-1.png", "Exit-1.png");
	 button2->setPosition(Vec2(size.width / 2, 50));
	 button2->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		 switch (type) {
		 case ui::Widget::TouchEventType::ENDED: Director::getInstance()->replaceScene(Hellotetris::create());
			 break;
		 }
	 });
	 this->addChild(button2, 3);

	 return true;
}