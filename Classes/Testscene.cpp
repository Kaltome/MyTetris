/**************************************************************
	
						����ר�ó���

***************************************************************/

#include "cocos2d.h"
#include<string>
#include <vector>
using namespace std;
USING_NS_CC;
#include "Testscene.h"



bool testfile::init() {

	auto tests = FileUtils::getInstance()->getStringFromFile("test.txt");


	vector<int> nums;
	size_t size = tests.size();
	size_t pos;
	for (size_t i = 0; i<size; i++)
	{
		pos = tests.find("\n", i);
		if (pos<size)
		{
			nums.push_back(stoi(tests.substr(i, pos - i - 1)));
			/*�˴�s����ȡ���ĵ�����Ϣ*/
			i = pos;
		}
	}

	//    for (int i = 0; i < bufferSize; ++i)
	//        
	//    {
	//        
	//        CCLog("%c",pBuffer[i]);
	//        
	//    }

	auto label = Label::create(to_string(nums[1]), "Maiandra GD", 30);
	label->setPosition(Vec2(500, 500));
	this->addChild(label);

	
	return true;
}