'Include "gui.bas" 'include the gui library
'Include "msg.bas"

Sub SELECT_FILE_INIT()
	Gui_TextField_SetValue(dir_field, lb_path$)
	
	Gui_ListBox_Clear(dir_listbox)
	Gui_ListBox_AddItem(dir_listbox, "..\\")
	
	dir_item$ = DirFirst
	
	Dim img_file$[999]
	Dim img_file_count
	img_file_count = 0
	
	While dir_item <> ""
		If DirExists(lb_path$ + "\\" + dir_item) And Left(dir_item,1) <> "." Then
			Gui_ListBox_AddItem(dir_listbox, dir_item)
		ElseIf Length(dir_item) > 4 Then
			If Right(dir_item, 4) = ".png" Then
				img_file$[img_file_count] = dir_item
				img_file_count = img_file_count + 1
				'Gui_ListBox_AddItem(dir_listbox, dir_item)
			End If
		End If
		dir_item = DirNext
	Wend
	
	If img_file_count > 0 Then
		For i = 0 to img_file_count - 1
			Gui_ListBox_AddItem(dir_listbox, img_file[i])
		Next
	End If
	
End Sub


Sub SELECT_FILE_UPDATE()
	lb_selected_item = Gui_ListBox_GetSelectedItem(dir_listbox)
	If Gui_ListBox_ItemChanged(dir_listbox) And lb_selected_item = lb_current_item Then
		'Print "Dir Changed"
		While MouseButton(0)
			Update
		Wend
		If DirExists(Gui_ListBox_GetValue$(dir_listbox, lb_selected_item)) Then
			ChangeDir(Gui_ListBox_GetValue$(dir_listbox, lb_selected_item))			
			Gui_ListBox_SetSelectedItem(dir_listbox, 0)
			lb_path$ = Dir$
			lb_current_item = 0
			SELECT_FILE_INIT
		End If
	ElseIf Not MouseButton(0) Then
		lb_current_item = lb_selected_item
		Gui_TextField_SetValue(dir_field, lb_path$ + "\\" + Gui_ListBox_GetValue$(dir_listbox, lb_current_item))
	End If
End Sub

Function FileWindow$()
	'SELECT DIRECTORY WINDOW
	push_n(gui_current_win)
	push_s(dir$)
	dir_win = Gui_WindowOpen("Select Icon", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 640, 480)
	Gui_SetWindowActive(dir_win)

	dir_label = Gui_CreateLabel("Icon:", 120, 16)
	dir_field = Gui_CreateDynamicTextField(500, 16)
	dir_listbox = Gui_CreateListBox(500, 300)

	dir_cancel_button = Gui_CreateButton("Cancel", 100, 20)
	dir_select_button = Gui_CreateButton("Select", 100, 20)

	dir_main_panel = Gui_CreatePanel(600, 440) 'Create a panel

	Gui_Panel_AddObject(dir_main_panel, dir_label, 10, 20)
	Gui_Panel_AddObject(dir_main_panel, dir_field, 50, 20)
	Gui_Panel_AddObject(dir_main_panel, dir_listbox, 50, 40)
	Gui_Panel_AddObject(dir_main_panel, dir_cancel_button, 290, 370)
	Gui_Panel_AddObject(dir_main_panel, dir_select_button, 400, 370)

	Gui_Window_AddPanel(dir_win, dir_main_panel, 20, 20) 'Add panel to window at (x = 150, y = 50)

	SELECT_FILE_INIT

	'Start In Main Window
	Window(dir_win)

	If FileExists("\\tmp\\rcbasic_dir_select.txt") Then
		RemoveFile("\\tmp\\rcbasic_dir_select.txt")
	End If

	file_path$ = ""

	While Not Key(K_Q)
		If Gui_Button_Clicked(dir_cancel_button) Then
			file_path$ = ""
			Exit While
		ElseIf Gui_Button_Clicked(dir_select_button) Then
			file_path$ = Gui_TextField_GetValue$(dir_field)
			i = Gui_GetFreeImage
			LoadImage(i, file_path$)
			If ImageExists(i) Then
				DeleteImage(i)
				Exit While
			Else
				Msg("Must select a Image")
			End If
		End If
		
		'Update events and draw gui
		If ActiveWindow = dir_win Then
			SELECT_FILE_UPDATE
		End If
		Gui_Update() 'update must be called at the end of the main loop
	Wend

	Gui_WindowClose(dir_win) 'closes the window
	
	Gui_SetWindowActive(pop_n)
	ChangeDir$(pop_s$)

	Return file_path$
End Function
