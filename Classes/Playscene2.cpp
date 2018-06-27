#include "Playscene2.h"
#include "cocos2d.h"
#include "Shape.h"
#include "ui/Cocosgui.h"
#include "TpGameover.h"
#include "Hellotetris.h"
#include "Square.h"
#include<string>
using namespace cocos2d;
using namespace std;

void Playscene2::getdspeed(double i) {
	ddownspeed = dorispeed = i;
}

int  Playscene2::addscore(Ctrlsquare& cplayer) {
	if (time == 0) return 0;
	return cplayer.cleanedrows / time * 120 + dorispeed;
}

void Playscene2::cleanrow(Ctrlsquare& cplayer,int crow) {
	cplayer.cleanedrows++;
	for (int i = crow; i > 0; i--) {
		for (int j = 0; j < 10; j++) {
			cplayer.isshow[i][j] = cplayer.isshow[i - 1][j];
		}
	}
}

void Playscene2::reset(Ctrlsquare& cplayer) {
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
			cleanrow(cplayer,i);
			i++;
		}
	}

	cplayer.cnum = cplayer.snum;
	cplayer.snum = CCRANDOM_0_1() * 7;

	cplayer.controlx = 3;
	cplayer.controly = 0;
}

bool Playscene2::checkgemeover(Ctrlsquare& cplayer) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			if (cplayer.isshow[i][j]) {
				//Gameoverscene::getfinal(cplayer.score, orispeed);
				return 1;
			}
		}
	}
	return 0;
}

void Playscene2::controlkeyevent1() {
	auto leftmove = EventListenerKeyboard::create();
	leftmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_A)
			player1.controlx--;
		if (checkhit(player1)) player1.controlx++;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(leftmove, this);

	auto rightmove = EventListenerKeyboard::create();
	rightmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_D)
			player1.controlx++;
		if (checkhit(player1)) player1.controlx--;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(rightmove, this);

	auto downmove = EventListenerKeyboard::create();
	downmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_S) {
			pretime1 = 0;
			downspeed1 = speedup;
		}
	};
	downmove->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_S); downspeed1 = dorispeed;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(downmove, this);

	auto shaperotate = EventListenerKeyboard::create();
	shaperotate->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
			rotate(player1);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(shaperotate, this);
}

void Playscene2::controlkeyevent2() {
	auto leftmove = EventListenerKeyboard::create();
	leftmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			player2.controlx--;
		if (checkhit(player2)) player2.controlx++;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(leftmove, this);

	auto rightmove = EventListenerKeyboard::create();
	rightmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			player2.controlx++;
		if (checkhit(player2)) player2.controlx--;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(rightmove, this);

	auto downmove = EventListenerKeyboard::create();
	downmove->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			pretime2 = 0;
			downspeed2 = speedup;
		}
	};
	downmove->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW); downspeed2 = dorispeed;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(downmove, this);

	auto shaperotate = EventListenerKeyboard::create();
	shaperotate->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event * event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ALT)
			rotate(player2);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(shaperotate, this);
}

