Include Once


GUI_DIR$ = Dir$

GUI_FONT = 0
GUI_FONT_COLOR = RGB(20,20,20)
Dim GUI_FONT_W
Dim GUI_FONT_H

Dim GUI_SCROLLDOWN_IMAGE
Dim GUI_SCROLLUP_IMAGE
Dim GUI_PAGEDOWN_IMAGE
Dim GUI_PAGEUP_IMAGE

GUI_DRAW_COLOR = 0

GUI_TMP_CANVAS = 0
GUI_WIN_CANVAS = 1
GUI_SURFACE_CANVAS = 2

MAX_GUI_ELEMENTS = 800
MAX_WINDOWS = 8
MAX_PANELS = 100
MAX_PANEL_OBJECTS = 50
MAX_TAB_GROUPS = 50
MAX_TABS = 20
MAX_TAB_OBJECTS = 20
MAX_BUTTONS = 100
MAX_DROPDOWNS = 30
MAX_DROPDOWN_VALUES = 20
MAX_LISTBOXES =100
MAX_LISTBOX_VALUES = 1024
MAX_TEXTFIELDS = 100
MAX_CHECKBOXES = 100
MAX_LABELS = 200
MAX_IMAGECLIPS = 100
MAX_IMAGESLIDES = 100
MAX_IMAGESLIDE_CLIPS = 100
MAX_IMAGES = 1024
MAX_SURFACES = 50

'MOUSE STATE
MOUSE_STATE = 0

MOUSE_PRESSED = 1
MOUSE_HOLD = 2
MOUSE_RELEASED = 3

'EVENTS
EVENT_ID = 0
EVENT_TYPE = 0

BUTTON_PRESSED = 1
BUTTON_RELEASED = 2
TAB_SWITCH = 3
DROPDOWN_PRESSED = 4
DROPDOWN_RELEASED = 5
LISTBOX_SCROLLUP_PRESSED = 6
LISTBOX_SCROLLUP_RELEASED = 7
LISTBOX_SCROLLDOWN_PRESSED = 8
LISTBOX_SCROLLDOWN_RELEASED = 9
LISTBOX_PAGEUP_PRESSED = 10
LISTBOX_PAGEUP_RELEASED = 11
LISTBOX_PAGEDOWN_PRESSED = 12
LISTBOX_PAGEDOWN_RELEASED = 13
LISTBOX_ITEM_SELECT = 14
TEXTFIELD_PRESSED = 15
TEXTFIELD_RELEASED = 16
TEXTFIELD_RETURN = 17
CHECKBOX_PRESSED = 18
CHECKBOX_RELEASED = 19
IMAGECLIP_PRESSED = 20
IMAGECLIP_RELEASED = 21
IMAGESLIDE_PRESSED = 22
IMAGESLIDE_RELEASED = 23
SURFACE_PRESSED = 24
SURFACE_RELEASED = 25

'GUI STATE
GUI_STATE = 0

GUI_STATE_DROPDOWN_OPEN = 1
GUI_STATE_TEXTFIELD_EDIT = 2

'Gui
GUI_TYPE_PANEL = 1
GUI_TYPE_BUTTON = 2
GUI_TYPE_TAB = 3
GUI_TYPE_DROPDOWN = 4
GUI_TYPE_LISTBOX = 5
GUI_TYPE_TEXTFIELD = 6
GUI_TYPE_CHECKBOX = 7
GUI_TYPE_LABEL = 8
GUI_TYPE_IMAGECLIP = 9
GUI_TYPE_IMAGESLIDE = 10
GUI_TYPE_SURFACE = 11

Dim Gui_Element_Index[MAX_GUI_ELEMENTS]
Dim Gui_Element_Type[MAX_GUI_ELEMENTS]
Dim Gui_Element_Active[MAX_GUI_ELEMENTS]
Dim Gui_Element_Exists[MAX_GUI_ELEMENTS]
Dim Gui_Element_Parent[MAX_GUI_ELEMENTS]
Dim Gui_Element_Window[MAX_GUI_ELEMENTS]

'Window
CURRENT_WINDOW = 0

GUI_CLEAR_COLOR = rgb(140,140,140)

SetClearColor(GUI_CLEAR_COLOR)

Dim Gui_Window_Exists[MAX_WINDOWS]
Dim Gui_Window_Panel_ID[MAX_WINDOWS, MAX_PANELS]
Dim Gui_Window_Panel_Exists[MAX_WINDOWS, MAX_PANELS]
Dim Gui_Window_Panel_Type[MAX_WINDOWS, MAX_PANELS]
Dim Gui_Window_Width[MAX_WINDOWS]
Dim Gui_Window_Height[MAX_WINDOWS]

MAX_WINDOW_OBJECTS = 2000

WINDOW_OBJECT_TYPE_PANEL = 0
WINDOW_OBJECT_TYPE_BUTTON = 1
WINDOW_OBJECT_TYPE_DROPDOWN = 2
WINDOW_OBJECT_TYPE_LISTBOX = 3
WINDOW_OBJECT_TYPE_TEXTFIELD = 4
WINDOW_OBJECT_TYPE_CHECKBOX = 5
WINDOW_OBJECT_TYPE_IMAGECLIP = 6
WINDOW_OBJECT_TYPE_IMAGESLIDE = 7
WINDOW_OBJECT_TYPE_LABEL = 8
WINDOW_OBJECT_TYPE_SURFACE = 9
WINDOW_OBJECT_TYPE_TABGROUP = 10

'WINDOW_OBJECT Structure
'0 - TYPE
'1 - OBJECT_ID
Dim Gui_Window_Objects[MAX_WINDOWS, MAX_WINDOW_OBJECTS, 2]
Dim Gui_Window_NumObjects[MAX_WINDOWS]

'Panel
PANEL_BKG_TYPE_COLOR = 0
PANEL_BKG_TYPE_IMAGE = 1

PANEL_BKG_TYPE = 0
PANEL_BKG_VALUE = RGB(110,110,110)

Dim Gui_Panel_Exists[MAX_PANELS]
Dim Gui_Panel_isActive[MAX_PANELS]
Dim Gui_Panel_X[MAX_PANELS]
Dim Gui_Panel_Y[MAX_PANELS]
Dim Gui_Panel_W[MAX_PANELS]
Dim Gui_Panel_H[MAX_PANELS]
Dim Gui_Panel_Image[MAX_PANELS]
Dim Gui_Panel_Object_ID[MAX_PANELS, MAX_PANEL_OBJECTS]
Dim Gui_Panel_Object_Type[MAX_PANELS, MAX_PANEL_OBJECTS]
Dim Gui_Panel_Object_Exists[MAX_PANELS, MAX_PANEL_OBJECTS]

'Tab Switcher
GUI_TAB_COLOR1 = RGB(128,128,128)
GUI_TAB_COLOR2 = RGB(96,96,96)
GUI_TAB_BORDER_COLOR = RGB(160,160,160)

Dim Gui_TabGroup_Parent[MAX_TAB_GROUPS]
Dim Gui_TabGroup_Exists[MAX_TAB_GROUPS]
Dim Gui_TabGroup_X[MAX_TAB_GROUPS]
Dim Gui_TabGroup_Y[MAX_TAB_GROUPS]
Dim Gui_TabGroup_W[MAX_TAB_GROUPS]
Dim Gui_TabGroup_H[MAX_TAB_GROUPS]
Dim Gui_TabGroup_ActiveTab[MAX_TAB_GROUPS]
Dim Gui_TabGroup_Tab_Object_ID[MAX_TAB_GROUPS, MAX_TABS, MAX_TAB_OBJECTS]
Dim Gui_TabGroup_Tab_Object_Type[MAX_TAB_GROUPS, MAX_TABS, MAX_TAB_OBJECTS]
Dim Gui_TabGroup_Tab_Object_Exists[MAX_TAB_GROUPS, MAX_TABS, MAX_TAB_OBJECTS]
Dim Gui_TabGroup_Tab_Exists[MAX_TAB_GROUPS, MAX_TABS]
Dim Gui_TabGroup_Tab_Image[MAX_TAB_GROUPS, MAX_TABS, 2]
Dim Gui_TabGroup_Tab_Title$[MAX_TAB_GROUPS, MAX_TABS]
Dim Gui_TabGroup_TabCount[MAX_TAB_GROUPS]

'Button
GUI_BUTTON_COLOR1 = RGB(120, 120, 120)
GUI_BUTTON_COLOR2 = RGB(84, 84, 84)
Dim Gui_Button_Panel[MAX_BUTTONS]
Dim Gui_Button_Exists[MAX_BUTTONS]
Dim Gui_Button_X[MAX_BUTTONS]
Dim Gui_Button_Y[MAX_BUTTONS]
Dim Gui_Button_W[MAX_BUTTONS]
Dim Gui_Button_H[MAX_BUTTONS]
Dim Gui_Button_Image[MAX_BUTTONS,2]
Dim Gui_Button_Current_Image[MAX_BUTTONS]

'DropDown
GUI_DROPDOWN_COLOR1 = RGB(120, 120, 120)
GUI_DROPDOWN_COLOR2 = RGB(80, 80, 80)
GUI_DROPDOWN_BORDER_COLOR = RGB(100,100,100)
GUI_DROPDOWN_HIGHLIGHT_COLOR = RGBA(0,180,228,20)
Dim GUI_DROPDOWN_MIN_W
Dim GUI_DROPDOWN_MIN_H
Dim Gui_DropDown_Panel[MAX_DROPDOWNS]
Dim Gui_DropDown_Exists[MAX_DROPDOWNS]
Dim Gui_DropDown_X[MAX_DROPDOWNS]
Dim Gui_DropDown_Y[MAX_DROPDOWNS]
Dim Gui_DropDown_W[MAX_DROPDOWNS]
Dim Gui_DropDown_H[MAX_DROPDOWNS]
Dim Gui_DropDown_Image[MAX_DROPDOWNS, 3]
Dim Gui_DropDown_Current_Image[MAX_DROPDOWNS]
Dim Gui_DropDown_Value$[MAX_DROPDOWNS, MAX_DROPDOWN_VALUES]
Dim Gui_DropDown_Count[MAX_DROPDOWNS]
Dim Gui_DropDown_Selected_Item[MAX_DROPDOWNS]
Dim Gui_DropDown_Highlighted_X
Dim Gui_DropDown_Highlighted_Y
Dim Gui_DropDown_Highlighted_Index

'ListBox
GUI_LISTBOX_COLOR1 = RGB(160, 160, 160)
GUI_LISTBOX_COLOR2 = RGB(90, 90, 90)
GUI_LISTBOX_COLOR3 = RGB(64, 64, 64)
GUI_LISTBOX_BORDER_COLOR = RGB(100,100,100)
GUI_LISTBOX_HIGHLIGHT_COLOR = RGB(0,0,160)
Dim GUI_LISTBOX_MIN_W
Dim GUI_LISTBOX_MIN_H
Dim Gui_ListBox_Panel[MAX_LISTBOXES]
Dim Gui_ListBox_Exists[MAX_LISTBOXES]
Dim Gui_ListBox_X[MAX_LISTBOXES]
Dim Gui_ListBox_Y[MAX_LISTBOXES]
Dim Gui_ListBox_W[MAX_LISTBOXES]
Dim Gui_ListBox_H[MAX_LISTBOXES]
Dim Gui_ListBox_Image[MAX_LISTBOXES]
Dim Gui_ListBox_Value$[MAX_LISTBOXES, MAX_LISTBOX_VALUES]
Dim Gui_ListBox_Count[MAX_LISTBOXES]
Dim Gui_ListBox_Selected_Item[MAX_LISTBOXES]
Dim Gui_ListBox_Offset[MAX_LISTBOXES]
Dim Gui_ListBox_ScrollBar_Image[MAX_LISTBOXES, 8]
Dim Gui_ListBox_ScrollBar_Action[4]
Dim Gui_ListBox_ScrollBar_Pressed[4]
Dim Gui_ListBox_ScrollBar_Hover[4]
Dim Gui_ListBox_Highlighted_X
Dim Gui_ListBox_Highlighted_Y
Dim Gui_ListBox_Highlighted_Index

'TextField
GUI_TEXTFIELD_COLOR1 = RGB(180, 180, 180)
GUI_TEXTFIELD_BORDER_COLOR = RGB(64, 64, 64)
Dim GUI_TEXTFIELD_MIN_W
Dim GUI_TEXTFIELD_MIN_H
Dim Gui_TextField_Panel[MAX_TEXTFIELDS]
Dim Gui_TextField_Exists[MAX_TEXTFIELDS]
Dim Gui_TextField_isDynamic[MAX_TEXTFIELDS]
Dim Gui_TextField_X[MAX_TEXTFIELDS]
Dim Gui_TextField_Y[MAX_TEXTFIELDS]
Dim Gui_TextField_W[MAX_TEXTFIELDS]
Dim Gui_TextField_H[MAX_TEXTFIELDS]
Dim Gui_TextField_Image[MAX_TEXTFIELDS]
Dim Gui_TextField_Value$[MAX_TEXTFIELDS]
Dim Gui_TextField_Offset[MAX_TEXTFIELDS]
Dim Gui_TextField_isPassword[MAX_TEXTFIELDS]

'CheckBox
GUI_CHECKBOX_COLOR1 = RGB(140, 140, 140)
GUI_CHECKBOX_COLOR2 = RGB(100, 100, 100)
GUI_CHECKBOX_CHECK_COLOR = RGB(0, 150, 0)
GUI_CHECKBOX_BORDER_COLOR = RGB(64, 64, 64)
Dim Gui_CheckBox_Panel[MAX_CHECKBOXES]
Dim Gui_CheckBox_Exists[MAX_CHECKBOXES]
Dim Gui_CheckBox_X[MAX_CHECKBOXES]
Dim Gui_CheckBox_Y[MAX_CHECKBOXES]
Dim Gui_CheckBox_W[MAX_CHECKBOXES]
Dim Gui_CheckBox_H[MAX_CHECKBOXES]
Dim Gui_CheckBox_Image[MAX_CHECKBOXES,3]
Dim Gui_CheckBox_Current_Image[MAX_CHECKBOXES]
Dim Gui_CheckBox_Value[MAX_CHECKBOXES]

'Label
Dim Gui_Label_Panel[MAX_LABELS]
Dim Gui_Label_Exists[MAX_LABELS]
Dim Gui_Label_X[MAX_LABELS]
Dim Gui_Label_Y[MAX_LABELS]
Dim Gui_Label_W[MAX_LABELS]
Dim Gui_Label_H[MAX_LABELS]
Dim Gui_Label_Image[MAX_LABELS]

'ImageClip
Dim Gui_ImageClip_Panel[MAX_IMAGECLIPS]
Dim Gui_ImageClip_Exists[MAX_IMAGECLIPS]
Dim Gui_ImageClip_X[MAX_IMAGECLIPS]
Dim Gui_ImageClip_Y[MAX_IMAGECLIPS]
Dim Gui_ImageClip_W[MAX_IMAGECLIPS]
Dim Gui_ImageClip_H[MAX_IMAGECLIPS]
Dim Gui_ImageClip_Image[MAX_IMAGECLIPS]
Dim Gui_ImageClip_Source_Image[MAX_IMAGECLIPS]
Dim Gui_ImageClip_Source_X[MAX_IMAGECLIPS]
Dim Gui_ImageClip_Source_Y[MAX_IMAGECLIPS]
Dim Gui_ImageClip_Source_W[MAX_IMAGECLIPS]
Dim Gui_ImageClip_Source_H[MAX_IMAGECLIPS]
Dim Gui_ImageClip_Stretched[MAX_IMAGECLIPS]

