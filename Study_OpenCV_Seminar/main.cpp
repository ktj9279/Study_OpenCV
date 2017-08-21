#include <iostream>
#include "opencv_set_3.2.0.h"
#include "inverse.h"
#include "callBack.h"
#include "templateMatching.h"
#include "CannyEdgeDetector.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	int exitCode = 0;

	cout << "< OpenCV Version : " << CV_VERSION << " >" << endl << endl;
	cout << "< Please connect a webcam to your computer!" << endl << endl;
	
	int index = -1;
	while(true){
		cout << "< The List of the Examples >" << endl
			<< "[0] Mat and inverse image" << endl
			<< "[1] VideoCapture and call back function" << endl
			<< "[2] Template matching" << endl
			<< "[3] Canny edge detector" << endl
			<< "[5221] Quit the program" << endl
			<< endl;
		cout << "Enter the number of example you want to run. : ";
		cin >> index;
		cout << endl;

		switch (index) {
		case 0:		// Mat and Inverse Image
			// TODO: exitCode
			inverse_main();
			break;
		case 1:		// VideoCapture and Call Back Function
			// TODO: exitCode
			callBack_main();
			break;
		case 2:    // Template matching
			// TODO: exitCode
			templateMatching_main();
			break;
		case 3:    // Canny edge detector
			exitCode = CannyEdgeDetector_main();
			break;
		case 5221:	// Quit the Program
			return exitCode;
		default:	// Error
			cout << "[Error] Incorrect number" << endl << endl;
			break;
		}
	}
		
	return exitCode;
}