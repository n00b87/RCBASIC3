#ifndef RC_VM_ASM_H_INCLUDED
#define RC_VM_ASM_H_INCLUDED

#define RC_CLEAN_AFTER_BUILD true
#define RC_NO_CLEAN_AFTER_BUILD false

#include <iostream>
#include <fstream>
#include <inttypes.h>
#include <vector>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;

#define LESS_FLAG 0
#define LESS_EQUAL_FLAG 1
#define GREATER_FLAG 2
#define GREATER_EQUAL_FLAG 3
#define EQUAL_FLAG 4
#define NOT_EQUAL_FLAG 5

#define CODE_SEGMENT 0
#define DATA_SEGMENT 1

namespace rc_cbc_assembler
{

    uint64_t numID_count = 0;
    uint64_t strID_count = 0;

    uint64_t vm_n_count = 0;
    uint64_t vm_s_count = 0;

    uint64_t n_stack_size = 0;
    uint64_t s_stack_size = 0;
    uint64_t loop_stack_size = 0;

    uint64_t str_data_size = 0;

    struct rc_label
    {
        string label_name;
        uint64_t label_address;
        int label_segment;
    };

    vector<rc_label> label;

    vector<unsigned char> rc_code_segment;
    vector<unsigned char> rc_data_segment;
    int current_segment = 0;

    string rc_intToString(int a)
    {
        stringstream ss;
        ss << a;
        string str = ss.str();
        ss.clear();
        return str;
    }

    int rc_stringToInt(string a)
    {
        stringstream ss;
        ss << a;
        int i = 0;
        ss >> i;
        ss.clear();
        return i;
    }

    double rc_stringToDouble(string a)
    {
        double d = atof(a.c_str());
        return d;
    }

    bool isDigit(char c)
    {
        return (c >= '0' && c <= '9');
    }

    int rc_find_digit(string line)
    {
        for(int i = 0; i < line.length(); i++)
        {
            if(isDigit(line[i]))
                return i;
        }
        return -1;
    }

    bool loadData(string datafile, string str_datafile)
    {

        fstream f(str_datafile.c_str(), fstream::in);
        if(!f.is_open())
            return false;

        char c;
        while(true)
        {
            f.get(c);

            if(f.eof())
                break;
            rc_data_segment.push_back(c);
        }
        f.close();

        str_data_size = rc_data_segment.size();
        f.open(datafile.c_str(), fstream::in);
        if(!f.is_open())
            return false;
        //n_count
        //s_count
        //n_stack_count
        //s_stack_count
        //loop_stack_count
        //numID_count
        //strID_count
        //label_count
        //labels

        string line = "";

        getline(f, line);
        vm_n_count = rc_stringToInt(line);

        getline(f, line);
        vm_s_count = rc_stringToInt(line);

        getline(f, line);
        n_stack_size = rc_stringToInt(line);

        getline(f, line);
        s_stack_size = rc_stringToInt(line);

        getline(f, line);
        loop_stack_size = rc_stringToInt(line);

        getline(f, line);
        numID_count = rc_stringToInt(line);

        getline(f, line);
        strID_count = rc_stringToInt(line);

        getline(f, line);
        int num_labels = rc_stringToInt(line);

        rc_label lbl;
        //cout << "num labels equals " << num_labels << endl;

        for(int i = 0; i < num_labels; i++)
        {
            getline(f, line);
            lbl.label_name = line.substr(0, line.find_first_of(" "));

            line = line.substr(line.find_first_of(" "));
            line = line.substr(line.find_first_not_of(" "));

            lbl.label_address = rc_stringToInt(line.substr(0, line.find_first_of(" ")));

            line = line.substr(line.find_first_of(" "));
            lbl.label_segment = rc_stringToInt(line.substr(line.find_first_not_of(" ")));

            if(lbl.label_segment == DATA_SEGMENT)
            {
                //cout << lbl.label_name << " is in data: " << lbl.label_address << endl;
                lbl.label_address += str_data_size;
            }
            else
            {
                //cout << lbl.label_name << " segment = " << lbl.label_segment << endl;
            }
            label.push_back(lbl);
        }

        f.close();

        return true;
    }

    union u_double
    {
        double f;
        unsigned char data[sizeof(double)];
    };

    union ru_int
    {
        uint64_t i;
        unsigned char data[sizeof(uint64_t)];
    };


