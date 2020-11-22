#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Question
{
private:
	wstring question;
	vector<wstring> answers;
	int correctAnswer=0;

public:
	void setQuestion(wstring question);
	void setCorrectAnswer(int correct);
	void setAnswers(vector<wstring> answers);
	wstring getQuestion();
	vector<wstring> getAnswers();
	int getCorrectAnswer();
	wstring getCorrectAnswerName();
	void compareAnswers(wstring correctAnswer);
	void print();

};

class QuestionList {

private:
	vector<Question> questionArray;

public:
	vector<Question> getQuestionArray();
	int readQuesionsFromFile(string pathToFile);

};