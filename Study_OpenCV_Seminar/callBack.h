#pragma once
#include "opencv_set_3.2.0.h"

using namespace std;
using namespace cv;

typedef struct CallBackParam {
	Mat img;
	Point pt1, pt2;
	Rect ROI;
	bool drag;
	bool updated;
	bool check;
};

void callBack_main();
void onMouseTest(int event, int x, int y, int flags, void* param);
void onMouseRect(int event, int x, int y, int flags, void* param);