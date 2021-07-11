Include "dir_util.bas"
ChangeDir$(SourceDirectory$)

Dim base_dir$ : base_dir$ = Dir$

Include "gui.bas" 'include the gui library
Include "dir_select_win.bas"

If Trim(Env("RCBASIC_HOME")) = "" Then
	Select Case OS$()
	Case "WINDOWS"
		SetEnv("RCBASIC_HOME", Dir$ + "\\..\\..\\rcbasic_32", 1)
		SetEnv("RCBASIC_ANDROID_DIR", Dir$ + "\\rcbasic_android", 1)
	Default
		SetEnv("RCBASIC_HOME", Dir$ + "/../..", 1)
		SetEnv("RCBASIC_ANDROID_DIR", Dir$ + "/rcbasic_android", 1)
	End Select
End If

If Trim(Env("RC_KEYSTORE_DIR")) = "" Then
	SetEnv("RC_KEYSTORE_DIR", base_dir$ + Replace("/../../keystore", "/", path_join$), 1)
ElseIf Right(Trim(Env("RC_KEYSTORE_DIR")), 1) = path_join$ Then
	SetEnv("RC_KEYSTORE_DIR", Left(Trim(Env("RC_KEYSTORE_DIR")), Length(Trim(Env("RC_KEYSTORE_DIR")))-1), 1)
End If

If Not DirExists(Env("RC_KEYSTORE_DIR")) Then
	MakeDir(Env("RC_KEYSTORE_DIR"))
End If

'SetEnv("RCBASIC_ANDROID_DIR", Dir$ + path_join$ + "rcbasic_android", 1)

Dim APP_NAME$
Dim PROJECT_NAME$
Dim PROJECT_CATEGORY$
Dim APP_TYPE$
Dim TERMINAL_FLAG$
Dim TGT_PLATFORMS$

Dim project_dir$
Dim output_dir$
Dim enable_threads$ : enable_threads$ = "false"

Dim Properties_File_Path$ : Properties_File_Path$ = "app.properties"
Dim Properties$[99]
Dim NumProperties : NumProperties = 0

Dim icon_path$

Dim ANDROID_APP_ID$ : ANDROID_APP_ID$ = "com.mycompany.myApp"
Dim ANDROID_ORIENTATION$
Dim ANDROID_KEYSTORE$
Dim ANDROID_KEYSTORE_PASS$
Dim ANDROID_ALIAS$
Dim ANDROID_ALIAS_PASS$
Dim ANDROID_BUILD_RELEASE
Dim ANDROID_BUILD_DEBUG : ANDROID_BUILD_DEBUG = True
Dim ANDROID_JAVA_DIR$

Dim source_file$

Dim call_dir$


Function ExtractName$(bas_file$)
	ext_start = FindLastOf(".", bas_file$)
	file_name$ = Left$(bas_file$, ext_start)
	Return file_name$
End Function


If NumCommands() > 2 Then
	call_dir$ = Command$(1)
	If Not DirExists(call_dir$) Then
		call_dir$ = ""
	End If
	project_dir$ = call_dir$
	source_file$ = Command$(2)
	PROJECT_NAME$ = ExtractName$(source_file$)
	icon_path$ = Dir$ + path_join$ + "icon" + path_join$ + "rcbasic.png"
	output_dir$ = HOME$ + path_join$ + "RCBasic Apps"
Else
	End
End If

Function GetPropertyArg$(arg_name$)
	arg_value$ = ""
	For i = 0 to NumProperties-1 Step 1
		If Left$(Properties$[i], Length(arg_name$)+1) = (arg_name$+"=") Then
			If Length(Properties$[i]) > (Length(arg_name$)+1) Then
				arg_value$ = Mid$(Properties$[i], Length(arg_name$)+1, Length(Properties$[i]) - (Length(arg_name$)+1))
			End If
		ElseIf Properties$[i] = arg_name$ Then
			If i < (NumProperties-1) Then
				arg_value$ = Properties$[i+1]
				i = i + 1
			End If
		End If
	Next
	Return arg_value$
End Function


