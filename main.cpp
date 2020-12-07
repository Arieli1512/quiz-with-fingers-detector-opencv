#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "Question.h"
#include "QuestionList.h"
#include "FingersDetector.h"


using namespace std;
using namespace sf;
using namespace cv;


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
	int totalQuestions = 10;
	int flag = 0;
	int score = 0;


public:
	RenderWindow window;
	Quiz(RectangleShape questionBox, vector<RectangleShape> answersBox, QuestionList questionList, FingersDetector fingersDetector)
		:window(VideoMode(1200.0f, 650.0f), "Quiz", Style::Close | Style::Resize) //1800 650
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


	void endingScreen()
	{
		window.clear();
		destroyWindow("window");
		destroyWindow("window real");
		this->camera.release();


		RectangleShape endScreen(Vector2f(1200.0f, 650.0f));
		endScreen.setTexture(&questionTexture);
		//endScreen.setOrigin(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
		//endScreen.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

		Text text2;
		text2.setFont(font);
		text2.setCharacterSize(40);
		text2.setString(L"Gra skończona, Twój wynik to: " + to_string(score)+L" punktów");
		text2.setOrigin(text2.getLocalBounds().width / 2.0f, text2.getLocalBounds().height / 2.0f);
		text2.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
		while (true)
		{
			window.clear();
			window.draw(endScreen);
			window.draw(text2);
			window.display();
			handleEvent();
		}
	}
	
	
	void startingScreen() {

		Texture texture;
		Image image;
		image.loadFromFile("../imagesSfml/answer.png");
		//image.createMaskFromColor(sf::Color::White);
		texture.loadFromImage(image);
		Sprite sprite;
		sprite.setTexture(texture);
		sprite.setPosition(1100, 10);

		//vector<Sprite> sprites = setFingersIcons();
		vector<string> names;
		vector<Sprite> sprites;
		vector<Texture> textures;
		vector<Image> images;
		names.push_back("../imagesSfml/finger.png");
		names.push_back("../imagesSfml/two-fingers.png");
		names.push_back("../imagesSfml/three-fingers.png");
		names.push_back("../imagesSfml/four-fingers.png");
		names.push_back("../imagesSfml/five-fingers.png");

		for (int i = 0; i < 5; i++) {

			Texture texture2;
			Image image2;
			image2.loadFromFile(names.at(i));
			//image.createMaskFromColor(sf::Color::White);
			images.push_back(image2);
			texture2.loadFromImage(images.at(i));

			textures.push_back(texture2);
		}

		for(int i=0;i<5;i++){
			Sprite sprite2;
			sprite2.setTexture(textures.at(i));
			sprite2.setPosition(250+i*150, 400);
			sprites.push_back(sprite2);
		}





		font.loadFromFile("../fonts/AllerDisplay.ttf");
		questionTexture.loadFromFile("../imagesSfml/baner4.jpg");
		RectangleShape helloScreen(Vector2f(1200.0f, 650.0f));
		helloScreen.setTexture(&questionTexture);
		helloScreen.setOrigin(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	
		helloScreen.setPosition(helloScreen.getLocalBounds().width/2.0f, helloScreen.getLocalBounds().height / 2.0f);

		Text text1;
		text1.setPosition(25, 10);
		text1.setFont(font);
		text1.setCharacterSize(45);
		text1.setString(L"QUIZ");

		Text text2;
		text2.setFont(font);
		text2.setCharacterSize(40);
		text2.setString(L"Przed tobą quiz skaadający się z 10 pytań.\nPokazuj palce, aby odpowiadać na pytania!\nAby rozpocząć grę pokaż 5 palców.");
		text2.setOrigin(text2.getLocalBounds().width / 2.0f, text2.getLocalBounds().height / 2.0f);
		text2.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f)-60);
		int flag = 0;

		while (true) {
			try {
				window.clear();
				window.draw(helloScreen);
				window.draw(text1);
				window.draw(text2);

				window.draw(sprite);

				for (int i = 0; i < sprites.size(); i++) {

					window.draw(sprites.at(i));
				}
				//window.draw(sprite2);
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

	void waitingScreen() {
		window.clear();



	

		RectangleShape waitScreen(Vector2f(1200.0f, 650.0f));
		waitScreen.setTexture(&questionTexture);

		//waitScreen.setOrigin(waitScreen.getLocalBounds().width / 2.0f, waitScreen.getLocalBounds().height / 2.0f);
		//waitScreen.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
		Text text2;
		text2.setFont(font);
		text2.setCharacterSize(40);


		//text2.setOrigin(text2.getLocalBounds().width / 2.0f, text2.getLocalBounds().height / 2.0f);
		//text2.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

		while (true)
		{
			window.clear();
			window.draw(waitScreen);
			elapsed = clock.getElapsedTime();
			int timeRemained = timer - (int)elapsed.asSeconds();
			if (timeRemained == 0) {
				clock.restart();
				return;
			}
			text2.setOrigin(text2.getLocalBounds().width / 2.0f, text2.getLocalBounds().height / 2.0f);
			text2.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f));
			text2.setString(L"Quiz rozpocznie się za " + to_string(timeRemained)+" ...");
			detectFingers();
			window.draw(text2);
			window.display();
			handleEvent();
		}
	}
	void setUp() {

		int x = questionList.readQuesionsFromFile("../pytania_projekt_sport.txt");
		if (x == -1) {
			return;
		}

		questionList.mixQuestions();

		textAnswers.setCharacterSize(25);
		textQuestions.setCharacterSize(35);

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

		

		textQuestions.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 100);
		window.setFramerateLimit(60);
		//window.clear(sf::Color(255, 255, 255));
		Text score("Pytanie 1/20", font);


		for (int i = 0; i < answersBox.size(); i++) {
			answersText[i].setFillColor(Color::White);
			answersBox[i].setOrigin(answersBox[i].getSize().x / 2.0f, answersBox[i].getSize().y / 2.0f);
			answersText[i].setOrigin(answersText[i].getLocalBounds().width / 2.0f, answersText[i].getLocalBounds().height / 2.0f);
			answersBox[i].setPosition(120.0f + 240.0f * i, 525.0f);
			answersText[i].setPosition(answersBox[i].getPosition());
			answersText[i].setPosition(120.0f + 240.0f * i, 525.0f);
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
				//cout << window.getSize().x << endl;
				//cout << window.getSize().y << endl;
				//window.setView(sf::View(window.getView().getCenter(), sf::Vector2f((float)event.size.width, (float)event.size.height)));
				break;

			}
		}
	}


	int detectFingers() {
		cv::Mat img;
		Mat partImg;
		
		camera.read(img);
		cv::Rect rect = cv::Rect(cv::Point2f(10, 10), cv::Point2f(300, 300));
		rectangle(img, cv::Point2f(10, 10), cv::Point2f(300, 300), cv::Scalar(255, 0, 0));
		partImg = img(rect);
		
		cv::imshow("window real", img);


		Mat thres = fingersDetector.processingImage(partImg);
		if (thres.empty()) {
			return -1;
		}
		vector<vector<cv::Point>> contours = fingersDetector.findContoursImage(thres);
		vector<vector<cv::Point>> hull(contours.size());
		vector<vector<int> > hulls2(contours.size());
		vector<vector<cv::Vec4i>> convDefect = fingersDetector.createConvexity(hull, contours);
		drawing = fingersDetector.drawContoursImage(thres, contours, hull);
		numOfFingers = fingersDetector.countFingers(contours, drawing, convDefect);


		cv::putText(drawing, to_string(numOfFingers), cv::Point(50, 50), FONT_HERSHEY_SIMPLEX, 2, Scalar(0,0,255),3);
		cv::imshow("window", drawing);
		//cv::imshow("real window",img );
		//waitKey(40);
		//cv::imshow("window real", pic);
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
		textP.setPosition(window.getSize().x-250, 10);
		timerW.setPosition(window.getSize().x - 200, 50);
		timerW.setFont(font);
		timerW.setCharacterSize(35);
		timerW.setFillColor(Color::White);
		textP.setFont(font);
		textP.setCharacterSize(25);
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


	RectangleShape questionBox(Vector2f(1200, 410.0f));
	vector<RectangleShape> answersBox(5, RectangleShape(Vector2f(240, 240)));
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
			if (x >1 && startFlag == 0) {
				mainController.clockReset();
				mainController.waitingScreen();
				mainController.handleAnswers();
				startFlag = 1;
			}
			else if (startFlag == 1) {
				int check = mainController.handleAnswers();
				if (check == 1)
					break;
			}


		}
		catch (cv::Exception& e) {
		}
	}

	mainController.endingScreen();
	return 0;
}
