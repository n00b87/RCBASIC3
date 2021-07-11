Include "dir_util.bas"
ChangeDir$(SourceDirectory$)

Dim path_join$

If OS$ = "WINDOWS" Then
	path_join$ = "\\"
Else
	path_join$ = "/"
End if

Function gen_app_settings(app_name$, icon_path$, orientation$)
	cwd$ = Dir$
	
	project_strings_xml$ = Dir$+path_join$+".."+path_join$+"android-project"+path_join$+"app"+path_join$+"src"+path_join$+"main"+path_join$+"res"+path_join$+"values"+path_join$+"strings.xml"
	
	If FileExists(project_strings_xml$) Then
		RemoveFile(project_strings_xml$)
		Print "------strings.xml deleted-------"
	End If
	
	return_val = True
	
	If Right$(Dir$, 7) <> "scripts" Then
		Print "Error: Could not find scripts folder"
		return_val = False
	End If
	
	strings_xml_base = FreeFile
	If return_val And ( Not FileOpen(strings_xml_base, "values" + path_join$ + "strings.xml", TEXT_INPUT) ) Then
		Print "Error: Missing strings.xml in scripts folder"
		return_val = False
	End If
	strings_xml_out = FreeFile
	If return_val And ( Not FileOpen(strings_xml_out, project_strings_xml$, TEXT_OUTPUT) ) Then
		Print "Error: Missing strings.xml in base project folder"
		Return False
	End If
	While return_val And ( Not EOF(strings_xml_base) )
		ln$ = ReadLine$(strings_xml_base)
		ln$ = Replace(ln$, "[rcbasic_app_name]", app_name$)
		WriteLine(strings_xml_out, ln$)
	Wend
	
	FileClose(strings_xml_base)
	FileClose(strings_xml_out)
	
	manifest_name$ = "AndroidManifest.xml"
	manifest_out$ = Dir$+path_join$+".."+path_join$+"android-project"+path_join$+"app"+path_join$+"src"+path_join$+"main"+path_join$+manifest_name$
	
	If FileExists(manifest_out$) Then
		RemoveFile(manifest_out$)
	End If
	
	manifest_tmp_file = FreeFile
	If Not FileOpen(manifest_tmp_file, manifest_name$, TEXT_INPUT) Then
		Print "Error: Manifest template not found"
		Return False
	End If
	
	manifest_out_file = FreeFile
	If Not FileOpen(manifest_out_file, manifest_out$, TEXT_OUTPUT) Then
		Print "Error: Can't output AndroidManifest.xml"
		Return False
	End If
	
	While Not EOF(manifest_tmp_file)
		ln$ = Readline$(manifest_tmp_file)
		
		ln_out$ = ln$
		ln_out$ = Replace(ln_out$, "[rcbasic_display]", orientation$)
		
		If orientation$ = "default" And ln_out$ <> ln$ Then
			ln_out$ = ""
		End If
		
		Writeline(manifest_out_file, ln_out$)
	Wend
	
	FileClose(manifest_tmp_file)
	FileClose(manifest_out_file)
	
	If FileExists(Replace(Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$),"[res_dir]","mipmap-mdpi")) Then
		RemoveFile(Replace(Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$),"[res_dir]","mipmap-mdpi"))
	End If
	
	If FileExists(Replace(Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$),"[res_dir]","mipmap-hdpi")) Then
		RemoveFile(Replace(Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$),"[res_dir]","mipmap-hdpi"))
	End If
	
	If FileExists(Replace(Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$),"[res_dir]","mipmap-xhdpi")) Then
		RemoveFile(Replace(Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$),"[res_dir]","mipmap-xhdpi"))
	End If
	
	If FileExists(Replace(Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$),"[res_dir]","mipmap-xxhdpi")) Then
		RemoveFile(Replace(Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$),"[res_dir]","mipmap-xxhdpi"))
	End If
	
	If FileExists(Replace(Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$),"[res_dir]","mipmap-xxxhdpi")) Then
		RemoveFile(Replace(Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$),"[res_dir]","mipmap-xxxhdpi"))
	End If
	
	'Do stuff with the icons
	If FileExists(icon_path$) Then
		image_magic_path$ = Dir$ + path_join$ + ".." + path_join$ + "ImageMagick"
		Print "SET to PATH:";image_magic_path$
		resize_cmd$ = Replace("convert [icon_path] -resize [size] ../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$)
		resize_cmd$ = Replace(resize_cmd$, "[icon_path]", icon_path$)
		CURRENT_PATH$ = Env("PATH")
		SetEnv("PATH", image_magic_path$, 1)
		Print "error code = ";System(Replace(Replace(resize_cmd$,"[size]","48x48"),"[res_dir]","mipmap-mdpi"))
		Print "error code = ";System(Replace(Replace(resize_cmd$,"[size]","72x72"),"[res_dir]","mipmap-hdpi"))
		Print "error code = ";System(Replace(Replace(resize_cmd$,"[size]","96x96"),"[res_dir]","mipmap-xhdpi"))
		Print "error code = ";System(Replace(Replace(resize_cmd$,"[size]","144x144"),"[res_dir]","mipmap-xxhdpi"))
		Print "error code = ";System(Replace(Replace(resize_cmd$,"[size]","192x192"),"[res_dir]","mipmap-xxxhdpi"))
		SetEnv("PATH", CURRENT_PATH$, 1)
	Else
		image_magic_path$ = Dir$ + path_join$ + "ImageMagick"
		copy_location$ = Replace("../android-project/app/src/main/res/[res_dir]/ic_launcher.png", "/", path_join$)
		CopyFile("mipmap-mdpi"+path_join$+"ic_launcher.png", Replace(copy_location$,"[res_dir]","mipmap-mdpi"))
		CopyFile("mipmap-hdpi"+path_join$+"ic_launcher.png", Replace(copy_location$,"[res_dir]","mipmap-hdpi"))
		CopyFile("mipmap-xhdpi"+path_join$+"ic_launcher.png", Replace(copy_location$,"[res_dir]","mipmap-xhdpi"))
		CopyFile("mipmap-xxhdpi"+path_join$+"ic_launcher.png", Replace(copy_location$,"[res_dir]","mipmap-xxhdpi"))
		CopyFile("mipmap-xxxhdpi"+path_join$+"ic_launcher.png", Replace(copy_location$,"[res_dir]","mipmap-xxxhdpi"))
	End If
	

	Return return_val
End Function

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
	sign_config$ = Replace(sign_config$, "rc_alias_name", alias$)
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
		
		WriteLine(build_gradle_out, ln$)
	Wend
	
	FileClose(build_gradle_base)
	FileClose(build_gradle_out)
	
	'ChangeDir(cwd$)
	
	Return return_val
End Function

If NumCommands() > 2 Then
	app_name$ = ""
	orientation$ = ""
	
	icon_path$ = ""
	
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
		Case "--APP_NAME"
			app_name$ = Trim(Command(i+1))
		Case "--ORIENTATION"
			orientation$ = Trim(Command(i+1))
		Case "--ICON"
			icon_path$ = Trim(Command(i+1))
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
	
	If app_name$ = "" Then
		Print "Error: Missing App Name for android build"
		End
	End If
	
	If orientation$ = "" Then
		orientation= "default"
	End If
	
	If Not gen_app_settings(app_name$, icon_path$, orientation$) Then
		Print "Error: Failed to generate android settings with args: "
		Print "APP_NAME=";app_name$
		Print "ICON=";icon_path$
		End
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
		Print "ORIENTATION=";orientation$
		End
	End If
	
Else
	Print "Error: Missing Args for gen_app_settings"
	End
End If
