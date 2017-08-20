#pragma once
#include "opencv_set_3.2.0.h"
#include "inverse.h"

using namespace std;
using namespace cv;

struct CallBackParam {
	Mat img;
	Point pt1 = Point(0, 0), pt2 = Point(0, 0);
	Rect ROI = Rect(0,0,0,0);
	bool drag = false;
	bool updated = false;
	bool check = false;
};

void callBack_main();
void onMouseTest(int event, int x, int y, int flags, void* param);
void onMouseRect(int event, int x, int y, int flags, void* param);