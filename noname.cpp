#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <queue>
 
using namespace std; 

void keyWordNum(ifstream &infile, int &ans);

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
	
	
	ifstream infile;
	infile.open(location, ios::in);
	if(!infile)
	{
		cerr<<"error:unable to open input file"<<endl;
	}
	int ans;
	keyWordNum(infile, ans);
	cout<<ans<<endl;
	return 0;
}


//��ȡ������Ϣ�ж��ж��ٹؼ��� 
void keyWordNum(ifstream &infile, int &ans)
{
	string str;
	ans = 0;
	if(infile.is_open())
	{
		while(infile>>str)
		{
			cout<<str<<endl;
			for(int i = 0; i < 32; i++)
			{
				if(str == keyWords[i])
				{
					ans++;
					break;						
				}
			}
		}
	}	
} 



