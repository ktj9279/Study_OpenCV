#include "templateMatching.h"

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold;    // Lower threshold: trackbar�� �����Ͽ� ���� ������ �� �ְ� �Ѵ�. 
const int max_lowThreshold = 100;    // Trackbar�� ������ �� �ִ� lower threshold�� �ִ�
int ratio = 3;    // Canny recommended a upper:lower ratio between 2:1 and 3:1.
int kernel_size = 3;    // The size of Sobel kernel: size�� Ŭ���� ������ �β������� �����ϰ� ��Ÿ������ ��ϰ��� ��ȭ�� �����ϰų� ���� ��ü�� �����Ҽ��� edge ���� ȿ���� ��������.
const char* edgeWindow = "Edge Map";
const char* checkWindow1 = "src_gray";
const char* checkWindow2 = "blured src_gray";

static void CannyThreshold(int, void*) {
	////////////////////////////
	/** Step.1 Blur the image */
	////////////////////////////
	// blur(src, dst, ksize, anchor, borderType) is equivalent to boxFilter(src, dst, src.type(), anchor, true, borderType).
	// @param Size(3, 3) blurring kernel size
	blur(src_gray, detected_edges, Size(3, 3));


	/////////////////////////////////
	/** Step.2~4 Apply cv::Canny() */
	/////////////////////////////////
	// @param lowThreshold Trackbar�� ���� �����Ǵ� lower threshold
	// @param lowThreshold * ratio Lower threshold�� �̸� ���س��� ratio�� ���Ͽ� upper threshold ����
	// @param kernel_size The size of the Sobel kernel
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
	

	///////////////////////
	/** Copy color edges */
	///////////////////////
	dst = Scalar::all(0);    // src�� �Ȱ��� ������� dst�� 0���� ä���� � ������ �����.
	src.copyTo(dst, detected_edges);    // �ռ� ���� � ������ dst ���� src�� �����Ѵ�.
									    // ��, mask(2nd param)�� �ȼ����� 0�� �ƴ� ��ġ�� �ȼ��� �����Ѵ�.
										// Canny()�� ����Ͽ� detected_edges�� ����� edges�� ��ġ���� src(���� �̹���)�� ����Ǹ鼭 ���������� color edges�� ����ȴ�.
	imshow(edgeWindow, dst);
}

int CannyEdgeDetector_main() {
	src = imread("lena.jpg", IMREAD_COLOR);
	if (src.empty()) {
		return -1;
	}
	dst.create(src.size(), src.type());    // Mat.size()�� Mat.type()�� ����Ͽ� src�� ���� size�� type�� ������ dst(Mat ��ü)�� ����
	cvtColor(src, src_gray, COLOR_BGR2GRAY);    // code(3rd param)�� ���� color space ��ȯ

	// blur() ȿ�� Ȯ��
	blur(src_gray, detected_edges, Size(10, 10));
	imshow(checkWindow1, src_gray);
	imshow(checkWindow2, detected_edges);

	namedWindow(edgeWindow, WINDOW_AUTOSIZE);
	createTrackbar("Min Threshold:", edgeWindow, &lowThreshold, max_lowThreshold, CannyThreshold);    // Trackbar�� �����̴� ��ġ�� ���� ������ TrackbarCallback onChange(5th param)�� ȣ��ȴ�.
	CannyThreshold(0, 0);

	cout << "< Press ESC key on the \"Edge Map\" window to return the main menu. >" << endl << endl;
	if (waitKey(0) == 27) {
		destroyAllWindows();
	}

	return 0;
}