ChangeDir("./script")
Include "./script/gui.bas" 'include the gui library
ChangeDir("../")
Print "M_DIR = ";Dir

win = Gui_WindowOpen("Build Android App", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 640, 480) 'open a window

keystore_name_label = Gui_CreateLabel("Key Store:",80, 20)
keystore_name_selection = Gui_CreateDropDown(500, 20)

keystore_alias_label = Gui_CreateLabel("Alias:", 80, 20)
keystore_alias_field = Gui_CreateTextField(500, 20)

keystore_password_label = Gui_CreateLabel("Password:", 80, 20)
keystore_password_field = Gui_CreateTextField(500, 20)


debug_label = Gui_CreateLabel("Debug:", 60, 20)
debug_checkbox = Gui_CreateCheckBox(20, 20)

release_label = Gui_CreateLabel("Release:", 60, 20)
release_checkbox = Gui_CreateCheckBox(20, 20)

ok_button = Gui_CreateButton("Build", 60, 20)
cancel_button = Gui_CreateButton("Close", 60, 20)

main_panel = Gui_CreatePanel(640, 200)

Gui_Panel_AddObject(main_panel, keystore_name_label, 10, 15)
Gui_Panel_AddObject(main_panel, keystore_name_selection, 90, 10)

Gui_Panel_AddObject(main_panel, keystore_alias_label, 20, 55)
Gui_Panel_AddObject(main_panel, keystore_alias_field, 90, 50)

Gui_Panel_AddObject(main_panel, keystore_password_label, 20, 95)
Gui_Panel_AddObject(main_panel, keystore_password_field, 90, 90)

Gui_Panel_AddObject(main_panel, debug_label, 240, 125)
Gui_Panel_AddObject(main_panel, debug_checkbox, 290, 120)

Gui_Panel_AddObject(main_panel, release_label, 340, 125)
Gui_Panel_AddObject(main_panel, release_checkbox, 390, 120)

Gui_Panel_AddObject(main_panel, ok_button, 300, 160)
Gui_Panel_AddObject(main_panel, cancel_button, 370, 160)


Gui_Window_AddPanel(win, main_panel, 0, 280)

'-----APP INFO PANEL------------------------
org_type_label = Gui_CreateLabel("Org Type:",80, 20)
org_type_selection = Gui_CreateDropDown(500, 20)

org_name_label = Gui_CreateLabel("Org Name:", 80, 20)
org_name_field = Gui_CreateTextField(500, 20)

app_name_label = Gui_CreateLabel("App Name:", 80, 20)
app_name_field = Gui_CreateTextField(500, 20)

orientation_label = Gui_CreateLabel("Display:",80, 20)
orientation_selection = Gui_CreateDropDown(500, 20)


app_panel = Gui_CreatePanel(640, 275)

Gui_Panel_AddObject(app_panel, org_type_label, 10, 15)
Gui_Panel_AddObject(app_panel, org_type_selection, 90, 10)

Gui_Panel_AddObject(app_panel, org_name_label, 20, 55)
Gui_Panel_AddObject(app_panel, org_name_field, 90, 50)

Gui_Panel_AddObject(app_panel, app_name_label, 20, 95)
Gui_Panel_AddObject(app_panel, app_name_field, 90, 90)

Gui_Panel_AddObject(app_panel, orientation_label, 20, 135)
Gui_Panel_AddObject(app_panel, orientation_selection, 90, 130)

Gui_Window_AddPanel(win, app_panel, 0, 0)


'Keystore Name Selection
ChangeDir("./keystore")
Print "KS_DIR = ";Dir
k$ = DirFirst$
print "K = "; Dir
While k$ <> ""
	If Left(k$,1) <> "." Then
		Gui_DropDown_AddItem(keystore_name_selection, k$)
	Else
		Print Left(k$,1)
	End If
	k$ = DirNext$
Wend
ChangeDir("../")

'Org Type Selection
Gui_DropDown_AddItem(org_type_selection, "com")
Gui_DropDown_AddItem(org_type_selection, "org")

'Orientation Selection
Gui_DropDown_AddItem(orientation_selection, "landscape")
Gui_DropDown_AddItem(orientation_selection, "portrait")

Dim org_type$
Dim org_name$
Dim app_name$
Dim act_name$


