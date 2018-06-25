#include "Playscene.h"
#include "cocos2d.h"
#include "Shape.h"
#include "Gameoverscene.h"
#include<string>
using namespace cocos2d;
using namespace std;

int  Playscene::addscore() {
	if (time == 0) return 0;
	return cleanrows / time * 300 + 3;
}

void Playscene::controlkeyevent() {
	auto leftmove = EventListenerKeyboard::create();
	leftmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			controlx--;
		if (checkhit()) controlx++;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(leftmove, this);

	auto rightmove = EventListenerKeyboard::create();
	rightmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			controlx++;
		if (checkhit()) controlx--;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(rightmove, this);

	auto downmove = EventListenerKeyboard::create();
	downmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			Sleep(100);
			pretime = 0;
			downspeed = speedup;
		}

	};
	downmove->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) downspeed = 1.8;
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
	cleanrows++;
	for (int i = crow; i > 0; i--) {
		for (int j = 0; j < 10; j++) {
			isshow[i][j] = isshow[i - 1][j];
		}
	}
}

void Playscene::reset() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cshape.shape[cnum][i][j] == 1)
			isshow[controly + i][controlx + j] = cshape.shape[cnum][i][j];
		}
	}

	for (int i = 23; i >= 0; i--) {
		int numperrow = 0;
		for (int j = 0; j < 10; j++) {
			if (isshow[i][j] == 1) numperrow++;
		}
		if (numperrow == 10) {
			cleanrow(i);
			i++;
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			if (isshow[i][j]) {
				Sleep(200);
				Gameoverscene::getfinalscore(score);
				Director::getInstance()->replaceScene(Gameoverscene::create());
			}
		}
	}

	cnum = snum;
	snum = CCRANDOM_0_1() * 7;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cshape.shape[snum][i][j]) next[i][j]->setVisible(200);
			else next[i][j]->setVisible(0);
		}
	}

	controlx = 4;
	controly = 0;

}

bool Playscene::checkhit() {
	int hit = 0;
	for (int i = 3; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (cshape.shape[cnum][i][j] == 1 && isshow[controly + i][controlx + j] == 1) {
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
		controly--;
	}

	for (int i = 3; i >= 0; i--) {
		for (int j = 0; j < 4; j++) {
			if (cshape.shape[cnum][i][j] == 1) {
				findend = 1;
				break;
			}
		}			
		if (findend == 1) break;
		downline++;
	}
	if (controly + 3 - downline >= 23) controly = 23 - 3 + downline;

	return (ishit|| controly == 23 - 3 + downline);
}

void Playscene::checkup() {
	if (controly < 0) controly = 0;
}

void Playscene::checkleft() {
	int leftline = 0;
	for (int i = 0; i < 4; i++) {
		int findend = 0;
		for (int j = 0; j < 4; j++) {
			if (cshape.shape[cnum][j][i] == 1) {
				findend = 1;
				break;
			}
		}
		if (findend == 1)break;
		leftline++;
	}
	if (controlx < 0 - leftline) controlx = 0 - leftline;
}

void Playscene::checkright() {
	int rightline = 0;
	for (int i = 3; i >= 0; i--) {
		int findend = 0;
		for (int j = 3; j >=0 ; j--) {
			if (cshape.shape[cnum][j][i] == 1) {
				findend = 1;
				break;
			}
		}
		if (findend == 1)break;
		rightline++;
	}
	if (controlx > 9 - 3 + rightline) controlx = 9 - 3 + rightline;
}

void Playscene::rotate() {
	Shape copy = cshape;
	if (cnum == 6) return;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
 			cshape.shape[cnum][i][j] = copy.shape[cnum][3 - j][i];
		}
	}
	if (checkhit()) cshape = copy;
}

void Playscene::resetisshow() {
	for (int i = 4; i < 24; i++) {
		for (int j = 0; j < 12; j++) {
			isshow[i][j] = 0;
		}
	}
}

bool Playscene::init() {

	cnum = CCRANDOM_0_1() * 7;
	snum = CCRANDOM_0_1() * 7;

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

	int showx = 624, showy = 384;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			next[i][j] = Sprite::create("squares.png");
			next[i][j]->setAnchorPoint(Vec2(0, 0));
			next[i][j]->setPosition(showx, showy);
			this->addChild(next[i][j]);
			showx += 36;
		}
		showx = 624;
		showy -= 36;
	}

	scorelabel = Label::create("Score : "+to_string(score), "Maiandra GD", 36);
	scorelabel->setAnchorPoint(Vec2(0, 0));
	scorelabel->setPosition(Vec2(624, 624));
	this->addChild(scorelabel);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cshape.shape[snum][i][j]) next[i][j]->setVisible(200);
			else next[i][j]->setVisible(0);
		}
	}

	controlkeyevent();


	
	this->scheduleUpdate();

	return true;
}

void Playscene::update(float mt) {

	score += addscore();
	scorelabel->setString("Score : " + to_string(score));


	time += mt;
	pretime += mt;
	if (pretime * downspeed >= 1) {
		controly += pretime* downspeed;
		pretime = 0;
	}

	for (int i = 4; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			if (isshow[i][j] == 0) square[i][j]->setOpacity(0);
			if (isshow[i][j] == 1) square[i][j]->setOpacity(200);
		}
	}

	auto change = checkdown();
	checkup();
	checkleft();
	checkright();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j + controlx < 0 || j + controlx > 19||i + controly > 23) continue;
			if (cshape.shape[cnum][i][j] == 1) square[controly+i][j+controlx]->setOpacity(200);
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			 square[i][j]->setOpacity(0);
		}
	}

	if (change) reset();
}