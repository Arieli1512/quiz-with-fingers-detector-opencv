#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm> 
#include <random>
#include <ctime>

using namespace std;

class Question {
private:
	wstring question;
	vector<wstring> answers;
	wstring correctAnswerName;
	int correctAnswer = 0;
public:
	void setQuestion(wstring question);
	void setCorrectAnswer(int correct);
	void setAnswers(vector<wstring> answers);
	void setCorrectAnswerName(wstring correctAnswerName);
	wstring getQuestion();
	vector<wstring> getAnswers();
	int getCorrectAnswer();
	wstring getCorrectAnswerName();
	void compareAnswers(wstring correctAnswer);
	void mixAnswers();
};
