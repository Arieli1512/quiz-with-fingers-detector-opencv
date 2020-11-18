#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Question {
private:
	string question;
	string optionA;
	string optionB;
	string optionC;
	string optionD;
	string optionE;
	string answer;
	int answerNumber;

public:
	void setQuestion(string question);
	void setOptionA(string optionA);
	void setOptionB(string optionB);
	void setOptionC(string optionC);
	void setOptionD(string optionD);
	void setOptionE(string optionE);
	void setAnswer(string answer);
	void setAnswerNumber(int number);

	string getQuestion();
	string getOptionA();
	string getOptionB();
	string getOptionC();
	string getOptionD();
	string getOptionE();
	string getAnswer();
	int getAnswerNumber();

};

class QuestionList {

private:
	vector<Question> questionArray;
public:
	int readQuesionsFromFile(string pathToFile);
	void printAllQuestions();
	void printQuestion(int index);
	string getAnswer(int index);
	int getAnswerNumber(int index);
	~QuestionList();
};
