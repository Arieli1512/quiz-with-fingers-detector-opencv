#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "processing.h"
#include "questions.h"
#include <SFML/Graphics.hpp>

using namespace cv;
using namespace std;
using namespace sf;

int main() {
	
		QuestionList questionList;
		int totalQuestions = 10;
		int x = questionList.readQuesionsFromFile("../pytania_projekt.txt");

		if (x == -1) {
			cout << "Nie mozna otworzyc pliku" << endl;
			return -2;
		}
		RenderWindow window(VideoMode(1400, 650), "Quiz", Style::Close | Style::Resize);
		RectangleShape pytanieBox(Vector2f(1400.0f, 400.0f));

		vector<RectangleShape> odpowiedziBox(5, RectangleShape(Vector2f(280, 300)));
		string abc[5] = { "Zielony","Fioletowy", "Niebieski", "Czerwony", "Czarny", };

		Texture button,pytanieTexture;
		Font font;

		Text textAnsweres("A",font);
		textAnsweres.setCharacterSize(30);
		Text textQuestions("A", font);
		textQuestions.setCharacterSize(36);

		vector<Text> odpowiedziText(5, textAnsweres);
		
		font.loadFromFile("../fonts/AllerDisplay.ttf");
		button.loadFromFile("../imagesSfml/baner4.jpg");

	
		textQuestions.setFillColor(sf::Color::White);

	
		pytanieTexture.loadFromFile("../imagesSfml/button.png");

		pytanieBox.setTexture(&button);
		pytanieBox.setFillColor(sf::Color::White);
		window.setFramerateLimit(60);
		window.clear(sf::Color(255, 255, 255));
		Event event;

		int timer = 0, qs = 0, qsFlag = 0;

		Text score("Pytanie 1/20", font);
		textQuestions.setCharacterSize(36);

		while (window.isOpen())
		{

			//window.clear(Color::White);
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case Event::Closed:
					window.close();
					break;
				case Event::Resized:
					//printf("New window width %i \nNew window height %i \n", event.size.width, event.size.height);
					break;

				}
			}

			window.clear();
			window.draw(pytanieBox);

			
			odpowiedziBox[1].setFillColor(sf::Color::Red);
			odpowiedziBox[2].setFillColor(sf::Color::Blue);
			odpowiedziBox[3].setFillColor(sf::Color(0, 153, 51));
			odpowiedziBox[4].setFillColor(sf::Color(102, 20, 179));
			odpowiedziBox[0].setFillColor(sf::Color::Magenta);

	
			pytanieBox.setPosition(0, 0);
			textQuestions.setPosition(300, 170);
		
			if (timer == 200) {
				timer = 0;
				qs++;
				qsFlag = qs-1;
				string mystr = "Pytanie ";
				mystr.append(to_string(qs+1));
				mystr.append("/20");
				score.setString(mystr);
				
			}
			
				for (int i = 0; i < odpowiedziBox.size(); ++i)
				{
			
			
				
					wstring questionString =questionList.getQuestionArray().at(qs).getQuestion();
					textQuestions.setString(sf::String::fromUtf8(questionString.begin(), questionString.end()));
					wstring answersString = questionList.getQuestionArray().at(qs).getAnswers().at(i);
					odpowiedziText[i].setString(sf::String::fromUtf8(answersString.begin(), answersString.end()));
	

					odpowiedziText[i].setFillColor(sf::Color::White);
					odpowiedziBox[i].setPosition(0.0f + 280.0f * i, 400.0f);
					odpowiedziText[i].setPosition(80.0f + 280.0f * i, 500.0f);
					window.draw(odpowiedziBox[i]);
					window.draw(odpowiedziText[i]);
					window.draw(textQuestions);
				}
			score.setPosition(10, 10);
			window.draw(score);
				

			window.display();

			timer++;
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