#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "QuestionList.h"
#include "FingersDetector.h"
#include "Screen.h"

using namespace std;
using namespace cv;
using namespace sf;


class GameScreen :public Screen {
public:
	GameScreen(RenderWindow& window, FingersDetector* fingersDetector) :Screen(window) {
		this->fingersDetector = fingersDetector;
	}
	void setCategory(int category);
	int showGameScreen();
	int getScore();
private:
	FingersDetector* fingersDetector;
	Text feedbackText, textAnswers, textQuestions, currentQuestion, currentScore, timerText;
	Font font;
	int score = 0, totalQuestions = 10, timer = 10, category = 0;
	int readCategoryFile(QuestionList& questionList);
	void configureGameScreen(vector<RectangleShape>& answerBoxes, vector<Text>& answersText);
	void drawOnWindow(RectangleShape& screen, vector<RectangleShape>& answerBoxes,
		vector<Text>& answersText, QuestionList& questionList, int qs);
	int checkAnswer(int numOfFingers, int correctAnswer, int& qs, Text& feedbackText, Text& currentQuestion);
};