
#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include "rc_utility.h"
#include "keywords.h"
#include "constants.h"

using namespace std;

vector<string> token; //stores tokens for the current source line
vector<string> tmp_token; //stores tokens for the current source line
string rc_keywordToken(string sline);
bool isKeyWord(string key);
bool tokens(const std::string &data); //reads current source line and fills token vector
int inc(string::size_type &, int); //returns the current position being read on the current source line
int iswhite(int); //returns whether the current character is a whitespace
bool isLetter(char c); //returns whether or not the current character is a letter
bool isDigit(char ch); //returns whether or not the current character is a digit
bool isOperatorToken(int token_index); //returns whether or not the token at the given index is an operator
void output_tokens(); //outputs the last set of tokens generated
void clearTokens();
bool multi_line_comment=false;

bool isOperatorToken(int token_index)
{
    int x = token_index;

    if(x < 0)
        return false;

    if(tmp_token[x].compare("<add>")==0 || tmp_token[x].compare("<sub>")==0 ||
       tmp_token[x].compare("<mul>")==0 || tmp_token[x].compare("<div>")==0 ||
       tmp_token[x].compare("<mod>")==0 || tmp_token[x].compare("<pow>")==0 ||
       tmp_token[x].compare("<equal>")==0 || tmp_token[x].compare("<greater>")==0 ||
       tmp_token[x].compare("<less>")==0 || tmp_token[x].compare("<greater_equal>")==0 ||
       tmp_token[x].compare("<less_equal>")==0 || tmp_token[x].compare("<not_equal>")==0 ||
       tmp_token[x].compare("<not>")==0 || tmp_token[x].compare("<and>")==0 ||
       tmp_token[x].compare("<or>")==0 || tmp_token[x].compare("<xor>")==0)
       {
           return true;
       }

    return false;
}

bool isSubDelimToken(int token_index)
{
    if(token_index < 0)
        return false;

    if(tmp_token[token_index].compare("<par>")==0 ||
       tmp_token[token_index].compare("<square>")==0 ||
       tmp_token[token_index].compare("<curly>")==0 ||
       tmp_token[token_index].compare("<comma>")==0 ||
       tmp_token[token_index].compare("!<par>")==0 ||
       tmp_token[token_index].compare("!<square>")==0 ||
       tmp_token[token_index].compare("!<curly>")==0 ||
       tmp_token[token_index].compare("!<comma>")==0)
        return true;

    string t = tmp_token[token_index].substr(1);
    t = t.substr(0, t.find_first_of(">"));
    if(isKeyWord(StringToUpper(t)))
        return true;

    return false;
}

