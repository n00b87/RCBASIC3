pushd %~dp0

mkdir obj >NUL
mkdir obj\Release>NUL

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c build_menu.cpp ^
                                    -o obj\Release\build_menu.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_projectSettings_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_projectSettings_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_replace_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_replace_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_setColorScheme_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_setColorScheme_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_editrc_distribute_dialog.cpp ^
                                    -o obj\Release\rcbasic_editrc_distribute_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c tools_menu.cpp ^
                                    -o obj\Release\tools_menu.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c exec_process.cpp ^
                                    -o obj\Release\exec_process.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c help_menu.cpp ^
                                    -o obj\Release\help_menu.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c parserThread.cpp ^
                                    -o obj\Release\parserThread.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c projects.cpp ^
                                    -o obj\Release\projects.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rc_closeFileSavePrompt_dialog.cpp ^
                                    -o obj\Release\rc_closeFileSavePrompt_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rc_closeProjectSavePrompt_dialog.cpp ^
                                    -o obj\Release\rc_closeProjectSavePrompt_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rc_find_dialog.cpp ^
                                    -o obj\Release\rc_find_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rc_ideApp.cpp ^
                                    -o obj\Release\rc_ideApp.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rc_newFile_dialog.cpp ^
                                    -o obj\Release\rc_newFile_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit.cpp ^
                                    -o obj\Release\rcbasic_edit.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_fileProperties_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_fileProperties_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_frame.cpp ^
                                    -o obj\Release\rcbasic_edit_frame.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_gotoLine_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_gotoLine_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_newProject_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_newProject_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_projectEnvironment_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_projectEnvironment_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_projectVariableEdit_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_projectVariableEdit_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_searchWrap_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_searchWrap_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_editrc_cancelDistProcess_dialog.cpp ^
                                    -o obj\Release\rcbasic_editrc_cancelDistProcess_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_editrc_distProcess_dialog.cpp ^
                                    -o obj\Release\rcbasic_editrc_distProcess_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_editrc_genKey_dialog.cpp ^
                                    -o obj\Release\rcbasic_editrc_genKey_dialog.o

call windres.exe -I%WX_HOME%\include -J rc -O coff -i resource.rc -o obj\Release\resource.res


call mingw32-g++.exe %LIB_PATH% -o bin\Release\rcbasic_edit.exe ^
                                obj\Release\build_menu.o ^
                                obj\Release\help_menu.o ^
                                obj\Release\parserThread.o ^
                                obj\Release\projects.o ^
                                obj\Release\rc_closeFileSavePrompt_dialog.o ^
                                obj\Release\rc_closeProjectSavePrompt_dialog.o ^
                                obj\Release\rc_find_dialog.o ^
                                obj\Release\rc_ideApp.o ^
                                obj\Release\rc_newFile_dialog.o ^
                                obj\Release\rcbasic_edit.o ^
                                obj\Release\rcbasic_edit_fileProperties_dialog.o ^
                                obj\Release\rcbasic_edit_frame.o ^
                                obj\Release\rcbasic_edit_gotoLine_dialog.o ^
                                obj\Release\rcbasic_edit_newProject_dialog.o ^
                                obj\Release\rcbasic_edit_projectEnvironment_dialog.o ^
                                obj\Release\rcbasic_edit_projectSettings_dialog.o ^
                                obj\Release\rcbasic_edit_projectVariableEdit_dialog.o ^
                                obj\Release\rcbasic_edit_replace_dialog.o ^
                                obj\Release\rcbasic_edit_searchWrap_dialog.o ^
                                obj\Release\rcbasic_edit_setColorScheme_dialog.o ^
                                obj\Release\rcbasic_editrc_cancelDistProcess_dialog.o ^
                                obj\Release\rcbasic_editrc_distProcess_dialog.o ^
                                obj\Release\rcbasic_editrc_distribute_dialog.o ^
                                obj\Release\rcbasic_editrc_genKey_dialog.o ^
                                obj\Release\tools_menu.o  ^
                                obj\Release\resource.res ^
                                -Wl,--allow-multiple-definition -s -mwindows  ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxbase30u.a ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxmsw30u_aui.a ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxmsw30u_core.a ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxmsw30u_stc.a ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxscintilla.a ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxmsw30u_richtext.a


popd
