
#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <SDL2/SDL.h>
#include "rc_utility.h"
#include "rc_debug.h"
#include "keywords.h"

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
                            rc_setError("Invalid Syntax: Can't use Keyword " + s_data + " in this operation");
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
                        rc_setError("Invalid Syntax: Missing a number or variable to negate");
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
    if(sline.compare("TEXT_INPUT")==0)
        return "<num>1";
    else if(sline.compare("TEXT_OUTPUT")==0)
        return "<num>2";
    else if(sline.compare("TEXT_APPEND")==0)
        return "<num>3";
    else if(sline.compare("TEXT_INPUT_PLUS")==0)
        return "<num>4";
    else if(sline.compare("TEXT_OUTPUT_PLUS")==0)
        return "<num>5";
    else if(sline.compare("TEXT_APPEND_PLUS")==0)
        return "<num>6";
    else if(sline.compare("BINARY_INPUT")==0)
        return "<num>7";
    else if(sline.compare("BINARY_OUTPUT")==0)
        return "<num>8";
    else if(sline.compare("BINARY_APPEND")==0)
        return "<num>9";
    else if(sline.compare("BINARY_INPUT_PLUS")==0)
        return "<num>10";
    else if(sline.compare("BINARY_OUTPUT_PLUS")==0)
        return "<num>11";
    else if(sline.compare("BINARY_APPEND_PLUS")==0)
        return "<num>12";
    else if(sline.compare("TRUE")==0)
        return "<num>1";
    else if(sline.compare("FALSE")==0)
        return "<num>0";
    else if(sline.compare("K_0")==0)
        return "<num>" + rc_intToString(SDLK_0);
    else if(sline.compare("K_1")==0)
        return "<num>" + rc_intToString(SDLK_1);
    else if(sline.compare("K_2")==0)
        return "<num>" + rc_intToString(SDLK_2);
    else if(sline.compare("K_3")==0)
        return "<num>" + rc_intToString(SDLK_3);
    else if(sline.compare("K_4")==0)
        return "<num>" + rc_intToString(SDLK_4);
    else if(sline.compare("K_5")==0)
        return "<num>" + rc_intToString(SDLK_5);
    else if(sline.compare("K_6")==0)
        return "<num>" + rc_intToString(SDLK_6);
    else if(sline.compare("K_7")==0)
        return "<num>" + rc_intToString(SDLK_7);
    else if(sline.compare("K_8")==0)
        return "<num>" + rc_intToString(SDLK_8);
    else if(sline.compare("K_9")==0)
        return "<num>" + rc_intToString(SDLK_9);
    else if(sline.compare("K_A")==0)
        return "<num>" + rc_intToString(SDLK_a);
    else if(sline.compare("K_AC_BACK")==0)
        return "<num>" + rc_intToString(SDLK_AC_BACK);
    else if(sline.compare("K_AC_BOOKMARKS")==0)
        return "<num>" + rc_intToString(SDLK_AC_BOOKMARKS);
    else if(sline.compare("K_AC_FORWARD")==0)
        return "<num>" + rc_intToString(SDLK_AC_FORWARD);
    else if(sline.compare("K_AC_HOME")==0)
        return "<num>" + rc_intToString(SDLK_AC_HOME);
    else if(sline.compare("K_AC_REFRESH")==0)
        return "<num>" + rc_intToString(SDLK_AC_REFRESH);
    else if(sline.compare("K_AC_SEARCH")==0)
        return "<num>" + rc_intToString(SDLK_AC_SEARCH);
    else if(sline.compare("K_AC_STOP")==0)
        return "<num>" + rc_intToString(SDLK_AC_STOP);
    else if(sline.compare("K_AGAIN")==0)
        return "<num>" + rc_intToString(SDLK_AGAIN);
    else if(sline.compare("K_ALTERASE")==0)
        return "<num>" + rc_intToString(SDLK_ALTERASE);
    else if(sline.compare("K_APPLICATION")==0)
        return "<num>" + rc_intToString(SDLK_APPLICATION);
    else if(sline.compare("K_AUDIOMUTE")==0)
        return "<num>" + rc_intToString(SDLK_AUDIOMUTE);
    else if(sline.compare("K_AUDIONEXT")==0)
        return "<num>" + rc_intToString(SDLK_AUDIONEXT);
    else if(sline.compare("K_AUDIOPLAY")==0)
        return "<num>" + rc_intToString(SDLK_AUDIOPLAY);
    else if(sline.compare("K_AUDIOPREV")==0)
        return "<num>" + rc_intToString(SDLK_AUDIOPREV);
    else if(sline.compare("K_AUDIOSTOP")==0)
        return "<num>" + rc_intToString(SDLK_AUDIOSTOP);
    else if(sline.compare("K_B")==0)
        return "<num>" + rc_intToString(SDLK_b);
    else if(sline.compare("K_BACKSLASH")==0)
        return "<num>" + rc_intToString(SDLK_BACKSLASH);
    else if(sline.compare("K_BACKSPACE")==0)
        return "<num>" + rc_intToString(SDLK_BACKSPACE);
    else if(sline.compare("K_BRIGHTNESSDOWN")==0)
        return "<num>" + rc_intToString(SDLK_BRIGHTNESSDOWN);
    else if(sline.compare("K_BRIGHTNESSUP")==0)
        return "<num>" + rc_intToString(SDLK_BRIGHTNESSUP);
    else if(sline.compare("K_C")==0)
        return "<num>" + rc_intToString(SDLK_c);
    else if(sline.compare("K_CALCULATOR")==0)
        return "<num>" + rc_intToString(SDLK_CALCULATOR);
    else if(sline.compare("K_CANCEL")==0)
        return "<num>" + rc_intToString(SDLK_CANCEL);
    else if(sline.compare("K_CAPSLOCK")==0)
        return "<num>" + rc_intToString(SDLK_CAPSLOCK);
    else if(sline.compare("K_CLEAR")==0)
        return "<num>" + rc_intToString(SDLK_CLEAR);
    else if(sline.compare("K_CLEARAGAIN")==0)
        return "<num>" + rc_intToString(SDLK_CLEARAGAIN);
    else if(sline.compare("K_COMPUTER")==0)
        return "<num>" + rc_intToString(SDLK_COMPUTER);
    else if(sline.compare("K_COPY")==0)
        return "<num>" + rc_intToString(SDLK_COPY);
    else if(sline.compare("K_CRSEL")==0)
        return "<num>" + rc_intToString(SDLK_CRSEL);
    else if(sline.compare("K_CURRENCYSUBUNIT")==0)
        return "<num>" + rc_intToString(SDLK_CURRENCYSUBUNIT);
    else if(sline.compare("K_CURRENCYUNIT")==0)
        return "<num>" + rc_intToString(SDLK_CURRENCYUNIT);
    else if(sline.compare("K_CUT")==0)
        return "<num>" + rc_intToString(SDLK_CUT);
    else if(sline.compare("K_D")==0)
        return "<num>" + rc_intToString(SDLK_d);
    else if(sline.compare("K_DECIMALSEPARATOR")==0)
        return "<num>" + rc_intToString(SDLK_DECIMALSEPARATOR);
    else if(sline.compare("K_DELETE")==0)
        return "<num>" + rc_intToString(SDLK_DELETE);
    else if(sline.compare("K_DISPLAYSWITCH")==0)
        return "<num>" + rc_intToString(SDLK_DISPLAYSWITCH);
    else if(sline.compare("K_DOWN")==0)
        return "<num>" + rc_intToString(SDLK_DOWN);
    else if(sline.compare("K_E")==0)
        return "<num>" + rc_intToString(SDLK_e);
    else if(sline.compare("K_EJECT")==0)
        return "<num>" + rc_intToString(SDLK_EJECT);
    else if(sline.compare("K_END")==0)
        return "<num>" + rc_intToString(SDLK_END);
    else if(sline.compare("K_EQUAL")==0)
        return "<num>" + rc_intToString(SDLK_EQUALS);
    else if(sline.compare("K_ESCAPE")==0)
        return "<num>" + rc_intToString(SDLK_ESCAPE);
    else if(sline.compare("K_EXECUTE")==0)
        return "<num>" + rc_intToString(SDLK_EXECUTE);
    else if(sline.compare("K_EXSEL")==0)
        return "<num>" + rc_intToString(SDLK_EXSEL);
    else if(sline.compare("K_F")==0)
        return "<num>" + rc_intToString(SDLK_f);
    else if(sline.compare("K_F1")==0)
        return "<num>" + rc_intToString(SDLK_F1);
    else if(sline.compare("K_F2")==0)
        return "<num>" + rc_intToString(SDLK_F2);
    else if(sline.compare("K_F3")==0)
        return "<num>" + rc_intToString(SDLK_F3);
    else if(sline.compare("K_F4")==0)
        return "<num>" + rc_intToString(SDLK_F4);
    else if(sline.compare("K_F5")==0)
        return "<num>" + rc_intToString(SDLK_F5);
    else if(sline.compare("K_F6")==0)
        return "<num>" + rc_intToString(SDLK_F6);
    else if(sline.compare("K_F7")==0)
        return "<num>" + rc_intToString(SDLK_F7);
    else if(sline.compare("K_F8")==0)
        return "<num>" + rc_intToString(SDLK_F8);
    else if(sline.compare("K_F9")==0)
        return "<num>" + rc_intToString(SDLK_F9);
    else if(sline.compare("K_F10")==0)
        return "<num>" + rc_intToString(SDLK_F10);
    else if(sline.compare("K_F11")==0)
        return "<num>" + rc_intToString(SDLK_F11);
    else if(sline.compare("K_F12")==0)
        return "<num>" + rc_intToString(SDLK_F12);
    else if(sline.compare("K_F13")==0)
        return "<num>" + rc_intToString(SDLK_F13);
    else if(sline.compare("K_F14")==0)
        return "<num>" + rc_intToString(SDLK_F14);
    else if(sline.compare("K_F15")==0)
        return "<num>" + rc_intToString(SDLK_F15);
    else if(sline.compare("K_F16")==0)
        return "<num>" + rc_intToString(SDLK_F16);
    else if(sline.compare("K_F17")==0)
        return "<num>" + rc_intToString(SDLK_F17);
    else if(sline.compare("K_F18")==0)
        return "<num>" + rc_intToString(SDLK_F18);
    else if(sline.compare("K_F19")==0)
        return "<num>" + rc_intToString(SDLK_F19);
    else if(sline.compare("K_F20")==0)
        return "<num>" + rc_intToString(SDLK_F20);
    else if(sline.compare("K_F21")==0)
        return "<num>" + rc_intToString(SDLK_F21);
    else if(sline.compare("K_F22")==0)
        return "<num>" + rc_intToString(SDLK_F22);
    else if(sline.compare("K_F23")==0)
        return "<num>" + rc_intToString(SDLK_F23);
    else if(sline.compare("K_F24")==0)
        return "<num>" + rc_intToString(SDLK_F24);
    else if(sline.compare("K_FIND")==0)
        return "<num>" + rc_intToString(SDLK_FIND);
    else if(sline.compare("K_G")==0)
        return "<num>" + rc_intToString(SDLK_g);
    else if(sline.compare("K_GRAVE")==0)
        return "<num>" + rc_intToString(SDLK_BACKQUOTE);
    else if(sline.compare("K_H")==0)
        return "<num>" + rc_intToString(SDLK_h);
    else if(sline.compare("K_HELP")==0)
        return "<num>" + rc_intToString(SDLK_HELP);
    else if(sline.compare("K_HOME")==0)
        return "<num>" + rc_intToString(SDLK_HOME);
    else if(sline.compare("K_I")==0)
        return "<num>" + rc_intToString(SDLK_i);
    else if(sline.compare("K_INSERT")==0)
        return "<num>" + rc_intToString(SDLK_INSERT);
    else if(sline.compare("K_J")==0)
        return "<num>" + rc_intToString(SDLK_j);
    else if(sline.compare("K_K")==0)
        return "<num>" + rc_intToString(SDLK_k);
    else if(sline.compare("K_KBDILLUMDOWN")==0)
        return "<num>" + rc_intToString(SDLK_KBDILLUMDOWN);
    else if(sline.compare("K_KBDILLUMTOGGLE")==0)
        return "<num>" + rc_intToString(SDLK_KBDILLUMTOGGLE);
    else if(sline.compare("K_KBDILLUMUP")==0)
        return "<num>" + rc_intToString(SDLK_KBDILLUMUP);
    else if(sline.compare("KEYPAD_0")==0)
        return "<num>" + rc_intToString(SDLK_KP_0);
    else if(sline.compare("KEYPAD_00")==0)
        return "<num>" + rc_intToString(SDLK_KP_00);
    else if(sline.compare("KEYPAD_000")==0)
        return "<num>" + rc_intToString(SDLK_KP_000);
    else if(sline.compare("KEYPAD_1")==0)
        return "<num>" + rc_intToString(SDLK_KP_1);
    else if(sline.compare("KEYPAD_2")==0)
        return "<num>" + rc_intToString(SDLK_KP_2);
    else if(sline.compare("KEYPAD_3")==0)
        return "<num>" + rc_intToString(SDLK_KP_3);
    else if(sline.compare("KEYPAD_4")==0)
        return "<num>" + rc_intToString(SDLK_KP_4);
    else if(sline.compare("KEYPAD_5")==0)
        return "<num>" + rc_intToString(SDLK_KP_5);
    else if(sline.compare("KEYPAD_6")==0)
        return "<num>" + rc_intToString(SDLK_KP_6);
    else if(sline.compare("KEYPAD_7")==0)
        return "<num>" + rc_intToString(SDLK_KP_7);
    else if(sline.compare("KEYPAD_8")==0)
        return "<num>" + rc_intToString(SDLK_KP_8);
    else if(sline.compare("KEYPAD_9")==0)
        return "<num>" + rc_intToString(SDLK_KP_9);
    else if(sline.compare("KEYPAD_A")==0)
        return "<num>" + rc_intToString(SDLK_KP_A);
    else if(sline.compare("KEYPAD_AMPERSAND")==0)
        return "<num>" + rc_intToString(SDLK_KP_AMPERSAND);
    else if(sline.compare("KEYPAD_AT")==0)
        return "<num>" + rc_intToString(SDLK_KP_AT);
    else if(sline.compare("KEYPAD_B")==0)
        return "<num>" + rc_intToString(SDLK_KP_B);
    else if(sline.compare("KEYPAD_BACKSPACE")==0)
        return "<num>" + rc_intToString(SDLK_KP_BACKSPACE);
    else if(sline.compare("KEYPAD_BINARY")==0)
        return "<num>" + rc_intToString(SDLK_KP_BINARY);
    else if(sline.compare("KEYPAD_C")==0)
        return "<num>" + rc_intToString(SDLK_KP_C);
    else if(sline.compare("KEYPAD_CLEAR")==0)
        return "<num>" + rc_intToString(SDLK_KP_CLEAR);
    else if(sline.compare("KEYPAD_CLEARENTRY")==0)
        return "<num>" + rc_intToString(SDLK_KP_CLEARENTRY);
    else if(sline.compare("KEYPAD_COLON")==0)
        return "<num>" + rc_intToString(SDLK_KP_COLON);
    else if(sline.compare("KEYPAD_COMMA")==0)
        return "<num>" + rc_intToString(SDLK_KP_COMMA);
    else if(sline.compare("KEYPAD_D")==0)
        return "<num>" + rc_intToString(SDLK_KP_D);
    else if(sline.compare("KEYPAD_DBLAMPERSAND")==0)
        return "<num>" + rc_intToString(SDLK_KP_DBLAMPERSAND);
    else if(sline.compare("KEYPAD_DBLVERTICALBAR")==0)
        return "<num>" + rc_intToString(SDLK_KP_DBLVERTICALBAR);
    else if(sline.compare("KEYPAD_DECIMAL")==0)
        return "<num>" + rc_intToString(SDLK_KP_DECIMAL);
    else if(sline.compare("KEYPAD_DIVIDE")==0)
        return "<num>" + rc_intToString(SDLK_KP_DIVIDE);
    else if(sline.compare("KEYPAD_E")==0)
        return "<num>" + rc_intToString(SDLK_KP_E);
    else if(sline.compare("KEYPAD_ENTER")==0)
        return "<num>" + rc_intToString(SDLK_KP_ENTER);
    else if(sline.compare("KEYPAD_EQUAL")==0)
        return "<num>" + rc_intToString(SDLK_KP_EQUALS);
    else if(sline.compare("KEYPAD_EQUALAS400")==0)
        return "<num>" + rc_intToString(SDLK_KP_EQUALSAS400);
    else if(sline.compare("KEYPAD_EXCLAM")==0)
        return "<num>" + rc_intToString(SDLK_KP_EXCLAM);
    else if(sline.compare("KEYPAD_F")==0)
        return "<num>" + rc_intToString(SDLK_KP_F);
    else if(sline.compare("KEYPAD_GREATER")==0)
        return "<num>" + rc_intToString(SDLK_KP_GREATER);
    else if(sline.compare("KEYPAD_HASH")==0)
        return "<num>" + rc_intToString(SDLK_KP_HASH);
    else if(sline.compare("KEYPAD_HEXADECIMAL")==0)
        return "<num>" + rc_intToString(SDLK_KP_HEXADECIMAL);
    else if(sline.compare("KEYPAD_LEFTBRACE")==0)
        return "<num>" + rc_intToString(SDLK_KP_LEFTBRACE);
    else if(sline.compare("KEYPAD_LEFTPAREN")==0)
        return "<num>" + rc_intToString(SDLK_KP_LEFTPAREN);
    else if(sline.compare("KEYPAD_LESS")==0)
        return "<num>" + rc_intToString(SDLK_KP_LESS);
    else if(sline.compare("KEYPAD_MEMADD")==0)
        return "<num>" + rc_intToString(SDLK_KP_MEMADD);
    else if(sline.compare("KEYPAD_MEMCLEAR")==0)
        return "<num>" + rc_intToString(SDLK_KP_MEMCLEAR);
    else if(sline.compare("KEYPAD_MEMDIVIDE")==0)
        return "<num>" + rc_intToString(SDLK_KP_MEMDIVIDE);
    else if(sline.compare("KEYPAD_MEMMULTIPLY")==0)
        return "<num>" + rc_intToString(SDLK_KP_MEMMULTIPLY);
    else if(sline.compare("KEYPAD_OCTAL")==0)
        return "<num>" + rc_intToString(SDLK_KP_OCTAL);
    else if(sline.compare("KEYPAD_PERCENT")==0)
        return "<num>" + rc_intToString(SDLK_KP_PERCENT);
    else if(sline.compare("KEYPAD_PERIOD")==0)
        return "<num>" + rc_intToString(SDLK_KP_PERIOD);
    else if(sline.compare("KEYPAD_PLUS")==0)
        return "<num>" + rc_intToString(SDLK_KP_PLUS);
    else if(sline.compare("KEYPAD_PLUSMINUS")==0)
        return "<num>" + rc_intToString(SDLK_KP_PLUSMINUS);
    else if(sline.compare("KEYPAD_POWER")==0)
        return "<num>" + rc_intToString(SDLK_KP_POWER);
    else if(sline.compare("KEYPAD_RIGHTBRACE")==0)
        return "<num>" + rc_intToString(SDLK_KP_RIGHTBRACE);
    else if(sline.compare("KEYPAD_RIGHTPAREN")==0)
        return "<num>" + rc_intToString(SDLK_KP_RIGHTPAREN);
    else if(sline.compare("KEYPAD_SPACE")==0)
        return "<num>" + rc_intToString(SDLK_KP_SPACE);
    else if(sline.compare("KEYPAD_TAB")==0)
        return "<num>" + rc_intToString(SDLK_KP_TAB);
    else if(sline.compare("KEYPAD_VERTICALBAR")==0)
        return "<num>" + rc_intToString(SDLK_KP_VERTICALBAR);
    else if(sline.compare("KEYPAD_XOR")==0)
        return "<num>" + rc_intToString(SDLK_KP_XOR);
    else if(sline.compare("K_L")==0)
        return "<num>" + rc_intToString(SDLK_l);
    else if(sline.compare("K_L")==0)
        return "<num>" + rc_intToString(SDLK_l);
    else if(sline.compare("K_LALT")==0)
        return "<num>" + rc_intToString(SDLK_LALT);
    else if(sline.compare("K_LCTRL")==0)
        return "<num>" + rc_intToString(SDLK_LCTRL);
    else if(sline.compare("K_LEFT")==0)
        return "<num>" + rc_intToString(SDLK_LEFT);
    else if(sline.compare("K_LEFTBRACKET")==0)
        return "<num>" + rc_intToString(SDLK_LEFTBRACKET);
    else if(sline.compare("K_LGUI")==0)
        return "<num>" + rc_intToString(SDLK_LGUI);
    else if(sline.compare("K_LSHIFT")==0)
        return "<num>" + rc_intToString(SDLK_LSHIFT);
    else if(sline.compare("K_M")==0)
        return "<num>" + rc_intToString(SDLK_m);
    else if(sline.compare("K_MAIL")==0)
        return "<num>" + rc_intToString(SDLK_MAIL);
    else if(sline.compare("K_MEDIASELECT")==0)
        return "<num>" + rc_intToString(SDLK_MEDIASELECT);
    else if(sline.compare("K_MENU")==0)
        return "<num>" + rc_intToString(SDLK_MENU);
    else if(sline.compare("K_MINUS")==0)
        return "<num>" + rc_intToString(SDLK_MINUS);
    else if(sline.compare("K_MODESWITCH")==0)
        return "<num>" + rc_intToString(SDLK_MODE);
    else if(sline.compare("K_MUTE")==0)
        return "<num>" + rc_intToString(SDLK_MUTE);
    else if(sline.compare("K_N")==0)
        return "<num>" + rc_intToString(SDLK_n);
    else if(sline.compare("K_NUMLOCK")==0)
        return "<num>" + rc_intToString(SDLK_NUMLOCKCLEAR);
    else if(sline.compare("K_O")==0)
        return "<num>" + rc_intToString(SDLK_o);
    else if(sline.compare("K_OPER")==0)
        return "<num>" + rc_intToString(SDLK_OPER);
    else if(sline.compare("K_OUT")==0)
        return "<num>" + rc_intToString(SDLK_OUT);
    else if(sline.compare("K_P")==0)
        return "<num>" + rc_intToString(SDLK_p);
    else if(sline.compare("K_PAGEDOWN")==0)
        return "<num>" + rc_intToString(SDLK_PAGEDOWN);
    else if(sline.compare("K_PAGEUP")==0)
        return "<num>" + rc_intToString(SDLK_PAGEUP);
    else if(sline.compare("K_PASTE")==0)
        return "<num>" + rc_intToString(SDLK_PASTE);
    else if(sline.compare("K_PAUSE")==0)
        return "<num>" + rc_intToString(SDLK_PAUSE);
    else if(sline.compare("K_POWER")==0)
        return "<num>" + rc_intToString(SDLK_POWER);
    else if(sline.compare("K_PRINTSCREEN")==0)
        return "<num>" + rc_intToString(SDLK_PRINTSCREEN);
    else if(sline.compare("K_PRIOR")==0)
        return "<num>" + rc_intToString(SDLK_PRIOR);
    else if(sline.compare("K_Q")==0)
        return "<num>" + rc_intToString(SDLK_q);
    else if(sline.compare("K_R")==0)
        return "<num>" + rc_intToString(SDLK_r);
    else if(sline.compare("K_RALT")==0)
        return "<num>" + rc_intToString(SDLK_RALT);
    else if(sline.compare("K_RCTRL")==0)
        return "<num>" + rc_intToString(SDLK_RCTRL);
    else if(sline.compare("K_RETURN")==0)
        return "<num>" + rc_intToString(SDLK_RETURN);
    else if(sline.compare("K_RETURN2")==0)
        return "<num>" + rc_intToString(SDLK_RETURN2);
    else if(sline.compare("K_RGUI")==0)
        return "<num>" + rc_intToString(SDLK_RGUI);
    else if(sline.compare("K_RIGHT")==0)
        return "<num>" + rc_intToString(SDLK_RIGHT);
    else if(sline.compare("K_RIGHTBRACKET")==0)
        return "<num>" + rc_intToString(SDLK_RIGHTBRACKET);
    else if(sline.compare("K_RSHIFT")==0)
        return "<num>" + rc_intToString(SDLK_RSHIFT);
    else if(sline.compare("K_S")==0)
        return "<num>" + rc_intToString(SDLK_s);
    else if(sline.compare("K_SCROLLLOCK")==0)
        return "<num>" + rc_intToString(SDLK_SCROLLLOCK);
    else if(sline.compare("K_SELECT")==0)
        return "<num>" + rc_intToString(SDLK_SELECT);
    else if(sline.compare("K_SEMICOLON")==0)
        return "<num>" + rc_intToString(SDLK_SEMICOLON);
    else if(sline.compare("K_SEPARATOR")==0)
        return "<num>" + rc_intToString(SDLK_SEPARATOR);
    else if(sline.compare("K_SLASH")==0)
        return "<num>" + rc_intToString(SDLK_SLASH);
    else if(sline.compare("K_SLEEP")==0)
        return "<num>" + rc_intToString(SDLK_SLEEP);
    else if(sline.compare("K_SPACE")==0)
        return "<num>" + rc_intToString(SDLK_SPACE);
    else if(sline.compare("K_STOP")==0)
        return "<num>" + rc_intToString(SDLK_STOP);
    else if(sline.compare("K_SYSREQ")==0)
        return "<num>" + rc_intToString(SDLK_SYSREQ);
    else if(sline.compare("K_T")==0)
        return "<num>" + rc_intToString(SDLK_t);
    else if(sline.compare("K_TAB")==0)
        return "<num>" + rc_intToString(SDLK_TAB);
    else if(sline.compare("K_THOUSANDSEPARATOR")==0)
        return "<num>" + rc_intToString(SDLK_THOUSANDSSEPARATOR);
    else if(sline.compare("K_U")==0)
        return "<num>" + rc_intToString(SDLK_u);
    else if(sline.compare("K_UNDO")==0)
        return "<num>" + rc_intToString(SDLK_UNDO);
    else if(sline.compare("K_UNKNOWN")==0)
        return "<num>" + rc_intToString(SDLK_UNKNOWN);
    else if(sline.compare("K_UP")==0)
        return "<num>" + rc_intToString(SDLK_UP);
    else if(sline.compare("K_V")==0)
        return "<num>" + rc_intToString(SDLK_v);
    else if(sline.compare("K_VOLUMEDOWN")==0)
        return "<num>" + rc_intToString(SDLK_VOLUMEDOWN);
    else if(sline.compare("K_VOLUMEUP")==0)
        return "<num>" + rc_intToString(SDLK_VOLUMEUP);
    else if(sline.compare("K_W")==0)
        return "<num>" + rc_intToString(SDLK_w);
    else if(sline.compare("K_WWW")==0)
        return "<num>" + rc_intToString(SDLK_WWW);
    else if(sline.compare("K_X")==0)
        return "<num>" + rc_intToString(SDLK_x);
    else if(sline.compare("K_Y")==0)
        return "<num>" + rc_intToString(SDLK_y);
    else if(sline.compare("K_Z")==0)
        return "<num>" + rc_intToString(SDLK_z);
    else if(sline.compare("WINDOWPOS_CENTERED")==0)
        return "<num>" + rc_intToString(SDL_WINDOWPOS_CENTERED);
    else if(sline.compare("HAT_RIGHT")==0)
        return "<num>" + rc_intToString(SDL_HAT_RIGHT);
    else if(sline.compare("HAT_LEFT")==0)
        return "<num>" + rc_intToString(SDL_HAT_LEFT);
    else if(sline.compare("HAT_UP")==0)
        return "<num>" + rc_intToString(SDL_HAT_UP);
    else if(sline.compare("HAT_DOWN")==0)
        return "<num>" + rc_intToString(SDL_HAT_DOWN);
    else if(sline.compare("HAT_LEFTUP")==0)
        return "<num>" + rc_intToString(SDL_HAT_LEFTUP);
    else if(sline.compare("HAT_LEFTDOWN")==0)
        return "<num>" + rc_intToString(SDL_HAT_LEFTDOWN);
    else if(sline.compare("HAT_RIGHTUP")==0)
        return "<num>" + rc_intToString(SDL_HAT_RIGHTUP);
    else if(sline.compare("HAT_RIGHTDOWN")==0)
        return "<num>" + rc_intToString(SDL_HAT_RIGHTDOWN);
    else if(sline.compare("HAT_CENTERED")==0)
        return "<num>" + rc_intToString(SDL_HAT_CENTERED);
    else if(sline.compare("BLENDMODE_NONE")==0)
        return "<num>" + rc_intToString(SDL_BLENDMODE_NONE);
    else if(sline.compare("BLENDMODE_BLEND")==0)
        return "<num>" + rc_intToString(SDL_BLENDMODE_BLEND);
    else if(sline.compare("BLENDMODE_ADD")==0)
        return "<num>" + rc_intToString(SDL_BLENDMODE_ADD);
    else if(sline.compare("BLENDMODE_MOD")==0)
        return "<num>" + rc_intToString(SDL_BLENDMODE_MOD);
    else if(sline.compare("ANDROID_EXTERNAL_STORAGE_READ")==0)
        return "<num>1";
    else if(sline.compare("ANDROID_EXTERNAL_STORAGE_WRITE")==0)
        return "<num>2";
    else if(sline.compare("POWERSTATE_UNKNOWN")==0)
        return "<num>0";
    else if(sline.compare("POWERSTATE_ON_BATTERY")==0)
        return "<num>1";
    else if(sline.compare("POWERSTATE_NO_BATTERY")==0)
        return "<num>2";
    else if(sline.compare("POWERSTATE_CHARGING")==0)
        return "<num>3";
    else if(sline.compare("POWERSTATE_CHARGED")==0)
        return "<num>4";

    return "";
}

void output_tokens()
{
    return;
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
