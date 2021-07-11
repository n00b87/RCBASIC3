Function Msg(txt$)
	push_n(gui_current_win)

	win = Gui_WindowOpen("Message", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, 300, 150)
	Gui_SetWindowActive(win)

	p = Gui_CreatePanel(300, 150)

	b = Gui_CreateButton("OK", 50, 20)

	label = Gui_CreateLabel(txt, len(txt)*21, 20)

	Gui_Panel_AddObject(p, b, 120, 120)

	lw = 0
	lh = 0
	GetTextSize(GUI_FONT, txt, lw, lh)

	Gui_Panel_AddObject(p, label, 150 - (lw/2), 40)

	Gui_Window_AddPanel(win, p, 0, 0)

	While True
		If Gui_Button_Clicked(b) Then
			Exit While
		End If
		Gui_Update
	Wend

	Gui_WindowClose(win)
	Gui_SetWindowActive(pop_n)
End Function