bool Playscene2::checkhit(Ctrlsquare& cplayer) {
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

bool Playscene2::checkdown(Ctrlsquare& cplayer) {
	int downline = 0;
	int findend = 0;
	int ishit = 0;

	if (checkhit(cplayer)) {
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

	return (ishit || cplayer.controly == 23 - 3 + downline);
}

void Playscene2::checkup(Ctrlsquare& cplayer) {
	if (cplayer.controly < 0) cplayer.controly = 0;
}

void Playscene2::checkleft(Ctrlsquare& cplayer) {
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

void Playscene2::checkright(Ctrlsquare& cplayer) {
	int rightline = 0;
	for (int i = 3; i >= 0; i--) {
		int findend = 0;
		for (int j = 3; j >= 0; j--) {
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

void Playscene2::rotate(Ctrlsquare& cplayer) {
	Ctrlsquare copy = cplayer;
	if (cplayer.cnum == 6) return;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cplayer.shape[cplayer.cnum][i][j] = copy.shape[cplayer.cnum][3 - j][i];
		}
	}
	if (checkhit(cplayer)) cplayer = copy;
}

bool Playscene2::init() {
	downspeed1 = ddownspeed;
	downspeed2 = ddownspeed;

	auto background = Sprite::create("BG.png");
	if (background != nullptr) {
		background->setPosition(Vec2(512, 384));
		this->addChild(background);
	}
	
	auto size = Director::getInstance()->getVisibleSize();
	
	auto button4 = ui::Button::create("Back.png", "Back-1.png", "Back-1.png");
	button4->setPosition(Vec2(size.width/2, 0 + button4->getCustomSize().height/2+10));
	button4->addTouchEventListener([&](Ref* s, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED: {
			Director::getInstance()->replaceScene(Hellotetris::create());
			break;
		}
		}
	});
	this->addChild(button4, 1);

	auto squarebg1 = Sprite::create("Squarebg1.png");
	squarebg1->setAnchorPoint(Vec2(0, 0));
	squarebg1->setPosition(Vec2(7, -12));
	this->addChild(squarebg1);
	player1.gameoverbg = Sprite::create("Oneloss.png");
	player1.gameoverbg->setAnchorPoint(Vec2(0, 0));
	player1.gameoverbg->setPosition(Vec2(16, 0));
	player1.gameoverbg->setVisible(0);
	this->addChild(player1.gameoverbg,1);

	auto squarebg2 = Sprite::create("Squarebg2.png");
	squarebg2->setAnchorPoint(Vec2(0, 0));
	squarebg2->setPosition(Vec2(639, -12));
	this->addChild(squarebg2);
	player2.gameoverbg = Sprite::create("Oneloss.png");
	player2.gameoverbg->setAnchorPoint(Vec2(0, 0));
	player2.gameoverbg->setPosition(Vec2(648, 0));
	player2.gameoverbg->setVisible(0);
	this->addChild(player2.gameoverbg,1);

	int squarex = 16, squarey = 876;
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			square1[i][j] = Sprite::create("squares.png");
			square1[i][j]->setAnchorPoint(Vec2(0, 0));
			square1[i][j]->setPosition(squarex, squarey);
			this->addChild(square1[i][j]);
			squarex += 36;
		}
		squarex = 16;
		squarey -= 36;
	}

	squarex = 650, squarey = 876;
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			square2[i][j] = Sprite::create("squares.png");
			square2[i][j]->setAnchorPoint(Vec2(0, 0));
			square2[i][j]->setPosition(squarex, squarey);
			this->addChild(square2[i][j]);
			squarex += 36;
		}
		squarex = 650;
		squarey -= 36;
	}

	player1.scoretitle = Label::create("Score1 : ", "Maiandra GD", 36);
	player1.scoretitle->setPosition(Vec2(size.width / 2, 700));
	this->addChild(player1.scoretitle);
	player1.scorelabel = Label::create(to_string(player1.score), "Maiandra GD", 32);
	player1.scorelabel->setPosition(Vec2(size.width / 2, 650));
	this->addChild(player1.scorelabel);

	player2.scoretitle = Label::create("Score2 : ", "Maiandra GD", 36);
	player2.scoretitle->setPosition(Vec2(size.width / 2, 570));
	this->addChild(player2.scoretitle);
	player2.scorelabel = Label::create(to_string(player2.score), "Maiandra GD", 32);
	player2.scorelabel->setPosition(Vec2(size.width / 2, 520));
	this->addChild(player2.scorelabel);

	auto nextlabel1 = Label::create("Player1-next:", "Maiandra GD", 32);
	nextlabel1->setPosition(Vec2(size.width / 2, 420));
	this->addChild(nextlabel1);
	auto nextlabel2 = Label::create("Player2-next:", "Maiandra GD", 32);
	nextlabel2->setPosition(Vec2(size.width / 2, 220));
	this->addChild(nextlabel2);

	int showx = 440, showy = 360;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			next1[i][j] = Sprite::create("squares.png");
			next1[i][j]->setAnchorPoint(Vec2(0, 0));
			next1[i][j]->setPosition(showx, showy);
			this->addChild(next1[i][j]);
			showx += 36;
		}
		showx = 440;
		showy -= 36;
	}

	showx = 440, showy = 160;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			next2[i][j] = Sprite::create("squares.png");
			next2[i][j]->setAnchorPoint(Vec2(0, 0));
			next2[i][j]->setPosition(showx, showy);
			this->addChild(next2[i][j]);
			showx += 36;
		}
		showx = 440;
		showy -= 36;
	}

	player1.cnum = CCRANDOM_0_1() * 7;
	player2.cnum = CCRANDOM_0_1() * 7;
	player1.snum = CCRANDOM_0_1() * 7;
	player2.snum = CCRANDOM_0_1() * 7;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (player1.shape[player1.snum][i][j]) next1[i][j]->setVisible(180);
			else next1[i][j]->setVisible(0);
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (player2.shape[player2.snum][i][j]) next2[i][j]->setVisible(180);
			else next2[i][j]->setVisible(0);
		}
	}

	controlkeyevent1();
	controlkeyevent2();

	this->schedule(schedule_selector(Playscene2::update1));
	this->schedule(schedule_selector(Playscene2::update2));

	return true;
}

