Include "dir_util.bas"
ChangeDir$(SourceDirectory$)

Include "strings.bas"


If Trim$(Env$("RC_PKG_HOME")) = "" Then
	SetEnv("RC_PKG_HOME", Dir$, 1)
Else
	Select Case Right$(Trim$(Env$("RC_PKG_HOME")), 1)
	Case "/","\\" : SetEnv("RC_PKG_HOME", Left$(Env$("RC_PKG_HOME"), Len(Env$("RC_PKG_HOME"))-1), 1)
	End Select
End If

Dim path_join$
Dim HOME$
Dim base_dir$ : base_dir$ = Dir$

If OS$ = "WINDOWS" Then
	path_join$ = "\\"
	HOME$=Env$("USERPROFILE")
	SetEnv("PATH", Env$("PATH")+";%RC_PKG_HOME%\\cmake\\bin", 1)
Else
	path_join$ = "/"
	HOME$=Env$("HOME")
End if

Dim NODEJS_PATH$ : NODEJS_PATH$ = base_dir$ + path_join$ + "node"

Function Build_App_Web(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$, enable_threads$)
	If Right(output_dir$, 1) <> path_join$ Then
		output_dir$ = output_dir$ + path_join$
	End If
	
	If Right(project_dir$, 1) = path_join$ Then
		project_dir$ = Left(project_dir$, Len(project_dir$)-1)
	End If
	
	web_junction$ = ""
	
	If project_dir$ <> Replace(project_dir$, " ", "") Then
		Select Case OS$
		Case "WINDOWS"
			web_junction$ = Env("TEMP") + "\\rcbasic_web_junction"
			'print "web_junction = ";web_junction$
			cmd$ = "mklink /J $web_junction \q$PRJ_DIR\q && cd $web_junction"
			cmd$ = Replace(cmd$, "$web_junction", web_junction$)
			cmd$ = Replace(cmd$, "$PRJ_DIR", project_dir$)
			'print "cmd = ";cmd$
			status = System(cmd$)
			If status <> 0 Then
				Print "This web build aint happenin chief"
				Return False
			Else
				project_dir$ = web_junction$
			End If
		Default
			'Need to Handle Mac and Linux
		End Select
	End If

	
	PRG_NAME$ = APP_NAME$
	PRG_LOCATION$ = project_dir$

	DST_LOCATION$ = output_dir$+PRG_NAME$+"_web"
	
	Print "WEB PRG_NAME$ = ";PRG_NAME
	Print "WEB PRG_LOCATION$ = ";PRG_LOCATION
	Print "WEB DST_LOCATION$ = ";DST_LOCATION

	PROG_NAME$=PRG_NAME$
	PROG_LOCATION$=PRG_LOCATION$ + "@" + path_join$
	OUT_HTML$=DST_LOCATION$+path_join$+PRG_NAME+".html"

	If Not DirExists(DST_LOCATION$) Then
		MakeDir(DST_LOCATION$)
	End If
	
	thread_flags$=""
	
	If enable_threads$="true" Then
		thread_flags$="-pthread -s PTHREAD_POOL_SIZE=2"
	End If
	
	ChangeDir("rc_em")
	
		
	THEORA_LIB$=Dir$+path_join$+"libtheora-1.1.1"+path_join$+"out"+path_join$+"lib"
	THEORA_INCLUDE$=Dir$+path_join$+"libtheora-1.1.1"+path_join$+"out"+path_join$+"include"

	pre_cmd$ = ""

	If Not DirExists("emsdk") Then

	Print "Starting Emscripten Initial Setup...."
	' Get the emsdk repo
	System("git clone https://github.com/emscripten-core/emsdk.git")

	' Enter that directory
	Print ".."
	Print "Go into folder"
	ChangeDir("emsdk")
	Print "PWD is "; Dir$
	Print ".."

	' Download and install the latest SDK tools.
	Print "EMSDK install latest ...."
	System("." + path_join$ + "emsdk install latest")
	Print "..."

	Else
	' Enter that directory
	ChangeDir("emsdk")
	End If

	' Make the "latest" SDK "active" for the current user. (writes ~/.emscripten file)
	Print "ACTIVATE"
	pre_cmd$ = "pushd " + Dir$ + " && ." + path_join$ + "emsdk activate latest" 
	'System("." + path_join$ + "emsdk activate latest")
	SetEnv("EM_CONFIG", HOME$ + path_join$ + ".emscripten",1)
	Print "..."

	' Activate PATH and other environment variables in the current terminal
	Select Case OS$
	Case "WINDOWS"
		pre_cmd$ = pre_cmd$ + " && .\\emsdk_env.bat"
	Default
		pre_cmd$ = pre_cmd$ + " && chmod u+x emsdk_env.sh && source $PWD/emsdk_env.sh"
	End Select

	pre_cmd$ = pre_cmd$ + " && popd && "

	Print "path is "; Dir$

	ChangeDir(".." + path_join$ + "rcbasic_runtime")

	Dim web_compile_cmd$
	web_compile_cmd$ = "em++ main.cpp theoraplay.c "
	web_compile_cmd$ = web_compile_cmd$ + "\q-L$THEORA_LIB\q \q-I$THEORA_INCLUDE\q "
	web_compile_cmd$ = web_compile_cmd$ + "-s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_GFX=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_NET=2 "
	web_compile_cmd$ = web_compile_cmd$ + "-s USE_OGG=1 -s USE_VORBIS=1 -ltheora -ltheoradec "
	web_compile_cmd$ = web_compile_cmd$ + "-o \q$OUT_HTML\q --preload-file $PROG_LOCATION -O3 -s ASYNCIFY "
	web_compile_cmd$ = web_compile_cmd$ + "-s SDL2_IMAGE_FORMATS='[\qbmp\q,\qpng\q,\qxpm\q]' --use-preload-plugins "
	web_compile_cmd$ = web_compile_cmd$ + "-s TOTAL_MEMORY=134217728 -s ALLOW_MEMORY_GROWTH=1 $rc_extra_web_flags"
	web_compile_cmd$ = Replace(web_compile_cmd$, "$THEORA_LIB", THEORA_LIB$)
	web_compile_cmd$ = Replace(web_compile_cmd$, "$THEORA_INCLUDE", THEORA_INCLUDE$)
	web_compile_cmd$ = Replace(web_compile_cmd$, "$OUT_HTML", OUT_HTML$)
	web_compile_cmd$ = Replace(web_compile_cmd$, "$PROG_LOCATION", PROG_LOCATION$)
	web_compile_cmd$ = Replace(web_compile_cmd$, "$rc_extra_web_flags", thread_flags$)

	Print "running command: ";web_compile_cmd$
	Print "--------------------------"

	System(pre_cmd$ + web_compile_cmd$)	
	
	If DirExists(web_junction$) Then
		Select Case OS$
		Case "WINDOWS"
			System("rmdir " + web_junction$)
		Default
			System("rm " + web_junction$)
		End Select
	End If
	
	ChangeDir(base_dir$)
	
	If Not FileExists(DST_LOCATION+path_join$+PRG_NAME+".js") Then
		Print "....PROG_NAME: ";PROG_NAME$
		Print "....PROG_LOCATION: ";PROG_LOCATION$
		Print "....OUT_HTML: ";OUT_HTML$
		Return False
	End If

	'CopyFile(Env$("RC_PKG_HOME")+path_join$+"rc_em"+path_join$+"resources"+path_join$+"rcb.html", DST_LOCATION$+path_join$+"tmp.html")
	If FileExists(Env$("RC_PKG_HOME")+path_join$+"rc_em"+path_join$+"resources"+path_join$+"banner.png") Then
		CopyFile(Env$("RC_PKG_HOME")+path_join$+"rc_em"+path_join$+"resources"+path_join$+"banner.png", DST_LOCATION$+path_join$+"banner.png")
	Else
		Print "Missing banner.png"
	End If
	
	If FileExists(Env$("RC_PKG_HOME")+path_join$+"rc_em"+path_join$+"resources"+path_join$+"style.css") Then
		CopyFile(Env$("RC_PKG_HOME")+path_join$+"rc_em"+path_join$+"resources"+path_join$+"style.css", DST_LOCATION$+path_join$+"style.css")
	Else
		Print "Missing style.css"
	End If
	
	html$=""
	f = FreeFile
	If FileExists(Env$("RC_PKG_HOME")+path_join$+"rc_em"+path_join$+"resources"+path_join$+"rcb.html") Then
		FileOpen(f, Env$("RC_PKG_HOME")+path_join$+"rc_em"+path_join$+"resources"+path_join$+"rcb.html", TEXT_INPUT)
		While Not EOF(0)
			html$=html$+ReadLine(f)+"\n"
		Wend
		FileClose(f)
	Else
		Print "Missing RCBASIC html template. Using emscripten default"
		Return True
	End If

	'RemoveFile(DST_LOCATION$+path_join$+"tmp.html")
	RemoveFile(OUT_HTML$)
	
	f = FreeFile
	If Not FileExists(OUT_HTML$) Then
		'Print "OUT_HTML = ";OUT_HTML$
		FileOpen(f, OUT_HTML$, TEXT_OUTPUT_PLUS)
		WriteLine(f, Replace(html$, "%SOURCE_JS%", PRG_NAME$+".js"))
		FileClose(f)
	End If
	
	Return True
