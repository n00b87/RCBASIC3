Include "dir_util.bas"
ChangeDir$(SourceDirectory$)

base_dir$ = Dir$

Dim path_join$

If OS$ = "WINDOWS" Then
	path_join$ = "\\"
Else
	path_join$ = "/"
End if


If Trim(Env("RC_KEYSTORE_DIR")) = "" Then
	SetEnv("RC_KEYSTORE_DIR", base_dir$ + Replace("/../../../../keystore", "/", path_join$), 1)
End If

If Not DirExists(Env("RC_KEYSTORE_DIR")) Then
	MakeDir(Env("RC_KEYSTORE_DIR"))
End If

Include "gui.bas" 'include the gui library

win = Gui_WindowOpen("New Keystore", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 640, 480) 'open a window

keystore_name_label = Gui_CreateLabel("Key Store Name:",100, 20)
keystore_name_field = Gui_CreateTextField(400, 20)

keystore_password_label = Gui_CreateLabel("Password:",80, 20)
keystore_password_field = Gui_CreateTextField(200, 20)

keystore_confirm_label = Gui_CreateLabel("Confirm:",80, 20)
keystore_confirm_field = Gui_CreateTextField(200, 20)


path_button = Gui_CreateButton("...", 20, 20) 'Create a button
'example_checkbox = Gui_CreateCheckBox(16,16) 'Create a Checkbox

keystore_panel = Gui_CreatePanel(600, 80) 'Create a panel

Gui_Panel_AddObject(keystore_panel, keystore_name_label, 20, 25) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(keystore_panel, keystore_name_field, 130, 20) 'Add checkbox to panel at (x = 20, y = 20)

Gui_Panel_AddObject(keystore_panel, keystore_password_label, 20, 55) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(keystore_panel, keystore_password_field, 80, 50) 'Add checkbox to panel at (x = 20, y = 20)

Gui_Panel_AddObject(keystore_panel, keystore_confirm_label, 300, 55) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(keystore_panel, keystore_confirm_field, 360, 50) 'Add checkbox to panel at (x = 20, y = 20)


'-----------KEY-------------------
'key_alias_title_label = Gui_CreateLabel("KEY", 80, 20)

key_alias_label = Gui_CreateLabel("Alias:",80, 20)
key_alias_field = Gui_CreateTextField(400, 20)

alias_password_label = Gui_CreateLabel("Password:",80, 20)
alias_password_field = Gui_CreateTextField(200, 20)

alias_confirm_label = Gui_CreateLabel("Confirm:",80, 20)
alias_confirm_field = Gui_CreateTextField(200, 20)

key_alias_panel = Gui_CreatePanel(600, 80) 'Create a panel

'Gui_Panel_AddObject(key_alias_panel, key_alias_title_label, 10, 10) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(key_alias_panel, key_alias_label, 20, 10) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(key_alias_panel, key_alias_field, 100, 10) 'Add checkbox to panel at (x = 20, y = 20)

'Gui_Panel_AddObject(key_alias_panel, alias_password_label, 20, 45) 'Add checkbox to panel at (x = 20, y = 20)
'Gui_Panel_AddObject(key_alias_panel, alias_password_field, 80, 40) 'Add checkbox to panel at (x = 20, y = 20)

'Gui_Panel_AddObject(key_alias_panel, alias_confirm_label, 300, 45) 'Add checkbox to panel at (x = 20, y = 20)
'Gui_Panel_AddObject(key_alias_panel, alias_confirm_field, 360, 40) 'Add checkbox to panel at (x = 20, y = 20)


'-----------CERTIFICATE-------------------
cert_title_label = Gui_CreateLabel("CERTIFICATE", 120, 20)

cert_name_label = Gui_CreateLabel("First and Last Name:",140, 20)
cert_name_field = Gui_CreateTextField(400, 20)

cert_org_unit_label = Gui_CreateLabel("Organizational Unit:",140, 20)
cert_org_unit_field = Gui_CreateTextField(400, 20)

cert_org_label = Gui_CreateLabel("Organiztion:",90, 20)
cert_org_field = Gui_CreateTextField(450, 20)

cert_city_label = Gui_CreateLabel("City or Locality:",120, 20)
cert_city_field = Gui_CreateTextField(420, 20)

