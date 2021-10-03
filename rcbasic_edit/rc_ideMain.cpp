/***************************************************************
 * Name:      rc_ide2Main.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2015-08-18
 * Copyright:  ()
 * License:
 **************************************************************/

//#include "wx_pch.h"
#include "rc_ideMain.h"
#include <wx/msgdlg.h>
#include <wx/filedlg.h>
#include <wx/file.h>
#include <wx/filefn.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <wx/stdpaths.h>
#include <wx/stc/stc.h>
#include <wx/utils.h>
#include <wx/process.h>
#include <iostream>

//(*InternalHeaders(rc_ideFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

#define RC_WINDOWS
//#define RC_LINUX

//(*IdInit(rc_ideFrame)
const long rc_ideFrame::ID_AUINOTEBOOK1 = wxNewId();
const long rc_ideFrame::newID = wxNewId();
const long rc_ideFrame::openID = wxNewId();
const long rc_ideFrame::saveID = wxNewId();
const long rc_ideFrame::saveAsID = wxNewId();
const long rc_ideFrame::idMenuQuit = wxNewId();
const long rc_ideFrame::undoID = wxNewId();
const long rc_ideFrame::redoID = wxNewId();
const long rc_ideFrame::cutID = wxNewId();
const long rc_ideFrame::copyID = wxNewId();
const long rc_ideFrame::pasteID = wxNewId();
const long rc_ideFrame::deleteID = wxNewId();
const long rc_ideFrame::compileID = wxNewId();
const long rc_ideFrame::runID = wxNewId();
const long rc_ideFrame::distributeID = wxNewId();
const long rc_ideFrame::idMenuAbout = wxNewId();
const long rc_ideFrame::referenceID = wxNewId();
const long rc_ideFrame::ID_STATUSBAR1 = wxNewId();
const long rc_ideFrame::toolNewID = wxNewId();
const long rc_ideFrame::toolOpenID = wxNewId();
const long rc_ideFrame::toolSaveID = wxNewId();
const long rc_ideFrame::toolSaveAsID = wxNewId();
const long rc_ideFrame::toolRunID = wxNewId();
const long rc_ideFrame::toolStopID = wxNewId();
const long rc_ideFrame::ID_TOOLBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(rc_ideFrame,wxFrame)
    //(*EventTable(rc_ideFrame)
    //*)
END_EVENT_TABLE()

int rc_current_page = 0;
wxString rc_fnames[999];
wxString rc_path = _("");//_("/home/cunningham/Desktop/alt_platforms/rc_ide/rc_ide/bin/Debug/");
wxString rc_keywords = _("");
wxString rc_keywords2 = _("");
wxFont rc_font;
int rc_nline = 0;
long pid = -1;
wxProcess * vm_process;

