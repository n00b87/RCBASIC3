'---------------------------------------------------------------------------------
'	3D PERSPECTIVE DEMO
'	
'	AUTHOR: n00b ( AKA RODNEY CUNNINGHAM )
'	DESCRIPTION: REPLICATE SNES MODE 7 3D EFFECT
'
'	email: n00bskillz87@gmail.com
'
'	http://www.rcbasic.com
'	http://www.rcbasic.freeforums.net
'	http://www.github.com/n00b87
'
'	LICENSE: ZLIB ( BASICALLY DO WHATEVER YOU WANT WITH IT )
'
'---------------------------------------------------------------------------------
WINDOW_WIDTH = 640
WINDOW_HEIGHT = 480

WindowOpen(0, "MODE 7 DEMO", WINDOWPOS_CENTERED, WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 1)

CanvasOpen(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1)
CanvasOpen(1, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1)
CanvasOpen(2, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1)
SetCanvasVisible(1, False)

Dim BUFFER_BACK
Dim BUFFER_DISPLAY
Dim BKG_IMAGE
Dim DISPLAY_IMAGE
Dim BKG_IMAGE_W
Dim BKG_IMAGE_H
Dim BKG_CENTER_X
Dim BKG_CENTER_Y
Dim WINDOW_CENTER_X
Dim WINDOW_CENTER_Y
Dim pos_x
Dim pos_y
Dim pos_dir

BUFFER_BACK = 1
BUFFER_DISPLAY = 0

BKG_IMAGE = 0
DISPLAY_IMAGE = 1
MOBILE_BUTTONS_IMAGE = 2

WINDOW_CENTER_X = WINDOW_WIDTH/2
WINDOW_CENTER_Y = WINDOW_HEIGHT/2

z_inc = 0.05
zoom = 1

pos_x = 0
pos_y = 0
pos_dir = 200

Function CRadians(angle)
	Return angle * 0.0174533
End Function

Sub LoadTexture(img_file$)
	LoadImage(BKG_IMAGE, img_file)
	GetImageSize(BKG_IMAGE, BKG_IMAGE_W, BKG_IMAGE_H)
	BKG_CENTER_X = Int(BKG_IMAGE_W / 2)
	BKG_CENTER_Y = Int(BKG_IMAGE_H / 2)
End Sub


Canvas(2)
SetCanvasZ(2, 0)
SetCanvasZ(0, 1)
ClearCanvas
SetColor(RGB(0,255,0))

Dim button[7]
button_size = 64
button_y = 400

Dim cmod[2]

current_cmod = 0
cmod_timer = Timer

If UCase(OS) = "ANDROID" Or UCase(OS) = "IOS" Then
	LoadImage(MOBILE_BUTTONS_IMAGE, "mobile_buttons.png")
	For i = 0 to 6
		button[i] = 20 + (i*button_size) + (i*4)
		DrawImage_Blit(MOBILE_BUTTONS_IMAGE, button[i], button_y, i * button_size, 0, button_size, button_size)
	Next
End If

sub ctrl()
	IF KEY(K_S) And z_inc < 0.05 THEN
		z_inc = z_inc + 0.001
		zoom = zoom + 0.01
	ELSEIF KEY(K_W) And z_inc > 0.01 THEN
		z_inc = z_inc - 0.001
		zoom = zoom - 0.01
	END IF
	
		If Key(K_LEFT) Then
		pos_dir = pos_dir + 1
	ElseIf Key(K_RIGHT) Then
		pos_dir = pos_dir - 1
	End If
	
	If pos_dir >= 360 Then
		pos_dir = pos_dir - 360
	ElseIf pos_dir < 0 Then
		pos_dir = 360 + pos_dir
	End If
	
	If Key(K_UP) Then
		pos_x = pos_x + sin(CRadians(pos_dir))*1.8
        pos_y = pos_y + cos(CRadians(pos_dir))*1.8
    End If
    If Key(K_DOWN) Then
        pos_x = pos_x - sin(CRadians(pos_dir))*0.8
        pos_y = pos_y - cos(CRadians(pos_dir))*0.8
    End If
    
    If Key(K_C) And (timer-cmod_timer > 200) Then
		current_cmod = Not current_cmod
		SetImageColorMod(0, cmod[current_cmod])
		cmod_timer = timer
	End If
	
end sub

Dim touch_status
Dim touch_x
Dim touch_y
Dim touch_dx
Dim touch_dy

function button_pressed(b)
	If touch_x >= button[b] And touch_x < (button[b] + button_size) And touch_y >= button_y And touch_y < (button_y + button_size) Then
		Return True
	End If
	Return False
end function

