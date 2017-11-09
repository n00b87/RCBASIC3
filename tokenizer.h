
#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "rc_utility.h"
#include "rc_debug.h"
#include "keywords.h"

using namespace std;

vector<string> token; //stores tokens for the current source line
bool tokens(const std::string &data); //reads current source line and fills token vector
int inc(string::size_type &, int); //returns the current position being read on the current source line
int iswhite(int); //returns whether the current character is a whitespace
bool isLetter(char c); //returns whether or not the current character is a letter
bool isDigit(char ch); //returns whether or not the current character is a digit
bool isOperatorToken(int token_index); //returns whether or not the token at the given index is an operator
void output_tokens(); //outputs the last set of tokens generated
bool isKeyWord(string key);
void clearTokens();

bool isOperatorToken(int token_index)
{
    int x = token_index;

    if(x < 0)
        return false;

    if(token[x].compare("<add>")==0 || token[x].compare("<sub>")==0 ||
       token[x].compare("<mul>")==0 || token[x].compare("<div>")==0 ||
       token[x].compare("<mod>")==0 || token[x].compare("<pow>")==0 ||
       token[x].compare("<equal>")==0 || token[x].compare("<greater>")==0 ||
       token[x].compare("<less>")==0 || token[x].compare("<greater_equal>")==0 ||
       token[x].compare("<less_equal")==0 || token[x].compare("<not_equal>")==0 ||
       token[x].compare("<not>")==0 || token[x].compare("<and>")==0 ||
       token[x].compare("<or>")==0 || token[x].compare("<xor>")==0)
       {
           return true;
       }

    return false;
}

bool isSubDelimToken(int token_index)
{
    if(token_index < 0)
        return false;

    if(token[token_index].compare("<par>")==0 ||
       token[token_index].compare("<square>")==0 ||
       token[token_index].compare("<curly>")==0 ||
       token[token_index].compare("<comma>")==0)
        return true;
    return false;
}

