//lab2: to count the keywords of C/C++ file
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <queue>
#include <ctype.h>
#include <vector>
using namespace std; 

//keywords
const string keyWords[32] = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "double", "else", "enum", "extern", "float",
	"for", "goto", "if", "int", "long", "register", "return",
	"short", "signed", "sizeof", "static", "struct", "switch",
	"typedef", "union", "unsigned", "void", "volatile", "while"
};


//enters the integer for counting the num of keyWords and the word to judge and the vector to save keywords
//the keywordNum and words are the paramters being used in the next operation 
//the function is used to judge whether the word is keyword 
//if it is keyword,it will be add to words and keywordnum will be add 1
//no return but keywordnum and words will be changed
void isKeyWords(string word, int &keyWordNum ,vector<string> &words)
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


//Enter the contents of each line as a string
// Handles special cases in strings:// "" and delete them 
//used for processing each line of the file
//return the string after deleting
string getRightString(string str)
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

//enter the fstream of C file, the num of keywords and the vector of keywords
//for rank 1 : count the num of keywords
//Each line is iterated, adding the keywords to the vector and counting
//no return but the ans and words are be quoted ,they are the target of function processing
void keyWordNum(ifstream &infile, int &ans, vector<string> &words) 
{
	string str;
	ans = 0;
	int len = 0;
		
	if(infile.is_open())
	{
		bool isLine = true;
		while(getline(infile, str))//ï¿½Ãµï¿½Ò»ï¿½ï¿½ 
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


//enter the keywords vector
//to count the num of switch and case and display result
//no return
//before this func we need do keyWordNum function
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

//enter the keyword of if else else-if, the stack, the num of else if and if else;
//the stack and two int are quated in this function;
//check if the word is if/else/else if to stack in/out and count the num;
//no return but the target is int &elseIfNum, int &ifElseNum;
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


//get every if else and {} in the stack to count the if-else/if-elseif-else num;
void ifNums(ifstream &infile, int &ifElseNum, int &elseIfNum)
{
	string str;
	int len = 0;
	stack<string> ifElseWords;
	if(infile.is_open())
	{
		bool isLine = true;
		bool isIf = false;
		while(getline(infile, str))//ï¿½Ãµï¿½Ò»ï¿½ï¿½ 
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
							else if(str[i + 1] > 'z' || str[i + 1] < 'a')
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
	cout<<"ÊäÈëµØÖ·: ";
	cin>>location;
	cout<<"rank: ";
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
