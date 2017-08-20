#include "inverse.h"

void inverse_main() {
	///////////////////////////////////////////
	/** Create Mat objects and read an image */
	///////////////////////////////////////////
	Mat src;
	src = imread("lena.jpg", IMREAD_GRAYSCALE);
	if (src.empty()) {
		cerr << "[Error] Image Load failed." << endl << endl;
	}
	cout << "< Information of the Source Image >" << endl
		<< "Width : " << src.cols << endl
		<< "Height : " << src.rows << endl
		<< "Channels : " << src.channels() << endl << endl;

	Mat dst_ptr = src.clone();
	Mat dst_iterator = src.clone();
	Mat dst_at = src.clone();
	
	namedWindow("Original Image", WINDOW_AUTOSIZE);
	namedWindow("Inversed Image", WINDOW_AUTOSIZE);


	/////////////////////////////
	/** Calculate elapsed time */
	/////////////////////////////
	const int TIMES = 100;
	cout << "< Elapsed Time >" << endl;
	double t = (double)getTickCount();
	for (int i = 0; i < TIMES; i++) {
		inverse_ptr(dst_ptr);
	}
	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= TIMES;
	cout << "1. 행 단위 포인터 접근 방법 (ptr) : " << t << " ms." << endl;
	
	t = (double)getTickCount();
	for (int i = 0; i < TIMES; i++) {
		inverse_iterator(dst_iterator);
	}
	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= TIMES;
	cout << "2. 반복자 사용 방법 (iterator) : " << t << " ms." << endl;
	
	t = (double)getTickCount();
	for (int i = 0; i < TIMES; i++) {
		inverse_at(dst_at);
	}
	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= TIMES;
	cout << "3. 임의 접근 연산자 사용 방법 (at) : " << t << " ms." << endl << endl;


	Mat dst = src.clone();
	inverse_ptr(dst);

	imshow("Original Image", src);
	imshow("Inversed Image", dst);
	cout << "< Press any key on the image window to return the main menu. >" << endl << endl;
	waitKey(0);

	destroyAllWindows();
}

void inverse_ptr(Mat & img) {
	if (img.channels() == 1) {    // Grayscale
		for (int row = 0; row < img.rows; row++) {
			uchar* p = img.ptr<uchar>(row);    // 각 행의 데이터 시작 주소를 획득
			for (int col = 0; col < img.cols; col++) {
				p[col] = 255 - p[col];    // row번째 행에서 col번째 열의 픽셀 값을 반전
			}
		}
	}
	else if (img.channels() == 3) {    // BGR
		for (int row = 0; row < img.rows; row++) {
			Vec3b* p = img.ptr<Vec3b>(row);    // Vec3b : unsigned char 3개짜리 자료형
			for (int col = 0; col < img.cols; col++) {
				p[col][0] = 255 - p[col][0];
				p[col][1] = 255 - p[col][1];
				p[col][2] = 255 - p[col][2];
			}
		}
	}
	else {
		cerr << "[Error] Undefined type of Mat to inverse." << endl << endl;;
	}
}

void inverse_ptr(Mat & img, Rect ROI) {
	if (img.channels() == 1) {    // Grayscale
		for (int row = ROI.y; row < ROI.y + ROI.height; row++) {
			uchar* p = img.ptr<uchar>(row);    // 각 행의 데이터 시작 주소를 획득
			for (int col = ROI.x; col < ROI.x + ROI.width; col++) {
				p[col] = 255 - p[col];    // row번째 행에서 col번째 열의 픽셀 값을 반전
			}
		}
	}
	else if (img.channels() == 3) {    // BGR
		for (int row = ROI.y; row < ROI.y + ROI.height; row++) {
			Vec3b* p = img.ptr<Vec3b>(row);    // Vec3b : unsigned char 3개짜리 자료형
			for (int col = ROI.x; col < ROI.x + ROI.width; col++) {
				p[col][0] = 255 - p[col][0];
				p[col][1] = 255 - p[col][1];
				p[col][2] = 255 - p[col][2];
			}
		}
	}
	else {
		cerr << "[Error] Undefined type of Mat to inverse." << endl << endl;;
	}
}

void inverse_iterator(Mat & img) {
	if (img.channels() == 1) {    // Grayscale
		MatIterator_<uchar> it, end;
		for (it = img.begin<uchar>(), end = img.end<uchar>(); it != end; it++) {
			*it = 255 - *it;
		}
	}
	else if (img.channels() == 3) {    // BGR
		MatIterator_<Vec3b> it, end;
		for (it = img.begin<Vec3b>(), end = img.end<Vec3b>(); it != end; it++) {
			(*it)[0] = 255 - (*it)[0];
			(*it)[1] = 255 - (*it)[1];
			(*it)[2] = 255 - (*it)[2];
		}
	}
	else {
		cerr << "[Error] Undefined type of Mat to inverse." << endl << endl;;
	}
}

void inverse_at(Mat & img) {
	if (img.channels() == 1) {    // Grayscale
		for (int row = 0; row < img.rows; row++) {
			for (int col = 0; col < img.cols; col++) {
				img.at<uchar>(row, col) = 255 - img.at<uchar>(row, col);
			}
		}
	}
	else if (img.channels() == 3) {    // BGR
		for (int row = 0; row < img.rows; row++) {
			for (int col = 0; col < img.cols; col++) {
				img.at<Vec3b>(row, col)[0] = 255 - img.at<Vec3b>(row, col)[0];
				img.at<Vec3b>(row, col)[1] = 255 - img.at<Vec3b>(row, col)[1];
				img.at<Vec3b>(row, col)[2] = 255 - img.at<Vec3b>(row, col)[2];
			}
		}
	}
	else {
		cerr << "[Error] Undefined type of Mat to inverse." << endl << endl;;
	}
}