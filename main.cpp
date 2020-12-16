#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Question.h"
#include "QuestionList.h"
#include "FingersDetector.h"
#include "Quiz.h"

using namespace std;
using namespace sf;
using namespace cv;

int main() {


	RectangleShape questionBox(Vector2f(1200, 410.0f));
	vector<RectangleShape> answersBox(5, RectangleShape(Vector2f(240, 240)));
	Quiz quiz(questionBox,answersBox);
	quiz.showStartingScreen();
	quiz.showCategoryScreen();
	quiz.setUp();

	int startFlag = 0;
	
	while (true) {
		try {
			quiz.handleEvent();
			int x = quiz.detectFingers();
			if (startFlag == 0) {
				quiz.clockReset();
				quiz.showWaitingScreen();
				startFlag = 1;
			}
			else if (startFlag == 1) {
				int check = quiz.handleAnswers();
				if (check == 1)
					break;
			}
		}
		catch (cv::Exception& e) {
		}
	}


	quiz.showEndingScreen();
	return 0;
}