End Function

Sub CopyDir(src_path$, dst_path$)
	Select Case OS$
	Case "WINDOWS"
		If Right$(Trim$(src_path$),1) = path_join$ Then
			src_path$ = Left$(Trim$(src_path$), Len(src_path$)-1)
		End If
		If Right$(Trim$(dst_path$),1) = path_join$ Then
			dst_path$ = Left$(Trim$(dst_path$), Len(dst_path$)-1)
		End If
		System("Xcopy /E /I \q" + src_path$ + "\q \q" + dst_path$ + "\q")
	Default
		If Right$(Trim$(src_path$),1) <> "." Then
			src_path$ = src_path$ + "."
		End If
		If Right$(Trim$(dst_path$),1) <> "/" Then
			dst_path$ = dst_path$ + "/"
		End If
		System("cp -a \q" + src_path$ + "\q \q" + dst_path$ + "\q")
	End Select
End Sub

Function Build_App_64(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$)
	'Print "MAKE APP:";output_dir$;";"
	
	Select Case OS$
	Case "WINDOWS"
		If Right(output_dir$, 1) <> "\\" Then
			output_dir$ = output_dir$ + "\\"
		End If
		
		If Right(project_dir$, 1) = "\\" Then
			project_dir$ = Left(project_dir$, Length(project_dir$)-1)
		End If
	Default
		If Right(output_dir$, 1) <> path_join$ Then
			output_dir$ = output_dir$ + path_join$
		End If
		
		If Right(project_dir$, 1) <> path_join$ Then
			project_dir$ = project_dir$ + path_join$
		End If
	End Select
	
	USR_PATH$ = output_dir$ + APP_NAME$ + ".AppDir"+path_join$+"usr"
	BIN_PATH$ = output_dir$ + APP_NAME$ + ".AppDir"+path_join$+"usr"+path_join$+"bin"
	LIB_PATH$ = output_dir$ + APP_NAME$ + ".AppDir"+path_join$+"usr"+path_join$+"lib"
	
	MakeDir(output_dir$ + APP_NAME$ + ".AppDir")
	Print "Directory: ";"Copy " + dir + "/rcbasic.AppDir/usr/. >-- to --> " + USR_PATH$ +"/"
	CopyDir(dir + path_join$ + "rcbasic.AppDir" + path_join$ + "usr" + path_join$,  USR_PATH$)
	CopyDir(project_dir$, USR_PATH$)
	CopyFile(dir + path_join$ + "rcbasic.AppDir" + path_join$ +"AppRun", output_dir$ + APP_NAME$ + ".AppDir" + path_join$ + "AppRun")
	
	If OS$ <> "WINDOWS" Then
		System("chmod u+x \q" + output_dir$ + APP_NAME$ + ".AppDir/AppRun\q")
	End If
	
	desktop$ = "[Desktop Entry]\n"
	desktop$ = desktop$ + "Name="+PROJECT_NAME$+"\n"
	desktop$ = desktop$ + "Exec=rcbasic main.cbc\n"
	desktop$ = desktop$ + "Comment=RCBasic Application\n"
	desktop$ = desktop$ + "Icon=rcbasic\n"
	desktop$ = desktop$ + "Type="+APP_TYPE$+"\n"
	desktop$ = desktop$ + "Terminal="+TERMINAL_FLAG$+"\n"
	desktop$ = desktop$ + "Categories="+PROJECT_CATEGORY$+";\n"
	
	f = FreeFile
	FileOpen(f, output_dir$ + APP_NAME$ + ".AppDir" + path_join$ + "rcbasic.desktop", TEXT_OUTPUT)
	WriteLine(f, desktop$)
	FileClose(f)
	
	FileOpen(f, USR_PATH$ + path_join$ + "share" + path_join$ + "applications" + path_join$ + "rcbasic.desktop", TEXT_OUTPUT)
	WriteLine(f, desktop$)
	FileClose(f)
	
	Print "ICON EXISTS: ";icon_path$;" --> ";FileExists(icon_path$)
	
	CopyFile(icon_path$, output_dir$ + APP_NAME$ + ".AppDir" + path_join$ + "rcbasic.png")
	
	'Currently, AppImageTool is only available on linux
	If OS$ = "LINUX" Then
		System("chmod u+x ./App/appimagetool.AppImage && ./App/appimagetool.AppImage \q" + output_dir$ + APP_NAME$ + ".AppDir\q \q" + output_dir$ + "/" + APP_NAME$ + "_LX64.AppImage\q")
	End If
		
	If DirExists(output_dir$ + APP_NAME$ + ".AppDir") Then
		'System("rm -r \q" + output_dir$ + APP_NAME$ + ".AppDir\q")
		
		PRINT "REMOVE ";"\q" + output_dir$ + APP_NAME$ + ".AppDir/AppRun\q"
		RemoveFile(output_dir$ + APP_NAME$ + ".AppDir" + path_join$ + "AppRun")
		
		CopyFile(dir + path_join$ + "App" + path_join$ + "rcbasic_run", output_dir$ + APP_NAME$ + ".AppDir" + path_join$ + APP_NAME$)
		CopyFile(dir + path_join$ + "App" + path_join$ + "libstdc++.so.6", output_dir$ + APP_NAME$ + ".AppDir" + path_join$ + "usr" + path_join$ + "lib" + path_join$ + "libstdc++.so.6")
		
		PRINT "RENAME: ";"\q" + output_dir$ + APP_NAME$ + ".AppDir\q"
		Select Case OS$
		Case "WINDOWS"
			System("cd \q" + output_dir$ + "\q && rename \q" + APP_NAME$ + ".AppDir\q \q" + APP_NAME$ + "_LX64B\q")
		Default
			System("mv \q" + output_dir$ + APP_NAME$ + ".AppDir\q \q" + output_dir$ + APP_NAME$ + "_LX64B\q")
		End Select
	End If
	
	If OS$ = "LINUX" Then
		If FileExists(output_dir$ + "/" + APP_NAME$ + "_LX64.AppImage") Then
			Print "Successfully packaged Linux 64-bit Program"
			Return True
		Else
			Print "Error: Failed to packaged Linux 64-bit Program"
		End If
	Else
		If DirExists(output_dir$ + APP_NAME$ + "_LX64B") Then
			Print "Successfully packaged Linux 64-bit Program"
			Return True
		Else
			Print "Error: Failed to packaged Linux 64-bit Program: "
		End If
	End If
	
	Return False
			
