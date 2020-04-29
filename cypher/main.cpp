#include <iostream>
#include <regex>
#include "json.hpp"
#include <Windows.h>
#include <fstream>
#include <ctime>
using namespace std;
using json = nlohmann::json;
class base
{
public:
	virtual void createKey(string text) = 0;
};
class rePlace : public base
{
public:
	void createKey(string text) override
	{
		bool trigger = false;
		vector<int> key;
		for (int a = 0; a < text.size(); a++)
			key.push_back(' ');
		for (int a = 0; a < key.size(); a++)
		{
			int num = rand() % key.size();
			for (int i = 0; i < text.size(); i++)
			{
				if (key[i] == num)
				{
					a = -1;
					for (int b = 0; b < text.size(); b++)
						key[b] = ' ';
					break;
				}
				if (i == text.size() - 1)
					key[a] = num;
			}
		}
		char cho;
		cout << "Key was generated. Print it on display? (Y/N)";
		while (1)
		{
			cin >> cho;
			if (cho == 'Y')
			{
				for (int a = 0; a < key.size(); a++)
					cout << key[a];
				cout << endl;
				break;
			}
			else if (cho == 'N')
			{
				break;
			}
			else
			{
				cout << "Incorrect answer. Try again" << endl;
				continue;
			}
		}
		saveKey(key , text);
	}
private:
	void saveKey(vector<int> key, string text)
	{
		cout << "Enter path for save key in document" << endl;
		string path;
		cin >> path;
		ofstream dock;
		dock.open(path, std::ios::app);
		if (dock.is_open())
		{
			dock << "Replace {Key: ";
			for (int a = 0; a < key.size(); a++)
				dock << key[a] << ",";
			dock << "}";
			cout << "Key was saved" << endl;
			crypt(key, text);
		}
		else
			cout << "Error. Cannot open this document" << endl;
	}
	void crypt(vector<int> key, string text)
	{
		string cypher;
		for (int a = 0; a < text.size(); a++)
			cypher.push_back(' ');
		int i = 0;
		for (int a = 0; a < text.size(); a++)
		{
			int place = key[i];
			cypher[place] = text[a];
			i++;
		}
		cout << "Cypher was created" << endl;
		cout << "Enter path to save cypher: " << endl;
		string path;
		cin >> path;
		ofstream dock;
		dock.open(path, std::ios::app);
		if (dock.is_open())
		{
			dock << "Replace {cypher: ";
			for (int a = 0; a < key.size(); a++)
				dock << cypher[a];
			dock << "}";
			cout << "Cypher was saved" << endl;
		}
		else
			cout << "Error. Cannot open this document" << endl;
	}
};
class gamming : public base
{
public:

private:

};
class change : public base
{
public:

private:

};
int main()
{
	while (1)
	{
		srand(time(NULL));
		cout << "Choose the option" << endl;
		cout << "1. Decrypt" << endl;
		cout << "2. Create key and crypt text" << endl;
		cout << "3. Exit" << endl;
		int cho;
		cin >> cho;
		if (cho == 1)
		{

		}
		else if (cho == 2)
		{
			cout << "Choose the kind of crypt" << endl;
			cout << "1. Replacement" << endl;
			cout << "2. Gamming" << endl;
			cout << "3. Transposition" << endl;
			cin >> cho;

			if (cho == 1)
			{
				cout << "Enter path of document with text: " << endl;
				string path;
				cin >> path;
				fstream text(path);
				string textDoc;
				if (text.is_open())
				{
					getline(text, textDoc);
					rePlace a;
					a.createKey(textDoc);
				}
				else
				{
					cout << "Error. The document was not found" << endl << endl;
					continue;
				}
			}
			else if (cho == 2)
			{

			}
			else if (cho == 3)
			{

			}
		}
		else
			return 0;
	}
}