Sub LoadAppProperties()
	Properties_File=FreeFile
	
	cwd$ = Dir$
		
	ChangeDir(call_dir$)
	
	If Not FileOpen(Properties_File, Properties_File_Path$, TEXT_INPUT) Then
		ChangeDir(cwd$)
		Return
	End If
	
	While Not EOF(Properties_File)
		ln$ = Trim(ReadLine(Properties_File))
		
		If ln$ <> "" Then
			Properties$[NumProperties] = ln$
			NumProperties = NumProperties + 1
		End If
	Wend
	
	FileClose(Properties_File)
	
	ChangeDir(cwd$)
	
	TGT_PLATFORMS$ = GetPropertyArg$("TGT_PLATFORM")
	PROJECT_NAME$ = GetPropertyArg$("PROJECT_NAME")
	PROJECT_CATEGORY$ = GetPropertyArg$("PROJECT_CATEGORY")
	APP_TYPE$ = GetPropertyArg$("APP_TYPE")
	TERMINAL_FLAG$ = GetPropertyArg$("TERMINAL_FLAG")
	project_dir$ = GetPropertyArg$("PROJECT_DIR")
	output_dir$ = GetPropertyArg$("OUTPUT_DIR")
	enable_threads$ = LCase(GetPropertyArg$("ENABLE_WEB_THREADS"))
	icon_path$ = GetPropertyArg$("ICON")
	
	ANDROID_APP_ID$ = GetPropertyArg$("ANDROID_APP_ID")
	ANDROID_ORIENTATION$ = GetPropertyArg$("ANDROID_ORIENTATION")
	ANDROID_KEYSTORE$ = GetPropertyArg$("ANDROID_KEYSTORE")
	ANDROID_KEYSTORE_PASS$ = GetPropertyArg$("ANDROID_KEYSTORE_PASS")
	ANDROID_ALIAS$ = GetPropertyArg$("ANDROID_ALIAS")
	ANDROID_ALIAS_PASS$ = GetPropertyArg$("ANDROID_ALIAS_PASS")
	ANDROID_BUILD_DEBUG = Val(GetPropertyArg$("ANDROID_DEBUG"))
	ANDROID_BUILD_RELEASE = Val(GetPropertyArg$("ANDROID_RELEASE"))
	ANDROID_JAVA_DIR$ = GetPropertyArg$("ANDROID_JAVA_DIR")
	
	If project_dir$ = "" Then
		project_dir$ = call_dir$
	End If
	
	If PROJECT_NAME$ = "" Then
		PROJECT_NAME$ = ExtractName$(source_file$)
	End If
	
	If Not FileExists(icon_path$) Then
		icon_path$ = "icon" + path_join$ + "rcbasic.png"
	End If
	
	If output_dir$ = "" Then
		output_dir$ = HOME$ + path_join$ + "RCBasic Apps"
	End If
	
	If ANDROID_APP_ID$ = "" Then
		ANDROID_APP_ID$ = "com.mycompany.myApp"
	End If
	
	If ANDROID_JAVA_DIR$ = "" Then
		ANDROID_JAVA_DIR$ = Replace(project_dir$ + "/java", "/", path_join$)
	End If
	
End Sub

Sub SaveAppProperties()
	cwd$ = Dir$
	If Properties_File_Path$ <> "" Then
		Properties_File=FreeFile
		
		ChangeDir(call_dir$)
		
		Print "Attempting to output to: ";Properties_File_Path$
		
		If Not FileOpen(Properties_File, Properties_File_Path$, TEXT_OUTPUT) Then
			ChangeDir(cwd$)
			Print "File Not Opened"
			Return
		End If
		
		WriteLine(Properties_File, "TGT_PLATFORM=" + TGT_PLATFORMS$)
		WriteLine(Properties_File, "PROJECT_NAME=" + PROJECT_NAME$)
		WriteLine(Properties_File, "PROJECT_CATEGORY=" + PROJECT_CATEGORY$)
		WriteLine(Properties_File, "APP_TYPE=" + APP_TYPE$)
		WriteLine(Properties_File, "TERMINAL_FLAG=" + TERMINAL_FLAG$)
		WriteLine(Properties_File, "PROJECT_DIR=" + project_dir$)
		WriteLine(Properties_File, "OUTPUT_DIR=" + output_dir$)
		WriteLine(Properties_File, "ENABLE_WEB_THREADS=" + LCase(enable_threads$))
		WriteLine(Properties_File, "ICON=" + icon_path$)
		
		WriteLine(Properties_File, "ANDROID_APP_ID=" + ANDROID_APP_ID$)
		WriteLine(Properties_File, "ANDROID_ORIENTATION=" + ANDROID_ORIENTATION$)
		WriteLine(Properties_File, "ANDROID_KEYSTORE=" + ANDROID_KEYSTORE$)
		'WriteLine(Properties_File, "ANDROID_KEYSTORE_PASS=" + ANDROID_KEYSTORE_PASS$)
		WriteLine(Properties_File, "ANDROID_ALIAS=" + ANDROID_ALIAS$)
		'WriteLine(Properties_File, "ANDROID_ALIAS_PASS=" + ANDROID_ALIAS_PASS$)
		WriteLine(Properties_File, "ANDROID_DEBUG=" + Str(ANDROID_BUILD_DEBUG))
		WriteLine(Properties_File, "ANDROID_RELEASE=" + Str(ANDROID_BUILD_RELEASE))
		WriteLine(Properties_File, "ANDROID_JAVA_DIR=" + ANDROID_JAVA_DIR$)
		
		FileClose(Properties_File)
		ChangeDir(cwd$)
	End If
