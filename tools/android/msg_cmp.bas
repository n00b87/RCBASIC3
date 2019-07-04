Include "gui.bas" 'include the gui library

cmp_msg_win = Gui_WindowOpen("Msg", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 200, 100)

msg_complete_panel = Gui_CreatePanel(200,100)

For i = 0 to NumCommands-1
	If Command$(i) = "complete" Then
		Gui_Panel_AddObject(msg_complete_panel, Gui_CreateLabel("Keystore Created", 160, 20), 20, 20)
		Exit For
	ElseIf Command$(i) = "fail" Then
		Gui_Panel_AddObject(msg_complete_panel, Gui_CreateLabel("Keystore Failed", 160, 20), 20, 20)
		Exit For
	ElseIf Command$(i) = "exists" Then
		Gui_Panel_AddObject(msg_complete_panel, Gui_CreateLabel("Keystore Already Exists", 160, 20), 20, 20)
		Exit For
	ElseIf Command$(i) = "pw_error1" Then
		Gui_Panel_AddObject(msg_complete_panel, Gui_CreateLabel("Invalid Password", 160, 20), 20, 20)
		Exit For
	ElseIf Command$(i) = "pw_error2" Then
		Gui_Panel_AddObject(msg_complete_panel, Gui_CreateLabel("Password doesn't Match", 160, 20), 20, 20)
		Exit For
	ElseIf Command$(i) = "release_build_fail" Then
		Gui_Panel_AddObject(msg_complete_panel, Gui_CreateLabel("Release Build Failed", 160, 20), 20, 20)
		Exit For
	ElseIf Command$(i) = "release_build_complete" Then
		Gui_Panel_AddObject(msg_complete_panel, Gui_CreateLabel("Release Build Successful", 160, 20), 20, 20)
		Exit For
	ElseIf Command$(i) = "debug_build_fail" Then
		Gui_Panel_AddObject(msg_complete_panel, Gui_CreateLabel("Debug Build Failed", 160, 20), 20, 20)
		Exit For
	ElseIf Command$(i) = "debug_build_complete" Then
		Gui_Panel_AddObject(msg_complete_panel, Gui_CreateLabel("Debug Build Successful", 160, 20), 20, 20)
		Exit For
	End If
Next

msg_complete_button = Gui_CreateButton("OK", 60, 20)
Gui_Panel_AddObject(msg_complete_panel, msg_complete_button, 70, 70)

Gui_Window_AddPanel(cmp_msg_win, msg_complete_panel, 0, 0)

While Not Gui_Button_Clicked(msg_complete_button)
	
	Gui_Update
Wend