void rc_initKeywords()
{
    rc_keywords = wxT("include once continue ");
    rc_keywords += wxT("true false mod shl shr and not or xor byref case do default else elseif end exit for function if loop next return select step sub then to until wend while ");
    rc_keywords += wxT("print dim delete fprint input arraydim stringarraydim numberarraydim arraysize stringarraysize numberarraysize asc chr insert instr lcase left length ");
    rc_keywords += wxT("ltrim mid replace replacesubstr reverse right rtrim stringfill str tally trim ucase val abs acos andbit asin atan bin cos exp frac hex int log max min ");
    rc_keywords += wxT("orbit randomize rand round sign sin sqrt tan xorbit fileopen fileclose readbyte writebyte readline writeline copyfile removefile fileexists movefile renamefile ");
    rc_keywords += wxT("filelength tell seek eof freefile changedir direxists dirfirst dir dirnext makedir removedir date ticks time timer wait windowopen windowclose raisewindow ");
    rc_keywords += wxT("window update showwindow hidewindow setwindowtitle windowtitle setwindowposition getwindowposition setwindowsize getwindowsize setwindowminsize getwindowminsize ");
    rc_keywords += wxT("setwindowmaxsize getwindowmaxsize windowisfullscreen windowisvisible windowisbordered windowisresizable windowisminimized windowismaximized setwindowfullscreen ");
    rc_keywords += wxT("maximizewindow minimizewindow setwindowborder canvasopen canvasclose setcanvasviewport getcanvasviewport canvas setcanvasoffset getcanvasoffset getcanvassize ");
    rc_keywords += wxT("clearcanvas setcanvasalpha copycanvas clonecanvas setcanvasz box boxfill circle circlefill ellipse ellipsefill floodfill getpixel setcolor line poly polyfill ");
    rc_keywords += wxT("rgb rgba pset loadimage imageexists colorkey copyimage deleteimage setimagealpha imagealpha getimagesize flipimage drawimage drawimage_blit drawimage_blit_ex ");
    rc_keywords += wxT("drawimage_rotate drawimage_rotate_ex drawimage_zoom drawimage_zoom_ex drawimage_rotozoom drawimage_rotozoom_ex getcursor prints inputs locate fontisloaded ");
    rc_keywords += wxT("font loadfont deletefont setfontstyle drawtext drawtext_shaded drawtext_blended inkey key waitkey hidemouse showmouse mouseisvisible getmouse getmousewheel ");
    rc_keywords += wxT("mousex mousey mousebutton mousewheelx mousewheely numjoysticks joyaxis joybutton joyname loadsound loadmusic playsound playsoundtimed playmusic pausesound ");
    rc_keywords += wxT("resumesound pausemusic resumemusic deletesound fademusicin fademusicout musicexists setmusicvolume musicvolume setmusicposition musicposition rewindmusic ");
    rc_keywords += wxT("setsoundchannels numsoundchannels soundisenabled soundexists setchannelvolume channelvolume setsoundvolume soundvolume stopmusic stopsound tcp_socketopen ");
    rc_keywords += wxT("tcp_socketclose tcp_remotehost tcp_remoteport tcp_getdata tcp_senddata tcp_acceptsocket udp_socketopen udp_socketclose udp_getdata udp_length udp_maxlength ");
    rc_keywords += wxT("udp_remotehost udp_remoteport udp_senddata zoneinputs touchpressure gettouch getmultitouch readinput_start readinput_stop readinput_text canvasclip windowclip ");
    rc_keywords += wxT("setcanvasvisible canvasisvisible rendertext gettextsize imagefrombuffer imagefrombuffer_ex readinput_settext gettouchfinger numfingers loadimage_ex rect ");
    rc_keywords += wxT("rectfill os numjoybuttons numjoyaxes loadvideo playvideo pausevideo stopvideo setvideoposition resumevideo videoposition deletevideo deletemusic system ");
    rc_keywords += wxT("videoisplaying roundrect roundrectfill videoend getvideostats setvideodrawrect getvideodrawrect getvideosize videoexists setvideoalpha soundfrombuffer ");
    rc_keywords += wxT("command numcommands str_f str_f$ str_s str_s$ cls env env$ setenv prefpath prefpath$ numjoyhats joyhat numjoytrackballs getjoytrackball windowhasinputfocus ");
    rc_keywords += wxT("windowhasmousefocus push_n push_s pop_n pop_s pop_s$ stack_size_n stack_size_s joystickisconnected numwindows windowexists readinput_togglebackspace windowevent_close ");
    rc_keywords += wxT("windowevent_minimize windowevent_maximize poly polyfill setclearcolor cint32 cint64 activecanvas activewindow fps hasclipboardtext setclipboardtext clipboardtext ");
    rc_keywords += wxT("setwindowicon hexval checksockets tcp_socketready udp_socketready easter bufferfromimage drawimage_flip drawimage_flip_ex stack_n stack_s setimageblendmode ");
    rc_keywords += wxT("imageblendmode setimagecolormod imagecolormod canvasalpha setcanvasblendmode canvasblendmode setcanvascolormod canvascolormod len degrees radians canvasz ");
    rc_keywords += wxT("setchanneldistance setchannelpanning channelisplaying channelispaused android_getexternalstoragepath android_getexternalstoragestate android_getinternalstoragepath ");
    rc_keywords += wxT("android_jni_message runtime_utility_message getdesktopdisplaymode drawimage_transform getpowerinfo systemram setrenderscalequality evaljs getrenderscalequality ");
    rc_keywords += wxT("write getglobalmouse globalmousex globalmousey getaccel accelname numaccels getgyro gyroname numgyros joyrumbleplay joyrumblestop joystickishaptic writebytebuffer ");
    rc_keywords += wxT("readbytebuffer windowevent_resize setwindowautoclose setwindowresizable systemreturnstdout windowmode windowflags restorewindow updateallwindows queryaudiospec ");
    rc_keywords += wxT("musicisplaying ");

    rc_keywords2 = wxT("k_0 k_1 k_2 k_3 k_4 k_5 k_6 k_7 k_8 k_9 k_a k_ac_back k_ac_bookmarks k_ac_forward k_ac_home k_ac_refresh k_ac_search k_ac_stop k_again k_alterase k_application ");
    rc_keywords2 += wxT("k_audiomute k_audionext k_audioplay k_audioprev k_audiostop k_b k_backslash k_backspace k_brightnessdown k_brightnessup k_c k_calculator k_cancel k_capslock k_clear ");
    rc_keywords2 += wxT("k_clearagain k_computer k_copy k_crsel k_currencysubunit k_currencyunit k_cut k_d k_decimalseparator k_delete k_displayswitch k_down k_e k_eject k_end k_equal k_escape ");
    rc_keywords2 += wxT("k_execute k_exsel k_f k_f1 k_f2 k_f3 k_f4 k_f5 k_f6 k_f7 k_f8 k_f9 k_f10 k_f11 k_f12 k_f13 k_f14 k_f15 k_f16 k_f17 k_f18 k_f19 k_f20 k_f21 k_f22 k_f23 k_f24 k_find k_g ");
    rc_keywords2 += wxT("k_grave k_h k_help k_home k_i k_insert k_j k_k k_kbdllumdown k_kbdllumtoggle k_kbdllumup keypad_0 keypad_00 keypad_000 keypad_1 keypad_2 keypad_3 keypad_4 keypad_5 ");
    rc_keywords2 += wxT("keypad_6 keypad_7 keypad_8 keypad_9 keypad_a keypad_ampersand keypad_at keypad_b keypad_backspace keypad_binary keypad_c keypad_clear keypad_clearentry keypad_colon ");
    rc_keywords2 += wxT("keypad_comma keypad_d keypad_dblampersand keypad_dblverticalbar keypad_decimal keypad_divide keypad_e keypad_enter keypad_equal keypad_equalas400 keypad_exclam keypad_f ");
    rc_keywords2 += wxT("keypad_greater keypad_hash keypad_hexadecimal keypad_leftbrace keypad_leftparen keypad_less keypad_memadd keypad_memclear keypad_memdivide keypad_memmultiply ");
    rc_keywords2 += wxT("keypad_memrecall keypad_memstore keypad_memsubtract keypad_minus keypad_multiply keypad_octal keypad_percent keypad_period keypad_plus keypad_plusminus keypad_power ");
    rc_keywords2 += wxT("keypad_rightbrace keypad_rightparen keypad_space keypad_tab keypad_verticalbar keypad_xor k_l k_lalt k_lctrl k_left k_leftbracket k_lgui k_leftshift k_m k_mail ");
    rc_keywords2 += wxT("k_mediaselect k_menu k_minus k_modeswitch k_mute k_n k_numlock k_o k_oper k_out k_p k_pagedown k_pageup k_paste k_pause k_power k_printscreen k_prior k_q k_r k_ralt ");
    rc_keywords2 += wxT("k_rctrl k_return k_return2 k_rgui k_right k_rightbracket k_rshift k_s k_scrolllock k_select k_semicolon k_separator k_slash k_sleep k_space k_stop k_sysreq k_t k_tab ");
    rc_keywords2 += wxT("k_thousandseparator k_u k_undo k_unknown k_up k_v k_volumedown k_volumeup k_w k_www k_x k_y k_z windowpos_centered hat_up hat_down hat_left hat_right hat_rightup ");
    rc_keywords2 += wxT("hat_rightdown hat_leftup hat_leftdown hat_centered text_input text_output text_append text_input_plus text_output_plus text_append_plus ");
    rc_keywords2 += wxT("binary_input binary_output binary_append binary_input_plus binary_output_plus binary_append_plus ");
    rc_keywords2 += wxT("blendmode_none blendmode_blend blendmode_add blendmode_mod ");
    rc_keywords2 += wxT("android_external_storage_read android_external_storage_write powerstate_unknown powerstate_on_battery powerstate_no_battery powerstate_charging powerstate_charged ");
    rc_keywords2 += wxT("window_visible window_hidden window_fullscreen window_borderless window_resizable window_highdpi ");
}