sub ctrl_mobile()
	GetTouch(touch_status, touch_x, touch_y, touch_dx, touch_dy)
	
	If touch_status Then
		IF button_pressed(4) And z_inc < 0.05 THEN
			z_inc = z_inc + 0.001
			zoom = zoom + 0.01
		ELSEIF button_pressed(5) And z_inc > 0.01 THEN
			z_inc = z_inc - 0.001
			zoom = zoom - 0.01
		END IF
		
		If button_pressed(0) Then
			pos_dir = pos_dir + 1
		ElseIf button_pressed(3) Then
			pos_dir = pos_dir - 1
		End If
		
		If pos_dir >= 360 Then
			pos_dir = pos_dir - 360
		ElseIf pos_dir < 0 Then
			pos_dir = 360 + pos_dir
		End If
		
		If button_pressed(1) Then
			pos_x = pos_x + sin(CRadians(pos_dir))*1.8
			pos_y = pos_y + cos(CRadians(pos_dir))*1.8
		End If
		If button_pressed(2) Then
			pos_x = pos_x - sin(CRadians(pos_dir))*0.8
			pos_y = pos_y - cos(CRadians(pos_dir))*0.8
		End If
		
		If button_pressed(6) And (timer-cmod_timer > 200) Then
			current_cmod = Not current_cmod
			SetImageColorMod(0, cmod[current_cmod])
			cmod_timer = timer
		End If
	End If
end sub

Sub DrawField(cam_x, cam_y, cam_z, cam_dir)
	'-------Get Display Image----------------------------------------
	Canvas(BUFFER_BACK)
	ClearCanvas
	
	DrawImage_Zoom(BKG_IMAGE, (cam_x*zoom)+WINDOW_CENTER_X, (cam_y*zoom)+WINDOW_CENTER_Y, zoom, zoom)
	
	If ImageExists(DISPLAY_IMAGE) Then
		DeleteImage(DISPLAY_IMAGE)
	End If
	
	CanvasClip(DISPLAY_IMAGE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1)
	
	ClearCanvas
	
	DrawImage_Rotate(DISPLAY_IMAGE, 0, 0, cam_dir)
	
	If ImageExists(DISPLAY_IMAGE) Then
		DeleteImage(DISPLAY_IMAGE)
	End If
	
	SETCOLOR(RGB(255,0,0))
	BOXFILL(WINDOW_CENTER_X-5, WINDOW_CENTER_Y-5, WINDOW_CENTER_X+5, WINDOW_CENTER_Y+5)
	LINE(WINDOW_CENTER_X, WINDOW_CENTER_Y, WINDOW_CENTER_X-100, WINDOW_CENTER_Y-200)
	LINE(WINDOW_CENTER_X, WINDOW_CENTER_Y, WINDOW_CENTER_X+100, WINDOW_CENTER_Y-200)
	
	
	CanvasClip(DISPLAY_IMAGE, 0, 0, WINDOW_WIDTH, WINDOW_CENTER_Y, 1)
	
	
	ClearCanvas
	ix = 0
	z = 0.01
	
	scan_h = 1
	screen_y = 0
	
	
	for y = -1 TO -220 STEP -1
		ix = y/2 + WINDOW_CENTER_X
		scan_w = (WINDOW_CENTER_X - ix) * 2
		scan_h = screen_y
		screen_y = (WINDOW_HEIGHT + y)/z
		If y = -1 Then
			scan_h = 1
		Else
			scan_h = (scan_h - screen_y)+1
		End If
		DrawImage_Blit_Ex(DISPLAY_IMAGE, 0, screen_y, WINDOW_WIDTH, scan_h, ix, (200+y), scan_w, 1)
		z = z + z_inc
	next
	
	
	If ImageExists(DISPLAY_IMAGE) Then
		DeleteImage(DISPLAY_IMAGE)
	End If
	
	CanvasClip(DISPLAY_IMAGE, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1)
	
	
	
	'return
	'SETCOLOR(RGB(255,0,0))
	'BOXFILL(WINDOW_CENTER_X-5, WINDOW_CENTER_Y-5, WINDOW_CENTER_X+5, WINDOW_CENTER_Y+5)
	
	'LINE(WINDOW_CENTER_X, WINDOW_CENTER_Y, WINDOW_CENTER_X-100, WINDOW_CENTER_Y-200)
	'LINE(WINDOW_CENTER_X, WINDOW_CENTER_Y, WINDOW_CENTER_X+100, WINDOW_CENTER_Y-200)
	
	'----------------------------------------------------------------
	
	'-------Display Field--------------------------------------------
	Canvas(BUFFER_DISPLAY)
	SetClearColor(RGB(40, 40, 200))
	ClearCanvas
	
	DrawImage_Blit_Ex(DISPLAY_IMAGE, 0, WINDOW_CENTER_Y, WINDOW_WIDTH, WINDOW_CENTER_Y, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)
	
End Sub

LoadTexture("mariocircuit-1.bmp")

cmod[0] = ImageColorMod(0)
cmod[1] = rgb(200,120, 130)

SetColor(RGB(255,255,255))
Locate(2, 2)
'PrintS(" ARROW KEYS TO MOVE")
'PrintS(" W AND S TO MOVE UP AND DOWN")
'PrintS(" C TO CHANGE COLOR MOD")
LoadFont(0, "FreeMono.ttf", 16)
'PrintS("Interface Test ->"+rcbasic_android_interface("my android args"))

While Not Key(K_ESCAPE)
	If UCase(OS) = "ANDROID" Or UCase(OS) = "IOS" Then
		ctrl_mobile
	Else
		ctrl
	End If
	
	DrawField(pos_x, pos_y, 0, pos_dir)
	'DrawText("Interface Test ->"+android_jni_message("my android args"), 20, 20)
	Update
Wend
