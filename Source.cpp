#include <iostream>
#include <string>
#include <stdlib.h> 
#include <string>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <mmsystem.h>

using namespace std;

struct Node* morseTree;

/// Description: General Structure for Nodes that will be created later 
struct Node {
	string symbol;
	struct Node* left, * right;
};

/// Description: Method for creating nodes for Morse Code Binary Tree
/// Parameters: symbol which need to be assigned for new node
/// Returns: Created Node
Node* morseNode(string symbol)
{
	Node* temp = new Node;

	temp->symbol = symbol;
	temp->left = NULL;		//left = '.'
	temp->right = NULL;		//right = '-'

	return temp;
}

/// Description: Reads information from strings
/// Parameters:	path - path of file for reading
/// Returns: information from file
string Read(string path) {
	string data = "";
	string line;
	ifstream file;

	file.open(path);

	while (file)
	{
		if (getline(file, line))
		{
			if (line != "" && line != "\n")
			{
				data += line;
			}
		}
	}

	file.close();

	return data;
}

/// Description: Creates nodes in Binary Tree and assign to all of them required characters
void morseTreefiller()
{
	morseTree = morseNode("ROOT");		

	morseTree->left = morseNode("E");
	morseTree->right = morseNode("T");

	morseTree->left->left = morseNode("I");
	morseTree->left->right = morseNode("A");
	morseTree->right->left = morseNode("N");
	morseTree->right->right = morseNode("M");

	morseTree->left->left->left = morseNode("S");
	morseTree->left->left->right = morseNode("U");
	morseTree->left->right->left = morseNode("R");
	morseTree->left->right->right = morseNode("W");
	morseTree->right->left->left = morseNode("D");
	morseTree->right->left->right = morseNode("K");
	morseTree->right->right->left = morseNode("G");
	morseTree->right->right->right = morseNode("O");

	morseTree->left->left->left->left = morseNode("H");
	morseTree->left->left->left->right = morseNode("V");
	morseTree->left->left->right->left = morseNode("F");
	morseTree->left->left->right->right = morseNode("");
	morseTree->left->right->left->left = morseNode("L");
	morseTree->left->right->left->right = morseNode("");
	morseTree->left->right->right->left = morseNode("P");
	morseTree->left->right->right->right = morseNode("J");
	morseTree->right->left->left->left = morseNode("B");
	morseTree->right->left->left->right = morseNode("X");
	morseTree->right->left->right->left = morseNode("C");
	morseTree->right->left->right->right = morseNode("Y");
	morseTree->right->right->left->left = morseNode("Z");
	morseTree->right->right->left->right = morseNode("Q");
	morseTree->right->right->right->left = morseNode("");
	morseTree->right->right->right->right = morseNode("");
}

/// Description: Filters string taken from file and fills with it existing array of strings
/// Parameters: data - information passed from file; arr - storage for Morse Code; arraySize - current size of array
void parseString(string data, string* arr, int* arraySize)
{
	int index = 0;
	int arrayIndex = 0;
	int stringSize = data.length();
	string result = "";
	while (index < stringSize)
	{
		if (data.at(index) != '\0')
		{
			if (data.at(index) == '/')
			{
				arr[arrayIndex++] = "SPACE";
				index++;
				continue;
			}

			if (data.at(index) == '-' || data.at(index) == '.')
			{
				result = "";

				while (index < stringSize)
				{
					if (data.at(index) == '-')
					{
						result += "-";
						index++;
						continue;
					}
					else if (data.at(index) == '.')
					{
						result += ".";
						index++;
						continue;
					}
					else if (data.at(index) == ' ')
					{
						break;
					}
				}
				arr[arrayIndex++] = result;
				index++;
			}

			while (index < stringSize && data.at(index) == ' ' && data.at(index) != '\0') { index++; }
		}
	}
	*arraySize = arrayIndex;
}