End Function

Function Build_App_32(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$)
	'Print "MAKE APP:";output_dir$;";"
	
	Select Case OS$
	Case "WINDOWS"
		If Right(output_dir$, 1) <> "\\" Then
			output_dir$ = output_dir$ + "\\"
		End If
		
		If Right(project_dir$, 1) = "\\" Then
			project_dir$ = Left(project_dir$, Length(project_dir$)-1)
		End If
	Default		
		If Right(output_dir$, 1) <> "/" Then
			output_dir$ = output_dir$ + "/"
		End If
		
		If Right(project_dir$, 1) <> "/" Then
			project_dir$ = project_dir$ + "/"
		End If
	End Select
	
	APP_PATH$ = output_dir$ + APP_NAME$ + "_LX32"
	
	MakeDir(APP_PATH$)
	CopyDir(dir + path_join$ + "linux_dist_32" + path_join$ + "bin" + path_join$, APP_PATH$ + path_join$ + "bin")
	CopyDir(dir + path_join$ + "linux_dist_32" + path_join$ + "lib" + path_join$, APP_PATH$ + path_join$ + "lib")
	CopyDir(project_dir$, APP_PATH$ + path_join$ + "assets")
	CopyFile("linux_dist_32" + path_join$ + "rc_app_run", APP_PATH$ + path_join$ + APP_NAME$)
	
	If OS$ <> "WINDOWS" Then
		System("chmod u+x \q" + APP_PATH$ + "/" + APP_NAME$ + "\q")
	End If
	
	If FileExists(APP_PATH$ + path_join$ + APP_NAME$) Then
		Print "Successfully packaged Linux 32-bit Program"
		Return True
	Else
		Print "Error: Failed to packaged Linux 32-bit Program"
	End If
	
	Return False
			
End Function

