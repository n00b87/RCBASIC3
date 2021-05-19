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
#define FN_WriteLine 72
#define WRITELINE_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WRITELINE_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_CopyFile 73
#define COPYFILE_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define COPYFILE_DST$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define FN_RemoveFile 74
#define REMOVEFILE_FILENAME$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_FileExists 75
#define FILEEXISTS_FILENAME$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_MoveFile 76
#define MOVEFILE_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define MOVEFILE_DST$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define FN_RenameFile 77
#define RENAMEFILE_SRC$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define RENAMEFILE_DST$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define FN_FileLength 78
#define FILELENGTH_FILENAME$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Tell 79
#define TELL_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Seek 80
#define SEEK_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SEEK_POS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_EOF 81
#define EOF_STREAM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_FreeFile 82
#define FN_ChangeDir 83
#define CHANGEDIR_P$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_DirExists 84
#define DIREXISTS_P$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_DirFirst$ 85
#define FN_Dir$ 86
#define FN_DirNext$ 87
#define FN_MakeDir 88
#define MAKEDIR_P$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_RemoveDir 89
#define REMOVEDIR_P$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_Date$ 90
#define FN_Easter$ 91
#define EASTER$_YEAR num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Ticks 92
#define FN_Time$ 93
#define FN_Timer 94
#define FN_Wait 95
#define WAIT_M_SEC num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowOpen 96
#define WINDOWOPEN_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WINDOWOPEN_TITLE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define WINDOWOPEN_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define WINDOWOPEN_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define WINDOWOPEN_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define WINDOWOPEN_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define WINDOWOPEN_FLAG num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define FN_WindowClose 97
#define WINDOWCLOSE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_RaiseWindow 98
#define RAISEWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Window 99
#define WINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Update 100
#define FN_Cls 101
#define FN_SetClearColor 102
#define SETCLEARCOLOR_C num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ShowWindow 103
#define SHOWWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_HideWindow 104
#define HIDEWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetWindowTitle 105
#define SETWINDOWTITLE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWTITLE_TITLE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_WindowTitle$ 106
#define WINDOWTITLE$_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetWindowPosition 107
#define SETWINDOWPOSITION_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWPOSITION_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETWINDOWPOSITION_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetWindowPosition 108
#define GETWINDOWPOSITION_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETWINDOWPOSITION_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETWINDOWPOSITION_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SetWindowSize 109
#define SETWINDOWSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETWINDOWSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetWindowSize 110
#define GETWINDOWSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETWINDOWSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETWINDOWSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SetWindowMinSize 111
#define SETWINDOWMINSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWMINSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETWINDOWMINSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetWindowMinSize 112
#define GETWINDOWMINSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETWINDOWMINSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETWINDOWMINSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SetWindowMaxSize 113
#define SETWINDOWMAXSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWMAXSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETWINDOWMAXSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetWindowMaxSize 114
#define GETWINDOWMAXSIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETWINDOWMAXSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETWINDOWMAXSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_WindowIsFullscreen 115
#define WINDOWISFULLSCREEN_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowIsVisible 116
#define WINDOWISVISIBLE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowIsBordered 117
#define WINDOWISBORDERED_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowIsResizable 118
#define WINDOWISRESIZABLE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowIsMinimized 119
#define WINDOWISMINIMIZED_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowIsMaximized 120
#define WINDOWISMAXIMIZED_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowHasInputFocus 121
#define WINDOWHASINPUTFOCUS_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowHasMouseFocus 122
#define WINDOWHASMOUSEFOCUS_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetWindowFullscreen 123
#define SETWINDOWFULLSCREEN_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWFULLSCREEN_FLAG num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_MaximizeWindow 124
#define MAXIMIZEWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_MinimizeWindow 125
#define MINIMIZEWINDOW_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetWindowBorder 126
#define SETWINDOWBORDER_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWBORDER_FLAG num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_WindowClip 127
#define WINDOWCLIP_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WINDOWCLIP_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define WINDOWCLIP_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define WINDOWCLIP_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define WINDOWCLIP_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_WindowExists 128
#define WINDOWEXISTS_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumWindows 129
#define FN_WindowEvent_Close 130
#define WINDOWEVENT_CLOSE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowEvent_Maximize 131
#define WINDOWEVENT_MAXIMIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WindowEvent_Minimize 132
#define WINDOWEVENT_MINIMIZE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ActiveWindow 133
#define FN_FPS 134
#define FN_SetWindowIcon 135
#define SETWINDOWICON_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETWINDOWICON_SLOT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasOpen 136
#define CANVASOPEN_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define CANVASOPEN_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define CANVASOPEN_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define CANVASOPEN_VIEWPORT_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define CANVASOPEN_VIEWPORT_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define CANVASOPEN_VIEWPORT_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define CANVASOPEN_VIEWPORT_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define CANVASOPEN_MODE num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define FN_CanvasClose 137
#define CANVASCLOSE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetCanvasVisible 138
#define SETCANVASVISIBLE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASVISIBLE_FLAG num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasIsVisible 139
#define CANVASISVISIBLE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetCanvasViewport 140
#define SETCANVASVIEWPORT_CNUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASVIEWPORT_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETCANVASVIEWPORT_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define SETCANVASVIEWPORT_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define SETCANVASVIEWPORT_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_GetCanvasViewport 141
#define GETCANVASVIEWPORT_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETCANVASVIEWPORT_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETCANVASVIEWPORT_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETCANVASVIEWPORT_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define GETCANVASVIEWPORT_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_Canvas 142
#define CANVAS_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetCanvasOffset 143
#define SETCANVASOFFSET_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASOFFSET_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETCANVASOFFSET_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetCanvasOffset 144
#define GETCANVASOFFSET_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETCANVASOFFSET_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETCANVASOFFSET_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_GetCanvasSize 145
#define GETCANVASSIZE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETCANVASSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETCANVASSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_ClearCanvas 146
#define FN_SetCanvasAlpha 147
#define SETCANVASALPHA_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASALPHA_A num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasAlpha 148
#define CANVASALPHA_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetCanvasBlendMode 149
#define SETCANVASBLENDMODE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASBLENDMODE_BLEND_MODE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasBlendMode 150
#define CANVASBLENDMODE_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetCanvasColorMod 151
#define SETCANVASCOLORMOD_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASCOLORMOD_C num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasColorMod 152
#define CANVASCOLORMOD_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_CopyCanvas 153
#define COPYCANVAS_SRC num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define COPYCANVAS_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define COPYCANVAS_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define COPYCANVAS_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define COPYCANVAS_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define COPYCANVAS_DST num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define COPYCANVAS_DX num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define COPYCANVAS_DY num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define FN_CloneCanvas 154
#define CLONECANVAS_SRC num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define CLONECANVAS_DST num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_SetCanvasZ 155
#define SETCANVASZ_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCANVASZ_Z num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CanvasZ 156
#define CANVASZ_C_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_CanvasClip 157
#define CANVASCLIP_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define CANVASCLIP_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define CANVASCLIP_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define CANVASCLIP_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define CANVASCLIP_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define CANVASCLIP_FLAG num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define FN_ActiveCanvas 158
#define FN_Box 159
#define BOX_X1 num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define BOX_Y1 num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define BOX_X2 num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define BOX_Y2 num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_BoxFill 160
#define BOXFILL_X1 num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define BOXFILL_Y1 num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define BOXFILL_X2 num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define BOXFILL_Y2 num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_Circle 161
#define CIRCLE_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define CIRCLE_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define CIRCLE_RADIUS num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_CircleFill 162
#define CIRCLEFILL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define CIRCLEFILL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define CIRCLEFILL_RADIUS num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_Ellipse 163
#define ELLIPSE_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ELLIPSE_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define ELLIPSE_RX num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define ELLIPSE_RY num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_EllipseFill 164
#define ELLIPSEFILL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ELLIPSEFILL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define ELLIPSEFILL_RX num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define ELLIPSEFILL_RY num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_FloodFill 165
#define FLOODFILL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FLOODFILL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_GetPixel 166
#define GETPIXEL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETPIXEL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_SetColor 167
#define SETCOLOR_C num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Line 168
#define LINE_X1 num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LINE_Y1 num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define LINE_X2 num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define LINE_Y2 num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_Poly 169
#define POLY_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define POLY_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define POLY_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_PolyFill 170
#define POLYFILL_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define POLYFILL_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define POLYFILL_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_Rect 171
#define RECT_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define RECT_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define RECT_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define RECT_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_RectFill 172
#define RECTFILL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define RECTFILL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define RECTFILL_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define RECTFILL_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_RoundRect 173
#define ROUNDRECT_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ROUNDRECT_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define ROUNDRECT_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define ROUNDRECT_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define ROUNDRECT_R num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_RoundRectFill 174
#define ROUNDRECTFILL_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ROUNDRECTFILL_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define ROUNDRECTFILL_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define ROUNDRECTFILL_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define ROUNDRECTFILL_R num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_RGB 175
#define RGB_R num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define RGB_G num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define RGB_B num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_RGBA 176
#define RGBA_R num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define RGBA_G num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define RGBA_B num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define RGBA_A num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_PSet 177
#define PSET_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define PSET_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_LoadImage 178
#define LOADIMAGE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LOADIMAGE_IMG$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_LoadImage_Ex 179
#define LOADIMAGE_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LOADIMAGE_EX_IMG$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define LOADIMAGE_EX_COLKEY num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ImageFromBuffer 180
#define IMAGEFROMBUFFER_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define IMAGEFROMBUFFER_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define IMAGEFROMBUFFER_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define IMAGEFROMBUFFER_BUFFER num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_ImageFromBuffer_Ex 181
#define IMAGEFROMBUFFER_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define IMAGEFROMBUFFER_EX_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define IMAGEFROMBUFFER_EX_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define IMAGEFROMBUFFER_EX_BUFFER num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define IMAGEFROMBUFFER_EX_COLKEY num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_BufferFromImage 182
#define BUFFERFROMIMAGE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define BUFFERFROMIMAGE_BUFFER num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ImageExists 183
#define IMAGEEXISTS_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ColorKey 184
#define COLORKEY_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define COLORKEY_C num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_CopyImage 185
#define COPYIMAGE_SRC num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define COPYIMAGE_DST num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_DeleteImage 186
#define DELETEIMAGE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetImageAlpha 187
#define SETIMAGEALPHA_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETIMAGEALPHA_A num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ImageAlpha 188
#define IMAGEALPHA_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_GetImageSize 189
#define GETIMAGESIZE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETIMAGESIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETIMAGESIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SetImageBlendMode 190
#define SETIMAGEBLENDMODE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETIMAGEBLENDMODE_BLEND_MODE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ImageBlendMode 191
#define IMAGEBLENDMODE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetImageColorMod 192
#define SETIMAGECOLORMOD_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETIMAGECOLORMOD_C num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ImageColorMod 193
#define IMAGECOLORMOD_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_DrawImage 194
#define DRAWIMAGE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_DrawImage_Blit 195
#define DRAWIMAGE_BLIT_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_BLIT_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_BLIT_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_BLIT_SRC_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_BLIT_SRC_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_BLIT_SRC_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_BLIT_SRC_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define FN_DrawImage_Blit_Ex 196
#define DRAWIMAGE_BLIT_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_BLIT_EX_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_BLIT_EX_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_BLIT_EX_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_BLIT_EX_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_BLIT_EX_SRC_X num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_BLIT_EX_SRC_Y num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define DRAWIMAGE_BLIT_EX_SRC_W num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define DRAWIMAGE_BLIT_EX_SRC_H num_var[8].nid_value[0].value[ num_var[8].byref_offset ]
#define FN_DrawImage_Rotate 197
#define DRAWIMAGE_ROTATE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ROTATE_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ROTATE_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ROTATE_ANGLE num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_DrawImage_Rotate_Ex 198
#define DRAWIMAGE_ROTATE_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_SRC_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_SRC_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_SRC_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_SRC_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define DRAWIMAGE_ROTATE_EX_ANGLE num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define FN_DrawImage_Zoom 199
#define DRAWIMAGE_ZOOM_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ZOOM_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ZOOM_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ZOOM_ZX num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_ZOOM_ZY num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_DrawImage_Zoom_Ex 200
#define DRAWIMAGE_ZOOM_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_SRC_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_SRC_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_SRC_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_SRC_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_ZX num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define DRAWIMAGE_ZOOM_EX_ZY num_var[8].nid_value[0].value[ num_var[8].byref_offset ]
#define FN_DrawImage_Rotozoom 201
#define DRAWIMAGE_ROTOZOOM_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_ANGLE num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_ZX num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_ROTOZOOM_ZY num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define FN_DrawImage_Rotozoom_Ex 202
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
#define FN_DrawImage_Flip 203
#define DRAWIMAGE_FLIP_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_FLIP_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_FLIP_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_FLIP_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_FLIP_V num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_DrawImage_Flip_Ex 204
#define DRAWIMAGE_FLIP_EX_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWIMAGE_FLIP_EX_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWIMAGE_FLIP_EX_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWIMAGE_FLIP_EX_SRC_X num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define DRAWIMAGE_FLIP_EX_SRC_Y num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define DRAWIMAGE_FLIP_EX_SRC_W num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define DRAWIMAGE_FLIP_EX_SRC_H num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
#define DRAWIMAGE_FLIP_EX_H num_var[7].nid_value[0].value[ num_var[7].byref_offset ]
#define DRAWIMAGE_FLIP_EX_V num_var[8].nid_value[0].value[ num_var[8].byref_offset ]
#define FN_InKey 205
#define FN_Key 206
#define KEY_KEY_CODE num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_WaitKey 207
#define FN_HideMouse 208
#define FN_ShowMouse 209
#define FN_MouseIsVisible 210
#define FN_GetMouse 211
#define GETMOUSE_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETMOUSE_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETMOUSE_MB1 num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETMOUSE_MB2 num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define GETMOUSE_MB3 num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_MouseX 212
#define FN_MouseY 213
#define FN_MouseButton 214
#define MOUSEBUTTON_MB num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_GetMouseWheel 215
#define GETMOUSEWHEEL_X_AXIS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETMOUSEWHEEL_Y_AXIS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_MouseWheelX 216
#define FN_MouseWheelY 217
#define FN_SoundFromBuffer 218
#define SOUNDFROMBUFFER_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SOUNDFROMBUFFER_BUFFER num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SOUNDFROMBUFFER_BUFFER_SIZE num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define SOUNDFROMBUFFER_VOL num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_LoadSound 219
#define LOADSOUND_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LOADSOUND_SND_FILE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_LoadMusic 220
#define LOADMUSIC_MUSIC_FILE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_PlaySound 221
#define PLAYSOUND_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define PLAYSOUND_CHANNEL num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define PLAYSOUND_LOOPS num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_PlaySoundTimed 222
#define PLAYSOUNDTIMED_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define PLAYSOUNDTIMED_CHANNEL num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define PLAYSOUNDTIMED_LOOPS num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define PLAYSOUNDTIMED_MS num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_PlayMusic 223
#define PLAYMUSIC_MLOOPS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_PauseSound 224
#define PAUSESOUND_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ResumeSound 225
#define RESUMESOUND_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_PauseMusic 226
#define FN_ResumeMusic 227
#define FN_DeleteSound 228
#define DELETESOUND_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_DeleteMusic 229
#define FN_FadeMusicIn 230
#define FADEMUSICIN_FADE_TIME num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FADEMUSICIN_LOOPS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_FadeMusicOut 231
#define FADEMUSICOUT_FADE_TIME num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_MusicExists 232
#define FN_SetMusicVolume 233
#define SETMUSICVOLUME_VOL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_MusicVolume 234
#define FN_SetMusicPosition 235
#define SETMUSICPOSITION_POS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_MusicPosition 236
#define FN_RewindMusic 237
#define FN_SetSoundChannels 238
#define SETSOUNDCHANNELS_MAX_CHANNELS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumSoundChannels 239
#define FN_SoundIsEnabled 240
#define FN_SoundExists 241
#define SOUNDEXISTS_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetChannelVolume 242
#define SETCHANNELVOLUME_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCHANNELVOLUME_VOL num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ChannelVolume 243
#define CHANNELVOLUME_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetSoundVolume 244
#define SETSOUNDVOLUME_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETSOUNDVOLUME_VOL num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_SoundVolume 245
#define SOUNDVOLUME_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_StopMusic 246
#define FN_StopSound 247
#define STOPSOUND_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetChannelPanning 248
#define SETCHANNELPANNING_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCHANNELPANNING_LEFT_VALUE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETCHANNELPANNING_RIGHT_VALUE num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SetChannelDistance 249
#define SETCHANNELDISTANCE_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETCHANNELDISTANCE_DIST_VALUE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ChannelIsPlaying 250
#define CHANNELISPLAYING_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ChannelIsPaused 251
#define CHANNELISPAUSED_CHANNEL num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumJoysticks 252
#define FN_NumJoyAxes 253
#define NUMJOYAXES_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumJoyButtons 254
#define NUMJOYBUTTONS_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumJoyHats 255
#define NUMJOYHATS_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumJoyTrackBalls 256
#define NUMJOYTRACKBALLS_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_JoyAxis 257
#define JOYAXIS_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define JOYAXIS_JOY_AXIS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_JoyButton 258
#define JOYBUTTON_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define JOYBUTTON_JOY_BUTTON num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_JoyHat 259
#define JOYHAT_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define JOYHAT_JOY_HAT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_GetJoyTrackBall 260
#define GETJOYTRACKBALL_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETJOYTRACKBALL_BALL num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETJOYTRACKBALL_DX num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETJOYTRACKBALL_DY num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_JoyName$ 261
#define JOYNAME$_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_JoystickIsConnected 262
#define JOYSTICKISCONNECTED_JOY_NUM num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_GetCursor 263
#define GETCURSOR_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETCURSOR_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_PrintS 264
#define PRINTS_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_InputS$ 265
#define INPUTS$_PROMPT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_ZoneInputS$ 266
#define ZONEINPUTS$_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define ZONEINPUTS$_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define ZONEINPUTS$_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define ZONEINPUTS$_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_Locate 267
#define LOCATE_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LOCATE_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_ReadInput_Start 268
#define FN_ReadInput_Stop 269
#define FN_ReadInput_Text$ 270
#define FN_ReadInput_SetText 271
#define READINPUT_SETTEXT_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_ReadInput_ToggleBackspace 272
#define READINPUT_TOGGLEBACKSPACE_FLAG num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_LoadFont 273
#define LOADFONT_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define LOADFONT_FNT_FILE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define LOADFONT_SIZE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_DeleteFont 274
#define DELETEFONT_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_FontIsLoaded 275
#define FONTISLOADED_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_Font 276
#define FONT_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_SetFontStyle 277
#define SETFONTSTYLE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETFONTSTYLE_STYLE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_DrawText 278
#define DRAWTEXT_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define DRAWTEXT_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWTEXT_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_DrawText_Shaded 279
#define DRAWTEXT_SHADED_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define DRAWTEXT_SHADED_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWTEXT_SHADED_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define DRAWTEXT_SHADED_FG_COLOR num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define DRAWTEXT_SHADED_BG_COLOR num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_DrawText_Blended 280
#define DRAWTEXT_BLENDED_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define DRAWTEXT_BLENDED_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define DRAWTEXT_BLENDED_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_RenderText 281
#define RENDERTEXT_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define RENDERTEXT_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_GetTextSize 282
#define GETTEXTSIZE_SLOT num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETTEXTSIZE_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define GETTEXTSIZE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETTEXTSIZE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_TouchPressure 283
#define FN_GetTouch 284
#define GETTOUCH_STATUS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETTOUCH_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETTOUCH_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETTOUCH_DX num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define GETTOUCH_DY num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define FN_GetMultiTouch 285
#define GETMULTITOUCH_STATUS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETMULTITOUCH_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETMULTITOUCH_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETMULTITOUCH_FINGERS num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define GETMULTITOUCH_DIST num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define GETMULTITOUCH_THETA num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define FN_GetTouchFinger 286
#define GETTOUCHFINGER_FINGER num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETTOUCHFINGER_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETTOUCHFINGER_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETTOUCHFINGER_PRESSURE num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_NumFingers 287
#define FN_CheckSockets 288
#define CHECKSOCKETS_TIMEOUT_MS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_TCP_SocketReady 289
#define TCP_SOCKETREADY_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_UDP_SocketReady 290
#define UDP_SOCKETREADY_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_TCP_SocketOpen 291
#define TCP_SOCKETOPEN_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define TCP_SOCKETOPEN_HOST$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define TCP_SOCKETOPEN_PORT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_TCP_SocketClose 292
#define TCP_SOCKETCLOSE_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_TCP_RemoteHost 293
#define TCP_REMOTEHOST_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_TCP_RemotePort 294
#define TCP_REMOTEPORT_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_TCP_GetData 295
#define TCP_GETDATA_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define TCP_GETDATA_SDATA$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define TCP_GETDATA_NUMBYTES num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_TCP_SendData 296
#define TCP_SENDDATA_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define TCP_SENDDATA_SDATA$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_TCP_AcceptSocket 297
#define TCP_ACCEPTSOCKET_SERVER num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define TCP_ACCEPTSOCKET_CLIENT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_UDP_SocketOpen 298
#define UDP_SOCKETOPEN_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define UDP_SOCKETOPEN_PORT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_UDP_SocketClose 299
#define UDP_SOCKETCLOSE_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_UDP_GetData 300
#define UDP_GETDATA_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define UDP_GETDATA_SDATA$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define UDP_GETDATA_HOST$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define UDP_GETDATA_PORT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_UDP_Length 301
#define FN_UDP_MaxLength 302
#define FN_UDP_RemoteHost$ 303
#define UDP_REMOTEHOST$_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_UDP_RemotePort 304
#define UDP_REMOTEPORT_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_UDP_SendData 305
#define UDP_SENDDATA_SOCKET num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define UDP_SENDDATA_SDATA$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define UDP_SENDDATA_HOST$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define UDP_SENDDATA_PORT num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_LoadVideo 306
#define LOADVIDEO_VID$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_PlayVideo 307
#define PLAYVIDEO_VLOOPS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_PauseVideo 308
#define FN_StopVideo 309
#define FN_SetVideoPosition 310
#define SETVIDEOPOSITION_POS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_ResumeVideo 311
#define FN_VideoPosition 312
#define FN_DeleteVideo 313
#define FN_VideoIsPlaying 314
#define FN_VideoEnd 315
#define FN_GetVideoStats 316
#define GETVIDEOSTATS_VFILE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define GETVIDEOSTATS_VLEN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETVIDEOSTATS_VFPS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETVIDEOSTATS_FRAME_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETVIDEOSTATS_FRAME_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_SetVideoDrawRect 317
#define SETVIDEODRAWRECT_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define SETVIDEODRAWRECT_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define SETVIDEODRAWRECT_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define SETVIDEODRAWRECT_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_GetVideoDrawRect 318
#define GETVIDEODRAWRECT_X num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETVIDEODRAWRECT_Y num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETVIDEODRAWRECT_W num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETVIDEODRAWRECT_H num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_GetVideoSize 319
#define GETVIDEOSIZE_W num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETVIDEOSIZE_H num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define FN_VideoExists 320
#define FN_SetVideoAlpha 321
#define SETVIDEOALPHA_A num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_System 322
#define SYSTEM_CMD$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_OS$ 323
#define FN_Command$ 324
#define COMMAND$_ARG num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_NumCommands 325
#define FN_Env$ 326
#define ENV$_V$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_SetEnv 327
#define SETENV_VAR$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define SETENV_VALUE$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define SETENV_OVERWRITE num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_PrefPath$ 328
#define PREFPATH$_ORG_NAME$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define PREFPATH$_APP_NAME$ str_var[1].sid_value[0].value[ str_var[1].byref_offset ]
#define FN_Android_GetExternalStoragePath$ 329
#define FN_Android_GetExternalStorageState 330
#define FN_Android_GetInternalStoragePath$ 331
#define FN_RCBasic_Android_Interface$ 332
#define RCBASIC_ANDROID_INTERFACE$_ARG$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_RCBasic_IOS_Interface$ 333
#define RCBASIC_IOS_INTERFACE$_ARG$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_ClipboardText$ 334
#define FN_SetClipboardText 335
#define SETCLIPBOARDTEXT_TXT$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_HasClipboardText 336
#define FN_GetDesktopDisplayMode 337
#define GETDESKTOPDISPLAYMODE_INDEX num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETDESKTOPDISPLAYMODE_W num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETDESKTOPDISPLAYMODE_H num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define GETDESKTOPDISPLAYMODE_FREQ num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define FN_DrawImage_Transform 338
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
#define FN_GetPowerInfo 339
#define GETPOWERINFO_STATUS num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define GETPOWERINFO_SECS num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define GETPOWERINFO_PCT num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define FN_SystemRam 340
#define FN_SetRenderScaleQuality 341
#define SETRENDERSCALEQUALITY_N num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define FN_EvalJS$ 342
#define EVALJS$_JS_CODE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define FN_GetRenderScaleQuality 343
#define FN_WindowOpen_Ex 344
#define WINDOWOPEN_EX_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WINDOWOPEN_EX_TITLE$ str_var[0].sid_value[0].value[ str_var[0].byref_offset ]
#define WINDOWOPEN_EX_X num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
#define WINDOWOPEN_EX_Y num_var[2].nid_value[0].value[ num_var[2].byref_offset ]
#define WINDOWOPEN_EX_W num_var[3].nid_value[0].value[ num_var[3].byref_offset ]
#define WINDOWOPEN_EX_H num_var[4].nid_value[0].value[ num_var[4].byref_offset ]
#define WINDOWOPEN_EX_FLAG num_var[5].nid_value[0].value[ num_var[5].byref_offset ]
#define WINDOWOPEN_EX_VSYNC num_var[6].nid_value[0].value[ num_var[6].byref_offset ]
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
#define FN_WindowEvent_SetExitOnClose 360
#define WINDOWEVENT_SETEXITONCLOSE_WIN num_var[0].nid_value[0].value[ num_var[0].byref_offset ]
#define WINDOWEVENT_SETEXITONCLOSE_EXIT_ON_CLOSE num_var[1].nid_value[0].value[ num_var[1].byref_offset ]
