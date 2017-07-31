#include <iostream>
#include "opencv_set_3.2.0.h"
#include "inverse.h"

// include한 header에서 사용한 것과 namespace가 중첩되어도 상관 없는가? 문제 없다면, #once 덕분인가?
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	cout << "< OpenCV Version : " << CV_VERSION << " >" << endl << endl;
	
	int index;
	while(1){
		cout << "< The List of Examples >" << endl
			<< "[0] Mat and inverse image" << endl
			<< "[5221] Quit the program" << endl
			<< endl;
		cout << "Enter the number of example you want to run : ";
		cin >> index;
		cout << endl;

		switch (index) {
		case 0:		// Mat and Inverse Image
			inverse_main();
			break;
		case 5221:	// Quit the Program
			return 0;
		default:	// Error
			cout << "[Error] Incorrect number" << endl << endl;
			break;
		}
	}
		
	return 0;
}