Function Build_App_Win_32(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$)
	'Print "MAKE APP:";output_dir$;";"
	
	Select Case OS$
	Case "WINDOWS"
		If Right(output_dir$, 1) <> "\\" Then
			output_dir$ = output_dir$ + "\\"
		End If
		
		If Right(project_dir$, 1) = "\\" Then
			project_dir$ = Left(project_dir$, Length(project_dir$)-1)
		End If
	Default
		If Right(output_dir$, 1) <> "/" Then
			output_dir$ = output_dir$ + "/"
		End If
		
		If Right(project_dir$, 1) <> "/" Then
			project_dir$ = project_dir$ + "/"
		End If
	End Select
	
	WIN_PKG_PATH$ = output_dir$ + APP_NAME$ + "_WIN32"
	
	MakeDir(WIN_PKG_PATH)
	CopyDir(dir + path_join$ + "rcbasic_win_dist" + path_join$ + "dist_32" + path_join$, WIN_PKG_PATH)
	CopyDir(project_dir$, WIN_PKG_PATH + path_join$ + "assets")
	RenameFile(WIN_PKG_PATH + path_join$ + "launcher.exe", WIN_PKG_PATH + path_join$ + APP_NAME$ + ".exe")
	
	
	If FileExists(WIN_PKG_PATH + path_join$ + APP_NAME$ + ".exe") Then
		Print "Successfully packaged Windows 32-bit Program"
		Return True
	Else
		Print "Error: Failed to packaged Windows 32-bit Program"
	End If
	
	Return False
			
End Function

Function Build_App_Win_64(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$)
	'Print "MAKE APP:";output_dir$;";"
	
	Select Case OS$
	Case "WINDOWS"
		If Right(output_dir$, 1) <> "\\" Then
			output_dir$ = output_dir$ + "\\"
		End If
		
		If Right(project_dir$, 1) = "\\" Then
			project_dir$ = Left(project_dir$, Length(project_dir$)-1)
		End If
	Default
		If Right(output_dir$, 1) <> "/" Then
			output_dir$ = output_dir$ + "/"
		End If
		
		If Right(project_dir$, 1) <> "/" Then
			project_dir$ = project_dir$ + "/"
		End If
	End Select
	
	WIN_PKG_PATH$ = output_dir$ + APP_NAME$ + "_WIN64"
	
	MakeDir(WIN_PKG_PATH)
	CopyDir(dir + path_join$ + "rcbasic_win_dist" + path_join$ + "dist_64" + path_join$, WIN_PKG_PATH)
	CopyDir(project_dir$, WIN_PKG_PATH + path_join$ + "assets")
	RenameFile(WIN_PKG_PATH + path_join$ + "launcher.exe", WIN_PKG_PATH + path_join$ + APP_NAME$ + ".exe")
	
	
	If FileExists(WIN_PKG_PATH + path_join$ + APP_NAME$ + ".exe") Then
		Print "Successfully packaged Windows 64-bit Program"
		Return True
	Else
		Print "Error: Failed to packaged Windows 64-bit Program"
	End If
	
	Return False
			
End Function

Function RemoveSpecialChar$(s$)
	ret$ = s
	ret = Replace(ret, " ", "")
	ret = Replace(ret, "&", " AND ")
	ret = Replace(ret, "!", "")
	ret = Replace(ret, "@", "")
	ret = Replace(ret, "$", "")
	ret = Replace(ret, "~", "")
	ret = Replace(ret, "<", "lt")
	ret = Replace(ret, ">", "gt")
	ret = Replace(ret, "?", "")
	ret = Replace(ret, "%", "")
	ret = Replace(ret, "_", "")
	Return ret
End Function

Function Build_App_MacOS(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$)
	
	Select Case OS$
	Case "WINDOWS"
		If Right(output_dir$, 1) <> "\\" Then
			output_dir$ = output_dir$ + "/"
		End If
		
		If Right(project_dir$, 1) = "\\" Then
			project_dir$ = Left(project_dir$, Length(project_dir$)-1)
		End If
	Default
		If Right(output_dir$, 1) <> "/" Then
			output_dir$ = output_dir$ + "/"
		End If
		
		If Right(project_dir$, 1) <> "/" Then
			project_dir$ = project_dir$ + "/"
		End If
	End Select
	
	APP_PATH$ = output_dir$ + APP_NAME$ + "_MAC"
	MAC_APP$ = APP_NAME$ + ".app"
	
	MakeDir(APP_PATH$)
	CopyDir(base_dir$ + path_join$ + "RCBasic_MACOS" + path_join$ + "rcbasic_app" + path_join$, APP_PATH$ + path_join$ + MAC_APP$)
	
	f = FreeFile
	
	FileOpen(f, APP_PATH$ + path_join$ + MAC_APP$ + path_join$ + "Contents" + path_join$ + "Info.plist", TEXT_INPUT)
	
	s$ = ""
	
	While Not EOF(f)
		s$ = s$ + ReadLine(f) + "\n"
	Wend
	
	FileClose(f)
	
	s = Replace(s, "rc_bundle_info", APP_NAME$)
	s = Replace(s, "com.rcbasic.app", "com." + RemoveSpecialChar(APP_NAME$) + ".app")
	s = Replace(s, "rc_bundle_name", APP_NAME$)
	
	RemoveFile(APP_PATH$ + path_join$ + MAC_APP$ + path_join$ + "Contents" + path_join$ + "Info.plist")
	
	FileOpen(f, APP_PATH$ + path_join$ + MAC_APP$ + path_join$ + "Contents" + path_join$ + "Info.plist", TEXT_OUTPUT)
	WriteLine(f, s)
	FileClose(f)
	
	'''''''''''''
	ChangeDir(NODEJS_PATH$)
	'png2icons "C:\Users\omega\Desktop\rcbasic_313\rcpkg_linux\rcpkg_linux\assets\rcbasic.AppDir\rcbasic.png" "C:\Users\omega\Desktop\rcbasic_313\rcpkg_linux\rcpkg_linux\assets\rcbasic.AppDir\rc_out" -icns
	System("png2icons \q" + icon_path$ + "\q \q" + APP_PATH$ + path_join$ + MAC_APP$ + path_join$ + "Contents" + path_join$ + "Resources" + path_join$ + "Icon\q -icns")
	ChangeDir(base_dir$)
	
	If Not FileExists(APP_PATH$ + path_join$ + MAC_APP$ + path_join$ + "Contents" + path_join$ + "Resources" + path_join$ + "Icon.icns") Then
		Print "MAC Icon failed to generate"
		Return False
	End If
	
	CopyDir(project_dir$, APP_PATH$ + path_join$ + MAC_APP$ + path_join$ + "Contents" + path_join$ + "assets")
	
	If DirExists(APP_PATH$ + path_join$ + MAC_APP$) Then
		Print "Successfully packaged Mac OS Program"
		Return True
	Else
		Print "Error: Failed to packaged Mac OS Program"
	End If
	
	Return False
			
