Dim key_store$
Dim key_alias$
Dim key_store_pass$
Dim key_alias_pass$

key_store$ = "key.store=../keystore/"
key_alias$ = "key.alias="
key_store_pass$ = "key.store.password="
key_alias_pass$ = "key.alias.password="

ant_build = 1

If NumCommands >= 2 Then
	For i = 0 to NumCommands-2
		If Command$(i) = "-key_store" Then
			key_store$ = key_store$ + Command$(i+1)
		ElseIf Command$(i) = "-key_alias" Then
			key_alias$ = key_alias$ + Command$(i+1)
		ElseIf Command$(i) = "-key_store_pass" Then
			key_store_pass$ = key_store_pass$ + Command$(i+1)
		ElseIf Command$(i) = "-key_alias_pass" Then
			key_alias_pass$ = key_alias_pass$ + Command$(i+1)
		ElseIf Command$(i) = "-release" Then
			ant_build = 2
		End If
	Next
Else
	End
End If

Dim ant_properties$: ant_properties$ = ""
f = FreeFile
FileOpen(f, "./script/ant.properties", TEXT_INPUT)
While Not EOF(f)
	ant_properties$ = ant_properties$ + ReadLine(f) + "\n"
Wend
FileClose(f)

ant_properties$ = ant_properties$ + "\n" + key_store$ + "\n" + key_alias$ + "\n" + key_store_pass$ + "\n" + key_alias_pass$ + "\n"

FileOpen(f, "./rcbasic_android/ant.properties", TEXT_OUTPUT_PLUS)
WriteLine(f, ant_properties$)
FileClose(f)


Print "RCBASIC ANDROID BUILDER"
Print ""
'ant_build=Val(input$("Select Build:\n1.Debug\n2.Release\n\nEnter:"))

api_version = 0

If ant_build <> 1 And ant_build <> 2 Then
	ant_build=1
End If

Dim script_str$[100]
script_index=0

sub addText(s$)
	If s$ = "" Then
		Return
	End If
	If Left(Trim(s$), 11) = "API_VERSION" Then
		For i = 0 to Length(s)-1
			If Mid(s$, i, 1) = "=" Then
				api_version = Val(Mid(s$, i+1, Length(s$)))
				Exit For
			End If
		Next
	Else
		script_str$[script_index]=s$
		script_index=script_index+1
	End If
end sub

f=FreeFile()

If FileOpen(f,dir$()+"/build.properties",TEXT_INPUT) Then
	i = 1
	While Not Eof(f)
		'Print i
		addText(ReadLine$(f))
		i = i + 1
	Wend
	FileClose(f)
End If

addText("export ANDROID_HOME=" + Dir$ + "/tools_r25.2.5-linux")
addText("export PATH=$ANDROID_HOME/tools:$ANT_HOME:$JAVA_HOME:$PATH")
addText("cd rcbasic_android")
addText("android update project --path . --target android-" + Str$(api_version))
addText("ant clean")

Select Case ant_build
Case 1
	addText("ant debug")
Case 2
	addText("ant release")
Default
	addText("ant debug")
End Select

If OS$()="LINUX" Then

	If FileOpen(f,dir$()+"/rc_build.sh",TEXT_OUTPUT_PLUS) Then
		For i = 0 to script_index-1
			WriteLine(f, script_str$[i]+"\n")
		Next
		FileClose(f)
	End If

	System("chmod u+x rc_build.sh")
	System("./rc_build.sh")

	RemoveFile(dir$()+"/rc_build.sh")
	
	
	If ant_build = 2 Then
		If Not FileExists("./rcbasic_android/bin/rcbasic-release.apk") Then
			ChangeDir("./script")
			System("rcbasic msg_cmp release_build_fail")
			ChangeDir("../")
		Else
			CopyFile("./rcbasic_android/bin/rcbasic-release.apk", "./APK/rcbasic_release.apk")
			ChangeDir("./script")
			System("rcbasic msg_cmp release_build_complete")
			ChangeDir("../")
		End If
	Else
		If Not FileExists("./rcbasic_android/bin/rcbasic-debug.apk") Then
			ChangeDir("./script")
			System("rcbasic msg_cmp debug_build_fail")
			ChangeDir("../")
		Else
			CopyFile("./rcbasic_android/bin/rcbasic-debug.apk", "./APK/rcbasic_debug.apk")
			ChangeDir("./script")
			System("rcbasic msg_cmp debug_build_complete")
			ChangeDir("../")
		End If
	End If
	
ElseIf OS$()="WINDOWS" Then
	If FileOpen(f,dir$()+"/rc_build.bat",TEXT_OUTPUT) Then
		For i = 0 to script_index-1
			WriteLine(f, script_str$[i]+"\n")
		Next
		FileClose(f)
	End If

	System("./rc_build.bat")

	RemoveFile(dir$()+"/rc_build.bat")
	
	If ant_build = 2 Then
		If Not FileExists(".\\rcbasic_android\\bin\\rcbasic-release.apk") Then
			ChangeDir(".\\script")
			System("rcbasic .\\script\\msg_cmp release_build_fail")
			ChangeDir("..\\")
		Else
			CopyFile(".\\rcbasic_android\\bin\\rcbasic-release.apk", ".\\APK\\rc.apk")
			ChangeDir(".\\script")
			System("rcbasic .\\script\\msg_cmp release_build_complete")
			ChangeDir("..\\")
		End If
	End If
End If

End