End Sub


Function Init_Java_Dir(java_dir$, prj_name$)
	activity_name$ = "rcbasic_" + Replace(Trim(prj_name$), " ", "_")
	
	If Right(java_dir$,1) = path_join$ Then
		java_dir$ = Left(java_dir$, Length(java_dir$)-1)
	End If
	
	rc_java_file_path$ = base_dir$ + Replace("/rcbasic_android/scripts/rcbasic.java", "/", path_join$)
	rc_java_file = FreeFile
	If Not FileOpen(rc_java_file, rc_java_file_path$, TEXT_INPUT) Then
		Print "Could not find Android Java Template: ";rc_java_file_path$
		Return False
	End If
	
	out_java_file = FreeFile
	If Not FileOpen(out_java_file, java_dir$ + path_join$ + activity_name$ + ".java", TEXT_OUTPUT) Then
		FileClose(rc_java_file)
		Print "Could not output to ";java_dir$
		Return False
	End If
	
	While Not EOF(rc_java_file)
		ln$ = Readline(rc_java_file)
		ln$ = Replace(ln$, "package_name", ANDROID_APP_ID$)
		ln$ = Replace(ln$, "app_name", activity_name$)
		Writeline(out_java_file, ln$)
	Wend
	
	FileClose(out_java_file)
	FileClose(rc_java_file)
	
	Return True
End Function


Function GetToken$(ByRef arg$)
	token$ = ""
	For i = 0 to Length(arg$)-1
		c$ = Left$(arg$, 1)
		If c$ = "," Then
			arg$ = Mid$(arg$, 1, Length(arg$)-1)
			Exit For
		Else
			token$ = token$ + c$
			arg$ = Mid$(arg$, 1, Length(arg$)-1)
		End If
	Next
	Return token$
End Function




win = Gui_WindowOpen("Distribute Your App", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 640, 480) 'open a window

Include "app_build_main.bas"
Include "app_build_android.bas"


'position main panel in window
Gui_Window_AddPanel(win, main_panel, 5, 32) 'Add panel to window at (x = 150, y = 50)

'postion android settings panel in window
Gui_Window_AddPanel(win, android_settings_panel, 5, 32)


tab_group = Gui_CreateTabGroup(630,28)

Gui_Window_AddTabGroup(win, tab_group, 5, 5)

tab1 = Gui_TabGroup_AddTab(tab_group, "Build")
tab2 = Gui_TabGroup_AddTab(tab_group, "Android Settings")
'tab3 = Gui_TabGroup_AddTab(tab_group, "Tab 3")

Gui_TabGroup_Tab_AddObject(tab_group, tab1, main_panel)
Gui_TabGroup_Tab_AddObject(tab_group, tab2, android_settings_panel)


Gui_Update