End Function


Function gen_id_path$(app_id$)
	Push_S(Dir$)
	ChangeDir(base_dir$ + Replace("/rcbasic_android/android-project/app/src/main/java", "/", path_join$))
	app_id$ = app_id$ + "."
	f_name$ = ""
	For i = 0 to Len(app_id$)-1
		c$ = Mid(app_id$, i, 1)
		If c$ = "." Then
			If Not DirExists(f_name$) And Trim(f_name$) <> "" Then
				MakeDir(f_name$)
			End If
			ChangeDir(f_name$)
			f_name$ = ""
		Else
			f_name$ = f_name$ + c$
		End If
	Next
	
	id_path$ = ""
	
	If Not DirExists(base_dir$ + Replace("/rcbasic_android/android-project/app/src/main/java/", "/", path_join$) + Replace(app_id$, ".", path_join$)) Then
		id_path$ = ""
	Else
		id_path$ = Dir$
	End If
	
	ChangeDir(Pop_S())
	Return id_path$
End Function

Function RmDir(rm_path$)
	Select Case OS$
	Case "WINDOWS"
		Return Not System("rmdir /s /q \q" + rm_path$ + "\q")
	Default
		Return Not System("rm -rf \q" + rm_path$ + "\q")
	End Select
End Function

Function Build_App_Android(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, icon_path$, ANDROID_APP_ID$, ANDROID_ORIENTATION$, ANDROID_KEYSTORE$, ANDROID_KEYSTORE_PASS$, ANDROID_ALIAS$, ANDROID_ALIAS_PASS$, ANDROID_BUILD_DEBUG, ANDROID_BUILD_RELEASE, ANDROID_JAVA_DIR$)
	'Print "MAKE APP:";output_dir$;";"
	
	Select Case OS$
	Case "WINDOWS"
		If Right(output_dir$, 1) <> "\\" Then
			output_dir$ = output_dir$ + "\\"
		End If
		
		If Right(project_dir$, 1) = "\\" Then
			project_dir$ = Left(project_dir$, Length(project_dir$)-1)
		End If
	Default
		If Right(output_dir$, 1) <> "/" Then
			output_dir$ = output_dir$ + "/"
		End If
		
		If Right(project_dir$, 1) <> "/" Then
			project_dir$ = project_dir$ + "/"
		End If
	End Select
	
	
	Print "APP_ID -- ";ANDROID_APP_ID$
	Print "DISPLAY -- ";ANDROID_ORIENTATION$
	Print "KEYSTORE -- ";ANDROID_KEYSTORE$
	Print "KEYSTORE_PASS -- ";ANDROID_KEYSTORE_PASS$
	Print "ALIAS -- ";ANDROID_ALIAS$
	Print "ALIAS_PASS -- ";ANDROID_ALIAS_PASS$
	Print "DEBUG -- ";ANDROID_BUILD_DEBUG
	Print "RELEASE -- ";ANDROID_BUILD_RELEASE
	
	SetEnv("APP_NAME",APP_NAME$,1)
	SetEnv("ORIENTATION",ANDROID_ORIENTATION$,1)
	SetEnv("ICON", icon_path$,1)
	SetEnv("APP_ID",ANDROID_APP_ID$,1)
	SetEnv("RC_KEY_STORE",ANDROID_KEYSTORE$,1)
	SetEnv("RC_KEY_STORE_PASS",ANDROID_KEYSTORE_PASS$,1)
	SetEnv("RC_ALIAS",ANDROID_ALIAS$,1)
	SetEnv("RC_ALIAS_PASS",ANDROID_ALIAS_PASS$,1)
	SetEnv("RC_ANDROID_DEBUG", Trim(Str(ANDROID_BUILD_DEBUG)), 1)
	SetEnv("RC_ANDROID_RELEASE", Trim(Str(ANDROID_BUILD_RELEASE)), 1)
	
	
	build_cmd$ = ""
	
	'C:\\Users\\omega\\Desktop\\ISO\\SDL2-2.0.14
	'rcbasic_android\scripts\java
	
	'rcbasic_android\android-project\app\src\main\java
	
	'C:\Users\omega\Desktop\rcbasic_313\rcpkg_linux\rcpkg_linux\assets\rcbasic_android\android-project\app\src\main\java\org\libsdl\app
	
	'Remove Build Directory. It will get remade during build process.
	If DirExists(base_dir$ + Replace("/rcbasic_android/android-project/app/build/outputs/apk/debug", "/", path_join$)) Then
		RmDir(base_dir$ + Replace("/rcbasic_android/android-project/app/build/outputs/apk/debug", "/", path_join$))
	End If
	
	'Remove Build Directory. It will get remade during build process.
	If DirExists(base_dir$ + Replace("/rcbasic_android/android-project/app/build/outputs/apk/release", "/", path_join$)) Then
		RmDir(base_dir$ + Replace("/rcbasic_android/android-project/app/build/outputs/apk/release", "/", path_join$))
	End If
	
	
	sdk_dir$ = Env("ANDROID_HOME")
	sdk_dir$ = Replace(sdk_dir$, "\\", "\\\\")
	sdk_dir$ = Replace(sdk_dir$, ":", "\\:")
	
	If FileExists(base_dir$ + path_join$ + "rcbasic_android" + path_join$ + "android-project" + path_join$ + "local.properties") Then
		RemoveFile(base_dir$ + path_join$ + "rcbasic_android" + path_join$ + "android-project" + path_join$ + "local.properties")
	End If
	
	f = FreeFile
	
	If Not FileOpen(f, base_dir$ + path_join$ + "rcbasic_android" + path_join$ + "android-project" + path_join$ + "local.properties", TEXT_OUTPUT) Then
		Print "Could not write to local.properties"
		Return False
	End If
	
	Writeline(f, "sdk.dir=" + sdk_dir$)
	FileClose(f)
	
	If DirExists(base_dir$ + Replace("/rcbasic_android/android-project/app/src/main/java", "/", path_join$)) Then
		RmDir(base_dir$ + Replace("/rcbasic_android/android-project/app/src/main/java", "/", path_join$))
	End If
	
	
	CopyDir(base_dir$ + Replace("/rcbasic_android/scripts/java", "/", path_join$), base_dir$ + Replace("/rcbasic_android/android-project/app/src/main/java", "/", path_join$))
	
	RemoveFile(base_dir$ + Replace("/rcbasic_android/android-project/app/src/main/java/org/libsdl/app/SDLActivity.java", "/", path_join$))
	
	in_file = FreeFile
	If Not FileOpen(in_file, base_dir$ + Replace("/rcbasic_android/scripts/java/org/libsdl/app/SDLActivity.java", "/", path_join$), TEXT_INPUT) Then
		Print "Could not find SDLActivity Base"
		Return False
	End If
	
	out_file = FreeFile
	If FileOpen(out_file, base_dir$ + Replace("/rcbasic_android/android-project/app/src/main/java/org/libsdl/app/SDLActivity.java", "/", path_join$), TEXT_OUTPUT) Then
		While Not EOF(in_file)
			ln$ = ReadLine(in_file)
			If FileExists(ANDROID_JAVA_DIR$ + Replace("/rcbasic_" + APP_NAME$ + ".java", "/", path_join$)) Then
				ln$ = Replace(ln$, "//rcbasic_android_interface", "return " + ANDROID_APP_ID$ + ".rcbasic_" + APP_NAME$ + ".rcbasic_android_interface(arg);")
			Else
				ln$ = Replace(ln$, "//rcbasic_android_interface", "return \q\q;")
			End If
			WriteLine(out_file, ln$)
		Wend
	Else
		Print "Could not output SDLActivity in Project"
		Return False
	End If
	FileClose(in_file)
	FileClose(out_file)
	'Print "Should have copied correctly";base_dir$ + Replace("/rcbasic_android/scripts/java", "/", path_join$)
	
	
	Print "ANDROID_JAVA_DIR$ = ";ANDROID_JAVA_DIR$
	If Trim(ANDROID_JAVA_DIR$) <> "" And DirExists(ANDROID_JAVA_DIR$) Then
		app_id_path$ = gen_id_path$(ANDROID_APP_ID$)
		Print "APP PATH = ";app_id_path
		If app_id_path$ <> "" Then
			CopyDir(ANDROID_JAVA_DIR$, app_id_path$)
		Else
			Print "Error: Could not create path for APP_ID("; ANDROID_APP_ID$;")"
			Return False
		End If
	End If
	
	If OS$ = "WINDOWS" Then : build_cmd$ = "set PATH=%RCBASIC_ANDROID_DIR%;%PATH% && "
	Else : build_cmd$ = "export PATH=$RCBASIC_ANDROID_DIR:$PATH && " : End If
	
	Select Case OS$()
	Case "WINDOWS"
		build_cmd$ = build_cmd$ + "cd " + project_dir$ + " && rcbasic_android_build.bat "
	Default
		build_cmd$ = build_cmd$ + "cd " + project_dir$ + " && chmod u+x $RCBASIC_ANDROID_DIR/rcbasic_android_build.sh && $RCBASIC_ANDROID_DIR/rcbasic_android_build.sh "
	End Select
	
	Print "\n\nRCBASIC_ANDROID_DIR=";env("RCBASIC_ANDROID_DIR");"\n\n"
	
	System(build_cmd$)
	
	SetEnv("APP_NAME","",1)
	SetEnv("ORIENTATION","",1)
	SetEnv("ICON","",1)
	SetEnv("APP_ID","",1)
	SetEnv("RC_KEY_STORE","",1)
	SetEnv("RC_KEY_STORE_PASS","",1)
	SetEnv("RC_ALIAS","",1)
	SetEnv("RC_ALIAS_PASS","",1)
	SetEnv("RC_ANDROID_DEBUG", "0", 1)
	SetEnv("RC_ANDROID_RELEASE", "0", 1)
	
	debug_success = 0
	release_success = 0
	
	If ANDROID_BUILD_DEBUG Then
		If FileExists(base_dir$ + Replace("/rcbasic_android/android-project/app/build/outputs/apk/debug/", "/", path_join$) + "app-debug.apk") Then
			If FileExists(output_dir$ + APP_NAME$ + "-debug.apk") Then
				RemoveFile(output_dir$ + APP_NAME$ + "-debug.apk")
			End If
			RenameFile(base_dir$ + Replace("/rcbasic_android/android-project/app/build/outputs/apk/debug/", "/", path_join$) + "app-debug.apk", output_dir$ + APP_NAME$ + "-debug.apk")
			If FileExists(output_dir$ + APP_NAME$ + "-debug.apk") Then
				debug_success = 1
			End If
		End If
	End If
	
	
	If ANDROID_BUILD_RELEASE Then
		If FileExists(base_dir$ + Replace("/rcbasic_android/android-project/app/build/outputs/apk/release/", "/", path_join$) + "app-release.apk") Then
			If FileExists(output_dir$ + APP_NAME$ + "-release.apk") Then
				RemoveFile(output_dir$ + APP_NAME$ + "-release.apk")
			End If
			RenameFile(base_dir$ + Replace("/rcbasic_android/android-project/app/build/outputs/apk/release/", "/", path_join$) + "app-release.apk", output_dir$ + APP_NAME$ + "-release.apk")
			If FileExists(output_dir$ + APP_NAME$ + "-release.apk") Then
				release_success = 1
			End If
		End If
	End If
	
	
	debug_status = ( (ANDROID_BUILD_DEBUG And debug_success) Or (Not ANDROID_BUILD_DEBUG) )
	release_status = ( (ANDROID_BUILD_RELEASE And release_success) Or (Not ANDROID_BUILD_RELEASE) )
	
	status = debug_status + ( release_status shl 1 )
	
	If debug_success Then
		Print "Successfully built Android Debug APK"
	ElseIf ANDROID_BUILD_DEBUG Then
		Print "Error: Failed to build Android Debug APK"
	End If
	
	If release_success Then
		Print "Successfully built Android Release APK"
	ElseIf ANDROID_BUILD_RELEASE Then
		Print "Error: Failed to build Android Release APK"
	End If
	
	Return status
			
