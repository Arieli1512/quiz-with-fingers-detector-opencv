#include "questions.h"
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

	int answerNumber=0;
	if (answer == getOptionA())
		answerNumber = 1;
	else if (answer == getOptionB())
		answerNumber = 2;
	else if (answer == getOptionC())
		answerNumber = 3;
	else if (answer == getOptionD())
		answerNumber = 4;
	else if (answer == getOptionE())
		answerNumber = 5;
	else answerNumber = 0;

	setAnswerNumber(answerNumber);
}
void Question::setAnswerNumber(int number) {

	this->answerNumber = number;
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
int Question::getAnswerNumber() {
	return answerNumber;
 }



QuestionList::~QuestionList() {
	questionArray.clear();
}


void QuestionList::printQuestion(int index) {
	Question question = questionArray.at(index);
	cout << question.getQuestion() << endl;
	cout << "1) " << question.getOptionA() << endl;
	cout << "2) " << question.getOptionB() << endl;
	cout << "3) " << question.getOptionC() << endl;
	cout << "4) " << question.getOptionD() << endl;
	cout << "5) " << question.getOptionE() << endl;
}
void QuestionList::printAllQuestions() {
	for (int i = 0; i < questionArray.size(); i++) {
		Question question = questionArray.at(i);
		cout << "Question: " << question.getQuestion() << endl << "Ansewer: " << question.getAnswer() << endl;
	}
}

int QuestionList::getAnswerNumber(int index) {
	return questionArray.at(index).getAnswerNumber();
}

string QuestionList::getAnswer(int index) {
	return questionArray.at(index).getAnswer();
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
