Function Gui_GetFreeID() 'Get the next available element id; useful for creating a custom widget; Returns -1 on failure

Function Gui_WindowOpen(title$, x, y, w, h) 'Opens a window and returns the index of the window

Function Gui_GetFreeImage() 'Returns the next available image slot or -1 on failure

Function Gui_LoadImage(img_file$) 'Loads an image and returns the image slot on success and -1 on failure

Sub Gui_SetPanelActive(panel, flag) 'Used to determine whether the gui update will read events from a panel; mostly used in the background

Function Gui_Window_AddPanel(win, panel, x, y) 'Adds a panel to a window; panels must be added to the window before they can be added to a tab group

Function Gui_CreatePanel(w, h) 'Creates a panel; returns id of the new panel or -1 on failure

Function Gui_Panel_AddObject(panel, obj, x, y) 'Adds an object to a panel; can't add a panel or tab group to a panel; returns true if added or false if not

Function Gui_Update() 'Updates the screen and polls events


'EVENT FUNCTIONS

'BUTTONS
Function Gui_CreateButton(txt$, w, h) 'Creates a button; returns id of the button or -1 on failure

Function Gui_Button_Clicked(button_id) 'Returns true if the button was clicked

Function Gui_Button_Down(button_id) 'Returns true if the button is down

Function Gui_Button_Up(button_id) 'Returns true if the button is up


'TAB GROUPS
Sub Gui_SetTabGroupActive(id, flag) 'Used to determine whether the gui update will read events from the panels in the group; mostly used in the background

Function Gui_Window_AddTabGroup(win, tab_group, x, y) 'Adds a tab group to a window

Function Gui_CreateTabGroup(w, h) 'Creates a new tab group; returns id of the new tab group or -1 on failure

Function Gui_TabGroup_AddTab(tabgroup_id, txt$) 'Add a tab to a tab group; returns the tab number

Function Gui_TabGroup_Tab_AddObject(tab_group, tab_num, obj_id) 'Adds an object to a tab group; object must be a panel or another tab group

Function Gui_TabSwitch(id, x) 'Switch tabs; mostly used in the background


Function Gui_TabGroup_TabChanged(tabgoup_id) 'Returns true if the tab group has switched to a different tab

Function Gui_TabGroup_GetActiveTab(tabgroup_id) 'Returns the active tab in the tab group


'DROPDOWN LISTS
Function Gui_CreateDropDown(w, h) 'Creates a drop down selection; returns id of the new selection or -1 on failure; drop downs do not scroll

Function Gui_DropDown_AddItem(dropdown_id, value$) 'Adds an item to a drop down selection; currently you can only add up to 12 values

Function Gui_DropDown_RemoveItem(dropdown_id, item_num) 'Removes given item number from listbox

Function Gui_DropDown_GetSelectedItem(dropdown_id) 'Returns the index of the selected item

Function Gui_DropDown_SetSelectedItem(dropdown_id, item_num) 'Sets the selected item

Function Gui_DropDown_GetValue$(dropdown_id, item_num) 'Returns the value of a item

Function Gui_DropDown_SetValue(dropdown_id, item_num, txt$) 'Sets the value of an item


'LISTBOXES
Function Gui_CreateListBox(w, h) 'Create a list box; returns id or -1 on failure

Function Gui_ListBox_AddItem(lbox, item$) 'Adds and item to a list box; returns item number

Function Gui_ListBox_Clear(lbox) 'Clears everything out of the list box

Function Gui_ListBox_RemoveItem(lbox, item_num) 'Removes given item from listbox

Sub Gui_ListBox_Scroll(lbox_id, i) 'Scroll through a list box; mostly used in the background

Sub Gui_ListBox_PageScroll(lbox_id, i) 'Scroll a given number of pages in a list box

Function Gui_ListBox_ItemChanged(lbox_id) 'Returns true if the selected item changed

Function Gui_ListBox_GetSelectedItem(lbox_id) 'Returns the selected item in a list box

Function Gui_ListBox_SetSelectedItem(lbox_id, item_num) 'Sets the selected item in a list box

Function Gui_ListBox_GetValue$(lbox_id, item_num) 'Gets the value of an item in a list box

Function Gui_ListBox_SetValue(lbox_id, item_num, l_value$) 'Sets the value of an item in a list box


'TEXTFIELDS AND LABELS
Function Gui_CreateLabel(txt$, w, h) 'Creates a label; returns id of the label or -1 on failure

Function Gui_CreateTextField(w, h) 'Create a text field; Returns id or -1 on failure; Textfields are single line and all other events are locked until you press enter

Function Gui_CreateDynamicTextField(w, h) 'Create a dynamic label; Returns id or -1 on failure

Function Gui_TextField_Return(tfield_id) 'Returns true if the ENTER button was pressed from a text field

Function Gui_TextField_GetValue$(tfield_id) 'Returns the value of a text field

Function Gui_TextField_SetValue(tfield_id, t_value$) 'Sets the value of a text field


'CHECKBOXES
Function Gui_CreateCheckBox(w, h) 'Creates a check box; returns id of the checkbox of -1 on failure

Function Gui_CheckBox_GetValue(cb_id) 'Returns the value of a check box

Function Gui_CheckBox_SetValue(cb_id, cb_value) 'Sets the value of a check box