While WindowExists(win)
	If Gui_Button_Clicked(project_dir_button) Then
		Gui_TextField_SetValue(project_dir_field, DirectoryWindow$(call_dir$))
	ElseIf Gui_Button_Clicked(output_dir_button) Then
		Gui_TextField_SetValue(output_dir_field, DirectoryWindow$(call_dir$))
	ElseIf Gui_Button_Clicked(keystore_password_show_button) Then
		show_keystore_pw = Not Gui_TextField_GetPasswordFieldAttribute(keystore_password_field)
		Gui_TextField_SetPasswordField(keystore_password_field, show_keystore_pw)
	ElseIf Gui_Button_Clicked(alias_password_show_button) Then
		show_alias_pw = Not Gui_TextField_GetPasswordFieldAttribute(alias_password_field)
		Gui_TextField_SetPasswordField(alias_password_field, show_alias_pw)
	ElseIf Gui_Button_Clicked(java_dir_init_button) Then
		java_dir$ = Gui_TextField_GetValue$(java_dir_field)
		If FileExists(base_dir$ + Replace("/rcbasic_android/scripts/rcbasic.java", "/", path_join$)) And DirExists(java_dir$) Then
			PROJECT_NAME$ = Trim(Gui_TextField_GetValue$(project_name_field))
			APP_NAME$ = Replace(PROJECT_NAME$, " ", "_")
			Init_Java_Dir(java_dir$, APP_NAME$)
		End If
	ElseIf Gui_Button_Clicked(icon_button) Then
		img_path$ = FileWindow$
		If Trim(img_path$) <> "" Then
			If ImageExists(icon) Then
				DeleteImage(icon)
			End If
			LoadImage(icon, img_path$)
			icon_path$ = img_path$
			GetImageSize(icon, iw, ih)
			Gui_Surface_Clear(icon_preview)
			Gui_Surface_DrawImage_Blit_Ex(icon_preview, icon, 0, 0, 128, 128, 0, 0, iw, ih)
		Else
			'Gui_Surface_Clear(icon_preview)
		End If
		Gui_Surface_Update(icon_preview)
	ElseIf Gui_TextField_Return(keystore_password_field) Then
		Gui_TextField_SetValue(keystore_password_field, Replace(Gui_TextField_GetValue$(keystore_password_field), " ", ""))
	ElseIf Gui_TextField_Return(alias_password_field) Then
		Gui_TextField_SetValue(alias_password_field, Replace(Gui_TextField_GetValue$(alias_password_field), " ", ""))
	ElseIf Gui_Button_Clicked(make_button) Or Gui_Button_Clicked(save_button)Then
		PROJECT_NAME$ = Trim(Gui_TextField_GetValue$(project_name_field))
		APP_NAME$ = Replace(PROJECT_NAME$, " ", "_")
		APP_TYPE$ = "Application"
		PROJECT_CATEGORY$ = Gui_DropDown_GetValue$(category_dropdown, Gui_DropDown_GetSelectedItem(category_dropdown))
		If Gui_CheckBox_GetValue(terminal_checkbox) Then
			TERMINAL_FLAG$ = "true"
		Else
			TERMINAL_FLAG$ = "false"
		End If
		
		project_dir$ = Trim(Gui_TextField_GetValue$(project_dir_field))
		output_dir$ = Trim(Gui_TextField_GetValue$(output_dir_field))
		
		ANDROID_APP_ID$ = Gui_TextField_GetValue$(app_id_field)
		ANDROID_ORIENTATION$ = Gui_DropDown_GetValue$(orientation_dropdown, Gui_DropDown_GetSelectedItem(orientation_dropdown))
		ANDROID_KEYSTORE$ = Trim(Gui_TextField_GetValue$(keystore_field))
		ANDROID_KEYSTORE_PATH$ = Env("RC_KEYSTORE_DIR") + path_join$ + Trim(Gui_TextField_GetValue$(keystore_field))
		If LCase(Right(ANDROID_KEYSTORE_PATH$, 4)) <> ".keystore" Then
			ANDROID_KEYSTORE_PATH$ = ANDROID_KEYSTORE_PATH$ + ".keystore "
		End If
		ANDROID_KEYSTORE_PATH$ = Replace(ANDROID_KEYSTORE_PATH$, "\\", "\\\\") 'Needs to be in escape character format in build.gradle
		ANDROID_KEYSTORE_PASS$ = Gui_TextField_GetValue$(keystore_password_field)
		ANDROID_ALIAS$ = Gui_TextField_GetValue$(alias_field)
		ANDROID_ALIAS_PASS$ = Gui_TextField_GetValue$(alias_password_field)
		ANDROID_BUILD_DEBUG = Gui_CheckBox_GetValue(debug_cb)
		ANDROID_BUILD_RELEASE = Gui_CheckBox_GetValue(release_cb)
		ANDROID_JAVA_DIR$ = Gui_TextField_GetValue$(java_dir_field)
		
		If Not DirExists(output_dir$) Then
			MakeDir(output_dir$)
		End If
		
		If Not DirExists(output_dir$) Then
			Print "Error: Could not make output directory at ";output_dir$
		Else
		
			TGT_PLATFORMS$ = ""
			
			If Gui_CheckBox_GetValue(web_cb) Then
				TGT_PLATFORMS$ = TGT_PLATFORMS$ + "WEB,"
			End If
			
			If Gui_CheckBox_GetValue(linux32_cb) Then
				TGT_PLATFORMS$ = TGT_PLATFORMS$ + "LINUX_32,"
			End If
			
			If Gui_CheckBox_GetValue(linux64_cb) Then
				TGT_PLATFORMS$ = TGT_PLATFORMS$ + "LINUX_64,"
			End If
			
			If Gui_CheckBox_GetValue(win32_cb) Then
				TGT_PLATFORMS$ = TGT_PLATFORMS$ + "WIN_32,"
			End If
			
			If Gui_CheckBox_GetValue(win64_cb) Then
				TGT_PLATFORMS$ = TGT_PLATFORMS$ + "WIN_64,"
			End If
			
			If Gui_CheckBox_GetValue(mac_cb) Then
				TGT_PLATFORMS$ = TGT_PLATFORMS$ + "MAC,"
			End If
			
			If Gui_CheckBox_GetValue(android_cb) Then
				TGT_PLATFORMS$ = TGT_PLATFORMS$ + "ANDROID,"
			End If
			
			If Right$(TGT_PLATFORMS$,1) = "," Then
				TGT_PLATFORMS$ = Left$(TGT_PLATFORMS$, Len(TGT_PLATFORMS$)-1)
			End If
			
			If Gui_CheckBox_GetValue(web_thread_checkbox) Then
				enable_threads$ = "true"
			Else
				enable_threads$ = "false"
			End If
			
			APP_PKG_ARGS$ = "TGT_PLATFORM=[TGT_ARGS] PROJECT_NAME=\q[PRJ_NAME]\q "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "PROJECT_CATEGORY=[PRJ_CAT] APP_TYPE=[APT] "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "TERMINAL_FLAG=[TRM_FLG] PROJECT_DIR=\q[PRJ_DIR]\q "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "OUTPUT_DIR=\q[OUT_DIR]\q ENABLE_WEB_THREADS=[WEB_THD] ICON=\q[ICN]\q "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "SOURCE=\q[SRC]\q "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "ANDROID_APP_ID=\q[ANDROID_APP_ID]\q "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "ANDROID_ORIENTATION=\q[ANDROID_ORIENTATION]\q "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "ANDROID_KEYSTORE=\q[ANDROID_KEYSTORE]\q "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "ANDROID_KEYSTORE_PASS=\q[ANDROID_KEYSTORE_PASS]\q "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "ANDROID_ALIAS=\q[ANDROID_ALIAS]\q "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "ANDROID_ALIAS_PASS=\q[ANDROID_ALIAS_PASS]\q "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "ANDROID_RELEASE=[ANDROID_RELEASE] "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "ANDROID_DEBUG=[ANDROID_DEBUG] "
			APP_PKG_ARGS$ = APP_PKG_ARGS$ + "ANDROID_JAVA_DIR=\q[JAVA_DIR]\q "
			
			'MAIN APP SETTINGS
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[TGT_ARGS]", TGT_PLATFORMS$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[PRJ_NAME]", PROJECT_NAME$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[PRJ_CAT]", PROJECT_CATEGORY$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[APT]", APP_TYPE$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[TRM_FLG]", TERMINAL_FLAG$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[PRJ_DIR]", project_dir$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[OUT_DIR]", output_dir$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[WEB_THD]", enable_threads$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[ICN]", icon_path$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[SRC]", source_file$)
			
			'ANDROID SETTINGS
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[ANDROID_APP_ID]", ANDROID_APP_ID$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[ANDROID_ORIENTATION]", ANDROID_ORIENTATION$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[ANDROID_KEYSTORE]", ANDROID_KEYSTORE_PATH$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[ANDROID_KEYSTORE_PASS]", ANDROID_KEYSTORE_PASS$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[ANDROID_ALIAS]", ANDROID_ALIAS$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[ANDROID_ALIAS_PASS]", ANDROID_ALIAS_PASS$)
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[ANDROID_RELEASE]", Str(ANDROID_BUILD_RELEASE))
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[ANDROID_DEBUG]", Str(ANDROID_BUILD_DEBUG))
			APP_PKG_ARGS$ = Replace(APP_PKG_ARGS$, "[JAVA_DIR]", ANDROID_JAVA_DIR$)
			
			SaveAppProperties()
			
			Print "APP_PKG_ARGS$ = ";APP_PKG_ARGS$
			
			If Gui_Button_Clicked(make_button) Then
				print "ANDROID_HOME=";ENV("ANDROID_HOME")
				Gui_WindowClose(win)
				System("rcbasic pkg " + APP_PKG_ARGS$)
				System("rcbasic \q"+base_dir$ + path_join$ + "msg_cmp\q complete")
			End If
			Exit While
		End If
	End If
	
	
	Gui_Update() 'update must be called at the end of the main loop
Wend

Gui_WindowClose(win) 'closes the window
