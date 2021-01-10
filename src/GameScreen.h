#pragma once
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "QuestionList.h"
#include "FingersDetector.h"

using namespace std;
using namespace cv;
using namespace sf;


class GameScreen {
public:
	GameScreen(RenderWindow& window, VideoCapture camera);
	void setCategory(int category);
	int showGameScreen();
	int getScore();
private:
	VideoCapture camera;
	RenderWindow& window;
	Text feedbackText, textAnswers, textQuestions, currentQuestion, currentScore, timerText;
	Font font;
	int score = 0, totalQuestions = 10, timer = 1, category = 0;
	void handleEvent();
	int readCategoryFile(QuestionList& questionList);
	void configureGameScreen(vector<RectangleShape>& answerBoxes, vector<Text>& answersText);
	void drawOnWindow(RectangleShape& screen, vector<RectangleShape>& answerBoxes,
		vector<Text>& answersText, QuestionList& questionList, int qs);
	int checkAnswer(int numOfFingers, int correctAnswer, int& qs, Text& feedbackText, Text& currentQuestion);
	int detectFingers();
};