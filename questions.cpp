#include "questions.h"
#include <string>

void Question::setQuestion(wstring question) {
	this->question = question;
}

void Question::setCorrectAnswer(int correct) {
	this->correctAnswer = correct+1;
}
void Question::setAnswers(vector < wstring > answers) {
	this->answers = answers;
}

wstring Question::getQuestion() {
	return this->question;
}

vector < wstring > Question::getAnswers() {
	return this->answers;
}

int Question::getCorrectAnswer() {
	return this->correctAnswer;
}

void Question::compareAnswers(wstring correctAnswer) {

	for (int i = 0; i < answers.size(); i++) {
		if (correctAnswer == answers.at(i)) {
			setCorrectAnswer(i);
			break;
		}
	}
}

void Question::print() {

	wcout << question << "\n";

	for (int i = 0; i < answers.size(); i++) {

		wcout << i + 1 << ") " << answers.at(i) << endl;
	}
	cout << "\n";


}

wstring Question::getCorrectAnswerName() {
	return answers.at(correctAnswer);
}




vector < Question > QuestionList::getQuestionArray() {
	return this->questionArray;
}

int QuestionList::readQuesionsFromFile(string pathToFile) {

	wifstream file;
	file.open(pathToFile.c_str());
	if (file.fail() == true) {

		return -1;
	}

	int numOfLines = 5;
	while (!file.eof()) {

		Question question;
		wstring textQuestion;

		getline(file, textQuestion);
		question.setQuestion(textQuestion);

		vector < wstring > texts;
		for (int i = 0; i < numOfLines; i++) {

			wstring text;
			getline(file, text);
			texts.push_back(text);
		}
		question.setAnswers(texts);
		question.print();
	
		wstring correctAnswer;
		getline(file, correctAnswer);
		question.compareAnswers(correctAnswer);

		questionArray.push_back(question);
	}
	file.close();

	return 0;
}