Function Gui_CheckBox_ValueChanged(cb_id) 'Returns true if the value of the check box changed and false if not


'IMAGE CLIPS
Function Gui_CreateImageClip(img_slot, w, h, src_w, src_h) 'Creates a image clip; returns id of the image clip or -1 on failure

Function Gui_ImageClip_SetOffset(clip_id, x, y) 'Sets the offset of the image clip; returns true if the offset could be set and false if not

Function Gui_ImageClip_SetSource(clip_id, src_img) 'Sets the source image of the image clip

Function Gui_ImageClip_SetSourceSize(clip_id, src_w, src_h) 'Sets the size of the portion of the source image captured

Function Gui_ImageClip_GetOffset_X(clip_id) 'Returns the x offset in the image clip

Function Gui_ImageClip_GetOffset_Y(clip_id) 'Returns the y offset in the image clip

Function Gui_ImageClip_GetOffset_W(clip_id) 'Returns the width of the image clip viewport

Function Gui_ImageClip_GetOffset_H(clip_id) 'Returns the height of the image clip viewport

Function Gui_ImageClip_GetImage(clip_id) 'Returns the image slot of the image clip


'IMAGE SLIDE
Function Gui_CreateImageSlide(w, h, clip_w, clip_h) 'Creates a image slide; returns id of image slide or -1 on failure

Function Gui_ImageSlide_AddImageClip(slide_id, clip_id) 'Add an image clip to an image slide; Returns true if the image clip was added and false if not

Function Gui_ImageSlide_SetOffset(slide_id, x, y) 'Sets the offset of the image slide; Returns true if offset could be set and false if not

Function Gui_ImageSlide_MoveOffset(slide_id, x, y) 'Sets offset of image slide relative to current offset; Returns true if offset could be set and false if not

Function Gui_ImageSlide_SetSelectedClip(slide_id, clip_num) 'Sets the selected clip in an image slide

Function Gui_ImageSlide_GetSelectedClip(slide_id) 'Returns the index of the selected clip in an image slide

Function Gui_ImageSlide_SetImageClip(slide_id, clip_num, clip_id) 'Sets the clip number in an image slide to a different image clip

Function Gui_ImageSlide_GetImageClip(slide_id, clip_num) 'Returns the id of the image clip at clip_num index in the image slide

Function Gui_ImageSlide_GetOffset_X(slide_id) 'Returns the x offset of an image slide

Function Gui_ImageSlide_GetOffset_Y(slide_id) 'Returns the y offset of an image slide


'SURFACES
Function Gui_CreateSurface(w, h) 'Create a drawing surface; Returns id or -1 on failure

Function Gui_Surface_Clicked(id) 'Returns true if the mouse was clicked inside a surface and false if not

Function Gui_Surface_Down(id) 'Returns true if the mouse is pressed down inside a surface and false if not

Function Gui_Surface_Up(id) 'Returns true if the mouse is not pressed down inside a surface and false if not

Sub Gui_Surface_GetMouse(id, ByRef mx, ByRef my) 'Gets the mouse position inside the surface

'All the following are the same as the rcbasic drawing commands but will draw to the drawing surface specified by id
Sub Gui_Surface_DrawImage(id, img, x, y)

Sub Gui_Surface_DrawImage_Blit(id, img, x, y, sx, sy, sw, sh)

Sub Gui_Surface_DrawImage_Blit_Ex(id, img, x, y, w, h, sx, sy, sw, sh)

Sub Gui_Surface_DrawImage_Rotate(id, img, x, y, angle)

Sub Gui_Surface_DrawImage_Rotate_Ex(id, img, x, y, sx, sy, sw, sh, angle)

Sub Gui_Surface_DrawImage_Zoom(id, img, x, y, zx, zy)

Sub Gui_Surface_DrawImage_Zoom_Ex(id, img, x, y, sx, sy, sw, sh, zx, zy)

Sub Gui_Surface_DrawImage_Rotozoom(id, img, x, y, angle, zx, zy)

Sub Gui_Surface_DrawImage_Rotozoom_Ex(id, img, x, y, sx, sy, sw, sh, angle, zx, zy)

Sub Gui_Surface_DrawImage_Flip(id, img, x, y, h, v)

Sub Gui_Surface_DrawImage_Flip_Ex(id, img, x, y, sx, sy, sw, sh, h, v)

Sub Gui_Surface_Box(id, x, y, x2, y2)

Sub Gui_Surface_BoxFill(id, x, y, x2, y2)

Sub Gui_Surface_Line(id, x, y, x2, y2)

Sub Gui_Surface_PSet(id, x, y)

Sub Gui_Surface_Rect(id, x, y, w, h)

Sub Gui_Surface_RectFill(id, x, y, w, h)

Sub Gui_Surface_Circle(id, x, y, r)

Sub Gui_Surface_CircleFill(id, x, y, r)

Sub Gui_Surface_Ellipse(id, x, y, rx, ry)

Sub Gui_Surface_EllipseFill(id, x, y, rx, ry)

Sub Gui_Surface_Clear(id)

Sub Gui_Surface_FloodFill(id, x, y)

Sub Gui_Surface_SetColor(id, color)

Sub Gui_Surface_SetClearColor(id, color)

Sub Gui_Surface_Update(id)
