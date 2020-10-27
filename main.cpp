#include <stdio.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;



int main() {


	String path = "palm.jpeg";
	Mat img = imread(path, IMREAD_COLOR);


	Mat img2, imgHSV, blurred, thres;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy; //linia 2punkty pierwszy x y start, drugi x y koniec

	cvtColor(img, img2, COLOR_BGR2HSV);
	imshow("win", img2);

	inRange(img2, Scalar(0, 48, 80), Scalar(20, 255, 255), imgHSV);

	imshow("after inRange", imgHSV);
	blur(imgHSV, blurred, Size(2, 2));
	threshold(blurred, thres, 0, 255, THRESH_BINARY);

	imshow("after threshold", thres);
	findContours(thres, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);


	vector<vector<Point>> hull(contours.size());
	vector<vector<int> > hulls2(contours.size());
	vector<vector<Vec4i>> convdefect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		convexHull((contours[i]), hull[i], false);
		convexHull((contours[i]), hulls2[i], false);
		if (hulls2[i].size() > 3)
			convexityDefects(contours[i], hulls2[i], convdefect[i]);
	}




	Mat drawing = Mat::zeros(thres.size(), CV_8UC3); //obraz BGR 8bit macierz

	for (size_t i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(0, 255, 0);
		drawContours(drawing, contours, (int)i, color);
		drawContours(drawing, hull, (int)i, color);
	}


	imshow("window drawing", drawing);

	waitKey(0);

}
