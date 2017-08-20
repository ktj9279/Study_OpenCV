#pragma once
#include "opencv_set_3.2.0.h"
#include "callBack.h"
#include <iostream>

using namespace std;
using namespace cv;

void templateMatching_main();
void matchingMethod(int, void*);
void onMouseRectTempl(int event, int x, int y, int flags, void* param);