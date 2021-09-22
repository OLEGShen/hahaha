#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <queue>
#include <ctype.h>
using namespace std; 

const string keyWords[32] = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "double", "else", "enum", "extern", "float",
	"for", "goto", "if", "int", "long", "register", "return",
	"short", "signed", "sizeof", "static", "struct", "switch",
	"typedef", "union", "unsigned", "void", "volatile", "while"
};

void isKeyWords(string word, int &keyWordNum)//简单的单词匹配 
{
	for(int i = 0; i < 32; i++)
	{
		if(keyWords[i] == word)
		{
			keyWordNum++;
			cout<<word<<endl;
			break;
		}
	}
}

string getRightString(string str)//处理字符串中的特殊情况：// “” /**/
{
	string ans;
	int isit = 0;
	int len = str.length();
	for(int i =0; i < len; i++)
	{
		if(isit == 0)
		{
			if(str[i] == '"')
			{
				isit = 1;
				continue;
			}
			else if(str[i] == '/' && str[i + 1] == '*')
			{
				isit = 2;
				i++;
				continue;
			}
			else if(str[i] == str[i + 1] && str[i] == '/')
			{
				break;
			}
			else
			{
				ans.push_back(str[i]);
			}
		}
		else if(isit != 0)
		{
			if(str[i] == '"' && isit == 1)
			{
				isit = 0;
			}
			else if(isit == 2)
			{
				if(str[i] == '*' && str[i + 1] == '/')
				{
					isit = 0;
					i++;
				}
			}
		}
	
	}
	return ans;
}

void keyWordNum(ifstream &infile, int &ans)//计算单词数量也就是第一环节 
{
	string str;
	ans = 0;
	
	int len = 0;
	
	if(infile.is_open())
	{
		while(getline(infile, str))//得到一行 
		{	
			str = getRightString(str);	
			len = str.length();
			int wordBegin = 0;
			int wordEnd = 0;
			bool isLetter = false;
			string word;
			for(int i = 0; i < len; i++)
			{
				if(str[i] <= 'z' && str[i] >= 'a')
				{
					if(!isLetter)
					{
						isLetter = true;
						wordBegin = i;
					}
					else 
					{
						if(i + 1 == len)
						{
							wordEnd = i + 1; 
							word = str.substr(wordBegin, wordEnd - wordBegin);
							isKeyWords(word, ans);
						}
					}
				}
				else if(isLetter)
				{
					isLetter = false;
					wordEnd = i;
					word = str.substr(wordBegin, wordEnd - wordBegin);
					isKeyWords(word, ans);
				}
			}	
		}
	}
}

int main(){
	string location;
	int rank;
	cout<<"输入文件的指定位置";
	cin>>location;
	cout<<"你想要的等级";
	cin>>rank;
	
	
	ifstream infile;
	infile.open(location, ios::in);
	if(!infile)
	{
		cerr<<"error:unable to open input file"<<endl;
	}
	int ans;
	keyWordNum(infile, ans);
	cout<<"total num: "<<ans<<endl;
	return 0;
}


//读取所有信息判断有多少关键字 


 


