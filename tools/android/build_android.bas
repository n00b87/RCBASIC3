ChangeDir("./script")
Include "./script/gui.bas" 'include the gui library
ChangeDir("../")

win = Gui_WindowOpen("Build Android App", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 640, 200) 'open a window

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


Gui_Window_AddPanel(win, main_panel, 0, 0)

ChangeDir("./keystore")
Dir$
k$ = DirFirst$
While k$ <> ""
	If Left(k$,1) <> "." Then
		Gui_DropDown_AddItem(keystore_name_selection, k$)
	End If
	k$ = DirNext$
Wend
ChangeDir("../")

While Not Key(K_ESCAPE)
	If Gui_Button_Clicked(ok_button) Then
		key_store$ = Gui_DropDown_GetValue$(keystore_name_selection, Gui_DropDown_GetSelectedItem(keystore_name_selection))
		key_alias$ = Gui_TextField_GetValue$(keystore_alias_field)
		key_store_pass$ = Gui_TextField_GetValue$(keystore_password_field)
		key_alias_pass$ = Gui_TextField_GetValue$(keystore_password_field)
		'print "key_store = ";key_store$
		'print "key_alias = ";key_alias$
		'print "key_store_pass = ";key_store_pass$
		'print "key_alias_pass = ";key_alias_pass$
		If Gui_CheckBox_GetValue(debug_checkbox) Then
			System("rcbasic build_apk -key_store " + key_store$ + " -key_alias " + key_alias$ + " -key_store_pass " + key_store_pass$ + " -key_alias_pass " + key_alias_pass$)
		End If
		
		If Gui_CheckBox_GetValue(release_checkbox) Then
			System("rcbasic build_apk -key_store " + key_store$ + " -key_alias " + key_alias$ + " -key_store_pass " + key_store_pass$ + " -key_alias_pass " + key_alias_pass$ + " -release -end")
		End If
	ElseIf Gui_Button_Clicked(cancel_button) Then
		Exit While
	End If
	Gui_Update
Wend

Gui_WindowClose(win)
