#ifndef RC_BUILTIN_H_INCLUDED
#define RC_BUILTIN_H_INCLUDED
#include "identifier.h"

void init_embedded()
{
embed_function("FPrint", ID_TYPE_SUB);
add_embedded_arg("txt$", ID_TYPE_STR);
embed_function("Input$", ID_TYPE_FN_STR);
add_embedded_arg("prompt$", ID_TYPE_STR);
embed_function("ArrayDim", ID_TYPE_FN_NUM);
add_embedded_arg("id", ID_TYPE_BYREF_NUM);
embed_function("StringArrayDim", ID_TYPE_FN_NUM);
add_embedded_arg("id$", ID_TYPE_BYREF_STR);
embed_function("NumberArrayDim", ID_TYPE_FN_NUM);
add_embedded_arg("id", ID_TYPE_BYREF_NUM);
embed_function("ArraySize", ID_TYPE_FN_NUM);
add_embedded_arg("id", ID_TYPE_BYREF_NUM);
add_embedded_arg("array_dim", ID_TYPE_NUM);
embed_function("StringArraySize", ID_TYPE_FN_NUM);
add_embedded_arg("id$", ID_TYPE_BYREF_STR);
add_embedded_arg("array_dim", ID_TYPE_NUM);
embed_function("NumberArraySize", ID_TYPE_FN_NUM);
add_embedded_arg("id", ID_TYPE_BYREF_NUM);
add_embedded_arg("array_dim", ID_TYPE_NUM);
embed_function("Abs", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("ACos", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("AndBit", ID_TYPE_FN_NUM);
add_embedded_arg("a", ID_TYPE_NUM);
add_embedded_arg("b", ID_TYPE_NUM);
embed_function("ASin", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("ATan", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Bin$", ID_TYPE_FN_STR);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("CInt32", ID_TYPE_FN_NUM);
add_embedded_arg("i", ID_TYPE_NUM);
embed_function("CInt64", ID_TYPE_FN_NUM);
add_embedded_arg("i", ID_TYPE_NUM);
embed_function("Cos", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Exp", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Frac", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Hex$", ID_TYPE_FN_STR);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Int", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Log", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Max", ID_TYPE_FN_NUM);
add_embedded_arg("a", ID_TYPE_NUM);
add_embedded_arg("b", ID_TYPE_NUM);
embed_function("Min", ID_TYPE_FN_NUM);
add_embedded_arg("a", ID_TYPE_NUM);
add_embedded_arg("b", ID_TYPE_NUM);
embed_function("OrBit", ID_TYPE_FN_NUM);
add_embedded_arg("a", ID_TYPE_NUM);
add_embedded_arg("b", ID_TYPE_NUM);
embed_function("Randomize", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Rand", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Round", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Sign", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Sin", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Sqrt", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Tan", ID_TYPE_FN_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("XOrBit", ID_TYPE_FN_NUM);
add_embedded_arg("a", ID_TYPE_NUM);
add_embedded_arg("b", ID_TYPE_NUM);
embed_function("Asc", ID_TYPE_FN_NUM);
add_embedded_arg("c$", ID_TYPE_STR);
embed_function("Chr$", ID_TYPE_FN_STR);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Insert$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("tgt$", ID_TYPE_STR);
add_embedded_arg("pos", ID_TYPE_NUM);
embed_function("InStr", ID_TYPE_FN_NUM);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("substr$", ID_TYPE_STR);
embed_function("LCase$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
embed_function("Left$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Length", ID_TYPE_FN_NUM);
add_embedded_arg("src$", ID_TYPE_STR);
embed_function("LTrim$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
embed_function("Mid$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("start", ID_TYPE_NUM);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Replace$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("rpc$", ID_TYPE_STR);
add_embedded_arg("pos", ID_TYPE_NUM);
embed_function("ReplaceSubstr$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("tgt$", ID_TYPE_STR);
add_embedded_arg("rpc$", ID_TYPE_STR);
embed_function("Reverse$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
embed_function("Right$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("RTrim$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
embed_function("StringFill$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Str$", ID_TYPE_FN_STR);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Str_F$", ID_TYPE_FN_STR);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Str_S$", ID_TYPE_FN_STR);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Tally", ID_TYPE_FN_NUM);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("substr$", ID_TYPE_STR);
embed_function("Trim$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
embed_function("UCase$", ID_TYPE_FN_STR);
add_embedded_arg("src$", ID_TYPE_STR);
embed_function("Val", ID_TYPE_FN_NUM);
add_embedded_arg("n$", ID_TYPE_STR);
embed_function("Push_N", ID_TYPE_SUB);
add_embedded_arg("n", ID_TYPE_NUM);
embed_function("Pop_N", ID_TYPE_FN_NUM);
embed_function("Push_S", ID_TYPE_SUB);
add_embedded_arg("s$", ID_TYPE_STR);
embed_function("Pop_S$", ID_TYPE_FN_STR);
embed_function("Stack_Size_N", ID_TYPE_FN_NUM);
embed_function("Stack_Size_S", ID_TYPE_FN_NUM);
embed_function("FileOpen", ID_TYPE_FN_NUM);
add_embedded_arg("stream", ID_TYPE_NUM);
add_embedded_arg("fileName$", ID_TYPE_STR);
add_embedded_arg("mode", ID_TYPE_NUM);
embed_function("FileClose", ID_TYPE_SUB);
add_embedded_arg("stream", ID_TYPE_NUM);
embed_function("ReadByte", ID_TYPE_FN_NUM);
add_embedded_arg("stream", ID_TYPE_NUM);
embed_function("WriteByte", ID_TYPE_SUB);
add_embedded_arg("stream", ID_TYPE_NUM);
add_embedded_arg("byte", ID_TYPE_NUM);
embed_function("ReadLine$", ID_TYPE_FN_STR);
add_embedded_arg("stream", ID_TYPE_NUM);
embed_function("WriteLine", ID_TYPE_SUB);
add_embedded_arg("stream", ID_TYPE_NUM);
add_embedded_arg("txt$", ID_TYPE_STR);
embed_function("CopyFile", ID_TYPE_SUB);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("dst$", ID_TYPE_STR);
embed_function("RemoveFile", ID_TYPE_FN_NUM);
add_embedded_arg("fileName$", ID_TYPE_STR);
embed_function("FileExists", ID_TYPE_FN_NUM);
add_embedded_arg("fileName$", ID_TYPE_STR);
embed_function("MoveFile", ID_TYPE_FN_NUM);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("dst$", ID_TYPE_STR);
embed_function("RenameFile", ID_TYPE_FN_NUM);
add_embedded_arg("src$", ID_TYPE_STR);
add_embedded_arg("dst$", ID_TYPE_STR);
embed_function("FileLength", ID_TYPE_FN_NUM);
add_embedded_arg("fileName$", ID_TYPE_STR);
embed_function("Tell", ID_TYPE_FN_NUM);
add_embedded_arg("stream", ID_TYPE_NUM);
embed_function("Seek", ID_TYPE_FN_NUM);
add_embedded_arg("stream", ID_TYPE_NUM);
add_embedded_arg("pos", ID_TYPE_NUM);
embed_function("EOF", ID_TYPE_FN_NUM);
add_embedded_arg("stream", ID_TYPE_NUM);
embed_function("FreeFile", ID_TYPE_FN_NUM);
embed_function("ChangeDir", ID_TYPE_SUB);
add_embedded_arg("p$", ID_TYPE_STR);
embed_function("DirExists", ID_TYPE_FN_NUM);
add_embedded_arg("p$", ID_TYPE_STR);
embed_function("DirFirst$", ID_TYPE_FN_STR);
embed_function("Dir$", ID_TYPE_FN_STR);
embed_function("DirNext$", ID_TYPE_FN_STR);
embed_function("MakeDir", ID_TYPE_FN_NUM);
add_embedded_arg("p$", ID_TYPE_STR);
embed_function("RemoveDir", ID_TYPE_FN_NUM);
add_embedded_arg("p$", ID_TYPE_STR);
embed_function("Date$", ID_TYPE_FN_STR);
embed_function("Ticks", ID_TYPE_FN_NUM);
embed_function("Time$", ID_TYPE_FN_STR);
embed_function("Timer", ID_TYPE_FN_NUM);
embed_function("Wait", ID_TYPE_SUB);
add_embedded_arg("m_sec", ID_TYPE_NUM);
embed_function("WindowOpen", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("title$", ID_TYPE_STR);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
add_embedded_arg("flag", ID_TYPE_NUM);
embed_function("WindowClose", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("RaiseWindow", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("Window", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("Update", ID_TYPE_SUB);
embed_function("Cls", ID_TYPE_SUB);
embed_function("SetClearColor", ID_TYPE_SUB);
add_embedded_arg("c", ID_TYPE_NUM);
embed_function("ShowWindow", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("HideWindow", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("SetWindowTitle", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("title$", ID_TYPE_STR);
embed_function("WindowTitle$", ID_TYPE_FN_STR);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("SetWindowPosition", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
embed_function("GetWindowPosition", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
embed_function("SetWindowSize", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
embed_function("GetWindowSize", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_BYREF_NUM);
add_embedded_arg("h", ID_TYPE_BYREF_NUM);
embed_function("SetWindowMinSize", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
embed_function("GetWindowMinSize", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_BYREF_NUM);
add_embedded_arg("h", ID_TYPE_BYREF_NUM);
embed_function("SetWindowMaxSize", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
embed_function("GetWindowMaxSize", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_BYREF_NUM);
add_embedded_arg("h", ID_TYPE_BYREF_NUM);
embed_function("WindowIsFullscreen", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("WindowIsVisible", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("WindowIsBordered", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("WindowIsResizable", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("WindowIsMinimized", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("WindowIsMaximized", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("WindowHasInputFocus", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("WindowHasMouseFocus", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("SetWindowFullscreen", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("flag", ID_TYPE_NUM);
embed_function("MaximizeWindow", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("MinimizeWindow", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("SetWindowBorder", ID_TYPE_SUB);
add_embedded_arg("win", ID_TYPE_NUM);
add_embedded_arg("flag", ID_TYPE_NUM);
embed_function("WindowClip", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
embed_function("WindowExists", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("NumWindows", ID_TYPE_FN_NUM);
embed_function("WindowEvent_Close", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("WindowEvent_Maximize", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("WindowEvent_Minimize", ID_TYPE_FN_NUM);
add_embedded_arg("win", ID_TYPE_NUM);
embed_function("CanvasOpen", ID_TYPE_SUB);
add_embedded_arg("c_num", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
add_embedded_arg("viewport_x", ID_TYPE_NUM);
add_embedded_arg("viewport_y", ID_TYPE_NUM);
add_embedded_arg("viewport_w", ID_TYPE_NUM);
add_embedded_arg("viewport_h", ID_TYPE_NUM);
add_embedded_arg("mode", ID_TYPE_NUM);
embed_function("CanvasClose", ID_TYPE_SUB);
add_embedded_arg("c_num", ID_TYPE_NUM);
embed_function("SetCanvasVisible", ID_TYPE_SUB);
add_embedded_arg("c_num", ID_TYPE_NUM);
add_embedded_arg("flag", ID_TYPE_NUM);
embed_function("CanvasIsVisible", ID_TYPE_FN_NUM);
add_embedded_arg("c_num", ID_TYPE_NUM);
embed_function("SetCanvasViewport", ID_TYPE_SUB);
add_embedded_arg("cnum", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
embed_function("GetCanvasViewport", ID_TYPE_SUB);
add_embedded_arg("c_num", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
add_embedded_arg("w", ID_TYPE_BYREF_NUM);
add_embedded_arg("h", ID_TYPE_BYREF_NUM);
embed_function("Canvas", ID_TYPE_SUB);
add_embedded_arg("c_num", ID_TYPE_NUM);
embed_function("SetCanvasOffset", ID_TYPE_SUB);
add_embedded_arg("c_num", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
embed_function("GetCanvasOffset", ID_TYPE_SUB);
add_embedded_arg("c_num", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
embed_function("GetCanvasSize", ID_TYPE_SUB);
add_embedded_arg("c_num", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_BYREF_NUM);
add_embedded_arg("h", ID_TYPE_BYREF_NUM);
embed_function("ClearCanvas", ID_TYPE_SUB);
embed_function("SetCanvasAlpha", ID_TYPE_SUB);
add_embedded_arg("c_num", ID_TYPE_NUM);
add_embedded_arg("a", ID_TYPE_NUM);
embed_function("CopyCanvas", ID_TYPE_SUB);
add_embedded_arg("src", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
add_embedded_arg("dst", ID_TYPE_NUM);
add_embedded_arg("dx", ID_TYPE_NUM);
add_embedded_arg("dy", ID_TYPE_NUM);
embed_function("CloneCanvas", ID_TYPE_SUB);
add_embedded_arg("src", ID_TYPE_NUM);
add_embedded_arg("dst", ID_TYPE_NUM);
embed_function("SetCanvasZ", ID_TYPE_SUB);
add_embedded_arg("c_num", ID_TYPE_NUM);
add_embedded_arg("z", ID_TYPE_NUM);
embed_function("CanvasClip", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
embed_function("Box", ID_TYPE_SUB);
add_embedded_arg("x1", ID_TYPE_NUM);
add_embedded_arg("y1", ID_TYPE_NUM);
add_embedded_arg("x2", ID_TYPE_NUM);
add_embedded_arg("y2", ID_TYPE_NUM);
embed_function("BoxFill", ID_TYPE_SUB);
add_embedded_arg("x1", ID_TYPE_NUM);
add_embedded_arg("y1", ID_TYPE_NUM);
add_embedded_arg("x2", ID_TYPE_NUM);
add_embedded_arg("y2", ID_TYPE_NUM);
embed_function("Circle", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("radius", ID_TYPE_NUM);
embed_function("CircleFill", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("radius", ID_TYPE_NUM);
embed_function("Ellipse", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("rx", ID_TYPE_NUM);
add_embedded_arg("ry", ID_TYPE_NUM);
embed_function("EllipseFill", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("rx", ID_TYPE_NUM);
add_embedded_arg("ry", ID_TYPE_NUM);
embed_function("FloodFill", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
embed_function("GetPixel", ID_TYPE_FN_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
embed_function("SetColor", ID_TYPE_SUB);
add_embedded_arg("c", ID_TYPE_NUM);
embed_function("Line", ID_TYPE_SUB);
add_embedded_arg("x1", ID_TYPE_NUM);
add_embedded_arg("y1", ID_TYPE_NUM);
add_embedded_arg("x2", ID_TYPE_NUM);
add_embedded_arg("y2", ID_TYPE_NUM);
embed_function("Poly", ID_TYPE_SUB);
add_embedded_arg("n", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
embed_function("PolyFill", ID_TYPE_SUB);
add_embedded_arg("n", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
embed_function("Rect", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
embed_function("RectFill", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
embed_function("RoundRect", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
add_embedded_arg("r", ID_TYPE_NUM);
embed_function("RoundRectFill", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
add_embedded_arg("r", ID_TYPE_NUM);
embed_function("RGB", ID_TYPE_FN_NUM);
add_embedded_arg("r", ID_TYPE_NUM);
add_embedded_arg("g", ID_TYPE_NUM);
add_embedded_arg("b", ID_TYPE_NUM);
embed_function("RGBA", ID_TYPE_FN_NUM);
add_embedded_arg("r", ID_TYPE_NUM);
add_embedded_arg("g", ID_TYPE_NUM);
add_embedded_arg("b", ID_TYPE_NUM);
add_embedded_arg("a", ID_TYPE_NUM);
embed_function("PSet", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
embed_function("LoadImage", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("img$", ID_TYPE_STR);
embed_function("LoadImage_Ex", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("img$", ID_TYPE_STR);
add_embedded_arg("colkey", ID_TYPE_NUM);
embed_function("ImageFromBuffer", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
add_embedded_arg("buffer", ID_TYPE_BYREF_NUM);
embed_function("ImageFromBuffer_Ex", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
add_embedded_arg("buffer", ID_TYPE_BYREF_NUM);
add_embedded_arg("colkey", ID_TYPE_NUM);
embed_function("ImageExists", ID_TYPE_FN_NUM);
add_embedded_arg("slot", ID_TYPE_NUM);
embed_function("ColorKey", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("c", ID_TYPE_NUM);
embed_function("CopyImage", ID_TYPE_SUB);
add_embedded_arg("src", ID_TYPE_NUM);
add_embedded_arg("dst", ID_TYPE_NUM);
embed_function("DeleteImage", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
embed_function("SetImageAlpha", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("a", ID_TYPE_NUM);
embed_function("ImageAlpha", ID_TYPE_FN_NUM);
add_embedded_arg("slot", ID_TYPE_NUM);
embed_function("GetImageSize", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_BYREF_NUM);
add_embedded_arg("h", ID_TYPE_BYREF_NUM);
embed_function("FlipImage", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
add_embedded_arg("v", ID_TYPE_NUM);
embed_function("DrawImage", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
embed_function("DrawImage_Blit", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("src_x", ID_TYPE_NUM);
add_embedded_arg("src_y", ID_TYPE_NUM);
add_embedded_arg("src_w", ID_TYPE_NUM);
add_embedded_arg("src_h", ID_TYPE_NUM);
embed_function("DrawImage_Blit_Ex", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
add_embedded_arg("src_x", ID_TYPE_NUM);
add_embedded_arg("src_y", ID_TYPE_NUM);
add_embedded_arg("src_w", ID_TYPE_NUM);
add_embedded_arg("src_h", ID_TYPE_NUM);
embed_function("DrawImage_Rotate", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("angle", ID_TYPE_NUM);
embed_function("DrawImage_Rotate_Ex", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("src_x", ID_TYPE_NUM);
add_embedded_arg("src_y", ID_TYPE_NUM);
add_embedded_arg("src_w", ID_TYPE_NUM);
add_embedded_arg("src_h", ID_TYPE_NUM);
add_embedded_arg("angle", ID_TYPE_NUM);
embed_function("DrawImage_Zoom", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("zx", ID_TYPE_NUM);
add_embedded_arg("zy", ID_TYPE_NUM);
embed_function("DrawImage_Zoom_Ex", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("src_x", ID_TYPE_NUM);
add_embedded_arg("src_y", ID_TYPE_NUM);
add_embedded_arg("src_w", ID_TYPE_NUM);
add_embedded_arg("src_h", ID_TYPE_NUM);
add_embedded_arg("zx", ID_TYPE_NUM);
add_embedded_arg("zy", ID_TYPE_NUM);
embed_function("DrawImage_Rotozoom", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("angle", ID_TYPE_NUM);
add_embedded_arg("zx", ID_TYPE_NUM);
add_embedded_arg("zy", ID_TYPE_NUM);
embed_function("DrawImage_Rotozoom_Ex", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("src_x", ID_TYPE_NUM);
add_embedded_arg("src_y", ID_TYPE_NUM);
add_embedded_arg("src_w", ID_TYPE_NUM);
add_embedded_arg("src_h", ID_TYPE_NUM);
add_embedded_arg("angle", ID_TYPE_NUM);
add_embedded_arg("zx", ID_TYPE_NUM);
add_embedded_arg("zy", ID_TYPE_NUM);
embed_function("InKey", ID_TYPE_FN_NUM);
embed_function("Key", ID_TYPE_FN_NUM);
add_embedded_arg("key_code", ID_TYPE_NUM);
embed_function("WaitKey", ID_TYPE_FN_NUM);
embed_function("HideMouse", ID_TYPE_SUB);
embed_function("ShowMouse", ID_TYPE_SUB);
embed_function("MouseIsVisible", ID_TYPE_FN_NUM);
embed_function("GetMouse", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
add_embedded_arg("mb1", ID_TYPE_BYREF_NUM);
add_embedded_arg("mb2", ID_TYPE_BYREF_NUM);
add_embedded_arg("mb3", ID_TYPE_BYREF_NUM);
embed_function("MouseX", ID_TYPE_FN_NUM);
embed_function("MouseY", ID_TYPE_FN_NUM);
embed_function("MouseButton", ID_TYPE_FN_NUM);
add_embedded_arg("mb", ID_TYPE_NUM);
embed_function("GetMouseWheel", ID_TYPE_SUB);
add_embedded_arg("x_axis", ID_TYPE_BYREF_NUM);
add_embedded_arg("y_axis", ID_TYPE_BYREF_NUM);
embed_function("MouseWheelX", ID_TYPE_FN_NUM);
embed_function("MouseWheelY", ID_TYPE_FN_NUM);
embed_function("SoundFromBuffer", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("buffer", ID_TYPE_BYREF_NUM);
add_embedded_arg("buffer_size", ID_TYPE_NUM);
add_embedded_arg("vol", ID_TYPE_NUM);
embed_function("LoadSound", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("snd_file$", ID_TYPE_STR);
embed_function("LoadMusic", ID_TYPE_SUB);
add_embedded_arg("music_file$", ID_TYPE_STR);
embed_function("PlaySound", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("channel", ID_TYPE_NUM);
add_embedded_arg("loops", ID_TYPE_NUM);
embed_function("PlaySoundTimed", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("channel", ID_TYPE_NUM);
add_embedded_arg("loops", ID_TYPE_NUM);
add_embedded_arg("ms", ID_TYPE_NUM);
embed_function("PlayMusic", ID_TYPE_SUB);
add_embedded_arg("mLoops", ID_TYPE_NUM);
embed_function("PauseSound", ID_TYPE_SUB);
add_embedded_arg("channel", ID_TYPE_NUM);
embed_function("ResumeSound", ID_TYPE_SUB);
add_embedded_arg("channel", ID_TYPE_NUM);
embed_function("PauseMusic", ID_TYPE_SUB);
embed_function("ResumeMusic", ID_TYPE_SUB);
embed_function("DeleteSound", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
embed_function("DeleteMusic", ID_TYPE_SUB);
embed_function("FadeMusicIn", ID_TYPE_SUB);
add_embedded_arg("fade_time", ID_TYPE_NUM);
add_embedded_arg("loops", ID_TYPE_NUM);
embed_function("FadeMusicOut", ID_TYPE_SUB);
add_embedded_arg("fade_time", ID_TYPE_NUM);
embed_function("MusicExists", ID_TYPE_FN_NUM);
embed_function("SetMusicVolume", ID_TYPE_SUB);
add_embedded_arg("vol", ID_TYPE_NUM);
embed_function("MusicVolume", ID_TYPE_FN_NUM);
embed_function("SetMusicPosition", ID_TYPE_SUB);
add_embedded_arg("pos", ID_TYPE_NUM);
embed_function("MusicPosition", ID_TYPE_FN_NUM);
embed_function("RewindMusic", ID_TYPE_SUB);
embed_function("SetSoundChannels", ID_TYPE_SUB);
add_embedded_arg("max_channels", ID_TYPE_NUM);
embed_function("NumSoundChannels", ID_TYPE_FN_NUM);
embed_function("SoundIsEnabled", ID_TYPE_FN_NUM);
embed_function("SoundExists", ID_TYPE_FN_NUM);
add_embedded_arg("slot", ID_TYPE_NUM);
embed_function("SetChannelVolume", ID_TYPE_SUB);
add_embedded_arg("channel", ID_TYPE_NUM);
add_embedded_arg("vol", ID_TYPE_NUM);
embed_function("ChannelVolume", ID_TYPE_FN_NUM);
add_embedded_arg("channel", ID_TYPE_NUM);
embed_function("SetSoundVolume", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("vol", ID_TYPE_NUM);
embed_function("SoundVolume", ID_TYPE_FN_NUM);
add_embedded_arg("slot", ID_TYPE_NUM);
embed_function("StopMusic", ID_TYPE_SUB);
embed_function("StopSound", ID_TYPE_SUB);
add_embedded_arg("channel", ID_TYPE_NUM);
embed_function("NumJoysticks", ID_TYPE_FN_NUM);
embed_function("NumJoyAxes", ID_TYPE_FN_NUM);
add_embedded_arg("joy_num", ID_TYPE_NUM);
embed_function("NumJoyButtons", ID_TYPE_FN_NUM);
add_embedded_arg("joy_num", ID_TYPE_NUM);
embed_function("NumJoyHats", ID_TYPE_FN_NUM);
add_embedded_arg("joy_num", ID_TYPE_NUM);
embed_function("NumJoyTrackBalls", ID_TYPE_FN_NUM);
add_embedded_arg("joy_num", ID_TYPE_NUM);
embed_function("JoyAxis", ID_TYPE_FN_NUM);
add_embedded_arg("joy_num", ID_TYPE_NUM);
add_embedded_arg("joy_axis", ID_TYPE_NUM);
embed_function("JoyButton", ID_TYPE_FN_NUM);
add_embedded_arg("joy_num", ID_TYPE_NUM);
add_embedded_arg("joy_button", ID_TYPE_NUM);
embed_function("JoyHat", ID_TYPE_FN_NUM);
add_embedded_arg("joy_num", ID_TYPE_NUM);
add_embedded_arg("joy_hat", ID_TYPE_NUM);
embed_function("GetJoyTrackBall", ID_TYPE_SUB);
add_embedded_arg("joy_num", ID_TYPE_NUM);
add_embedded_arg("ball", ID_TYPE_NUM);
add_embedded_arg("dx", ID_TYPE_BYREF_NUM);
add_embedded_arg("dy", ID_TYPE_BYREF_NUM);
embed_function("JoyName$", ID_TYPE_FN_STR);
add_embedded_arg("joy_num", ID_TYPE_NUM);
embed_function("JoystickIsConnected", ID_TYPE_FN_NUM);
add_embedded_arg("joy_num", ID_TYPE_NUM);
embed_function("GetCursor", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
embed_function("PrintS", ID_TYPE_SUB);
add_embedded_arg("txt$", ID_TYPE_STR);
embed_function("InputS$", ID_TYPE_FN_STR);
add_embedded_arg("prompt$", ID_TYPE_STR);
embed_function("ZoneInputS$", ID_TYPE_FN_STR);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
embed_function("Locate", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
embed_function("ReadInput_Start", ID_TYPE_SUB);
embed_function("ReadInput_Stop", ID_TYPE_SUB);
embed_function("ReadInput_Text$", ID_TYPE_FN_STR);
embed_function("ReadInput_SetText", ID_TYPE_SUB);
add_embedded_arg("txt$", ID_TYPE_STR);
embed_function("ReadInput_ToggleBackspace", ID_TYPE_SUB);
add_embedded_arg("flag", ID_TYPE_NUM);
embed_function("LoadFont", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("fnt_file$", ID_TYPE_STR);
add_embedded_arg("size", ID_TYPE_NUM);
embed_function("DeleteFont", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
embed_function("FontIsLoaded", ID_TYPE_FN_NUM);
add_embedded_arg("slot", ID_TYPE_NUM);
embed_function("Font", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
embed_function("SetFontStyle", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("style", ID_TYPE_NUM);
embed_function("DrawText", ID_TYPE_SUB);
add_embedded_arg("txt$", ID_TYPE_STR);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
embed_function("DrawText_Shaded", ID_TYPE_SUB);
add_embedded_arg("txt$", ID_TYPE_STR);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("fg_color", ID_TYPE_NUM);
add_embedded_arg("bg_color", ID_TYPE_NUM);
embed_function("DrawText_Blended", ID_TYPE_SUB);
add_embedded_arg("txt$", ID_TYPE_STR);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
embed_function("RenderText", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("txt$", ID_TYPE_STR);
embed_function("GetTextSize", ID_TYPE_SUB);
add_embedded_arg("slot", ID_TYPE_NUM);
add_embedded_arg("txt$", ID_TYPE_STR);
add_embedded_arg("w", ID_TYPE_BYREF_NUM);
add_embedded_arg("h", ID_TYPE_BYREF_NUM);
embed_function("TouchPressure", ID_TYPE_FN_NUM);
embed_function("GetTouch", ID_TYPE_SUB);
add_embedded_arg("status", ID_TYPE_BYREF_NUM);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
add_embedded_arg("dx", ID_TYPE_BYREF_NUM);
add_embedded_arg("dy", ID_TYPE_BYREF_NUM);
embed_function("GetMultiTouch", ID_TYPE_SUB);
add_embedded_arg("status", ID_TYPE_BYREF_NUM);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
add_embedded_arg("fingers", ID_TYPE_BYREF_NUM);
add_embedded_arg("dist", ID_TYPE_BYREF_NUM);
add_embedded_arg("theta", ID_TYPE_BYREF_NUM);
embed_function("GetTouchFinger", ID_TYPE_SUB);
add_embedded_arg("finger", ID_TYPE_NUM);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
add_embedded_arg("pressure", ID_TYPE_BYREF_NUM);
embed_function("NumFingers", ID_TYPE_FN_NUM);
embed_function("TCP_SocketOpen", ID_TYPE_FN_NUM);
add_embedded_arg("socket", ID_TYPE_NUM);
add_embedded_arg("host$", ID_TYPE_STR);
add_embedded_arg("port", ID_TYPE_NUM);
embed_function("TCP_SocketClose", ID_TYPE_SUB);
add_embedded_arg("socket", ID_TYPE_NUM);
embed_function("TCP_RemoteHost", ID_TYPE_FN_NUM);
add_embedded_arg("socket", ID_TYPE_NUM);
embed_function("TCP_RemotePort", ID_TYPE_FN_NUM);
add_embedded_arg("socket", ID_TYPE_NUM);
embed_function("TCP_GetData", ID_TYPE_FN_NUM);
add_embedded_arg("socket", ID_TYPE_NUM);
add_embedded_arg("sData$", ID_TYPE_BYREF_STR);
add_embedded_arg("numBytes", ID_TYPE_NUM);
embed_function("TCP_SendData", ID_TYPE_SUB);
add_embedded_arg("socket", ID_TYPE_NUM);
add_embedded_arg("sData$", ID_TYPE_STR);
embed_function("TCP_AcceptSocket", ID_TYPE_FN_NUM);
add_embedded_arg("server", ID_TYPE_NUM);
add_embedded_arg("client", ID_TYPE_NUM);
embed_function("UDP_SocketOpen", ID_TYPE_FN_NUM);
add_embedded_arg("socket", ID_TYPE_NUM);
add_embedded_arg("port", ID_TYPE_NUM);
embed_function("UDP_SocketClose", ID_TYPE_FN_NUM);
add_embedded_arg("socket", ID_TYPE_NUM);
embed_function("UDP_GetData", ID_TYPE_FN_NUM);
add_embedded_arg("socket", ID_TYPE_NUM);
add_embedded_arg("sData$", ID_TYPE_BYREF_STR);
add_embedded_arg("host$", ID_TYPE_BYREF_STR);
add_embedded_arg("port", ID_TYPE_BYREF_NUM);
embed_function("UDP_Length", ID_TYPE_FN_NUM);
embed_function("UDP_MaxLength", ID_TYPE_FN_NUM);
embed_function("UDP_RemoteHost$", ID_TYPE_FN_STR);
add_embedded_arg("socket", ID_TYPE_NUM);
embed_function("UDP_RemotePort", ID_TYPE_FN_NUM);
add_embedded_arg("socket", ID_TYPE_NUM);
embed_function("UDP_SendData", ID_TYPE_SUB);
add_embedded_arg("socket", ID_TYPE_NUM);
add_embedded_arg("sData$", ID_TYPE_STR);
add_embedded_arg("host$", ID_TYPE_STR);
add_embedded_arg("port", ID_TYPE_NUM);
embed_function("LoadVideo", ID_TYPE_SUB);
add_embedded_arg("vid$", ID_TYPE_STR);
embed_function("PlayVideo", ID_TYPE_SUB);
add_embedded_arg("vLoops", ID_TYPE_NUM);
embed_function("PauseVideo", ID_TYPE_SUB);
embed_function("StopVideo", ID_TYPE_SUB);
embed_function("SetVideoPosition", ID_TYPE_SUB);
add_embedded_arg("pos", ID_TYPE_NUM);
embed_function("ResumeVideo", ID_TYPE_SUB);
embed_function("VideoPosition", ID_TYPE_FN_NUM);
embed_function("DeleteVideo", ID_TYPE_SUB);
embed_function("VideoIsPlaying", ID_TYPE_FN_NUM);
embed_function("VideoEnd", ID_TYPE_FN_NUM);
embed_function("GetVideoStats", ID_TYPE_SUB);
add_embedded_arg("vFile$", ID_TYPE_STR);
add_embedded_arg("vLen", ID_TYPE_BYREF_NUM);
add_embedded_arg("fps", ID_TYPE_BYREF_NUM);
add_embedded_arg("frame_w", ID_TYPE_BYREF_NUM);
add_embedded_arg("frame_h", ID_TYPE_BYREF_NUM);
embed_function("SetVideoDrawRect", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_NUM);
add_embedded_arg("y", ID_TYPE_NUM);
add_embedded_arg("w", ID_TYPE_NUM);
add_embedded_arg("h", ID_TYPE_NUM);
embed_function("GetVideoDrawRect", ID_TYPE_SUB);
add_embedded_arg("x", ID_TYPE_BYREF_NUM);
add_embedded_arg("y", ID_TYPE_BYREF_NUM);
add_embedded_arg("w", ID_TYPE_BYREF_NUM);
add_embedded_arg("h", ID_TYPE_BYREF_NUM);
embed_function("GetVideoSize", ID_TYPE_SUB);
add_embedded_arg("w", ID_TYPE_BYREF_NUM);
add_embedded_arg("h", ID_TYPE_BYREF_NUM);
embed_function("VideoExists", ID_TYPE_FN_NUM);
embed_function("SetVideoAlpha", ID_TYPE_SUB);
add_embedded_arg("a", ID_TYPE_NUM);
embed_function("System", ID_TYPE_FN_NUM);
add_embedded_arg("cmd$", ID_TYPE_STR);
embed_function("OS$", ID_TYPE_FN_STR);
embed_function("Command$", ID_TYPE_FN_STR);
add_embedded_arg("arg", ID_TYPE_NUM);
embed_function("NumCommands", ID_TYPE_FN_NUM);
embed_function("Env$", ID_TYPE_FN_STR);
add_embedded_arg("v$", ID_TYPE_STR);
embed_function("SetEnv$", ID_TYPE_SUB);
add_embedded_arg("v$", ID_TYPE_STR);
embed_function("PrefPath$", ID_TYPE_FN_STR);
add_embedded_arg("org_name$", ID_TYPE_STR);
add_embedded_arg("app_name$", ID_TYPE_STR);

}


#endif // RC_BUILTIN_H_INCLUDED
