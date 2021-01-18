#include "FingersDetector.h"


Mat FingersDetector::findSkinInRegion(Mat img) {
	Mat img2, imgHSV, blurred, thres;
	cvtColor(img, img2, COLOR_BGR2HSV);
	inRange(img2, Scalar(0, 48, 80), Scalar(20, 255, 255), imgHSV);
	blur(imgHSV, blurred, Size(2, 2));
	threshold(blurred, thres, 0, 255, THRESH_BINARY);

	return thres;
}


vector<vector<Point>> FingersDetector::findContoursImage(Mat thresImage) {
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(thresImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	return contours;
}


vector<vector<Vec4i>> FingersDetector::createConvexity(vector<vector<Point>>& hull, vector<vector<Point>>& contours) {
	vector<vector<int> > hull2(contours.size());
	vector<vector<Vec4i>> convDefect(contours.size());
	for (int i = 0; i < contours.size(); i++) {
		convexHull(contours[i], hull[i]);
		convexHull(contours[i], hull2[i]);
		convexityDefects(contours[i], hull2[i], convDefect[i]);
	}
	return convDefect;
}

Mat FingersDetector::drawContoursImage(Mat& thresImage, vector<vector<Point>>& contours, vector<vector<Point>>& hull) {
	Mat drawing = Mat::zeros(thresImage.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++) {
		Scalar color = Scalar(0, 255, 0);
		drawContours(drawing, contours, (int)i, color);
		drawContours(drawing, hull, (int)i, color);
	}

	return drawing;
}


bool FingersDetector::isFinger(Point startPoint, Point endPoint, Point farPoint, bool flag) {
	//obliczanie dlugosci odcinka
	float a = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(endPoint.y - startPoint.y, 2));
	float b = sqrt(pow(farPoint.x - startPoint.x, 2) + pow(farPoint.y - startPoint.y, 2));
	float c = sqrt(pow(endPoint.x - farPoint.x, 2) + pow(endPoint.y - farPoint.y, 2));
	float hc = (a + b + c) / 2;
	float area = sqrt(hc * (hc - a) * (hc - b) * (hc - c)); //wzor herona
	float hei = (2 * area) / a; //wysokosc 
	//twierdzenie cosinusow
	float angle = acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c)) * 57; //1rad = 57stp
	if (flag == true)
		if (angle < 90 && hei>30) { //jezeli kat mniejszy niz 90 i wysokkosc wieksza niz 30 -> palec
			return true;
		}
	if (flag == false)
		if (angle >= 90 && hei > 30) {
			return true;
		}
	return false;
}

void FingersDetector::setFlagSwitchCamera(int flagSwitchCamera) {
	this->flagSwitchCamera = flagSwitchCamera;
}

void FingersDetector::setCoordinatesWindow(int x, int y) {
	this->coordX = x;
	this->coordY = y;
}

int FingersDetector::countFingers(vector<vector<Point>>& contours, Mat drawing, vector<vector<Vec4i>>& convdefect) {
	int counterFin = 0, flag = 0;
	bool flagFinger = false;

	for (int i = 0; i < contours.size(); i++) {
		size_t counter = contours[i].size(); //ile punktow ma dany kontur
		if (counter < 200) //miedzy 200-600
			continue;

		for (Vec4i& v : convdefect[i]) {

			int start = v[0], end = v[1], far = v[2];
			Point startPoint(contours[i][start]);
			Point endPoint(contours[i][end]);
			Point farPoint = (contours[i][far]);
			line(drawing, startPoint, endPoint, Scalar(0, 255, 0), 2);
			line(drawing, startPoint, farPoint, Scalar(255, 0, 0), 2);
			line(drawing, endPoint, farPoint, Scalar(0, 0, 255), 2);
			bool val = isFinger(startPoint, endPoint, farPoint, true);
			if (isFinger(startPoint, endPoint, farPoint, false))
				flag = 1;
			if (val)counterFin++;
		}
	}

	if (flag == 1 && counterFin == 0)counterFin = 1; //jeden palec
	else if (counterFin > 0)counterFin++; //wiecej

	return counterFin;
}

int FingersDetector::countFingers(Mat img) {
	Mat thresholdImage = findSkinInRegion(img);
	if (thresholdImage.empty()) {
		return -1;
	}
	vector<vector<cv::Point>> contours = findContoursImage(thresholdImage);
	vector<vector<cv::Point>> hull(contours.size());
	vector<vector<int> > hulls2(contours.size());
	vector<vector<cv::Vec4i>> convDefect = createConvexity(hull, contours);
	contoursImage = drawContoursImage(thresholdImage, contours, hull);
	int numOfFingers = countFingers(contours, contoursImage, convDefect);

	return numOfFingers;
}

void FingersDetector::validateCoordinates() {
	int maxWidth = camera.get(3) / 2;
	int maxHeight = camera.get(4) / 3;
	if (coordX > maxWidth)
		coordX = maxWidth;
	if (coordY > maxHeight)
		coordY = maxHeight;
	if (coordX < 0)
		coordX = 0;
	if (coordY < 0)
		coordY = 0;
}

int FingersDetector::detectFingers() {

	if (flagSwitchCamera == 0) {
		VideoCapture camera1(0);
		this->camera = camera1;
		flagSwitchCamera = 1;
	}
	Mat img, partImg;
	camera.read(img);
	validateCoordinates();
	cv::Rect rect = cv::Rect(cv::Point2f(coordX, coordY), cv::Point2f(300 + coordX, 300 + coordY));
	rectangle(img, cv::Point2f(coordX, coordY), cv::Point2f(300 + coordX, 300 + coordY), cv::Scalar(255, 0, 0));
	partImg = img(rect);
	cv::imshow("window real", img);
	int numOfFingers = countFingers(partImg);
	cv::putText(contoursImage, to_string(numOfFingers), cv::Point(50, 50), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 3);
	cv::imshow("window", contoursImage);
	return numOfFingers;
}