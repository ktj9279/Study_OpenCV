#include "templateMatching.h"

// bool useMask;
Mat img; Mat templ; Mat mask; Mat result;
const char* imgWindow = "Source Image";
const char* resultWindow = "Result";
int matchMethod;
int maxTrackbar = 5;

void templateMatching_main()
{
	Rect rTempl(0, 0, 0, 0);
	
	img = imread("lena.jpg", IMREAD_COLOR);
	imshow(imgWindow, img);

	CallBackParam param;
	param.img = img; param.check = false; param.drag = false; param.updated = false;
	cout << "< Drag the mouse on the \"Source Image\" window to select a template and then press any key. >" << endl << endl;
	while (true) {
		setMouseCallback(imgWindow, onMouseRectTempl, &param);
		if (waitKey(0)) {
			rTempl.x = param.pt1.x < param.pt2.x ? param.pt1.x : param.pt2.x;
			rTempl.y = param.pt1.y < param.pt2.y ? param.pt1.y : param.pt2.y;
			rTempl.width = abs(param.pt1.x - param.pt2.x);
			rTempl.height = abs(param.pt1.y - param.pt2.y);
			templ = Mat(img, rTempl);
			setMouseCallback(imgWindow, NULL, NULL);
			break;
		}
	}

	/*
	useMask = true;
	mask = imread(argv[3], IMREAD_COLOR);
	if (img.empty() || templ.empty() || (useMask && mask.empty()))
	{
		cout << "Can't read one of the images" << endl;
	}
	*/

	if (img.empty() || templ.empty()) {
		cerr << "[Error] Can't read one of the images" << endl;
	}

	namedWindow(imgWindow, WINDOW_AUTOSIZE);
	namedWindow(resultWindow, WINDOW_AUTOSIZE);

	const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
	createTrackbar(trackbar_label, imgWindow, &matchMethod, maxTrackbar, matchingMethod);

	matchingMethod(0, 0);

	cout << "< Press ESC key on the \"Source Image\" window to return the main menu. >" << endl << endl;
	if (waitKey(0) == 27) {
		destroyAllWindows();
	}
}

void matchingMethod(int, void*){
	Mat imgDisplay;
	imgDisplay = img.clone();
	int resultCols = img.cols - templ.cols + 1;
	int resultRows = img.rows - templ.rows + 1;
	result.create(resultRows, resultCols, CV_32FC1);
		
	/*
	bool method_accepts_mask = (CV_TM_SQDIFF == match_method || match_method == CV_TM_CCORR_NORMED);
	if (use_mask && method_accepts_mask) {
		matchTemplate(img, templ, result, match_method, mask);
	}
	else {
		matchTemplate(img, templ, result, match_method);
	}
	*/
	matchTemplate(img, templ, result, matchMethod);

	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;
	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
	if (matchMethod == TM_SQDIFF || matchMethod == TM_SQDIFF_NORMED) {
		matchLoc = minLoc;
	}
	else {
		matchLoc = maxLoc;
	}

	rectangle(imgDisplay, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 0, 255), 1);
	rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 0, 255), 1);
	imshow(imgWindow, imgDisplay);
	imshow(resultWindow, result);
}

void onMouseRectTempl(int event, int x, int y, int flags, void* param) {
	CallBackParam* p = (CallBackParam*)param;

	if (event == CV_EVENT_LBUTTONDOWN) {
		p->pt1.x = x;
		p->pt1.y = y;
		p->pt2 = p->pt1;
		p->drag = true;
	}

	if (event == CV_EVENT_LBUTTONUP) {
		p->ROI.x = x < p->pt1.x ? x : p->pt1.x;
		p->ROI.y = y < p->pt1.y ? y : p->pt1.y;
		p->ROI.width = abs(x - p->pt1.x);
		p->ROI.height = abs(y - p->pt1.y);
		p->drag = false;

		if (p->ROI.width >= 10 && p->ROI.height >= 10)
		{
			p->updated = true;
		}
	}

	if (p->drag && event == CV_EVENT_MOUSEMOVE) {
		if (p->pt2.x != x || p->pt2.y != y) {
			p->pt2.x = x;
			p->pt2.y = y;
			Mat imgRect = p->img.clone();
			rectangle(imgRect, p->pt1, p->pt2, Scalar(0, 0, 255), 1);
			imshow(imgWindow, imgRect);
		}
	}
}