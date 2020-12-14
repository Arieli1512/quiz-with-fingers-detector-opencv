#include "QuestionList.h"

vector < Question > QuestionList::getQuestionArray() {
	return this->questionArray;
}


wstring QuestionList::readQuestion(wifstream& file) {
	wstring textQuestion;
	getline(file, textQuestion);
	size_t len = textQuestion.length();


	if (textQuestion.at(len - 1) != '\?') {
		wstring nextLine;
		getline(file, nextLine);
		textQuestion += '\n';
		textQuestion.append(nextLine);
	}
	return textQuestion;
}

vector<wstring> QuestionList::readAnswers(wifstream& file) {
	int numOfLines = 5;
	vector < wstring > texts;
	for (int i = 0; i < numOfLines; i++) {

		wstring text;
		getline(file, text);
		texts.push_back(text);
	}
	return texts;
}

int QuestionList::readFromFile(string pathToFile) {

	wifstream file;
	file.open(pathToFile.c_str());
	if (file.fail() == true)
		return -1;
	
	while (!file.eof()) {
		Question question;
		wstring textQuestion = readQuestion(file);
		question.setQuestion(textQuestion);
		vector < wstring > texts = readAnswers(file);
		question.setAnswers(texts);
		question.mixAnswers();
		wstring correctAnswerName;
		getline(file, correctAnswerName);
		question.setCorrectAnswerName(correctAnswerName);
		question.compareAnswers(correctAnswerName);
		questionArray.push_back(question);
	}

	file.close();
	return 0;
}




void QuestionList::mixQuestions() {
	srand(unsigned(time(NULL)));
	random_shuffle(questionArray.begin(), questionArray.end());
}

