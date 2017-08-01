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
	
	// Set mouse call back function on an window
	setMouseCallback(vidWindow, onMouseTest, NULL);

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
			if (!vid.grab()) {
				if (cnt == 1) {
					cerr << "[Error] Grab failed" << endl << endl;
					cnt++;
				}
			}
			if (!vid.retrieve(frame)) {
				if (cnt == 1) {
					cerr << "[Error] Retrieve failed" << endl << endl;
					cnt++;
				}
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

		imshow(vidWindow, frame);
		if (cnt == 1) {
			cout << "< Press ESC key to disconnect the camera >" << endl << endl;
			cnt++;
		}
		// 한 프레임이 넘어가는 속도를 계산하여 waitKey()의 인수로 넘긴다.
		if (waitKey(1000.f / FPS) == 27) {
			// Release mouse call back function
			setMouseCallback(vidWindow, NULL, NULL);
			destroyAllWindows();

			vid.read(param.img); param.drag = false; param.updated = false; param.check = false;
			namedWindow(imgWindow, WINDOW_AUTOSIZE);
			imshow(imgWindow, param.img);
			
			while (true) {
				setMouseCallback(imgWindow, onMouseRect, &param);

				cout << "< Drag the mouse on the image window. >" << endl << endl;
				cout << "< Press any key on the image window to return the main menu. >" << endl << endl;
				if (waitKey(0)) {
					setMouseCallback(imgWindow, NULL, NULL);
					destroyAllWindows();

					break;
				}
			}

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

	if (event == EVENT_LBUTTONDOWN) {
		p->pt1.x = x;
		p->pt1.y = y;
		p->pt2 = p->pt1;
		p->drag = true;
	}

	if (event == EVENT_LBUTTONUP) {
		int w = x - p->pt1.x;
		int h = y - p->pt1.y;
		p->ROI.x = p->pt1.x;
		p->ROI.y = p->pt1.y;
		p->ROI.width = abs(w);
		p->ROI.height = abs(h);
		p->drag = false;

		if (w >= 10 && h >= 10)
		{
			p->updated = true;
			p->check = true;
		}
	}

	if (p->drag && event == CV_EVENT_MOUSEMOVE) {
		if (p->pt2.x != x || p->pt2.y != y) {
			Mat imgRect = p->img.clone();
			p->pt2.x = x;
			p->pt2.y = y;
			rectangle(imgRect, p->pt1, p->pt2, Scalar(0, 0, 255), 1);
			imshow("Image Viwer", imgRect);
		}
	}
}