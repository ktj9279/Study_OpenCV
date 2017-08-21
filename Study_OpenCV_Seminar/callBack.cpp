#include "callBack.h"

void callBack_main() {
	//////////////////////////////////////////////////////////////////////////////
	/** Create a VideoCapture object and connect a webcam to it or read a video */
	//////////////////////////////////////////////////////////////////////////////
	VideoCapture vid;
	vid.open(0);    // Open a camera
	if (!vid.isOpened()) {
		cerr << "[Error] Video open failed" << endl << endl;
	}

	Mat frame;
	const int FPS = 30;
	const string vidWindow("Video Viwer");
	const string imgWindow("Image Viwer");
	namedWindow(vidWindow, WINDOW_AUTOSIZE);

	int index = -1;
	int cnt = 1;

	CallBackParam param;
	
	cout << "< The List of the methods >" << endl
		<< "[0] grab() and retrieve()" << endl
		<< "[1] read() = grab() + retrieve()" << endl
		<< "[2] Operator >>" << endl
		<< endl;
	cout << "Enter the number of method you want to run. : ";
	cin >> index;
	cout << endl;


	/////////////////////////////////////////////
	/** Read and show every frame of the video */
	/////////////////////////////////////////////
	while (true) {
		// CallBackParam *p = (CallBackParam*)param;

		switch (index) {
		case 0:		// Method 1: grab() and retrieve()
			if (vid.grab()) {
				if (!vid.retrieve(frame)) {
					cerr << "[Error] Retrieve failed" << endl << endl;
				}
			}
			else { 
				cerr << "[Error] Grab failed" << endl << endl;
				break;
			}

			break;
		case 1:		// Method 2: read() = grab() + retrieve()
			if (!vid.read(frame)) {
				if (cnt == 1) {
					cerr << "[Error] Read failed" << endl << endl;
					cnt++;
				}
			}

			break;
		case 2:		// Method 3: Operator >>
			vid >> frame;

			break;
		default:	// Error
			cout << "[Error] Incorrect number" << endl << endl;

			break;
		}

		// Draw image
		if (param.check == true) {    // Inverse image
			inverse_ptr(frame, param.ROI);
		}
		else if (param.drag == true || param.updated == true) {    // Draw rectangle
			rectangle(frame, param.pt1, param.pt2, Scalar(0, 0, 255), 1);
			// 아래 주석을 해제하면, 마우스 드래그로 지정된 영역이 실시간으로 반전된다.
			// inverse_ptr(frame, Rect(param.pt1, param.pt2));
		}

		param.img = frame;

		// Set mouse call back function on a window
		setMouseCallback(vidWindow, onMouseRect, &param);

		imshow(vidWindow, frame);

		if (cnt == 1) {
			cout << "< Drag the mouse on the video window to select a ROI. >" << endl;
			cout << "< Click the right mouse button to inverse the video. >" << endl;
			cout << "< Press ESC key on the video window to return the main menu. >" << endl << endl;
			cnt++;
		}
		// 한 프레임이 넘어가는 속도를 계산하여 waitKey()의 인수로 넘긴다.
		if (waitKey((int)(1000.f / FPS)) == 27) {
			// Release mouse call back function
			setMouseCallback(vidWindow, NULL, NULL);
			destroyAllWindows();

			break;
		}
	}

	vid.release();
}

void onMouseTest(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
	}
	else if (event == CV_EVENT_RBUTTONDOWN)
	{
		std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
	}
	else if (event == CV_EVENT_MBUTTONDOWN)
	{
		std::cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
	}
	else if (event == CV_EVENT_MOUSEMOVE)
	{
		std::cout << "Mouse move over the window - position (" << x << ", " << y << ")" << std::endl;
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		std::cout << "Left button of the mouse is released - position (" << x << ", " << y << ")" << std::endl;
	}
	else if (event == CV_EVENT_RBUTTONUP)
	{
		std::cout << "Right button of the mouse is released - position (" << x << ", " << y << ")" << std::endl;
	}
	else if (event == CV_EVENT_MBUTTONUP)
	{
		std::cout << "Middle button of the mouse is released - position (" << x << ", " << y << ")" << std::endl;
	}
	else if (event == CV_EVENT_LBUTTONDBLCLK)
	{
		std::cout << "Left button of the mouse is double-clicked - position (" << x << ", " << y << ")" << std::endl;
	}
	else if (event == CV_EVENT_RBUTTONDBLCLK)
	{
		std::cout << "Right button of the mouse is double-clicked - position (" << x << ", " << y << ")" << std::endl;
	}
	else if (event == CV_EVENT_MBUTTONDBLCLK)
	{
		std::cout << "Middle button of the mouse is double-clicked - position (" << x << ", " << y << ")" << std::endl;
	}

	if (flags & CV_EVENT_FLAG_LBUTTON)
	{
		std::cout << "\tCV_EVENT_FLAG_LBUTTON" << std::endl;
	}
	if (flags & CV_EVENT_FLAG_RBUTTON)
	{
		std::cout << "\tCV_EVENT_FLAG_RBUTTON" << std::endl;
	}
	if (flags & CV_EVENT_FLAG_MBUTTON)
	{
		std::cout << "\tCV_EVENT_FLAG_MBUTTON" << std::endl;
	}
	if (flags & CV_EVENT_FLAG_CTRLKEY)
	{
		std::cout << "\tCV_EVENT_FLAG_CTRLKEY" << std::endl;
	}
	if (flags & CV_EVENT_FLAG_SHIFTKEY)
	{
		std::cout << "\tCV_EVENT_FLAG_SHIFTKEY" << std::endl;
	}
	if (flags & CV_EVENT_FLAG_ALTKEY)
	{
		std::cout << "\tCV_EVENT_FLAG_ALTKEY" << std::endl;
	}
}

void onMouseRect(int event, int x, int y, int flags, void* param) {
	CallBackParam* p = (CallBackParam*)param;

	if (p->check == false && event == CV_EVENT_LBUTTONDOWN) {
		p->pt1.x = x;
		p->pt1.y = y;
		p->pt2 = p->pt1;
		p->drag = true;
	}

	if (p->check == false && event == CV_EVENT_LBUTTONUP) {
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
		p->pt2.x = x;
		p->pt2.y = y;
		// Mat imgRect = p->img.clone();
		// rectangle(imgRect, p->pt1, p->pt2, Scalar(0, 0, 255), 1);
		// imshow("Video Viwer", imgRect);
	}

	if (p->updated == true && event == CV_EVENT_RBUTTONDOWN) {
		// Mat imgInversed = p->img.clone();
		// inverse_ptr(imgInversed, p->ROI);
		// imshow("Video Viwer", imgInversed);
		if (p->check == true) {
			p->updated = false;
		}
		p->check = !p->check;
	}
}