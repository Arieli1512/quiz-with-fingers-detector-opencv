#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 
#include <random>
#include <ctime>
#include "Question.h"

class QuestionList {

private:
	vector<Question> questionArray;
	wstring readQuestion(wifstream& file);
	vector<wstring> readAnswers(wifstream& file);
public:
	vector<Question> getQuestionArray();
	int readFromFile(string pathToFile);
	void mixQuestions();
};