End Function


Function GetArg$(arg_name$)
	arg_value$ = ""
	For i = 0 to NumCommands()-1 Step 1
		If Left$(Command$(i), Length(arg_name$)+1) = (arg_name$+"=") Then
			If Length(Command$(i)) > (Length(arg_name$)+1) Then
				arg_value$ = Mid$(Command$(i), Length(arg_name$)+1, Length(Command$(i)) - (Length(arg_name$)+1))
			End If
		ElseIf Command$(i) = arg_name$ Then
			If i < (NumCommands()-1) Then
				arg_value$ = Command$(i+1)
				i = i + 1
			End If
		End If
	Next
	Return arg_value$
End Function

Function SetValue$(default_value$, s_value$)
	If Trim$(s_value$) = "" Then
		Return default_value$
	End If
	Return s_value$
End Function

Dim APP_NAME$
Dim PROJECT_NAME$
Dim PROJECT_CATEGORY$
Dim APP_TYPE$
Dim TERMINAL_FLAG$

Dim project_dir$
Dim output_dir$

Dim icon_path$
Dim src_file$

Dim PLATFORM_LINUX32, PLATFORM_LINUX64, PLATFORM_WIN32, PLATFORM_WIN64, PLATFORM_MAC, PLATFORM_IOS, PLATFORM_ANDROID, PLATFORM_WEB

