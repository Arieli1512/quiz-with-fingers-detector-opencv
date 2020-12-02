#include "QuestionList.h"

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
		//question.print();

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

