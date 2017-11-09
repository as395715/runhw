//****************************************************************
//Program: HW5.cc
//
//Author: Ashley Smith
//Email: as395715@ohio.edu
//
//Description: This program will take in students test answers from a file, grade the test, 
//				and print a grade card for each student. This will be done using arrays.
//
//Date: Created: October 19, 2016 Modified: October 27, 2016
//****************************************************************

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<string>
#include<fstream>

using namespace std;

void load_key(char answers[], int &count, ifstream &instream);
//******************************************************************
 //
 // Function: load_key
 //
 // Purpose: loads the first line from the file into the array
 //
 // Parameters: instream - takes the content from the file
 //		answers - first line, key
 //		count - number of elements in the array
 //
 // Pre Conditions: file will load until end of file
 //
 // Post Conditions: will load content into array 
 //
 //******************************************************************

void load_report(char answers[], char student_answers[], int &count, ifstream &instream);
//******************************************************************
 //
 // Function: load_report
 //
 // Purpose: loads the contents from the file into the array
 //
 // Parameters: instream - takes the content from the file
 //		answers - first line, key array
 //		student_answers - answers by the students
 //		count - number of elements in the array
 //
 // Pre Conditions: file will load until end of file
 //
 // Post Conditions: will load content into array 
 //
 //******************************************************************

void test_check(char answers[], char student_answers[], int &total, double &score, int &count, ifstream &instream);
//******************************************************************
 //
 // Function: test_check
 //
 // Purpose: compares key answers to students answers to grade it
 //
 // Parameters: instream - takes the content from the file
 //		answers - first line, key array
 //		student_answers - answers by the students
 //		score - percentage grade
 //		count - number of elements in the array
 //
 // Pre Conditions: compares the elements of both arrays to determine grade
 //
 // Post Conditions: will determine the score 
 //
 //******************************************************************

void grade_report(char answers[], char student_answers[], double &score, int &count, ifstream &instream);
//******************************************************************
 //
 // Function: grade_report
 //
 // Purpose: prints out the individual grade reports for each student
 //
 // Parameters: instream - takes the content from the file
 //		answers - first line, key array
 //		student_answers - answers by the students
 //		score - percentage grade
 //		count - number of elements in the array
 //
 // Pre Conditions: file will load until end of file
 //
 // Post Conditions: prints each students grade report
 //
 //******************************************************************

char letter_grade(double &score);
//******************************************************************
 //
 // Function: letter_grade
 //
 // Purpose: converts the percentage score into a letter grade
 //
 // Parameters: score - percentage grade
 //
 // Pre Conditions: will determine the letter grade based on percentage
 //
 // Post Conditions: returns the letter grade
 //
 //******************************************************************

int main()
{
	ifstream instream;
	char answers[100];
	char student_answers[50];
	int count = 0;
	double score = 0;
	char filename[100];

	cout << "Please enter the file name: ";
	cin >> filename;

	instream.open(filename);

	load_key(answers, count, instream);

	for (int i = 0; i < count; ++i)
	{
		cout << answers[i];
	}
	cout << endl;

	while(!instream.eof())
	{
	grade_report(answers, student_answers, score, count, instream);
	}



	instream.close();

	return 0;
}

//All funtion definitions

//Function definition to load the key of answers into an array.
void load_key(char answers[], int &count, ifstream &instream)
{
	int i = 0;
	instream.get(answers[i]);
	answers[i] = tolower (answers[i]);

	while(answers[i] != '\n')
	{
		i++;
		instream.get(answers[i]);
		answers[i] = tolower (answers[i]);
	}
	count = i;
	count--;
}

//Function definition to load the students names and answers into an array.
void load_report(char answers[], char student_answers[], int &count, ifstream &instream)
{
	string first;
	string last;

	for (int i = 2; i < count; ++i)
	{
	
		instream >> first;
		instream >> last;

		cout << "\n" << last << ", " << first << "\n";

		cout << "-----------------------------------------" << endl;

		cout << "The correct answers are in parenthesis: " << endl;

		instream.get(student_answers[i]);
		student_answers[i] = tolower (student_answers[i]);

		if(student_answers[i] == ' ')
		{
			student_answers[i] = '-';
		}

		while(student_answers[i] != '\n')
		{
			i++;
			instream.get(student_answers[i]);
			student_answers[i] = tolower (student_answers[i]);

			if(student_answers[i] == ' ')
			{
				student_answers[i] = '-';
			}
		}
		count = i;
	}
}

//Function definition to compare the key answers to the students answers and determine the score.
void test_check(char answers[], char student_answers[], double &score, int &count, ifstream &instream)
{
	//int total = 0;
	
	for (int i = 0; i < count; ++i)
	{
		int total = 0;

		for(int k = 0; k < count; k++)
		{
			if(student_answers[i] == answers[i])
			{
				total++;
				score = (total/count)*100;
			}
		}
	}
}

//Function definition to print out the grade report for each student.
void grade_report(char answers[], char student_answers[], double &score, int &count, ifstream &instream)
{

	load_report(answers, student_answers, count, instream);

	for (int i = 3; i < count-1; ++i)
	{
		cout << i-2 << ": " << student_answers[i] << "(" << answers[i-3] << ")" << endl;
	}
	count = count-4;

	test_check(answers, student_answers, score, count, instream);
	letter_grade(score);
}

//Function definition to convert the percentage grade to a letter grade.
char letter_grade(double &score)
 {
 	if(score <= 100 && score >= 90)
 	{
 		cout << "Score : " << score << "%% " << "A" << endl;
	}
 	else if(score < 90 && score >= 80)
 	{
 		cout << "Score : " << score << "%% " << "B" << endl;
 	}
 	else if(score < 80 && score >= 70)
 	{
 		cout << "Score : " << score << "%% " << "C" << endl;
 	}
 	else if(score < 70 && score >= 60)
 	{
 		cout << "Score : " << score << "%% " << "D" << endl;
 	}
 	else if(score < 60)
 	{
 		cout << "Score : " << score << "%% " << "F" << endl;
 	}
 	return 0;
 }