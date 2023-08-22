'StringFill
'Stack_Size_N
'Stack_Size_S
'Text I/O
sub FPrint(txt$)
function Input$(prompt$)
'Arrays
function ArrayDim(Byref id)
function StringArrayDim(Byref id$)
function NumberArrayDim(Byref id)
function ArraySize(Byref id, array_dim)
function StringArraySize(Byref id$, array_dim)
function NumberArraySize(Byref id, array_dim)
'Math
function Abs(n)
function ACos(n)
function AndBit(a,b)
function ASin(n)
function ATan(n)
function Bin$(n)
function CInt32(i)
function CInt64(i)
function Cos(n)
function Degrees(r)
function Exp(n)
function Frac(n)
function Hex$(n)
function HexVal(n$)
function Int(n)
function Log(n)
function Max(a, b)
function Min(a, b)
function OrBit(a, b)
function Radians(d)
function Randomize(n)
function Rand(n)
function Round(n)
function Sign(n)
function Sin(n)
function Sqrt(n)
function Tan(n)
function XOrBit(a, b)
'Strings
function Asc(c$)
function Chr$(n)
function Insert$(src$, tgt$, pos)
function InStr(src$, substr$)
function LCase$(src$)
function Left$(src$, n)
function Length(src$)
function Len(src$)
function LTrim$(src$)
function Mid$(src$, start, n)
function ReplaceSubstr$(src$, rpc$, pos)
function Replace$(src$, tgt$, rpc$)
function Reverse$(src$)
function Right$(src$, n)
function RTrim$(src$)
function StringFill$(src$, n)
function Str$(n)
function Str_F$(n)
function Str_S$(n)
function Tally(src$, substr$)
function Trim$(src$)
function UCase$(src$)
function Val(n$)
'Stacks
sub Stack_N(n)
sub Stack_S(n)
sub Push_N(n)
function Pop_N()
sub Push_S(s$)
function Pop_S$()
function Stack_Size_N()
function Stack_Size_S()
'File I/O
function FileOpen(stream, fileName$, mode)
sub FileClose(stream)
function ReadByte(stream)
sub WriteByte(stream, byte)
function ReadLine$(stream)
sub Write(stream, txt$)
sub WriteLine(stream, txt$)
sub CopyFile(src$, dst$)
function RemoveFile(fileName$)
function FileExists(fileName$)
function MoveFile(src$, dst$)
function RenameFile(src$, dst$)
function FileLength(fileName$)
function Tell(stream)
function Seek(stream, pos)
function EOF(stream)
function FreeFile()
'Directories
sub ChangeDir(p$)
function DirExists(p$)
function DirFirst$()
function Dir$()
function DirNext$()
function MakeDir(p$)
function RemoveDir(p$)
'Date and Time
function Date$()
function Easter$(year)
function Ticks()
function Time$()
function Timer()
sub Wait(m_sec)
'Window Management
sub WindowOpen(win, title$, x, y, w, h, flag, vsync)
sub WindowClose(win)
sub RaiseWindow(win)
sub Window(win)
sub Update()
sub Cls()
sub SetClearColor(c)
sub ShowWindow(win)
sub HideWindow(win)
sub SetWindowTitle(win, title$)
function WindowTitle$(win)
sub SetWindowPosition(win, x, y)
sub GetWindowPosition(win, byref x, byref y)
sub SetWindowSize(win, w, h)
sub GetWindowSize(win, byref w, byref h)
sub SetWindowMinSize(win, w, h)
sub GetWindowMinSize(win, byref w, byref h)
sub SetWindowMaxSize(win, w, h)
sub GetWindowMaxSize(win, byref w, byref h)
function WindowIsFullscreen(win)
function WindowIsVisible(win)
function WindowIsBordered(win)
function WindowIsResizable(win)
function WindowIsMinimized(win)
function WindowIsMaximized(win)
function WindowHasInputFocus(win)
function WindowHasMouseFocus(win)
sub SetWindowFullscreen(win, flag)
sub MaximizeWindow(win)
sub MinimizeWindow(win)
sub SetWindowBorder(win, flag)
sub WindowClip(slot, x, y, w, h)
function WindowExists(win)
function NumWindows()
function WindowEvent_Close(win)
function WindowEvent_Maximize(win)
function WindowEvent_Minimize(win)
function ActiveWindow()
function FPS()
sub SetWindowIcon(win, slot)
'Canvases
sub CanvasOpen(c_num, w, h, viewport_x, viewport_y, viewport_w, viewport_h, mode)
sub CanvasClose(c_num)
sub SetCanvasVisible(c_num, flag)
function CanvasIsVisible(c_num)
sub SetCanvasViewport(cnum, x, y, w, h)
sub GetCanvasViewport(c_num, byref x, byref y, byref w, byref h)
sub Canvas(c_num)
sub SetCanvasOffset(c_num, x, y)
sub GetCanvasOffset(c_num, byref x, byref y)
sub GetCanvasSize(c_num, byref w, byref h)
sub ClearCanvas()
sub SetCanvasAlpha(c_num, a)
function CanvasAlpha(c_num)
function SetCanvasBlendMode(c_num, blend_mode)
function CanvasBlendMode(c_num)
function SetCanvasColorMod(c_num, c)
function CanvasColorMod(c_num)
sub CopyCanvas(src, x, y, w, h, dst, dx, dy)
sub CloneCanvas(src, dst)
sub SetCanvasZ(c_num, z)
function CanvasZ(c_num)
sub CanvasClip(slot, x, y, w, h, flag)
function ActiveCanvas()
'Graphics Primitives
sub Box(x1, y1, x2, y2)
sub BoxFill(x1, y1, x2, y2)
sub Circle(x,y,radius)
sub CircleFill(x,y,radius)
sub Ellipse(x,y,rx,ry)
sub EllipseFill(x,y,rx,ry)
sub FloodFill(x,y)
function GetPixel(x,y)
sub SetColor(c)
sub Line(x1, y1, x2, y2)
sub Poly(n, byref x, byref y)
sub PolyFill(n, byref x, byref y)
sub Rect(x, y, w, h)
sub RectFill(x, y, w, h)
sub RoundRect(x, y, w, h, r)
sub RoundRectFill(x, y, w, h, r)
function RGB(r,g,b)
function RGBA(r,g,b,a)
sub PSet(x,y)
'Images
sub LoadImage(slot, img$)
sub LoadImage_Ex(slot, img$, colkey)
sub ImageFromBuffer(slot, w, h, byref buffer)
sub ImageFromBuffer_Ex(slot, w, h, byref buffer, colkey)
sub BufferFromImage(slot, byref buffer)
function ImageExists(slot)
sub ColorKey(slot, c)
sub CopyImage(src, dst)
sub DeleteImage(slot)
sub SetImageAlpha(slot, a)
function ImageAlpha(slot)
sub GetImageSize(slot, byref w, byref h)
function SetImageBlendMode(slot, blend_mode)
function ImageBlendMode(slot)
function SetImageColorMod(slot, c)
function ImageColorMod(slot)
sub DrawImage(slot, x, y)
sub DrawImage_Blit(slot, x, y, src_x, src_y, src_w, src_h)
sub DrawImage_Blit_Ex(slot, x, y, w, h, src_x, src_y, src_w, src_h)
sub DrawImage_Rotate(slot, x, y, angle)
sub DrawImage_Rotate_Ex(slot, x, y, src_x, src_y, src_w, src_h, angle)
sub DrawImage_Zoom(slot, x, y, zx, zy)
sub DrawImage_Zoom_Ex(slot, x, y, src_x, src_y, src_w, src_h, zx, zy)
sub DrawImage_Rotozoom(slot, x, y, angle, zx, zy)
sub DrawImage_Rotozoom_Ex(slot, x, y, src_x, src_y, src_w, src_h, angle, zx, zy)
sub DrawImage_Flip(slot, x, y, h, v)
sub DrawImage_Flip_Ex(slot, x, y, src_x, src_y, src_w, src_h, h, v)
'Keyboard and Mouse
function InKey()
function Key(key_code)
function WaitKey()
sub HideMouse()
sub ShowMouse()
function MouseIsVisible()
sub GetMouse(byref x, byref y, byref mb1, byref mb2, byref mb3)
function MouseX()
function MouseY()
function MouseButton(mb)
sub GetMouseWheel(byref x_axis, byref y_axis)
function MouseWheelX()
function MouseWheelY()
'Sound and Music
sub SoundFromBuffer(slot, byref buffer, buffer_size, vol)
sub LoadSound(slot, snd_file$)
sub LoadMusic(music_file$)
sub PlaySound(slot, channel, loops)
sub PlaySoundTimed(slot, channel, loops, ms)
sub PlayMusic(mLoops)
sub PauseSound(channel)
sub ResumeSound(channel)
sub PauseMusic()
sub ResumeMusic()
sub DeleteSound(slot)
sub DeleteMusic()
sub FadeMusicIn(fade_time, loops)
sub FadeMusicOut(fade_time)
function MusicExists()
sub SetMusicVolume(vol)
function MusicVolume()
sub SetMusicPosition(pos)
function MusicPosition()
sub RewindMusic()
sub SetSoundChannels(max_channels)
function NumSoundChannels()
function SoundIsEnabled()
function SoundExists(slot)
sub SetChannelVolume(channel, vol)
function ChannelVolume(channel)
sub SetSoundVolume(slot, vol)
function SoundVolume(slot)
sub StopMusic()
sub StopSound(channel)
function SetChannelPanning(channel, left_value, right_value)
function SetChannelDistance(channel, dist_value)
function ChannelIsPlaying(channel)
function ChannelIsPaused(channel)
'Joysticks
function NumJoysticks()
function NumJoyAxes(joy_num)
function NumJoyButtons(joy_num)
function NumJoyHats(joy_num)
function NumJoyTrackBalls(joy_num)
function JoyAxis(joy_num, joy_axis)
function JoyButton(joy_num, joy_button)
function JoyHat(joy_num, joy_hat)
sub GetJoyTrackBall(joy_num, ball, byref dx, byref dy)
function JoyName$(joy_num)
function JoystickIsConnected(joy_num)
'Screen Console
sub GetCursor(byref x, byref y)
sub PrintS(txt$)
function InputS$(prompt$)
function ZoneInputS$(x, y, w, h)
sub Locate(x, y)
'Text Editing
sub ReadInput_Start()
sub ReadInput_Stop()
function ReadInput_Text$()
sub ReadInput_SetText(txt$)
sub ReadInput_ToggleBackspace(flag)
'Text Drawing
sub LoadFont(slot, fnt_file$, size)
sub DeleteFont(slot)
function FontIsLoaded(slot)
sub Font(slot)
sub SetFontStyle(slot, style)
sub DrawText(txt$, x, y)
sub DrawText_Shaded(txt$, x, y, fg_color, bg_color)
sub DrawText_Blended(txt$, x, y)
sub RenderText(slot, txt$)
sub GetTextSize(slot, txt$, byref w, byref h)
'Touch Events
function TouchPressure()
sub GetTouch(byref status, byref x, byref y, byref dx, byref dy)
sub GetMultiTouch(byref status, byref x, byref y, byref fingers, byref dist, byref theta)
sub GetTouchFinger(finger, byref x, byref y, byref pressure)
function NumFingers()
'Networking
function CheckSockets(timeout_ms)
function TCP_SocketReady(socket)
function UDP_SocketReady(socket)
function TCP_SocketOpen(socket, host$, port)
sub TCP_SocketClose(socket)
function TCP_RemoteHost(socket)
function TCP_RemotePort(socket)
function TCP_GetData(socket, ByRef sData$, numBytes)
sub TCP_SendData(socket, sData$)
function TCP_AcceptSocket(server, client)
function UDP_SocketOpen(socket, port)
function UDP_SocketClose(socket)
function UDP_GetData(socket, byref sData$, byref host$, byref port)
function UDP_Length()
function UDP_MaxLength()
function UDP_RemoteHost$(socket)
function UDP_RemotePort(socket)
sub UDP_SendData(socket, sData$, host$, port)
'Video Playback
sub LoadVideo(vid$)
sub PlayVideo(vLoops)
sub PauseVideo()
sub StopVideo()
sub SetVideoPosition(pos)
sub ResumeVideo()
function VideoPosition()
sub DeleteVideo()
function VideoIsPlaying()
function VideoEnd()
sub GetVideoStats(vFile$, byref vLen, byref vfps, byref frame_w, byref frame_h)
sub SetVideoDrawRect(x, y, w, h)
sub GetVideoDrawRect(byref x, byref y, byref w, byref h)
sub GetVideoSize(byref w, byref h)
function VideoExists()
sub SetVideoAlpha(a)
'Operating System
function System(cmd$)
function OS$()
function Command$(arg)
function NumCommands()
function Env$(v$)
sub SetEnv(var$, value$, overwrite)
function PrefPath$(org_name$, app_name$)
function Android_GetExternalStoragePath$()
function Android_GetExternalStorageState()
function Android_GetInternalStoragePath$()
function Android_JNI_Message$(arg$)
function Runtime_Utility_Message$(arg$)
'Clipboard
function ClipboardText$()
sub SetClipboardText(txt$)
function HasClipboardText()

