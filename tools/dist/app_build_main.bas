Include "gui.bas" 'include the gui library


main_panel = Gui_CreatePanel(630, 445) 'Create a panel


project_dir_label = Gui_CreateLabel("Project Dir:", 120, 16)
project_dir_field = Gui_CreateTextField(300, 16)
project_dir_button = Gui_CreateButton("Browse", 100, 20) 'Create a button

project_name_label = Gui_CreateLabel("Project Name:", 120, 16)
project_name_field = Gui_CreateTextField(300, 16)

category_label = Gui_CreateLabel("Category:", 120, 16)
category_dropdown = Gui_CreateDropDown(300, 16)

Gui_DropDown_AddItem(category_dropdown, "AudioVideo")
Gui_DropDown_AddItem(category_dropdown, "Audio")
Gui_DropDown_AddItem(category_dropdown, "Video")
Gui_DropDown_AddItem(category_dropdown, "Development")
Gui_DropDown_AddItem(category_dropdown, "Education")
Gui_DropDown_AddItem(category_dropdown, "Game")
Gui_DropDown_AddItem(category_dropdown, "Graphics")
Gui_DropDown_AddItem(category_dropdown, "Network")
Gui_DropDown_AddItem(category_dropdown, "Office")
Gui_DropDown_AddItem(category_dropdown, "Science")
Gui_DropDown_AddItem(category_dropdown, "Settings")
Gui_DropDown_AddItem(category_dropdown, "System")
Gui_DropDown_AddItem(category_dropdown, "Utility")

icon_label = Gui_CreateLabel("Project Icon:", 100, 16)
icon_preview = Gui_CreateSurface(128, 128)
icon_button = Gui_CreateButton("Select Image", 128, 20)

terminal_label = Gui_CreateLabel("Enable Terminal:", 120, 16)
terminal_checkbox = Gui_CreateCheckBox(16,16) 'Create a Checkbox

web_thread_label = Gui_CreateLabel("Enable Web Threads:", 120, 16)
web_thread_checkbox = Gui_CreateCheckBox(16,16) 'Create a Checkbox

output_dir_label = Gui_CreateLabel("Output Dir:", 120, 16)
output_dir_field = Gui_CreateTextField(300, 16)
output_dir_button = Gui_CreateButton("Browse", 100, 20)

linux32_label = Gui_CreateLabel("Linux 32-Bit:", 100, 16)
linux64_label = Gui_CreateLabel("Linux 64-Bit:", 100, 16)
win32_label = Gui_CreateLabel("Windows 32-Bit:", 100, 16)
win64_label = Gui_CreateLabel("Windows 64-Bit:", 100, 16)
mac_label = Gui_CreateLabel("Mac OS:", 100, 16)
web_label = Gui_CreateLabel("Web Broswer:", 100, 16)
android_label = Gui_CreateLabel("Android APK:", 100, 16)

linux32_cb = Gui_CreateCheckBox(16, 16)
linux64_cb = Gui_CreateCheckBox(16, 16)
win32_cb = Gui_CreateCheckBox(16, 16)
win64_cb = Gui_CreateCheckBox(16, 16)
mac_cb = Gui_CreateCheckBox(16, 16)
web_cb = Gui_CreateCheckBox(16, 16)
android_cb = Gui_CreateCheckBox(16, 16)

make_button = Gui_CreateButton("MAKE APP", 110, 20)
save_button = Gui_CreateButton("SAVE PROJECT", 110, 20)


Gui_Panel_AddObject(main_panel, project_dir_label, 20, 20)
Gui_Panel_AddObject(main_panel, project_dir_field, 110, 20)
Gui_Panel_AddObject(main_panel, project_dir_button, 420, 20)

Gui_Panel_AddObject(main_panel, project_name_label, 20, 50)
Gui_Panel_AddObject(main_panel, project_name_field, 110, 50)

Gui_Panel_AddObject(main_panel, category_label, 20, 80)
Gui_Panel_AddObject(main_panel, category_dropdown, 110, 80)

Gui_Panel_AddObject(main_panel, icon_label, 20, 120)
Gui_Panel_AddObject(main_panel, icon_preview, 110, 120)
Gui_Panel_AddObject(main_panel, icon_button, 110, 250)