PLATFORM_LINUX32 = 0
PLATFORM_LINUX64 = 1
PLATFORM_WIN32 = 2
PLATFORM_WIN64 = 3
PLATFORM_MAC = 4
PLATFORM_IOS = 5
PLATFORM_ANDROID = 6
PLATFORM_WEB = 7

Dim NUM_PLATFORMS
NUM_PLATFORMS=8

Dim TGT_PLATFORM[NUM_PLATFORMS]

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

Sub GetPlatforms(platform_arg$)
	'Initialize to 0
	For i = 0 to NUM_PLATFORMS-1
		TGT_PLATFORM[i] = 0
	Next
	
	Dim platform_token$: platform_token$ = GetToken$(platform_arg$)
	
	While Trim(platform_token$) <> ""
		Select Case platform_token$
		Case "LINUX_32"
			TGT_PLATFORM[PLATFORM_LINUX32] = True
		Case "LINUX_64"
			TGT_PLATFORM[PLATFORM_LINUX64] = True
		Case "WIN_32"
			TGT_PLATFORM[PLATFORM_WIN32] = True
		Case "WIN_64"
			TGT_PLATFORM[PLATFORM_WIN64] = True
		Case "MAC"
			TGT_PLATFORM[PLATFORM_MAC] = True
		Case "IOS"
			TGT_PLATFORM[PLATFORM_IOS] = True
		Case "ANDROID"
			TGT_PLATFORM[PLATFORM_ANDROID] = True
		Case "WEB"
			TGT_PLATFORM[PLATFORM_WEB] = True
		End Select
		platform_token$ = GetToken$(platform_arg$)
	Wend
End Sub


Function CompiledSrc$(bas_file$)
	ext_start = FindLastOf(".", bas_file$)
	cbc_file_name$ = Left$(bas_file$, ext_start) + ".cbc"
	Return cbc_file_name$
End Function

'rcbasic ap_assist TGT_PLATFORM=WEB PROJECT_NAME=video_demo PROJECT_CATEGORY=Game TERMINAL_FLAG=false PROJECT_DIR=$prj_path OUTPUT_DIR=/home/n00b/Desktop/projects ENABLE_WEB_THREADS=true

'rcbasic ap_assist TGT_PLATFORM=WEB PROJECT_NAME=video_demo PROJECT_CATEGORY=Game TERMINAL_FLAG=false PROJECT_DIR=%prj_path% OUTPUT_DIR=%out_dir% ENABLE_WEB_THREADS=true

PROJECT_NAME$ = GetArg$("PROJECT_NAME")
APP_NAME$ = Replace(PROJECT_NAME$, " ", "_")
APP_TYPE$ = SetValue$("Application", GetArg$("APP_TYPE"))
PROJECT_CATEGORY$ = SetValue$("Game", GetArg$("PROJECT_CATEGORY"))
TERMINAL_FLAG$ = SetValue$("true", LCase$(GetArg$("TERMINAL_FLAG")))
project_dir$ = GetArg$("PROJECT_DIR")
output_dir$ = GetArg$("OUTPUT_DIR")
icon_path$ = SetValue$(Env$("RC_PKG_HOME") + path_join$ + "icon" + path_join$ + "rcbasic.png", GetArg$("ICON"))
enable_threads$ = SetValue$("false", LCase$(GetArg$("ENABLE_WEB_THREADS")))
src_file$ = GetArg$("SOURCE")

ANDROID_APP_ID$ = GetArg$("ANDROID_APP_ID")
ANDROID_ORIENTATION$ = GetArg$("ANDROID_ORIENTATION")
ANDROID_KEYSTORE$ = GetArg$("ANDROID_KEYSTORE")
ANDROID_KEYSTORE_PASS$ = GetArg$("ANDROID_KEYSTORE_PASS")
ANDROID_ALIAS$ = GetArg$("ANDROID_ALIAS")
ANDROID_ALIAS_PASS$ = GetArg$("ANDROID_ALIAS_PASS")
ANDROID_BUILD_DEBUG = Val(GetArg$("ANDROID_DEBUG"))
ANDROID_BUILD_RELEASE = Val(GetArg$("ANDROID_RELEASE"))
ANDROID_JAVA_DIR$ = GetArg$("ANDROID_JAVA_DIR")


