Include "dir_util.bas"
ChangeDir$(SourceDirectory$)

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


id$ = "com.rcbasic.test"

Function gen_id_path$(app_id$)
	Push_S(Dir$)
	ChangeDir(base_dir$ + Replace("/rcbasic_android/android-project/app/src/main/java", "/", path_join$))
	app_id$ = app_id$ + "."
	f_name$ = ""
	For i = 0 to Len(app_id$)-1
		c$ = Mid(app_id$, i, 1)
		If c$ = "." Then
			If Not DirExists(f_name$) And Trim(f_name$) <> "" Then
				Print "MK: ";f_name$
				MakeDir(f_name$)
			End If
			ChangeDir(f_name$)
			f_name$ = ""
		Else
			f_name$ = f_name$ + c$
		End If
	Next
	
	id_path$ = Dir$
	ChangeDir(Pop_S())
	Return id_path$
End Function

gen_id_path$(id$)