'ImageSlide
GUI_IMAGESLIDE_BORDER_COLOR = RGB(80, 80, 80)
GUI_IMAGESLIDE_COLOR = RGB( 128, 128, 128)
GUI_IMAGESLIDE_HIGHLIGHT_COLOR = RGB(255, 0, 0)
Dim Gui_ImageSlide_Panel[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_Exists[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_X[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_Y[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_W[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_H[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_ImageClip[MAX_IMAGESLIDES, MAX_IMAGESLIDE_CLIPS]
Dim Gui_ImageSlide_SelectedClip[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_Count[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_Image[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_ImageClip_W[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_ImageClip_H[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_Offset_X[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_Offset_Y[MAX_IMAGESLIDES]
Dim Gui_ImageSlide_Hover

'Surface
Dim GUI_ACTIVE_SURFACE

GUI_SURFACE_CMD_DRAWIMAGE = 1
GUI_SURFACE_CMD_DRAWIMAGE_EX = 2
GUI_SURFACE_CMD_DRAWIMAGE_ROTATE = 3
GUI_SURFACE_CMD_DRAWIMAGE_ROTATE_EX = 4
GUI_SURFACE_CMD_DRAWIMAGE_ZOOM = 5
GUI_SURFACE_CMD_DRAWIMAGE_ZOOM_EX = 6
GUI_SURFACE_CMD_DRAWIMAGE_BLIT = 7
GUI_SURFACE_CMD_DRAWIMAGE_BLIT_EX = 8
GUI_SURFACE_CMD_DRAWIMAGE_FLIP = 9
GUI_SURFACE_CMD_DRAWIMAGE_FLIP_EX = 10
GUI_SURFACE_CMD_DRAWIMAGE_ROTOZOOM = 11
GUI_SURFACE_CMD_DRAWIMAGE_ROTOZOOM_EX = 12
GUI_SURFACE_CMD_PSET = 13
GUI_SURFACE_CMD_LINE = 14
GUI_SURFACE_CMD_BOX = 15
GUI_SURFACE_CMD_BOXFILL = 16
GUI_SURFACE_CMD_RECT = 17
GUI_SURFACE_CMD_RECTFILL = 18
GUI_SURFACE_CMD_CIRCLE = 19
GUI_SURFACE_CMD_CIRCLEFILL = 20
GUI_SURFACE_CMD_ELLIPSE = 21
GUI_SURFACE_CMD_ELLIPSEFILL = 22
GUI_SURFACE_CMD_CLEAR = 23
GUI_SURFACE_CMD_FLOODFILL = 24
GUI_SURFACE_CMD_SETCLEARCOLOR = 25
GUI_SURFACE_CMD_SETCOLOR = 26

GUI_SURFACE_CLEAR_COLOR = RGB(0, 0, 0)
GUI_SURFACE_BORDER_COLOR = RGB(80, 80, 80)
Dim Gui_Surface_Panel[MAX_SURFACES]
Dim Gui_Surface_Exists[MAX_SURFACES]
Dim Gui_Surface_X[MAX_SURFACES]
Dim Gui_Surface_Y[MAX_SURFACES]
Dim Gui_Surface_W[MAX_SURFACES]
Dim Gui_Surface_H[MAX_SURFACES]
Dim Gui_Surface_Image[MAX_SURFACES]
Dim Gui_Surface_MouseX[MAX_SURFACES]
Dim Gui_Surface_MouseY[MAX_SURFACES]
Dim Gui_Surface_DrawCommand[MAX_SURFACES, 2048, 16]
Dim Gui_Surface_NumCommands[MAX_SURFACES]

Dim gui_current_win

Sub Gui_Init()
	'Initialization Code For Gui System
	For i = 0 to MAX_GUI_ELEMENTS-1
		Gui_Element_Exists[i] = False
		Gui_Element_Parent[i] = i
		Gui_Element_Window[i] = 0
		Gui_Element_Active[i] = False
		Gui_Element_Index[i] = 0
		Gui_Element_Type[i] = 0
	Next
	For i = 0 to MAX_WINDOWS-1
		For j = 0 to MAX_PANELS-1
			Gui_Window_Panel_Exists[i,J] = False
		Next
	Next
	For i = 0 to MAX_PANELS-1
		Gui_Panel_Exists[i] = False
		Gui_Panel_isActive[i] = False
		For j = 0 to MAX_PANEL_OBJECTS-1
			Gui_Panel_Object_Exists[i, j] = False
		Next
	Next
	
	Gui_Button_Exists[0] = True 'This is a simple fix to a bug with the first button created
	
	For i = 1 to MAX_BUTTONS-1
		Gui_Button_Exists[i] = False
		Gui_Button_Current_Image[i] = 0
	Next
	For i = 0 to MAX_DROPDOWNS-1
		Gui_DropDown_Exists[i] = False
	Next
	For i = 0 to MAX_LISTBOXES-1
		Gui_ListBox_Exists[i] = False
	Next
	For i = 0 to MAX_TEXTFIELDS-1
		Gui_TextField_Exists[i] = False
	Next
	If OS = "WINDOWS" Then
		LoadFont(GUI_FONT, GUI_DIR+"\\font\\FreeMono.TTF", 12)
	Else
		LoadFont(GUI_FONT, GUI_DIR+"/font/FreeMono.ttf", 12)
	End If
	
	GetTextSize(GUI_FONT, "A", GUI_FONT_W, GUI_FONT_H)
	GUI_DROPDOWN_MIN_W = GUI_FONT_W + 4
	GUI_DROPDOWN_MIN_H = GUI_FONT_H + 4
	GUI_LISTBOX_MIN_W = GUI_FONT_W + 4
	GUI_LISTBOX_MIN_H = GUI_FONT_H + 4
	GUI_TEXTFIELD_MIN_W = GUI_FONT_W + 4
	GUI_TEXTFIELD_MIN_H = GUI_FONT_H + 4
	
	GUI_PAGEUP_IMAGE = 0
	GUI_SCROLLUP_IMAGE = 1
	GUI_SCROLLDOWN_IMAGE = 2
	GUI_PAGEDOWN_IMAGE = 3
End Sub

Function Gui_GetFreeID()
	For i = 0 to MAX_GUI_ELEMENTS-1
		If Not Gui_Element_Exists[i] Then
			Return i
		End If
	Next
	Return -1
End Function

Sub AddWindowObject(obj_type, obj_id)
	n = Gui_Window_NumObjects[gui_current_win]
	Gui_Window_Objects[gui_current_win, n, 0] = obj_type
	Gui_Window_Objects[gui_current_win, n, 1] = obj_id
	Gui_Window_NumObjects[gui_current_win] = n + 1
End Sub

Sub ClearWindowObjects(win)
	If Gui_Window_NumObjects[win] <= 0 Then
		Gui_Window_NumObjects[win] = 0
		Return
	end If
	
	For i = 0 To Gui_Window_NumObjects[win]-1
		obj_type = Gui_Window_Objects[win, i, 0]
		obj_id = Gui_Window_Objects[win, i, 1]
		Select Case obj_type
		Case WINDOW_OBJECT_TYPE_PANEL
			If ImageExists(Gui_Panel_Image[obj_id]) Then
				DeleteImage(Gui_Panel_Image[obj_id])
			End If
			Gui_Panel_Exists[obj_id] = False
		Case WINDOW_OBJECT_TYPE_BUTTON
			If ImageExists(Gui_Button_Image[obj_id,0]) Then
				DeleteImage(Gui_Button_Image[obj_id,0])
			End If
			If ImageExists(Gui_Button_Image[obj_id,1]) Then
				DeleteImage(Gui_Button_Image[obj_id,1])
			End If
			Gui_Button_Current_Image[obj_id] = 0
			Gui_Button_Panel[obj_id] = -1
			Gui_Button_Exists[obj_id] = False
		Case WINDOW_OBJECT_TYPE_DROPDOWN
			If ImageExists(Gui_DropDown_Image[obj_id,0]) Then
				DeleteImage(Gui_DropDown_Image[obj_id,0])
			End If
			If ImageExists(Gui_DropDown_Image[obj_id,1]) Then
				DeleteImage(Gui_DropDown_Image[obj_id,1])
			End If
			If ImageExists(Gui_DropDown_Image[obj_id,2]) Then
				DeleteImage(Gui_DropDown_Image[obj_id,2])
			End If
			Gui_DropDown_Current_Image[obj_id] = 0
			Gui_DropDown_Panel[obj_id] = -1
			Gui_DropDown_Exists[obj_id] = False
		Case WINDOW_OBJECT_TYPE_LISTBOX
			If ImageExists(Gui_ListBox_Image[obj_id]) Then
				DeleteImage(Gui_ListBox_Image[obj_id])
			End If
			For i = 0 to 7
				If ImageExists(Gui_ListBox_ScrollBar_Image[obj_id, i]) Then
					DeleteImage(Gui_ListBox_ScrollBar_Image[obj_id, i])
				End If
			Next
			Gui_DropDown_Current_Image[obj_id] = 0
			Gui_DropDown_Panel[obj_id] = -1
			Gui_DropDown_Exists[obj_id] = False
		Case WINDOW_OBJECT_TYPE_TEXTFIELD
			If ImageExists(Gui_TextField_Image[obj_id]) Then
				DeleteImage(Gui_TextField_Image[obj_id])
			End If
			Gui_TextField_Panel[obj_id] = -1
			Gui_TextField_Exists[obj_id] = False
		Case WINDOW_OBJECT_TYPE_CHECKBOX
			If ImageExists(Gui_CheckBox_Image[obj_id,0]) Then
				DeleteImage(Gui_CheckBox_Image[obj_id,0])
			End If
			If ImageExists(Gui_CheckBox_Image[obj_id,1]) Then
				DeleteImage(Gui_CheckBox_Image[obj_id,1])
			End If
			If ImageExists(Gui_CheckBox_Image[obj_id,2]) Then
				DeleteImage(Gui_CheckBox_Image[obj_id,2])
			End If
			Gui_CheckBox_Current_Image[obj_id] = 0
			Gui_CheckBox_Panel[obj_id] = -1
			Gui_CheckBox_Exists[obj_id] = False
		Case WINDOW_OBJECT_TYPE_IMAGECLIP
			If ImageExists(Gui_ImageClip_Image[obj_id]) Then
				DeleteImage(Gui_ImageClip_Image[obj_id])
			End If
			Gui_ImageClip_Panel[obj_id] = -1
			Gui_ImageClip_Exists[obj_id] = False
		Case WINDOW_OBJECT_TYPE_IMAGESLIDE
			If ImageExists(Gui_ImageSlide_Image[obj_id]) Then
				DeleteImage(Gui_ImageSlide_Image[obj_id])
			End If
			Gui_ImageSlide_Panel[obj_id] = -1
			Gui_ImageSlide_Exists[obj_id] = False
		Case WINDOW_OBJECT_TYPE_LABEL
			If ImageExists(Gui_Label_Image[obj_id]) Then
				DeleteImage(Gui_Label_Image[obj_id])
			End If
			Gui_Label_Panel[obj_id] = -1
			Gui_Label_Exists[obj_id] = False
		Case WINDOW_OBJECT_TYPE_SURFACE
			If ImageExists(Gui_Surface_Image[obj_id]) Then
				DeleteImage(Gui_Surface_Image[obj_id])
			End If
			Gui_Surface_Panel[obj_id] = -1
			Gui_Surface_Exists[obj_id] = False
		Case WINDOW_OBJECT_TYPE_TABGROUP
			For i = 0 to MAX_TABS-1
				If ImageExists(Gui_TabGroup_Tab_Image[obj_id,i,0]) Then
					DeleteImage(Gui_TabGroup_Tab_Image[obj_id,i,0])
				End If
				If ImageExists(Gui_TabGroup_Tab_Image[obj_id,i,1]) Then
					DeleteImage(Gui_TabGroup_Tab_Image[obj_id,i,1])
				End If
			Next
			Gui_TabGroup_ActiveTab[obj_id] = 0
			Gui_TabGroup_Exists[obj_id] = False
			Gui_TabGroup_TabCount[obj_id] = 0
		End Select
	Next
End Sub

Function Gui_WindowOpen(title$, x, y, w, h)
	visible = true
	fullscreen = false
	resizable = true
	borderless = false
	highDPI = false
	
	win_mode = WindowMode(visible, fullscreen, resizable, borderless, highDPI)

	vsync = true
	For i = 0 to MAX_WINDOWS-1
		If Not WindowExists(i) Then
			current_win = gui_current_win
			WindowOpen(i, title$, x, y, w, h, win_mode, vsync)
			Window(i)
			Cls
			CanvasOpen(GUI_TMP_CANVAS, w, h, 0, 0, w, h, 0)
			CanvasOpen(GUI_WIN_CANVAS, w, h, 0, 0, w, h, 1)
			SetCanvasVisible(GUI_TMP_CANVAS, False)
			If current_win >= 0 And current_win < MAX_WINDOWS Then
				Window(current_win)
			End If
			EVENT_TYPE = 0
			EVENT_ID = 0
			Return i
		End If
	Next
	Return -1
End Function

Sub Gui_SetWindowActive(win_id)
	Window(win_id)
	gui_current_win = win_id
	EVENT_TYPE = 0
End Sub

Sub RemovePanelObjects(panel_index)
	'panel_index = Gui_Element_Index[panel]
	
	For i = 0 to MAX_PANEL_OBJECTS-1
		If Gui_Panel_Object_Exists[panel_index, i] Then
			obj = Gui_Panel_Object_ID[panel_index, i] 
			obj_index = Gui_Element_Index[obj]
			
			Gui_Panel_Object_Exists[panel_index, i] = False
			Gui_Element_Exists[obj] = False

		End If
	Next
	
End Sub

Sub Gui_WindowClose(win_id)
	n = gui_current_win
	
	Gui_SetWindowActive(win_id)
	ClearWindowObjects(win_id)
	
	For i = 0 to 7
		CanvasClose(i)
	Next
	
	Gui_Window_Exists[win_id] = False
	For i = 0 to MAX_PANELS-1
		Gui_Window_Panel_Exists[win_id, i] = False
	Next
	
	For i = 0 to MAX_GUI_ELEMENTS-1
		If Gui_Element_Window[i] = win_id Then
			Gui_Element_Active[i] = False
			Gui_Element_Exists[i] = False
			panel_id = Gui_Element_Index[i]
			RemovePanelObjects(panel_id)
		End If
	Next
	
	Gui_Window_NumObjects[win_id] = 0
	
	Gui_SetWindowActive(n)
	
	If gui_current_win = win_id Then
		For i = 0 to MAX_WINDOWS-1
			If WindowExists(i) And i <> win_id Then
				Gui_SetWindowActive(i)
				Exit For
			End If
		Next
	End If
	WindowClose(win_id)
End Sub

Function Gui_GetFreeImage()
	For i = 20 to MAX_IMAGES-1
		If Not ImageExists(i) Then
			Return i
		End If
	Next
	Return -1
End Function

Function Gui_LoadImage(img_file$)
	img = Gui_GetFreeImage
	If img >= 0 Then
		LoadImage(img, img_file$)
		If ImageExists(img) Then
			Return img
		End If
	End If
	Return -1
End Function

Function Gui_CreateEmptyImage(w, h)
	Dim buf[w*h]
	img = Gui_GetFreeImage
	ImageFromBuffer(img, w, h, buf)
	Return img
End Function

Sub Gui_SetPanelActive(panel, flag)
	panel_index = Gui_Element_Index[panel]
	Gui_Element_Active[panel] = flag
	For i = 0 to MAX_PANEL_OBJECTS-1
		If Gui_Panel_Object_Exists[panel_index, i] Then
			Gui_Element_Active[ Gui_Panel_Object_ID[panel_index, i] ] = flag
		End If
	Next
End Sub

Sub Gui_SetTabGroupActive(id, flag)
	tab_index = Gui_Element_Index[id]
	Gui_Element_Active[id] = flag
	
	If flag = False Then
		For tab = 0 to Gui_TabGroup_TabCount[tab_index]-1
			For i = 0 to MAX_TAB_OBJECTS-1
				If Gui_TabGroup_Tab_Object_Exists[tab_index, tab, i] Then
					Gui_Element_Active[ Gui_TabGroup_Tab_Object_ID[tab_index, tab, i] ] = False
				End If
			Next
		Next
	Else
		tab = Gui_TabGroup_ActiveTab[tab_index]
		For i = 0 to MAX_TAB_OBJECTS-1
			If Gui_TabGroup_Tab_Object_Exists[tab_index, tab, i] Then
				Gui_Element_Active[ Gui_TabGroup_Tab_Object_ID[tab_index, tab, i] ] = True
			End If
		Next
	End If
End Sub

Function Gui_Window_AddTabGroup(win, tab_group, x, y)
	tab_index = Gui_Element_Index[tab_group]
	For i = 0 to MAX_PANELS-1
		If Not Gui_Window_Panel_Exists[win, i] Then
			Gui_Window_Panel_Exists[win, i] = True
			Gui_Window_Panel_Type[win, i] = GUI_TYPE_TAB
			Gui_Window_Panel_ID[win, i] = tab_group
			
			Gui_TabGroup_X[tab_index] = x
			Gui_TabGroup_Y[tab_index] = y
			Gui_Element_Window[tab_group] = win
			Return True
		End If
	Next
	Return False
End Function

Function Gui_CreateTabGroup(w, h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	For i = 0 to MAX_TAB_GROUPS-1
		If Not Gui_TabGroup_Exists[i] Then
			Gui_TabGroup_Exists[i] = True
			Gui_TabGroup_W[i] = w
			Gui_TabGroup_H[i] = h
			Gui_TabGroup_TabCount[i] = 0
			
			Gui_Element_Type[id] = GUI_TYPE_TAB
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Gui_Element_Parent[id] = id
			Return id
		End If
	Next
	Return -1
End Function

Function Gui_TabGroup_Tab_AddObject(tab_group, tab_num, obj_id)
	tab_index = Gui_Element_Index[tab_group]
	obj_type = Gui_Element_Type[obj_id]
	obj_index = Gui_Element_Index[obj_id]
	
	For i = 0 to MAX_TAB_OBJECTS-1
		If Not Gui_TabGroup_Tab_Object_Exists[tab_index, tab_num, i] Then
			Gui_TabGroup_Tab_Object_Exists[tab_index, tab_num, i] = True
			Gui_TabGroup_Tab_Object_ID[tab_index, tab_num, i] = obj_id
			Gui_TabGroup_Tab_Object_Type[tab_index, tab_num, i] = obj_type
			Gui_Element_Parent[obj_id] = tab_group
			If tab_num = Gui_TabGroup_ActiveTab[tab_index] Then
				Gui_Element_Active[obj_id] = True
			Else
				Gui_Element_Active[obj_id] = False
			End If
			Return i
		End If
	Next
	Return -1
End Function

Function Gui_TabGroup_AddTab(tab_id, txt$)
	tab_group = Gui_Element_Index[tab_id]
	current_tab = Gui_TabGroup_TabCount[tab_group]
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	If Gui_TabGroup_TabCount[tab_group]+1 < MAX_TABS Then
		i = Gui_TabGroup_TabCount[tab_group]
		Gui_TabGroup_TabCount[tab_group] = Gui_TabGroup_TabCount[tab_group] + 1
		Gui_TabGroup_Tab_Exists[tab_group, i] = True
		Gui_TabGroup_Tab_Title$[tab_group, i] = txt$
		
		dim buf[4]
		
		Gui_TabGroup_Tab_Image[tab_group, i, 0] = Gui_GetFreeImage
		ImageFromBuffer(Gui_TabGroup_Tab_Image[tab_group, i, 0], 2, 2, buf)
		
		Gui_TabGroup_Tab_Image[tab_group, i, 1] = Gui_GetFreeImage
		ImageFromBuffer(Gui_TabGroup_Tab_Image[tab_group, i, 1], 2, 2, buf)
	Else
		Return -1
	End If
	tab_w = Int(Gui_TabGroup_W[tab_group] / Gui_TabGroup_TabCount[tab_group])
	tab_h = Gui_TabGroup_H[tab_group]
	margin_w = tab_w/10
	margin_h = tab_h/10
	txt_w = 0
	txt_h = 0
	
	For tab_num = 0 to Gui_TabGroup_TabCount[tab_group]-1
		GetTextSize(GUI_FONT, Gui_TabGroup_Tab_Title$[tab_group, tab_num], txt_w, txt_h)
		SetColor(GUI_TAB_COLOR1)
		RectFill(0, 0, tab_w, tab_h)
		SetColor(GUI_FONT_COLOR)
		Font(GUI_FONT)
		DrawText(Gui_TabGroup_Tab_Title$[tab_group, tab_num], margin_w/2, margin_h/2)
		SetColor(GUI_TAB_BORDER_COLOR)
		Rect(0, 0, tab_w, tab_h)
		tab_image = Gui_TabGroup_Tab_Image[tab_group, tab_num, 0]
		If ImageExists(tab_image) Then
			DeleteImage(tab_image)
		End If
		CanvasClip(tab_image, 0, 0, tab_w, tab_h, 1)
		
		SetColor(GUI_TAB_COLOR2)
		RectFill(0, 0, tab_w, tab_h)
		SetColor(GUI_FONT_COLOR)
		Font(GUI_FONT)
		DrawText(Gui_TabGroup_Tab_Title$[tab_group, tab_num], margin_w/2, margin_h/2)
		SetColor(GUI_TAB_BORDER_COLOR)
		Rect(0, 0, tab_w, tab_h)
		tab_image = Gui_TabGroup_Tab_Image[tab_group, tab_num, 1]
		If ImageExists(tab_image) Then
			DeleteImage(tab_image)
		End If
		CanvasClip(tab_image, 0, 0, tab_w, tab_h, 1)
	Next
	Return current_tab
End Function

Function Gui_Window_AddPanel(win, panel, x, y)
	panel_index = Gui_Element_Index[panel]
	For i = 0 to MAX_PANELS-1
		If Not Gui_Window_Panel_Exists[win, i] Then
			Gui_Window_Panel_Exists[win, i] = True
			Gui_Window_Panel_Type[win, i] = GUI_TYPE_PANEL
			Gui_Window_Panel_ID[win, i] = panel
			Gui_Panel_X[panel_index] = x
			Gui_Panel_Y[panel_index] = y
			Gui_Element_Window[panel] = win
			Return True
		End If
	Next
	Return False
End Function

Function Gui_CreatePanel(w, h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	For i = 0 to MAX_PANELS-1
		If Not Gui_Panel_Exists[i] Then
			Gui_Panel_Exists[i] = True
			Gui_Panel_W[i] = w
			Gui_Panel_H[i] = h
			Gui_Panel_Image[i] = Gui_GetFreeImage
			'Dim buf[w*h]
			'For b = 0 to (w*h)-1
			'	buf[b] = RGB(128,128,128)
			'Next
			'ImageFromBuffer(Gui_Panel_Image[i], w, h, buf)
			Canvas(GUI_TMP_CANVAS)
			SetColor(RGB(128,128,128))
			RectFill(0, 0, w, h)
			CanvasClip(Gui_Panel_Image[i], 0, 0, w, h, 1)
			Gui_Element_Type[id] = GUI_TYPE_PANEL
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Gui_Element_Parent[id] = id
			
			AddWindowObject(WINDOW_OBJECT_TYPE_PANEL, id)
			Return id
		End If
	Next
	Return -1
End Function

Function Gui_Panel_AddObject(panel, obj, x, y)
	panel_index = Gui_Element_Index[panel]
	obj_index = Gui_Element_Index[obj]
	obj_type = Gui_Element_Type[obj]
	For i = 0 to MAX_PANEL_OBJECTS-1
		If Not Gui_Panel_Object_Exists[panel_index, i] Then
			Gui_Panel_Object_Exists[panel_index, i] = True
			Gui_Panel_Object_Type[panel_index, i] = obj_type
			Gui_Panel_Object_ID[panel_index, i] = obj
			Gui_Element_Parent[obj] = panel
			Select Case obj_type
			Case GUI_TYPE_BUTTON
				Gui_Button_X[obj_index] = x
				Gui_Button_Y[obj_index] = y
				Gui_Button_Panel[obj_index] = panel
			Case GUI_TYPE_DROPDOWN
				Gui_DropDown_X[obj_index] = x
				Gui_DropDown_Y[obj_index] = y
				Gui_DropDown_Panel[obj_index] = panel
			Case GUI_TYPE_LISTBOX
				Gui_ListBox_X[obj_index] = x
				Gui_ListBox_Y[obj_index] = y
				Gui_ListBox_Panel[obj_index] = panel
			Case GUI_TYPE_TEXTFIELD
				Gui_TextField_X[obj_index] = x
				Gui_TextField_Y[obj_index] = y
				Gui_TextField_Panel[obj_index] = panel
			Case GUI_TYPE_CHECKBOX
				Gui_CheckBox_X[obj_index] = x
				Gui_CheckBox_Y[obj_index] = y
				Gui_CheckBox_Panel[obj_index] = panel
			Case GUI_TYPE_LABEL
				Gui_Label_X[obj_index] = x
				Gui_Label_Y[obj_index] = y
				Gui_Label_Panel[obj_index] = panel
			Case GUI_TYPE_IMAGECLIP
				Gui_ImageClip_X[obj_index] = x
				Gui_ImageClip_Y[obj_index] = y
				Gui_ImageClip_Panel[obj_index] = panel
			Case GUI_TYPE_IMAGESLIDE
				Gui_ImageSlide_X[obj_index] = x
				Gui_ImageSlide_Y[obj_index] = y
				Gui_ImageSlide_Panel[obj_index] = panel
			Case GUI_TYPE_SURFACE
				Gui_Surface_X[obj_index] = x
				Gui_Surface_Y[obj_index] = y
				Gui_Surface_Panel[obj_index] = panel
			End Select
			Return True
		End If
	Next
	Return False
End Function

Function Gui_CreateDropDown(w, h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	If w < GUI_DROPDOWN_MIN_W Then
		w = GUI_DROPDOWN_MIN_W
	End If
	If h < GUI_DROPDOWN_MIN_H Then
		h = GUI_DROPDOWN_MIN_H
	End If
	For i = 0 to MAX_DROPDOWNS-1
		If Not Gui_DropDown_Exists[i] Then
			Gui_DropDown_Exists[i] = True
			Gui_DropDown_W[i] = w
			Gui_DropDown_H[i] = h
			Gui_DropDown_Count[i] = 0
			
			Canvas(GUI_TMP_CANVAS)
			ClearCanvas
			
			Gui_DropDown_Image[i,0] = Gui_GetFreeImage
			SetColor(GUI_DROPDOWN_COLOR1)
			RectFill(0, 0, w, h)
			SetColor(GUI_DROPDOWN_BORDER_COLOR)
			Rect(0, 0, w, h)
			arrow_x = w - GUI_DROPDOWN_MIN_W
			arrow_y = 0
			arrow_w = GUI_DROPDOWN_MIN_W
			arrow_h = h
			Rect(arrow_x, arrow_y, arrow_w, arrow_h)
			SetColor(RGB(0,0,0))
			DrawText("V", arrow_x + arrow_w/2 - GUI_FONT_W/2, arrow_y + arrow_h/2 - GUI_FONT_H/2)
			CanvasClip(Gui_DropDown_Image[i,0], 0, 0, w, h, 1)
			
			ClearCanvas
			Gui_DropDown_Image[i,1] = Gui_GetFreeImage
			SetColor(GUI_DROPDOWN_COLOR2)
			RectFill(0, 0, w, h)
			SetColor(GUI_DROPDOWN_BORDER_COLOR)
			Rect(0, 0, w, h)
			arrow_x = w - GUI_DROPDOWN_MIN_W
			arrow_y = 0
			arrow_w = GUI_DROPDOWN_MIN_W
			arrow_h = h
			Rect(arrow_x, arrow_y, arrow_w, arrow_h)
			SetColor(RGB(0,0,0))
			DrawText("V", arrow_x + arrow_w/2 - GUI_FONT_W/2, arrow_y + arrow_h/2 - GUI_FONT_H/2)
			CanvasClip(Gui_DropDown_Image[i,1], 0, 0, w, h, 1)
			
			Dim buf[w*h]
			Gui_DropDown_Image[i,2] = Gui_GetFreeImage
			ImageFromBuffer(Gui_DropDown_Image[i,2], w, h, buf)
			Gui_Element_Type[id] = GUI_TYPE_DROPDOWN
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Return id
		End If
	Next
	Return -1
End Function

Sub RedrawDropDownSelected(d_index)
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	
	dim txt_w
	dim txt_h
	txt$ = Gui_DropDown_Value$[d_index, Gui_DropDown_Selected_Item[d_index]]
	
	If txt$ = "" Then
		txt$ = " "
	End If
	
	GetTextSize(GUI_FONT, txt, txt_w, txt_h)
	
	selection_w = Gui_DropDown_W[d_index] - GUI_DROPDOWN_MIN_W
	selection_h = Gui_DropDown_H[d_index]
			
	margin_w = selection_w/10
	margin_h = selection_h/10
			
	If txt_w > (selection_w - (margin_w*2) ) Then
		txt_w = selection_w - (margin_w*2)
	End If
	
	If txt_h > (selection_h - (margin_h*2) ) Then
		txt_h = selection_h - (margin_h*2)
	End If
	
	txt_img = Gui_GetFreeImage
	
	
	SetColor(GUI_DROPDOWN_COLOR1)
	RectFill(0, 0, selection_w, selection_h)
	
	SetColor(GUI_FONT_COLOR)
	DrawText(txt$, 0, 0)
	CanvasClip(txt_img, 0, 0, txt_w, txt_h, 1)
	
	'SetColor(GUI_BUTTON_COLOR1)
	'RectFill(0, 0, w, h)
	'DrawImage(txt_img, margin_w, margin_h)
	
	ClearCanvas
	
	w = Gui_DropDown_W[d_index]
	h = Gui_DropDown_H[d_index]
	
	SetColor(GUI_DROPDOWN_COLOR1)
	RectFill(0, 0, w, h)
	SetColor(GUI_DROPDOWN_BORDER_COLOR)
	Rect(0, 0, w, h)
	arrow_x = w - GUI_DROPDOWN_MIN_W
	arrow_y = 0
	arrow_w = GUI_DROPDOWN_MIN_W
	arrow_h = h
	Rect(arrow_x, arrow_y, arrow_w, arrow_h)
	SetColor(RGB(0,0,0))
	DrawImage(txt_img, margin_w, margin_h)
	DrawText("V", arrow_x + arrow_w/2 - GUI_FONT_W/2, arrow_y + arrow_h/2 - GUI_FONT_H/2)
	If ImageExists(Gui_DropDown_Image[d_index, 0]) Then
		DeleteImage(Gui_DropDown_Image[d_index, 0])
	End If
	CanvasClip(Gui_DropDown_Image[d_index,0], 0, 0, w, h, 1)
			
	ClearCanvas
	
	SetColor(GUI_DROPDOWN_COLOR2)
	RectFill(0, 0, w, h)
	SetColor(GUI_DROPDOWN_BORDER_COLOR)
	Rect(0, 0, w, h)
	arrow_x = w - GUI_DROPDOWN_MIN_W
	arrow_y = 0
	arrow_w = GUI_DROPDOWN_MIN_W
	arrow_h = h
	Rect(arrow_x, arrow_y, arrow_w, arrow_h)
	SetColor(RGB(0,0,0))
	DrawImage(txt_img, margin_w, margin_h)
	DrawText("V", arrow_x + arrow_w/2 - GUI_FONT_W/2, arrow_y + arrow_h/2 - GUI_FONT_H/2)
	If ImageExists(Gui_DropDown_Image[d_index, 1]) Then
		DeleteImage(Gui_DropDown_Image[d_index, 1])
	End If
	CanvasClip(Gui_DropDown_Image[d_index,1], 0, 0, w, h, 1)
	DeleteImage(txt_img)
End Sub

Function Gui_DropDown_AddItem(d_id, value$)
	d_index = Gui_Element_Index[d_id]
	If Gui_DropDown_Count[d_index]+1 < MAX_DROPDOWN_VALUES Then
		num = Gui_DropDown_Count[d_index]
		Gui_DropDown_Value$[d_index, num] = value$
		Gui_DropDown_Count[d_index] = Gui_DropDown_Count[d_index] + 1
		'Need to draw dropdown image here
		Canvas(GUI_TMP_CANVAS)
		ClearCanvas
		SetColor(GUI_DROPDOWN_COLOR1)
		RectFill(0, 0, Gui_DropDown_W[d_index], Gui_DropDown_Count[d_index] * GUI_FONT_H)
		SetColor(GUI_FONT_COLOR)
		For i = 0 to Gui_DropDown_Count[d_index]-1
			DrawText(Gui_DropDown_Value$[d_index, i], 0, i * GUI_FONT_H)
		Next
		If ImageExists(Gui_DropDown_Image[d_index, 2]) Then
			DeleteImage(Gui_DropDown_Image[d_index, 2])
		End If
		CanvasClip(Gui_DropDown_Image[d_index, 2], 0, 0, Gui_DropDown_W[d_index], Gui_DropDown_Count[d_index] * GUI_FONT_H, 1)
		If Gui_DropDown_Count[d_index] = 1 Then
			Gui_DropDown_Selected_Item[d_index] = 0
			RedrawDropDownSelected(d_index)
		End If
		Return num
	End If
	Return -1
End Function

Sub RedrawDropDown(d_index)
	num = Gui_DropDown_Count[d_index]
	
	'Need to draw dropdown image here
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	SetColor(GUI_DROPDOWN_COLOR1)
	RectFill(0, 0, Gui_DropDown_W[d_index], Gui_DropDown_Count[d_index] * GUI_FONT_H)
	SetColor(GUI_FONT_COLOR)
	If Gui_DropDown_Count[d_index] > 0 Then
		For i = 0 to Gui_DropDown_Count[d_index]-1
			DrawText(Gui_DropDown_Value$[d_index, i], 0, i * GUI_FONT_H)
		Next
	End If
	If ImageExists(Gui_DropDown_Image[d_index, 2]) Then
		DeleteImage(Gui_DropDown_Image[d_index, 2])
	End If
	CanvasClip(Gui_DropDown_Image[d_index, 2], 0, 0, Gui_DropDown_W[d_index], Gui_DropDown_Count[d_index] * GUI_FONT_H, 1)
	If Gui_DropDown_Count[d_index] <= 1 Then
		Gui_DropDown_Selected_Item[d_index] = 0
		RedrawDropDownSelected(d_index)
	End If
End Sub

Function Gui_DropDown_RemoveItem(d_id, item_num)
	d_index = Gui_Element_Index[d_id]
	If item_num < Gui_DropDown_Count[d_index] Then
		For i = item_num to Gui_DropDown_Count[d_index]-1
			Gui_DropDown_Value$[d_index, i] = Gui_DropDown_Value$[d_index, i+1]
		Next
		Gui_DropDown_Count[d_index] = Gui_DropDown_Count[d_index] - 1
	End If
End Function

Function Gui_DropDown_Clear(d_id)
	d_index = Gui_Element_Index[d_id]
	Gui_DropDown_Count[d_index] = 0
	Gui_DropDown_Selected_Item[d_index] = 0
	RedrawDropDown(d_index)
End Function

Function Gui_DropDown_Update(d_id)
	d_index = Gui_Element_Index[d_id]
	RedrawDropDown(d_index)
End Function

Function Gui_CreateButton(txt$, w, h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	For i = 0 to MAX_BUTTONS-1
		If Not Gui_Button_Exists[i] Then
			Gui_Button_Exists[i] = True
			Gui_Button_W[i] = w
			Gui_Button_H[i] = h
			
			current_canvas = ActiveCanvas
			Canvas(GUI_TMP_CANVAS)
			ClearCanvas
			
			dim txt_w
			dim txt_h
			GetTextSize(GUI_FONT, txt, txt_w, txt_h)
			
			margin_w = w/10
			margin_h = h/10
			
			If txt_w > (w - (margin_w*2) ) Then
				txt_w = w - (margin_w*2)
			End If
			
			If txt_h > (h - (margin_h*2) ) Then
				txt_h = h - (margin_h*2)
			End If
			
			img = Gui_GetFreeImage
			SetColor(GUI_BUTTON_COLOR1)
			RectFill(0, 0, w, h)
			SetColor(GUI_FONT_COLOR)
			DrawText(txt$, 0, 0)
			CanvasClip(img, 0, 0, txt_w, txt_h, 1)
			SetColor(GUI_BUTTON_COLOR1)
			RectFill(0, 0, w, h)
			DrawImage(img, margin_w, margin_h)
			DeleteImage(img)
			CanvasClip(img, 0, 0, w, h, 1)
			Gui_Button_Image[i, 0] = img
			
			img = Gui_GetFreeImage
			SetColor(GUI_BUTTON_COLOR2)
			RectFill(0, 0, w, h)
			SetColor(GUI_FONT_COLOR)
			DrawText(txt$, 0, 0)
			CanvasClip(img, 0, 0, txt_w, txt_h, 1)
			SetColor(GUI_BUTTON_COLOR2)
			RectFill(0, 0, w, h)
			DrawImage(img, margin_w, margin_h)
			DeleteImage(img)
			CanvasClip(img, 0, 0, w, h, 1)
			Gui_Button_Image[i, 1] = img
			
			Gui_Element_Type[id] = GUI_TYPE_BUTTON
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			
			AddWindowObject(WINDOW_OBJECT_TYPE_BUTTON, id)
			Return id
		End If
	Next
	Return -1
End Function

Function Gui_CreateCheckBox(w, h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	For i = 0 to MAX_CHECKBOXES-1
		If Not Gui_CheckBox_Exists[i] Then
			Gui_CheckBox_Exists[i] = True
			Gui_CheckBox_W[i] = w
			Gui_CheckBox_H[i] = h
			Gui_CheckBox_Current_Image[i] = 0
			Gui_CheckBox_Value[i] = 0
			
			Canvas(GUI_TMP_CANVAS)
			
			img = Gui_GetFreeImage
			SetColor(GUI_CHECKBOX_COLOR1)
			RectFill(0, 0, w, h)
			SetColor(GUI_CHECKBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(img, 0, 0, w, h, 1)
			Gui_CheckBox_Image[i, 0] = img
			
			img = Gui_GetFreeImage
			SetColor(GUI_CHECKBOX_COLOR2)
			RectFill(0, 0, w, h)
			SetColor(GUI_CHECKBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(img, 0, 0, w, h, 1)
			Gui_CheckBox_Image[i, 1] = img
			
			img = Gui_GetFreeImage
			SetColor(GUI_CHECKBOX_CHECK_COLOR)
			RectFill(0, 0, w, h)
			SetColor(GUI_CHECKBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(img, 0, 0, w, h, 1)
			Gui_CheckBox_Image[i, 2] = img
			
			Gui_Element_Type[id] = GUI_TYPE_CHECKBOX
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Return id
		End If
	Next
	Return -1
End Function

Function Gui_CreateLabel(txt$, w, h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	For i = 0 to MAX_LABELS-1
		If Not Gui_Label_Exists[i] Then
			Gui_Label_Exists[i] = True
			Gui_Label_W[i] = w
			Gui_Label_H[i] = h
			
			Canvas(GUI_TMP_CANVAS)
			ClearCanvas
			
			img = Gui_GetFreeImage
			SetColor(PANEL_BKG_VALUE)
			RectFill(0, 0, w, h)
			SetColor(GUI_FONT_COLOR)
			DrawText(txt$, 0, 0)
			CanvasClip(img, 0, 0, w, h, 1)
			
			Gui_Label_Image[i] = img
			
			Gui_Element_Type[id] = GUI_TYPE_LABEL
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Return id
		End If
	Next
	Return -1
End Function

Sub RedrawImageClip(img_clip_index)
	i = img_clip_index
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	SetColor(rgb(0,0,0))
	RectFill(0, 0, Gui_ImageClip_W[i], Gui_ImageClip_H[i])
	If ImageExists(Gui_ImageClip_Source_Image[i]) Then
		DrawImage_Blit_Ex(Gui_ImageClip_Source_Image[i], 0, 0, Gui_ImageClip_W[i], Gui_ImageClip_H[i], Gui_ImageClip_Source_X[i], Gui_ImageClip_Source_Y[i], Gui_ImageClip_Source_W[i], Gui_ImageClip_Source_H[i])
	End If
	If ImageExists(Gui_ImageClip_Image[i]) Then
		DeleteImage(Gui_ImageClip_Image[i])
	End If
	CanvasClip(Gui_ImageClip_Image[i], 0, 0, Gui_ImageClip_W[i], Gui_ImageClip_H[i], 1)
End Sub

Function Gui_CreateImageClip(img_slot, w, h, src_w, src_h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	For i = 0 to MAX_IMAGECLIPS-1
		If Not Gui_ImageClip_Exists[i] Then
			Gui_ImageClip_Exists[i] = True
			Gui_ImageClip_W[i] = w
			Gui_ImageClip_H[i] = h
			Gui_ImageClip_Source_Image[i] = img_slot
			Gui_ImageClip_Source_X[i] = 0
			Gui_ImageClip_Source_Y[i] = 0
			Gui_ImageClip_Source_W[i] = src_w
			Gui_ImageClip_Source_H[i] = src_h
			Gui_ImageClip_Image[i] = Gui_GetFreeImage
			
			RedrawImageClip(i)
			
			Gui_Element_Type[id] = GUI_TYPE_IMAGECLIP
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Return id
		End If
	Next
	Return -1
End Function

Function Gui_ImageClip_Clear(clip_id)
	i = Gui_Element_Index[clip_id]
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	SetColor(rgb(0,0,0))
	RectFill(0, 0, Gui_ImageClip_W[i], Gui_ImageClip_H[i])
	If ImageExists(Gui_ImageClip_Image[i]) Then
		DeleteImage(Gui_ImageClip_Image[i])
	End If
	CanvasClip(Gui_ImageClip_Image[i], 0, 0, Gui_ImageClip_W[i], Gui_ImageClip_H[i], 1)
End Function

Function Gui_ImageClip_SetSource(clip_id, src_img)
	clip_index = Gui_Element_Index[clip_id]
	Gui_ImageClip_Source_Image[clip_index] = src_img
End Function

Function Gui_ImageClip_SetSourceSize(clip_id, src_w, src_h)
	clip_index = Gui_Element_Index[clip_id]
	Gui_ImageClip_Source_W[clip_index] = src_w
	Gui_ImageClip_Source_H[clip_index] = src_h
End Function

Function Gui_ImageClip_SetOffset(clip_id, x, y)
	clip_index = Gui_Element_Index[clip_id]
	If Gui_ImageClip_Exists[clip_index] Then
		img_w = 0
		img_h = 0
		GetImageSize( Gui_ImageClip_Source_Image[clip_index], img_w, img_h)
		If x < 0 Then
			Gui_ImageClip_Source_X[clip_index] = 0
		ElseIf x > (img_w - Gui_ImageClip_Source_W[clip_index]) Then
			Gui_ImageClip_Source_X[clip_index] = img_w - Gui_ImageClip_Source_W[clip_index]
		Else
			Gui_ImageClip_Source_X[clip_index] = x
		End If
		If y < 0 Then
			Gui_ImageClip_Source_Y[clip_index] = 0
		ElseIf y > (img_h - Gui_ImageClip_Source_H[clip_index]) Then
			Gui_ImageClip_Source_Y[clip_index] = img_h - Gui_ImageClip_Source_H[clip_index]
		Else
			Gui_ImageClip_Source_Y[clip_index] = y
		End If
		RedrawImageClip(clip_index)
		Return True
	End If
	Return False
End Function


Sub RedrawImageSlide(slide_index)
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	SetColor(GUI_IMAGESLIDE_COLOR)
	RectFill(0, 0, Gui_ImageSlide_W[slide_index], Gui_ImageSlide_H[slide_index])
	SetColor(GUI_IMAGESLIDE_BORDER_COLOR)
	If Gui_ImageSlide_Count[slide_index] > 0 Then
		For i = 0 to Gui_ImageSlide_Count[slide_index]-1
			clip_index = Gui_Element_Index[ Gui_ImageSlide_ImageClip[slide_index, i] ]
			x = (i*Gui_ImageSlide_ImageClip_W[slide_index]) - Gui_ImageSlide_Offset_X[slide_index]
			If ImageExists(Gui_ImageClip_Image[clip_index]) Then
				DrawImage(Gui_ImageClip_Image[clip_index], x, 0)
			End If
			Rect(x,0, Gui_ImageSlide_ImageClip_W[slide_index], Gui_ImageSlide_ImageClip_H[slide_index])
		Next
	End If
	Rect(0, 0, Gui_ImageSlide_W[slide_index], Gui_ImageSlide_H[slide_index])
	SetColor(GUI_IMAGESLIDE_HIGHLIGHT_COLOR)
	sx = (Gui_ImageSlide_SelectedClip[slide_index]*Gui_ImageSlide_ImageClip_W[slide_index]) - Gui_ImageSlide_Offset_X[slide_index]
	Rect( sx+1, 1, Gui_ImageSlide_ImageClip_W[slide_index]-2, Gui_ImageSlide_ImageClip_H[slide_index]-2)
	If ImageExists(Gui_ImageSlide_Image[slide_index]) Then
		DeleteImage(Gui_ImageSlide_Image[slide_index])
	End If
	CanvasClip(Gui_ImageSlide_Image[slide_index], 0, 0, Gui_ImageSlide_W[slide_index], Gui_ImageSlide_H[slide_index], 1)
End Sub

Function Gui_CreateImageSlide(w, h, clip_w, clip_h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	For i = 0 to MAX_IMAGESLIDES-1
		If Not Gui_ImageSlide_Exists[i] Then
			Gui_ImageSlide_Exists[i] = True
			Gui_ImageSlide_W[i] = w
			Gui_ImageSlide_H[i] = h
			Gui_ImageSlide_Offset_X[i] = 0
			Gui_ImageSlide_Offset_Y[i] = 0
			Gui_ImageSlide_ImageClip_W[i] = clip_w
			Gui_ImageSlide_ImageClip_H[i] = clip_h
			Gui_ImageSlide_Count[i] = 0
			Gui_ImageSlide_Image[i] = Gui_GetFreeImage
			
			RedrawImageSlide(i)
			
			Gui_Element_Type[id] = GUI_TYPE_IMAGESLIDE
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Return id
		End If
	Next
	Return -1
End Function

Function Gui_ImageSlide_AddImageClip(slide_id, clip_id)
	slide_index = Gui_Element_Index[slide_id]
	clip_index = Gui_Element_Index[clip_id]
	If Gui_ImageSlide_Exists[slide_index] And Gui_ImageClip_Exists[clip_index] And (Gui_ImageSlide_Count[slide_index]+1) < MAX_IMAGESLIDE_CLIPS Then
		Gui_ImageSlide_ImageClip[slide_index, Gui_ImageSlide_Count[slide_index]] = clip_id
		Gui_ImageSlide_Count[slide_index] = Gui_ImageSlide_Count[slide_index] + 1
		RedrawImageSlide(slide_index)
		Return True
	End If
	Return False
End Function

Function Gui_ImageSlide_RemoveImageClip(slide_id)
	slide_index = Gui_Element_Index[slide_id]
	If Gui_ImageSlide_Exists[slide_index] And Gui_ImageSlide_Count[slide_index] > 0 Then
		Gui_ImageSlide_Count[slide_index] = Gui_ImageSlide_Count[slide_index] - 1
		RedrawImageSlide(slide_index)
		Return True
	End If
	Return False
End Function

Function Gui_ImageSlide_Clear(slide_id)
	slide_index = Gui_Element_Index[slide_id]
	If Gui_ImageSlide_Exists[slide_index] Then
		Gui_ImageSlide_Count[slide_index] = 0
		Gui_ImageSlide_SelectedClip[slide_index] = 0
		RedrawImageSlide(slide_index)
		Return True
	End If
	Return False
End Function

Function Gui_ImageSlide_GetNumClips(slide_id)
	slide_index = Gui_Element_Index[slide_id]
	If Gui_ImageSlide_Exists[slide_index] Then
		Return Gui_ImageSlide_Count[slide_index]
	End If
	Return 0
End Function

Function Gui_ImageSlide_SetOffset(slide_id, x, y)
	slide_index = Gui_Element_Index[slide_id]
	If Gui_ImageSlide_Exists[slide_index] Then
		If x < 0 Then
			Gui_ImageSlide_Offset_X[slide_index] = 0
		ElseIf x < (Gui_ImageSlide_Count[slide_index]*Gui_ImageSlide_ImageClip_W[slide_index]) - Gui_ImageSlide_ImageClip_W[slide_index] Then
			Gui_ImageSlide_Offset_X[slide_index] = x
		Else
			Gui_ImageSlide_Offset_X[slide_index] = (Gui_ImageSlide_Count[slide_index]*Gui_ImageSlide_ImageClip_W[slide_index]) - Gui_ImageSlide_ImageClip_W[slide_index]
		End If
		RedrawImageSlide(slide_index)
		Return True
	End If
	Return False
End Function

Function Gui_ImageSlide_MoveOffset(slide_id, x, y)
	slide_index = Gui_Element_Index[slide_id]
	If Gui_ImageSlide_Exists[slide_index] Then
		x = Gui_ImageSlide_Offset_X[slide_index] + x
		If x < 0 Then
			Gui_ImageSlide_Offset_X[slide_index] = 0
		ElseIf x < (Gui_ImageSlide_Count[slide_index]*Gui_ImageSlide_ImageClip_W[slide_index]) - Gui_ImageSlide_ImageClip_W[slide_index] Then
			Gui_ImageSlide_Offset_X[slide_index] = x
		Else
			Gui_ImageSlide_Offset_X[slide_index] = (Gui_ImageSlide_Count[slide_index]*Gui_ImageSlide_ImageClip_W[slide_index]) - Gui_ImageSlide_ImageClip_W[slide_index]
		End If
		RedrawImageSlide(slide_index)
		Return True
	End If
	Return False
End Function

Sub RedrawListBox(lbox_index)
	dim numItemsDisplayed
	numItemsDisplayed = Int(Gui_ListBox_H[lbox_index] / GUI_FONT_H)
	If numItemsDisplayed < Gui_ListBox_H[lbox_index] / GUI_FONT_H Then
		numItemsDisplayed = numItemsDisplayed + 1
	End If
	If Gui_ListBox_Offset[lbox_index] + numItemsDisplayed > Gui_ListBox_Count[lbox_index] Then
		numItemsDisplayed = Gui_ListBox_Count[lbox_index] - Gui_ListBox_Offset[lbox_index]
	End If
	If numItemsDisplayed < 0 Then
		numItemsDisplayed = 0
	End If
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	SetColor(GUI_LISTBOX_COLOR1)
	w = Gui_ListBox_W[lbox_index]
	h = Gui_ListBox_H[lbox_index]
	RectFill(0, 0, w, h)
	SetColor(GUI_FONT_COLOR)
	offset = Gui_ListBox_Offset[lbox_index]
	If numItemsDisplayed > 0 Then
		For i = 0 to numItemsDisplayed-1
			If Length(Trim(Gui_ListBox_Value$[lbox_index, offset + i ])) > 0 Then 
				DrawText(Gui_ListBox_Value$[lbox_index, offset + i ], 0, i*GUI_FONT_H)
			End If
		Next
	End If
	SetColor(GUI_LISTBOX_BORDER_COLOR)
	Rect(0, 0, w, h)
	If ImageExists(Gui_ListBox_Image[lbox_index]) Then
		DeleteImage(Gui_ListBox_Image[lbox_index])
	End If
	If Gui_ListBox_Selected_Item[lbox_index] >= Gui_ListBox_Offset[lbox_index] And (Gui_ListBox_Selected_Item[lbox_index] - Gui_ListBox_Offset[lbox_index]) < numItemsDisplayed Then
		'print "highlighted = ";Gui_ListBox_Highlighted_Index
		'print "offset = ";Gui_ListBox_Offset[lbox_index]
		'print "numDisplayed = ";numItemsDisplayed
		SetColor(GUI_LISTBOX_HIGHLIGHT_COLOR)
		Rect(0, (Gui_ListBox_Selected_Item[lbox_index] - Gui_ListBox_Offset[lbox_index]) * GUI_FONT_H, w, GUI_FONT_H)
	End If
	CanvasClip(Gui_ListBox_Image[lbox_index], 0, 0, w, h, 1)
End Sub

Function Gui_ListBox_AddItem(lbox, item$)
	lbox_index = Gui_Element_Index[lbox]
	If Gui_ListBox_Count[lbox_index]+1 < MAX_LISTBOX_VALUES Then
		num = Gui_ListBox_Count[lbox_index]
		Gui_ListBox_Count[lbox_index] = Gui_ListBox_Count[lbox_index] + 1
		Gui_ListBox_Value[lbox_index, num] = item$
		If (num * GUI_FONT_H) - (Gui_ListBox_Offset[lbox_index] * GUI_FONT_H) > 0 And (num * GUI_FONT_H) - (Gui_ListBox_Offset[lbox_index] * GUI_FONT_H) < Gui_ListBox_H[lbox_index] Then
			'redraw listbox
			RedrawListBox(lbox_index)
		End If
	End If
End Function

Function Gui_ListBox_RemoveItem(lbox, item_num)
	lbox_index = Gui_Element_Index[lbox]
	If item_num < Gui_ListBox_Count[lbox_index] Then
		For i = item_num to Gui_ListBox_Count[lbox_index]-1
			Gui_ListBox_Value$[lbox_index, i] = Gui_ListBox_Value$[lbox_index, i+1]
		Next
		Gui_ListBox_Count[lbox_index] = Gui_ListBox_Count[lbox_index] - 1
	End If
End Function

Function Gui_ListBox_Clear(lbox)
	lbox_index = Gui_Element_Index[lbox]
	Gui_ListBox_Count[lbox_index] = 0
	RedrawListBox(lbox_index)
End Function

Function Gui_ListBox_Update(lbox)
	lbox_index = Gui_Element_Index[lbox]
	RedrawListBox(lbox_index)
End Function

Function Gui_CreateListBox(w, h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	If w < GUI_LISTBOX_MIN_W Then
		w = GUI_LISTBOX_MIN_W
	End If
	If h < GUI_LISTBOX_MIN_H Then
		h = GUI_LISTBOX_MIN_H
	End If
	For i = 0 to MAX_LISTBOXES-1
		If Not Gui_ListBox_Exists[i] Then
			Gui_ListBox_Exists[i] = True
			Gui_ListBox_W[i] = w
			Gui_ListBox_H[i] = h
			Gui_ListBox_Count[i] = 0
			Gui_ListBox_Offset[i] = 0
			
			Canvas(GUI_TMP_CANVAS)
			ClearCanvas
			
			Gui_ListBox_Image[i] = Gui_GetFreeImage
			SetColor(GUI_LISTBOX_COLOR1)
			RectFill(0, 0, w, h)
			SetColor(GUI_LISTBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(Gui_ListBox_Image[i], 0, 0, w, h, 1)
			
			
			If OS = "WINDOWS" Then
				GUI_SCROLLDOWN_IMAGE = Gui_GetFreeImage
				LoadImage(GUI_SCROLLDOWN_IMAGE, GUI_DIR+"\\gui_gfx\\scroll_down.png")
				GUI_SCROLLUP_IMAGE = Gui_GetFreeImage
				LoadImage(GUI_SCROLLUP_IMAGE, GUI_DIR+"\\gui_gfx\\scroll_up.png")
				GUI_PAGEDOWN_IMAGE = Gui_GetFreeImage
				LoadImage(GUI_PAGEDOWN_IMAGE, GUI_DIR+"\\gui_gfx\\page_down.png")
				GUI_PAGEUP_IMAGE = Gui_GetFreeImage
				LoadImage(GUI_PAGEUP_IMAGE, GUI_DIR+"\\gui_gfx\\page_up.png")				
			Else
				GUI_SCROLLDOWN_IMAGE = Gui_GetFreeImage
				LoadImage(GUI_SCROLLDOWN_IMAGE, GUI_DIR+"/gui_gfx/scroll_down.png")
				GUI_SCROLLUP_IMAGE = Gui_GetFreeImage
				LoadImage(GUI_SCROLLUP_IMAGE, GUI_DIR+"/gui_gfx/scroll_up.png")
				GUI_PAGEDOWN_IMAGE = Gui_GetFreeImage
				LoadImage(GUI_PAGEDOWN_IMAGE, GUI_DIR+"/gui_gfx/page_down.png")
				GUI_PAGEUP_IMAGE = Gui_GetFreeImage
				LoadImage(GUI_PAGEUP_IMAGE, GUI_DIR+"/gui_gfx/page_up.png")
				End If
			
			w = GUI_LISTBOX_MIN_W
			h = Int(h / 4)
			
			Dim img_w
			Dim img_h
			GetImageSize(GUI_PAGEUP_IMAGE, img_w, img_h) 'all these images are the same size so i only get it here
			
			draw_guigfx_w = w-4
			draw_guigfx_h = GUI_LISTBOX_MIN_H - 4
			
			ClearCanvas
			Gui_ListBox_ScrollBar_Image[i, 0] = Gui_GetFreeImage
			SetColor(GUI_LISTBOX_COLOR2)
			RectFill(0, 0, w, h)
			DrawImage_Blit_Ex(GUI_PAGEUP_IMAGE, 2, (h/2) - (draw_guigfx_h/2), draw_guigfx_w, draw_guigfx_h, 0, 0, img_w, img_h)
			SetColor(GUI_LISTBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(Gui_ListBox_ScrollBar_Image[i, 0], 0, 0, w, h, 1)
			
			ClearCanvas
			Gui_ListBox_ScrollBar_Image[i, 1] = Gui_GetFreeImage
			SetColor(GUI_LISTBOX_COLOR2)
			RectFill(0, 0, w, h)
			DrawImage_Blit_Ex(GUI_SCROLLUP_IMAGE, 2, (h/2) - (draw_guigfx_h/2), draw_guigfx_w, draw_guigfx_h, 0, 0, img_w, img_h)
			SetColor(GUI_LISTBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(Gui_ListBox_ScrollBar_Image[i, 1], 0, 0, w, h, 1)
			
			ClearCanvas
			Gui_ListBox_ScrollBar_Image[i, 2] = Gui_GetFreeImage
			SetColor(GUI_LISTBOX_COLOR2)
			RectFill(0, 0, w, h)
			DrawImage_Blit_Ex(GUI_SCROLLDOWN_IMAGE, 2, (h/2) - (draw_guigfx_h/2), draw_guigfx_w, draw_guigfx_h, 0, 0, img_w, img_h)
			SetColor(GUI_LISTBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(Gui_ListBox_ScrollBar_Image[i, 2], 0, 0, w, h, 1)
			
			ClearCanvas
			Gui_ListBox_ScrollBar_Image[i, 3] = Gui_GetFreeImage
			SetColor(GUI_LISTBOX_COLOR2)
			RectFill(0, 0, w, h)
			DrawImage_Blit_Ex(GUI_PAGEDOWN_IMAGE, 2, (h/2) - (draw_guigfx_h/2), draw_guigfx_w, draw_guigfx_h, 0, 0, img_w, img_h)
			SetColor(GUI_LISTBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(Gui_ListBox_ScrollBar_Image[i, 3], 0, 0, w, h, 1)
			
			ClearCanvas
			Gui_ListBox_ScrollBar_Image[i, 4] = Gui_GetFreeImage
			SetColor(GUI_LISTBOX_COLOR3)
			RectFill(0, 0, w, h)
			DrawImage_Blit_Ex(GUI_PAGEUP_IMAGE, 2, (h/2) - (draw_guigfx_h/2), draw_guigfx_w, draw_guigfx_h, 0, 0, img_w, img_h)
			SetColor(GUI_LISTBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(Gui_ListBox_ScrollBar_Image[i, 4], 0, 0, w, h, 1)
			
			ClearCanvas
			Gui_ListBox_ScrollBar_Image[i, 5] = Gui_GetFreeImage
			SetColor(GUI_LISTBOX_COLOR3)
			RectFill(0, 0, w, h)
			DrawImage_Blit_Ex(GUI_SCROLLUP_IMAGE, 2, (h/2) - (draw_guigfx_h/2), draw_guigfx_w, draw_guigfx_h, 0, 0, img_w, img_h)
			SetColor(GUI_LISTBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(Gui_ListBox_ScrollBar_Image[i, 5], 0, 0, w, h, 1)
			
			ClearCanvas
			Gui_ListBox_ScrollBar_Image[i, 6] = Gui_GetFreeImage
			SetColor(GUI_LISTBOX_COLOR3)
			RectFill(0, 0, w, h)
			DrawImage_Blit_Ex(GUI_SCROLLDOWN_IMAGE, 2, (h/2) - (draw_guigfx_h/2), draw_guigfx_w, draw_guigfx_h, 0, 0, img_w, img_h)
			SetColor(GUI_LISTBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(Gui_ListBox_ScrollBar_Image[i, 6], 0, 0, w, h, 1)
			
			ClearCanvas
			Gui_ListBox_ScrollBar_Image[i, 7] = Gui_GetFreeImage
			SetColor(GUI_LISTBOX_COLOR3)
			RectFill(0, 0, w, h)
			DrawImage_Blit_Ex(GUI_PAGEDOWN_IMAGE, 2, (h/2) - (draw_guigfx_h/2), draw_guigfx_w, draw_guigfx_h, 0, 0, img_w, img_h)
			SetColor(GUI_LISTBOX_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(Gui_ListBox_ScrollBar_Image[i, 7], 0, 0, w, h, 1)
			
			DeleteImage(GUI_PAGEDOWN_IMAGE)
			DeleteImage(GUI_PAGEUP_IMAGE)
			DeleteImage(GUI_SCROLLDOWN_IMAGE)
			DeleteImage(GUI_SCROLLUP_IMAGE)
			
			Gui_Element_Type[id] = GUI_TYPE_LISTBOX
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Return id
		End If
	Next
	Return -1
End Function

Sub RedrawTextField(t_index)
	'need to redraw textfield
	If ImageExists(Gui_TextField_Image[t_index]) Then
		DeleteImage(Gui_TextField_Image[t_index])
	End If
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	w = Gui_TextField_W[t_index]
	h = Gui_TextField_H[t_index]
	If GUI_STATE = GUI_STATE_TEXTFIELD_EDIT Then
		SetColor(rgb(255,255,255))
	Else
		SetColor(GUI_TEXTFIELD_COLOR1)
	End If
	RectFill(0, 0, w, h)
	Font(GUI_FONT)
	SetColor(GUI_FONT_COLOR)
	txt$ = Mid(Gui_TextField_Value$[t_index], Gui_TextField_Offset[t_index], Length(Gui_TextField_Value$[t_index]))
	If Length(txt$) = 0 Then
		DrawText(" ", 1, 1)
	ElseIf Gui_TextField_isPassword[t_index] Then
		DrawText(StringFill$("*", Length(txt$)), 1, 1)
	Else
		DrawText(txt$, 1, 1)
	End If
	SetColor(GUI_TEXTFIELD_BORDER_COLOR)
	Rect(0, 0, w, h)
	CanvasClip(Gui_TextField_Image[t_index], 0, 0, w, h, 1)
End Sub

Function Gui_CreateTextField(w, h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	For i = 0 to MAX_TEXTFIELDS-1
		If Not Gui_TextField_Exists[i] Then
			Gui_TextField_Exists[i] = True
			Gui_TextField_W[i] = w
			Gui_TextField_H[i] = h
			Gui_TextField_Offset[i] = 0
			
			Canvas(GUI_TMP_CANVAS)
			ClearCanvas
			
			img = Gui_GetFreeImage
			
			SetColor(GUI_TEXTFIELD_COLOR1)
			RectFill(0, 0, w, h)
			SetColor(GUI_TEXTFIELD_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(img, 0, 0, w, h, 1)
			Gui_TextField_Image[i] = img
			
			Gui_Element_Type[id] = GUI_TYPE_TEXTFIELD
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Return id
		End If
	Next
	Return -1
End Function

Function Gui_CreateDynamicTextField(w, h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	For i = 0 to MAX_TEXTFIELDS-1
		If Not Gui_TextField_Exists[i] Then
			Gui_TextField_Exists[i] = True
			Gui_TextField_isDynamic[i] = True
			Gui_TextField_W[i] = w
			Gui_TextField_H[i] = h
			Gui_TextField_Offset[i] = 0
			
			Canvas(GUI_TMP_CANVAS)
			ClearCanvas
			
			img = Gui_GetFreeImage
			
			SetColor(GUI_TEXTFIELD_COLOR1)
			RectFill(0, 0, w, h)
			SetColor(GUI_TEXTFIELD_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(img, 0, 0, w, h, 1)
			Gui_TextField_Image[i] = img
			
			Gui_Element_Type[id] = GUI_TYPE_TEXTFIELD
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Return id
		End If
	Next
	Return -1
End Function

Function Gui_CreateSurface(w, h)
	id = Gui_GetFreeID
	If id < 0 Then
		Return -1
	End If
	For i = 0 to MAX_SURFACES-1
		If Not Gui_Surface_Exists[i] Then
			Gui_Surface_Exists[i] = True
			Gui_Surface_W[i] = w
			Gui_Surface_H[i] = h
			
			Canvas(GUI_TMP_CANVAS)
			ClearCanvas
			
			img = Gui_GetFreeImage
			
			SetColor(GUI_SURFACE_CLEAR_COLOR)
			RectFill(0, 0, w, h)
			SetColor(GUI_SURFACE_BORDER_COLOR)
			Rect(0, 0, w, h)
			CanvasClip(img, 0, 0, w, h, 1)
			Gui_Surface_Image[i] = img
			
			Gui_Element_Type[id] = GUI_TYPE_SURFACE
			Gui_Element_Index[id] = i
			Gui_Element_Exists[id] = True
			Gui_Element_Active[id] = True
			Return id
		End If
	Next
	Return -1
End Function

Function IsOnObject(id, x, y)
	obj_type = Gui_Element_Type[id]
	obj_index = Gui_Element_Index[id]
	Select Case obj_type
	Case GUI_TYPE_BUTTON
		panel_index = Gui_Element_Index[ Gui_Button_Panel[obj_index] ]
		x = x - Gui_Panel_X[panel_index]
		y = y - Gui_Panel_Y[panel_index]
		If x >= Gui_Button_X[obj_index] And x < (Gui_Button_X[obj_index]+Gui_Button_W[obj_index]) And y >= Gui_Button_Y[obj_index] And y < (Gui_Button_Y[obj_index]+Gui_Button_H[obj_index]) Then
			Return True
		End If
	Case GUI_TYPE_TAB
		tx = Gui_TabGroup_X[obj_index]
		ty = Gui_TabGroup_Y[obj_index]
		tw = Gui_TabGroup_W[obj_index]
		th = Gui_TabGroup_H[obj_index]
		If x >= tx And x < (tx+tw) And y >= ty And y < (ty+th) Then
			Return True
		End If
	Case GUI_TYPE_DROPDOWN
		panel_index = Gui_Element_Index[ Gui_DropDown_Panel[obj_index] ]
		x = x - Gui_Panel_X[panel_index]
		y = y - Gui_Panel_Y[panel_index]
		If x >= Gui_DropDown_X[obj_index] And x < (Gui_DropDown_X[obj_index]+Gui_DropDown_W[obj_index]) And y >= Gui_DropDown_Y[obj_index] And y < (Gui_DropDown_Y[obj_index]+Gui_DropDown_H[obj_index]) Then
			Return True
		End If
	Case GUI_TYPE_LISTBOX
		panel_index = Gui_Element_Index[ Gui_ListBox_Panel[obj_index] ]
		x = x - Gui_Panel_X[panel_index]
		y = y - Gui_Panel_Y[panel_index]
		If x >= Gui_ListBox_X[obj_index] And x < (Gui_ListBox_X[obj_index]+Gui_ListBox_W[obj_index]) And y >= Gui_ListBox_Y[obj_index] And y < (Gui_ListBox_Y[obj_index]+Gui_ListBox_H[obj_index]) Then
			sx = ( Gui_ListBox_X[obj_index] + Gui_ListBox_W[obj_index] ) - GUI_LISTBOX_MIN_W
			scroll_index = Int( (y - Gui_ListBox_Y[obj_index]) / (Gui_ListBox_H[obj_index]/4) )
			For i = 0 to 3
				Gui_ListBox_ScrollBar_Hover[i] = False
			Next
			If x >= sx And scroll_index >= 0 And scroll_index < ( Gui_ListBox_H[obj_index] / (Gui_ListBox_H[obj_index]/4) )  Then
				Gui_ListBox_ScrollBar_Hover[scroll_index] = True
				'print "scroll = ";scroll_index
			Else
				Gui_ListBox_Highlighted_Index = Gui_ListBox_Offset[obj_index] + Int( (y - Gui_ListBox_Y[obj_index]) / GUI_FONT_H)
			End If
			Return True
		End If
	Case GUI_TYPE_TEXTFIELD
		panel_index = Gui_Element_Index[ Gui_TextField_Panel[obj_index] ]
		x = x - Gui_Panel_X[panel_index]
		y = y - Gui_Panel_Y[panel_index]
		If x >= Gui_TextField_X[obj_index] And x < (Gui_TextField_X[obj_index]+Gui_TextField_W[obj_index]) And y >= Gui_TextField_Y[obj_index] And y < (Gui_TextField_Y[obj_index]+Gui_TextField_H[obj_index]) Then
			Return True
		End If
	Case GUI_TYPE_CHECKBOX
		panel_index = Gui_Element_Index[ Gui_CheckBox_Panel[obj_index] ]
		x = x - Gui_Panel_X[panel_index]
		y = y - Gui_Panel_Y[panel_index]
		If x >= Gui_CheckBox_X[obj_index] And x < (Gui_CheckBox_X[obj_index]+Gui_CheckBox_W[obj_index]) And y >= Gui_CheckBox_Y[obj_index] And y < (Gui_CheckBox_Y[obj_index]+Gui_CheckBox_H[obj_index]) Then
			Return True
		End If
	Case GUI_TYPE_IMAGECLIP
		panel_index = Gui_Element_Index[ Gui_ImageClip_Panel[obj_index] ]
		x = x - Gui_Panel_X[panel_index]
		y = y - Gui_Panel_Y[panel_index]
		If x >= Gui_ImageClip_X[obj_index] And x < (Gui_ImageClip_X[obj_index]+Gui_ImageClip_W[obj_index]) And y >= Gui_ImageClip_Y[obj_index] And y < (Gui_ImageClip_Y[obj_index]+Gui_ImageClip_H[obj_index]) Then
			Return True
		End If
	Case GUI_TYPE_IMAGESLIDE
		panel_index = Gui_Element_Index[ Gui_ImageSlide_Panel[obj_index] ]
		x = x - Gui_Panel_X[panel_index]
		y = y - Gui_Panel_Y[panel_index]
		If x >= Gui_ImageSlide_X[obj_index] And x < (Gui_ImageSlide_X[obj_index]+Gui_ImageSlide_W[obj_index]) And y >= Gui_ImageSlide_Y[obj_index] And y < (Gui_ImageSlide_Y[obj_index]+Gui_ImageSlide_H[obj_index]) Then
			Gui_ImageSlide_Hover = Int(( (x-Gui_ImageSlide_X[obj_index]) / Gui_ImageSlide_ImageClip_W[obj_index]) + (Gui_ImageSlide_Offset_X[obj_index] / Gui_ImageSlide_ImageClip_W[obj_index]))
			'print x;" / ";Gui_ImageSlide_ImageClip_W[obj_index]
			Return True
		End If
	Case GUI_TYPE_SURFACE
		panel_index = Gui_Element_Index[ Gui_Surface_Panel[obj_index] ]
		x = x - Gui_Panel_X[panel_index]
		y = y - Gui_Panel_Y[panel_index]
		If x >= Gui_Surface_X[obj_index] And x < (Gui_Surface_X[obj_index]+Gui_Surface_W[obj_index]) And y >= Gui_Surface_Y[obj_index] And y < (Gui_Surface_Y[obj_index]+Gui_Surface_H[obj_index]) Then
			Return True
		End If
	End Select
	Return False
End Function

Sub SetListBoxScrollAction()
	For i = 0 to 3
		Gui_ListBox_ScrollBar_Action[i] = Gui_ListBox_ScrollBar_Hover[i]
	Next
End Sub

Sub Gui_ListBox_Scroll(lbox_id, i)
	lbox_index = Gui_Element_Index[lbox_id]
	lb_max = Gui_ListBox_Count[lbox_index] - Int( Gui_ListBox_H[lbox_index] / GUI_FONT_H )
	lb_offset = Gui_ListBox_Offset[lbox_index]
	If (lb_offset + i) < 0 Then
		Gui_ListBox_Offset[lbox_index] = 0
	ElseIf (lb_offset +i) > lb_max Then
		Gui_ListBox_Offset[lbox_index] = lb_max
	Else
		Gui_ListBox_Offset[lbox_index] = lb_offset + i
	End If
	
	If Gui_ListBox_Offset[lbox_index] < 0 Then
		Gui_ListBox_Offset[lbox_index] = 0
	End If
	
	RedrawListBox(lbox_index)
End Sub

Sub Gui_ListBox_PageScroll(lbox_id, i)
	lbox_index = Gui_Element_Index[lbox_id]
	lb_max = Gui_ListBox_Count[lbox_index] - Int( Gui_ListBox_H[lbox_index] / GUI_FONT_H )
	lb_offset = Gui_ListBox_Offset[lbox_index]
	lb_page = Int(Gui_ListBox_H[lbox_index] / GUI_FONT_H)
	
	i = i * lb_page
	
	If (lb_offset + i ) < 0 Then
		Gui_ListBox_Offset[lbox_index] = 0
	ElseIf (lb_offset +i) > lb_max Then
		Gui_ListBox_Offset[lbox_index] = lb_max
	Else
		Gui_ListBox_Offset[lbox_index] = lb_offset + i
	End If
	
	If Gui_ListBox_Offset[lbox_index] < 0 Then
		Gui_ListBox_Offset[lbox_index] = 0
	End If
	
	RedrawListBox(lbox_index)
End Sub

Function Gui_TabSwitch(id, x)
	index = Gui_Element_Index[id]
	x = x - Gui_TabGroup_X[index]
	tab_w = Gui_TabGroup_W[index] / Gui_TabGroup_TabCount[index]
	tab = Int(x / tab_w)
	
	If tab >= Gui_TabGroup_TabCount[index] Then
		tab = Gui_TabGroup_TabCount[index]-1
	End If
	
	old_AT = Gui_TabGroup_ActiveTab[index]
	new_AT = tab
	
	For i = 0 to MAX_TAB_OBJECTS-1
		If Gui_TabGroup_Tab_Object_Exists[index,old_AT, i] Then
			obj_id = Gui_TabGroup_Tab_Object_ID[index, old_AT, i]
			Gui_Element_Active[obj_id] = False
			obj_type = Gui_Element_Type[obj_id]
			Select Case obj_type
			Case GUI_TYPE_PANEL
				Gui_SetPanelActive(obj_id, False)
			Case GUI_TYPE_TAB
				Gui_SetTabGroupActive(obj_id, False)
			End Select
		End If
	Next
	
	For i = 0 to MAX_TAB_OBJECTS-1
		If Gui_TabGroup_Tab_Object_Exists[index,new_AT, i] Then
			obj_id = Gui_TabGroup_Tab_Object_ID[index, new_AT, i]
			Gui_Element_Active[obj_id] = True
			obj_type = Gui_Element_Type[obj_id]
			Select Case obj_type
			Case GUI_TYPE_PANEL
				Gui_SetPanelActive(obj_id, True)
			Case GUI_TYPE_TAB
				Gui_SetTabGroupActive(obj_id, True)
			End Select
		End If
	Next
	
	Gui_TabGroup_ActiveTab[index] = tab
	
	Return tab
End Function

Function GetDropDownSelection(byref x, byref y)
	d_index = Gui_Element_Index[EVENT_ID]
	panel_id = Gui_DropDown_Panel[d_index]
	panel_index = Gui_Element_Index[panel_id]
	x = x - (Gui_Panel_X[panel_index] + Gui_DropDown_X[d_index])
	y = y - (Gui_Panel_Y[panel_index] + Gui_DropDown_Y[d_index] + Gui_DropDown_H[d_index])
	selection = -1
	If x >= 0 And x < Gui_DropDown_W[d_index] Then
		selection = Int(y / GUI_FONT_H)
		If selection < 0 Or selection >= Gui_DropDown_Count[d_index] Then
			selection = -1
		End If
	End If
	Return selection
End Function

Function ClipBoard_Text_Event(event_flag)
	If Not ( event_flag And HasClipboardText ) Then
		Return 0
	End If
	ReadInput_SetText(ReadInput_Text$ + ClipboardText$)
	Return 1
End Function

mb_right = 0

Sub Gui_PollEvents()
	mx = mouseX
	my = mouseY
	mb = mouseButton(0)
	
	If mb Then
		Select Case MOUSE_STATE
		Case 0
			MOUSE_STATE = MOUSE_PRESSED
		Case MOUSE_PRESSED
			MOUSE_STATE = MOUSE_HOLD
		Case MOUSE_RELEASED
			MOUSE_STATE = 0
		End Select
	Else
		Select Case MOUSE_STATE
		Case MOUSE_PRESSED
			MOUSE_STATE = MOUSE_RELEASED
		Case MOUSE_RELEASED
			MOUSE_STATE = 0
		Case MOUSE_HOLD
			MOUSE_STATE = MOUSE_RELEASED
		End Select
	End If
	
	If MouseButton(2) Then
		mb_right = 1
	ElseIf MouseButton(2) = 0 And mb_right = 1 Then
		mb_right = 2
	Else
		mb_right = 0
	End If
	
	If GUI_STATE = GUI_STATE_DROPDOWN_OPEN Then
		'handle dropdown here
		d_index = Gui_Element_Index[EVENT_ID]
		
		dx = mx
		dy = my
		
		Gui_DropDown_Highlighted_Index = GetDropDownSelection(dx, dy)
		
		Gui_DropDown_Highlighted_X = dx
		Gui_DropDown_Highlighted_Y = dy
		
		If MOUSE_STATE = MOUSE_PRESSED Then
			If Gui_DropDown_Highlighted_Index >= 0 Then
				Gui_DropDown_Selected_Item[d_index] = Gui_DropDown_Highlighted_Index
			End If
			
			RedrawDropDownSelected(d_index)
			
			GUI_STATE = 0
			EVENT_TYPE = 0
		End If
		
	ElseIf GUI_STATE = GUI_STATE_TEXTFIELD_EDIT Then
		t_index = Gui_Element_Index[EVENT_ID]
		ClipBoard_Text_Event( mb_right = 2 )
		Gui_TextField_Value$[t_index] = ReadInput_Text$
		Gui_TextField_Offset[t_index] = Length(Gui_TextField_Value$[t_index]) - (Gui_TextField_W[t_index]/GUI_FONT_W)
		If Gui_TextField_Offset[t_index] < 0 Then
			Gui_TextField_Offset[t_index] = 0
		End If
		
		RedrawTextField(t_index)
		
		If Key(K_RETURN) Or mb Then
			ReadInput_Stop
			GUI_STATE = 0
			RedrawTextField(t_index)
			EVENT_TYPE = TEXTFIELD_RETURN
		End If
	Else
		For i = 0 to MAX_GUI_ELEMENTS-1
			If Gui_Element_Active[i] And Gui_Element_Active[ Gui_Element_Parent[i] ] And Gui_Element_Window[ Gui_Element_Parent[i] ] = gui_current_win Then
				obj_index = Gui_Element_Index[i]
				Select Case Gui_Element_Type[i]
				Case GUI_TYPE_BUTTON
					Gui_Button_Current_Image[obj_index] = 0
					If (EVENT_TYPE = BUTTON_PRESSED Or EVENT_TYPE = BUTTON_RELEASED) And EVENT_ID <> i Then
						'do nothing and continue looping
						'print "here: ";i
					ElseIf EVENT_TYPE = BUTTON_PRESSED And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_RELEASED Then
						EVENT_TYPE = BUTTON_RELEASED
						'print "released ";i
						EVENT_ID = i
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_PRESSED Then
						EVENT_TYPE = BUTTON_PRESSED
						'print "BUTTON pressed: ";I
						EVENT_ID = i
						Gui_Button_Current_Image[obj_index] = 1
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_HOLD Then
						'mouse is down before going over button
						Return
					ElseIf EVENT_TYPE = BUTTON_PRESSED And MOUSE_STATE = MOUSE_HOLD Then
						Gui_Button_Current_Image[obj_index] = 1
						Return
					ElseIf EVENT_TYPE = BUTTON_PRESSED Or EVENT_TYPE = BUTTON_RELEASED Then
						EVENT_TYPE = 0
						Return
					End If
				Case GUI_TYPE_TAB
					If EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_PRESSED Then
						EVENT_TYPE = TAB_SWITCH
						EVENT_ID = i
						Gui_TabSwitch(i, mx)
						Return
					ElseIf EVENT_TYPE = TAB_SWITCH Then
						EVENT_TYPE = 0
					End If
				Case GUI_TYPE_DROPDOWN
					Gui_DropDown_Current_Image[obj_index] = 0
					If (EVENT_TYPE = DROPDOWN_PRESSED Or EVENT_TYPE = DROPDOWN_RELEASED) And EVENT_ID <> i Then
						'do nothing and continue looping
					ElseIf EVENT_TYPE = DROPDOWN_PRESSED And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_RELEASED Then
						EVENT_TYPE = DROPDOWN_RELEASED
						EVENT_ID = i
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_PRESSED Then
						EVENT_TYPE = DROPDOWN_PRESSED
						EVENT_ID = i
						Gui_DropDown_Current_Image[obj_index] = 1
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_HOLD Then
						'mouse is down before going over button
						Return
					ElseIf EVENT_TYPE = DROPDOWN_PRESSED And MOUSE_STATE = MOUSE_HOLD Then
						Gui_DropDown_Current_Image[obj_index] = 1
						Return
					ElseIf EVENT_TYPE = DROPDOWN_RELEASED Then
						GUI_STATE = GUI_STATE_DROPDOWN_OPEN
						Return
					ElseIf EVENT_TYPE = DROPDOWN_PRESSED Then
						EVENT_TYPE = 0
						Return
					End If
				Case GUI_TYPE_LISTBOX
					Gui_ListBox_ScrollBar_Action[0] = False
					Gui_ListBox_ScrollBar_Action[1] = False
					Gui_ListBox_ScrollBar_Action[2] = False
					Gui_ListBox_ScrollBar_Action[3] = False
					Gui_ListBox_ScrollBar_Pressed[0] = False
					Gui_ListBox_ScrollBar_Pressed[1] = False
					Gui_ListBox_ScrollBar_Pressed[2] = False
					Gui_ListBox_ScrollBar_Pressed[3] = False
					on_obj = IsOnObject(i, mx, my)
					If (EVENT_TYPE >= 6 And EVENT_TYPE <= 14) And EVENT_ID <> i Then
						'do nothing and continue looping
					ElseIf EVENT_TYPE = LISTBOX_SCROLLUP_PRESSED And on_obj And Gui_ListBox_ScrollBar_Hover[1] And MOUSE_STATE = MOUSE_RELEASED Then
						EVENT_TYPE = LISTBOX_SCROLLUP_RELEASED
						EVENT_ID = i
						'scroll listbox up by 1
						Gui_ListBox_Scroll(i, -1)
						Return
					ElseIf EVENT_TYPE = LISTBOX_SCROLLDOWN_PRESSED And on_obj And Gui_ListBox_ScrollBar_Hover[2] And MOUSE_STATE = MOUSE_RELEASED Then
						EVENT_TYPE = LISTBOX_SCROLLDOWN_RELEASED
						EVENT_ID = i
						'scroll listbox down by 1
						Gui_ListBox_Scroll(i, 1)
						Return
					ElseIf EVENT_TYPE = LISTBOX_PAGEUP_PRESSED And on_obj And Gui_ListBox_ScrollBar_Hover[0] And MOUSE_STATE = MOUSE_RELEASED Then
						EVENT_TYPE = LISTBOX_PAGEUP_RELEASED
						EVENT_ID = i
						'scroll listbox up by 1 page
						Gui_ListBox_PageScroll(i, -1)
						Return
					ElseIf EVENT_TYPE = LISTBOX_PAGEDOWN_PRESSED And on_obj And Gui_ListBox_ScrollBar_Hover[3] And MOUSE_STATE = MOUSE_RELEASED Then
						EVENT_TYPE = LISTBOX_PAGEDOWN_RELEASED
						EVENT_ID = i
						'scroll listbox down by 1 page
						Gui_ListBox_PageScroll(i, 1)
						Return
					ElseIf EVENT_TYPE = 0 And on_obj And MOUSE_STATE = MOUSE_PRESSED Then
						
						If Gui_ListBox_ScrollBar_Hover[1] Then
							EVENT_TYPE = LISTBOX_SCROLLUP_PRESSED
						ElseIf Gui_ListBox_ScrollBar_Hover[2] Then
							EVENT_TYPE = LISTBOX_SCROLLDOWN_PRESSED
						ElseIf Gui_ListBox_ScrollBar_Hover[0] Then
							EVENT_TYPE = LISTBOX_PAGEUP_PRESSED
						ElseIf Gui_ListBox_ScrollBar_Hover[3] Then
							EVENT_TYPE = LISTBOX_PAGEDOWN_PRESSED
						Else
							EVENT_TYPE = LISTBOX_ITEM_SELECT
							If Gui_ListBox_Highlighted_Index < Gui_ListBox_Count[obj_index] Then
								Gui_ListBox_Selected_Item[obj_index] = Gui_ListBox_Highlighted_Index
							Else
								Gui_ListBox_Selected_Item[obj_index] = Gui_ListBox_Count[obj_index] - 1
							End If
							RedrawListBox(obj_index)
							'print "selected item is ";Gui_ListBox_Selected_Item[obj_index]
						End If
						
						SetListBoxScrollAction()
						
						EVENT_ID = i
						Return
					ElseIf EVENT_TYPE = 0 And on_obj And MOUSE_STATE = MOUSE_HOLD Then
						'mouse is down before going over listbox
						Return
					ElseIf MOUSE_STATE = MOUSE_HOLD Then
						Select Case EVENT_TYPE
						Case LISTBOX_SCROLLUP_PRESSED
							Gui_ListBox_ScrollBar_Action[1] = True
						Case LISTBOX_SCROLLDOWN_PRESSED
							Gui_ListBox_ScrollBar_Action[2] = True
						Case LISTBOX_PAGEUP_PRESSED
							Gui_ListBox_ScrollBar_Action[0] = True
						Case LISTBOX_PAGEDOWN_PRESSED
							Gui_ListBox_ScrollBar_Action[3] = True
						End Select
						Return
					ElseIf EVENT_TYPE >= LISTBOX_SCROLLUP_PRESSED And EVENT_TYPE <= LISTBOX_ITEM_SELECT Then
						EVENT_TYPE = 0
						Return
					End If
				Case GUI_TYPE_TEXTFIELD
					If Not Gui_TextField_isDynamic[obj_index] Then
						If (EVENT_TYPE = TEXTFIELD_PRESSED Or EVENT_TYPE = TEXTFIELD_RELEASED) And EVENT_ID <> i Then
							'Do nothing and continue looping
						ElseIf EVENT_TYPE = TEXTFIELD_PRESSED And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_RELEASED Then
							EVENT_TYPE = TEXTFIELD_RELEASED
							EVENT_ID = i
							'print "released"
							Return
						ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_PRESSED Then
							EVENT_TYPE = TEXTFIELD_PRESSED
							EVENT_ID = i
							'print "pressed"
							Return
						ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_HOLD Then
							'mouse is down before going over button
							Return
						ElseIf EVENT_TYPE = TEXTFIELD_PRESSED And MOUSE_STATE = MOUSE_HOLD Then
							Return
						ElseIf EVENT_TYPE = TEXTFIELD_RELEASED Then
							GUI_STATE = GUI_STATE_TEXTFIELD_EDIT
							ReadInput_Start
							ReadInput_SetText(Gui_TextField_Value$[obj_index])
							Return
						ElseIf EVENT_TYPE = TEXTFIELD_PRESSED Or EVENT_TYPE = TEXTFIELD_RETURN Then
							EVENT_TYPE = 0
							'print "null"
							Return
						End If
					End If
				Case GUI_TYPE_CHECKBOX
					'Gui_CheckBox_Current_Image[obj_index] = 0
					If (EVENT_TYPE = CHECKBOX_PRESSED Or EVENT_TYPE = CHECKBOX_RELEASED) And EVENT_ID <> i Then
						'do nothing and continue looping
					ElseIf EVENT_TYPE = CHECKBOX_PRESSED And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_RELEASED Then
						Select Case Gui_CheckBox_Value[obj_index]
						Case 0
							Gui_CheckBox_Value[obj_index] = 1
							Gui_CheckBox_Current_Image[obj_index] = 2
						Case 1
							Gui_CheckBox_Value[obj_index] = 0
							Gui_CheckBox_Current_Image[obj_index] = 0
						End Select
						EVENT_TYPE = CHECKBOX_RELEASED
						EVENT_ID = i
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_PRESSED Then
						EVENT_TYPE = CHECKBOX_PRESSED
						EVENT_ID = i
						Gui_CheckBox_Current_Image[obj_index] = 1
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_HOLD Then
						'mouse is down before going over button
						Return
					ElseIf EVENT_TYPE = CHECKBOX_PRESSED And MOUSE_STATE = MOUSE_HOLD Then
						Gui_CheckBox_Current_Image[obj_index] = 1
						Return
					ElseIf EVENT_TYPE = CHECKBOX_PRESSED Or EVENT_TYPE = CHECKBOX_RELEASED Then
						EVENT_TYPE = 0
						Return
					End If
				Case GUI_TYPE_IMAGECLIP
					If (EVENT_TYPE = IMAGECLIP_PRESSED Or EVENT_TYPE = IMAGECLIP_RELEASED) And EVENT_ID <> i Then
						'do nothing and continue looping
					ElseIf EVENT_TYPE = IMAGECLIP_PRESSED And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_RELEASED Then
						EVENT_TYPE = IMAGECLIP_RELEASED
						EVENT_ID = i
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_PRESSED Then
						EVENT_TYPE = IMAGECLIP_PRESSED
						EVENT_ID = i
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_HOLD Then
						'mouse is down before going over button
						Return
					ElseIf EVENT_TYPE = IMAGECLIP_PRESSED And MOUSE_STATE = MOUSE_HOLD Then
						Return
					ElseIf EVENT_TYPE = IMAGECLIP_PRESSED Or EVENT_TYPE = IMAGECLIP_RELEASED Then
						EVENT_TYPE = 0
						Return
					End If
				Case GUI_TYPE_IMAGESLIDE
					If (EVENT_TYPE = IMAGESLIDE_PRESSED Or EVENT_TYPE = IMAGESLIDE_RELEASED) And EVENT_ID <> i Then
						'do nothing and continue looping
					ElseIf EVENT_TYPE = IMAGESLIDE_PRESSED And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_RELEASED Then
						EVENT_TYPE = IMAGESLIDE_RELEASED
						EVENT_ID = i
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_PRESSED Then
						EVENT_TYPE = IMAGESLIDE_PRESSED
						EVENT_ID = i
						Gui_ImageSlide_SelectedClip[obj_index] = Gui_ImageSlide_Hover
						RedrawImageSlide(obj_index)
						'Print Gui_ImageSlide_SelectedClip[obj_index]
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_HOLD Then
						'mouse is down before going over button
						Return
					ElseIf EVENT_TYPE = IMAGESLIDE_PRESSED And MOUSE_STATE = MOUSE_HOLD Then
						Return
					ElseIf EVENT_TYPE = IMAGESLIDE_PRESSED Or EVENT_TYPE = IMAGESLIDE_RELEASED Then
						EVENT_TYPE = 0
						Return
					End If
				Case GUI_TYPE_TAB
					If EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_PRESSED Then
						EVENT_TYPE = TAB_SWITCH
						EVENT_ID = i
						Gui_TabSwitch(i, mx)
						Return
					ElseIf EVENT_TYPE = TAB_SWITCH Then
						EVENT_TYPE = 0
					End If
				Case GUI_TYPE_SURFACE
					s_panel_index = Gui_Element_Index[ Gui_Surface_Panel[obj_index] ]
					Gui_Surface_MouseX[obj_index] = mx - Gui_Surface_X[obj_index] - Gui_Panel_X[ s_panel_index ]
					Gui_Surface_MouseY[obj_index] = my - Gui_Surface_Y[obj_index] - Gui_Panel_Y[ s_panel_index ]
					If (EVENT_TYPE = SURFACE_PRESSED Or EVENT_TYPE = SURFACE_RELEASED) And EVENT_ID <> i Then
						'do nothing and continue looping
					ElseIf EVENT_TYPE = SURFACE_PRESSED And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_RELEASED Then
						EVENT_TYPE = SURFACE_RELEASED
						EVENT_ID = i
						s_panel_index = Gui_Element_Index[ Gui_Surface_Panel[obj_index] ]
						Gui_Surface_MouseX[obj_index] = mx - Gui_Surface_X[obj_index] - Gui_Panel_X[ s_panel_index ]
						Gui_Surface_MouseY[obj_index] = my - Gui_Surface_Y[obj_index] - Gui_Panel_Y[ s_panel_index ]
						If Gui_Surface_MouseX[obj_index] < 0 Or Gui_Surface_MouseX[obj_index] >= Gui_Surface_W[obj_index] Then
							Gui_Surface_MouseX[obj_index] = 0
						End If
						If Gui_Surface_MouseY[obj_index] < 0 Or Gui_Surface_MouseY[obj_index] >= Gui_Surface_H[obj_index] Then
							Gui_Surface_MouseY[obj_index] = 0
						End If
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_PRESSED Then
						EVENT_TYPE = SURFACE_PRESSED
						EVENT_ID = i
						s_panel_index = Gui_Element_Index[ Gui_Surface_Panel[obj_index] ]
						Gui_Surface_MouseX[obj_index] = mx - Gui_Surface_X[obj_index] - Gui_Panel_X[ s_panel_index ]
						Gui_Surface_MouseY[obj_index] = my - Gui_Surface_Y[obj_index] - Gui_Panel_Y[ s_panel_index ]
						If Gui_Surface_MouseX[obj_index] < 0 Or Gui_Surface_MouseX[obj_index] >= Gui_Surface_W[obj_index] Then
							Gui_Surface_MouseX[obj_index] = 0
						End If
						If Gui_Surface_MouseY[obj_index] < 0 Or Gui_Surface_MouseY[obj_index] >= Gui_Surface_H[obj_index] Then
							Gui_Surface_MouseY[obj_index] = 0
						End If
						Return
					ElseIf EVENT_TYPE = 0 And IsOnObject(i,mx,my) And MOUSE_STATE = MOUSE_HOLD Then
						'mouse is down before going over button
						Return
					ElseIf EVENT_TYPE = SURFACE_PRESSED And MOUSE_STATE = MOUSE_HOLD Then
						s_panel_index = Gui_Element_Index[ Gui_Surface_Panel[obj_index] ]
						Gui_Surface_MouseX[obj_index] = mx - Gui_Surface_X[obj_index] - Gui_Panel_X[ s_panel_index ]
						Gui_Surface_MouseY[obj_index] = my - Gui_Surface_Y[obj_index] - Gui_Panel_Y[ s_panel_index ]
						If Gui_Surface_MouseX[obj_index] < 0 Or Gui_Surface_MouseX[obj_index] >= Gui_Surface_W[obj_index] Then
							Gui_Surface_MouseX[obj_index] = 0
						End If
						If Gui_Surface_MouseY[obj_index] < 0 Or Gui_Surface_MouseY[obj_index] >= Gui_Surface_H[obj_index] Then
							Gui_Surface_MouseY[obj_index] = 0
						End If
						Return
					ElseIf EVENT_TYPE = SURFACE_PRESSED Or EVENT_TYPE = SURFACE_RELEASED Then
						EVENT_TYPE = 0
						Return
					End If
				End Select
			End If
		Next
	End If
End Sub


Sub Gui_DrawPanel(panel)
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	panel_index = Gui_Element_Index[panel]
	panel_image = Gui_Panel_Image[panel_index]
	panel_w = Gui_Panel_W[panel_index]
	panel_h = Gui_Panel_H[panel_index]
	SetColor(PANEL_BKG_VALUE)
	RectFill(0, 0, panel_w, panel_h)
	For i = 0 to MAX_PANEL_OBJECTS-1
		If Gui_Panel_Object_Exists[panel_index, i] Then
			obj_index = Gui_Element_Index[ Gui_Panel_Object_ID[panel_index, i] ]
			obj_id = Gui_Panel_Object_ID[panel_index, i]
			Select Case Gui_Panel_Object_Type[panel_index, i]
			Case GUI_TYPE_BUTTON
				DrawImage(Gui_Button_Image[obj_index, Gui_Button_Current_Image[obj_index] ], Gui_Button_X[obj_index], Gui_Button_Y[obj_index] )
			Case GUI_TYPE_DROPDOWN
				DrawImage(Gui_DropDown_Image[obj_index, Gui_DropDown_Current_Image[obj_index]], Gui_DropDown_X[obj_index], Gui_DropDown_Y[obj_index] )
			Case GUI_TYPE_LISTBOX
				DrawImage(Gui_ListBox_Image[obj_index], Gui_ListBox_X[obj_index], Gui_ListBox_Y[obj_index] )
				sx = (Gui_ListBox_X[obj_index] + Gui_ListBox_W[obj_index]) - GUI_LISTBOX_MIN_W
				sy = Gui_ListBox_Y[obj_index]
				sh = Gui_ListBox_H[obj_index] / 4
				For scroll_index = 0 to 3
					'If i = 3 Then
					If Gui_ListBox_ScrollBar_Action[scroll_index] and EVENT_ID = obj_id Then
						'print scroll_index
						DrawImage(Gui_ListBox_ScrollBar_Image[obj_index, scroll_index+4], sx, (scroll_index * sh) + sy)
					Else
						DrawImage(Gui_ListBox_ScrollBar_Image[obj_index, scroll_index], sx, (scroll_index * sh) + sy)
					End If
				Next
			Case GUI_TYPE_TEXTFIELD
				If Gui_TextField_isDynamic[obj_index] Then
					RectFill(Gui_TextField_X[obj_index], Gui_TextField_Y[obj_index], Gui_TextField_W[obj_index], Gui_TextField_H[obj_index])
					SetColor(RGB(20,20,20))
					Font(GUI_FONT)
					DrawText(Gui_TextField_Value$[obj_index]+" ", Gui_TextField_X[obj_index], Gui_TextField_Y[obj_index])
					SetColor(PANEL_BKG_VALUE)
				Else
					DrawImage(Gui_TextField_Image[obj_index], Gui_TextField_X[obj_index], Gui_TextField_Y[obj_index] )
				End If
			Case GUI_TYPE_CHECKBOX
				DrawImage(Gui_CheckBox_Image[obj_index, Gui_CheckBox_Current_Image[obj_index] ], Gui_CheckBox_X[obj_index], Gui_CheckBox_Y[obj_index] )
			Case GUI_TYPE_LABEL
				DrawImage(Gui_Label_Image[obj_index], Gui_Label_X[obj_index], Gui_Label_Y[obj_index] )
			Case GUI_TYPE_IMAGECLIP
				DrawImage(Gui_ImageClip_Image[obj_index], Gui_ImageClip_X[obj_index], Gui_ImageClip_Y[obj_index] )
			Case GUI_TYPE_IMAGESLIDE
				DrawImage(Gui_ImageSlide_Image[obj_index], Gui_ImageSlide_X[obj_index], Gui_ImageSlide_Y[obj_index] )
			Case GUI_TYPE_SURFACE
				DrawImage(Gui_Surface_Image[obj_index], Gui_Surface_X[obj_index], Gui_Surface_Y[obj_index] )
			End Select
		End If
	Next
	If ImageExists(panel_image) Then
		DeleteImage(panel_image)
	End If
	CanvasClip(panel_image, 0, 0, panel_w, panel_h, 1)
	Canvas(GUI_WIN_CANVAS)
	DrawImage(panel_image, Gui_Panel_X[panel_index], Gui_Panel_Y[panel_index])
End Sub

Sub Gui_DrawTabGroup(tab_group)
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	tab_index = Gui_Element_Index[tab_group]
	tab_w = Gui_TabGroup_W[tab_index] / Gui_TabGroup_TabCount[tab_index]
	dim tab_image
	
	If Gui_TabGroup_TabCount[tab_index] > 0 Then
		For i = 0 to Gui_TabGroup_TabCount[tab_index]-1
			If i = Gui_TabGroup_ActiveTab[tab_index] Then
				tab_image = Gui_TabGroup_Tab_Image[tab_index,i,0]
			Else
				tab_image = Gui_TabGroup_Tab_Image[tab_index,i,1]
			End If
			DrawImage(tab_image, tab_w * i, 0)
		Next
		
		
	End If
	t = Gui_GetFreeImage
	CanvasClip(t, 0, 0, Gui_TabGroup_W[tab_index], Gui_TabGroup_H[tab_index], 1)
	Canvas(GUI_WIN_CANVAS)
	DrawImage(t, Gui_TabGroup_X[tab_index], Gui_TabGroup_Y[tab_index])
	DeleteImage(t)
End Sub

Sub DrawDropDownMenu()
	d_index = Gui_Element_Index[EVENT_ID]
	panel_id = Gui_DropDown_Panel[d_index]
	panel_index = Gui_Element_Index[panel_id]
	dx = Gui_Panel_X[panel_index] + Gui_DropDown_X[d_index]
	dy = Gui_Panel_Y[panel_index] + Gui_DropDown_Y[d_index] + Gui_DropDown_H[d_index]
	DrawImage(Gui_DropDown_Image[d_index, 2], dx, dy)
	If Gui_DropDown_Highlighted_Index >= 0 And Gui_DropDown_Highlighted_Index <= Gui_DropDown_Count[d_index] Then
		SetColor(GUI_DROPDOWN_HIGHLIGHT_COLOR)
		RectFill(dx, dy + (Gui_DropDown_Highlighted_Index*GUI_FONT_H), Gui_DropDown_W[d_index], GUI_FONT_H)
	End If
End Sub

Function Gui_Update()
	win = gui_current_win
	If win < 0 Then
		win = 0
	End If
	If WindowHasMouseFocus(win) Then
		Gui_PollEvents
	End If
	Canvas(GUI_WIN_CANVAS)
	ClearCanvas
	For i = 0 to MAX_PANELS-1
		If Gui_Window_Panel_Exists[win, i] And Gui_Element_Active[ Gui_Window_Panel_ID[win, i] ] Then
			Select Case Gui_Window_Panel_Type[win, i]
			Case GUI_TYPE_PANEL
				Gui_DrawPanel(Gui_Window_Panel_ID[win, i])
			Case GUI_TYPE_TAB
				Gui_DrawTabGroup(Gui_Window_Panel_ID[win, i])
			End Select
		End If
	Next
	
	If GUI_STATE = GUI_STATE_DROPDOWN_OPEN Then
		Canvas(GUI_WIN_CANVAS)
		DrawDropDownMenu
		Canvas(GUI_TMP_CANVAS)
	End If
	
	Update
	Return True
End Function

Function Gui_Exclusive_Update(p)
	win = gui_current_win
	If win < 0 Then
		win = 0
	End If
	Gui_PollEvents
	Canvas(GUI_WIN_CANVAS)
	
	Gui_DrawPanel(p)
	
	If GUI_STATE = GUI_STATE_DROPDOWN_OPEN Then
		Canvas(GUI_WIN_CANVAS)
		DrawDropDownMenu
		Canvas(GUI_TMP_CANVAS)
	End If
	
	Update
	Return True
End Function

'EVENT FUNCTIONS

Function Gui_Button_Clicked(id)
	If EVENT_ID = id And EVENT_TYPE = BUTTON_RELEASED Then
		Return True
	End If
	Return False
End Function

Function Gui_Button_Down(id)
	If EVENT_ID = id And EVENT_TYPE = BUTTON_PRESSED Then
		Return True
	End If
	Return False
End Function

Function Gui_Button_Up(id)
	If EVENT_ID = id And Not EVENT_TYPE = BUTTON_PRESSED Then
		Return True
	End If
	Return False
End Function

Function Gui_TabGroup_TabChanged(id)
	If EVENT_ID = id And EVENT_TYPE = TAB_SWITCH Then
		Return True
	End If
	Return False
End Function

Function Gui_TabGroup_GetActiveTab(id)
	tab_index = Gui_Element_Index[id]
	Return Gui_TabGroup_ActiveTab[tab_index]
End Function

Function Gui_DropDown_GetSelectedItem(id)
	d_index = Gui_Element_Index[id]
	If Gui_DropDown_Exists[d_index] Then
		Return Gui_DropDown_Selected_Item[d_index]
	End If
	Return -1
End Function

Function Gui_DropDown_SetSelectedItem(id, item_num)
	d_index = Gui_Element_Index[id]
	If Gui_DropDown_Exists[d_index] Then
		Gui_DropDown_Selected_Item[d_index] = item_num
		RedrawDropDownSelected(d_index)
		Return True
	End If
	Return False
End Function

Function Gui_DropDown_GetValue$(id, item_num)
	d_index = Gui_Element_Index[id]
	If Gui_DropDown_Exists[d_index] And item_num < Gui_DropDown_Count[d_index] Then
		Return Gui_DropDown_Value$[d_index, item_num]
	End If
	Return ""
End Function

Function Gui_DropDown_Search(id, txt$)
	d_index = Gui_Element_Index[id]
	If Gui_DropDown_Exists[d_index] Then
		For i = 0 to Gui_DropDown_Count[d_index]-1
			If Gui_DropDown_Value$[d_index, i] = txt$ Then
				Return i
			End If
		Next
	End If
	Return -1
End Function

Function Gui_DropDown_SetValue(id, item_num, txt$)
	d_index = Gui_Element_Index[id]
	If Gui_DropDown_Exists[d_index] And item_num < Gui_DropDown_Count[d_index] Then
		Gui_DropDown_Value$[d_index, item_num] = txt$
		Return True
	End If
	Return False
End Function

Function Gui_ListBox_ItemChanged(lbox_id)
	If EVENT_TYPE = LISTBOX_ITEM_SELECT And EVENT_ID = lbox_id Then
		Return True
	End If
	Return False
End Function

Function Gui_ListBox_GetSelectedItem(lbox_id)
	lbox_index = Gui_Element_Index[lbox_id]
	If Gui_ListBox_Exists[lbox_index] Then
		Return Gui_ListBox_Selected_Item[lbox_index]
	End If
	Return -1
End Function

Function Gui_ListBox_SetSelectedItem(lbox_id, item_num)
	lbox_index = Gui_Element_Index[lbox_id]
	If Gui_ListBox_Exists[lbox_index] And item_num < Gui_ListBox_Count[lbox_index] Then
		Gui_ListBox_Selected_Item[lbox_index] = item_num
		Return True
	End If
	Return False
End Function

Function Gui_ListBox_GetValue$(lbox_id, item_num)
	lbox_index = Gui_Element_Index[lbox_id]
	If Gui_ListBox_Exists[lbox_index] And item_num < Gui_ListBox_Count[lbox_index] Then
		Return Gui_ListBox_Value$[lbox_index, item_num]
	End If
	Return ""
End Function

Function Gui_ListBox_SetValue(lbox_id, item_num, l_value$)
	lbox_index = Gui_Element_Index[lbox_id]
	If Gui_ListBox_Exists[lbox_index] And item_num < Gui_ListBox_Count[lbox_index] Then
		Gui_ListBox_Value$[lbox_index, item_num] = l_value$
		Return True
	End If
	Return False
End Function

Function Gui_TextField_Return(tfield_id)
	If EVENT_TYPE = TEXTFIELD_RETURN And EVENT_ID = tfield_id Then
		Return True
	End If
	Return False
End Function

Function Gui_TextField_GetValue$(tfield_id)
	tfield_index = Gui_Element_Index[tfield_id]
	If Gui_TextField_Exists[tfield_index] Then
		Return Gui_TextField_Value$[tfield_index]
	End If
	Return ""
End Function

Function Gui_TextField_SetValue(tfield_id, t_value$)
	tfield_index = Gui_Element_Index[tfield_id]
	If Gui_TextField_Exists[tfield_index] Then
		Gui_TextField_Value$[tfield_index] = t_value$
		If Not Gui_TextField_isDynamic[tfield_index] Then
			RedrawTextField(tfield_index)
		End If
		Return True
	End If
	Return False
End Function

Function Gui_TextField_SetPasswordField(tfield_id, attribute_value)
	tfield_index = Gui_Element_Index[tfield_id]
	If Gui_TextField_Exists[tfield_index] Then
		Gui_TextField_isPassword[tfield_index] = attribute_value
		RedrawTextField(tfield_index)
		Return True
	End If
	Return False
End Function

Function Gui_TextField_GetPasswordFieldAttribute(tfield_id)
	tfield_index = Gui_Element_Index[tfield_id]
	If Gui_TextField_Exists[tfield_index] Then
		Return Gui_TextField_isPassword[tfield_index]
	End If
	Return False
End Function

Function Gui_CheckBox_GetValue(cb_id)
	cb_index = Gui_Element_Index[cb_id]
	If Gui_CheckBox_Exists[cb_index] Then
		Return Gui_CheckBox_Value[cb_index]
	End If
	Return 0
End Function

Function Gui_CheckBox_SetValue(cb_id, cb_value)
	cb_index = Gui_Element_Index[cb_id]
	If Gui_CheckBox_Exists[cb_index] Then
		Gui_CheckBox_Value[cb_index] = cb_value
		Select Case cb_value
		Case 0
			Gui_CheckBox_Current_Image[cb_index] = 0
		Default
			Gui_CheckBox_Current_Image[cb_index] = 2
		End Select
		Return True
	End If
	Return False
End Function

Function Gui_CheckBox_ValueChanged(cb_id)
	If EVENT_TYPE = CHECKBOX_RELEASED And EVENT_ID = cb_id Then
		Return True
	End If
	Return False
End Function

Function Gui_ImageClip_GetOffset_X(clip_id)
	clip_index = Gui_Element_Index[clip_id]
	If Gui_ImageClip_Exists[clip_index] Then
		Return Gui_ImageClip_Source_X[clip_index]
	End If
End Function

Function Gui_ImageClip_GetOffset_Y(clip_id)
	clip_index = Gui_Element_Index[clip_id]
	If Gui_ImageClip_Exists[clip_index] Then
		Return Gui_ImageClip_Source_Y[clip_index]
	End If
End Function

Function Gui_ImageClip_GetOffset_W(clip_id)
	clip_index = Gui_Element_Index[clip_id]
	If Gui_ImageClip_Exists[clip_index] Then
		Return Gui_ImageClip_Source_W[clip_index]
	End If
End Function

Function Gui_ImageClip_GetOffset_H(clip_id)
	clip_index = Gui_Element_Index[clip_id]
	If Gui_ImageClip_Exists[clip_index] Then
		Return Gui_ImageClip_Source_H[clip_index]
	End If
End Function

Function Gui_ImageClip_GetImage(clip_id)
	clip_index = Gui_Element_Index[clip_id]
	If Gui_ImageClip_Exists[clip_index] Then
		Return Gui_ImageClip_Source_Image[clip_index]
	End If
End Function

Function Gui_ImageSlide_SetSelectedClip(slide_id, clip_num)
	slide_index = Gui_Element_Index[slide_id]
	If Gui_ImageSlide_Exists[slide_index] And Gui_ImageSlide_Count[slide_index] > clip_num Then
		Gui_ImageSlide_SelectedClip[slide_index] = clip_num
	End If
End Function

Function Gui_ImageSlide_GetSelectedClip(slide_id)
	slide_index = Gui_Element_Index[slide_id]
	If Gui_ImageSlide_Exists[slide_index] Then
		Return Gui_ImageSlide_SelectedClip[slide_index]
	End If
End Function

Function Gui_ImageSlide_SetImageClip(slide_id, clip_num, clip_id)
	slide_index = Gui_Element_Index[slide_id]
	clip_index = Gui_Element_Index[clip_id]
	If Gui_ImageSlide_Exists[slide_index] And clip_num < Gui_ImageSlide_Count[slide_index] And Gui_ImageClip_Exists[clip_index] Then
		Gui_ImageSlide_ImageClip[slide_index, clip_num] = clip_id
		RedrawImageSlide(slide_index)
		Return True
	End If
End Function

Function Gui_ImageSlide_GetImageClip(slide_id, clip_num)
	slide_index = Gui_Element_Index[slide_id]
	If Gui_ImageSlide_Exists[slide_index] And clip_num < Gui_ImageSlide_Count[slide_index] Then
		Return Gui_ImageSlide_ImageClip[slide_index, clip_num]
	End If
	Return -1
End Function

Function Gui_ImageSlide_GetOffset_X(slide_id)
	slide_index = Gui_Element_Index[slide_id]
	If Gui_ImageSlide_Exists[slide_index] Then
		Return Gui_ImageSlide_Offset_X[slide_index]
	End If
End Function

Function Gui_ImageSlide_GetOffset_Y(slide_id)
	slide_index = Gui_Element_Index[slide_id]
	If Gui_ImageSlide_Exists[slide_index] Then
		Return Gui_ImageSlide_Offset_Y[slide_index]
	End If
End Function

Function Gui_Surface_Clicked(id)
	If EVENT_ID = id And EVENT_TYPE = SURFACE_RELEASED Then
		Return True
	End If
	Return False
End Function

Function Gui_Surface_Down(id)
	If EVENT_ID = id And EVENT_TYPE = SURFACE_PRESSED Then
		Return True
	End If
	Return False
End Function

Function Gui_Surface_Up(id)
	If EVENT_ID = id And Not EVENT_TYPE = SURFACE_PRESSED Then
		Return True
	End If
	Return False
End Function

Sub Gui_Surface_GetMouse(id, ByRef mx, ByRef my)
	surface_index = Gui_Element_Index[id]
	mx = Gui_Surface_MouseX[surface_index]
	my = Gui_Surface_MouseY[surface_index]
End Sub

Function Gui_Surface_MouseOver(id)
	surface_index = Gui_Element_Index[id]
	mx = Gui_Surface_MouseX[surface_index]
	my = Gui_Surface_MouseY[surface_index]
	If mx > 0 And mx < Gui_Surface_W[surface_index] And my > 0 And my < Gui_Surface_H[surface_index] Then
		Return True
	End If
	Return False
End Function

Sub Gui_Surface_DrawImage(id, img, x, y)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_DrawImage_Blit(id, img, x, y, sx, sy, sw, sh)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE_BLIT
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = sx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 5] = sy
	Gui_Surface_DrawCommand[surface_index, cmd_num, 6] = sw
	Gui_Surface_DrawCommand[surface_index, cmd_num, 7] = sh
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_DrawImage_Blit_Ex(id, img, x, y, w, h, sx, sy, sw, sh)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE_BLIT_EX
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = w
	Gui_Surface_DrawCommand[surface_index, cmd_num, 5] = h
	Gui_Surface_DrawCommand[surface_index, cmd_num, 6] = sx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 7] = sy
	Gui_Surface_DrawCommand[surface_index, cmd_num, 8] = sw
	Gui_Surface_DrawCommand[surface_index, cmd_num, 9] = sh
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_DrawImage_Rotate(id, img, x, y, angle)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE_ROTATE
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = angle
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_DrawImage_Rotate_Ex(id, img, x, y, sx, sy, sw, sh, angle)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE_ROTATE_EX
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = sx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 5] = sy
	Gui_Surface_DrawCommand[surface_index, cmd_num, 6] = sw
	Gui_Surface_DrawCommand[surface_index, cmd_num, 7] = sh
	Gui_Surface_DrawCommand[surface_index, cmd_num, 8] = angle
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_DrawImage_Zoom(id, img, x, y, zx, zy)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE_ZOOM
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = zx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 5] = zy
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_DrawImage_Zoom_Ex(id, img, x, y, sx, sy, sw, sh, zx, zy)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE_ZOOM_EX
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = sx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 5] = sy
	Gui_Surface_DrawCommand[surface_index, cmd_num, 6] = sw
	Gui_Surface_DrawCommand[surface_index, cmd_num, 7] = sh
	Gui_Surface_DrawCommand[surface_index, cmd_num, 8] = zx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 9] = zy
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_DrawImage_Rotozoom(id, img, x, y, angle, zx, zy)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE_ROTOZOOM
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = angle
	Gui_Surface_DrawCommand[surface_index, cmd_num, 5] = zx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 6] = zy
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_DrawImage_Rotozoom_Ex(id, img, x, y, sx, sy, sw, sh, angle, zx, zy)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE_ROTOZOOM_EX
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = sx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 5] = sy
	Gui_Surface_DrawCommand[surface_index, cmd_num, 6] = sw
	Gui_Surface_DrawCommand[surface_index, cmd_num, 7] = sh
	Gui_Surface_DrawCommand[surface_index, cmd_num, 8] = angle
	Gui_Surface_DrawCommand[surface_index, cmd_num, 9] = zx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 10] = zy
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_DrawImage_Flip(id, img, x, y, h, v)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE_FLIP
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = h
	Gui_Surface_DrawCommand[surface_index, cmd_num, 5] = v
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_DrawImage_Flip_Ex(id, img, x, y, sx, sy, sw, sh, h, v)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_DRAWIMAGE_FLIP_EX
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = img
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = sx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 5] = sy
	Gui_Surface_DrawCommand[surface_index, cmd_num, 6] = sw
	Gui_Surface_DrawCommand[surface_index, cmd_num, 7] = sh
	Gui_Surface_DrawCommand[surface_index, cmd_num, 8] = h
	Gui_Surface_DrawCommand[surface_index, cmd_num, 9] = v
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_Box(id, x, y, x2, y2)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_BOX
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = x2
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = y2
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_BoxFill(id, x, y, x2, y2)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_BOXFILL
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = x2
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = y2
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_Line(id, x, y, x2, y2)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_LINE
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = x2
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = y2
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_PSet(id, x, y)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_PSET
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_Rect(id, x, y, w, h)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_RECT
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = w
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = h
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_RectFill(id, x, y, w, h)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_RECTFILL
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = w
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = h
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_Circle(id, x, y, r)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_CIRCLE
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = r
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_CircleFill(id, x, y, r)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_CIRCLEFILL
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = r
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_Ellipse(id, x, y, rx, ry)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_ELLIPSE
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = rx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = ry
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_EllipseFill(id, x, y, rx, ry)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_ELLIPSEFILL
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_DrawCommand[surface_index, cmd_num, 3] = rx
	Gui_Surface_DrawCommand[surface_index, cmd_num, 4] = ry
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_Clear(id)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_CLEAR
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_FloodFill(id, x, y)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_FLOODFILL
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = x
	Gui_Surface_DrawCommand[surface_index, cmd_num, 2] = y
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_SetColor(id, color)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_SETCOLOR
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = color
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_SetClearColor(id, color)
	surface_index = Gui_Element_Index[id]
	cmd_num = Gui_Surface_NumCommands[surface_index]
	Gui_Surface_DrawCommand[surface_index, cmd_num, 0] = GUI_SURFACE_CMD_SETCLEARCOLOR
	Gui_Surface_DrawCommand[surface_index, cmd_num, 1] = color
	Gui_Surface_NumCommands[surface_index] = cmd_num + 1
End Sub

Sub Gui_Surface_Update(id)
	surface_index = Gui_Element_Index[id]
	cmd_count = Gui_Surface_NumCommands[surface_index]
	If cmd_count <= 0 Then
		Return
	End If
	s_panel_index = Gui_Element_Index[ Gui_Surface_Panel[surface_index] ]
	Gui_Surface_MouseX[surface_index] = MouseX - Gui_Surface_X[surface_index] - Gui_Panel_X[ s_panel_index ]
	Gui_Surface_MouseY[surface_index] = MouseY - Gui_Surface_Y[surface_index] - Gui_Panel_Y[ s_panel_index ]
	Canvas(GUI_TMP_CANVAS)
	ClearCanvas
	For i = 0 to cmd_count-1
		Select Case Gui_Surface_DrawCommand[surface_index, i, 0]
		Case GUI_SURFACE_CMD_DRAWIMAGE
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			DrawImage(img, x, y)
		Case GUI_SURFACE_CMD_DRAWIMAGE_BLIT
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			sx = Gui_Surface_DrawCommand[surface_index, i, 4]
			sy = Gui_Surface_DrawCommand[surface_index, i, 5]
			sw = Gui_Surface_DrawCommand[surface_index, i, 6]
			sh = Gui_Surface_DrawCommand[surface_index, i, 7]
			DrawImage_Blit(img, x, y, sx, sy, sw, sh)
		Case GUI_SURFACE_CMD_DRAWIMAGE_BLIT_EX
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			w = Gui_Surface_DrawCommand[surface_index, i, 4]
			h = Gui_Surface_DrawCommand[surface_index, i, 5]
			sx = Gui_Surface_DrawCommand[surface_index, i, 6]
			sy = Gui_Surface_DrawCommand[surface_index, i, 7]
			sw = Gui_Surface_DrawCommand[surface_index, i, 8]
			sh = Gui_Surface_DrawCommand[surface_index, i, 9]
			DrawImage_Blit_Ex(img, x, y, w, h, sx, sy, sw, sh)
		Case GUI_SURFACE_CMD_DRAWIMAGE_ROTATE
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			angle = Gui_Surface_DrawCommand[surface_index, i, 4]
			DrawImage_Rotate(img, x, y, angle)
		Case GUI_SURFACE_CMD_DRAWIMAGE_ROTATE_EX
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			sx = Gui_Surface_DrawCommand[surface_index, i, 4]
			sy = Gui_Surface_DrawCommand[surface_index, i, 5]
			sw = Gui_Surface_DrawCommand[surface_index, i, 6]
			sh = Gui_Surface_DrawCommand[surface_index, i, 7]
			angle = Gui_Surface_DrawCommand[surface_index, i, 8]
			DrawImage_Rotate_Ex(img, x, y, sx, sy, sw, sh, angle)
		Case GUI_SURFACE_CMD_DRAWIMAGE_ZOOM
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			zx = Gui_Surface_DrawCommand[surface_index, i, 4]
			zy = Gui_Surface_DrawCommand[surface_index, i, 5]
			DrawImage_Zoom(img, x, y, zx, zy)
		Case GUI_SURFACE_CMD_DRAWIMAGE_ZOOM_EX
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			sx = Gui_Surface_DrawCommand[surface_index, i, 4]
			sy = Gui_Surface_DrawCommand[surface_index, i, 5]
			sw = Gui_Surface_DrawCommand[surface_index, i, 6]
			sh = Gui_Surface_DrawCommand[surface_index, i, 7]
			zx = Gui_Surface_DrawCommand[surface_index, i, 8]
			zy = Gui_Surface_DrawCommand[surface_index, i, 9]
			DrawImage_Zoom_Ex(img, x, y, sx, sy, sw, sh, zx, zy)
		Case GUI_SURFACE_CMD_DRAWIMAGE_ROTOZOOM
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			angle = Gui_Surface_DrawCommand[surface_index, i, 4]
			zx = Gui_Surface_DrawCommand[surface_index, i, 5]
			zy = Gui_Surface_DrawCommand[surface_index, i, 6]
			DrawImage_Rotozoom(img, x, y, angle, zx, zy)
		Case GUI_SURFACE_CMD_DRAWIMAGE_ROTOZOOM_EX
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			sx = Gui_Surface_DrawCommand[surface_index, i, 4]
			sy = Gui_Surface_DrawCommand[surface_index, i, 5]
			sw = Gui_Surface_DrawCommand[surface_index, i, 6]
			sh = Gui_Surface_DrawCommand[surface_index, i, 7]
			angle = Gui_Surface_DrawCommand[surface_index, i, 8]
			zx = Gui_Surface_DrawCommand[surface_index, i, 9]
			zy = Gui_Surface_DrawCommand[surface_index, i, 10]
			DrawImage_Rotozoom_Ex(img, x, y, sx, sy, sw, sh, angle, zx, zy)
		Case GUI_SURFACE_CMD_DRAWIMAGE_FLIP
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			h = Gui_Surface_DrawCommand[surface_index, i, 4]
			v = Gui_Surface_DrawCommand[surface_index, i, 5]
			DrawImage_Flip(img, x, y, h, v)
		Case GUI_SURFACE_CMD_DRAWIMAGE_FLIP_EX
			img = Gui_Surface_DrawCommand[surface_index, i, 1]
			x = Gui_Surface_DrawCommand[surface_index, i, 2]
			y = Gui_Surface_DrawCommand[surface_index, i, 3]
			sx = Gui_Surface_DrawCommand[surface_index, i, 4]
			sy = Gui_Surface_DrawCommand[surface_index, i, 5]
			sw = Gui_Surface_DrawCommand[surface_index, i, 6]
			sh = Gui_Surface_DrawCommand[surface_index, i, 7]
			h = Gui_Surface_DrawCommand[surface_index, i, 8]
			v = Gui_Surface_DrawCommand[surface_index, i, 9]
			DrawImage_Flip_Ex(img, x, y, sx, sy, sw, sh, h, v)
		Case GUI_SURFACE_CMD_BOX
			x1 = Gui_Surface_DrawCommand[surface_index, i, 1]
			y1 = Gui_Surface_DrawCommand[surface_index, i, 2]
			x2 = Gui_Surface_DrawCommand[surface_index, i, 3]
			y2 = Gui_Surface_DrawCommand[surface_index, i, 4]
			Box(x1, y1, x2, y2)
		Case GUI_SURFACE_CMD_BOXFILL
			x1 = Gui_Surface_DrawCommand[surface_index, i, 1]
			y1 = Gui_Surface_DrawCommand[surface_index, i, 2]
			x2 = Gui_Surface_DrawCommand[surface_index, i, 3]
			y2 = Gui_Surface_DrawCommand[surface_index, i, 4]
			BoxFill(x1, y1, x2, y2)
		Case GUI_SURFACE_CMD_LINE
			x1 = Gui_Surface_DrawCommand[surface_index, i, 1]
			y1 = Gui_Surface_DrawCommand[surface_index, i, 2]
			x2 = Gui_Surface_DrawCommand[surface_index, i, 3]
			y2 = Gui_Surface_DrawCommand[surface_index, i, 4]
			Line(x1, y1, x2, y2)
		Case GUI_SURFACE_CMD_PSET
			x = Gui_Surface_DrawCommand[surface_index, i, 1]
			y = Gui_Surface_DrawCommand[surface_index, i, 2]
			PSet(x, y)
		Case GUI_SURFACE_CMD_RECT
			x = Gui_Surface_DrawCommand[surface_index, i, 1]
			y = Gui_Surface_DrawCommand[surface_index, i, 2]
			w = Gui_Surface_DrawCommand[surface_index, i, 3]
			h = Gui_Surface_DrawCommand[surface_index, i, 4]
			Rect(x, y, w, h)
		Case GUI_SURFACE_CMD_RECTFILL
			x = Gui_Surface_DrawCommand[surface_index, i, 1]
			y = Gui_Surface_DrawCommand[surface_index, i, 2]
			w = Gui_Surface_DrawCommand[surface_index, i, 3]
			h = Gui_Surface_DrawCommand[surface_index, i, 4]
			RectFill(x, y, w, h)
		Case GUI_SURFACE_CMD_CIRCLE
			x = Gui_Surface_DrawCommand[surface_index, i, 1]
			y = Gui_Surface_DrawCommand[surface_index, i, 2]
			r = Gui_Surface_DrawCommand[surface_index, i, 3]
			Circle(x, y, r)
		Case GUI_SURFACE_CMD_CIRCLEFILL
			x = Gui_Surface_DrawCommand[surface_index, i, 1]
			y = Gui_Surface_DrawCommand[surface_index, i, 2]
			r = Gui_Surface_DrawCommand[surface_index, i, 3]
			CircleFill(x, y, r)
		Case GUI_SURFACE_CMD_ELLIPSE
			x = Gui_Surface_DrawCommand[surface_index, i, 1]
			y = Gui_Surface_DrawCommand[surface_index, i, 2]
			rx = Gui_Surface_DrawCommand[surface_index, i, 3]
			ry = Gui_Surface_DrawCommand[surface_index, i, 4]
			Ellipse(x, y, rx, ry)
		Case GUI_SURFACE_CMD_ELLIPSEFILL
			x = Gui_Surface_DrawCommand[surface_index, i, 1]
			y = Gui_Surface_DrawCommand[surface_index, i, 2]
			rx = Gui_Surface_DrawCommand[surface_index, i, 3]
			ry = Gui_Surface_DrawCommand[surface_index, i, 4]
			EllipseFill(x, y, rx, ry)
		Case GUI_SURFACE_CMD_CLEAR
			'ClearCanvas()
			SetColor(GUI_SURFACE_CLEAR_COLOR)
			RectFill(0, 0, Gui_Surface_W[surface_index], Gui_Surface_H[surface_index])
		Case GUI_SURFACE_CMD_FLOODFILL
			x = Gui_Surface_DrawCommand[surface_index, i, 1]
			y = Gui_Surface_DrawCommand[surface_index, i, 2]
			FloodFill(x, y)
		Case GUI_SURFACE_CMD_SETCOLOR
			c = Gui_Surface_DrawCommand[surface_index, i, 1]
			SetColor(c)
		Case GUI_SURFACE_CMD_SETCLEARCOLOR
			c = Gui_Surface_DrawCommand[surface_index, i, 1]
			GUI_SURFACE_CLEAR_COLOR = c
		End Select
	Next
	If ImageExists(Gui_Surface_Image[surface_index]) Then
		DeleteImage(Gui_Surface_Image[surface_index])
	End If
	Gui_Surface_NumCommands[surface_index] = 0
	CanvasClip(Gui_Surface_Image[surface_index], 0, 0, Gui_Surface_W[surface_index], Gui_Surface_H[surface_index], 1)
	SetClearColor(GUI_CLEAR_COLOR)
End Sub

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

'Create a throw away button because of a bug that happens to the first button pressed
Gui_Init
