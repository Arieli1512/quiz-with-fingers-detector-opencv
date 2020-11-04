#include "processing.h"


Mat imageAfterPreprocessing(String path) {

	Mat img = imread(path, IMREAD_COLOR);

	if (img.empty()) {
		Mat m;
		return m;
	}
	
	imshow("zdjecie wejsciowe", img);

	Mat img2, imgHSV, blurred, thres;

	cvtColor(img, img2, COLOR_BGR2HSV);
	inRange(img2, Scalar(0, 48, 80), Scalar(20, 255, 255), imgHSV);
	blur(imgHSV, blurred, Size(2, 2)); 
	threshold(blurred, thres, 0, 255, THRESH_BINARY);

	return thres;
}


vector<vector<Point>> findContoursImage(Mat thresImage) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(thresImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

	return contours;
}


vector<vector<Vec4i>> createConvexity(vector<vector<Point>>& hull, vector<vector<Point>>& contours) {

	vector<vector<int> > hull2(contours.size());
	vector<vector<Vec4i>> convDefect(contours.size());

	for (int i = 0; i < contours.size(); i++) {

		convexHull(contours[i], hull[i]);
		convexHull(contours[i], hull2[i]);
		convexityDefects(contours[i], hull2[i], convDefect[i]);
	}

	return convDefect;
}

Mat drawContoursImage(Mat& thresImage, vector<vector<Point>>& contours, vector<vector<Point>>& hull) {
	Mat drawing = Mat::zeros(thresImage.size(), CV_8UC3);

	for (size_t i = 0; i < contours.size(); i++) {

		Scalar color = Scalar(0, 255, 0);
		drawContours(drawing, contours, (int)i, color);
		drawContours(drawing, hull, (int)i, color);
	}

	return drawing;
}


bool isFinger(Point startPoint,Point endPoint, Point farPoint) {

	//obliczanie dlugosci odcinka
	float a = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(endPoint.y - startPoint.y, 2));
	float b = sqrt(pow(farPoint.x - startPoint.x, 2) + pow(farPoint.y - startPoint.y, 2));
	float c = sqrt(pow(endPoint.x - farPoint.x, 2) + pow(endPoint.y - farPoint.y, 2));


	float hc = (a + b + c) / 2;
	float area = sqrt(hc * (hc - a) * (hc - b) * (hc - c)); //wzor herona
	float hei = (2 * area) / a; //wysokosc 

	

	//twierdzenie cosinusow

	float angle = acos((pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c)) * 57; //1rad = 57stp
	if (angle < 90 && hei>30) { //jezeli kat mniejszy niz 90 i wysokkosc wieksza niz 30 -> palec
		return true;
	}


	return false;
}

int countFingers(vector<vector<Point>>& contours, Mat drawing, vector<vector<Vec4i>>& convdefect) {
	int counterFin = 0;

	for (int i = 0; i < contours.size(); i++) {

		size_t counter = contours[i].size(); //ile punktow ma dany kontur

		if (counter < 500) //miedzy 300-600
			continue;

		for (Vec4i& v : convdefect[i]) {

			int start = v[0], end = v[1], far = v[2];

			Point startPoint(contours[i][start]);
			Point endPoint(contours[i][end]);
			Point farPoint = (contours[i][far]);
			
			line(drawing, startPoint, endPoint, Scalar(0, 255, 0), 2);
			line(drawing, startPoint, farPoint, Scalar(255, 0, 0), 2);
			line(drawing, endPoint, farPoint, Scalar(0, 0, 255), 2);

			bool val = isFinger(startPoint, endPoint, farPoint);

			if (val)counterFin++;
		}


	}

	counterFin++;

	return counterFin;
}