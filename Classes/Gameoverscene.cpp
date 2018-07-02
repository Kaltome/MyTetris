/**************************************************************

					游戏结束（单人）场景

***************************************************************/
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

//排行榜读取、输出
void Gameoverscene::output() {
	ofstream out;
	ifstream in("Scoreslist.txt", ifstream::app);
	int score;
	int alllists = 1;													//记录读取的分数的数量
	vector<int> scorelist;												//存储分数
	while (in >> score) {												//读取
		scorelist.push_back(score);
		alllists++;
	}
	scorelist.push_back(finalscore);
	sort(scorelist.begin(), scorelist.end());							//排序算法
	for (int i = alllists; i > 0; i--) {
		if (scorelist[i-1] == finalscore) rank = alllists-i+1;			//寻找排名（大到小）
	}
	out.open("Scoreslist.txt",fstream::out);							//输出
	for (int i = alllists; i>0 && i>alllists - 6; i--) {
		out << scorelist[i-1] << endl;
	}

}

//控制自动回到主界面
void Gameoverscene::update(float mt) {
	exittime += mt;
	if(exittime > 4) 	Director::getInstance()->replaceScene(Hellotetris::create());
}

//从单人游戏界面获取最终分数
 void Gameoverscene::getfinal(int i, int j) {
	finalscore = i;
	finalspeed = j;
}

bool Gameoverscene::init() {
	output();

	//背景，标题，最终分数，排名显示
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

	//返回按钮
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