#define FN_FPrint 0
#define FPRINT_TXT$ str_var[0].sid_value[0].value[0]
#define FN_Input$ 1
#define INPUT$_PROMPT$ str_var[0].sid_value[0].value[0]
#define FN_ArrayDim 2
#define ARRAYDIM_ID num_var[0].nid_value[0].value[0]
#define FN_StringArrayDim 3
#define STRINGARRAYDIM_ID$ str_var[0].sid_value[0].value[0]
#define FN_NumberArrayDim 4
#define NUMBERARRAYDIM_ID num_var[0].nid_value[0].value[0]
#define FN_ArraySize 5
#define ARRAYSIZE_ID num_var[0].nid_value[0].value[0]
#define ARRAYSIZE_ARRAY_DIM num_var[1].nid_value[0].value[0]
#define FN_StringArraySize 6
#define STRINGARRAYSIZE_ID$ str_var[0].sid_value[0].value[0]
#define STRINGARRAYSIZE_ARRAY_DIM num_var[0].nid_value[0].value[0]
#define FN_NumberArraySize 7
#define NUMBERARRAYSIZE_ID num_var[0].nid_value[0].value[0]
#define NUMBERARRAYSIZE_ARRAY_DIM num_var[1].nid_value[0].value[0]
#define FN_Abs 8
#define ABS_N num_var[0].nid_value[0].value[0]
#define FN_ACos 9
#define ACOS_N num_var[0].nid_value[0].value[0]
#define FN_AndBit 10
#define ANDBIT_A num_var[0].nid_value[0].value[0]
#define ANDBIT_B num_var[1].nid_value[0].value[0]
#define FN_ASin 11
#define ASIN_N num_var[0].nid_value[0].value[0]
#define FN_ATan 12
#define ATAN_N num_var[0].nid_value[0].value[0]
#define FN_Bin$ 13
#define BIN$_N num_var[0].nid_value[0].value[0]
#define FN_CInt32 14
#define CINT32_I num_var[0].nid_value[0].value[0]
#define FN_CInt64 15
#define CINT64_I num_var[0].nid_value[0].value[0]
#define FN_Cos 16
#define COS_N num_var[0].nid_value[0].value[0]
#define FN_Exp 17
#define EXP_N num_var[0].nid_value[0].value[0]
#define FN_Frac 18
#define FRAC_N num_var[0].nid_value[0].value[0]
#define FN_Hex$ 19
#define HEX$_N num_var[0].nid_value[0].value[0]
#define FN_Int 20
#define INT_N num_var[0].nid_value[0].value[0]
#define FN_Log 21
#define LOG_N num_var[0].nid_value[0].value[0]
#define FN_Max 22
#define MAX_A num_var[0].nid_value[0].value[0]
#define MAX_B num_var[1].nid_value[0].value[0]
#define FN_Min 23
#define MIN_A num_var[0].nid_value[0].value[0]
#define MIN_B num_var[1].nid_value[0].value[0]
#define FN_OrBit 24
#define ORBIT_A num_var[0].nid_value[0].value[0]
#define ORBIT_B num_var[1].nid_value[0].value[0]
#define FN_Randomize 25
#define RANDOMIZE_N num_var[0].nid_value[0].value[0]
#define FN_Rand 26
#define RAND_N num_var[0].nid_value[0].value[0]
#define FN_Round 27
#define ROUND_N num_var[0].nid_value[0].value[0]
#define FN_Sign 28
#define SIGN_N num_var[0].nid_value[0].value[0]
#define FN_Sin 29
#define SIN_N num_var[0].nid_value[0].value[0]
#define FN_Sqrt 30
#define SQRT_N num_var[0].nid_value[0].value[0]
#define FN_Tan 31
#define TAN_N num_var[0].nid_value[0].value[0]
#define FN_XOrBit 32
#define XORBIT_A num_var[0].nid_value[0].value[0]
#define XORBIT_B num_var[1].nid_value[0].value[0]
#define FN_Asc 33
#define ASC_C$ str_var[0].sid_value[0].value[0]
#define FN_Chr$ 34
#define CHR$_N num_var[0].nid_value[0].value[0]
#define FN_Insert$ 35
#define INSERT$_SRC$ str_var[0].sid_value[0].value[0]
#define INSERT$_TGT$ str_var[1].sid_value[0].value[0]
#define INSERT$_POS num_var[0].nid_value[0].value[0]
#define FN_InStr 36
#define INSTR_SRC$ str_var[0].sid_value[0].value[0]
#define INSTR_SUBSTR$ str_var[1].sid_value[0].value[0]
#define FN_LCase$ 37
#define LCASE$_SRC$ str_var[0].sid_value[0].value[0]
#define FN_Left$ 38
#define LEFT$_SRC$ str_var[0].sid_value[0].value[0]
#define LEFT$_N num_var[0].nid_value[0].value[0]
#define FN_Length 39
#define LENGTH_SRC$ str_var[0].sid_value[0].value[0]
#define FN_LTrim$ 40
#define LTRIM$_SRC$ str_var[0].sid_value[0].value[0]
#define FN_Mid$ 41
#define MID$_SRC$ str_var[0].sid_value[0].value[0]
#define MID$_START num_var[0].nid_value[0].value[0]
#define MID$_N num_var[1].nid_value[0].value[0]
#define FN_Replace$ 42
#define REPLACE$_SRC$ str_var[0].sid_value[0].value[0]
#define REPLACE$_RPC$ str_var[1].sid_value[0].value[0]
#define REPLACE$_POS num_var[0].nid_value[0].value[0]
#define FN_ReplaceSubstr$ 43
#define REPLACESUBSTR$_SRC$ str_var[0].sid_value[0].value[0]
#define REPLACESUBSTR$_TGT$ str_var[1].sid_value[0].value[0]
#define REPLACESUBSTR$_RPC$ str_var[2].sid_value[0].value[0]
#define FN_Reverse$ 44
#define REVERSE$_SRC$ str_var[0].sid_value[0].value[0]
#define FN_Right$ 45
#define RIGHT$_SRC$ str_var[0].sid_value[0].value[0]
#define RIGHT$_N num_var[0].nid_value[0].value[0]
#define FN_RTrim$ 46
#define RTRIM$_SRC$ str_var[0].sid_value[0].value[0]
#define FN_StringFill$ 47
#define STRINGFILL$_SRC$ str_var[0].sid_value[0].value[0]
#define STRINGFILL$_N num_var[0].nid_value[0].value[0]
#define FN_Str$ 48
#define STR$_N num_var[0].nid_value[0].value[0]
#define FN_Str_F$ 49
#define STR_F$_N num_var[0].nid_value[0].value[0]
#define FN_Str_S$ 50
#define STR_S$_N num_var[0].nid_value[0].value[0]
#define FN_Tally 51
#define TALLY_SRC$ str_var[0].sid_value[0].value[0]
#define TALLY_SUBSTR$ str_var[1].sid_value[0].value[0]
#define FN_Trim$ 52
#define TRIM$_SRC$ str_var[0].sid_value[0].value[0]
#define FN_UCase$ 53
#define UCASE$_SRC$ str_var[0].sid_value[0].value[0]
#define FN_Val 54
#define VAL_N$ str_var[0].sid_value[0].value[0]
#define FN_Push_N 55
#define PUSH_N_N num_var[0].nid_value[0].value[0]
#define FN_Pop_N 56
#define FN_Push_S 57
#define PUSH_S_S$ str_var[0].sid_value[0].value[0]
#define FN_Pop_S$ 58
#define FN_Stack_Size_N 59
#define FN_Stack_Size_S 60
#define FN_FileOpen 61
#define FILEOPEN_STREAM num_var[0].nid_value[0].value[0]
#define FILEOPEN_FILENAME$ str_var[0].sid_value[0].value[0]
#define FILEOPEN_MODE num_var[1].nid_value[0].value[0]
#define FN_FileClose 62
#define FILECLOSE_STREAM num_var[0].nid_value[0].value[0]
#define FN_ReadByte 63
#define READBYTE_STREAM num_var[0].nid_value[0].value[0]
#define FN_WriteByte 64
#define WRITEBYTE_STREAM num_var[0].nid_value[0].value[0]
#define WRITEBYTE_BYTE num_var[1].nid_value[0].value[0]
#define FN_ReadLine$ 65
#define READLINE$_STREAM num_var[0].nid_value[0].value[0]
#define FN_WriteLine 66
#define WRITELINE_STREAM num_var[0].nid_value[0].value[0]
#define WRITELINE_TXT$ str_var[0].sid_value[0].value[0]
#define FN_CopyFile 67
#define COPYFILE_SRC$ str_var[0].sid_value[0].value[0]
#define COPYFILE_DST$ str_var[1].sid_value[0].value[0]
#define FN_RemoveFile 68
#define REMOVEFILE_FILENAME$ str_var[0].sid_value[0].value[0]
#define FN_FileExists 69
#define FILEEXISTS_FILENAME$ str_var[0].sid_value[0].value[0]
#define FN_MoveFile 70
#define MOVEFILE_SRC$ str_var[0].sid_value[0].value[0]
#define MOVEFILE_DST$ str_var[1].sid_value[0].value[0]
#define FN_RenameFile 71
#define RENAMEFILE_SRC$ str_var[0].sid_value[0].value[0]
#define RENAMEFILE_DST$ str_var[1].sid_value[0].value[0]
#define FN_FileLength 72
#define FILELENGTH_FILENAME$ str_var[0].sid_value[0].value[0]
#define FN_Tell 73
#define TELL_STREAM num_var[0].nid_value[0].value[0]
#define FN_Seek 74
#define SEEK_STREAM num_var[0].nid_value[0].value[0]
#define SEEK_POS num_var[1].nid_value[0].value[0]
#define FN_EOF 75
#define EOF_STREAM num_var[0].nid_value[0].value[0]
#define FN_FreeFile 76
#define FN_ChangeDir 77
#define CHANGEDIR_P$ str_var[0].sid_value[0].value[0]
#define FN_DirExists 78
#define DIREXISTS_P$ str_var[0].sid_value[0].value[0]
#define FN_DirFirst$ 79
#define FN_Dir$ 80
#define FN_DirNext$ 81
#define FN_MakeDir 82
#define MAKEDIR_P$ str_var[0].sid_value[0].value[0]
#define FN_RemoveDir 83
#define REMOVEDIR_P$ str_var[0].sid_value[0].value[0]
#define FN_Date$ 84
#define FN_Ticks 85
#define FN_Time$ 86
#define FN_Timer 87
#define FN_Wait 88
#define WAIT_M_SEC num_var[0].nid_value[0].value[0]
#define FN_WindowOpen 89
#define WINDOWOPEN_WIN num_var[0].nid_value[0].value[0]
#define WINDOWOPEN_TITLE$ str_var[0].sid_value[0].value[0]
#define WINDOWOPEN_X num_var[1].nid_value[0].value[0]
#define WINDOWOPEN_Y num_var[2].nid_value[0].value[0]
#define WINDOWOPEN_W num_var[3].nid_value[0].value[0]
#define WINDOWOPEN_H num_var[4].nid_value[0].value[0]
#define WINDOWOPEN_FLAG num_var[5].nid_value[0].value[0]
#define FN_WindowClose 90
#define WINDOWCLOSE_WIN num_var[0].nid_value[0].value[0]
#define FN_RaiseWindow 91
#define RAISEWINDOW_WIN num_var[0].nid_value[0].value[0]
#define FN_Window 92
#define WINDOW_WIN num_var[0].nid_value[0].value[0]
#define FN_Update 93
#define FN_Cls 94
#define FN_SetClearColor 95
#define SETCLEARCOLOR_C num_var[0].nid_value[0].value[0]
#define FN_ShowWindow 96
#define SHOWWINDOW_WIN num_var[0].nid_value[0].value[0]
#define FN_HideWindow 97
#define HIDEWINDOW_WIN num_var[0].nid_value[0].value[0]
#define FN_SetWindowTitle 98
#define SETWINDOWTITLE_WIN num_var[0].nid_value[0].value[0]
#define SETWINDOWTITLE_TITLE$ str_var[0].sid_value[0].value[0]
#define FN_WindowTitle$ 99
#define WINDOWTITLE$_WIN num_var[0].nid_value[0].value[0]
#define FN_SetWindowPosition 100
#define SETWINDOWPOSITION_WIN num_var[0].nid_value[0].value[0]
#define SETWINDOWPOSITION_X num_var[1].nid_value[0].value[0]
#define SETWINDOWPOSITION_Y num_var[2].nid_value[0].value[0]
#define FN_GetWindowPosition 101
#define GETWINDOWPOSITION_WIN num_var[0].nid_value[0].value[0]
#define GETWINDOWPOSITION_X num_var[1].nid_value[0].value[0]
#define GETWINDOWPOSITION_Y num_var[2].nid_value[0].value[0]
#define FN_SetWindowSize 102
#define SETWINDOWSIZE_WIN num_var[0].nid_value[0].value[0]
#define SETWINDOWSIZE_W num_var[1].nid_value[0].value[0]
#define SETWINDOWSIZE_H num_var[2].nid_value[0].value[0]
#define FN_GetWindowSize 103
#define GETWINDOWSIZE_WIN num_var[0].nid_value[0].value[0]
#define GETWINDOWSIZE_W num_var[1].nid_value[0].value[0]
#define GETWINDOWSIZE_H num_var[2].nid_value[0].value[0]
#define FN_SetWindowMinSize 104
#define SETWINDOWMINSIZE_WIN num_var[0].nid_value[0].value[0]
#define SETWINDOWMINSIZE_W num_var[1].nid_value[0].value[0]
#define SETWINDOWMINSIZE_H num_var[2].nid_value[0].value[0]
#define FN_GetWindowMinSize 105
#define GETWINDOWMINSIZE_WIN num_var[0].nid_value[0].value[0]
#define GETWINDOWMINSIZE_W num_var[1].nid_value[0].value[0]
#define GETWINDOWMINSIZE_H num_var[2].nid_value[0].value[0]
#define FN_SetWindowMaxSize 106
#define SETWINDOWMAXSIZE_WIN num_var[0].nid_value[0].value[0]
#define SETWINDOWMAXSIZE_W num_var[1].nid_value[0].value[0]
#define SETWINDOWMAXSIZE_H num_var[2].nid_value[0].value[0]
#define FN_GetWindowMaxSize 107
#define GETWINDOWMAXSIZE_WIN num_var[0].nid_value[0].value[0]
#define GETWINDOWMAXSIZE_W num_var[1].nid_value[0].value[0]
#define GETWINDOWMAXSIZE_H num_var[2].nid_value[0].value[0]
#define FN_WindowIsFullscreen 108
#define WINDOWISFULLSCREEN_WIN num_var[0].nid_value[0].value[0]
#define FN_WindowIsVisible 109
#define WINDOWISVISIBLE_WIN num_var[0].nid_value[0].value[0]
#define FN_WindowIsBordered 110
#define WINDOWISBORDERED_WIN num_var[0].nid_value[0].value[0]
#define FN_WindowIsResizable 111
#define WINDOWISRESIZABLE_WIN num_var[0].nid_value[0].value[0]
#define FN_WindowIsMinimized 112
#define WINDOWISMINIMIZED_WIN num_var[0].nid_value[0].value[0]
#define FN_WindowIsMaximized 113
#define WINDOWISMAXIMIZED_WIN num_var[0].nid_value[0].value[0]
#define FN_WindowHasInputFocus 114
#define WINDOWHASINPUTFOCUS_WIN num_var[0].nid_value[0].value[0]
#define FN_WindowHasMouseFocus 115
#define WINDOWHASMOUSEFOCUS_WIN num_var[0].nid_value[0].value[0]
#define FN_SetWindowFullscreen 116
#define SETWINDOWFULLSCREEN_WIN num_var[0].nid_value[0].value[0]
#define SETWINDOWFULLSCREEN_FLAG num_var[1].nid_value[0].value[0]
#define FN_MaximizeWindow 117
#define MAXIMIZEWINDOW_WIN num_var[0].nid_value[0].value[0]
#define FN_MinimizeWindow 118
#define MINIMIZEWINDOW_WIN num_var[0].nid_value[0].value[0]
#define FN_SetWindowBorder 119
#define SETWINDOWBORDER_WIN num_var[0].nid_value[0].value[0]
#define SETWINDOWBORDER_FLAG num_var[1].nid_value[0].value[0]
#define FN_WindowClip 120
#define WINDOWCLIP_SLOT num_var[0].nid_value[0].value[0]
#define WINDOWCLIP_X num_var[1].nid_value[0].value[0]
#define WINDOWCLIP_Y num_var[2].nid_value[0].value[0]
#define WINDOWCLIP_W num_var[3].nid_value[0].value[0]
#define WINDOWCLIP_H num_var[4].nid_value[0].value[0]
#define FN_WindowExists 121
#define WINDOWEXISTS_WIN num_var[0].nid_value[0].value[0]
#define FN_NumWindows 122
#define FN_WindowEvent_Close 123
#define WINDOWEVENT_CLOSE_WIN num_var[0].nid_value[0].value[0]
#define FN_WindowEvent_Maximize 124
#define WINDOWEVENT_MAXIMIZE_WIN num_var[0].nid_value[0].value[0]
#define FN_WindowEvent_Minimize 125
#define WINDOWEVENT_MINIMIZE_WIN num_var[0].nid_value[0].value[0]
#define FN_ActiveWindow 126
#define FN_FPS 127
#define FN_CanvasOpen 128
#define CANVASOPEN_C_NUM num_var[0].nid_value[0].value[0]
#define CANVASOPEN_W num_var[1].nid_value[0].value[0]
#define CANVASOPEN_H num_var[2].nid_value[0].value[0]
#define CANVASOPEN_VIEWPORT_X num_var[3].nid_value[0].value[0]
#define CANVASOPEN_VIEWPORT_Y num_var[4].nid_value[0].value[0]
#define CANVASOPEN_VIEWPORT_W num_var[5].nid_value[0].value[0]
#define CANVASOPEN_VIEWPORT_H num_var[6].nid_value[0].value[0]
#define CANVASOPEN_MODE num_var[7].nid_value[0].value[0]
#define FN_CanvasClose 129
#define CANVASCLOSE_C_NUM num_var[0].nid_value[0].value[0]
#define FN_SetCanvasVisible 130
#define SETCANVASVISIBLE_C_NUM num_var[0].nid_value[0].value[0]
#define SETCANVASVISIBLE_FLAG num_var[1].nid_value[0].value[0]
#define FN_CanvasIsVisible 131
#define CANVASISVISIBLE_C_NUM num_var[0].nid_value[0].value[0]
#define FN_SetCanvasViewport 132
#define SETCANVASVIEWPORT_CNUM num_var[0].nid_value[0].value[0]
#define SETCANVASVIEWPORT_X num_var[1].nid_value[0].value[0]
#define SETCANVASVIEWPORT_Y num_var[2].nid_value[0].value[0]
#define SETCANVASVIEWPORT_W num_var[3].nid_value[0].value[0]
#define SETCANVASVIEWPORT_H num_var[4].nid_value[0].value[0]
#define FN_GetCanvasViewport 133
#define GETCANVASVIEWPORT_C_NUM num_var[0].nid_value[0].value[0]
#define GETCANVASVIEWPORT_X num_var[1].nid_value[0].value[0]
#define GETCANVASVIEWPORT_Y num_var[2].nid_value[0].value[0]
#define GETCANVASVIEWPORT_W num_var[3].nid_value[0].value[0]
#define GETCANVASVIEWPORT_H num_var[4].nid_value[0].value[0]
#define FN_Canvas 134
#define CANVAS_C_NUM num_var[0].nid_value[0].value[0]
#define FN_SetCanvasOffset 135
#define SETCANVASOFFSET_C_NUM num_var[0].nid_value[0].value[0]
#define SETCANVASOFFSET_X num_var[1].nid_value[0].value[0]
#define SETCANVASOFFSET_Y num_var[2].nid_value[0].value[0]
#define FN_GetCanvasOffset 136
#define GETCANVASOFFSET_C_NUM num_var[0].nid_value[0].value[0]
#define GETCANVASOFFSET_X num_var[1].nid_value[0].value[0]
#define GETCANVASOFFSET_Y num_var[2].nid_value[0].value[0]
#define FN_GetCanvasSize 137
#define GETCANVASSIZE_C_NUM num_var[0].nid_value[0].value[0]
#define GETCANVASSIZE_W num_var[1].nid_value[0].value[0]
#define GETCANVASSIZE_H num_var[2].nid_value[0].value[0]
#define FN_ClearCanvas 138
#define FN_SetCanvasAlpha 139
#define SETCANVASALPHA_C_NUM num_var[0].nid_value[0].value[0]
#define SETCANVASALPHA_A num_var[1].nid_value[0].value[0]
#define FN_CopyCanvas 140
#define COPYCANVAS_SRC num_var[0].nid_value[0].value[0]
#define COPYCANVAS_X num_var[1].nid_value[0].value[0]
#define COPYCANVAS_Y num_var[2].nid_value[0].value[0]
#define COPYCANVAS_W num_var[3].nid_value[0].value[0]
#define COPYCANVAS_H num_var[4].nid_value[0].value[0]
#define COPYCANVAS_DST num_var[5].nid_value[0].value[0]
#define COPYCANVAS_DX num_var[6].nid_value[0].value[0]
#define COPYCANVAS_DY num_var[7].nid_value[0].value[0]
#define FN_CloneCanvas 141
#define CLONECANVAS_SRC num_var[0].nid_value[0].value[0]
#define CLONECANVAS_DST num_var[1].nid_value[0].value[0]
#define FN_SetCanvasZ 142
#define SETCANVASZ_C_NUM num_var[0].nid_value[0].value[0]
#define SETCANVASZ_Z num_var[1].nid_value[0].value[0]
#define FN_CanvasClip 143
#define CANVASCLIP_SLOT num_var[0].nid_value[0].value[0]
#define CANVASCLIP_X num_var[1].nid_value[0].value[0]
#define CANVASCLIP_Y num_var[2].nid_value[0].value[0]
#define CANVASCLIP_W num_var[3].nid_value[0].value[0]
#define CANVASCLIP_H num_var[4].nid_value[0].value[0]
#define FN_ActiveCanvas 144
#define FN_Box 145
#define BOX_X1 num_var[0].nid_value[0].value[0]
#define BOX_Y1 num_var[1].nid_value[0].value[0]
#define BOX_X2 num_var[2].nid_value[0].value[0]
#define BOX_Y2 num_var[3].nid_value[0].value[0]
#define FN_BoxFill 146
#define BOXFILL_X1 num_var[0].nid_value[0].value[0]
#define BOXFILL_Y1 num_var[1].nid_value[0].value[0]
#define BOXFILL_X2 num_var[2].nid_value[0].value[0]
#define BOXFILL_Y2 num_var[3].nid_value[0].value[0]
#define FN_Circle 147
#define CIRCLE_X num_var[0].nid_value[0].value[0]
#define CIRCLE_Y num_var[1].nid_value[0].value[0]
#define CIRCLE_RADIUS num_var[2].nid_value[0].value[0]
#define FN_CircleFill 148
#define CIRCLEFILL_X num_var[0].nid_value[0].value[0]
#define CIRCLEFILL_Y num_var[1].nid_value[0].value[0]
#define CIRCLEFILL_RADIUS num_var[2].nid_value[0].value[0]
#define FN_Ellipse 149
#define ELLIPSE_X num_var[0].nid_value[0].value[0]
#define ELLIPSE_Y num_var[1].nid_value[0].value[0]
#define ELLIPSE_RX num_var[2].nid_value[0].value[0]
#define ELLIPSE_RY num_var[3].nid_value[0].value[0]
#define FN_EllipseFill 150
#define ELLIPSEFILL_X num_var[0].nid_value[0].value[0]
#define ELLIPSEFILL_Y num_var[1].nid_value[0].value[0]
#define ELLIPSEFILL_RX num_var[2].nid_value[0].value[0]
#define ELLIPSEFILL_RY num_var[3].nid_value[0].value[0]
#define FN_FloodFill 151
#define FLOODFILL_X num_var[0].nid_value[0].value[0]
#define FLOODFILL_Y num_var[1].nid_value[0].value[0]
#define FN_GetPixel 152
#define GETPIXEL_X num_var[0].nid_value[0].value[0]
#define GETPIXEL_Y num_var[1].nid_value[0].value[0]
#define FN_SetColor 153
#define SETCOLOR_C num_var[0].nid_value[0].value[0]
#define FN_Line 154
#define LINE_X1 num_var[0].nid_value[0].value[0]
#define LINE_Y1 num_var[1].nid_value[0].value[0]
#define LINE_X2 num_var[2].nid_value[0].value[0]
#define LINE_Y2 num_var[3].nid_value[0].value[0]
#define FN_Poly 155
#define POLY_N num_var[0].nid_value[0].value[0]
#define POLY_X num_var[1].nid_value[0].value[0]
#define POLY_Y num_var[2].nid_value[0].value[0]
#define FN_PolyFill 156
#define POLYFILL_N num_var[0].nid_value[0].value[0]
#define POLYFILL_X num_var[1].nid_value[0].value[0]
#define POLYFILL_Y num_var[2].nid_value[0].value[0]
#define FN_Rect 157
#define RECT_X num_var[0].nid_value[0].value[0]
#define RECT_Y num_var[1].nid_value[0].value[0]
#define RECT_W num_var[2].nid_value[0].value[0]
#define RECT_H num_var[3].nid_value[0].value[0]
#define FN_RectFill 158
#define RECTFILL_X num_var[0].nid_value[0].value[0]
#define RECTFILL_Y num_var[1].nid_value[0].value[0]
#define RECTFILL_W num_var[2].nid_value[0].value[0]
#define RECTFILL_H num_var[3].nid_value[0].value[0]
#define FN_RoundRect 159
#define ROUNDRECT_X num_var[0].nid_value[0].value[0]
#define ROUNDRECT_Y num_var[1].nid_value[0].value[0]
#define ROUNDRECT_W num_var[2].nid_value[0].value[0]
#define ROUNDRECT_H num_var[3].nid_value[0].value[0]
#define ROUNDRECT_R num_var[4].nid_value[0].value[0]
#define FN_RoundRectFill 160
#define ROUNDRECTFILL_X num_var[0].nid_value[0].value[0]
#define ROUNDRECTFILL_Y num_var[1].nid_value[0].value[0]
#define ROUNDRECTFILL_W num_var[2].nid_value[0].value[0]
#define ROUNDRECTFILL_H num_var[3].nid_value[0].value[0]
#define ROUNDRECTFILL_R num_var[4].nid_value[0].value[0]
#define FN_RGB 161
#define RGB_R num_var[0].nid_value[0].value[0]
#define RGB_G num_var[1].nid_value[0].value[0]
#define RGB_B num_var[2].nid_value[0].value[0]
#define FN_RGBA 162
#define RGBA_R num_var[0].nid_value[0].value[0]
#define RGBA_G num_var[1].nid_value[0].value[0]
#define RGBA_B num_var[2].nid_value[0].value[0]
#define RGBA_A num_var[3].nid_value[0].value[0]
#define FN_PSet 163
#define PSET_X num_var[0].nid_value[0].value[0]
#define PSET_Y num_var[1].nid_value[0].value[0]
#define FN_LoadImage 164
#define LOADIMAGE_SLOT num_var[0].nid_value[0].value[0]
#define LOADIMAGE_IMG$ str_var[0].sid_value[0].value[0]
#define FN_LoadImage_Ex 165
#define LOADIMAGE_EX_SLOT num_var[0].nid_value[0].value[0]
#define LOADIMAGE_EX_IMG$ str_var[0].sid_value[0].value[0]
#define LOADIMAGE_EX_COLKEY num_var[1].nid_value[0].value[0]
#define FN_ImageFromBuffer 166
#define IMAGEFROMBUFFER_SLOT num_var[0].nid_value[0].value[0]
#define IMAGEFROMBUFFER_W num_var[1].nid_value[0].value[0]
#define IMAGEFROMBUFFER_H num_var[2].nid_value[0].value[0]
#define IMAGEFROMBUFFER_BUFFER num_var[3].nid_value[0].value[0]
#define FN_ImageFromBuffer_Ex 167
#define IMAGEFROMBUFFER_EX_SLOT num_var[0].nid_value[0].value[0]
#define IMAGEFROMBUFFER_EX_W num_var[1].nid_value[0].value[0]
#define IMAGEFROMBUFFER_EX_H num_var[2].nid_value[0].value[0]
#define IMAGEFROMBUFFER_EX_BUFFER num_var[3].nid_value[0].value[0]
#define IMAGEFROMBUFFER_EX_COLKEY num_var[4].nid_value[0].value[0]
#define FN_ImageExists 168
#define IMAGEEXISTS_SLOT num_var[0].nid_value[0].value[0]
#define FN_ColorKey 169
#define COLORKEY_SLOT num_var[0].nid_value[0].value[0]
#define COLORKEY_C num_var[1].nid_value[0].value[0]
#define FN_CopyImage 170
#define COPYIMAGE_SRC num_var[0].nid_value[0].value[0]
#define COPYIMAGE_DST num_var[1].nid_value[0].value[0]
#define FN_DeleteImage 171
#define DELETEIMAGE_SLOT num_var[0].nid_value[0].value[0]
#define FN_SetImageAlpha 172
#define SETIMAGEALPHA_SLOT num_var[0].nid_value[0].value[0]
#define SETIMAGEALPHA_A num_var[1].nid_value[0].value[0]
#define FN_ImageAlpha 173
#define IMAGEALPHA_SLOT num_var[0].nid_value[0].value[0]
#define FN_GetImageSize 174
#define GETIMAGESIZE_SLOT num_var[0].nid_value[0].value[0]
#define GETIMAGESIZE_W num_var[1].nid_value[0].value[0]
#define GETIMAGESIZE_H num_var[2].nid_value[0].value[0]
#define FN_FlipImage 175
#define FLIPIMAGE_SLOT num_var[0].nid_value[0].value[0]
#define FLIPIMAGE_H num_var[1].nid_value[0].value[0]
#define FLIPIMAGE_V num_var[2].nid_value[0].value[0]
#define FN_DrawImage 176
#define DRAWIMAGE_SLOT num_var[0].nid_value[0].value[0]
#define DRAWIMAGE_X num_var[1].nid_value[0].value[0]
#define DRAWIMAGE_Y num_var[2].nid_value[0].value[0]
#define FN_DrawImage_Blit 177
#define DRAWIMAGE_BLIT_SLOT num_var[0].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_X num_var[1].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_Y num_var[2].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_SRC_X num_var[3].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_SRC_Y num_var[4].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_SRC_W num_var[5].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_SRC_H num_var[6].nid_value[0].value[0]
#define FN_DrawImage_Blit_Ex 178
#define DRAWIMAGE_BLIT_EX_SLOT num_var[0].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_EX_X num_var[1].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_EX_Y num_var[2].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_EX_W num_var[3].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_EX_H num_var[4].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_EX_SRC_X num_var[5].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_EX_SRC_Y num_var[6].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_EX_SRC_W num_var[7].nid_value[0].value[0]
#define DRAWIMAGE_BLIT_EX_SRC_H num_var[8].nid_value[0].value[0]
#define FN_DrawImage_Rotate 179
#define DRAWIMAGE_ROTATE_SLOT num_var[0].nid_value[0].value[0]
#define DRAWIMAGE_ROTATE_X num_var[1].nid_value[0].value[0]
#define DRAWIMAGE_ROTATE_Y num_var[2].nid_value[0].value[0]
#define DRAWIMAGE_ROTATE_ANGLE num_var[3].nid_value[0].value[0]
#define FN_DrawImage_Rotate_Ex 180
#define DRAWIMAGE_ROTATE_EX_SLOT num_var[0].nid_value[0].value[0]
#define DRAWIMAGE_ROTATE_EX_X num_var[1].nid_value[0].value[0]
#define DRAWIMAGE_ROTATE_EX_Y num_var[2].nid_value[0].value[0]
#define DRAWIMAGE_ROTATE_EX_SRC_X num_var[3].nid_value[0].value[0]
#define DRAWIMAGE_ROTATE_EX_SRC_Y num_var[4].nid_value[0].value[0]
#define DRAWIMAGE_ROTATE_EX_SRC_W num_var[5].nid_value[0].value[0]
#define DRAWIMAGE_ROTATE_EX_SRC_H num_var[6].nid_value[0].value[0]
#define DRAWIMAGE_ROTATE_EX_ANGLE num_var[7].nid_value[0].value[0]
#define FN_DrawImage_Zoom 181
#define DRAWIMAGE_ZOOM_SLOT num_var[0].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_X num_var[1].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_Y num_var[2].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_ZX num_var[3].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_ZY num_var[4].nid_value[0].value[0]
#define FN_DrawImage_Zoom_Ex 182
#define DRAWIMAGE_ZOOM_EX_SLOT num_var[0].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_EX_X num_var[1].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_EX_Y num_var[2].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_EX_SRC_X num_var[3].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_EX_SRC_Y num_var[4].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_EX_SRC_W num_var[5].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_EX_SRC_H num_var[6].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_EX_ZX num_var[7].nid_value[0].value[0]
#define DRAWIMAGE_ZOOM_EX_ZY num_var[8].nid_value[0].value[0]
#define FN_DrawImage_Rotozoom 183
#define DRAWIMAGE_ROTOZOOM_SLOT num_var[0].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_X num_var[1].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_Y num_var[2].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_ANGLE num_var[3].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_ZX num_var[4].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_ZY num_var[5].nid_value[0].value[0]
#define FN_DrawImage_Rotozoom_Ex 184
#define DRAWIMAGE_ROTOZOOM_EX_SLOT num_var[0].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_EX_X num_var[1].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_EX_Y num_var[2].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_EX_SRC_X num_var[3].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_EX_SRC_Y num_var[4].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_EX_SRC_W num_var[5].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_EX_SRC_H num_var[6].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_EX_ANGLE num_var[7].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_EX_ZX num_var[8].nid_value[0].value[0]
#define DRAWIMAGE_ROTOZOOM_EX_ZY num_var[9].nid_value[0].value[0]
#define FN_InKey 185
#define FN_Key 186
#define KEY_KEY_CODE num_var[0].nid_value[0].value[0]
#define FN_WaitKey 187
#define FN_HideMouse 188
#define FN_ShowMouse 189
#define FN_MouseIsVisible 190
#define FN_GetMouse 191
#define GETMOUSE_X num_var[0].nid_value[0].value[0]
#define GETMOUSE_Y num_var[1].nid_value[0].value[0]
#define GETMOUSE_MB1 num_var[2].nid_value[0].value[0]
#define GETMOUSE_MB2 num_var[3].nid_value[0].value[0]
#define GETMOUSE_MB3 num_var[4].nid_value[0].value[0]
#define FN_MouseX 192
#define FN_MouseY 193
#define FN_MouseButton 194
#define MOUSEBUTTON_MB num_var[0].nid_value[0].value[0]
#define FN_GetMouseWheel 195
#define GETMOUSEWHEEL_X_AXIS num_var[0].nid_value[0].value[0]
#define GETMOUSEWHEEL_Y_AXIS num_var[1].nid_value[0].value[0]
#define FN_MouseWheelX 196
#define FN_MouseWheelY 197
#define FN_SoundFromBuffer 198
#define SOUNDFROMBUFFER_SLOT num_var[0].nid_value[0].value[0]
#define SOUNDFROMBUFFER_BUFFER num_var[1].nid_value[0].value[0]
#define SOUNDFROMBUFFER_BUFFER_SIZE num_var[2].nid_value[0].value[0]
#define SOUNDFROMBUFFER_VOL num_var[3].nid_value[0].value[0]
#define FN_LoadSound 199
#define LOADSOUND_SLOT num_var[0].nid_value[0].value[0]
#define LOADSOUND_SND_FILE$ str_var[0].sid_value[0].value[0]
#define FN_LoadMusic 200
#define LOADMUSIC_MUSIC_FILE$ str_var[0].sid_value[0].value[0]
#define FN_PlaySound 201
#define PLAYSOUND_SLOT num_var[0].nid_value[0].value[0]
#define PLAYSOUND_CHANNEL num_var[1].nid_value[0].value[0]
#define PLAYSOUND_LOOPS num_var[2].nid_value[0].value[0]
#define FN_PlaySoundTimed 202
#define PLAYSOUNDTIMED_SLOT num_var[0].nid_value[0].value[0]
#define PLAYSOUNDTIMED_CHANNEL num_var[1].nid_value[0].value[0]
#define PLAYSOUNDTIMED_LOOPS num_var[2].nid_value[0].value[0]
#define PLAYSOUNDTIMED_MS num_var[3].nid_value[0].value[0]
#define FN_PlayMusic 203
#define PLAYMUSIC_MLOOPS num_var[0].nid_value[0].value[0]
#define FN_PauseSound 204
#define PAUSESOUND_CHANNEL num_var[0].nid_value[0].value[0]
#define FN_ResumeSound 205
#define RESUMESOUND_CHANNEL num_var[0].nid_value[0].value[0]
#define FN_PauseMusic 206
#define FN_ResumeMusic 207
#define FN_DeleteSound 208
#define DELETESOUND_SLOT num_var[0].nid_value[0].value[0]
#define FN_DeleteMusic 209
#define FN_FadeMusicIn 210
#define FADEMUSICIN_FADE_TIME num_var[0].nid_value[0].value[0]
#define FADEMUSICIN_LOOPS num_var[1].nid_value[0].value[0]
#define FN_FadeMusicOut 211
#define FADEMUSICOUT_FADE_TIME num_var[0].nid_value[0].value[0]
#define FN_MusicExists 212
#define FN_SetMusicVolume 213
#define SETMUSICVOLUME_VOL num_var[0].nid_value[0].value[0]
#define FN_MusicVolume 214
#define FN_SetMusicPosition 215
#define SETMUSICPOSITION_POS num_var[0].nid_value[0].value[0]
#define FN_MusicPosition 216
#define FN_RewindMusic 217
#define FN_SetSoundChannels 218
#define SETSOUNDCHANNELS_MAX_CHANNELS num_var[0].nid_value[0].value[0]
#define FN_NumSoundChannels 219
#define FN_SoundIsEnabled 220
#define FN_SoundExists 221
#define SOUNDEXISTS_SLOT num_var[0].nid_value[0].value[0]
#define FN_SetChannelVolume 222
#define SETCHANNELVOLUME_CHANNEL num_var[0].nid_value[0].value[0]
#define SETCHANNELVOLUME_VOL num_var[1].nid_value[0].value[0]
#define FN_ChannelVolume 223
#define CHANNELVOLUME_CHANNEL num_var[0].nid_value[0].value[0]
#define FN_SetSoundVolume 224
#define SETSOUNDVOLUME_SLOT num_var[0].nid_value[0].value[0]
#define SETSOUNDVOLUME_VOL num_var[1].nid_value[0].value[0]
#define FN_SoundVolume 225
#define SOUNDVOLUME_SLOT num_var[0].nid_value[0].value[0]
#define FN_StopMusic 226
#define FN_StopSound 227
#define STOPSOUND_CHANNEL num_var[0].nid_value[0].value[0]
#define FN_NumJoysticks 228
#define FN_NumJoyAxes 229
#define NUMJOYAXES_JOY_NUM num_var[0].nid_value[0].value[0]
#define FN_NumJoyButtons 230
#define NUMJOYBUTTONS_JOY_NUM num_var[0].nid_value[0].value[0]
#define FN_NumJoyHats 231
#define NUMJOYHATS_JOY_NUM num_var[0].nid_value[0].value[0]
#define FN_NumJoyTrackBalls 232
#define NUMJOYTRACKBALLS_JOY_NUM num_var[0].nid_value[0].value[0]
#define FN_JoyAxis 233
#define JOYAXIS_JOY_NUM num_var[0].nid_value[0].value[0]
#define JOYAXIS_JOY_AXIS num_var[1].nid_value[0].value[0]
#define FN_JoyButton 234
#define JOYBUTTON_JOY_NUM num_var[0].nid_value[0].value[0]
#define JOYBUTTON_JOY_BUTTON num_var[1].nid_value[0].value[0]
#define FN_JoyHat 235
#define JOYHAT_JOY_NUM num_var[0].nid_value[0].value[0]
#define JOYHAT_JOY_HAT num_var[1].nid_value[0].value[0]
#define FN_GetJoyTrackBall 236
#define GETJOYTRACKBALL_JOY_NUM num_var[0].nid_value[0].value[0]
#define GETJOYTRACKBALL_BALL num_var[1].nid_value[0].value[0]
#define GETJOYTRACKBALL_DX num_var[2].nid_value[0].value[0]
#define GETJOYTRACKBALL_DY num_var[3].nid_value[0].value[0]
#define FN_JoyName$ 237
#define JOYNAME$_JOY_NUM num_var[0].nid_value[0].value[0]
#define FN_JoystickIsConnected 238
#define JOYSTICKISCONNECTED_JOY_NUM num_var[0].nid_value[0].value[0]
#define FN_GetCursor 239
#define GETCURSOR_X num_var[0].nid_value[0].value[0]
#define GETCURSOR_Y num_var[1].nid_value[0].value[0]
#define FN_PrintS 240
#define PRINTS_TXT$ str_var[0].sid_value[0].value[0]
#define FN_InputS$ 241
#define INPUTS$_PROMPT$ str_var[0].sid_value[0].value[0]
#define FN_ZoneInputS$ 242
#define ZONEINPUTS$_X num_var[0].nid_value[0].value[0]
#define ZONEINPUTS$_Y num_var[1].nid_value[0].value[0]
#define ZONEINPUTS$_W num_var[2].nid_value[0].value[0]
#define ZONEINPUTS$_H num_var[3].nid_value[0].value[0]
#define FN_Locate 243
#define LOCATE_X num_var[0].nid_value[0].value[0]
#define LOCATE_Y num_var[1].nid_value[0].value[0]
#define FN_ReadInput_Start 244
#define FN_ReadInput_Stop 245
#define FN_ReadInput_Text$ 246
#define FN_ReadInput_SetText 247
#define READINPUT_SETTEXT_TXT$ str_var[0].sid_value[0].value[0]
#define FN_ReadInput_ToggleBackspace 248
#define READINPUT_TOGGLEBACKSPACE_FLAG num_var[0].nid_value[0].value[0]
#define FN_LoadFont 249
#define LOADFONT_SLOT num_var[0].nid_value[0].value[0]
#define LOADFONT_FNT_FILE$ str_var[0].sid_value[0].value[0]
#define LOADFONT_SIZE num_var[1].nid_value[0].value[0]
#define FN_DeleteFont 250
#define DELETEFONT_SLOT num_var[0].nid_value[0].value[0]
#define FN_FontIsLoaded 251
#define FONTISLOADED_SLOT num_var[0].nid_value[0].value[0]
#define FN_Font 252
#define FONT_SLOT num_var[0].nid_value[0].value[0]
#define FN_SetFontStyle 253
#define SETFONTSTYLE_SLOT num_var[0].nid_value[0].value[0]
#define SETFONTSTYLE_STYLE num_var[1].nid_value[0].value[0]
#define FN_DrawText 254
#define DRAWTEXT_TXT$ str_var[0].sid_value[0].value[0]
#define DRAWTEXT_X num_var[0].nid_value[0].value[0]
#define DRAWTEXT_Y num_var[1].nid_value[0].value[0]
#define FN_DrawText_Shaded 255
#define DRAWTEXT_SHADED_TXT$ str_var[0].sid_value[0].value[0]
#define DRAWTEXT_SHADED_X num_var[0].nid_value[0].value[0]
#define DRAWTEXT_SHADED_Y num_var[1].nid_value[0].value[0]
#define DRAWTEXT_SHADED_FG_COLOR num_var[2].nid_value[0].value[0]
#define DRAWTEXT_SHADED_BG_COLOR num_var[3].nid_value[0].value[0]
#define FN_DrawText_Blended 256
#define DRAWTEXT_BLENDED_TXT$ str_var[0].sid_value[0].value[0]
#define DRAWTEXT_BLENDED_X num_var[0].nid_value[0].value[0]
#define DRAWTEXT_BLENDED_Y num_var[1].nid_value[0].value[0]
#define FN_RenderText 257
#define RENDERTEXT_SLOT num_var[0].nid_value[0].value[0]
#define RENDERTEXT_TXT$ str_var[0].sid_value[0].value[0]
#define FN_GetTextSize 258
#define GETTEXTSIZE_SLOT num_var[0].nid_value[0].value[0]
#define GETTEXTSIZE_TXT$ str_var[0].sid_value[0].value[0]
#define GETTEXTSIZE_W num_var[1].nid_value[0].value[0]
#define GETTEXTSIZE_H num_var[2].nid_value[0].value[0]
#define FN_TouchPressure 259
#define FN_GetTouch 260
#define GETTOUCH_STATUS num_var[0].nid_value[0].value[0]
#define GETTOUCH_X num_var[1].nid_value[0].value[0]
#define GETTOUCH_Y num_var[2].nid_value[0].value[0]
#define GETTOUCH_DX num_var[3].nid_value[0].value[0]
#define GETTOUCH_DY num_var[4].nid_value[0].value[0]
#define FN_GetMultiTouch 261
#define GETMULTITOUCH_STATUS num_var[0].nid_value[0].value[0]
#define GETMULTITOUCH_X num_var[1].nid_value[0].value[0]
#define GETMULTITOUCH_Y num_var[2].nid_value[0].value[0]
#define GETMULTITOUCH_FINGERS num_var[3].nid_value[0].value[0]
#define GETMULTITOUCH_DIST num_var[4].nid_value[0].value[0]
#define GETMULTITOUCH_THETA num_var[5].nid_value[0].value[0]
#define FN_GetTouchFinger 262
#define GETTOUCHFINGER_FINGER num_var[0].nid_value[0].value[0]
#define GETTOUCHFINGER_X num_var[1].nid_value[0].value[0]
#define GETTOUCHFINGER_Y num_var[2].nid_value[0].value[0]
#define GETTOUCHFINGER_PRESSURE num_var[3].nid_value[0].value[0]
#define FN_NumFingers 263
#define FN_TCP_SocketOpen 264
#define TCP_SOCKETOPEN_SOCKET num_var[0].nid_value[0].value[0]
#define TCP_SOCKETOPEN_HOST$ str_var[0].sid_value[0].value[0]
#define TCP_SOCKETOPEN_PORT num_var[1].nid_value[0].value[0]
#define FN_TCP_SocketClose 265
#define TCP_SOCKETCLOSE_SOCKET num_var[0].nid_value[0].value[0]
#define FN_TCP_RemoteHost 266
#define TCP_REMOTEHOST_SOCKET num_var[0].nid_value[0].value[0]
#define FN_TCP_RemotePort 267
#define TCP_REMOTEPORT_SOCKET num_var[0].nid_value[0].value[0]
#define FN_TCP_GetData 268
#define TCP_GETDATA_SOCKET num_var[0].nid_value[0].value[0]
#define TCP_GETDATA_SDATA$ str_var[0].sid_value[0].value[0]
#define TCP_GETDATA_NUMBYTES num_var[1].nid_value[0].value[0]
#define FN_TCP_SendData 269
#define TCP_SENDDATA_SOCKET num_var[0].nid_value[0].value[0]
#define TCP_SENDDATA_SDATA$ str_var[0].sid_value[0].value[0]
#define FN_TCP_AcceptSocket 270
#define TCP_ACCEPTSOCKET_SERVER num_var[0].nid_value[0].value[0]
#define TCP_ACCEPTSOCKET_CLIENT num_var[1].nid_value[0].value[0]
#define FN_UDP_SocketOpen 271
#define UDP_SOCKETOPEN_SOCKET num_var[0].nid_value[0].value[0]
#define UDP_SOCKETOPEN_PORT num_var[1].nid_value[0].value[0]
#define FN_UDP_SocketClose 272
#define UDP_SOCKETCLOSE_SOCKET num_var[0].nid_value[0].value[0]
#define FN_UDP_GetData 273
#define UDP_GETDATA_SOCKET num_var[0].nid_value[0].value[0]
#define UDP_GETDATA_SDATA$ str_var[0].sid_value[0].value[0]
#define UDP_GETDATA_HOST$ str_var[1].sid_value[0].value[0]
#define UDP_GETDATA_PORT num_var[1].nid_value[0].value[0]
#define FN_UDP_Length 274
#define FN_UDP_MaxLength 275
#define FN_UDP_RemoteHost$ 276
#define UDP_REMOTEHOST$_SOCKET num_var[0].nid_value[0].value[0]
#define FN_UDP_RemotePort 277
#define UDP_REMOTEPORT_SOCKET num_var[0].nid_value[0].value[0]
#define FN_UDP_SendData 278
#define UDP_SENDDATA_SOCKET num_var[0].nid_value[0].value[0]
#define UDP_SENDDATA_SDATA$ str_var[0].sid_value[0].value[0]
#define UDP_SENDDATA_HOST$ str_var[1].sid_value[0].value[0]
#define UDP_SENDDATA_PORT num_var[1].nid_value[0].value[0]
#define FN_LoadVideo 279
#define LOADVIDEO_VID$ str_var[0].sid_value[0].value[0]
#define FN_PlayVideo 280
#define PLAYVIDEO_VLOOPS num_var[0].nid_value[0].value[0]
#define FN_PauseVideo 281
#define FN_StopVideo 282
#define FN_SetVideoPosition 283
#define SETVIDEOPOSITION_POS num_var[0].nid_value[0].value[0]
#define FN_ResumeVideo 284
#define FN_VideoPosition 285
#define FN_DeleteVideo 286
#define FN_VideoIsPlaying 287
#define FN_VideoEnd 288
#define FN_GetVideoStats 289
#define GETVIDEOSTATS_VFILE$ str_var[0].sid_value[0].value[0]
#define GETVIDEOSTATS_VLEN num_var[0].nid_value[0].value[0]
#define GETVIDEOSTATS_VFPS num_var[1].nid_value[0].value[0]
#define GETVIDEOSTATS_FRAME_W num_var[2].nid_value[0].value[0]
#define GETVIDEOSTATS_FRAME_H num_var[3].nid_value[0].value[0]
#define FN_SetVideoDrawRect 290
#define SETVIDEODRAWRECT_X num_var[0].nid_value[0].value[0]
#define SETVIDEODRAWRECT_Y num_var[1].nid_value[0].value[0]
#define SETVIDEODRAWRECT_W num_var[2].nid_value[0].value[0]
#define SETVIDEODRAWRECT_H num_var[3].nid_value[0].value[0]
#define FN_GetVideoDrawRect 291
#define GETVIDEODRAWRECT_X num_var[0].nid_value[0].value[0]
#define GETVIDEODRAWRECT_Y num_var[1].nid_value[0].value[0]
#define GETVIDEODRAWRECT_W num_var[2].nid_value[0].value[0]
#define GETVIDEODRAWRECT_H num_var[3].nid_value[0].value[0]
#define FN_GetVideoSize 292
#define GETVIDEOSIZE_W num_var[0].nid_value[0].value[0]
#define GETVIDEOSIZE_H num_var[1].nid_value[0].value[0]
#define FN_VideoExists 293
#define FN_SetVideoAlpha 294
#define SETVIDEOALPHA_A num_var[0].nid_value[0].value[0]
#define FN_System 295
#define SYSTEM_CMD$ str_var[0].sid_value[0].value[0]
#define FN_OS$ 296
#define FN_Command$ 297
#define COMMAND$_ARG num_var[0].nid_value[0].value[0]
#define FN_NumCommands 298
#define FN_Env$ 299
#define ENV$_V$ str_var[0].sid_value[0].value[0]
#define FN_SetEnv$ 300
#define SETENV$_V$ str_var[0].sid_value[0].value[0]
#define FN_PrefPath$ 301
#define PREFPATH$_ORG_NAME$ str_var[0].sid_value[0].value[0]
#define PREFPATH$_APP_NAME$ str_var[1].sid_value[0].value[0]