'v3.12
Sub GetDesktopDisplayMode(index, ByRef w, ByRef h, ByRef freq)
Sub DrawImage_Transform(slot, x, y, w, h, src_x, src_y, src_w, src_h, angle, center_x, center_y, flip_h, flip_v)
Sub GetPowerInfo(ByRef status, ByRef secs, ByRef pct)
Function SystemRam()
Function SetRenderScaleQuality(n)
Function EvalJS$(js_code$) 'Only useable in Emscripten
Function GetRenderScaleQuality()

'v3.14
sub GetGlobalMouse(ByRef x, ByRef y, ByRef mb1, ByRef mb2, ByRef mb3)
function GlobalMouseX()
function GlobalMouseY()
sub GetAccel(accel_num, ByRef x, ByRef y, ByRef z)
function AccelName$(accel_num)
function NumAccels()
sub GetGyro(gyro_num, ByRef x, ByRef y, ByRef z)
function GyroName$(gyro_num)
function NumGyros()
sub JoyRumblePlay(joy_num, strength, duration)
sub JoyRumbleStop(joy_num)
function JoystickIsHaptic(joy_num)
function WriteByteBuffer(stream, ByRef buf, buf_size)
function ReadByteBuffer(stream, ByRef buf, buf_size)
function WindowEvent_Resize(win)
sub SetWindowAutoClose( win, exit_on_close )
sub SetWindowResizable(win, flag) 'new
function SystemReturnStdOut$(cmd$) 'new
function WindowMode(visible, fullscreen, resizable, borderless, highDPI)
function WindowFlags(win)
sub RestoreWindow(win)
sub UpdateAllWindows() 'new
function QueryAudioSpec(ByRef freq, ByRef format, ByRef channels) 'new

