#include "stdafx.h"
#include "demo.h"
#include "ColorsEngineer.h"

using namespace std;
using namespace cv;

void  ColorsEngineer::run(Mat &frame)
{
	//设定对比度和亮度的初值
	int iContrastValue = random(300);
	int iBrightValue = random(200);

	if (!frame.data) { printf("Oh，no，木有图像!~\n"); return; }
	Mat dstImage = Mat::zeros(frame.size(), frame.type());

	//三个for循环，执行运算 dstImage(i,j) =a*frame(i,j) + b
	for (int y = 0; y < frame.rows; y++)
	{
		for (int x = 0; x < frame.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((iContrastValue*0.01)*(frame.at<Vec3b>(y, x)[c]) + iBrightValue);
			}
		}
	}

	imshow(WINDOW_NAME, dstImage);
}