GetPlatforms(GetArg$("TGT_PLATFORM"))

'Checking for missing values
error = 0


ChangeDir(project_dir$)
Print "Build Command: rcbasic_build " + src_file$ + " in " + Dir$
System("rcbasic_build \q" + src_file$ + "\q")

cbc_file$ = CompiledSrc$(src_file$)

If Not FileExists(cbc_file$) Then
	Print "Failed to build Source File: (";src_file$;")"
	End
End If

If FileExists("main.cbc") Then
	RemoveFile("main.cbc")
End If

RenameFile(cbc_file$, "main.cbc")

ChangeDir(base_dir$)


If APP_NAME$ = "" Then
	Print "Error: Missing App Name"
	error = 1
End If

If project_dir$ = "" Then
	Print "Error: Missing Project Directory"
	error = 1
End If

If Not DirExists(project_dir$) Then
	Print "Error: Cannot Locate Project Directory"
	error = 1
End If

If DirExists(project_dir$) Then
	If Right(project_dir$, 1) = path_join$ Then
		project_dir$ = Left(project_dir$, Length(project_dir$)-1)
	End If
	If Not FileExists(project_dir$ + path_join$ + "main.cbc") Then
		Print "Error: Cannot Locate main.cbc in project directory"
		error = 1
	End If
End If
		

If output_dir$ = "" Then
	Print "Output Directory was not set"
	error = 1
ElseIf Not DirExists(output_dir$) Then
	Print "Cannot Locate Output Directory"
	error = 1
Else
	print "DEBUB: CLEAR ";output_dir$
	RmDir(output_dir$)
	MakeDir(output_dir$)
End If

If icon_path$ = "" Then
	Print "Cannot Locate Icon"
	error = 1
End If

If error Then
	End
End If

Print ""
Print "PROJECT_NAME: ";PROJECT_NAME$
Print "PROJECT_CATEGORY: ";PROJECT_CATEGORY$
Print "APP_NAME: ";APP_NAME$
Print "APP_TYPE: ";APP_TYPE$
Print "PROJECT_DIR: ";project_dir$
Print "OUTPUT_DIR: ";output_dir$
Print "ICON: ";icon_path$

Dim lx32_flag
Dim lx64_flag
Dim win32_flag
Dim win64_flag
Dim mac_flag
Dim web_flag
Dim android_flag

If TGT_PLATFORM[PLATFORM_LINUX32] Then
	lx32_flag = Build_App_32(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$)
End If

If TGT_PLATFORM[PLATFORM_LINUX64] Then
	lx64_flag = Build_App_64(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$)
End If

If TGT_PLATFORM[PLATFORM_WIN32] Then
	win32_flag = Build_App_Win_32(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$)
End If

If TGT_PLATFORM[PLATFORM_WIN64] Then
	win64_flag = Build_App_Win_64(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$)
End If

If TGT_PLATFORM[PLATFORM_MAC] Then
	mac_flag = Build_App_MacOS(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$)
End If

If TGT_PLATFORM[PLATFORM_WEB] Then
	web_flag = Build_App_Web(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, APP_TYPE$, TERMINAL_FLAG$, PROJECT_CATEGORY$, icon_path$, enable_threads$)
End If

If TGT_PLATFORM[PLATFORM_ANDROID] Then
	android_flag = Build_App_Android(project_dir$, output_dir$, PROJECT_NAME$, APP_NAME$, icon_path$, ANDROID_APP_ID$, ANDROID_ORIENTATION$, ANDROID_KEYSTORE$, ANDROID_KEYSTORE_PASS$, ANDROID_ALIAS$, ANDROID_ALIAS_PASS$, ANDROID_BUILD_DEBUG, ANDROID_BUILD_RELEASE, ANDROID_JAVA_DIR$)
End if

Print "\n\n"
Print "RESULTS\n--------------------\n"

If lx32_flag Then
	Print "Successfully Created Linux 32-Bit App"
ElseIf TGT_PLATFORM[PLATFORM_LINUX32] Then
	Print "Failed to Create Linux 32-Bit App"
End If

If lx64_flag Then
	Print "Successfully Created Linux 64-Bit App"
ElseIf TGT_PLATFORM[PLATFORM_LINUX64] Then
	Print "Failed to Create Linux 64-Bit App"
End If

If win32_flag Then
	Print "Successfully Created Windows 32-Bit App"
ElseIf TGT_PLATFORM[PLATFORM_WIN32] Then
	Print "Failed to Create Windows 32-Bit App"
End If

If win64_flag Then
	Print "Successfully Created Windows 64-Bit App"
ElseIf TGT_PLATFORM[PLATFORM_WIN64] Then
	Print "Failed to Create Windows 64-Bit App"
End If

If mac_flag Then
	Print "Successfully Created Mac OS App"
ElseIf TGT_PLATFORM[PLATFORM_MAC] Then
	Print "Failed to Create Mac OS App"
End If

If web_flag Then
	Print "Successfully Created Web App"
ElseIf TGT_PLATFORM[PLATFORM_WEB] Then
	Print "Failed to Create Web App"
End If

If android_flag Then
	If AndBit(android_flag, 1) Then
		Print "Successfully Created Android Debug App"
	Else
		Print "Failed to Create Android Debug App"
	End If
	
	If AndBit(android_flag SHR 1, 1) Then
		Print "Successfully Created Android Release App"
	Else
		Print "Failed to Create Android Release App"
	End If
	
ElseIf TGT_PLATFORM[PLATFORM_ANDROID] Then
	Print "Failed to Create Android (Debug or Release) App"
End If

'install cmake, icnsutils, and git
