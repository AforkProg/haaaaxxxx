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
	virtual void findText() = 0;
};
class rePlace : public base
{
public:
	void findText()
	{
		cout << "Enter path to document with key" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(key)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .key document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream text(path);
		string keyDoc;
		string key;
		if (text.is_open())
		{
			getline(text, keyDoc);
			cmatch result;
			regex regular("(Replace)""(.+)");
			if (regex_search(keyDoc.c_str(), result, regular))
			{
				key = result[2];
				findCypher(key);
			}
			else
			{
				cout << "Key is not for Replace" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Error. The document was not found" << endl << endl;
			system("pause");
			exit(0);
		}
	}
	void createKey(string text)
	{
		bool trigger = false;
		vector<int> key;
		for (int a = 0; a < text.size(); a++)
			key.push_back(' ');
		cout << "Key is generating. Please wait...";
		int time = rand() % 2000 + 1000;
		Sleep(time);
		for (int a = 0; a < key.size(); a++)
		{
			int num = rand() % key.size();
			for (int i = 0; i < text.size(); i++)
			{
				if (key[i] == num)
				{
					num = rand() % key.size();
					i = -1;
					continue;
				}
				if (i == text.size() - 1)
					key[a] = num;
			}
		}
		for (int a = 0; a < 33; a++)
			cout << "\b";
		string chos;
		cout << "Key was generated. Print it on display? (Y/N)";
		while (1)
		{
			cin >> chos;
			cmatch result;
			regex regular("([\\w])");
			if (regex_search(chos.c_str(), result, regular))
			{
				if (chos == "Y")
				{
					for (int a = 0; a < key.size(); a++)
						cout << key[a];
					cout << endl;
					break;
				}
				else if (chos == "N")
				{
					break;
				}
				else
				{
					cout << "Incorrect answer. Try again" << endl;
					continue;
				}
			}
			else
			{
				cout << "Incorrect symbol" << endl;
				system("pause");
				exit(0);
			}
		}
		saveKey(key , text);
	}
private:
	void findCypher(string keyTemp)
	{
		cout << "Enter path to document with cypher" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(encrypt)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .encrypt document extension" << endl;
			system("pause");
			exit(0);
		}
		fstream text(path);
		string keyDoc;
		if (text.is_open())
		{
			getline(text, keyDoc);
			cmatch result;
			regex regular("(Replace)""(.+)");
			if (regex_search(keyDoc.c_str(), result, regular))
			{
				string cypherTemp = result[2];
				string key;
				string cypher;
				for (int a = 7; ; a++)
				{
					if (keyTemp[a] == '}')
						break;
					else
					{
						key.push_back(keyTemp[a]);
					}
				}
				for (int a = 10; ; a++)
				{
					if (cypherTemp[a] == '}')
						break;
					else
						cypher.push_back(cypherTemp[a]);
				}
				decrypt(key, cypher);
			}
			else
			{
				cout << "Key is not for Replace" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Error. The document was not found" << endl << endl;
			system("pause");
			exit(0);
		}
	}
	void decrypt(string key, string cypher)
	{
		vector<int> keyA;
		string text;
		for (int a = 0; a < cypher.size(); a++)
			text.push_back(' ');
		string temp;
		int num;
		for (int a = 0; a < key.size(); a++)
		{
			if (key[a] == ',')
				continue;
			else
			{
				temp = key[a];
				num = stoi(temp);
				keyA.push_back(num);
			}
		}
		int tempT;
		for (int a = 0; a < cypher.size(); a++)
		{
			tempT = keyA[a];
			text[a] = cypher[tempT];
		}
		cout << "Enter path to save text" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(.+)""(.txt)");
		if (regex_search(path.c_str(), result, regular))
		{
			ofstream dock;
			dock.open(path, std::ios::app);
			if (dock.is_open())
			{
				dock << text;
			}
			else
			{
				cout << "Error. Wrong path" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			cout << "Use .txt document extension" << endl;
			system("pause");
			exit(0);
		}

	}
	void saveKey(vector<int> key, string text)
	{
		cout << "Enter path for save key in document" << endl;
		string path;
		cin >> path;
		cmatch result;
		regex regular("(\.)""(key)");
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .key document extension" << endl;
			system("pause");
			exit(0);
		}
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
		{
			cout << "Error. Cannot open this document" << endl;
			system("pause");
			exit(0);
		}
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
		regex regular("(\.)""(encrypt)");
		cmatch result;
		if (regex_search(path.c_str(), result, regular))
		{
			cout << "";
		}
		else
		{
			cout << "Use .encrypt document extension" << endl;
			system("pause");
			exit(0);
		}
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
		{
			cout << "Error. Cannot open this document" << endl;
			system("pause");
			exit(0);
		}
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

class crypt
{
public:
	void selectC(base & method, string text)
	{
		method.createKey(text);
	}
};
class decrypt
{
public:
	void selectD(base & method)
	{
		method.findText();
	}
};
int main()
{
	crypt cr;
	decrypt dcr;
	rePlace a;
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
			cout << "Choose the kind of crypt" << endl;
			cout << "1. Replacement" << endl;
			cout << "2. Gamming" << endl;
			cout << "3. Transposition" << endl;
			cin >> cho;
			if (cho == 1)
			{
				dcr.selectD(a);
			}
			else
			{
				cout << "Incorrect option" << endl;
				system("pause");
				break;
			}
		}
		else if (cho == 2)
		{
			cout << "Choose the kind of crypt" << endl;
			cout << "1. Replacement" << endl;
			cout << "2. Gamming" << endl;
			cout << "3. Transposition" << endl;
			string chos;
			cin >> chos;
			cmatch result;
			regex regular("([\\d])");
			if (regex_search(chos.c_str(), result, regular))
			{
				if (chos == "1")
				{
					cout << "Enter path of document with text: " << endl;
					string path;
					cin >> path;
					fstream text(path);
					string textDoc;
					if (text.is_open())
					{
						getline(text, textDoc);
						cr.selectC(a, textDoc);
					}
					else
					{
						cout << "Error. The document was not found" << endl << endl;
						system("pause");
						return 0;
					}
				}
				else if (chos == "2")
				{

				}
				else if (chos == "3")
				{

				}
				else
				{
					cout << "Incorrect option" << endl;
					system("pause");
					return 0;
				}
			}
			else
			{
				cout << "Incorrect option" << endl;
				system("pause");
				return 0;
			}
			
		}
		else
			return 0;
	}
}