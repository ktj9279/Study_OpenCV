#pragma once
#include "opencv_set_3.2.0.h"
#include "inverse.h"

using namespace std;
using namespace cv;

struct CallBackParam {
	Mat img;
	Point pt1 = Point(0, 0);    // ROI 좌측상단
	Point pt2 = Point(0, 0);    // ROI 우측하단
	Rect ROI = Rect(0, 0, 0, 0);
	bool drag = false;    // CV_EVENT_LBUTTONDOWN 발생 여부 확인
	bool updated = false;    // 가로, 세로 각각 10px 초과의 크기로 ROI가 설정되었는지 확인
	bool check = false;    // CV_EVENT_RBUTTONDOWN 발생 여부 확인
};

void callBack_main();
void onMouseTest(int event, int x, int y, int flags, void* param);
void onMouseRect(int event, int x, int y, int flags, void* param);