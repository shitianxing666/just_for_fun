#include "stdafx.h"
#include "demo.h"
#include "videoMaster.h"
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <direct.h>  
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void Demo::run()
{
	char path_buffer[MAX_PATH];
	_getcwd(path_buffer, MAX_PATH);
	string work_path = path_buffer;
	if (!work_path.data()) {
		cout << "work_path error" << endl;
		return;
	}

	// 带标题栏和菜单栏
	//int window_width = GetSystemMetrics(SM_CXSCREEN);
	//int window_height = GetSystemMetrics(SM_CYSCREEN);
	// 不带标题栏和菜单栏
	int window_width = GetSystemMetrics(SM_CXFULLSCREEN);
	int window_height = GetSystemMetrics(SM_CYFULLSCREEN);
	std::cout << "have not menu bar width:" << window_width << std::endl;
	std::cout << "have not menu bar height:" << window_height << std::endl;

	//设置窗口大小可变
	cvNamedWindow(WINDOW_NAME, 0);
	//设置窗口大小与屏幕分辨率统一
	cvResizeWindow(WINDOW_NAME, window_width, window_height);
	//将窗口左上角移至屏幕左上角
	cvMoveWindow(WINDOW_NAME, 0, 0);

#if 0
	/*opencv设置动画序列帧*/
	vector<Mat> imgList;
	for (int i = 0; i < IMG_SIZE; i++) {
		string img_path = work_path + CONFIG_IMG_PATH + to_string(i) + JPG;
		imgList.emplace_back(imread(img_path, IMREAD_COLOR));
	}

	for (auto i = 0; i < IMG_SIZE; i++) {
		cout << i << endl;
		//imshow(WINDOW_NAME, imgList[i]);
		waitKey(20); //20ms
	}
#endif

	Mat frame;
	//string cmd = SYSTEM_CMD_START + work_path + CONFIG_ETC_PATH;

	VideoCapture capture((work_path + CONFIG_VIDEO_PATH).data());

	if (capture.isOpened())	// 摄像头读取文件开关
	{
		while (true)
		{
			capture >> frame;

			if (!frame.empty())
			{
				VideoMaster videoMaster;
				videoMaster.run(frame);
				//imshow(WINDOW_NAME, frame);
			}
			else
			{
				printf(" --(!) No captured frame -- Break!");
				break;
			}
			//每隔50ms刷新一次
			int c = waitKey(50);
			//按X键直接运行窗口效果
			if ((char)c == 'x') {
				//system(cmd.data());
				return;
			}
			//按ESC键直接跳出视频运行窗口效果
			if ((char)c == 27)
			{
				break;
			}
		}
	}
}