    void writeSegment(unsigned char c)
    {
        switch(current_segment)
        {
            case CODE_SEGMENT:
                rc_code_segment.push_back(c);
                break;
            case DATA_SEGMENT:
                rc_data_segment.push_back(c);
                break;
        }
    }

    string line_arg[10];
    int line_arg_count = 0;

    bool parseLine(string line)
    {
        line += " "; //add a space so that it reads the last argument on the line
        line_arg_count = 0;
        for(int i = 0; i < 10; i++)
            line_arg[i] = "";
        for(int i = 0; i < line.length(); i++)
        {
            if(line.substr(i,1).compare(" ")==0)
            {
                //cout << "line_arg[" << line_arg_count << "] = " << line_arg[line_arg_count] << endl;
                line_arg_count++;
                for(; i < line.length(); i++)
                {
                    if(line.substr(i,1).compare(" ")!=0)
                        break;
                }
                i--;
            }
            else
            {
                line_arg[line_arg_count] += line.substr(i,1);
            }
        }
        return true;
    }

    bool LABEL_NOT_FOUND = false;

    uint64_t lookUpAddress(string lbl_name)
    {
        LABEL_NOT_FOUND = false;
        for(int i = 0; i < label.size(); i++)
        {
            if(label[i].label_name.compare(lbl_name)==0)
                return label[i].label_address;
        }
        LABEL_NOT_FOUND = true;
        return -1;
    }

