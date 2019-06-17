#pragma once

#include "resource.h"

#define WINDOW_NAME "过场动画"
#define CONFIG_VIDEO_PATH  "\\config\\video\\1.avi"
#define CONFIG_IMG_PATH  "\\config\\img\\"
#define CONFIG_ICON_PATH "\\config\\icon\\"
#define JPG  ".jpg"
#define PNG  ".png"
#define IMG_SIZE  7

#define random(x) (rand()%x)

enum ImgListIndex {
	CHARATOR_SCARY = 0,
};

class Demo {
public:
	void run();
};
