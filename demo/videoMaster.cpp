#include "stdafx.h"
#include "videoMaster.h"
#include "demo.h"
#include "LightEngineer.h"
#include "ContrastEngineer.h"
#include "SharpenEngineer.h"
#include "BlurEngineer.h"
#include "ColorsEngineer.h"
#include "OpticalFlowEngineer.h"

using namespace std;
using namespace cv;

VideoMaster::VideoMaster() 
{
	p_lightEngineer = new LightEngineer;
	p_contrastEngineer = new ContrastEngineer;
	p_sharpenEngineer = new SharpenEngineer ;
	p_blurEngineer = new BlurEngineer;
	p_colorsEngineer = new ColorsEngineer;
	p_opticalFlowEngineer = new OpticalFlowEngineer;
}

VideoMaster::~VideoMaster()
{
	delete p_lightEngineer;
	delete p_contrastEngineer;
	delete p_sharpenEngineer;
	delete p_blurEngineer;
	delete p_colorsEngineer;
	delete p_opticalFlowEngineer;
}


void VideoMaster::run(Mat &frame)
{
	int type = random(TYPE_SIZE);
	cout << "current type is ---> " << type << endl;
	switch (type)
	{
	case LIGHT_CHANGE:
		p_lightEngineer->run(frame);
		break;
	case CONTRAST_CHANGE:
		p_contrastEngineer->run(frame);
		break;
	case SHARPEN:
		p_sharpenEngineer->run(frame);
		break;
	case BLUR:
		p_blurEngineer->run(frame);
		break;
	case COLORS_INVERT:
		p_colorsEngineer->run(frame);
		break;
	case OPTICALFLOW:
		p_opticalFlowEngineer->run(frame);
		break;
	
	//...

	default:
		imshow(WINDOW_NAME, frame);
		break;
	}
}
