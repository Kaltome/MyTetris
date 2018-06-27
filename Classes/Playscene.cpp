#include "Playscene.h"
#include "cocos2d.h"
#include "Shape.h"
#include "Gameoverscene.h"
#include "Hellotetris.h"
#include "ui/Cocosgui.h"
#include "Square.h"
#include<string>
using namespace cocos2d;
using namespace std;

void Playscene::getspeed(double i) {
	downspeed = i;
	orispeed = i;
}

int  Playscene::addscore() {
	if (time == 0) return 0;
	return cplayer.cleanedrows / time * 150 + 1;
}

void Playscene::controlkeyevent() {
	auto pausegame1 = EventListenerKeyboard::create();
	pausegame1->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) ispause++;
		if (ispause % 2) this->scheduleUpdate();
		else this->unscheduleUpdate();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(pausegame1, this);

	auto leftmove = EventListenerKeyboard::create();
	leftmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			cplayer.controlx--;
		if (checkhit()) cplayer.controlx++;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(leftmove, this);

	auto rightmove = EventListenerKeyboard::create();
	rightmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			cplayer.controlx++;
		if (checkhit()) cplayer.controlx--;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(rightmove, this);

	auto downmove = EventListenerKeyboard::create();
	downmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			pretime = 0;
			downspeed = speedup;
		}
	};
	downmove->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) downspeed = orispeed;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(downmove, this);

	auto shaperotate = EventListenerKeyboard::create();
	shaperotate->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
			rotate();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(shaperotate, this);
}

void Playscene::cleanrow(int crow) {
	cplayer.cleanedrows++;
	for (int i = crow; i > 0; i--) {
		for (int j = 0; j < 10; j++) {
			cplayer.isshow[i][j] = cplayer.isshow[i - 1][j];
		}
	}
}

void Playscene::reset() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cplayer.shape[cplayer.cnum][i][j] == 1)
				cplayer.isshow[cplayer.controly + i][cplayer.controlx + j] = cplayer.shape[cplayer.cnum][i][j];
		}
	}

	for (int i = 23; i >= 0; i--) {
		int numperrow = 0;
		for (int j = 0; j < 10; j++) {
			if (cplayer.isshow[i][j] == 1) numperrow++;
		}
		if (numperrow == 10) {
			cleanrow(i);
			i++;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			if (cplayer.isshow[i][j]) {
				Sleep(200);
				Gameoverscene::getfinal(cplayer.score, orispeed);
				Director::getInstance()->replaceScene(Gameoverscene::create());
			}
		}
	}

	cplayer.cnum = cplayer.snum;
	cplayer.snum = CCRANDOM_0_1() * 7;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cplayer.shape[cplayer.snum][i][j] == 1) next[i][j]->setVisible(180);
			else next[i][j]->setVisible(0);
		}
	}

	cplayer.controlx = 3;
	cplayer.controly = 0;
}

bool Playscene::checkhit() {
	int hit = 0;
	for (int i = 3; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (cplayer.shape[cplayer.cnum][i][j] == 1 && cplayer.isshow[cplayer.controly + i][cplayer.controlx + j] == 1) {
				hit = 1;
			}
		}
	}
	return hit;
}

bool Playscene::checkdown() {
	int downline = 0;
	int findend = 0;
	int ishit = 0;

	if (checkhit()) {
		ishit = 1;
		cplayer.controly--;
	}

	for (int i = 3; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (cplayer.shape[cplayer.cnum][i][j] == 1) {
				findend = 1;
				break;
			}
		}			
		if (findend == 1) break;
		downline++;
	}
	if (cplayer.controly + 3 - downline >= 23) cplayer.controly = 23 - 3 + downline;

	return (ishit|| cplayer.controly == 23 - 3 + downline);
}

void Playscene::checkup() {
	if (cplayer.controly < 0) cplayer.controly = 0;
}

