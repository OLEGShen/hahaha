#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <fstream>

using namespace std; 

const string keyWords[32] = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "double", "else", "enum", "extern", "float",
	"for", "goto", "if", "int", "long", "register", "return",
	"short", "signed", "sizeof", "static", "struct", "switch",
	"typedef", "union", "unsigned", "void", "volatile", "while"
};

int main(){
	string location;
	int rank;
	cout<<"�����ļ���ָ��λ��";
	cin>>location;
	cout<<"����Ҫ�ĵȼ�";
	cin>>rank;
	
	string str;
	ifstream infile;
	infile.open(location, ios::in);
	if(infile.is_open())
	{
		while(!infile.eof())
		{
			getline(infile, str);
			cout<<str<<endl;
		}
	}
	return 0;
}



