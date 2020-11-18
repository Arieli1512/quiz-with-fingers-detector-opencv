#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "binaries/processing.h"
#include "binaries/questions.h"

using namespace cv;
using namespace std;


int main() {

		Mat img;
		VideoCapture cam(0);
		bool printQuestion = true;
		int timerQuestion = 0, numOfQuestion = 0, totalQuestions = 3 - 1, timeToAnswer = 100;

		FingersDetector fing;
		QuestionList questionList;
	
		int x = questionList.readQuesionsFromFile("C:\\Users\\micha\\OneDrive\\Pulpit\\pytania.txt");
		if (x == -1) {
			cout << "Nie mozna otworzyc pliku" << endl;
			return -2;
		}

		while (1) {

			try {
				cam.read(img);
				Mat thres = fing.processingImage(img);
				if (thres.empty()) {
					cout << "File not found" << endl;
					return -1;
				}
				vector<vector<Point>> contours = fing.findContoursImage(thres);
				vector<vector<Point>> hull(contours.size());
				vector<vector<int> > hulls2(contours.size());
				vector<vector<Vec4i>> convDefect = fing.createConvexity(hull, contours);
				Mat drawing = fing.drawContoursImage(thres, contours, hull);
				int numOfFingers = fing.countFingers(contours, drawing, convDefect);

				if (printQuestion == true && numOfQuestion <= totalQuestions) {
					questionList.printQuestion(numOfQuestion);
					printQuestion = false;
				}
				timerQuestion++;

				if (timerQuestion == timeToAnswer && numOfQuestion <= totalQuestions) {
					if (numOfFingers == questionList.getAnswerNumber(numOfQuestion)) {
						cout << endl<<"Dobra odpowiedz!" << endl<<endl;

					}
					else cout << endl<<"Zla odpowiedz, poprawna odpowiedz to : " <<questionList.getAnswer(numOfQuestion) << endl<<endl;
					printQuestion = true;
					timerQuestion = 0;
					numOfQuestion++;
				}

				putText(drawing, to_string(numOfFingers), Point(50, 50), FONT_HERSHEY_SIMPLEX, 2, 255);
				cv::imshow("window", drawing);
				if (waitKey(30) == 27)return -1;

			}
			catch (cv::Exception& e)
			{
			}

		}
		
		return 0;	
}