bool tokens(const std::string &data)
{
    string::size_type x = 0;

    while(x < data.length())
    {
        char ch = data[x];

        //s_data will hold a number or identifier
        string s_data = "";

        while(isspace(ch))
           ch = data[inc(x, 1)];

        switch(ch)
        {
            case '+':
                inc(x, 1);
                token.push_back("<add>");
                break;
            case '-':
                if(isOperatorToken(token.size()-1) || isSubDelimToken(token.size()-1) || token.size()==0)
                {
                    ch = data[inc(x, 1)];
                    if (isdigit(ch))
                    {
                        s_data = "<num>-";
                        do
                        {
                            s_data.push_back(ch);
                            ch = data[inc(x, 1)];
                        } while(isdigit(ch) || ch == '.');

                        token.push_back(s_data);
                    }
                    else if (isalpha(ch) || ch == '_')
                    {
                        //s_data = "<id>";
                        do
                        {
                            s_data.push_back(ch);
                            ch = data[inc(x, 1)];
                        } while(isalnum(ch) || ch == '_');

                        if(isKeyWord(StringToUpper(s_data)))
                        {
                            //s_data  = "<"+s_data+">";
                            //keyword = s_data;
                            rc_setError("Invalid Syntax: Can't use Keyword " + s_data + " in this operation");
                            return false;
                        }
                        else
                        {
                            s_data = "<id>"+s_data;

                            token.push_back("<par>");
                            token.push_back("<num>-1");
                            token.push_back("<mul>");
                            token.push_back(s_data);
                            token.push_back("</par>");
                        }
                    }
                }
                else
                {
                    inc(x, 1);
                    token.push_back("<sub>");
                }
                break;
            case '*':
                inc(x, 1);
                token.push_back("<mul>");
                break;
            case '/':
                inc(x, 1);
                token.push_back("<div>");
                break;
            case '%':
                inc(x, 1);
                token.push_back("<mod>");
                break;
            case '^':
                inc(x, 1);
                token.push_back("<pow>");
                break;
            case '(':
                inc(x, 1);
                token.push_back("<par>");
                break;
            case ')':
                inc(x, 1);
                token.push_back("</par>");
                break;
            //case '.':
              //  inc(x, 1);
                //token.push_back("<dot>");
                //break;
            case ',':
                inc(x, 1);
                token.push_back("<comma>");
                break;
            case '=':
                inc(x, 1);
                token.push_back("<equal>");
                break;
            case '>':
                ch = data[x+1];
                if(ch == '=')
                {
                    inc(x, 2);
                    token.push_back("<greater_equal>");
                }
                else
                {
                    inc(x, 1);
                    token.push_back("<greater>");
                }
                break;
             case '<':
                ch = data[x+1];
                if (ch == '=')
                {
                    inc(x, 2);
                    token.push_back("<less_equal>");
                }
                else if (ch == '>')
                {
                    inc(x, 2);
                    token.push_back("<not_equal>");
                }
                else
                {
                    inc(x, 1);
                    token.push_back("<less>");
                }
                break;
            case '{':
                inc(x, 1);
                token.push_back("<curly>");
                break;
            case '}':
                inc(x, 1);
                token.push_back("</curly>");
                break;
            case '[':
                inc(x, 1);
                token.push_back("<square>");
                break;
            case ']':
                inc(x, 1);
                token.push_back("</square>");
                break;
            case '\"':
                s_data = "<string>";
                ch = data[inc(x, 1)];
                while(ch != '\"' && ch != '\r' && ch != '\n')
                {
                    s_data.push_back(ch);
                    ch = data[inc(x, 1)];
                }
                if (ch == '\"')
                    token.push_back(s_data);
                else
                {
                    rc_setError("String was not closed before end of line");
                    return false;
                }
                inc(x, 1);
                break;
            default:
                 if (isdigit(ch))
                {
                    s_data = "<num>";
                    do
                    {
                        s_data.push_back(ch);
                        ch = data[inc(x, 1)];
                    } while(isdigit(ch) || ch == '.');

                    token.push_back(s_data);
                }
                else if (isalpha(ch) || ch == '_')
                {
                    //s_data = "<id>";
                    do
                    {
                        s_data.push_back(ch);
                        ch = data[inc(x, 1)];
                    } while(isalnum(ch) || ch == '_' || ch == '$' || ch == '.');

                    if(isKeyWord(StringToUpper(s_data)))
                    {
                        s_data  = "<"+StringToLower(s_data)+">";
                        //keyword = s_data;
                    }
                    else
                    {
                        s_data = "<id>"+s_data;
                    }
                    token.push_back(s_data);
                }
                else if(ch == '~')
                {
                    ch = data[inc(x,1)];
                    do
                    {
                        s_data.push_back(ch);
                        ch = data[inc(x,1)];
                    } while(isdigit(ch));
                    token.push_back(s_data);
                }
                else if(x==data.length())
                {
                    break;
                }
                else
                {
                    cout << "illegal character found" << endl;
                    return false;
                }
                break;
        }
    }

    return true;
}

int inc(string::size_type &x, int by)
{
    return x = x + by;
}

int iswhite(int c)
{
    return (c == ' ' || c == '\t');
}

bool isLetter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isDigit(char c)
{
    return (c >= '0' && c <= '9');
}

bool isKeyWord(string key)
{
    int len = sizeof(keyWords)/sizeof(keyWords[0]);
    int i;
    for(i = 0; i < len; i++)
    {
        if(key == keyWords[i])
        {
            return true;
        }
    }
    return false;
}

void output_tokens()
{
    for(int i = 0; i < token.size(); i++)
    {
        try
        {
            cout << token.at(i) << endl;
        }
        catch(out_of_range& e)
        {
            cout << "Token Out of Range Error: " << e.what() << endl;
        }
    }
}

void clearTokens()
{
    token.clear();
}

#endif // TOKENIZER_H_INCLUDED