void Playscene::checkleft() {
	int leftline = 0;
	for (int i = 0; i < 4; i++) {
		int findend = 0;
		for (int j = 0; j < 4; j++) {
			if (cplayer.shape[cplayer.cnum][j][i] == 1) {
				findend = 1;
				break;
			}
		}
		if (findend == 1)break;
		leftline++;
	}
	if (cplayer.controlx < 0 - leftline) cplayer.controlx = 0 - leftline;
}

void Playscene::checkright() {
	int rightline = 0;
	for (int i = 3; i >= 0; i--) {
		int findend = 0;
		for (int j = 3; j >=0 ; j--) {
			if (cplayer.shape[cplayer.cnum][j][i] == 1) {
				findend = 1;
				break;
			}
		}
		if (findend == 1)break;
		rightline++;
	}
	if (cplayer.controlx > 9 - 3 + rightline) cplayer.controlx = 9 - 3 + rightline;
}

void Playscene::rotate() {
	Ctrlsquare copy = cplayer;
	if (cplayer.cnum == 6) return;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cplayer.shape[cplayer.cnum][i][j] = copy.shape[cplayer.cnum][3 - j][i];
		}
	}
	if (checkhit()) cplayer = copy;
}

bool Playscene::init() {

	cplayer.cnum = CCRANDOM_0_1() * 7;
	cplayer.snum = CCRANDOM_0_1() * 7;


	auto background = Sprite::create("BG.png");
	if (background != nullptr) {
		background->setPosition(Vec2(512, 384));
		this->addChild(background);
	}

	auto squarebg = Sprite::create("Squarebg.png");
	squarebg->setAnchorPoint(Vec2(0, 0));
	squarebg->setPosition(Vec2(104, -12));
	this->addChild(squarebg);

	int squarex = 112, squarey = 876;
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			square[i][j] = Sprite::create("squares.png");
			square[i][j]->setAnchorPoint(Vec2(0, 0));
			square[i][j]->setPosition(squarex, squarey);
			this->addChild(square[i][j]);			
			squarex += 36;
		}
		squarex = 112;
		squarey -= 36;
	}

	int showx = 656, showy = 448;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			next[i][j] = Sprite::create("squares.png");
			next[i][j]->setAnchorPoint(Vec2(0, 0));
			next[i][j]->setPosition(showx, showy);
			this->addChild(next[i][j]);
			showx += 36;
		}
		showx = 656;
		showy -= 36;
	}

	cplayer.scorelabel = Label::create("Score : "+to_string(cplayer.score), "Maiandra GD", 36);
	cplayer.scorelabel->setAnchorPoint(Vec2(0, 0));
	cplayer.scorelabel->setPosition(Vec2(648, 624));
	this->addChild(cplayer.scorelabel);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cplayer.shape[cplayer.snum][i][j]) next[i][j]->setVisible(200);
			else next[i][j]->setVisible(0);
		}
	}

	controlkeyevent();

	auto size = Director::getInstance()->getVisibleSize();
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

void Playscene::update(float mt) {

	cplayer.score += addscore();
	cplayer.scorelabel->setString("Score : " + to_string(cplayer.score));

	time += mt;
	pretime += mt;
	if (pretime * downspeed >= 1) {
		cplayer.controly += pretime* downspeed;
		pretime = 0;
	}

	for (int i = 4; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			if (cplayer.isshow[i][j] == 0) square[i][j]->setOpacity(0);
			if (cplayer.isshow[i][j] == 1) square[i][j]->setOpacity(220);
		}
	}

	auto change = checkdown();
	checkup();
	checkleft();
	checkright();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j + cplayer.controlx < 0 || j + cplayer.controlx > 19||i + cplayer.controly > 23) continue;
			if (cplayer.shape[cplayer.cnum][i][j] == 1) square[cplayer.controly+i][j+ cplayer.controlx]->setOpacity(200);
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			 square[i][j]->setOpacity(0);
		}
	}

	if (change) reset();
}