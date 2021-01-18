#include "StartupScreen.h"


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
	ifstream file;
	file.open("../config.txt");
	if (file.fail() != true) {

	}
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
			if (fingersDetector->detectFingers() == 5) {
				if (file.fail() != true)
					file.close();
				break;
			}
			Point2f point = readFromFileCoordinates();
			fingersDetector->setCoordinatesWindow(point.x, point.y);
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
	int resX, resY;
	file.open("../config.txt");
	if (file.fail() == true)
		return NULL;
	getline(file, coordX);
	getline(file, coordY);

	try {
		resX = stoi(coordX);
	}
	catch (std::exception& e) {
		resX = 0;
	}
	try {
		resY = stoi(coordY);
	}
	catch (std::exception& e) {
		resY = 0;
	}

	Point2f point = Point2f(resX, resY);
	file.close();
	return point;
}