Function Gen_Manifest()
	org_type$ = Gui_DropDown_GetValue$(org_type_selection, Gui_DropDown_GetSelectedItem(org_type_selection))
	org_name$ = Gui_TextField_GetValue$(org_name_field)
	app_name$ = Gui_TextField_GetValue$(app_name_field)
	orientation$ = Gui_DropDown_GetValue$(orientation_selection, Gui_DropDown_GetSelectedItem(orientation_selection))
	
	If org_name = "" or lcase(org_name) = "libsdl" Then
		Print "Org Name is NULL"
		Return False
	End If
	
	If app_name = "" Then
		Print "App Name is NULL"
		Return False
	End If
	
	
	act_name$ = "rcbasic_" + ReplaceSubstr(Trim(app_name), " ", "_")
	package_name$ = Trim(org_type) + "." + Trim(org_name) + "." + act_name
	print "org_type: ";org_type
	print "org_name: ";org_name
	print "app_name: ";app_name
	print "orientation: ";orientation
	f = FreeFile
	manifest_file$ = Dir + "/script/AndroidManifest.xml"
	If Not FileOpen(f, manifest_file$, TEXT_INPUT) Then
		Print "Could not open ";manifest_file$
		Return False
	End If
	
	manifest_str$ = ""
	
	While Not EOF(f)
		manifest_str$ = manifest_str$ + ReadLine(f) + "\n"
	Wend
	
	manifest_str$ = ReplaceSubstr(manifest_str$, "rcbasic_package", package_name$)
	manifest_str$ = ReplaceSubstr(manifest_str$, "rcbasic_application_label", app_name$)
	manifest_str$ = ReplaceSubstr(manifest_str$, "rcbasic_activity_name", act_name$)
	manifest_str$ = ReplaceSubstr(manifest_str$, "rcbasic_app_label", app_name$)
	manifest_str$ = ReplaceSubstr(manifest_str$, "rcbasic_orientation", orientation$)
	
	FileClose(f)
	
	If FileExists(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name + "/" + app_name + "/" + act_name + ".java") Then
		RemoveFile(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name + "/" + app_name + "/" + act_name + ".java")
	End If
	
	If DirExists(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name + "/" + app_name) Then
		RemoveDir(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name + "/" + app_name)
	End If
	
	If Not DirExists(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name) Then
		MakeDir(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name)
	End If
	
	MakeDir(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name + "/" + app_name)
	
	If FileExists(Dir$ + "/rcbasic_android/AndroidManifest.xml") Then
		RemoveFile(Dir$ + "/rcbasic_android/AndroidManifest.xml")
	End If
	
	FileOpen(f, Dir$ + "/rcbasic_android/AndroidManifest.xml", TEXT_OUTPUT_PLUS)
	WriteLine(f, manifest_str$)
	FileClose(f)
	
	
	rc_java$ = ""
	
	FileOpen(f, Dir$ + "/script/rcbasic.java", TEXT_INPUT)
	
	While Not EOF(f)
		rc_java$ = rc_java$ + ReadLine(f) + "\n"
	Wend
	
	FileClose(f)
	
	rc_java$ = ReplaceSubstr(rc_java$, "package_name", package_name)
	rc_java$ = ReplaceSubstr(rc_java$, "app_name", act_name)
	
	'---JAVA FILE
	FileOpen(f, Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name + "/" + app_name + "/" + act_name + ".java", TEXT_OUTPUT_PLUS)
	WriteLine(f, rc_java$)
	FileClose(f)
	Return True
End Function

Sub Clean_TMP_Dir()
	If FileExists(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name + "/" + app_name + "/" + act_name + ".java") Then
		RemoveFile(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name + "/" + app_name + "/" + act_name + ".java")
	End If
	
	If DirExists(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name + "/" + app_name) Then
		RemoveDir(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name + "/" + app_name)
	End If
	
	If DirExists(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name) Then
		RemoveDir(Dir$ + "/rcbasic_android/src/" + org_type + "/" + org_name)
	End If
End Sub

While Not Key(K_ESCAPE)
	If Gui_Button_Clicked(ok_button) Then
		If Gen_Manifest Then
			'Exit While
			key_store$ = Gui_DropDown_GetValue$(keystore_name_selection, Gui_DropDown_GetSelectedItem(keystore_name_selection))
			key_alias$ = Gui_TextField_GetValue$(keystore_alias_field)
			key_store_pass$ = Gui_TextField_GetValue$(keystore_password_field)
			key_alias_pass$ = Gui_TextField_GetValue$(keystore_password_field)
			'print "key_store = ";key_store$
			'print "key_alias = ";key_alias$
			'print "key_store_pass = ";key_store_pass$
			'print "key_alias_pass = ";key_alias_pass$
			If Gui_CheckBox_GetValue(debug_checkbox) Then
				System("rcbasic build_apk -key_store NA -key_alias NA -key_store_pass NA -key_alias_pass NA -app_name " + ReplaceSubstr(Trim(app_name$), " ", "_"))
			End If
			
			If Gui_CheckBox_GetValue(release_checkbox) Then
				System("rcbasic build_apk -key_store " + key_store$ + " -key_alias " + key_alias$ + " -key_store_pass " + key_store_pass$ + " -key_alias_pass " + key_alias_pass$ + " -app_name " + ReplaceSubstr(Trim(app_name$), " ", "_") + " -release -end")
			End If
			
			Clean_TMP_Dir
			
		End If
	ElseIf Gui_Button_Clicked(cancel_button) Then
		Exit While
	End If
	Gui_Update
Wend

Gui_WindowClose(win)
