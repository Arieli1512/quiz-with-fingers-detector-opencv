#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "binaries/processing.h"

using namespace cv;
using namespace std;


int main() {

	String path = "palec5.jpg";
	Mat thres = imageAfterPreprocessing(path);
	if (thres.empty()) {
		cout << "File not found" << endl;
		return - 1;
	}
	vector<vector<Point>> contours  = findContoursImage(thres);

	vector<vector<Point>> hull(contours.size());
	vector<vector<int> > hulls2(contours.size());
	vector<vector<Vec4i>> convDefect = createConvexity(hull, contours);


	Mat drawing = drawContoursImage(thres, contours, hull);
	int counter = countFingers(contours, drawing, convDefect);


	cout << "liczba palcow : " << counter << endl;

	imshow("window drawing", drawing);

	waitKey(0);

	return 0;
}