/// Description: Method with recursion for traveling in Binary Tree, finding required nodes and making sound effects
/// Parameters: code - passed morse code; node - Morse Code Tree's root node
/// Returns: Symbol of reached Node 
string morseConverter(string code, Node* node)
{	
	for (int index = 0; index < code.length(); index++)
	{
		if (code.at(index) == '.')
		{
			PlaySound(TEXT("res/Sounds/dot.wav"), NULL, 0);
			node = node->left;
		}
		else if (code.at(index) == '-')
		{
			PlaySound(TEXT("res/Sounds/dash.wav"), NULL, 0);
			node = node->right;
		}
		else {
			cout << "Unknown element." << endl;
			break;
		}
	}	
	PlaySound(TEXT("res/Sounds/space.wav"), NULL, 0);

	cout << node->symbol;

	return node->symbol;
}

/// Description: Converts Morse Code stored in string array to general text and uses pause between words
/// Parameters: arr - storage for Morse Code; size - size of string array, node - Morse Code Tree's root node
void morse(string* arr, int size, Node* node)
{
	for (int index = 0; index < size; index++)
	{
		if (arr[index] == "SPACE")
		{
			arr[index] = " ";
			cout << " ";
			PlaySound(TEXT("res/Sounds/space.wav"), NULL, 0);
			PlaySound(TEXT("res/Sounds/space.wav"), NULL, 0);
		}
		else 
		{
			arr[index] = morseConverter(arr[index], morseTree);
		}

	}
}

/// Description: Main method with Menu with GUI and external methods' interaction between each other
void main()
{
	bool menu = true;
	int option = 0;
	int size = 0;
	string arr[100];
	string filesPath[5] = { "res/TextFiles/File1.txt", "res/TextFiles/File2.txt", "res/TextFiles/File3.txt", "res/TextFiles/File4.txt", "res/TextFiles/File5.txt" };
	string data = "";

	while (menu)
	{
		cout << "Please choose option for demonstraion:" << endl;
		cout << "1) Convert all 5 files." << endl;
		cout << "2) Convert File #1." << endl;
		cout << "3) Convert File #2." << endl;
		cout << "4) Convert File #3." << endl;
		cout << "5) Convert File #4." << endl;
		cout << "6) Convert File #5." << endl << endl;
		cout << "Enter any other characters to exit menu." << endl << endl;
		cout << "Option Number: ";

		cin >> option;

		cout << endl << endl;

		switch (option)
		{
			default:
				cout << endl << endl << "BYE! Exiting..." << endl;
				menu = false;
				break;

			case 1: 
				for (int index = 0; index < 5; index++, size = 0, data = "")
				{
					data = Read(filesPath[index]);
					cout << "Data of File " << index + 1 << ":  " << data << endl;
					cout << "Converting File " << index + 1 << " from Morse Code: ";

					morseTreefiller();
					parseString(data, arr, &size);
					morse(arr, size, morseTree);
					cout << endl << endl;
				}
				break;

			case 2:
				data = Read(filesPath[0]);
				cout << "Data of File 1:  " << data << endl;
				cout << "Converting File 1 from Morse Code: ";

				morseTreefiller();
				parseString(data, arr, &size);
				morse(arr, size, morseTree);
				cout << endl << endl;
				break;

			case 3:
				data = Read(filesPath[1]);
				cout << "Data of File 2:  " << data << endl;
				cout << "Converting File 2 from Morse Code: ";

				morseTreefiller();
				parseString(data, arr, &size);
				morse(arr, size, morseTree);
				cout << endl << endl;
				break;

			case 4:
				data = Read(filesPath[2]);
				cout << "Data of File 3:  " << data << endl;
				cout << "Converting File 3 from Morse Code: ";

				morseTreefiller();
				parseString(data, arr, &size);
				morse(arr, size, morseTree);
				cout << endl << endl;
				break;

			case 5:
				data = Read(filesPath[3]);
				cout << "Data of File 4:  " << data << endl;
				cout << "Converting File 4 from Morse Code: ";

				morseTreefiller();
				parseString(data, arr, &size);
				morse(arr, size, morseTree);
				cout << endl << endl;
				break;

			case 6:
				data = Read(filesPath[4]);
				cout << "Data of File 5:  " << data << endl;
				cout << "Converting File 5 from Morse Code: ";

				morseTreefiller();
				parseString(data, arr, &size);
				morse(arr, size, morseTree);
				cout << endl << endl;
				break;
		}
	}	
}
