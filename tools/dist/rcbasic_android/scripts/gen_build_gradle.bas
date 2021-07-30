Include "dir_util.bas"
ChangeDir$(SourceDirectory$)

Dim path_join$

If OS$ = "WINDOWS" Then
	path_join$ = "\\"
Else
	path_join$ = "/"
End if

Function gen_build_gradle(api_version, min_api_version, app_id$, release, key_store$, key_store_pass$, alias$, alias_pass$)
	cwd$ = Dir$
	
	sign_config$ = ""
	sign_config_file = FreeFile
	If Not FileOpen(sign_config_file, "sign_config_template", TEXT_INPUT) Then
		Return False
	End If
	
	While Not EOF(sign_config_file)
		sign_config$ = sign_config + ReadLine$(sign_config_file) + "\n"
	Wend
	
	FileClose(sign_config_file)
	
	sign_config$ = Replace(sign_config$, "rc_keystore.jks", key_store$)
	sign_config$ = Replace(sign_config$, "rc_keystore_password", key_store_pass$)
	sign_config$ = Replace(sign_config$, "rc_alias", alias$)
	sign_config$ = Replace(sign_config$, "rc_alias_password", alias_pass$)
	
	'ChangeDir("scripts")
	If FileExists(Dir$+path_join$+".."+path_join$+"android-project"+path_join$+"app"+path_join$+"build.gradle") Then
		RemoveFile(Dir$+path_join$+".."+path_join$+"android-project"+path_join$+"app"+path_join$+"build.gradle")
		Print "------Build Gradle deleted-------"
	End If
	return_val = True
	If Right$(Dir$, 7) <> "scripts" Then
		Print "Error: Could not find scripts folder"
		return_val = False
	End If
	build_gradle_base = FreeFile
	If return_val And ( Not FileOpen(build_gradle_base, "build_base.gradle", TEXT_INPUT) ) Then
		Print "Error: Missing build_base.gradle in scripts folder"
		return_val = False
	End If
	build_gradle_out = FreeFile
	If return_val And ( Not FileOpen(build_gradle_out, Dir$+path_join$+".."+path_join$+"android-project"+path_join$+"app"+path_join$+"build.gradle", TEXT_OUTPUT) ) Then
		Print "Error: Missing build_base.gradle in scripts folder"
		Return False
	End If
	While return_val And ( Not EOF(build_gradle_base) )
		ln$ = ReadLine$(build_gradle_base)
		
		ln$ = Replace(ln$, "RCBASIC_APP_ID", app_id$)
		ln$ = Replace(ln$, "RCBASIC_API_VERSION", Str$(api_version))
		ln$ = Replace(ln$, "RCBASIC_MIN_API_VERSION", Str$(min_api_version))
		If release Then
			ln$ = Replace(ln$, "//rc_signingConfig_block", sign_config$)
			ln$ = Replace(ln$, "//rc_signConfig_release", "signingConfig signingConfigs.release")
		End If
		
		WriteLine(build_gradle_out, ln$ + "\n")
	Wend
	
	FileClose(build_gradle_base)
	FileClose(build_gradle_out)
	
	'ChangeDir(cwd$)
	
	Return return_val
End Function

If NumCommands() > 2 Then
	api_version = 0
	min_api_version = 0
	app_id$ = ""
	
	release = false
	
	key_store$ = ""
	key_store_pass$ = ""
	alias$ = ""
	alias_pass$ = ""
	
	For i = 1 to NumCommands()-2
		Select Case Trim(Command(i))
		Case "--API_VERSION"
			api_version = Int(Val(Command(i+1)))
		Case "--MIN_API_VERSION"
			min_api_version = Int(Val(Command(i+1)))
		Case "--APP_ID"
			app_id$ = Trim(Command(i+1))
		Case "--RELEASE"
			release = true
		Case "--KEY_STORE"
			key_store$ = Trim(Command(i+1))
		Case "--KEY_STORE_PASS"
			key_store_pass$ = Trim(Command(i+1))
		Case "--ALIAS"
			alias$ = Trim(Command(i+1))
		Case "--ALIAS_PASS"
			alias_pass$ = Trim(Command(i+1))
		End Select
	Next
	
	If Trim(Command(NumCommands()-1)) = "--RELEASE" Then
		release = true
	End If
	
	If api_version=0 Or min_api_version=0 Or app_id$="" Then
		Print "Error: Missing Args for gen_build_gradle"
		Print "API_VERSION=";api_version
		Print "MIN_API_VERSION=";min_api_version
		Print "APP_ID=";app_id$
		End
	ElseIf Not gen_build_gradle(api_version, min_api_version, app_id$, release, key_store, key_store_pass, alias, alias_pass) Then
		Print "Error: Failed to generate build.gradle with args: "
		Print "API_VERSION=";api_version
		Print "MIN_API_VERSION=";min_api_version
		Print "APP_ID=";app_id$
		End
	End If
Else
	Print "Error: Missing Args for gen_build_gradle"
	End
End If