void Playscene2::update1(float mt1) {
	time += mt1;

	player1.score += addscore(player1);
	player1.scorelabel->setString(to_string(player1.score));

	pretime1 += mt1;
	if (pretime1 * downspeed1 >= 1) {
		player1.controly += pretime1 * downspeed1;
		pretime1 = 0;
	}

	for (int i = 4; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			if (player1.isshow[i][j] == 0) square1[i][j]->setOpacity(0);
			if (player1.isshow[i][j] == 1) square1[i][j]->setOpacity(220);
		}
	}

	auto change1 = checkdown(player1);
	checkup(player1);
	checkleft(player1);
	checkright(player1);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j + player1.controlx < 0 || j + player1.controlx > 9 || i + player1.controly > 23) continue;
			if (player1.shape[player1.cnum][i][j] == 1) square1[player1.controly + i][j + player1.controlx]->setOpacity(200);
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			square1[i][j]->setOpacity(0);
		}
	}

	if (change1) {
		reset(player1);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (player1.shape[player1.snum][i][j] == 1) next1[i][j]->setVisible(180);
				else next1[i][j]->setVisible(0);
			}
		}
		if (checkgemeover(player1)) {
			for (int i = 0; i < 24; i++) {
				for (int j = 0; j < 10; j++) {
					if (player1.isshow[i][j]) square1[i][j]->setVisible(50);
				}
			}
			player1.gameoverbg->setVisible(255);
			gameovernum++;
			if (gameovernum == 2) {
				Sleep(200);
				TpGameover::getfinals(player1.score, player2.score);
				Director::getInstance()->replaceScene(TpGameover::create());
			}
			this->unschedule(schedule_selector(Playscene2::update1));
		}
	}
}

void Playscene2::update2(float mt2) {
	player2.score += addscore(player2);
	player2.scorelabel->setString(to_string(player2.score));

	pretime2 += mt2;
	if (pretime2 * downspeed2 >= 1) {
		player2.controly += pretime2 * downspeed2;
		pretime2 = 0;
	}

	for (int i = 4; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			if (player2.isshow[i][j] == 0) square2[i][j]->setOpacity(0);
			if (player2.isshow[i][j] == 1) square2[i][j]->setOpacity(220);
		}
	}

	for (int i = 4; i < 24; i++) {
		for (int j = 0; j < 10; j++) {
			if (player2.isshow[i][j] == 0) square2[i][j]->setOpacity(0);
			if (player2.isshow[i][j] == 1) square2[i][j]->setOpacity(220);
		}
	}

	auto change2 = checkdown(player2);
	checkup(player2);
	checkleft(player2);
	checkright(player2);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (j + player2.controlx < 0 || j + player2.controlx > 9 || i + player2.controly > 23) continue;
			if (player2.shape[player2.cnum][i][j] == 1) square2[player2.controly + i][j + player2.controlx]->setOpacity(200);
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			square2[i][j]->setOpacity(0);
		}
	}

	if (change2) {
		reset(player2);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (player2.shape[player2.snum][i][j] == 1) next2[i][j]->setVisible(180);
				else next2[i][j]->setVisible(0);
			}
		}
		if (checkgemeover(player2)) {
			for (int i = 0; i < 24; i++) {
				for (int j = 0; j < 10; j++) {
					if (player2.isshow[i][j]) square2[i][j]->setVisible(50);
				}
			}
			player2.gameoverbg->setVisible(255);
			gameovernum++;
			if (gameovernum == 2) {
				Sleep(200);
				TpGameover::getfinals(player1.score, player2.score);
				Director::getInstance()->replaceScene(TpGameover::create());
			}
			this->unschedule(schedule_selector(Playscene2::update2));
		}
	}
}