    bool genByteCode(string asm_file)
    {
        fstream f(asm_file.c_str(), fstream::in);

        string line = "";

        u_double rc_dbl;
        ru_int rc_int;

        while(true)
        {
            //cout << "start" << endl;
            getline(f, line);

            if(f.eof())
            {
                return true;
            }

            //cout << "balls" << endl;

            parseLine(line);
            //cout << "line = " << line << endl;

            if(line_arg[0].compare(".code")==0)
            {
                //cout << "switching to code" << endl;
                current_segment = CODE_SEGMENT;
            }
            else if(line_arg[0].compare(".data")==0)
            {
                //cout << "switching to data" << endl;
                current_segment = DATA_SEGMENT;
            }
            else if(line_arg[0].compare("label")==0)
            {
                continue;
            }
            else if(line_arg[0].compare("end")==0)
            {
                writeSegment(0);
            }
            else if(line_arg[0].compare("mov")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(32);
                }
                else if(arg1_type.compare("n")==0 && (isDigit(arg2_type[0]) || arg2_type[0]=='-'))
                {
                    writeSegment(33);
                }
                else if(arg1_type.compare("n")==0 && arg2_type.compare("!")==0)
                {
                    writeSegment(34);
                }
                else if(arg1_type.compare("!")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(35);
                }
                else if(arg1_type.compare("n")==0 && arg2_type.compare("%")==0)
                {
                    writeSegment(133);
                }
            }
            else if(line_arg[0].compare("mov$")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("s")==0 && arg2_type.compare("s")==0)
                {
                    writeSegment(36);
                }
                else if(arg1_type.compare("s")==0 && arg2_type.compare("@")==0)
                {
                    writeSegment(37);
                }
                else if(arg1_type.compare("s")==0 && arg2_type.compare("!")==0)
                {
                    writeSegment(38);
                }
                else if(arg1_type.compare("!")==0 && arg2_type.compare("s")==0)
                {
                    writeSegment(39);
                }
            }
            else if(line_arg[0].compare("mov_r")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(40);
                }
                else
                    cout << "Error mov_r" << endl;
            }
            else if(line_arg[0].compare("mov_r$")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("s")==0 && arg2_type.compare("s")==0)
                {
                    writeSegment(41);
                }
                else
                    cout << "Error mov_r" << endl;
            }
            else if(line_arg[0].compare("mov_type")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                //mov_type is not currently supported
                cout << "Error mov_type not supported yet" << endl;
            }
            else if(line_arg[0].compare("add$")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("s")==0 && arg2_type.compare("s")==0)
                {
                    writeSegment(43);
                }
                else
                    cout << "Error add$" << endl;
            }
            else if(line_arg[0].compare("add")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(44);
                }
                else
                    cout << "Error add" << endl;
            }
            else if(line_arg[0].compare("sub")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(45);
                }
                else
                    cout << "Error sub" << endl;
            }
            else if(line_arg[0].compare("mul")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(46);
                }
                else
                    cout << "Error mul" << endl;
            }
            else if(line_arg[0].compare("div")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(47);
                }
                else
                    cout << "Error div" << endl;
            }
            else if(line_arg[0].compare("pow")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(48);
                }
                else
                    cout << "Error pow" << endl;
            }
            else if(line_arg[0].compare("mod")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(49);
                }
                else
                    cout << "Error mod" << endl;
            }
            else if(line_arg[0].compare("shl")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(50);
                }
                else
                    cout << "Error shl" << endl;
            }
            else if(line_arg[0].compare("shr")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(51);
                }
                else
                    cout << "Error shr" << endl;
            }
            else if(line_arg[0].compare("and")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(52);
                }
                else
                    cout << "Error and" << endl;
            }
            else if(line_arg[0].compare("or")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(53);
                }
                else
                    cout << "Error or" << endl;
            }
            else if(line_arg[0].compare("xor")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(54);
                }
                else
                    cout << "Error xor" << endl;
            }
            else if(line_arg[0].compare("not")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);

                if(arg1_type.compare("n")==0)
                {
                    writeSegment(55);
                }
                else
                    cout << "Error not" << endl;
            }
            else if(line_arg[0].compare("cmp")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(56);
                }
                else if(arg1_type.compare("n")==0 && (isDigit(arg2_type[0]) || arg2_type[0] == '-'))
                {
                    writeSegment(134);
                }
                else
                    cout << "Error cmp: " << line << endl;
            }
            else if(line_arg[0].compare("cmp$")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("s")==0 && arg2_type.compare("s")==0)
                {
                    writeSegment(57);
                }
                else
                    cout << "Error cmp$" << endl;
            }
            else if(line_arg[0].compare("cmp_u")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);
                string arg2_type = line_arg[2].substr(0,1);

                if(arg1_type.compare("n")==0 && arg2_type.compare("n")==0)
                {
                    writeSegment(58);
                }
                else
                    cout << "Error cmp_u" << endl;
            }
            else if(line_arg[0].compare("jmp")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);

                if(arg1_type.compare("n")==0)
                {
                    writeSegment(59);
                }
                else if(arg1_type.compare("@")==0)
                {
                    writeSegment(60);
                }
                else
                    cout << "Error jmp" << endl;
            }
            else if(line_arg[0].compare("je")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);

                if(arg1_type.compare("n")==0)
                {
                    writeSegment(61);
                }
                else if(arg1_type.compare("@")==0)
                {
                    writeSegment(62);
                }
                else
                    cout << "Error je" << endl;
            }
            else if(line_arg[0].compare("jne")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);

                if(arg1_type.compare("n")==0)
                {
                    writeSegment(63);
                }
                else if(arg1_type.compare("@")==0)
                {
                    writeSegment(64);
                }
                else
                    cout << "Error jne" << endl;
            }
            else if(line_arg[0].compare("jg")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);

                if(arg1_type.compare("n")==0)
                {
                    writeSegment(65);
                }
                else if(arg1_type.compare("@")==0)
                {
                    writeSegment(66);
                }
                else
                    cout << "Error jg" << endl;
            }
            else if(line_arg[0].compare("jge")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);

                if(arg1_type.compare("n")==0)
                {
                    writeSegment(67);
                }
                else if(arg1_type.compare("@")==0)
                {
                    writeSegment(68);
                }
                else
                    cout << "Error jge" << endl;
            }
            else if(line_arg[0].compare("jl")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);

                if(arg1_type.compare("n")==0)
                {
                    writeSegment(69);
                }
                else if(arg1_type.compare("@")==0)
                {
                    writeSegment(70);
                }
                else
                    cout << "Error jl" << endl;
            }
            else if(line_arg[0].compare("jle")==0)
            {
                string arg1_type = line_arg[1].substr(0,1);

                if(arg1_type.compare("n")==0)
                {
                    writeSegment(71);
                }
                else if(arg1_type.compare("@")==0)
                {
                    writeSegment(72);
                }
                else
                    cout << "Error jle" << endl;
            }
            else if(line_arg[0].compare("obj_num")==0)
            {
                writeSegment(73);
            }
            else if(line_arg[0].compare("obj_num1")==0)
            {
                writeSegment(74);
            }
            else if(line_arg[0].compare("obj_num2")==0)
            {
                writeSegment(75);
            }
            else if(line_arg[0].compare("obj_num3")==0)
            {
                writeSegment(76);
            }
            else if(line_arg[0].compare("obj_str")==0)
            {
                writeSegment(77);
            }
            else if(line_arg[0].compare("obj_str1")==0)
            {
                writeSegment(78);
            }
            else if(line_arg[0].compare("obj_str2")==0)
            {
                writeSegment(79);
            }
            else if(line_arg[0].compare("obj_str3")==0)
            {
                writeSegment(80);
            }
            else if(line_arg[0].compare("obj_usr")==0)
            {
                writeSegment(81);
            }
            else if(line_arg[0].compare("obj_usr1")==0)
            {
                writeSegment(82);
            }
            else if(line_arg[0].compare("obj_usr2")==0)
            {
                writeSegment(83);
            }
            else if(line_arg[0].compare("obj_usr3")==0)
            {
                writeSegment(84);
            }
            else if(line_arg[0].compare("obj_get")==0)
            {
                writeSegment(85);
            }
            else if(line_arg[0].compare("obj_get$")==0)
            {
                writeSegment(86);
            }
            else if(line_arg[0].compare("obj_set")==0)
            {
                writeSegment(87);
            }
            else if(line_arg[0].compare("obj_set$")==0)
            {
                writeSegment(88);
            }
            else if(line_arg[0].compare("clear_obj")==0)
            {
                writeSegment(89);
            }
            else if(line_arg[0].compare("dim_type")==0)
            {
                writeSegment(90);
            }
            else if(line_arg[0].compare("dim_type1")==0)
            {
                writeSegment(91);
            }
            else if(line_arg[0].compare("dim_type2")==0)
            {
                writeSegment(92);
            }
            else if(line_arg[0].compare("dim_type3")==0)
            {
                writeSegment(93);
            }
            else if(line_arg[0].compare("dim_num1")==0)
            {
                writeSegment(94);
            }
            else if(line_arg[0].compare("dim_num2")==0)
            {
                writeSegment(95);
            }
            else if(line_arg[0].compare("dim_num3")==0)
            {
                writeSegment(96);
            }
            else if(line_arg[0].compare("dim_str1")==0)
            {
                writeSegment(97);
            }
            else if(line_arg[0].compare("dim_str2")==0)
            {
                writeSegment(98);
            }
            else if(line_arg[0].compare("dim_str3")==0)
            {
                writeSegment(99);
            }
            else if(line_arg[0].compare("delete")==0)
            {
                writeSegment(100);
            }
            else if(line_arg[0].compare("delete$")==0)
            {
                writeSegment(101);
            }
            else if(line_arg[0].compare("push")==0)
            {
                string arg_type = line_arg[1].substr(0,1);
                if(arg_type.compare("n")==0)
                    writeSegment(102);
                else if(arg_type.compare("!")==0)
                    writeSegment(103);
                else if(isDigit(arg_type[0]) || arg_type[0]=='-')
                    writeSegment(131);
            }
            else if(line_arg[0].compare("push$")==0)
            {
                string arg_type = line_arg[1].substr(0,1);
                if(arg_type.compare("s")==0)
                    writeSegment(104);
                else if(arg_type.compare("!")==0)
                    writeSegment(105);
            }
            else if(line_arg[0].compare("push_empty$")==0)
            {
                writeSegment(106);
            }
            else if(line_arg[0].compare("pop")==0)
            {
                string arg_type = line_arg[1].substr(0,1);
                if(arg_type.compare("n")==0)
                    writeSegment(107);
                else if(arg_type.compare("!")==0)
                    writeSegment(108);
            }
            else if(line_arg[0].compare("pop$")==0)
            {
                string arg_type = line_arg[1].substr(0,1);
                if(arg_type.compare("s")==0)
                    writeSegment(109);
                else if(arg_type.compare("!")==0)
                    writeSegment(110);
            }
            else if(line_arg[0].compare("get_stack_size")==0)
            {
                writeSegment(111);
            }
            else if(line_arg[0].compare("get_stack_size$")==0)
            {
                writeSegment(112);
            }
            else if(line_arg[0].compare("clear_stack")==0)
            {
                writeSegment(113);
            }
            else if(line_arg[0].compare("clear_stack$")==0)
            {
                writeSegment(114);
            }
            else if(line_arg[0].compare("while")==0)
            {
                writeSegment(115);
            }
            else if(line_arg[0].compare("wend")==0)
            {
                writeSegment(116);
            }
            else if(line_arg[0].compare("for")==0)
            {
                writeSegment(117);
            }
            else if(line_arg[0].compare("next")==0)
            {
                writeSegment(118);
            }
            else if(line_arg[0].compare("do")==0)
            {
                writeSegment(119);
            }
            else if(line_arg[0].compare("loop")==0)
            {
                writeSegment(120);
            }
            else if(line_arg[0].compare("loop_while")==0)
            {
                writeSegment(121);
            }
            else if(line_arg[0].compare("loop_until")==0)
            {
                writeSegment(122);
            }
            else if(line_arg[0].compare("pop_loop_stack")==0)
            {
                writeSegment(123);
            }
            else if(line_arg[0].compare("gosub")==0)
            {
                writeSegment(124);
            }
            else if(line_arg[0].compare("return")==0)
            {
                writeSegment(125);
            }
            else if(line_arg[0].compare("ptr")==0)
            {
                writeSegment(126);
            }
            else if(line_arg[0].compare("ptr$")==0)
            {
                writeSegment(127);
            }
            else if(line_arg[0].compare("print")==0)
            {
                writeSegment(128);
            }
            else if(line_arg[0].compare("print$")==0)
            {
                writeSegment(129);
            }
            else if(line_arg[0].compare("func")==0)
            {
                writeSegment(130);
            }
            else if(line_arg[0].compare("println")==0)
            {
                writeSegment(132);
            }
            else if(line_arg[0].compare("mov_arr")==0)
            {
                writeSegment(135);
            }
            else if(line_arg[0].compare("mov_arr$")==0)
            {
                writeSegment(136);
            }
            else if(line_arg[0].compare("pop_ptr")==0)
            {
                writeSegment(137);
            }
            else if(line_arg[0].compare("preset")==0)
            {
                writeSegment(138);
            }
            else if(line_arg[0].compare("preset$")==0)
            {
                writeSegment(139);
            }
            else if(line_arg[0].compare("redim1")==0)
            {
                writeSegment(140);
            }
            else if(line_arg[0].compare("redim2")==0)
            {
                writeSegment(141);
            }
            else if(line_arg[0].compare("redim3")==0)
            {
                writeSegment(142);
            }
            else if(line_arg[0].compare("redim1$")==0)
            {
                writeSegment(143);
            }
            else if(line_arg[0].compare("redim2$")==0)
            {
                writeSegment(144);
            }
            else if(line_arg[0].compare("redim3$")==0)
            {
                writeSegment(145);
            }
            else if(line_arg[0].compare("for_offset_arr1")==0)
            {
                writeSegment(146);
            }
            else if(line_arg[0].compare("for_offset_arr2")==0)
            {
                writeSegment(147);
            }
            else if(line_arg[0].compare("for_offset_arr3")==0)
            {
                writeSegment(148);
            }
            else if(line_arg[0].compare("for_offset_0")==0)
            {
                writeSegment(149);
            }
            else
            {
                cout << "unrecognized cmd: " << line_arg[0] << endl;
            }



            string arg_type = "";
            //cout << "line arg count = " << line_arg_count << endl << endl;

            for(int i = 1; i < line_arg_count; i++)
            {
                if(isDigit(line_arg[i][0]) || line_arg[i][0]=='-')
                {
                    rc_dbl.f = rc_stringToDouble(line_arg[i]);
                    //cout << "dbl_f = " << rc_dbl.f << endl;
                    for(int n = 0; n < sizeof(double); n++)
                        writeSegment(rc_dbl.data[n]);
                }
                else if(line_arg[i].substr(0,1).compare("%")==0)
                {
                    //compare flags
                    string cmp_flag = line_arg[i].substr(1)+" ";
                    cmp_flag = cmp_flag.substr(0, cmp_flag.find_first_of(" "));
                    if(cmp_flag.compare("LESS_FLAG")==0)
                    {
                        rc_int.i = LESS_FLAG;
                    }
                    else if(cmp_flag.compare("LESS_EQUAL_FLAG")==0)
                    {
                        rc_int.i = LESS_EQUAL_FLAG;
                    }
                    else if(cmp_flag.compare("GREATER_FLAG")==0)
                    {
                        rc_int.i = GREATER_FLAG;
                    }
                    else if(cmp_flag.compare("GREATER_EQUAL_FLAG")==0)
                    {
                        rc_int.i = GREATER_EQUAL_FLAG;
                    }
                    else if(cmp_flag.compare("EQUAL_FLAG")==0)
                    {
                        rc_int.i = EQUAL_FLAG;
                    }
                    else if(cmp_flag.compare("NOT_EQUAL_FLAG")==0)
                    {
                        rc_int.i = NOT_EQUAL_FLAG;
                    }
                    else
                    {
                        cout << "invalid flag" << endl;
                        return false;
                    }

                    for(int n = 0; n < sizeof(uint64_t); n++)
                        writeSegment(rc_int.data[n]);
                }
                else if(line_arg[i].substr(0,1).compare("@")==0)
                {
                    rc_int.i = lookUpAddress(line_arg[i].substr(1));
                    if(LABEL_NOT_FOUND)
                    {
                        if(isDigit(line_arg[i][1]))
                        {
                            rc_int.i = rc_stringToInt(line_arg[i].substr(1));
                        }
                        else
                        {
                            cout << "something is really wrong" << endl;
                            return false;
                        }
                    }
                    for(int n = 0; n < sizeof(uint64_t); n++)
                        writeSegment(rc_int.data[n]);
                }
                else
                {
                    int p = rc_find_digit(line_arg[i]);
                    rc_int.i = rc_stringToInt(line_arg[i].substr(p));
                    if(rc_int.i < 0)
                    {
                        cout << "something is wrong" << endl;
                        return false;
                    }
                    for(int n = 0; n < sizeof(uint64_t); n++)
                        writeSegment(rc_int.data[n]);
                }
            }
        }
        return true;
    }

    fstream output_file;

    void rc_write(ru_int rc_int)
    {
        for(int i = 0; i < sizeof(uint64_t); i++)
            output_file.put(rc_int.data[i]);
    }

    bool compileCBC(string file_name)
    {
        char header[] = {'R','C','3'};

        ru_int rc_int;
        u_double rc_dbl;

        output_file.open(file_name.c_str(), fstream::out | fstream::binary);

        if(!output_file.is_open())
            return false;

        output_file.write(header, 3);

        rc_int.i = vm_n_count;
        rc_write(rc_int);

        rc_int.i = vm_s_count;
        rc_write(rc_int);

        rc_int.i = n_stack_size;
        rc_write(rc_int);

        rc_int.i = s_stack_size;
        rc_write(rc_int);

        rc_int.i = loop_stack_size;
        rc_write(rc_int);

        rc_int.i = numID_count;
        rc_write(rc_int);

        rc_int.i = strID_count;
        rc_write(rc_int);

        rc_int.i = rc_code_segment.size();
        rc_write(rc_int);

        rc_int.i = rc_data_segment.size();
        rc_write(rc_int);

        //cout << "data is " << rc_data_segment.size() << endl << endl;

        for(int i = 0; i < rc_code_segment.size(); i++)
        {
            output_file.put(rc_code_segment[i]);
        }

        for(int i = 0; i < rc_data_segment.size(); i++)
        {
            output_file.put(rc_data_segment[i]);
        }

        output_file.close();

        return true;
    }

    bool is_file_exist(const char *fileName)
    {
        std::ifstream infile(fileName);
        return infile.good();
    }

    void rc_clean()
    {
        if(is_file_exist("main.rc_data"))
            remove("main.rc_data");
        if(is_file_exist("main_str_data.sdata"))
            remove("main_str_data.sdata");
        if(is_file_exist("main.rc_asm"))
            remove("main.rc_asm");
    }

    int rc_assemble(string cbc_file, bool clean_after_build=RC_CLEAN_AFTER_BUILD)
    {

        if(is_file_exist(cbc_file.c_str()))
            remove(cbc_file.c_str());

        if(!loadData("main.rc_data", "main_str_data.sdata"))
        {
            cout << "Error loading compiler data" << endl;
            if(clean_after_build) rc_clean();
            return 0;
        }
        if(!genByteCode("main.rc_asm"))
        {
            cout << "Error generating bytecode" << endl;
            if(clean_after_build) rc_clean();
            return 0;
        }
        if(!compileCBC(cbc_file))
        {
            cout << "Error generating CBC file" << endl;
            if(clean_after_build) rc_clean();
            return 0;
        }
        cout << "RCBasic Binary Program compiled" << endl;

        //debug
        //fstream f("code.dbg", fstream::out | fstream::binary);
        //for(int i = 0; i < rc_code_segment.size(); i++)
        //    f.put(rc_code_segment[i]);
        //f.close();
        //f.open("data.dbg", fstream::out | fstream::binary);

        //for(int i = 0; i < rc_data_segment.size(); i++)
        //    f.put(rc_data_segment[i]);

        //f.close();
        //end debug
        if(clean_after_build) rc_clean();
        return 0;
    }
}


#endif // RC_VM_ASM_H_INCLUDED