cert_state_label = Gui_CreateLabel("State or Province:",130, 20)
cert_state_field = Gui_CreateTextField(410, 20)

cert_cc_label = Gui_CreateLabel("Country Code (XX):",130, 20)
cert_cc_field = Gui_CreateTextField(410, 20)


cert_panel = Gui_CreatePanel(600, 220) 'Create a panel

Gui_Panel_AddObject(cert_panel, cert_title_label, 10, 10) 'Add checkbox to panel at (x = 20, y = 20)

Gui_Panel_AddObject(cert_panel, cert_name_label, 20, 35) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(cert_panel, cert_name_field, 160, 30) 'Add checkbox to panel at (x = 20, y = 20)

Gui_Panel_AddObject(cert_panel, cert_org_unit_label, 20, 65) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(cert_panel, cert_org_unit_field, 160, 60) 'Add checkbox to panel at (x = 20, y = 20)

Gui_Panel_AddObject(cert_panel, cert_org_label, 20, 95) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(cert_panel, cert_org_field, 110, 90) 'Add checkbox to panel at (x = 20, y = 20)

Gui_Panel_AddObject(cert_panel, cert_city_label, 20, 125) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(cert_panel, cert_city_field, 140, 120) 'Add checkbox to panel at (x = 20, y = 20)

Gui_Panel_AddObject(cert_panel, cert_state_label, 20, 155) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(cert_panel, cert_state_field, 150, 150) 'Add checkbox to panel at (x = 20, y = 20)

Gui_Panel_AddObject(cert_panel, cert_cc_label, 20, 185) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(cert_panel, cert_cc_field, 150, 180) 'Add checkbox to panel at (x = 20, y = 20)


'--------------ACTION------------------------
ok_button = Gui_CreateButton("OK", 60, 20)
cancel_button = Gui_CreateButton("Cancel", 60, 20)


act_panel = Gui_CreatePanel(600, 40) 'Create a panel

Gui_Panel_AddObject(act_panel, ok_button, 400, 10) 'Add button to panel at (x = 20, y = 100)
Gui_Panel_AddObject(act_panel, cancel_button, 470, 10) 'Add button to panel at (x = 20, y = 100)


'---------------WINDOW------------------------------
Gui_Window_AddPanel(win, keystore_panel, 20, 20) 'Add panel to window at (x = 150, y = 50)
Gui_Window_AddPanel(win, key_alias_panel, 20, 110) 'Add panel to window at (x = 150, y = 50)
Gui_Window_AddPanel(win, cert_panel, 20, 200) 'Add panel to window at (x = 150, y = 50)
Gui_Window_AddPanel(win, act_panel, 20, 430) 'Add panel to window at (x = 150, y = 50)

'--------------KEY TOOL------------------------------------
VAR_CN$="&USR_NAME"
VAR_OU$="&ORG_UNIT"
VAR_O$="&ORG_NAME"
VAR_C$="&COUNTRY_CODE"
VAR_ALIAS$="&ALIAS"
VAR_PW$="&PASSWORD"
VAR_KEYSTORE$="&KEYSTORE_NAME"
keystore_cmd$ = "echo y | keytool -genkeypair -dname \qcn=&USR_NAME, ou=&ORG_UNIT, o=&ORG_NAME, c=&COUNTRY_CODE\q -alias &ALIAS -keyalg RSA -keypass &PASSWORD -keystore &KEYSTORE_NAME.keystore -storepass &PASSWORD -validity 20000"

'build_xml$ = "/home/n00b/Desktop/rcbasic_release/rcbasic_android/tools_r25.2.5-linux/tools/ant/build.xml"


Dim script_str$[100]
script_index=0

sub addText(s$,n)
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
	ElseIf n = 2 Then
		If OS$="WINDOWS" Then
			script_str$[script_index]="set " + s$
		Else
			script_str$[script_index]="export " + s$
		End If
		script_index=script_index+1
	Else
		script_str$[script_index]=s$
		script_index=script_index+1
	End If
end sub

f=FreeFile()

If FileOpen(f,dir$()+path_join$+"build.properties",TEXT_INPUT) Then
	i = 1
	While Not Eof(f)
		'Print i
		addText(Replace(ReadLine$(f), "%CD%", Dir$), 2)
		i = i + 1
	Wend
	FileClose(f)
End If

