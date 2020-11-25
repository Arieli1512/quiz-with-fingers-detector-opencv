#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "processing.h"
#include "questions.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>


using namespace std;
using namespace sf;

class Quiz {
private:
	RectangleShape questionBox;
	vector<RectangleShape> answersBox;
	QuestionList questionList;
	FingersDetector fingersDetector;

	Texture button, questionTexture;
	Text textAnswers, textQuestions;

	vector<Text> answersText;
	Font font;
	Event event;
	Text currentQuestion;
	VideoCapture camera;
	Mat drawing;
	Time elapsed;
	Clock clock;
	int qs = 0;
	int timer = 10;
	int totalQuestions = 12;
	int flag = 0;
	int score = 0;


public:
	RenderWindow window;
	Quiz(RectangleShape questionBox, vector<RectangleShape> answersBox, QuestionList questionList, FingersDetector fingersDetector)
		:window(VideoMode(1800, 650), "Quiz", Style::Close | Style::Resize)
	{
		this->questionBox = questionBox;
		this->answersBox = answersBox;
		this->questionList = questionList;
	}
	int numOfFingers = 0;

	void clockReset()
	{
		clock.restart();
	}

	void configCamera() {
		VideoCapture cam1(0);
		this->camera = cam1;
	}

	void startingScreen() {
		font.loadFromFile("../fonts/AllerDisplay.ttf");
		questionTexture.loadFromFile("../imagesSfml/baner4.jpg");
		RectangleShape helloScreen(Vector2f(1800, 650.0f));
		helloScreen.setTexture(&questionTexture);
		helloScreen.setOrigin(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
		helloScreen.setPosition(900, 325);

		Text text1;
		text1.setPosition(25, 10);
		text1.setFont(font);
		text1.setCharacterSize(55);
		text1.setString(L"QUIZ");

		Text text2;
		text2.setPosition(25, 300);
		text2.setFont(font);
		text2.setCharacterSize(70);
		text2.setString(L"By rozpocząć grę pokaż do kamery\n pięć palców");

		int flag = 0;

		while (true) {
			try {
				window.clear();
				window.draw(helloScreen);
				window.draw(text1);
				window.draw(text2);
				window.display();
				handleEvent();
				if (flag == 0)
				{
					configCamera();
					flag = 1;
				}
				int x = detectFingers();
				if (x == 5) {
					cout << "Pokazales 5 placow!" << endl;
					break;
				}
			}
			catch (cv::Exception& e) {
			}
		}



	}
	void setUp() {

		int x = questionList.readQuesionsFromFile("../pytania_projekt.txt");
		if (x == -1) {
			return;
		}

		textAnswers.setCharacterSize(36);
		textQuestions.setCharacterSize(45);

		textAnswers.setFont(font);
		textQuestions.setFont(font);

		vector<Text> answersTextx(5, textAnswers);
		this->answersText = answersTextx;

		string str1 = "Pytanie 1 / ";
		str1.append(to_string(totalQuestions));
		currentQuestion.setString(str1);

		font.loadFromFile("../fonts/AllerDisplay.ttf");
		button.loadFromFile("../imagesSfml/baner4.jpg");
		currentQuestion.setFont(font);

		textQuestions.setFillColor(sf::Color::White);
		answersBox[0].setFillColor(sf::Color::Magenta);
		answersBox[1].setFillColor(sf::Color::Red);
		answersBox[2].setFillColor(sf::Color::Blue);
		answersBox[3].setFillColor(sf::Color(0, 153, 51));
		answersBox[4].setFillColor(sf::Color(102, 20, 179));

		questionBox.setTexture(&button);
		questionBox.setFillColor(sf::Color::White);

		questionBox.setOrigin(questionBox.getSize().x / 2.0f, questionBox.getSize().y / 2.0f);
		questionBox.setPosition(900, 200);

		textQuestions.setPosition(900, 200);
		window.setFramerateLimit(60);
		//window.clear(sf::Color(255, 255, 255));
		Text score("Pytanie 1/20", font);


		for (int i = 0; i < answersBox.size(); i++) {
			answersText[i].setFillColor(Color::White);
			answersBox[i].setOrigin(answersBox[i].getSize().x / 2.0f, answersBox[i].getSize().y / 2.0f);
			answersText[i].setOrigin(answersText[i].getLocalBounds().width / 2.0f, answersText[i].getLocalBounds().height / 2.0f);
			answersBox[i].setPosition(180.0f + 360.0f * i, 550.0f);
			answersText[i].setPosition(answersBox[i].getPosition());
			answersText[i].setPosition(180.0f + 360.0f * i, 500.0f);
		}


	}

	void handleEvent() {
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				break;

			}
		}
	}


	int detectFingers() {
		cv::Mat img;
		camera.read(img);
		Mat thres = fingersDetector.processingImage(img);
		if (thres.empty()) {
			return -1;
		}
		vector<vector<cv::Point>> contours = fingersDetector.findContoursImage(thres);
		vector<vector<cv::Point>> hull(contours.size());
		vector<vector<int> > hulls2(contours.size());
		vector<vector<cv::Vec4i>> convDefect = fingersDetector.createConvexity(hull, contours);
		drawing = fingersDetector.drawContoursImage(thres, contours, hull);
		numOfFingers = fingersDetector.countFingers(contours, drawing, convDefect);


		cv::putText(drawing, to_string(numOfFingers), cv::Point(50, 50), FONT_HERSHEY_SIMPLEX, 2, 255);
		cv::imshow("window", drawing);
		return numOfFingers;
	}

	int handleAnswers() {
		//window.clear();
		//window.clear();
		window.draw(questionBox);
		Text textP;
		Text currentScore;
		Text timerW;
		switch (flag) {
		case 1:
			textP.setString(L"Poprawna odpowiedź");
			textP.setFillColor(Color::Green);
			break;
		case 2:
			textP.setString(L"Błędna odpowiedź");
			textP.setFillColor(Color::Red);
			break;
		}
		textP.setPosition(1495, 10);
		timerW.setPosition(1495, 50);
		timerW.setFont(font);
		timerW.setCharacterSize(50);
		timerW.setFillColor(Color::White);
		textP.setFont(font);
		textP.setCharacterSize(30);
		currentScore.setPosition(10, 60);
		currentScore.setCharacterSize(30);
		currentScore.setFont(font);
		elapsed = clock.getElapsedTime();
		int timeRemained = timer - (int)elapsed.asSeconds();
		timerW.setString(to_string(timeRemained));

		if ((int)elapsed.asSeconds() > (timer - 1)) {

			if (numOfFingers == questionList.getQuestionArray().at(qs).getCorrectAnswer()) {
				score++;
				flag = 1;
				cout << "Poprawna odp" << numOfFingers << "  corr answ :" << questionList.getQuestionArray().at(qs).getCorrectAnswer() << endl;
			}
			else {
				flag = 2;
				cout << "Zla odp" << numOfFingers << "  corr answ :" << questionList.getQuestionArray().at(qs).getCorrectAnswer() << endl;
			}

			qs++;
			string mystr = "Pytanie ";
			mystr.append(to_string(qs + 1));
			mystr.append(" / ");
			mystr.append(to_string(totalQuestions));
			currentQuestion.setString(mystr);
			clock.restart();
		}

		currentScore.setString("Punkty " + to_string(score));
		window.draw(textP);
		window.draw(currentScore);
		window.draw(timerW);
		for (int i = 0; i < answersBox.size(); i++) {


			if (qs == totalQuestions)
				return 1;
			wstring questionString = questionList.getQuestionArray().at(qs).getQuestion();
			wstring answersString = questionList.getQuestionArray().at(qs).getAnswers().at(i);

			textQuestions.setString(sf::String::fromUtf8(questionString.begin(), questionString.end()));
			answersText[i].setString(sf::String::fromUtf8(answersString.begin(), answersString.end()));

			textQuestions.setOrigin(textQuestions.getLocalBounds().width / 2.0f, textQuestions.getLocalBounds().height / 2.0f);
			answersText[i].setOrigin(answersText[i].getLocalBounds().width / 2.0f, answersText[i].getLocalBounds().height / 2.0f);
			window.draw(answersBox[i]);
			window.draw(answersText[i]);
			window.draw(textQuestions);

		}


		currentQuestion.setPosition(10, 10);
		window.draw(currentQuestion);
		window.display();


		return 0;

	}

};




int main() {


	RectangleShape questionBox(Vector2f(1800.0f, 400.0f));
	vector<RectangleShape> answersBox(5, RectangleShape(Vector2f(360, 300)));
	QuestionList questionList;
	FingersDetector fingersDetector;

	Quiz mainController(questionBox, answersBox, questionList, fingersDetector);


	mainController.startingScreen();
	mainController.setUp();

	int startFlag = 0;

	while (true) {

		try {
			mainController.handleEvent();
			int x = mainController.detectFingers();
			if (x == 5 && startFlag == 0) {
				mainController.clockReset();
				mainController.handleAnswers();
				startFlag = 1;
			}
			else if (startFlag == 1) {
				int check = mainController.handleAnswers();
				if (check == 1)return 0;
			}


		}
		catch (cv::Exception& e) {
		}
	}
	return 0;
}
