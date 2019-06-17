#include "stdafx.h"
#include "demo.h"
#include "BlurEngineer.h"

using namespace std;
using namespace cv;

void BlurEngineer::run(Mat &frame)
{
	//载入原图
	if (!frame.data) { printf("Oh，no，木有图像~！\n"); return ; }

	int iBoxFilterValue = random(40);  //方框滤波参数值
	int iMeanBlurValue = random(40);  //均值滤波参数值
	int iGaussianBlurValue = random(40);  //高斯滤波参数值

	//克隆原图到三个Mat类型中
	Mat dstImage1 = frame.clone();
	Mat dstImage2 = frame.clone();
	Mat dstImage3 = frame.clone();

	switch (random(3))
	{
	case 1:
		boxFilter(frame, dstImage1, -1, Size(iBoxFilterValue + 1, iBoxFilterValue + 1));
		imshow(WINDOW_NAME, dstImage1);
		break;
	case 2:
		GaussianBlur(frame, dstImage3, Size(iGaussianBlurValue * 2 + 1, iGaussianBlurValue * 2 + 1), 0, 0);
		imshow(WINDOW_NAME, dstImage2);
		break;
	default:
		blur(frame, dstImage2, Size(iMeanBlurValue + 1, iMeanBlurValue + 1), Point(-1, -1));
		imshow(WINDOW_NAME, dstImage3);
		break;
	}

}
