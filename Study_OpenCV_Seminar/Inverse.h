#pragma once
#include "opencv2\opencv.hpp"

using namespace std;
using namespace cv;

void inverse_main();
void inverse_ptr(Mat&);
void inverse_iterator(Mat&);
void inverse_at(Mat&);