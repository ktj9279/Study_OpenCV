#include <iostream>
#include "opencv_set_3.2.0.h"
#include "inverse.h"
#include "callBack.h"
#include "templateMatching.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
	cout << "< OpenCV Version : " << CV_VERSION << " >" << endl << endl;
	cout << "< Please connect a webcam to your computer!" << endl << endl;
	
	int index = -1;
	while(true){
		cout << "< The List of the Examples >" << endl
			<< "[0] Mat and inverse image" << endl
			<< "[1] VideoCapture and call back function" << endl
			<< "[2] Template matching" << endl
			<< "[5221] Quit the program" << endl
			<< endl;
		cout << "Enter the number of example you want to run. : ";
		cin >> index;
		cout << endl;

		switch (index) {
		case 0:		// Mat and Inverse Image
			inverse_main();
			break;
		case 1:		// VideoCapture and Call Back Function
			callBack_main();
			break;
		case 2:
			templateMatching_main();
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