#include "templateMatching.h"

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold;    // Lower threshold: trackbar에 설정하여 값을 조절할 수 있게 한다. 
const int max_lowThreshold = 100;    // Trackbar로 조절할 수 있는 lower threshold의 최댓값
int ratio = 3;    // Canny recommended a upper:lower ratio between 2:1 and 3:1.
int kernel_size = 3;    // The size of Sobel kernel: size가 클수록 에지가 두꺼워져서 선명하게 나타나지만 명암값의 변화가 촘촘하거나 영상 자체가 복잡할수록 edge 검출 효과가 떨어진다.
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
	// @param lowThreshold Trackbar에 의해 조절되는 lower threshold
	// @param lowThreshold * ratio Lower threshold에 미리 정해놓은 ratio를 곱하여 upper threshold 결정
	// @param kernel_size The size of the Sobel kernel
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * ratio, kernel_size);
	

	///////////////////////
	/** Copy color edges */
	///////////////////////
	dst = Scalar::all(0);    // src와 똑같이 맞춰놓은 dst를 0으로 채워서 까만 바탕을 만든다.
	src.copyTo(dst, detected_edges);    // 앞서 만든 까만 바탕의 dst 위에 src을 복사한다.
									    // 단, mask(2nd param)의 픽셀값이 0이 아닌 위치의 픽셀만 복사한다.
										// Canny()를 사용하여 detected_edges에 검출된 edges의 위치에만 src(원본 이미지)가 복사되면서 최종적으로 color edges가 검출된다.
	imshow(edgeWindow, dst);
}

int CannyEdgeDetector_main() {
	src = imread("lena.jpg", IMREAD_COLOR);
	if (src.empty()) {
		return -1;
	}
	dst.create(src.size(), src.type());    // Mat.size()와 Mat.type()을 사용하여 src와 같은 size와 type을 갖도록 dst(Mat 객체)를 생성
	cvtColor(src, src_gray, COLOR_BGR2GRAY);    // code(3rd param)에 따라 color space 변환

	// blur() 효과 확인
	blur(src_gray, detected_edges, Size(10, 10));
	imshow(checkWindow1, src_gray);
	imshow(checkWindow2, detected_edges);

	namedWindow(edgeWindow, WINDOW_AUTOSIZE);
	createTrackbar("Min Threshold:", edgeWindow, &lowThreshold, max_lowThreshold, CannyThreshold);    // Trackbar의 슬라이더 위치가 변할 때마다 TrackbarCallback onChange(5th param)가 호출된다.
	CannyThreshold(0, 0);

	cout << "< Press ESC key on the \"Edge Map\" window to return the main menu. >" << endl << endl;
	if (waitKey(0) == 27) {
		destroyAllWindows();
	}

	return 0;
}