rc_ideFrame::rc_ideFrame(wxWindow* parent,wxWindowID id)
{
    rc_initKeywords();
    wxFont rc_font(12,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL);
    rc_path =  wxStandardPaths::Get().GetExecutablePath();
    #ifndef RC_WINDOWS
        rc_path = rc_path.substr(0, rc_path.find_last_of(_("/"))) +_("/");
    #else
        rc_path = rc_path.substr(0, rc_path.find_last_of(_("\\"))) +_("\\");
    #endif
    //(*Initialize(rc_ideFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, _("RC Basic"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(640,480));
    SetMinSize(wxSize(640,480));
    SetExtraStyle( GetExtraStyle() | wxFRAME_EX_METAL );
    {
    	wxIcon FrameIcon;
    	#ifdef RC_WINDOWS
            FrameIcon.CopyFromBitmap(wxBitmap(wxImage(rc_path + _T("\\icon\\rcbasic.ico"))));
    	#else
            FrameIcon.CopyFromBitmap(wxBitmap(wxImage(rc_path + _T("/icon/rcbasic.ico"))));
    	#endif
    	SetIcon(FrameIcon);
    }

    wxBitmap PlayButton_Image;
    wxBitmap StopButton_Image;
    #ifdef RC_WINDOWS
        PlayButton_Image = wxBitmap(wxImage(rc_path + _T("\\icon\\play.png")));
        StopButton_Image = wxBitmap(wxImage(rc_path + _T("\\icon\\stop.png")));
    #else
        PlayButton_Image = wxBitmap(wxImage(rc_path + _T("/icon/play.bmp")));
        StopButton_Image = wxBitmap(wxImage(rc_path + _T("/icon/stop.png")));
    #endif

    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    AuiNotebook1 = new wxAuiNotebook(this, ID_AUINOTEBOOK1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE);
    BoxSizer1->Add(AuiNotebook1, 1, wxALL|wxEXPAND, 1);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem6 = new wxMenuItem(Menu1, newID, _("New\tCtrl-N"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem6);
    MenuItem5 = new wxMenuItem(Menu1, openID, _("Open\tCtrl-O"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem5);
    MenuItem4 = new wxMenuItem(Menu1, saveID, _("Save\tCtrl-S"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem4);
    MenuItem3 = new wxMenuItem(Menu1, saveAsID, _("Save As"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem7 = new wxMenuItem(Menu3, undoID, _("Undo"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem7);
    MenuItem8 = new wxMenuItem(Menu3, redoID, _("Redo"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem8);
    Menu3->AppendSeparator();
    MenuItem9 = new wxMenuItem(Menu3, cutID, _("Cut"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem9);
    MenuItem10 = new wxMenuItem(Menu3, copyID, _("Copy"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem10);
    MenuItem11 = new wxMenuItem(Menu3, pasteID, _("Paste"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem11);
    MenuItem12 = new wxMenuItem(Menu3, deleteID, _("Delete"), wxEmptyString, wxITEM_NORMAL);
    Menu3->Append(MenuItem12);
    MenuBar1->Append(Menu3, _("Edit"));
    Menu4 = new wxMenu();
    MenuItem13 = new wxMenuItem(Menu4, compileID, _("Compile\tF5"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem13);
    MenuItem14 = new wxMenuItem(Menu4, runID, _("Run\tF8"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem14);
    MenuItem16 = new wxMenuItem(Menu4, distributeID, _("Distribute"), wxEmptyString, wxITEM_NORMAL);
    Menu4->Append(MenuItem16);
    MenuBar1->Append(Menu4, _("Build"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuItem15 = new wxMenuItem(Menu2, referenceID, _("Reference"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(MenuItem15);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    ToolBar1 = new wxToolBar(this, ID_TOOLBAR1, wxDefaultPosition, wxDefaultSize, wxTB_HORIZONTAL|wxNO_BORDER, _T("ID_TOOLBAR1"));
    ToolBarItem1 = ToolBar1->AddTool(toolNewID, _("New File"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, _("New File"));
    ToolBarItem2 = ToolBar1->AddTool(toolOpenID, _("Open File"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_OPEN")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, _("Open File"));
    ToolBarItem3 = ToolBar1->AddTool(toolSaveID, _("Save File"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString);
    ToolBarItem4 = ToolBar1->AddTool(toolSaveAsID, _("Save File As"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE_AS")),wxART_TOOLBAR), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, _("Save File As"));
    ToolBar1->AddSeparator();
    ToolBarItem5 = ToolBar1->AddTool(toolRunID, _("Run Program"), PlayButton_Image, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, _("Run Program"));
    ToolBarItem6 = ToolBar1->AddTool(toolStopID, _("Stop Program"), StopButton_Image, wxNullBitmap, wxITEM_NORMAL, wxEmptyString, _("Abort Program"));
    ToolBar1->Realize();
    SetToolBar(ToolBar1);
    SetSizer(BoxSizer1);
    Layout();
    Center();

    Connect(newID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnNewPage);
    Connect(openID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnPageOpen);
    Connect(saveID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::onSavePage);
    Connect(saveAsID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnSavePageAs);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnQuit);
    Connect(undoID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnUndo);
    Connect(redoID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnRedo);
    Connect(cutID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnCut);
    Connect(copyID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnCopy);
    Connect(pasteID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnPaste);
    Connect(deleteID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnDelete);
    Connect(compileID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnCompile);
    Connect(runID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnRun);
    Connect(distributeID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnDistribute);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnAbout);
    Connect(referenceID,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&rc_ideFrame::OnReference);
    Connect(toolNewID,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&rc_ideFrame::OnNewPage);
    Connect(toolOpenID,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&rc_ideFrame::OnPageOpen);
    Connect(toolSaveID,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&rc_ideFrame::onSavePage);
    Connect(toolSaveAsID,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&rc_ideFrame::OnSavePageAs);
    Connect(toolRunID,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&rc_ideFrame::OnRun);
    Connect(toolStopID,wxEVT_COMMAND_TOOL_CLICKED,(wxObjectEventFunction)&rc_ideFrame::OnStop);
    //*)
}

rc_ideFrame::~rc_ideFrame()
{
    //(*Destroy(rc_ideFrame)
    //*)
}

void rc_ideFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void rc_ideFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _("RCBASIC Editor\nCopyright (C) 2015-2021 Rodney Cunningham ( aka n00b )\n\nFor latest release, updates, and info go to \nhttp://www.rcbasic.com\n\nAnd the forum at \nhttp://rcbasic.freeforums.net");
    wxMessageBox(msg);
}

void rc_ideFrame::OnNewPage(wxCommandEvent& event)
{
    wxString txtID_str = _("ID_RC_TXT") + wxString::Format(wxT("%i"),rc_current_page);
    rc_current_page++;
    //wxTextCtrl * rc_txtCtrl = new wxTextCtrl(AuiNotebook1, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_DONTWRAP, wxDefaultValidator, txtID_str);
    wxStyledTextCtrl * rc_txtCtrl = new wxStyledTextCtrl(AuiNotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, txtID_str);
    rc_txtCtrl->SetMarginType(0, wxSTC_MARGIN_NUMBER);
    rc_txtCtrl->SetMarginWidth(0, 40);
    rc_txtCtrl->SetUndoCollection(true);
    rc_txtCtrl->EmptyUndoBuffer();
    rc_txtCtrl->SetLexer(wxSTC_LEX_FREEBASIC);
    rc_txtCtrl->StyleSetForeground(wxSTC_B_KEYWORD, wxColour(0, 0, 210));
    rc_txtCtrl->StyleSetForeground(wxSTC_B_KEYWORD2, wxColour(0, 180, 0));
    rc_txtCtrl->StyleSetForeground(wxSTC_B_NUMBER, wxColour(200, 40, 40));
    rc_txtCtrl->StyleSetForeground(wxSTC_B_STRING, wxColour(230, 10, 230));
    rc_txtCtrl->StyleSetForeground(wxSTC_B_COMMENT, wxColour(128,128,128));
    rc_txtCtrl->SetKeyWords(0, rc_keywords);
    rc_txtCtrl->SetKeyWords(1, rc_keywords2);
    wxFont rc_font(12,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL);
    rc_txtCtrl->StyleSetFont(wxSTC_STYLE_DEFAULT, rc_font);
    rc_txtCtrl->SetTabWidth(4);
    rc_txtCtrl->Connect(wxEVT_STC_CHARADDED, wxStyledTextEventHandler(rc_ideFrame::OnDocumentKey), NULL, this);
    AuiNotebook1->AddPage(rc_txtCtrl, _("Untitled"));
    rc_fnames[AuiNotebook1->GetPageIndex(rc_txtCtrl)] = _("");
}

void rc_ideFrame::OnPageOpen(wxCommandEvent& event)
{
    wxFileDialog * FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_OPEN, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    FileDialog1->ShowModal();
    #ifndef RC_WINDOWS
        wxString rc_filename = FileDialog1->GetDirectory() + _("/") + FileDialog1->GetFilename();
    #else
        wxString rc_filename = FileDialog1->GetDirectory() + _("\\") + FileDialog1->GetFilename();
        wxString rc_tabname = FileDialog1->GetFilename();
    #endif
    //wxMessageBox(rc_filename);
    if(FileDialog1->GetReturnCode() == wxID_CANCEL)
    {
        FileDialog1->Destroy();
        return;
    }

    FileDialog1->Destroy();

    #ifndef RC_WINDOWS
    if(rc_filename.compare(_("/"))!=0)
    #else
    if(rc_filename.compare(_("\\"))!=0)
    #endif // RC_WINDOWS
    {
        wxFileInputStream input(rc_filename);

        if(input.IsOk())
        {
            wxString txtID_str = _("ID_RC_TXT") + wxString::Format(wxT("%i"),rc_current_page);
            rc_current_page++;
            wxStyledTextCtrl * rc_txtCtrl = new wxStyledTextCtrl(AuiNotebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, txtID_str);

            wxTextInputStream text(input);

            long i = 0;
            rc_txtCtrl->GotoPos(0);
            rc_txtCtrl->GotoLine(i);
            //wxString line=text.ReadLine();

            while(input.IsOk() && !input.Eof() )
            {
                //rc_txtCtrl->GotoPos(0);
                //rc_txtCtrl->GotoLine(i);
                wxString line=text.ReadLine();

                if(i > 0)
                    rc_txtCtrl->AddText( _("\n"));
                rc_txtCtrl->GotoPos(0);
                rc_txtCtrl->GotoLine(i);
                int spos = line.find_first_of("\r");
                if(spos == 0)
                    line = "\n";
                else if(spos != wxString::npos)
                    line = line.substr(0, spos+1);
                else
                    line = line.substr(0, line.find_last_not_of("\n")+1);
                rc_txtCtrl->AddText(line);
                i++;
            }

            //wxMessageBox(wxString::Format(wxT("%i"),(int)i));

            rc_txtCtrl->SetMarginType(0, wxSTC_MARGIN_NUMBER);
            rc_txtCtrl->SetMarginWidth(0, 40);
            rc_txtCtrl->SetUndoCollection(true);
            rc_txtCtrl->EmptyUndoBuffer();
            rc_txtCtrl->SetLexer(wxSTC_LEX_FREEBASIC);
            rc_txtCtrl->StyleSetForeground(wxSTC_B_KEYWORD, wxColour(0, 0, 210));
            rc_txtCtrl->StyleSetForeground(wxSTC_B_KEYWORD2, wxColour(0, 180, 0));
            rc_txtCtrl->StyleSetForeground(wxSTC_B_NUMBER, wxColour(200, 40, 40));
            rc_txtCtrl->StyleSetForeground(wxSTC_B_STRING, wxColour(230, 10, 230));
            rc_txtCtrl->StyleSetForeground(wxSTC_B_COMMENT, wxColour(128,128,128));
            rc_txtCtrl->SetKeyWords(0, rc_keywords);
            rc_txtCtrl->SetKeyWords(1, rc_keywords2);
            wxFont rc_font(12,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL);
            rc_txtCtrl->StyleSetFont(wxSTC_STYLE_DEFAULT, rc_font);
            rc_txtCtrl->SetTabWidth(4);
            rc_txtCtrl->Connect(wxEVT_STC_CHARADDED, wxStyledTextEventHandler(rc_ideFrame::OnDocumentKey), NULL, this);
            AuiNotebook1->AddPage(rc_txtCtrl, rc_tabname);
            rc_fnames[AuiNotebook1->GetPageIndex(rc_txtCtrl)] = rc_filename;
        }
    }
}

void rc_ideFrame::onSavePage(wxCommandEvent& event)
{
    if(AuiNotebook1->GetSelection() < 0)
    {
        wxMessageBox(_("Nothing to Save"));
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    //wxMessageBox(t->GetLabelText(),_("test"));


    if(rc_fnames[AuiNotebook1->GetPageIndex(t)].compare(_(""))!=0)
    {
        wxFileOutputStream output(rc_fnames[AuiNotebook1->GetPageIndex(t)]);

        if(output.IsOk())
        {
            wxTextOutputStream text(output);
            text.SetMode(wxEOL_UNIX);
            long i = 0;
            while(i < t->GetLineCount())
            {
                wxString line = t->GetLine(i);
                int spos = line.find_first_of("\n");
                if(spos == wxString::npos)
                    line = line + "\n";
                else
                    line = line.substr(0, spos) + "\n";
                //line = line;
                text.WriteString(line);
                i++;
            }
            output.Close();
        }
    }
    else
    {
        wxFileDialog * FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
        FileDialog1->ShowModal();
        #ifndef RC_WINDOWS
        wxString rc_filename = FileDialog1->GetDirectory() + _("/") + FileDialog1->GetFilename();
        wxString rc_tabname = FileDialog1->GetFilename();
        #else
        wxString rc_filename = FileDialog1->GetDirectory() + _("\\") + FileDialog1->GetFilename();
        wxString rc_tabname = FileDialog1->GetFilename();
        #endif
        //wxMessageBox(rc_filename);

        if(FileDialog1->GetReturnCode() == wxID_CANCEL)
        {
            FileDialog1->Destroy();
            return;
        }

        FileDialog1->Destroy();

        #ifndef RC_WINDOWS
        if(rc_filename.compare(_("/"))!=0)
        #else
        if(rc_filename.compare(_("\\"))!=0)
        #endif
        {
            wxFileOutputStream output(rc_filename);

            if(!output.IsOk())
            {
                output.Close();
                return;
            }

            wxTextOutputStream text(output);
            text.SetMode(wxEOL_UNIX);
            long i = 0;
            while(i < t->GetLineCount())
            {
                wxString line = t->GetLine(i);
                int spos = line.find_first_of("\n");
                if(spos == wxString::npos)
                    line = line + "\n";
                else
                    line = line.substr(0, spos) + "\n";
                //line = line;
                text.WriteString(line);
                i++;
            }
            output.Close();
            rc_fnames[AuiNotebook1->GetPageIndex(t)] = rc_filename;
            AuiNotebook1->SetPageText(AuiNotebook1->GetPageIndex(t), rc_tabname);
        }

    }
}

void rc_ideFrame::OnSavePageAs(wxCommandEvent& event)
{
    if(AuiNotebook1->GetSelection() < 0)
    {
        wxMessageBox(_("Nothing to Save"));
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    //wxMessageBox(t->GetLabelText(),_("test"));

    wxFileDialog * FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr,wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    FileDialog1->ShowModal();
    #ifndef RC_WINDOWS
    wxString rc_filename = FileDialog1->GetDirectory() + _("/") + FileDialog1->GetFilename();
    wxString rc_tabname = FileDialog1->GetFilename();
    #else
    wxString rc_filename = FileDialog1->GetDirectory() + _("\\") + FileDialog1->GetFilename();
    wxString rc_tabname = FileDialog1->GetFilename();
    #endif
    //wxMessageBox(rc_filename);

    if(FileDialog1->GetReturnCode() == wxID_CANCEL)
    {
        FileDialog1->Destroy();
        return;
    }

    FileDialog1->Destroy();

    #ifndef RC_WINDOWS
    if(rc_filename.compare(_("/"))!=0)
    #else
    if(rc_filename.compare(_("\\"))!=0)
    #endif
    {
        wxFileOutputStream output(rc_filename);

        if(!output.IsOk())
        {
            output.Close();
            return;
        }

        wxTextOutputStream text(output);
        text.SetMode(wxEOL_UNIX);
        long i = 0;
        while(i < t->GetLineCount())
        {
            wxString line = t->GetLine(i);
            int spos = line.find_first_of("\n");
            if(spos == wxString::npos)
                line = line + "\n";
            else
                line = line.substr(0, spos) + "\n";
            //line = line;
            text.WriteString(line);
            i++;
        }
        output.Close();
        rc_fnames[AuiNotebook1->GetPageIndex(t)] = rc_filename;
        AuiNotebook1->SetPageText(AuiNotebook1->GetPageIndex(t), rc_tabname);
    }
}

void rc_ideFrame::OnUndo(wxCommandEvent& event)
{
    if(AuiNotebook1->GetSelection() < 0)
    {
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    t->Undo();
}

void rc_ideFrame::OnRedo(wxCommandEvent& event)
{
    if(AuiNotebook1->GetSelection() < 0)
    {
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    t->Redo();
}

void rc_ideFrame::OnCut(wxCommandEvent& event)
{
    if(AuiNotebook1->GetSelection() < 0)
    {
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    t->Cut();
}

void rc_ideFrame::OnCopy(wxCommandEvent& event)
{
    if(AuiNotebook1->GetSelection() < 0)
    {
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    t->Copy();
}

void rc_ideFrame::OnPaste(wxCommandEvent& event)
{
    if(AuiNotebook1->GetSelection() < 0)
    {
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    t->Paste();
}

void rc_ideFrame::OnDelete(wxCommandEvent& event)
{
    if(AuiNotebook1->GetSelection() < 0)
    {
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    t->Clear();
}

void rc_ideFrame::OnCompile(wxCommandEvent& event)
{
    //wxMessageBox(wxString::Format(wxT("%i"),AuiNotebook1->GetSelection()),_("WX AUI"));
    if(AuiNotebook1->GetSelection() < 0)
    {
        wxMessageBox(_("Nothing to Compile"));
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    if(t == NULL)
        return;
    if(rc_fnames[AuiNotebook1->GetSelection()].compare(_(""))==0)
    {
        wxMessageDialog * MessageDialog1 = new wxMessageDialog(this, _("--You must save the file first."), wxEmptyString , wxOK, wxDefaultPosition);
        wxFileDialog * FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
        if(MessageDialog1->ShowModal() == wxID_OK)
        {
            //wxTextCtrl * t = (wxTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
            wxFileDialog * FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
            FileDialog1->ShowModal();
            #ifndef RC_WINDOWS
            wxString rc_filename = FileDialog1->GetDirectory() + _("/") + FileDialog1->GetFilename();
            wxString rc_tabname = FileDialog1->GetFilename();
            #else
            wxString rc_filename = FileDialog1->GetDirectory() + _("\\") + FileDialog1->GetFilename();
            wxString rc_tabname = FileDialog1->GetFilename();
            #endif
            //wxMessageBox(rc_filename);
            FileDialog1->Destroy();
            #ifndef RC_WINDOWS
            if(rc_filename.compare(_("/"))!=0)
            #else
            if(rc_filename.compare(_("\\"))!=0)
            #endif
            {
                wxFileOutputStream output(rc_filename);

                if(!output.IsOk())
                {
                    output.Close();
                    return;
                }

                wxTextOutputStream text(output);
                text.SetMode(wxEOL_UNIX);
                long i = 0;
                while(i < t->GetLineCount())
                {
                    wxString line = t->GetLine(i);
                    int spos = line.find_first_of("\n");
                    if(spos == wxString::npos)
                        line = line + "\n";
                    else
                        line = line.substr(0, spos) + "\n";
                    //line = line;
                    text.WriteString(line);
                    i++;
                }
                output.Close();
                rc_fnames[AuiNotebook1->GetPageIndex(t)] = rc_filename;
                AuiNotebook1->SetPageText(AuiNotebook1->GetPageIndex(t), rc_tabname);
            }
        }
        MessageDialog1->Destroy();
        FileDialog1->Destroy();
    }
    else
    {
        //wxMessageBox(_("File to Run = ") + rc_fnames[AuiNotebook1->GetSelection()]);
        wxFileOutputStream output(rc_fnames[AuiNotebook1->GetPageIndex(t)]);

        if(!output.IsOk())
        {
            output.Close();
            return;
        }

        wxTextOutputStream text(output);
        text.SetMode(wxEOL_UNIX);
        long i = 0;
        while(i < t->GetLineCount())
        {
            wxString line = t->GetLine(i);
            int spos = line.find_first_of("\n");
            if(spos == wxString::npos)
                line = line + "\n";
            else
                line = line.substr(0, spos) + "\n";
            //line = line;
            text.WriteString(line);
            i++;
        }
        output.Close();
    }

    #ifndef RC_WINDOWS
    wxSetWorkingDirectory(rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("/")));
    wxString fs = rc_path + _("rcbasic_build ") + _("\"") + rc_fnames[AuiNotebook1->GetPageIndex(t)] + _("\"");
    #else
    wxSetWorkingDirectory(rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("\\")));
    wxString fs = rc_path + _("rcbasic_build.exe ") + _("\"") + rc_fnames[AuiNotebook1->GetPageIndex(t)] + _("\"");
    #endif

    int rt = -1;
    rt = wxExecute(fs, wxEXEC_SYNC);
}

void rc_ideFrame::OnRun(wxCommandEvent& event)
{
    //wxMessageBox(wxString::Format(wxT("%i"),AuiNotebook1->GetSelection()),_("WX AUI"));
    if(AuiNotebook1->GetSelection() < 0)
    {
        wxMessageBox(_("Nothing to Run"));
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    if(t == NULL)
        return;
    if(rc_fnames[AuiNotebook1->GetSelection()].compare(_(""))==0)
    {
        wxMessageDialog * MessageDialog1 = new wxMessageDialog(this, _("--You must save the file first."), wxEmptyString , wxOK, wxDefaultPosition);
        wxFileDialog * FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
        if(MessageDialog1->ShowModal() == wxID_OK)
        {
            //wxTextCtrl * t = (wxTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
            wxFileDialog * FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
            FileDialog1->ShowModal();
            #ifndef RC_WINDOWS
            wxString rc_filename = FileDialog1->GetDirectory() + _("/") + FileDialog1->GetFilename();
            wxString rc_tabname = FileDialog1->GetFilename();
            #else
            wxString rc_filename = FileDialog1->GetDirectory() + _("\\") + FileDialog1->GetFilename();
            wxString rc_tabname = FileDialog1->GetFilename();
            #endif
            //wxMessageBox(rc_filename);
            FileDialog1->Destroy();

            #ifndef RC_WINDOWS
            if(rc_filename.compare(_("/"))!=0)
            #else
            if(rc_filename.compare(_("\\"))!=0)
            #endif
            {
                wxFileOutputStream output(rc_filename);

                if(!output.IsOk())
                {
                    output.Close();
                    return;
                }

                wxTextOutputStream text(output);
                text.SetMode(wxEOL_UNIX);
                long i = 0;
                while(i < t->GetLineCount())
                {
                    wxString line = t->GetLine(i);
                    int spos = line.find_first_of("\n");
                    if(spos == wxString::npos)
                        line = line + "\n";
                    else
                        line = line.substr(0, spos) + "\n";
                    //line = line;
                    text.WriteString(line);
                    i++;
                }
                output.Close();
                rc_fnames[AuiNotebook1->GetPageIndex(t)] = rc_filename;
                AuiNotebook1->SetPageText(AuiNotebook1->GetPageIndex(t), rc_tabname);
            }
        }
        MessageDialog1->Destroy();
        FileDialog1->Destroy();
    }
    else
    {
        //wxMessageBox(_("File to Run = ") + rc_fnames[AuiNotebook1->GetSelection()]);
        wxFileOutputStream output(rc_fnames[AuiNotebook1->GetPageIndex(t)]);

        if(!output.IsOk())
        {
            output.Close();
            return;
        }

        wxTextOutputStream text(output);
        text.SetMode(wxEOL_UNIX);
        long i = 0;
        while(i < t->GetLineCount())
        {
            wxString line = t->GetLine(i);
            int spos = line.find_first_of("\n");
            if(spos == wxString::npos)
                line = line + "\n";
            else
                line = line.substr(0, spos) + "\n";
            //line = line;
            text.WriteString(line);
            i++;
        }
        output.Close();
    }

    #ifndef RC_WINDOWS
    wxSetWorkingDirectory(rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("/")));
    wxString fs = rc_path + _("rcbasic_build ") + _("\"") + rc_fnames[AuiNotebook1->GetPageIndex(t)] + _("\"");
    #else
    //wxMessageBox(_("Set Dir: ") + rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("\\")));
    wxSetWorkingDirectory(rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("\\")));
    wxString fs = rc_path + _("rcbasic_build.exe ") + _("\"") + rc_fnames[AuiNotebook1->GetPageIndex(t)] + _("\"");
    #endif

    int rt = -1;
    rt = wxExecute(fs, wxEXEC_SYNC);

    #ifndef RC_WINDOWS
    fs = rc_path + _("rcbasic ") + _("\"") + rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_first_of(".")) + _(".cbc\"");
    #else
    wxShell(_("cls"));
    fs = rc_path + _("rcbasic.exe ") + _("\"") + rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_first_of(".")) + _(".cbc\"");
    #endif // RC_WINDOWS
    vm_process = new MyProcess(this);
    pid = wxExecute(fs, wxEXEC_ASYNC | wxEXEC_MAKE_GROUP_LEADER, vm_process);
}

void rc_ideFrame::OnDistribute(wxCommandEvent& event)
{
    //wxMessageBox(wxString::Format(wxT("%i"),AuiNotebook1->GetSelection()),_("WX AUI"));
    if(AuiNotebook1->GetSelection() < 0)
    {
        wxMessageBox(_("Nothing to Port"));
        return;
    }
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    if(t == NULL)
        return;
    if(rc_fnames[AuiNotebook1->GetSelection()].compare(_(""))==0)
    {
        wxMessageDialog * MessageDialog1 = new wxMessageDialog(this, _("--You must save the file first."), wxEmptyString , wxOK, wxDefaultPosition);
        wxFileDialog * FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
        if(MessageDialog1->ShowModal() == wxID_OK)
        {
            //wxTextCtrl * t = (wxTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
            wxFileDialog * FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
            FileDialog1->ShowModal();
            #ifndef RC_WINDOWS
            wxString rc_filename = FileDialog1->GetDirectory() + _("/") + FileDialog1->GetFilename();
            wxString rc_tabname = FileDialog1->GetFilename();
            #else
            wxString rc_filename = FileDialog1->GetDirectory() + _("\\") + FileDialog1->GetFilename();
            wxString rc_tabname = FileDialog1->GetFilename();
            #endif
            //wxMessageBox(rc_filename);
            FileDialog1->Destroy();

            #ifndef RC_WINDOWS
            if(rc_filename.compare(_("/"))!=0)
            #else
            if(rc_filename.compare(_("\\"))!=0)
            #endif
            {
                wxFileOutputStream output(rc_filename);

                if(!output.IsOk())
                {
                    output.Close();
                    return;
                }

                wxTextOutputStream text(output);
                text.SetMode(wxEOL_UNIX);
                long i = 0;
                while(i < t->GetLineCount())
                {
                    wxString line = t->GetLine(i);
                    int spos = line.find_first_of("\n");
                    if(spos == wxString::npos)
                        line = line + "\n";
                    else
                        line = line.substr(0, spos) + "\n";
                    //line = line;
                    text.WriteString(line);
                    i++;
                }
                output.Close();
                rc_fnames[AuiNotebook1->GetPageIndex(t)] = rc_filename;
                AuiNotebook1->SetPageText(AuiNotebook1->GetPageIndex(t), rc_tabname);
            }
        }
        MessageDialog1->Destroy();
        FileDialog1->Destroy();
    }
    else
    {
        //wxMessageBox(_("File to Run = ") + rc_fnames[AuiNotebook1->GetSelection()]);
        wxFileOutputStream output(rc_fnames[AuiNotebook1->GetPageIndex(t)]);

        if(!output.IsOk())
        {
            output.Close();
            return;
        }

        wxTextOutputStream text(output);
        text.SetMode(wxEOL_UNIX);
        long i = 0;
        while(i < t->GetLineCount())
        {
            wxString line = t->GetLine(i);
            int spos = line.find_first_of("\n");
            if(spos == wxString::npos)
                line = line + "\n";
            else
                line = line.substr(0, spos) + "\n";
            //line = line;
            text.WriteString(line);
            i++;
        }
        output.Close();
    }

    wxString RC_PKG_HOME;
    wxGetEnv(_("RC_PKG_HOME"), &RC_PKG_HOME);

    #ifndef RC_WINDOWS
    wxString call_dir = rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("/"));
    wxString f_name = rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("/")+1);
    wxString fs = rc_path + _("rcbasic ") + _("\"") + RC_PKG_HOME + _("/app_build_gui\" \"") + call_dir + _("\" \"") + f_name + _("\"");
    #else
    wxString call_dir = rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(0, rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("\\"));
    wxString f_name = rc_fnames[AuiNotebook1->GetPageIndex(t)].substr(rc_fnames[AuiNotebook1->GetPageIndex(t)].find_last_of("\\")+1);
    wxString fs = rc_path + _("rcbasic ") + _("\"") + RC_PKG_HOME + _("\\app_build_gui\" \"") + call_dir + _("\" \"") + f_name + _("\"");
    #endif

    //wxPuts(_("cmd -> ") + fs);

    int rt = -1;
    rt = wxExecute(fs, wxEXEC_SYNC);
}

void rc_ideFrame::OnReference(wxCommandEvent& event)
{
    //wxMessageBox(_("Refer to the documentation in " + rc_path));
    #ifndef RC_WINDOWS
    wxLaunchDefaultBrowser(_("http://rcbasic.online/doc/rcbasic_manual.html"));
    #else
    wxLaunchDefaultBrowser(_("http://rcbasic.online/doc/rcbasic_manual.html"));
    #endif
}

void rc_ideFrame::OnDocumentKey(wxStyledTextEvent& event)
{
    wxStyledTextCtrl * t = (wxStyledTextCtrl*)AuiNotebook1->GetPage(AuiNotebook1->GetSelection());
    char chr = event.GetKey();
    int currentLine = t->GetCurrentLine();
    int indent = 0;

    if(chr == '\n')
    {
        //wxMessageBox(_("Current Line = ") + wxString::Format("%i",currentLine));
        if(currentLine > 0)
        {
            indent = t->GetLineIndentation(currentLine-1);
        }
        if(indent == 0)
            return;
        //wxMessageBox(_("Position from line = ") + wxString::Format("%i",t->PositionFromLine(currentLine)));
        t->SetLineIndentation(currentLine, indent);
        t->GotoPos(t->GetLineIndentPosition(currentLine));
    }

}

void rc_ideFrame::OnStop(wxCommandEvent& event)
{
    if(pid != -1)
    {
        //wxMessageBox("Kill process");
        wxKill(pid, wxSIGKILL, NULL, wxKILL_CHILDREN);
        //std::cout << "program aborted" << endl;
        pid = -1;
    }
}
