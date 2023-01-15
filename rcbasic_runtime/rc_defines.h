#define FN_FPrint 0
#define FPRINT_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Input$ 1
#define INPUT$_PROMPT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_ArrayDim 2
#define ARRAYDIM_ID num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_StringArrayDim 3
#define STRINGARRAYDIM_ID$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_NumberArrayDim 4
#define NUMBERARRAYDIM_ID num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ArraySize 5
#define ARRAYSIZE_ID num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ARRAYSIZE_ARRAY_DIM num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_StringArraySize 6
#define STRINGARRAYSIZE_ID$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define STRINGARRAYSIZE_ARRAY_DIM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumberArraySize 7
#define NUMBERARRAYSIZE_ID num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define NUMBERARRAYSIZE_ARRAY_DIM num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_Abs 8
#define ABS_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ACos 9
#define ACOS_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_AndBit 10
#define ANDBIT_A num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ANDBIT_B num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ASin 11
#define ASIN_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ATan 12
#define ATAN_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Bin$ 13
#define BIN$_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_CInt32 14
#define CINT32_I num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_CInt64 15
#define CINT64_I num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Cos 16
#define COS_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Degrees 17
#define DEGREES_R num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Exp 18
#define EXP_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Frac 19
#define FRAC_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Hex$ 20
#define HEX$_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_HexVal 21
#define HEXVAL_N$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Int 22
#define INT_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Log 23
#define LOG_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Max 24
#define MAX_A num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define MAX_B num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_Min 25
#define MIN_A num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define MIN_B num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_OrBit 26
#define ORBIT_A num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ORBIT_B num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_Radians 27
#define RADIANS_D num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Randomize 28
#define RANDOMIZE_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Rand 29
#define RAND_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Round 30
#define ROUND_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Sign 31
#define SIGN_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Sin 32
#define SIN_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Sqrt 33
#define SQRT_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Tan 34
#define TAN_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_XOrBit 35
#define XORBIT_A num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define XORBIT_B num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_Asc 36
#define ASC_C$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Chr$ 37
#define CHR$_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Insert$ 38
#define INSERT$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define INSERT$_TGT$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define INSERT$_POS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_InStr 39
#define INSTR_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define INSTR_SUBSTR$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define FN_LCase$ 40
#define LCASE$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Left$ 41
#define LEFT$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define LEFT$_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Length 42
#define LENGTH_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Len 43
#define LEN_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_LTrim$ 44
#define LTRIM$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Mid$ 45
#define MID$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define MID$_START num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define MID$_N num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ReplaceSubstr$ 46
#define REPLACESUBSTR$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define REPLACESUBSTR$_RPC$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define REPLACESUBSTR$_POS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Replace$ 47
#define REPLACE$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define REPLACE$_TGT$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define REPLACE$_RPC$ str_var[2].sid_value[0].value[ str_var[2].byref_offset ]
#define FN_Reverse$ 48
#define REVERSE$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Right$ 49
#define RIGHT$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define RIGHT$_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_RTrim$ 50
#define RTRIM$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_StringFill$ 51
#define STRINGFILL$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define STRINGFILL$_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Str$ 52
#define STR$_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Str_F$ 53
#define STR_F$_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Str_S$ 54
#define STR_S$_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Tally 55
#define TALLY_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define TALLY_SUBSTR$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define FN_Trim$ 56
#define TRIM$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_UCase$ 57
#define UCASE$_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Val 58
#define VAL_N$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Stack_N 59
#define STACK_N_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Stack_S 60
#define STACK_S_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Push_N 61
#define PUSH_N_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Pop_N 62
#define FN_Push_S 63
#define PUSH_S_S$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Pop_S$ 64
#define FN_Stack_Size_N 65
#define FN_Stack_Size_S 66
#define FN_FileOpen 67
#define FILEOPEN_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FILEOPEN_FILENAME$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FILEOPEN_MODE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_FileClose 68
#define FILECLOSE_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ReadByte 69
#define READBYTE_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WriteByte 70
#define WRITEBYTE_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WRITEBYTE_BYTE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ReadLine$ 71
#define READLINE$_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Write 72
#define WRITE_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WRITE_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_WriteLine 73
#define WRITELINE_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WRITELINE_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_CopyFile 74
#define COPYFILE_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define COPYFILE_DST$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define FN_RemoveFile 75
#define REMOVEFILE_FILENAME$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_FileExists 76
#define FILEEXISTS_FILENAME$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_MoveFile 77
#define MOVEFILE_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define MOVEFILE_DST$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define FN_RenameFile 78
#define RENAMEFILE_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define RENAMEFILE_DST$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define FN_FileLength 79
#define FILELENGTH_FILENAME$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Tell 80
#define TELL_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Seek 81
#define SEEK_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SEEK_POS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_EOF 82
#define EOF_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_FreeFile 83
#define FN_ChangeDir 84
#define CHANGEDIR_P$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_DirExists 85
#define DIREXISTS_P$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_DirFirst$ 86
#define FN_Dir$ 87
#define FN_DirNext$ 88
#define FN_MakeDir 89
#define MAKEDIR_P$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_RemoveDir 90
#define REMOVEDIR_P$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Date$ 91
#define FN_Easter$ 92
#define EASTER$_YEAR num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Ticks 93
#define FN_Time$ 94
#define FN_Timer 95
#define FN_Wait 96
#define WAIT_M_SEC num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowOpen 97
#define WINDOWOPEN_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WINDOWOPEN_TITLE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define WINDOWOPEN_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define WINDOWOPEN_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define WINDOWOPEN_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define WINDOWOPEN_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define WINDOWOPEN_FLAG num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define WINDOWOPEN_VSYNC num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define FN_WindowClose 98
#define WINDOWCLOSE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_RaiseWindow 99
#define RAISEWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Window 100
#define WINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Update 101
#define FN_Cls 102
#define FN_SetClearColor 103
#define SETCLEARCOLOR_C num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ShowWindow 104
#define SHOWWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_HideWindow 105
#define HIDEWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetWindowTitle 106
#define SETWINDOWTITLE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWTITLE_TITLE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_WindowTitle$ 107
#define WINDOWTITLE$_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetWindowPosition 108
#define SETWINDOWPOSITION_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWPOSITION_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETWINDOWPOSITION_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetWindowPosition 109
#define GETWINDOWPOSITION_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETWINDOWPOSITION_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETWINDOWPOSITION_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SetWindowSize 110
#define SETWINDOWSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETWINDOWSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetWindowSize 111
#define GETWINDOWSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETWINDOWSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETWINDOWSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SetWindowMinSize 112
#define SETWINDOWMINSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWMINSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETWINDOWMINSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetWindowMinSize 113
#define GETWINDOWMINSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETWINDOWMINSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETWINDOWMINSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SetWindowMaxSize 114
#define SETWINDOWMAXSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWMAXSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETWINDOWMAXSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetWindowMaxSize 115
#define GETWINDOWMAXSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETWINDOWMAXSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETWINDOWMAXSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_WindowIsFullscreen 116
#define WINDOWISFULLSCREEN_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowIsVisible 117
#define WINDOWISVISIBLE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowIsBordered 118
#define WINDOWISBORDERED_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowIsResizable 119
#define WINDOWISRESIZABLE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowIsMinimized 120
#define WINDOWISMINIMIZED_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowIsMaximized 121
#define WINDOWISMAXIMIZED_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowHasInputFocus 122
#define WINDOWHASINPUTFOCUS_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowHasMouseFocus 123
#define WINDOWHASMOUSEFOCUS_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetWindowFullscreen 124
#define SETWINDOWFULLSCREEN_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWFULLSCREEN_FLAG num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_MaximizeWindow 125
#define MAXIMIZEWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_MinimizeWindow 126
#define MINIMIZEWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetWindowBorder 127
#define SETWINDOWBORDER_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWBORDER_FLAG num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_WindowClip 128
#define WINDOWCLIP_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WINDOWCLIP_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define WINDOWCLIP_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define WINDOWCLIP_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define WINDOWCLIP_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_WindowExists 129
#define WINDOWEXISTS_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumWindows 130
#define FN_WindowEvent_Close 131
#define WINDOWEVENT_CLOSE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowEvent_Maximize 132
#define WINDOWEVENT_MAXIMIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowEvent_Minimize 133
#define WINDOWEVENT_MINIMIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ActiveWindow 134
#define FN_FPS 135
#define FN_SetWindowIcon 136
#define SETWINDOWICON_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWICON_SLOT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasOpen 137
#define CANVASOPEN_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define CANVASOPEN_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define CANVASOPEN_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define CANVASOPEN_VIEWPORT_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define CANVASOPEN_VIEWPORT_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define CANVASOPEN_VIEWPORT_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define CANVASOPEN_VIEWPORT_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define CANVASOPEN_MODE num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define FN_CanvasClose 138
#define CANVASCLOSE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetCanvasVisible 139
#define SETCANVASVISIBLE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASVISIBLE_FLAG num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasIsVisible 140
#define CANVASISVISIBLE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetCanvasViewport 141
#define SETCANVASVIEWPORT_CNUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASVIEWPORT_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETCANVASVIEWPORT_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define SETCANVASVIEWPORT_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define SETCANVASVIEWPORT_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_GetCanvasViewport 142
#define GETCANVASVIEWPORT_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETCANVASVIEWPORT_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETCANVASVIEWPORT_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETCANVASVIEWPORT_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define GETCANVASVIEWPORT_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_Canvas 143
#define CANVAS_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetCanvasOffset 144
#define SETCANVASOFFSET_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASOFFSET_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETCANVASOFFSET_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetCanvasOffset 145
#define GETCANVASOFFSET_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETCANVASOFFSET_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETCANVASOFFSET_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetCanvasSize 146
#define GETCANVASSIZE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETCANVASSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETCANVASSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_ClearCanvas 147
#define FN_SetCanvasAlpha 148
#define SETCANVASALPHA_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASALPHA_A num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasAlpha 149
#define CANVASALPHA_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetCanvasBlendMode 150
#define SETCANVASBLENDMODE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASBLENDMODE_BLEND_MODE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasBlendMode 151
#define CANVASBLENDMODE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetCanvasColorMod 152
#define SETCANVASCOLORMOD_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASCOLORMOD_C num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasColorMod 153
#define CANVASCOLORMOD_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_CopyCanvas 154
#define COPYCANVAS_SRC num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define COPYCANVAS_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define COPYCANVAS_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define COPYCANVAS_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define COPYCANVAS_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define COPYCANVAS_DST num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define COPYCANVAS_DX num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define COPYCANVAS_DY num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define FN_CloneCanvas 155
#define CLONECANVAS_SRC num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define CLONECANVAS_DST num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_SetCanvasZ 156
#define SETCANVASZ_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASZ_Z num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasZ 157
#define CANVASZ_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_CanvasClip 158
#define CANVASCLIP_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define CANVASCLIP_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define CANVASCLIP_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define CANVASCLIP_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define CANVASCLIP_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define CANVASCLIP_FLAG num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define FN_ActiveCanvas 159
#define FN_Box 160
#define BOX_X1 num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define BOX_Y1 num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define BOX_X2 num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define BOX_Y2 num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_BoxFill 161
#define BOXFILL_X1 num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define BOXFILL_Y1 num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define BOXFILL_X2 num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define BOXFILL_Y2 num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_Circle 162
#define CIRCLE_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define CIRCLE_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define CIRCLE_RADIUS num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_CircleFill 163
#define CIRCLEFILL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define CIRCLEFILL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define CIRCLEFILL_RADIUS num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_Ellipse 164
#define ELLIPSE_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ELLIPSE_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define ELLIPSE_RX num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define ELLIPSE_RY num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_EllipseFill 165
#define ELLIPSEFILL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ELLIPSEFILL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define ELLIPSEFILL_RX num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define ELLIPSEFILL_RY num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_FloodFill 166
#define FLOODFILL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FLOODFILL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_GetPixel 167
#define GETPIXEL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETPIXEL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_SetColor 168
#define SETCOLOR_C num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Line 169
#define LINE_X1 num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LINE_Y1 num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define LINE_X2 num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define LINE_Y2 num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_Poly 170
#define POLY_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define POLY_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define POLY_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_PolyFill 171
#define POLYFILL_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define POLYFILL_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define POLYFILL_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_Rect 172
#define RECT_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define RECT_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define RECT_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define RECT_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_RectFill 173
#define RECTFILL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define RECTFILL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define RECTFILL_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define RECTFILL_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_RoundRect 174
#define ROUNDRECT_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ROUNDRECT_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define ROUNDRECT_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define ROUNDRECT_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define ROUNDRECT_R num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_RoundRectFill 175
#define ROUNDRECTFILL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ROUNDRECTFILL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define ROUNDRECTFILL_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define ROUNDRECTFILL_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define ROUNDRECTFILL_R num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_RGB 176
#define RGB_R num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define RGB_G num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define RGB_B num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_RGBA 177
#define RGBA_R num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define RGBA_G num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define RGBA_B num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define RGBA_A num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_PSet 178
#define PSET_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define PSET_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_LoadImage 179
#define LOADIMAGE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LOADIMAGE_IMG$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_LoadImage_Ex 180
#define LOADIMAGE_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LOADIMAGE_EX_IMG$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define LOADIMAGE_EX_COLKEY num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ImageFromBuffer 181
#define IMAGEFROMBUFFER_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define IMAGEFROMBUFFER_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define IMAGEFROMBUFFER_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define IMAGEFROMBUFFER_BUFFER num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_ImageFromBuffer_Ex 182
#define IMAGEFROMBUFFER_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define IMAGEFROMBUFFER_EX_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define IMAGEFROMBUFFER_EX_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define IMAGEFROMBUFFER_EX_BUFFER num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define IMAGEFROMBUFFER_EX_COLKEY num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_BufferFromImage 183
#define BUFFERFROMIMAGE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define BUFFERFROMIMAGE_BUFFER num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ImageExists 184
#define IMAGEEXISTS_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ColorKey 185
#define COLORKEY_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define COLORKEY_C num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CopyImage 186
#define COPYIMAGE_SRC num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define COPYIMAGE_DST num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_DeleteImage 187
#define DELETEIMAGE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetImageAlpha 188
#define SETIMAGEALPHA_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETIMAGEALPHA_A num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ImageAlpha 189
#define IMAGEALPHA_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_GetImageSize 190
#define GETIMAGESIZE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETIMAGESIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETIMAGESIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SetImageBlendMode 191
#define SETIMAGEBLENDMODE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETIMAGEBLENDMODE_BLEND_MODE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ImageBlendMode 192
#define IMAGEBLENDMODE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetImageColorMod 193
#define SETIMAGECOLORMOD_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETIMAGECOLORMOD_C num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ImageColorMod 194
#define IMAGECOLORMOD_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_DrawImage 195
#define DRAWIMAGE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_DrawImage_Blit 196
#define DRAWIMAGE_BLIT_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_BLIT_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_BLIT_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_BLIT_SRC_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_BLIT_SRC_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_BLIT_SRC_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_BLIT_SRC_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define FN_DrawImage_Blit_Ex 197
#define DRAWIMAGE_BLIT_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_BLIT_EX_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_BLIT_EX_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_BLIT_EX_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_BLIT_EX_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_BLIT_EX_SRC_X num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_BLIT_EX_SRC_Y num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define DRAWIMAGE_BLIT_EX_SRC_W num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define DRAWIMAGE_BLIT_EX_SRC_H num_var[8].nid_value[0].value[ num_var[8].byref_offset ]
#define FN_DrawImage_Rotate 198
#define DRAWIMAGE_ROTATE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ROTATE_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ROTATE_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ROTATE_ANGLE num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_DrawImage_Rotate_Ex 199
#define DRAWIMAGE_ROTATE_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_SRC_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_SRC_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_SRC_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_SRC_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_ANGLE num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define FN_DrawImage_Zoom 200
#define DRAWIMAGE_ZOOM_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ZOOM_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ZOOM_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ZOOM_ZX num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_ZOOM_ZY num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_DrawImage_Zoom_Ex 201
#define DRAWIMAGE_ZOOM_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_SRC_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_SRC_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_SRC_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_SRC_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_ZX num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_ZY num_var[8].nid_value[0].value[ num_var[8].byref_offset ]
#define FN_DrawImage_Rotozoom 202
#define DRAWIMAGE_ROTOZOOM_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_ANGLE num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_ZX num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_ZY num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define FN_DrawImage_Rotozoom_Ex 203
#define DRAWIMAGE_ROTOZOOM_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_EX_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_EX_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_EX_SRC_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_EX_SRC_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_EX_SRC_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_EX_SRC_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_EX_ANGLE num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_EX_ZX num_var[8].nid_value[0].value[ num_var[8].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_EX_ZY num_var[9].nid_value[0].value[ num_var[9].byref_offset ]
#define FN_DrawImage_Flip 204
#define DRAWIMAGE_FLIP_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_FLIP_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_FLIP_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_FLIP_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_FLIP_V num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_DrawImage_Flip_Ex 205
#define DRAWIMAGE_FLIP_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_FLIP_EX_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_FLIP_EX_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_FLIP_EX_SRC_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_FLIP_EX_SRC_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_FLIP_EX_SRC_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_FLIP_EX_SRC_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define DRAWIMAGE_FLIP_EX_H num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define DRAWIMAGE_FLIP_EX_V num_var[8].nid_value[0].value[ num_var[8].byref_offset ]
#define FN_InKey 206
#define FN_Key 207
#define KEY_KEY_CODE num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WaitKey 208
#define FN_HideMouse 209
#define FN_ShowMouse 210
#define FN_MouseIsVisible 211
#define FN_GetMouse 212
#define GETMOUSE_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETMOUSE_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETMOUSE_MB1 num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETMOUSE_MB2 num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define GETMOUSE_MB3 num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_MouseX 213
#define FN_MouseY 214
#define FN_MouseButton 215
#define MOUSEBUTTON_MB num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_GetMouseWheel 216
#define GETMOUSEWHEEL_X_AXIS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETMOUSEWHEEL_Y_AXIS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_MouseWheelX 217
#define FN_MouseWheelY 218
#define FN_SoundFromBuffer 219
#define SOUNDFROMBUFFER_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SOUNDFROMBUFFER_BUFFER num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SOUNDFROMBUFFER_BUFFER_SIZE num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define SOUNDFROMBUFFER_VOL num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_LoadSound 220
#define LOADSOUND_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LOADSOUND_SND_FILE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_LoadMusic 221
#define LOADMUSIC_MUSIC_FILE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_PlaySound 222
#define PLAYSOUND_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define PLAYSOUND_CHANNEL num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define PLAYSOUND_LOOPS num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_PlaySoundTimed 223
#define PLAYSOUNDTIMED_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define PLAYSOUNDTIMED_CHANNEL num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define PLAYSOUNDTIMED_LOOPS num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define PLAYSOUNDTIMED_MS num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_PlayMusic 224
#define PLAYMUSIC_MLOOPS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_PauseSound 225
#define PAUSESOUND_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ResumeSound 226
#define RESUMESOUND_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_PauseMusic 227
#define FN_ResumeMusic 228
#define FN_DeleteSound 229
#define DELETESOUND_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_DeleteMusic 230
#define FN_FadeMusicIn 231
#define FADEMUSICIN_FADE_TIME num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FADEMUSICIN_LOOPS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_FadeMusicOut 232
#define FADEMUSICOUT_FADE_TIME num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_MusicExists 233
#define FN_SetMusicVolume 234
#define SETMUSICVOLUME_VOL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_MusicVolume 235
#define FN_SetMusicPosition 236
#define SETMUSICPOSITION_POS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_MusicPosition 237
#define FN_RewindMusic 238
#define FN_SetSoundChannels 239
#define SETSOUNDCHANNELS_MAX_CHANNELS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumSoundChannels 240
#define FN_SoundIsEnabled 241
#define FN_SoundExists 242
#define SOUNDEXISTS_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetChannelVolume 243
#define SETCHANNELVOLUME_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCHANNELVOLUME_VOL num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ChannelVolume 244
#define CHANNELVOLUME_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetSoundVolume 245
#define SETSOUNDVOLUME_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETSOUNDVOLUME_VOL num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_SoundVolume 246
#define SOUNDVOLUME_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_StopMusic 247
#define FN_StopSound 248
#define STOPSOUND_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetChannelPanning 249
#define SETCHANNELPANNING_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCHANNELPANNING_LEFT_VALUE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETCHANNELPANNING_RIGHT_VALUE num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SetChannelDistance 250
#define SETCHANNELDISTANCE_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCHANNELDISTANCE_DIST_VALUE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ChannelIsPlaying 251
#define CHANNELISPLAYING_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ChannelIsPaused 252
#define CHANNELISPAUSED_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumJoysticks 253
#define FN_NumJoyAxes 254
#define NUMJOYAXES_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumJoyButtons 255
#define NUMJOYBUTTONS_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumJoyHats 256
#define NUMJOYHATS_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumJoyTrackBalls 257
#define NUMJOYTRACKBALLS_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_JoyAxis 258
#define JOYAXIS_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define JOYAXIS_JOY_AXIS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_JoyButton 259
#define JOYBUTTON_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define JOYBUTTON_JOY_BUTTON num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_JoyHat 260
#define JOYHAT_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define JOYHAT_JOY_HAT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_GetJoyTrackBall 261
#define GETJOYTRACKBALL_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETJOYTRACKBALL_BALL num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETJOYTRACKBALL_DX num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETJOYTRACKBALL_DY num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_JoyName$ 262
#define JOYNAME$_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_JoystickIsConnected 263
#define JOYSTICKISCONNECTED_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_GetCursor 264
#define GETCURSOR_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETCURSOR_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_PrintS 265
#define PRINTS_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_InputS$ 266
#define INPUTS$_PROMPT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_ZoneInputS$ 267
#define ZONEINPUTS$_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ZONEINPUTS$_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define ZONEINPUTS$_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define ZONEINPUTS$_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_Locate 268
#define LOCATE_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LOCATE_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ReadInput_Start 269
#define FN_ReadInput_Stop 270
#define FN_ReadInput_Text$ 271
#define FN_ReadInput_SetText 272
#define READINPUT_SETTEXT_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_ReadInput_ToggleBackspace 273
#define READINPUT_TOGGLEBACKSPACE_FLAG num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_LoadFont 274
#define LOADFONT_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LOADFONT_FNT_FILE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define LOADFONT_SIZE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_DeleteFont 275
#define DELETEFONT_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_FontIsLoaded 276
#define FONTISLOADED_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Font 277
#define FONT_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetFontStyle 278
#define SETFONTSTYLE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETFONTSTYLE_STYLE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_DrawText 279
#define DRAWTEXT_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define DRAWTEXT_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWTEXT_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_DrawText_Shaded 280
#define DRAWTEXT_SHADED_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define DRAWTEXT_SHADED_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWTEXT_SHADED_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWTEXT_SHADED_FG_COLOR num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWTEXT_SHADED_BG_COLOR num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_DrawText_Blended 281
#define DRAWTEXT_BLENDED_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define DRAWTEXT_BLENDED_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWTEXT_BLENDED_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_RenderText 282
#define RENDERTEXT_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define RENDERTEXT_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_GetTextSize 283
#define GETTEXTSIZE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETTEXTSIZE_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define GETTEXTSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETTEXTSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_TouchPressure 284
#define FN_GetTouch 285
#define GETTOUCH_STATUS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETTOUCH_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETTOUCH_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETTOUCH_DX num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define GETTOUCH_DY num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_GetMultiTouch 286
#define GETMULTITOUCH_STATUS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETMULTITOUCH_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETMULTITOUCH_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETMULTITOUCH_FINGERS num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define GETMULTITOUCH_DIST num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define GETMULTITOUCH_THETA num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define FN_GetTouchFinger 287
#define GETTOUCHFINGER_FINGER num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETTOUCHFINGER_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETTOUCHFINGER_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETTOUCHFINGER_PRESSURE num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_NumFingers 288
#define FN_CheckSockets 289
#define CHECKSOCKETS_TIMEOUT_MS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_TCP_SocketReady 290
#define TCP_SOCKETREADY_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_UDP_SocketReady 291
#define UDP_SOCKETREADY_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_TCP_SocketOpen 292
#define TCP_SOCKETOPEN_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define TCP_SOCKETOPEN_HOST$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define TCP_SOCKETOPEN_PORT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_TCP_SocketClose 293
#define TCP_SOCKETCLOSE_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_TCP_RemoteHost 294
#define TCP_REMOTEHOST_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_TCP_RemotePort 295
#define TCP_REMOTEPORT_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_TCP_GetData 296
#define TCP_GETDATA_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define TCP_GETDATA_SDATA$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define TCP_GETDATA_NUMBYTES num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_TCP_SendData 297
#define TCP_SENDDATA_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define TCP_SENDDATA_SDATA$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_TCP_AcceptSocket 298
#define TCP_ACCEPTSOCKET_SERVER num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define TCP_ACCEPTSOCKET_CLIENT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_UDP_SocketOpen 299
#define UDP_SOCKETOPEN_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define UDP_SOCKETOPEN_PORT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_UDP_SocketClose 300
#define UDP_SOCKETCLOSE_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_UDP_GetData 301
#define UDP_GETDATA_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define UDP_GETDATA_SDATA$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define UDP_GETDATA_HOST$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define UDP_GETDATA_PORT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_UDP_Length 302
#define FN_UDP_MaxLength 303
#define FN_UDP_RemoteHost$ 304
#define UDP_REMOTEHOST$_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_UDP_RemotePort 305
#define UDP_REMOTEPORT_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_UDP_SendData 306
#define UDP_SENDDATA_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define UDP_SENDDATA_SDATA$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define UDP_SENDDATA_HOST$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define UDP_SENDDATA_PORT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_LoadVideo 307
#define LOADVIDEO_VID$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_PlayVideo 308
#define PLAYVIDEO_VLOOPS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_PauseVideo 309
#define FN_StopVideo 310
#define FN_SetVideoPosition 311
#define SETVIDEOPOSITION_POS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ResumeVideo 312
#define FN_VideoPosition 313
#define FN_DeleteVideo 314
#define FN_VideoIsPlaying 315
#define FN_VideoEnd 316
#define FN_GetVideoStats 317
#define GETVIDEOSTATS_VFILE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define GETVIDEOSTATS_VLEN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETVIDEOSTATS_VFPS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETVIDEOSTATS_FRAME_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETVIDEOSTATS_FRAME_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_SetVideoDrawRect 318
#define SETVIDEODRAWRECT_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETVIDEODRAWRECT_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETVIDEODRAWRECT_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define SETVIDEODRAWRECT_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_GetVideoDrawRect 319
#define GETVIDEODRAWRECT_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETVIDEODRAWRECT_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETVIDEODRAWRECT_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETVIDEODRAWRECT_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_GetVideoSize 320
#define GETVIDEOSIZE_W num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETVIDEOSIZE_H num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_VideoExists 321
#define FN_SetVideoAlpha 322
#define SETVIDEOALPHA_A num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_System 323
#define SYSTEM_CMD$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_OS$ 324
#define FN_Command$ 325
#define COMMAND$_ARG num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumCommands 326
#define FN_Env$ 327
#define ENV$_V$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_SetEnv 328
#define SETENV_VAR$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define SETENV_VALUE$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define SETENV_OVERWRITE num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_PrefPath$ 329
#define PREFPATH$_ORG_NAME$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define PREFPATH$_APP_NAME$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define FN_Android_GetExternalStoragePath$ 330
#define FN_Android_GetExternalStorageState 331
#define FN_Android_GetInternalStoragePath$ 332
#define FN_Android_JNI_Message$ 333
#define ANDROID_JNI_MESSAGE$_ARG$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Runtime_Utility_Message$ 334
#define RUNTIME_UTILITY_MESSAGE$_ARG$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_ClipboardText$ 335
#define FN_SetClipboardText 336
#define SETCLIPBOARDTEXT_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_HasClipboardText 337
#define FN_GetDesktopDisplayMode 338
#define GETDESKTOPDISPLAYMODE_INDEX num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETDESKTOPDISPLAYMODE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETDESKTOPDISPLAYMODE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETDESKTOPDISPLAYMODE_FREQ num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_DrawImage_Transform 339
#define DRAWIMAGE_TRANSFORM_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_TRANSFORM_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_TRANSFORM_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_TRANSFORM_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_TRANSFORM_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_TRANSFORM_SRC_X num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_TRANSFORM_SRC_Y num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define DRAWIMAGE_TRANSFORM_SRC_W num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define DRAWIMAGE_TRANSFORM_SRC_H num_var[8].nid_value[0].value[ num_var[8].byref_offset ]
#define DRAWIMAGE_TRANSFORM_ANGLE num_var[9].nid_value[0].value[ num_var[9].byref_offset ]
#define DRAWIMAGE_TRANSFORM_CENTER_X num_var[10].nid_value[0].value[ num_var[10].byref_offset ]
#define DRAWIMAGE_TRANSFORM_CENTER_Y num_var[11].nid_value[0].value[ num_var[11].byref_offset ]
#define DRAWIMAGE_TRANSFORM_FLIP_H num_var[12].nid_value[0].value[ num_var[12].byref_offset ]
#define DRAWIMAGE_TRANSFORM_FLIP_V num_var[13].nid_value[0].value[ num_var[13].byref_offset ]
#define FN_GetPowerInfo 340
#define GETPOWERINFO_STATUS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETPOWERINFO_SECS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETPOWERINFO_PCT num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SystemRam 341
#define FN_SetRenderScaleQuality 342
#define SETRENDERSCALEQUALITY_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_EvalJS$ 343
#define EVALJS$_JS_CODE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_GetRenderScaleQuality 344
#define FN_GetGlobalMouse 345
#define GETGLOBALMOUSE_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETGLOBALMOUSE_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETGLOBALMOUSE_MB1 num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETGLOBALMOUSE_MB2 num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define GETGLOBALMOUSE_MB3 num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_GlobalMouseX 346
#define FN_GlobalMouseY 347
#define FN_GetAccel 348
#define GETACCEL_ACCEL_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETACCEL_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETACCEL_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETACCEL_Z num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_AccelName$ 349
#define ACCELNAME$_ACCEL_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumAccels 350
#define FN_GetGyro 351
#define GETGYRO_GYRO_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETGYRO_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETGYRO_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETGYRO_Z num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_GyroName$ 352
#define GYRONAME$_GYRO_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumGyros 353
#define FN_JoyRumblePlay 354
#define JOYRUMBLEPLAY_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define JOYRUMBLEPLAY_STRENGTH num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define JOYRUMBLEPLAY_DURATION num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_JoyRumbleStop 355
#define JOYRUMBLESTOP_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_JoystickIsHaptic 356
#define JOYSTICKISHAPTIC_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WriteByteBuffer 357
#define WRITEBYTEBUFFER_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WRITEBYTEBUFFER_BUF num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define WRITEBYTEBUFFER_BUF_SIZE num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_ReadByteBuffer 358
#define READBYTEBUFFER_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define READBYTEBUFFER_BUF num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define READBYTEBUFFER_BUF_SIZE num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_WindowEvent_Resize 359
#define WINDOWEVENT_RESIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetWindowAutoClose 360
#define SETWINDOWAUTOCLOSE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWAUTOCLOSE_EXIT_ON_CLOSE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_SetWindowResizable 361
#define SETWINDOWRESIZABLE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWRESIZABLE_FLAG num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_SystemReturnStdOut$ 362
#define SYSTEMRETURNSTDOUT$_CMD$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_WindowMode 363
#define WINDOWMODE_VISIBLE num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WINDOWMODE_FULLSCREEN num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define WINDOWMODE_RESIZABLE num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define WINDOWMODE_BORDERLESS num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define WINDOWMODE_HIGHDPI num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_WindowFlags 364
#define WINDOWFLAGS_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_RestoreWindow 365
#define RESTOREWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_UpdateAllWindows 366
#define FN_QueryAudioSpec 367
#define QUERYAUDIOSPEC_FREQ num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define QUERYAUDIOSPEC_FORMAT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define QUERYAUDIOSPEC_CHANNELS num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_MusicIsPlaying 368
#define FN_DrawGeometry 369
#define DRAWGEOMETRY_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWGEOMETRY_NUM_VERTICES num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWGEOMETRY_VERTICES num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWGEOMETRY_NUM_INDICES num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWGEOMETRY_INDICES num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_Size 370
#define SIZE_S$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_BufferFromString 371
#define BUFFERFROMSTRING_S$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define BUFFERFROMSTRING_BUFFER num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_StringFromBuffer$ 372
#define STRINGFROMBUFFER$_BUFFER num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define STRINGFROMBUFFER$_BUFFER_SIZE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
