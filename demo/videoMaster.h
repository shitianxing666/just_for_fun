#pragma once
#include <opencv2/opencv.hpp>

#define TYPE_SIZE 7

class LightEngineer;
class ContrastEngineer;
class SharpenEngineer;
class BlurEngineer;
class ColorsEngineer;
class OpticalFlowEngineer;

enum  FrameProcType {
	LIGHT_CHANGE = 0,
	CONTRAST_CHANGE ,
	SHARPEN,
	BLUR = 3,
	COLORS_INVERT,
	OPTICALFLOW = 5
};

class VideoMaster
{
public:
	typedef std::shared_ptr<VideoMaster> ptr;
	VideoMaster();
	~VideoMaster();
	void run(cv::Mat &frame);
private:
	LightEngineer *p_lightEngineer;
	ContrastEngineer *p_contrastEngineer;
	SharpenEngineer *p_sharpenEngineer;
	BlurEngineer *p_blurEngineer;
	ColorsEngineer *p_colorsEngineer;
	OpticalFlowEngineer *p_opticalFlowEngineer;
};