'v3.15
function MusicIsPlaying()

'v3.19
function DrawGeometry(slot, num_vertices, ByRef vertices, num_indices, ByRef Indices)

'v3.20
function Size(s$)
function BufferFromString(s$, ByRef buffer)
function StringFromBuffer$(ByRef buffer, buffer_size)
sub GrabInput(flag)
function GrabbedWindow()
sub WarpMouse(x, y)
sub WarpMouseGlobal(x, y)
sub SetMouseZone(x, y, w, h)
sub ClearMouseZone()
sub SetWindowAlwaysOnTop(win, flag)
sub SetMouseRelative(flag)
sub SetWindowVSync(win, flag)
function OpenURL(url$)
function APIVersion$()
function FlashWindow(win)
function MessageBox(title$, msg$)
sub NumberArrayCopy(ByRef src, ByRef dst)
sub StringArrayCopy(ByRef src$, ByRef dst$)
sub ArrayCopy(ByRef src, ByRef dst)
sub NumberArrayFill(ByRef src, fdata)
sub StringArrayFill(ByRef src$, fdata$)
sub ArrayFill(ByRef src, fdata)
function Runtime$()

'More v3.20 (Matrices and Parrallism)
sub DimMatrix(m, m_rows, m_cols, preserve_flag)
function AddMatrix(mA, mB, mC)
function AugmentMatrix (mA, mB, mC)
sub CopyMatrix(mA, mB)
function InsertMatrixColumns(mA, c, num_cols)
function InsertMatrixRows(mA, r, num_rows)
function MultiplyMatrix (mA, mB, mC)
function CubeMatrix(mA, mB)
function DeleteMatrixColumns(mA, c, num_cols)
function DeleteMatrixRows(mA, r, num_rows)
sub ClearMatrix(mA)
function ClearMatrixColumns (mA, c, num_cols)
function ClearMatrixRows(mA, r, num_rows)
sub FillMatrix(mA, v)
function FillMatrixColumns(mA, c, num_cols, v)
function FillMatrixRows(mA, r, num_rows, v)
function CopyMatrixColumns(mA, mB, c, num_cols)
function CopyMatrixRows (mA, mB, r, num_rows)
sub IdentityMatrix(mA, n)
function SolveMatrix(mA, mB, mC)
function IsEqualMatrix(mA, mB, tolerance)
function Determinant(mA)
function AdjointMatrix(mA, mB)
function InvertMatrix(mA, mB)
sub MatrixFromBuffer(mA, r, c, ByRef buffer)
sub GetMatrix(ByRef buffer, mA)
sub RandomizeMatrix(mA, vmin, vmax)
function MatrixValue(mA, r, c)
sub SetMatrixValue(mA, r, c, v)
sub ScalarMatrix (mA, mB, s_value)
function ScalarMatrixColumns(mA, mB, c, num_cols, s_value)
function ScalarMatrixRows(mA, mB, r, num_rows, s_value)
function SquareMatrix(mA, mB)
sub SubMatrix(mA, r, c)
function SubtractMatrix (mA, mB, mC)
sub SwapMatrix(mA, mB)
function SwapMatrixColumn(mA, C1, C2)
function SwapMatrixRow(mA, R1, R2)
function TransposeMatrix(mA, mB)
function UnAugmentMatrix(mA, mB, mC)
sub ZeroMatrix(mA)

