#include "StartupScreen.h"

using namespace sf;

StartupScreen::StartupScreen(RenderWindow& window, VideoCapture camera) :window(window) {
	this->camera = camera;
};

void StartupScreen::handleEvent() {
	Event event;
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

void StartupScreen::showStartingScreen() {

	RectangleShape helloScreen(Vector2f(1200.0f, 650.0f));
	Text text1, text2;
	Texture texture, questionTexture;
	Font font;
	Image image;
	vector<string> names;
	vector<Texture> textures;
	vector<Image> images;
	Sprite sprite;
	image.loadFromFile("../imagesSfml/answer.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setPosition(1100, 10);
	names.push_back("../imagesSfml/finger.png");
	names.push_back("../imagesSfml/two-fingers.png");
	names.push_back("../imagesSfml/three-fingers.png");
	names.push_back("../imagesSfml/four-fingers.png");
	names.push_back("../imagesSfml/five-fingers.png");
	vector<Sprite> sprites = configureSpritesIcons(names, textures, images, 250, 400, 150);
	questionTexture.loadFromFile("../imagesSfml/baner.jpg");
	font.loadFromFile("../fonts/AllerDisplay.ttf");
	configurateStartingScreen(text1, text2, helloScreen, questionTexture, font);

	while (true) {
		try {
			window.clear();
			window.draw(helloScreen);
			window.draw(text1);
			window.draw(text2);
			window.draw(sprite);
			for (int i = 0; i < sprites.size(); i++)
				window.draw(sprites.at(i));
			window.display();
			handleEvent();
			if (detectFingers() == 5)
				break;
		}
		catch (cv::Exception& e) {
		}
	}
}

void StartupScreen::configurateStartingScreen(Text& text1, Text& text2, RectangleShape& helloScreen, Texture& questionTexture, Font& font) {
	text1.setPosition(25, 10);
	text1.setFont(font);
	text1.setCharacterSize(45);
	text1.setString(L"QUIZ");
	text2.setFont(font);
	text2.setCharacterSize(40);
	text2.setString(L"Przed tob¹ Quiz sk³adaj¹cy siê z 10 pytañ.\n"
		"Pokazuj palce, aby odpowiadaæ na pytania!\nAby rozpocz¹æ grê poka¿ 5 palców.");
	text2.setOrigin(text2.getLocalBounds().width / 2.0f, text2.getLocalBounds().height / 2.0f);
	text2.setPosition(window.getSize().x / 2.0f, (window.getSize().y / 2.0f) - 60);
	helloScreen.setTexture(&questionTexture);
	helloScreen.setOrigin(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
	helloScreen.setPosition(helloScreen.getLocalBounds().width / 2.0f, helloScreen.getLocalBounds().height / 2.0f);

}

vector<Sprite> StartupScreen::configureSpritesIcons(vector<string>& names, vector<Texture>& textures, vector<Image>& images, int x, int y, int shift) {
	vector<Sprite> sprites;
	for (int i = 0; i < 5; i++) {
		Texture texture2;
		Image image2;
		image2.loadFromFile(names.at(i));
		images.push_back(image2);
		texture2.loadFromImage(images.at(i));
		textures.push_back(texture2);
	}
	for (int i = 0; i < 5; i++) {
		Sprite sprite2;
		sprite2.setTexture(textures.at(i));
		sprite2.setPosition(x + i * shift, y);
		sprites.push_back(sprite2);
	}
	return sprites;
}

Point2f StartupScreen::readFromFileCoordinates() {
	ifstream file;
	string coordX;
	string coordY;

	file.open("../config.txt");
	if (file.fail() == true)
		return NULL;

	getline(file, coordX);
	int resX = stoi(coordX);
	getline(file, coordY);
	int resY = stoi(coordY);
	Point2f point = Point2f(resX, resY);
	file.close();
	return point;
}

int StartupScreen::detectFingers() {

	FingersDetector fingersDetector;
	Mat img, partImg;
	camera.read(img);
	Point2f point = readFromFileCoordinates();
	cv::Rect rect = cv::Rect(cv::Point2f(point.x, point.y), cv::Point2f(300 + point.x, 300 + point.y));
	rectangle(img, cv::Point2f(point.x, point.y), cv::Point2f(300 + point.x, 300 + point.y), cv::Scalar(255, 0, 0));
	partImg = img(rect);
	cv::imshow("window real", img);
	int numOfFingers = fingersDetector.countFingers(partImg);
	Mat contoursImage = fingersDetector.getContoursImage();
	cv::putText(contoursImage, to_string(numOfFingers), cv::Point(50, 50), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 0, 255), 3);
	cv::imshow("window", contoursImage);
	return numOfFingers;
}