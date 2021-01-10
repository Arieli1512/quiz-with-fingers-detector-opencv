#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;


class FingersDetector {
private:
	Mat img;
	Mat thresImage;
	bool isFinger(Point startPoint, Point endPoint, Point farPoint, bool flag);
public:
	Mat processingImage(Mat img);
	vector<vector<Point>> findContoursImage(Mat thresImage);
	vector<vector<Vec4i>> createConvexity(vector<vector<Point>>& hull, vector<vector<Point>>& contours);
	Mat drawContoursImage(Mat& thresImage, vector<vector<Point>>& contours, vector<vector<Point>>& hull);

	int countFingers(vector<vector<Point>>& contours, Mat drawing, vector<vector<Vec4i>>& convdefect);

};