bool tokens(const std::string &data)
{
    string::size_type x = 0;
    bool esc_char = false;

    string arg_data = "";
    int arg_data_scope = 0;

    if(multi_line_comment)
    {
        x = data.find("'/");
        if(x == string::npos)
            return true;

        multi_line_comment = false;
        x += 2;
    }

    while(x < data.length())
    {
        char ch = data[x];

        //s_data will hold a number or identifier
        string s_data = "";
        string rc_builtin_constant = "";

        while(isspace(ch))
           ch = data[inc(x, 1)];

        switch(ch)
        {
            case ':':
                inc(x, 1);
                tmp_token.push_back("<:>");
                break;
            case '.':
                inc(x, 1);
                tmp_token.push_back("<child>");
                break;
            case '+':
                inc(x, 1);
                tmp_token.push_back("<add>");
                break;
            case '-':
                if(isOperatorToken(tmp_token.size()-1) || isSubDelimToken(tmp_token.size()-1) || tmp_token.size()==0)
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

                        tmp_token.push_back(s_data);
                    }
                    else if (isalpha(ch) || ch == '_')
                    {
                        //s_data = "<id>";
                        do
                        {
                            s_data.push_back(ch);
                            ch = data[inc(x, 1)];
                        } while(isalnum(ch) || ch == '_');

                        if(ch=='(')
                        {
                            arg_data = "";
                            arg_data_scope = 0;
                            do
                            {
                                arg_data.push_back(ch);

                                if(ch=='(')
                                    arg_data_scope++;
                                else if(ch==')')
                                    arg_data_scope--;

                                ch = data[inc(x, 1)];

                            } while(arg_data_scope > 0 && x < data.length());
                        }
                        else if(ch=='[')
                        {
                            arg_data = "";
                            arg_data_scope = 0;
                            do
                            {
                                arg_data.push_back(ch);

                                if(ch=='[')
                                    arg_data_scope++;
                                else if(ch==']')
                                    arg_data_scope--;

                                ch = data[inc(x, 1)];

                            } while(arg_data_scope > 0 && x < data.length());
                        }

                        if(isKeyWord(StringToUpper(s_data)))
                        {
                            //s_data  = "<"+s_data+">";
                            //keyword = s_data;
                            //rc_setError("Invalid Syntax: Can't use Keyword " + s_data + " in this operation");
                            return false;
                        }
                        else
                        {
                            s_data = "<id>"+s_data;

                            tmp_token.push_back("<par>");
                            tmp_token.push_back("<num>-1");
                            tmp_token.push_back("<mul>");
                            tmp_token.push_back(s_data);
                            if(arg_data.compare("")!=0)
                                tokens(arg_data);
                            tmp_token.push_back("</par>");
                        }
                    }
                    else
                    {
                        //rc_setError("Invalid Syntax: Missing a number or variable to negate");
                        return false;
                    }
                }
                else
                {
                    inc(x, 1);
                    tmp_token.push_back("<sub>");
                }
                break;
            case '*':
                inc(x, 1);
                tmp_token.push_back("<mul>");
                break;
            case '/':
                ch = data[x+1];
                if(ch == '\'')
                {
                    //start multi-line comment
                    multi_line_comment = true;
                    size_t end_comment = data.substr(x+2).find("'/");
                    if(end_comment == string::npos)
                    {
                        return true;
                    }
                    else
                    {
                        x += end_comment+4;
                        //cout << "data[" << x << "] = " << data[x] << endl;
                        multi_line_comment = false;
                    }
                }
                else
                {
                    inc(x, 1);
                    tmp_token.push_back("<div>");
                }
                break;
            case '%':
                inc(x, 1);
                tmp_token.push_back("<mod>");
                break;
            case '^':
                inc(x, 1);
                tmp_token.push_back("<pow>");
                break;
            case '(':
                inc(x, 1);
                tmp_token.push_back("<par>");
                break;
            case ')':
                inc(x, 1);
                tmp_token.push_back("</par>");
                break;
            //case '.':
              //  inc(x, 1);
                //token.push_back("<dot>");
                //break;
            case ',':
                inc(x, 1);
                tmp_token.push_back("<comma>");
                break;
            case ';':
                inc(x, 1);
                tmp_token.push_back("<semi>");
                break;
            case '=':
                inc(x, 1);
                tmp_token.push_back("<equal>");
                break;
            case '>':
                ch = data[x+1];
                if(ch == '=')
                {
                    inc(x, 2);
                    tmp_token.push_back("<greater_equal>");
                }
                else
                {
                    inc(x, 1);
                    tmp_token.push_back("<greater>");
                }
                break;
             case '<':
                ch = data[x+1];
                if (ch == '=')
                {
                    inc(x, 2);
                    tmp_token.push_back("<less_equal>");
                }
                else if (ch == '>')
                {
                    inc(x, 2);
                    tmp_token.push_back("<not_equal>");
                }
                else
                {
                    inc(x, 1);
                    tmp_token.push_back("<less>");
                }
                break;
            case '{':
                inc(x, 1);
                tmp_token.push_back("<curly>");
                break;
            case '}':
                inc(x, 1);
                tmp_token.push_back("</curly>");
                break;
            case '[':
                inc(x, 1);
                tmp_token.push_back("<square>");
                break;
            case ']':
                inc(x, 1);
                tmp_token.push_back("</square>");
                break;
            case '\'':
                return true;
                break;
            case '\"':
                s_data = "<string>";
                ch = data[inc(x, 1)];
                while(ch != '\"' && ch != '\r' && ch != '\n' && ch != '\0')
                {
                    if(ch == '\\')
                    {
                        esc_char = true;
                    }
                    if(esc_char)
                    {
                        ch = data[inc(x,1)];
                        if(ch == '\\')
                            s_data.push_back('\\');
                        else if(ch == '\"' || ch == 'q')
                            s_data.push_back('\"');
                        else if(ch == '\'')
                            s_data.push_back('\'');
                        else if(ch == 'n')
                            s_data.push_back('\n');
                        else if(ch == 'r')
                            s_data.push_back('\r');
                        else if(ch == 't')
                            s_data.push_back('\t');
                        else if(ch == '0')
                            s_data.push_back('\0');
                        else if(ch == 'b')
                            s_data.push_back('\b');
                        else if(ch == 'a')
                            s_data.push_back('\a');
                        else if(ch == 'v')
                            s_data.push_back('\v');
                        else if(ch == 'f')
                            s_data.push_back('\f');
                        else
                        {
                            cout << "Invalid escape sequence in string expression: \\" << ch << endl;
                            return false;
                        }
                        esc_char = false;
                        ch = data[inc(x,1)];
                    }
                    else
                    {
                        s_data.push_back(ch);
                        ch = data[inc(x, 1)];
                    }
                }
                if (ch == '\"')
                    tmp_token.push_back(s_data);
                else
                {
                    //rc_setError("String was not closed before end of line");
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

                    tmp_token.push_back(s_data);
                }
                else if (isalpha(ch) || ch == '_')
                {
                    //s_data = "<id>";
                    do
                    {
                        s_data.push_back(ch);
                        ch = data[inc(x, 1)];
                    } while(isalnum(ch) || ch == '_' || ch == '$' );//|| ch == '.');

                    rc_builtin_constant = rc_keywordToken(StringToUpper(s_data));

                    string kw_s_data = StringToUpper(s_data);
                    if(isKeyWord(kw_s_data))
                    {
                        s_data  = "<"+StringToLower(kw_s_data.compare("SUB")==0 ? "subp" : s_data)+">";
                        //keyword = s_data;
                    }
                    else if(rc_builtin_constant.compare("")!=0)
                    {
                        s_data = rc_builtin_constant;
                        rc_builtin_constant = "";
                    }
                    else
                    {
                        s_data = "<id>"+s_data;
                    }

                    if(s_data.compare("<user_const>")!=0)
                        tmp_token.push_back(s_data);
                }
                else if(ch == '~')
                {
                    ch = data[inc(x,1)];
                    do
                    {
                        s_data.push_back(ch);
                        ch = data[inc(x,1)];
                    } while(isdigit(ch));
                    tmp_token.push_back(s_data);
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

string rc_keywordToken(string sline)
{
    return "";
}

void output_tokens()
{
    for(int i = 0; i < tmp_token.size(); i++)
    {
        try
        {
            cout << i << ":" << tmp_token.at(i) << endl;
        }
        catch(out_of_range& e)
        {
            cout << "Token Out of Range Error: " << e.what() << endl;
        }
    }
}

void clearTokens()
{
    tmp_token.clear();
    token.clear();
}

#endif // TOKENIZER_H_INCLUDED
