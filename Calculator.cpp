#include <iostream>
#include <fstream>
//#include <sstream>
using namespace std;

string inputString(string text);
ofstream openFile(string fileName);

void generatePreamble();

void fillArray(int array[201], int max);
void generateIf(char sign, int a, int b);
void generateOperations(char (&signs)[4], int (&aarray)[201], int (&barray)[201]);

char signs[4]{'+', '-', '*', '/'};

const string tS = "   ";

ofstream file;

int main(int argc, char *argv[]) {
	
	//Parameters and setting everything up:
	cout << "Welcome to the calculator generating program. Enter a file name for the calculator .cpp to continue\n"
		 << "WARNING: The generated .cpp might be a large file\n\n"
		 << "ANOTHER WARNING!!!: the program will take a little while after giving it a file name. BE PATIENT!\n\n";
	string fileName = inputString("File name:");		//Get input and store in a string
	file = openFile(fileName);							//Generate file and open it
	
	generatePreamble();
	
	int max = 201;
	int aarray[201];
	int barray[201];
	
	//Fill arrays. Signs array is already filled (when it was declared outside main())
	fillArray(aarray, max);
	fillArray(barray, max);
	
	generateOperations(signs, aarray, barray);	//This baby here does the magic

	file << tS << "return 0;" << endl << "}";
	
	return 0;
}

string inputString(string text)
{
	cout << text + '\n';
	cin >> text;
	return text;
}

ofstream openFile(string fileName)
{
	ofstream file;
	file.open(fileName + ".cpp");
	file << "//GENERATED FILE. File name: " + fileName + ".cpp\n" << "//ADVANCED CALCULATOR MADE BY ELMENDUKO\n";
	file << "//Free software! For extra annoyance: in case you didn't notice, this file uses 3 spaces for indentation\n";

	return file;
}

void generatePreamble()
{
	file << "#include <iostream>\n" << "using namespace std;\n\n";	//#includes and namespaces
	
	//A function for inputting an int:
	file << "int inputInt(string text)\n" << "{\n" << tS << "cout << text" << " << endl;\n" << tS << "int input;" <<
		"\n" << tS << "cin >> input;\n" << tS << "return input;" << endl << "}" << endl << endl;
	
	//A function for inputting a char:
	file << "char inputChar(string text)\n" << "{\n" << tS << "cout << text" << " << endl;\n" << tS << "char input;" <<
		"\n" << tS << "cin >> input;\n" << tS << "return input;" << endl << "}" << endl << endl;
	
	//int main():
	file << "int main (int argc, char *argv[]) {" << endl << tS << "int a = inputInt(\"Enter an integer between 0 and 100: \");" << endl 
		 << tS << "int b = inputInt(\"Enter another integer between 0 and 100: \");" << endl << tS << 
		 "char sign = inputChar(\"What operation? +, -, *, or /? \");" << endl << endl;
	
	
}

void fillArray(int array[201], int max)
{
	for(int i = 0; i <= max; i++)
	{
		array[i] = i;
	}
}

void generateIf(char sign, int a, int b)
{
	/*stringstream ss;
	ss << sign;
	string signString;
	ss >> signString;
	signString = "\"" + signString + "\"";*/
	
	double result;
	if(sign == '+')
	{
		result = a + b;
	}else if(sign == '-')
	{
		result = a - b;
	}else if(sign == '*')
	{
		result = a * b;
	}else if(sign == '/' && b != 0)
	{
		result = a / b;
	}else
	{
		result = -1;
	}
	
	string resultString = to_string(result);
	
	file << tS + "if((sign == \'" + string(1, sign) + "\') && (a == " + to_string(a) + ") && (b == " + to_string(b) + "))" + "\n";
	file << tS + "{" << "\n";
	file << tS + tS + "cout << \"result = \" << " + resultString + ";\n";
	file << tS + "}" << "\n";
}

void generateOperations(char (&signs)[4], int (&aarray)[201], int (&barray)[201])
{
	for(auto sign : signs)
	{
		for(auto a : aarray)
		{
			for(auto b : barray)
			{
				generateIf(sign, a, b);
				cout << a << " " << string(1, sign) << " " << b << "\n";
			}
		}
	}
}