Gui_Panel_AddObject(main_panel, linux32_label, 280, 120)
Gui_Panel_AddObject(main_panel, linux64_label, 280, 140)
Gui_Panel_AddObject(main_panel, win32_label, 280, 160)
Gui_Panel_AddObject(main_panel, win64_label, 280, 180)
Gui_Panel_AddObject(main_panel, mac_label, 280, 200)
Gui_Panel_AddObject(main_panel, web_label, 280, 220)
Gui_Panel_AddObject(main_panel, android_label, 280, 240)

Gui_Panel_AddObject(main_panel, linux32_cb, 380, 120)
Gui_Panel_AddObject(main_panel, linux64_cb, 380, 140)
Gui_Panel_AddObject(main_panel, win32_cb, 380, 160)
Gui_Panel_AddObject(main_panel, win64_cb, 380, 180)
Gui_Panel_AddObject(main_panel, mac_cb, 380, 200)
Gui_Panel_AddObject(main_panel, web_cb, 380, 220)
Gui_Panel_AddObject(main_panel, android_cb, 380, 240)

Gui_Panel_AddObject(main_panel, terminal_label, 20, 290)
Gui_Panel_AddObject(main_panel, terminal_checkbox, 145, 290)

Gui_Panel_AddObject(main_panel, web_thread_label, 20, 310)
Gui_Panel_AddObject(main_panel, web_thread_checkbox, 145, 310)

Gui_Panel_AddObject(main_panel, output_dir_label, 20, 350)
Gui_Panel_AddObject(main_panel, output_dir_field, 110, 350)
Gui_Panel_AddObject(main_panel, output_dir_button, 420, 350)

Gui_Panel_AddObject(main_panel, make_button, 120, 400)
Gui_Panel_AddObject(main_panel, save_button, 250, 400)




icon = Gui_GetFreeImage
Dim iw
Dim ih


LoadAppProperties()

Gui_TextField_SetValue(project_dir_field, project_dir$)
Gui_TextField_SetValue(project_name_field, PROJECT_NAME$)

Gui_DropDown_SetSelectedItem(category_dropdown, Max(Gui_DropDown_Search(category_dropdown, PROJECT_CATEGORY$), 0))

print "icon_path=";icon_path$

If icon_path$ <> "" Then
	If ImageExists(icon) Then
		DeleteImage(icon)
	End If
	If FileExists(icon_path$) Then
		LoadImage(icon, icon_path$)
	End If
	
	If Not ImageExists(icon) Then
		icon_path$ = ""
	Else
		GetImageSize(icon, iw, ih)
		Gui_Surface_Clear(icon_preview)
		Gui_Surface_DrawImage_Blit_Ex(icon_preview, icon, 0, 0, 128, 128, 0, 0, iw, ih)
	End If
Else
	icon_path$ = ""
End If
Gui_Surface_Update(icon_preview)


Dim platform_arg$ : platform_arg$ = TGT_PLATFORMS$
Dim platform_token$: platform_token$ = GetToken$(platform_arg$)

While Trim(platform_token$) <> ""
	Select Case platform_token$
	Case "LINUX_32"
		Gui_CheckBox_SetValue(linux32_cb, True)
	Case "LINUX_64"
		Gui_CheckBox_SetValue(linux64_cb, True)
	Case "WIN_32"
		Gui_CheckBox_SetValue(win32_cb, True)
	Case "WIN_64"
		Gui_CheckBox_SetValue(win64_cb, True)
	Case "MAC"
		Gui_CheckBox_SetValue(mac_cb, True)
	Case "WEB"
		Gui_CheckBox_SetValue(web_cb, True)
	Case "ANDROID"
		Gui_CheckBox_SetValue(android_cb, True)
	End Select
	platform_token$ = GetToken$(platform_arg$)
Wend


If TERMINAL_FLAG$ = "true" Then
	Gui_CheckBox_SetValue(terminal_checkbox, True)
End If

If enable_threads$ = "true" Then
	Gui_CheckBox_SetValue(web_thread_checkbox, True)
End If

Gui_TextField_SetValue(output_dir_field, output_dir$)

