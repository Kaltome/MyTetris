#include"cocos2d.h"
#include"Gameoverscene.h"
#include "Playscene.h"
#include "Hellotetris.h"
#include "ui/Cocosgui.h"
#include <string>
#include<fstream>
#include<vector>
#include <algorithm>
using namespace std;
USING_NS_CC;
ofstream out("Scoreslist.txt", fstream::out);
ifstream in("Scoreslist.txt");

void Gameoverscene::output() {
	int score;
	int alllists = 1;
	vector<int> scorelist;
	while (in >> score) {
		scorelist.push_back(score);
		alllists++;
	}
	scorelist.push_back(finalscore);
	sort(scorelist.begin(), scorelist.end());
	for (int i = 0; i < alllists; i++) {
		if (scorelist[i] == finalscore) rank = i+1;
	}
	for (int i = 0; i < 5 && i<alllists; i++) {
		if (scorelist[i] < 0) scorelist[i] = 0;
		out << scorelist[i] << endl;
	}
}

void Gameoverscene::update(float mt) {
	exittime += mt;
	if(exittime > 4) 	Director::getInstance()->replaceScene(Hellotetris::create());
}

 void Gameoverscene::getfinal(int i, int j) {
	finalscore = i;
	finalspeed = j;
	
}

bool Gameoverscene::init() {
	output();
	auto background = Sprite::create("BG.png");
	if (background != nullptr) {
		background->setPosition(Vec2(512, 384));
		this->addChild(background);
	}

	auto size = Director::getInstance()->getVisibleSize();
	youloss = Sprite::create("Youloss.png");
	youloss->setPosition(Vec2(size.width / 2, size.height / 2 + 100));
	this->addChild(youloss);

	yourscore = Label::create("Your score : " + to_string(finalscore) , "Maiandra GD", 36);
	yourscore->setPosition(Vec2(size.width / 2, size.height / 2 - 50));
	this->addChild(yourscore);

	yourrank = Label::create("Your rank : " + to_string(rank), "Maiandra GD", 30);
	yourrank->setPosition(Vec2(size.width / 2, size.height / 2 - 100));
	this->addChild(yourrank);

	auto button4 = ui::Button::create("Back.png", "Back-1.png", "Back-1.png");
	button4->setPosition(Vec2(size.width - button4->getCustomSize().width, 0 + button4->getCustomSize().height));
	button4->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: {
			Director::getInstance()->replaceScene(Hellotetris::create());
			break;
		}
		}
	});
	this->addChild(button4, 1);

	this->scheduleUpdate();



	return true;
}