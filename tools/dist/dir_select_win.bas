Include "gui.bas" 'include the gui library
Include Once

Dim dir_win

Dim dir_label
Dim dir_field
Dim dir_listbox

Dim dir_cancel_button
Dim dir_select_button

Dim dir_main_panel

Dim lb_path$
lb_path$ = Dir$

Dim lb_current_item
lb_current_item = 0

Dim path_join$
Dim HOME$

If OS$ = "WINDOWS" Then
	path_join$ = "\\"
	HOME$=Env$("USERPROFILE")
Else
	path_join$ = "/"
	HOME$=Env$("HOME")
End if


Function GetArg$(arg_name$)
	arg_value$ = ""
	For i = 0 to NumCommands()-1 Step 1
		If Left$(Command$(i), Length(arg_name$)+1) = (arg_name$+"=") Then
			If Length(Command$(i)) > (Length(arg_name$)+1) Then
				arg_value$ = Mid$(Command$(i), Length(arg_name$)+1, Length(Command$(i)) - (Length(arg_name$)+1))
			End If
		ElseIf Command$(i) = arg_name$ Then
			If i < (NumCommands()-1) Then
				arg_value$ = Command$(i+1)
				i = i + 1
			End If
		End If
	Next
	Return arg_value$
End Function


Sub SELECT_DIR_INIT()
	Gui_TextField_SetValue(dir_field, lb_path$)
	
	Gui_ListBox_Clear(dir_listbox)
	Gui_ListBox_AddItem(dir_listbox, ".." + path_join$)
	
	dir_item$ = DirFirst
	
	While Trim(dir_item) <> ""
		If Left(dir_item+" ",1) <> "." Then
			If DirExists(lb_path$ + path_join$ + dir_item) Then
				Gui_ListBox_AddItem(dir_listbox, dir_item)
			End If
		End If
		dir_item = DirNext
	Wend
End Sub


Sub SELECT_DIR_UPDATE()
	lb_selected_item = Gui_ListBox_GetSelectedItem(dir_listbox)
	If Gui_ListBox_ItemChanged(dir_listbox) And lb_selected_item = lb_current_item Then
		While MouseButton(0)
			Update
		Wend
		ChangeDir(Gui_ListBox_GetValue$(dir_listbox, lb_selected_item))
		Gui_ListBox_SetSelectedItem(dir_listbox, 0)
		lb_path$ = Dir$
		lb_current_item = 0
		SELECT_DIR_INIT
	ElseIf Not MouseButton(0) Then
		lb_current_item = lb_selected_item
		Gui_TextField_SetValue(dir_field, lb_path$ + path_join$ + Gui_ListBox_GetValue$(dir_listbox, lb_current_item))
	End If
End Sub


'SELECT DIRECTORY WINDOW
Function DirectoryWindow$(start_dir$)
	push_n(gui_current_win)
	
	Push_S(Dir$)
	
	lb_path$ = Dir$
	
	If start_dir$ <> "" And DirExists(start_dir$) Then
		lb_path$ = start_dir$
		ChangeDir(lb_path$)
	End If

	lb_current_item = 0
	
	dir_win = Gui_WindowOpen("Select Dir", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 640, 480)
	Gui_SetWindowActive(dir_win)

	dir_label = Gui_CreateLabel("Dir:", 120, 16)
	dir_field = Gui_CreateDynamicTextField(500, 16)
	
	'Print "LB"
	dir_listbox = Gui_CreateListBox(500, 300)
	'Print "LB END"

	dir_cancel_button = Gui_CreateButton("Cancel", 100, 20)
	dir_select_button = Gui_CreateButton("Select", 100, 20)

	dir_main_panel = Gui_CreatePanel(600, 440) 'Create a panel

	Gui_Panel_AddObject(dir_main_panel, dir_label, 10, 20)
	Gui_Panel_AddObject(dir_main_panel, dir_field, 50, 20)
	Gui_Panel_AddObject(dir_main_panel, dir_listbox, 50, 40)
	Gui_Panel_AddObject(dir_main_panel, dir_cancel_button, 290, 370)
	Gui_Panel_AddObject(dir_main_panel, dir_select_button, 400, 370)

	Gui_Window_AddPanel(dir_win, dir_main_panel, 20, 20) 'Add panel to window at (x = 150, y = 50)

	SELECT_DIR_INIT

	'Start In Main Window

	dir_select_path$ = ""

	While Not Key(K_Q)
		If Gui_Button_Clicked(dir_cancel_button) Then
			dir_select_path$ = ""
			Exit While
		ElseIf Gui_Button_Clicked(dir_select_button) Then
			dir_select_path$ = Gui_TextField_GetValue$(dir_field)
			Exit While
		End If
		
		'Update events and draw gui
		If gui_current_win = dir_win Then
			SELECT_DIR_UPDATE
		End If
		Gui_Update() 'update must be called at the end of the main loop
	Wend

	Gui_WindowClose(dir_win) 'closes the window
	
	Gui_SetWindowActive(pop_n)
	
	ChangeDir$(Pop_S$)

	Return Replace(dir_select_path, ".."+path_join$, "")
End Function

Include "icon_select_win.bas"

'Print FileWindow$
'Print "Output++: ";DirectoryWindow$
