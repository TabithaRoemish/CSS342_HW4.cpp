// File: SetDriver.cpp
//	Programmer: Tabitha Roemish 
//	Date: 10/30/2017
//	File Includes:
//		main()

#include <string>
#include <iostream>
#include "LinkedList.h"
#include "Set.h"

using namespace std;
void parseWords(string str, LinkedList<string>& lst);


int main()
{
	LinkedList<string> lst1;
	string starter = "This is a demonstration of the LinkedList insert function with strings.";
	parseWords(starter, lst1);
	cout << "Here is a list with no duplicates: \n";
	cout << lst1;
	
	//insert duplicates
	string duplicates = "the the the a a a a LinkedList insert is is";
	parseWords(duplicates, lst1);
	Set<string> SetCopy(lst1);
	cout << endl;
	cout << "After adding this string to the list, 'the the the a a a a LinkedList insert is is', ";
	cout << "\nHere is the count for 'the': " << SetCopy.getCount("the");
	cout << endl << "\nand here are the top three keys in the set: \n";
	SetCopy.printPopular(cout);
	cout << endl;

	cout << "Here is the full list: \n";
	cout << SetCopy;
	
	cin.get();
	return 0;
}

void parseWords(string str, LinkedList<string>& lst)
{
	string temp = "";
	for (unsigned i = 0; i < str.length(); i++)
	{
		if (str[i] != ' ' && !ispunct(str[i]))
			temp += str[i];
		else
		{
			if (temp.length() > 0)
			{
				lst.insert(temp);
				temp = "";
			}
		}
	}
}