sub GetMatrixSize(mA, ByRef r, ByRef c)
function SetMatrixProcess(p_num) 'Set to -1 for main thread


'ERROR_FLAG - MATRIX_ON_ERROR_STOP, MATRIX_ON_ERROR_WAIT, MATRIX_ON_ERROR_CONTINUE
function ProcessOpen(p_num) 'stops and locks mutex, and clears queue before changing mode
sub SetProcessErrorMode(p_num, error_mode)
function ProcessError(p_num)
sub ProcessWait(p_num) 'waits for all calculations to complete and lock matrix mutex
sub ProcessWaitAll() 'waits for all process to finish
sub ProcessContinue(p_num) 'unlock mutex
sub ProcessStop(p_num) 'stops after current calculation its working on and lock mutex
sub ProcessClear(p_num) 'locks mutex and clears matrix queue
function ProcessClose(p_num)
function ProcessErrorMode(p_num)
sub ProcessSleep(p_num, msec)
function ProcessExists(p_num)
sub ProcessStopAll()
sub ProcessContinueAll()
function ProcessQueueSize(p_num)

function NumCPUs()


sub GetProjectionGeometry(cam_dist, mA, f_vertex_count, ByRef columns, ByRef uv, graph_offset_x, graph_offset_y, v_color, ByRef vertex_count, ByRef vertex2D, ByRef index_count, ByRef index, ByRef clip_dist, ByRef min_x, ByRef min_y, ByRef max_x, ByRef max_y)
function CalculateFaceZ(cam_dist, graph_offset_x, graph_offset_y, view_w, view_h, view_depth, mA, f_vertex_count, ByRef columns, ByRef face_min_z, ByRef face_max_z, ByRef z_avg)
