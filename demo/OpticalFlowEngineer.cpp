#include "stdafx.h"
#include "demo.h"
#include "OpticalFlowEngineer.h"

using namespace std;
using namespace cv;

static Mat gray;	// 当前图片
static Mat gray_prev;	// 预测图片
static vector<Point2f> points[2];	// point0为特征点的原来位置，point1为特征点的新位置
static vector<Point2f> initial;	// 初始化跟踪点的位置
static vector<Point2f> features;	// 检测的特征
static int maxCount = 500;	// 检测的最大特征数
static double qLevel = 0.01;	// 特征检测的等级
static double minDist = 10.0;	// 两特征点之间的最小距离
static vector<uchar> status;	// 跟踪特征的状态，特征的流发现为1，否则为0
static vector<float> err;

static bool addNewPoints();
static bool acceptTrackedPoint(int i);

//-------------------------------------------------------------------------------------------------
// brief: 跟踪
// parameter: frame	输入的视频帧
//			  output 有跟踪结果的视频帧
// return: void
//-------------------------------------------------------------------------------------------------
void OpticalFlowEngineer::run(Mat &frame)
{
	Mat output;
	cvtColor(frame, gray, COLOR_BGR2GRAY);
	frame.copyTo(output);

	// 添加特征点
	if (addNewPoints())
	{
		goodFeaturesToTrack(gray, features, maxCount, qLevel, minDist);
		points[0].insert(points[0].end(), features.begin(), features.end());
		initial.insert(initial.end(), features.begin(), features.end());
	}

	if (gray_prev.empty())
	{
		gray.copyTo(gray_prev);
	}
	// l-k光流法运动估计
	calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);
	// 去掉一些不好的特征点
	int k = 0;
	for (size_t i = 0; i < points[1].size(); i++)
	{
		if (acceptTrackedPoint(i))
		{
			initial[k] = initial[i];
			points[1][k++] = points[1][i];
		}
	}
	points[1].resize(k);
	initial.resize(k);
	// 显示特征点和运动轨迹
	for (size_t i = 0; i < points[1].size(); i++)
	{
		line(output, initial[i], points[1][i], Scalar(0, 0, 255));
		circle(output, points[1][i], 3, Scalar(0, 255, 0), -1);
	}

	// 把当前跟踪结果作为下一此参考
	swap(points[1], points[0]);
	swap(gray_prev, gray);

	imshow(WINDOW_NAME, output);
}

//-------------------------------------------------------------------------------------------------
// function: addNewPoints
// brief: 检测新点是否应该被添加
// parameter:
// return: 是否被添加标志
//-------------------------------------------------------------------------------------------------
bool addNewPoints()
{
	return points[0].size() <= 10;
}

//-------------------------------------------------------------------------------------------------
// function: acceptTrackedPoint
// brief: 决定哪些跟踪点被接受
// parameter:
// return:
//-------------------------------------------------------------------------------------------------
bool acceptTrackedPoint(int i)
{
	return status[i] && ((abs(points[0][i].x - points[1][i].x) + abs(points[0][i].y - points[1][i].y)) > 2);
}