If OS$ = "WINDOWS" Then
	addText("set JAVA_HOME="+base_dir$ + "\\..\\openjdk-11", 1)
	addText("set PATH=%JAVA_HOME%;%JAVA_HOME%\\bin;%PATH%", 1)
End If

While Not Key(K_Q) And WindowExists(win)
	'Check for Events
	If Gui_Button_Clicked(ok_button) Then
		ChangeDir(Env("RC_KEYSTORE_DIR"))
		If Length( Trim(Gui_TextField_GetValue$(keystore_password_field)+".") ) = 1 Or Length( Trim(Gui_TextField_GetValue$(keystore_confirm_field)+".") ) = 1 Then
			System(Replace("pushd base_dir && rcbasic msg_cmp pw_error1 && popd","base_dir", base_dir$))
		ElseIf Trim(Gui_TextField_GetValue$(keystore_password_field)) <> Trim(Gui_TextField_GetValue$(keystore_confirm_field)) Then
			System(Replace("pushd base_dir && rcbasic msg_cmp pw_error2 && popd","base_dir", base_dir$))
		ElseIf Trim(Gui_TextField_GetValue$(alias_password_field)) <> Trim(Gui_TextField_GetValue$(alias_confirm_field)) Then
			System(Replace("pushd base_dir && rcbasic msg_cmp pw_error2 && popd","base_dir", base_dir$))
		Else
			keystore_cmd$=Replace$(keystore_cmd$,VAR_CN$, Gui_TextField_GetValue$(cert_name_field))
			keystore_cmd$=Replace$(keystore_cmd$,VAR_OU$, Gui_TextField_GetValue$(cert_org_unit_field))
			keystore_cmd$=Replace$(keystore_cmd$,VAR_O$, Gui_TextField_GetValue$(cert_org_field))
			keystore_cmd$=Replace$(keystore_cmd$,VAR_C$, Gui_TextField_GetValue$(cert_cc_field))
			keystore_cmd$=Replace$(keystore_cmd$,VAR_ALIAS$, Trim(Gui_TextField_GetValue$(key_alias_field)))
			keystore_cmd$=Replace$(keystore_cmd$,VAR_PW$, Trim(Gui_TextField_GetValue$(keystore_password_field)))
			keystore_cmd$=Replace$(keystore_cmd$,VAR_KEYSTORE$, Trim(Gui_TextField_GetValue$(keystore_name_field)))
			If FileExists(Env("RC_KEYSTORE_DIR") + path_join$ + Trim(Gui_TextField_GetValue$(keystore_name_field)) + ".keystore") Then
				System(Replace("pushd base_dir && rcbasic msg_cmp exists && popd","base_dir", base_dir$))
				Exit While
			Else
				If OS$ = "WINDOWS" Then
					If FileOpen(f,base_dir$+"\\rc_build.bat",TEXT_OUTPUT) Then
						For i = 0 to script_index-1
							WriteLine(f, script_str$[i])
						Next
						WriteLine(f, keystore_cmd$)
						FileClose(f)
					End If
					
					System("\q"+base_dir$+"\\rc_build.bat\q")

					RemoveFile(base_dir$+"\\rc_build.bat")
				Else
					If FileOpen(f,base_dir$+"/rc_build.sh",TEXT_OUTPUT) Then
						For i = 0 to script_index-1
							WriteLine(f, script_str$[i])
						Next
						WriteLine(f, keystore_cmd$)
						FileClose(f)
					End If
					
					System("chmod u+x \q"+base_dir$+"/rc_build.sh\q && "+base_dir$+"/rc_build.sh")

					RemoveFile(base_dir$+"/rc_build.bat")
				End If
				
				If FileExists(dir + "\\" + Gui_TextField_GetValue$(keystore_name_field) + ".keystore") Then
					System(Replace("pushd base_dir && rcbasic msg_cmp complete && popd","base_dir", base_dir$))
				Else
					System(Replace("pushd base_dir && rcbasic msg_cmp fail && popd","base_dir", base_dir$))
				End If
				Exit While
			End If
		End If
		ChangeDir(base_dir$)
	ElseIf Gui_Button_Clicked(cancel_button) Then
		Exit While
	End If
	
	'Update events and draw gui
	Gui_Update() 'update must be called at the end of the main loop
Wend

Gui_WindowClose(win) 'closes the window
