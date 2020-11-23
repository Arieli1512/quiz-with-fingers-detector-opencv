#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "processing.h"
#include "questions.h"
#include <SFML/Graphics.hpp>

//using namespace cv;
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

	int qs=0;
	int timer=0;
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

	void configCamera() {
		VideoCapture cam1(0);
		this->camera = cam1;
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
			questionTexture.loadFromFile("../imagesSfml/button.png");
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
				answersBox[i].setOrigin(answersBox[i].getSize().x/2.0f, answersBox[i].getSize().y / 2.0f);
				answersText[i].setOrigin(answersText[i].getLocalBounds().width/2.0f, answersText[i].getLocalBounds().height / 2.0f);
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
			window.draw(questionBox);
			Text textP;
			Text currentScore;

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
			textP.setFont(font);
			textP.setCharacterSize(30);
			currentScore.setPosition(10, 60);
			currentScore.setCharacterSize(30);
			currentScore.setFont(font);

			if (timer ==200) {
				
				if (numOfFingers == questionList.getQuestionArray().at(qs).getCorrectAnswer()) {
					score++;
					flag = 1;
					cout << "POprawna odp" << numOfFingers <<"  corr answ :"<< questionList.getQuestionArray().at(qs).getCorrectAnswer()<<endl;
				}
				else {
					flag = 2;
					cout << "Zla odp" << numOfFingers << "  corr answ :" << questionList.getQuestionArray().at(qs).getCorrectAnswer() << endl;
				}

				timer = 0;
				qs++;
				string mystr = "Pytanie ";
				mystr.append(to_string(qs + 1));
				mystr.append(" / ");
				mystr.append(to_string(totalQuestions));
				currentQuestion.setString(mystr);

			}

			currentScore.setString("Punkty " + to_string(score));
			window.draw(textP);
			window.draw(currentScore);
			for (int i = 0; i < answersBox.size(); i++){

	
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

			timer++;
			//cv::putText(drawing, to_string(numOfFingers), cv::Point(50, 50), FONT_HERSHEY_SIMPLEX, 2, 255);
			//cv::imshow("window", drawing);
			//
			//if (waitKey(30) == 27)
			//	return -1;

		return 0;

	}

};






int main() {
	

		RectangleShape questionBox(Vector2f(1800.0f, 400.0f));
		vector<RectangleShape> answersBox(5, RectangleShape(Vector2f(360, 300)));
		QuestionList questionList;
		FingersDetector fingersDetector;

		Quiz mainController(questionBox, answersBox, questionList, fingersDetector);

		mainController.setUp();
		mainController.configCamera();
		int startFlag = 1;
		while (true){

			try {
				mainController.handleEvent();
				int x = mainController.detectFingers();
				if (x == 5 && startFlag == 0) {
					mainController.handleAnswers();
					startFlag = 1;
				}
				else if (startFlag == 1)
					mainController.handleAnswers();
					

			}
			catch (cv::Exception& e) {
				//cout << e.what();
			}
		}

		//Mat img;
		//VideoCapture cam(0);
		//bool printQuestion = true;
		//int timerQuestion = 0, numOfQuestion = 0, totalQuestions = 3 - 1, timeToAnswer = 100;

		//FingersDetector fing;
		//QuestionList questionList;
	
		//int x = questionList.readQuesionsFromFile("C:\\Users\\micha\\OneDrive\\Pulpit\\pytania.txt");
		//if (x == -1) {
		//	cout << "Nie mozna otworzyc pliku" << endl;
		//	return -2;
		//}


		//while (1) {

		//	try {
		//		cam.read(img);
		//		Mat thres = fing.processingImage(img);
		//		if (thres.empty()) {
		//			cout << "File not found" << endl;
		//			return -1;
		//		}
		//		vector<vector<Point>> contours = fing.findContoursImage(thres);
		//		vector<vector<Point>> hull(contours.size());
		//		vector<vector<int> > hulls2(contours.size());
		//		vector<vector<Vec4i>> convDefect = fing.createConvexity(hull, contours);
		//		Mat drawing = fing.drawContoursImage(thres, contours, hull);
		//		int numOfFingers = fing.countFingers(contours, drawing, convDefect);

		//		if (printQuestion == true && numOfQuestion <= totalQuestions) {
		//			
		//			questionList.getQuestionArray().at(numOfQuestion).print();
		//			printQuestion = false;
		//		}
		//		timerQuestion++;

		//		if (timerQuestion == timeToAnswer && numOfQuestion <= totalQuestions) {
		//			if (numOfFingers == questionList.getQuestionArray().at(numOfQuestion).getCorrectAnswer()) {
		//				cout << endl<<"Dobra odpowiedz!" << endl<<endl;

		//			}
		//			else
		//				wcout << endl<<"Zla odpowiedz, poprawna odpowiedz to : " << questionList.getQuestionArray().at(numOfQuestion).getCorrectAnswerName() << endl<<endl;
		//			printQuestion = true;
		//			timerQuestion = 0;
		//			numOfQuestion++;
		//		
		//		}

		//		putText(drawing, to_string(numOfFingers), Point(50, 50), FONT_HERSHEY_SIMPLEX, 2, 255);
		//		cv::imshow("window", drawing);
		//		if (waitKey(30) == 27)return -1;

		//	}
		//	catch (cv::Exception& e)
		//	{
		//	}

		//}
		//
		return 0;	
}
