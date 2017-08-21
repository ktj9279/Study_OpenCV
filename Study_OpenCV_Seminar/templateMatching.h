// http://docs.opencv.org/3.2.0/de/da9/tutorial_template_matching.html

#pragma once
#include "opencv_set_3.2.0.h"
#include "callBack.h"

using namespace std;
using namespace cv;

void templateMatching_main();
void matchingMethod(int, void*);
void onMouseRectTempl(int event, int x, int y, int flags, void* param);