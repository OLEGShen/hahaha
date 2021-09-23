#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <queue>
#include <ctype.h>
#include <vector>
using namespace std; 

const string keyWords[32] = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "double", "else", "enum", "extern", "float",
	"for", "goto", "if", "int", "long", "register", "return",
	"short", "signed", "sizeof", "static", "struct", "switch",
	"typedef", "union", "unsigned", "void", "volatile", "while"
};

void isKeyWords(string word, int &keyWordNum ,vector<string> &words)//简单的单词匹配 
{
	for(int i = 0; i < 32; i++)
	{
		if(keyWords[i] == word)
		{
			keyWordNum++;
			words.push_back(word);
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
		}
	
	}
	return ans;
}

void keyWordNum(ifstream &infile, int &ans, vector<string> &words)//第一环节:计算数量 
{
	string str;
	ans = 0;
	int len = 0;
		
	if(infile.is_open())
	{
		bool isLine = true;
		while(getline(infile, str))//得到一行 
		{	
			str = getRightString(str);	
			len = str.length();
			int wordBegin = 0;
			int wordEnd = 0;
			bool isLetter = false;
			string word;
			str = getRightString(str);
			for(int i = 0; i < len; i++)
			{
				if(isLine)
				{
					if(str[i] == '/' && str[i + 1] == '*')
					{
						isLine = false;
						i++;
						continue;
					}
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
								isKeyWords(word, ans, words);
							}
						}
					}
					else if(isLetter)
					{
						isLetter = false;
						wordEnd = i;
						word = str.substr(wordBegin, wordEnd - wordBegin);
						isKeyWords(word, ans, words);
					}
				}
				else
				{
					if(str[i] == '*' && str[i + 1] == '/')
					{
						isLine = true;
						i++;
					}	
				}	
			}	
		}
	}
}

void switchCaseNum(vector<string> A)
{
	int ansA = 0;
	vector<int> ansB;
	int temp;
	int len = A.size();
	bool isIn = false;
	for(int i = 0; i < len; i++)
	{
		if(A[i] == "switch" && !isIn)
		{
			ansA ++;
			isIn = true;
		}
		if(isIn)
		{
			if(A[i] == "case")
			{
				temp++;
			}
			if(A[i] == "default")
			{
				ansB.push_back(temp);
				temp = 0;
				isIn = false;
			}
		}
	}
	cout<<"switch num: "<<ansA<<endl;
	cout<<"case num: ";
	for(int i =0; i < ansB.size(); i++)
	{
		cout<<ansB[i]<<" ";
	}
	cout<<endl;
}

void wordForIf(stack<string> &ifElseWords,string word, int &elseIfNum, int &ifElseNum)
{
	if(word == "if")
	{
		ifElseWords.push(word);
	}
	else if(word == "else")
	{
		if(ifElseWords.top() == "if")
		{
			ifElseWords.pop();
			ifElseNum ++;
		}
		else if(ifElseWords.top() == "else if")
		{
			ifElseWords.pop();
			ifElseWords.pop();
			elseIfNum++;
		}
	}
	else if(word == "else if")
	{
		if(ifElseWords.top() == "else if")
		{
		}
		else 
		{
			
			ifElseWords.push(word);
		}
	}
}

void ifNums(ifstream &infile, int &ifElseNum, int &elseIfNum)
{
	string str;
	int len = 0;
	stack<string> ifElseWords;
	if(infile.is_open())
	{
		bool isLine = true;
		bool isIf = false;
		while(getline(infile, str))//得到一行 
		{	
			str = getRightString(str);	
			len = str.length();
			int wordBegin = 0;
			int wordEnd = 0;
			bool isLetter = false;
			string word;
			str = getRightString(str);
			for(int i = 0; i < len; i++)
			{
				if(isLine)
				{
					if(str[i] == '/' && str[i + 1] == '*')
					{
						isLine = false;
						i++;
						continue;
					}
					if(ifElseWords.size() != 0)
					{
						if(str[i] == '{')
						{
							string tempStr;
							tempStr.push_back(str[i]);
							
							ifElseWords.push(tempStr);
							continue;
						}
						else if(str[i] == '}')
						{
							string tempStr;
							tempStr.push_back(str[i]);
							if(ifElseWords.top() == "{")
							{
								ifElseWords.pop();
								continue;
							}
							else 
							{
								ifElseWords.push(tempStr);
							}
								
						}
					}
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
								wordForIf(ifElseWords, word, elseIfNum, ifElseNum);
							}
							if(str[i + 1] > 'z' || str[i + 1] < 'a')
							{
								isLetter = false;
								wordEnd = i + 1;
								word = str.substr(wordBegin, wordEnd - wordBegin);
								if (word == "else")
								{
									
									if(i + 2 < len)
									{
										if(str[i + 2] =='i' && str[i + 3] == 'f')
										{
											word = "else if";
											
											i += 3;
										}
									}	
								}
								wordForIf(ifElseWords, word, elseIfNum, ifElseNum);
								
							}
						}
					}
				}
				else
				{
					if(str[i] == '*' && str[i + 1] == '/')
					{
						isLine = true;
						i++;
					}	
				}
//				cout<<"dfwef    ";	
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
	vector<string> words;
	keyWordNum(infile, ans,words);
	infile.close();
	
	if(rank >=1)
		cout<<"total num: "<<ans<<endl;
	if(rank >=2)
		switchCaseNum(words);
	int ifElseNum = 0, elseIfNum = 0;
	if(rank >= 3)
	{
		ifstream file;
		file.open(location, ios::in);
		if(!file)
		{
			cerr<<"error:unable to open input file"<<endl;
		}
		
		ifNums(file, ifElseNum, elseIfNum);
		cout<<"if-else num: "<<ifElseNum<<endl;
	}
	if(rank >= 4)
	{
		cout<<"if-elseif-else num:"<<elseIfNum<<endl;
	}
	return 0;
}
