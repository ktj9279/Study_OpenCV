#pragma once
#include "opencv_set_3.2.0.h"
#include "inverse.h"

using namespace std;
using namespace cv;

struct CallBackParam {
	Mat img;
	Point pt1 = Point(0, 0);    // ROI �������
	Point pt2 = Point(0, 0);    // ROI �����ϴ�
	Rect ROI = Rect(0, 0, 0, 0);
	bool drag = false;    // CV_EVENT_LBUTTONDOWN �߻� ���� Ȯ��
	bool updated = false;    // ����, ���� ���� 10px �ʰ��� ũ��� ROI�� �����Ǿ����� Ȯ��
	bool check = false;    // CV_EVENT_RBUTTONDOWN �߻� ���� Ȯ��
};

void callBack_main();
void onMouseTest(int event, int x, int y, int flags, void* param);
void onMouseRect(int event, int x, int y, int flags, void* param);