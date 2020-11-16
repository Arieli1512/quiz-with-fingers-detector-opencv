#include "Questions.h"
#include <string>

void Question::setQuestion(string question) {
	this->question = question;
}
void Question::setOptionA(string optionA) {
	this->optionA = optionA;
}
void Question::setOptionB(string optionB) {
	this->optionB = optionB;
}
void Question::setOptionC(string optionC) {
	this->optionC = optionC;
}
void Question::setOptionD(string optionD) {
	this->optionD = optionD;
}
void Question::setOptionE(string optionE) {
	this->optionE = optionE;
}
void Question::setAnswer(string answer) {
	this->answer = answer;
}

string Question::getQuestion() {
	return question;
}

string Question::getOptionA() {
	return optionA;
}

string Question::getOptionB() {
	return optionB;
}

string Question::getOptionC() {
	return optionC;
}

string Question::getOptionD() {
	return optionD;
}

string Question::getOptionE() {
	return optionE;
}

string Question::getAnswer() {
	return answer;
}




QuestionList::~QuestionList() {
	questionArray.clear();
}


void QuestionList::printQuestion(int index) {
	Question question = questionArray.at(index);
	cout << "Question: " << question.getQuestion() << endl << "Ansewer: " << question.getAnswer() << endl;
}
void QuestionList::printAllQuestions() {
	for (int i = 0; i < questionArray.size(); i++) {
		Question question = questionArray.at(i);
		cout << "Question: " << question.getQuestion() << endl << "Ansewer: " << question.getAnswer() << endl;
	}
}

int QuestionList::readQuesionsFromFile(string pathToFile) {

	ifstream file;
	file.open(pathToFile, ios::in);
	if (file.fail() == true) {
		//cout << "Nie udalo sie otworzyc pliku!";
		return -1;
	}

	int numOfLines = 7;
	while (!file.eof()) {

		Question question;
		string text;
		vector<string> texts;
		for (int i = 0; i < numOfLines; i++) {
			getline(file, text);
			texts.push_back(text);
		}
		question.setQuestion(texts.at(0));
		question.setOptionA(texts.at(1));
		question.setOptionB(texts.at(2));
		question.setOptionC(texts.at(3));
		question.setOptionD(texts.at(4));
		question.setOptionE(texts.at(5));
		question.setAnswer(texts.at(6));

		questionArray.push_back(question);
	}
	file.close();
	return 0;
}
