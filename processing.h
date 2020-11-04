#ifndef processing_h
#define preocessing_h

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

Mat imageAfterPreprocessing(String path);
vector<vector<Point>> findContoursImage(Mat thresImage);
vector<vector<Vec4i>> createConvexity(vector<vector<Point>>& hull, vector<vector<Point>>& contours);
Mat drawContoursImage(Mat& thresImage, vector<vector<Point>>& contours, vector<vector<Point>>& hull);
bool isFinger(Point startPoint, Point endPoint, Point farPoint);
int countFingers(vector<vector<Point>>& contours, Mat drawing, vector<vector<Vec4i>>& convdefect);


#endif // !processing_h
