#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "processing.h"

using namespace cv;
using namespace std;

const char* questions[4] = { "Stolica Hiszpanii to ?",
	"Kto byl pierwszym krolem Polski",
	"Kto wygral MS w Pilce Noznej w 2018 roku?" };
const char* answers[4][5] = {
	{ "Barcelona", "Londyn", "Madryt","Grenada","Sewilla"},
	{ "Mieszko I", "Boleslaw I Chrobry", "Kazimierz Wielki","Stansilaw Poniatowski","Mieszko II" },
{"Polska","Niemcy","Rosja","Chorwacja","Francja"}
};
int correctAnswer[4] = { 3, 2, 5 };



int main() {


		VideoCapture cam(0);

		//String path = "finger5.jpg";
		Mat img;
		
		int printFirst = 0, timerQ = 0, nextAnswer = 0;

		while (1) {


			try {

				cam.read(img);
				
				Mat thres = imageAfterPreprocessing(img);

				if (thres.empty()) {
					cout << "File not found" << endl;
					return -1;
				}
				vector<vector<Point>> contours = findContoursImage(thres);
				vector<vector<Point>> hull(contours.size());
				vector<vector<int> > hulls2(contours.size());
				vector<vector<Vec4i>> convDefect = createConvexity(hull, contours);


				Mat drawing = drawContoursImage(thres, contours, hull);
				int counter = countFingers(contours, drawing, convDefect);

				if (printFirst == 0 && nextAnswer<3) {
					cout << questions[nextAnswer]<<endl;
					for (int i = 0; i < 5; i++) {
						cout << i+1<<") "<< answers[nextAnswer][i] << endl;
					}
					printFirst = 1;
				}

				timerQ++;
				if (timerQ == 150 && nextAnswer<3) {
					if (counter == correctAnswer[nextAnswer]) {
						cout << endl<<"Dobra odpowiedz!" << endl<<endl;

					}
					else cout << endl<<"Zla odpowiedz!" << endl<<endl;
					printFirst = 0;
					timerQ = 0;
					nextAnswer++;
				}

				
				putText(drawing, to_string(counter), Point(50, 50), FONT_HERSHEY_SIMPLEX, 2, 255);
				cv::imshow("window", drawing);
				if (waitKey(30) == 27)return -1;

			}
			catch (cv::Exception& e)
			{

			}


		}

		return 0;	
}