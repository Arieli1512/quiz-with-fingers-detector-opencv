#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;


class FingersDetector {
public:
	int detectFingers();
	void setFlagSwitchCamera(int flagSwitchCamera);
	void setCoordinatesWindow(int x, int y);
	void closeCamera();
private:
	int flagSwitchCamera = 0;
	int coordX = 10, coordY = 10;
	VideoCapture camera;
	Mat contoursImage;
	bool isFinger(Point startPoint, Point endPoint, Point farPoint, bool flag);
	Mat findSkinInRegion(Mat img);
	vector<vector<Point>> findContoursImage(Mat thresImage);
	vector<vector<Vec4i>> createConvexity(vector<vector<Point>>& hull, vector<vector<Point>>& contours);
	Mat drawContoursImage(Mat& thresImage, vector<vector<Point>>& contours, vector<vector<Point>>& hull);
	int countFingers(vector<vector<Point>>& contours, Mat drawing, vector<vector<Vec4i>>& convdefect);
	int countFingers(Mat img);
	void validateCoordinates();
};