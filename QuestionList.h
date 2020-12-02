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

public:
	vector<Question> getQuestionArray();
	int readQuesionsFromFile(string pathToFile);
	void mixQuestions();
};
