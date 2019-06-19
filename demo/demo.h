#pragma once

#include "resource.h"
#include <string>

#define WINDOW_NAME "过场动画"
#define JPG  ".jpg"
#define PNG  ".png"

#define random(x) (rand()%(x))

enum ImgListIndex {
	CHARATOR_SCARY = 0,
};

class Demo {
public:
	Demo();
	void run();
private:
	std::string m_workPath;
	std::string m_ymlPath;
	std::string m_videoPath;
	std::string m_imgPath;
	std::string m_iconPath;
	int m_imgSize;
};
