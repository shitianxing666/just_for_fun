#include "stdafx.h"
#include "demo.h"
#include "SharpenEngineer.h"

using namespace std;
using namespace cv;

void SharpenEngineer::run(Mat &frame)
{
	//创建并初始化滤波模板
     cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));
     kernel.at<float>(1, 1) = 5.0;
     kernel.at<float>(0, 1) = -1.0;
     kernel.at<float>(1, 0) = -1.0;
     kernel.at<float>(1, 2) = -1.0;
     kernel.at<float>(2, 1) = -1.0;

     Mat result(frame.size(), frame.type());

     //对图像进行滤波
     cv::filter2D(frame, result, frame.depth(), kernel);

	 imshow(WINDOW_NAME, result);
}
