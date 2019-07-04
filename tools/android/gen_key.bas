ChangeDir("./script")
Include "./script/gui.bas" 'include the gui library
ChangeDir("../")

win = Gui_WindowOpen("New Keystore", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 640, 480) 'open a window

keystore_name_label = Gui_CreateLabel("Key Store Name:",100, 20)
keystore_name_field = Gui_CreateTextField(400, 20)

keystore_password_label = Gui_CreateLabel("Password:",80, 20)
keystore_password_field = Gui_CreateTextField(200, 20)

keystore_confirm_label = Gui_CreateLabel("Confirm:",80, 20)
keystore_confirm_field = Gui_CreateTextField(200, 20)


path_button = Gui_CreateButton("...", 20, 20) 'Create a button
'example_checkbox = Gui_CreateCheckBox(16,16) 'Create a Checkbox

keystore_panel = Gui_CreatePanel(600, 100) 'Create a panel

Gui_Panel_AddObject(keystore_panel, keystore_name_label, 20, 25) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(keystore_panel, keystore_name_field, 130, 20) 'Add checkbox to panel at (x = 20, y = 20)

Gui_Panel_AddObject(keystore_panel, keystore_password_label, 20, 55) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(keystore_panel, keystore_password_field, 80, 50) 'Add checkbox to panel at (x = 20, y = 20)

Gui_Panel_AddObject(keystore_panel, keystore_confirm_label, 300, 55) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(keystore_panel, keystore_confirm_field, 360, 50) 'Add checkbox to panel at (x = 20, y = 20)


'-----------KEY-------------------
key_alias_title_label = Gui_CreateLabel("KEY", 80, 20)

key_alias_label = Gui_CreateLabel("Alias:",80, 20)
key_alias_field = Gui_CreateTextField(400, 20)

key_alias_panel = Gui_CreatePanel(600, 60) 'Create a panel

Gui_Panel_AddObject(key_alias_panel, key_alias_title_label, 10, 10) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(key_alias_panel, key_alias_label, 20, 35) 'Add checkbox to panel at (x = 20, y = 20)
Gui_Panel_AddObject(key_alias_panel, key_alias_field, 100, 30) 'Add checkbox to panel at (x = 20, y = 20)


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
Gui_Window_AddPanel(win, key_alias_panel, 20, 130) 'Add panel to window at (x = 150, y = 50)
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
keystore_cmd$ = "echo y | keytool -genkeypair -dname 'cn=&USR_NAME, ou=&ORG_UNIT, o=&ORG_NAME, c=&COUNTRY_CODE' -alias &ALIAS -keyalg RSA -keypass &PASSWORD -keystore &KEYSTORE_NAME.keystore -storepass &PASSWORD -validity 20000"

'build_xml$ = "/home/n00b/Desktop/rcbasic_release/rcbasic_android/tools_r25.2.5-linux/tools/ant/build.xml"


While Not Key(K_Q)
	'Check for Events
	If Gui_Button_Clicked(ok_button) Then
		ChangeDir("./keystore")
		If Length( Trim(Gui_TextField_GetValue$(keystore_password_field)+".") ) = 1 Or Length( Trim(Gui_TextField_GetValue$(keystore_confirm_field)+".") ) = 1 Then
			ChangeDir("../script")
			System("rcbasic ../script/msg_cmp pw_error1")
			ChangeDir("../")
		ElseIf Trim(Gui_TextField_GetValue$(keystore_password_field)) <> Trim(Gui_TextField_GetValue$(keystore_confirm_field)) Then
			ChangeDir("../script")
			System("rcbasic ../script/msg_cmp pw_error2")
			ChangeDir("../")
		Else
			keystore_cmd$=ReplaceSubstr$(keystore_cmd$,VAR_CN$, Gui_TextField_GetValue$(cert_name_field))
			keystore_cmd$=ReplaceSubstr$(keystore_cmd$,VAR_OU$, Gui_TextField_GetValue$(cert_org_unit_field))
			keystore_cmd$=ReplaceSubstr$(keystore_cmd$,VAR_O$, Gui_TextField_GetValue$(cert_org_field))
			keystore_cmd$=ReplaceSubstr$(keystore_cmd$,VAR_C$, Gui_TextField_GetValue$(cert_cc_field))
			keystore_cmd$=ReplaceSubstr$(keystore_cmd$,VAR_ALIAS$, Gui_TextField_GetValue$(key_alias_field))
			keystore_cmd$=ReplaceSubstr$(keystore_cmd$,VAR_PW$, Gui_TextField_GetValue$(keystore_password_field))
			keystore_cmd$=ReplaceSubstr$(keystore_cmd$,VAR_KEYSTORE$, Gui_TextField_GetValue$(keystore_name_field))
			If FileExists(dir + "/" + Gui_TextField_GetValue$(keystore_name_field) + ".keystore") Then
				ChangeDir("../script")
				System("rcbasic ../script/msg_cmp exists")
				Exit While
			Else
				System(keystore_cmd$)
				If FileExists(dir + "/" + Gui_TextField_GetValue$(keystore_name_field) + ".keystore") Then
					ChangeDir("../script")
					System("rcbasic ../script/msg_cmp complete")
				Else
					ChangeDir("../script")
					System("rcbasic ../script/msg_cmp fail")
				End If
				Exit While
			End If
		End If
	ElseIf Gui_Button_Clicked(cancel_button) Then
		Exit While
	End If
	
	'Update events and draw gui
	Gui_Update() 'update must be called at the end of the main loop
Wend

Gui_WindowClose(win) 'closes the window
