Include "gui.bas" 'include the gui library

key_store$=""
key_store_pass$=""
key_alias$=""
key_alias_pass$=""

'panel
android_settings_panel = Gui_CreatePanel(630, 445)

'-----APP INFO PANEL------------------------
app_id_label = Gui_CreateLabel("App ID:",80, 20)
app_id_field = Gui_CreateTextField(500, 20)


'Orientation Selection
orientation_label = Gui_CreateLabel("Display:",80, 20)
orientation_dropdown = Gui_CreateDropDown(500, 20)

Gui_DropDown_AddItem(orientation_dropdown, "default")
Gui_DropDown_AddItem(orientation_dropdown, "landscape")
Gui_DropDown_AddItem(orientation_dropdown, "portrait")


'Key Store Info
keystore_label = Gui_CreateLabel("Keystore:",160, 20)
keystore_field = Gui_CreateTextField(440, 20)

keystore_password_label = Gui_CreateLabel("Keystore Password:", 160, 20)
keystore_password_field = Gui_CreateTextField(335, 20)
keystore_password_show_button = Gui_CreateButton("show/hide", 100, 20) 'Create a button

alias_label = Gui_CreateLabel("Alias:", 160, 20)
alias_field = Gui_CreateTextField(440, 20)

alias_password_label = Gui_CreateLabel("Alias Password:", 160, 20)
alias_password_field = Gui_CreateTextField(335, 20)
alias_password_show_button = Gui_CreateButton("show/hide", 100, 20) 'Create a button

java_dir_label = Gui_CreateLabel("Java Src Path:", 160, 20)
java_dir_field = Gui_CreateTextField(335, 20)
java_dir_init_button = Gui_CreateButton("Initialize", 100, 20) 'Create a button

debug_label = Gui_CreateLabel("Debug:", 100, 16)
release_label = Gui_CreateLabel("Release:", 100, 16)

debug_cb = Gui_CreateCheckBox(16, 16)
release_cb = Gui_CreateCheckBox(16, 16)

'Position Widgets in Panel
Gui_Panel_AddObject(android_settings_panel, app_id_label, 20, 15)
Gui_Panel_AddObject(android_settings_panel, app_id_field, 90, 10)

Gui_Panel_AddObject(android_settings_panel, orientation_label, 20, 55)
Gui_Panel_AddObject(android_settings_panel, orientation_dropdown, 90, 50)

Gui_Panel_AddObject(android_settings_panel, keystore_label, 20, 115)
Gui_Panel_AddObject(android_settings_panel, keystore_field, 150, 110)

Gui_Panel_AddObject(android_settings_panel, keystore_password_label, 20, 155)
Gui_Panel_AddObject(android_settings_panel, keystore_password_field, 150, 150)
Gui_Panel_AddObject(android_settings_panel, keystore_password_show_button, 490, 150)

Gui_Panel_AddObject(android_settings_panel, alias_label, 20, 215)
Gui_Panel_AddObject(android_settings_panel, alias_field, 150, 210)

Gui_Panel_AddObject(android_settings_panel, alias_password_label, 20, 255)
Gui_Panel_AddObject(android_settings_panel, alias_password_field, 150, 250)
Gui_Panel_AddObject(android_settings_panel, alias_password_show_button, 490, 250)

Gui_Panel_AddObject(android_settings_panel, java_dir_label, 20, 335)
Gui_Panel_AddObject(android_settings_panel, java_dir_field, 150, 330)
Gui_Panel_AddObject(android_settings_panel, java_dir_init_button, 490, 330)

Gui_Panel_AddObject(android_settings_panel, debug_label, 20, 390)
Gui_Panel_AddObject(android_settings_panel, debug_cb, 60, 390)

Gui_Panel_AddObject(android_settings_panel, release_label, 110, 390)
Gui_Panel_AddObject(android_settings_panel, release_cb, 170, 390)




Gui_TextField_SetValue(app_id_field, ANDROID_APP_ID$)
Gui_DropDown_SetSelectedItem(orientation_dropdown, Max(Gui_DropDown_Search(orientation_dropdown, ANDROID_ORIENTATION$), 0))

Gui_TextField_SetValue(keystore_field, ANDROID_KEYSTORE$)

Gui_TextField_SetPasswordField(keystore_password_field, true)
Gui_TextField_SetValue(keystore_password_field, ANDROID_KEYSTORE_PASS$)

Gui_TextField_SetValue(alias_field, ANDROID_ALIAS$)

Gui_TextField_SetPasswordField(alias_password_field, true)
Gui_TextField_SetValue(alias_password_field, ANDROID_ALIAS_PASS$)

Gui_TextField_SetValue(java_dir_field, ANDROID_JAVA_DIR$)

Gui_CheckBox_SetValue(debug_cb, ANDROID_BUILD_DEBUG)
Gui_CheckBox_SetValue(release_cb, ANDROID_BUILD_RELEASE)

Dim show_keystore_pw : show_keystore_pw = false
Dim show_alias_pw : show_alias_pw = false


/'While Not Key(K_ESCAPE)
	key_store$ = Gui_TextField_GetValue$(keystore_field)
	key_store_pass$ = Gui_TextField_GetValue$(keystore_password_field)
			
	key_alias$ = Gui_TextField_GetValue$(alias_field)
	key_alias_pass$ = Gui_TextField_GetValue$(alias_password_field)
	
	Gui_Update
Wend'/

