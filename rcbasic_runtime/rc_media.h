#include "rc_os_defines.h"

#ifdef RC_ANDROID
#define RC_MOBILE
#endif

#ifdef RC_IOS
#define RC_MOBILE
#endif


#ifdef RC_ANDROID

#include <android/log.h>
//Using SDL and standard IO
#include "SDL.h"
#include "SDL_image.h"
#include "SDL2_gfxPrimitives.h"
#include "SDL_ttf.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include "SDL_mixer.h"
#include "SDL_net.h"
//#include "../SDL/src/core/android/SDL_android.h"

//#include "../SDL/src/dynapi/SDL_dynapi_overrides.h"

//#include "../soft_render/SDL_rotate.c"

#include <assert.h>

#include "theoraplay.h"

#else

#ifdef RC_IOS

//Using SDL and standard IO
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_net.h"

#include <assert.h>

#include "theoraplay.h"

#else
//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "theoraplay.h"

#endif //RC_IOS

#endif // RC_ANDROID

//#include "soft_render/SDL_rotate.c"

#include <set>

using namespace std;

#ifdef RC_MOBILE
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int MAX_WINDOWS = 1;  //8
const int MAX_SCREENS = 8; //32
const int MAX_IMAGES = 4096; //65536;
const int MAX_SPRITES = 32; //1024;
const int MAX_SOUNDS = 1024;
const int MAX_MUSIC = 1;
const int MAX_FONTS = 32;
const int MAX_FINGERS = 10;
const int MAX_SOCKETS = 256;
const int MAX_ACCELS = 20;
const int MAX_GYROS = 20;
const int MAX_JOYSTICKS = 8;
#else

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int MAX_WINDOWS = 8;  //8
const int MAX_SCREENS = 8; //32
const int MAX_IMAGES = 4096; //65536;
const int MAX_SOUNDS = 1024;
const int MAX_MUSIC = 1;
const int MAX_FONTS = 32;
const int MAX_FINGERS = 10;
const int MAX_SOCKETS = 256;
const int MAX_ACCELS = 20;
const int MAX_GYROS = 20;
const int MAX_JOYSTICKS = 8;
#endif // RC_MOBILE

SDL_Window * rc_win[MAX_WINDOWS];
int rc_win_event[MAX_WINDOWS];
SDL_Texture * rc_backBuffer[MAX_WINDOWS];
SDL_Rect rc_bb_rect[MAX_WINDOWS];
SDL_Surface * rc_win_surface[MAX_WINDOWS];
SDL_Renderer * rc_win_renderer[MAX_WINDOWS];
Uint32 rc_win_id[MAX_WINDOWS];
bool rc_win_exitOnClose[MAX_WINDOWS];

Uint32 rc_screen_format[MAX_WINDOWS];

SDL_Texture * rc_himage[MAX_IMAGES][MAX_WINDOWS];
SDL_Rect rc_himage_rect[MAX_IMAGES];
bool rc_image_isLoaded[MAX_IMAGES];

SDL_Texture * rc_hscreen[MAX_WINDOWS][MAX_SCREENS];
SDL_Surface * rc_sscreen[MAX_WINDOWS][MAX_SCREENS];
SDL_Rect rc_screen_rect[MAX_WINDOWS][MAX_SCREENS];
int rc_screen_z[MAX_WINDOWS][MAX_SCREENS];
SDL_Rect rc_screenview[MAX_WINDOWS][MAX_SCREENS];
int rc_screen_width[MAX_WINDOWS][MAX_SCREENS];
int rc_screen_height[MAX_WINDOWS][MAX_SCREENS];
Uint8 rc_screen_transparent[MAX_WINDOWS][MAX_SCREENS];
int rc_screen_zOrder[MAX_WINDOWS][MAX_SCREENS];
bool rc_screen_visible[MAX_WINDOWS][MAX_SCREENS];

SDL_Surface * rc_simage[MAX_IMAGES];
SDL_Rect rc_image_rect[MAX_IMAGES];
Uint32 rc_image_width[MAX_IMAGES];
Uint32 rc_image_height[MAX_IMAGES];
Uint32 rc_image_colorKey[MAX_IMAGES];
Uint8 rc_image_colorKey_r[MAX_IMAGES];
Uint8 rc_image_colorKey_g[MAX_IMAGES];
Uint8 rc_image_colorKey_b[MAX_IMAGES];
Uint8 rc_image_colorKey_a[MAX_IMAGES];

int rc_active_window = -1;
int rc_active_screen = -1;

Uint32 rc_ink = 0x00000000;
SDL_Color rc_ink_color;
Uint32 rc_paper = 0x00000000;
Uint32 rc_clearColor = 0x00000000;
Uint32 rc_colorKey = 0x00000000;
SDL_Color rc_colorKey_color;
int rc_colorKey_switch = 0;

int rc_console_width[MAX_WINDOWS]; //number of characters wide
int rc_console_height[MAX_WINDOWS]; //number of rows
int rc_sConsole_x[MAX_WINDOWS];
int rc_sConsole_y[MAX_WINDOWS];
Uint8 rc_cursor_visible = 1;
SDL_Color rc_console_pen;
int rc_pen_color = 0x00FFFFFF;
SDL_Surface * rc_console = NULL;
SDL_Texture * rc_hconsole[MAX_WINDOWS];
TTF_Font * rc_console_font = NULL;
string rc_input_buffer = "";

TTF_Font * rc_draw_font[MAX_FONTS];
string rc_draw_font_path = "";
int rc_active_font = -1;

int rc_inkey = 0;
SDL_Keycode rc_keycode;
SDL_Scancode rc_scancode;
SDL_Keymod rc_keymod;
int rc_mouseX = 0;
int rc_mouseY = 0;
int rc_mbutton1 = 0;
int rc_mbutton2 = 0;
int rc_mbutton3 = 0;
int rc_mwheelx = 0;
int rc_mwheely = 0;

//SDL_Event event;

Uint32 prev_color = 0;

bool rc_engine_isRunning = false;
bool rc_engine_isInitialized = false;
bool rc_media_isActive = false;

const Uint8 * keyState = NULL;

SDL_Joystick * rc_joystick[MAX_JOYSTICKS];
int rc_joy_axis[MAX_JOYSTICKS][100];
int rc_numJoysticks = 0;
int rc_joybutton[MAX_JOYSTICKS][100];
SDL_JoystickID rc_joyID[MAX_JOYSTICKS];

SDL_Joystick * tmp_joy;
SDL_JoystickID tmp_joy_id;
int tmp_joy_flag = 0;

SDL_Haptic * rc_haptic[MAX_JOYSTICKS]; //1 for each joystick

double rc_pressure = 0;
int rc_touchX = 0;
int rc_touchY = 0;
int rc_motionX = 0;
int rc_motionY = 0;
int rc_touch = 0;
int rc_mt_status = 0;
int rc_mt_x = 0;
int rc_mt_y = 0;
int rc_mt_numFingers = 0;
double rc_mt_theta = 0;
double rc_mt_dist = 0;
SDL_TouchID rc_touchDevice;
SDL_Finger rc_finger[MAX_FINGERS];
set<int> rc_fingers_pressed;

SDL_Sensor * rc_accel[MAX_ACCELS];
int num_accels = 0;

SDL_Sensor * rc_gyro[MAX_GYROS];
int num_gyros = 0;

int rc_win_width[MAX_WINDOWS];
int rc_win_height[MAX_WINDOWS];

Uint32 rc_update_timer = 0;
Uint32 rc_auto_time = 0;
int rc_update_flag = 0;

Mix_Chunk * rc_sound[MAX_SOUNDS];
Mix_Music * rc_music;

TCPsocket rc_socket[MAX_SOCKETS];

UDPsocket rc_udp_socket[MAX_SOCKETS];
UDPpacket * rc_udp_packet;
int rc_udp_channel;
string rc_udp_data;
int rc_udp_len;
int rc_udp_maxlen;
string rc_udp_host;
Uint16 rc_udp_port;
int rc_packet_size = 0;
SDLNet_SocketSet rc_socket_set;


SDL_PixelFormat * rc_pformat;
SDL_DisplayMode rc_displayMode[MAX_WINDOWS];

string rc_textinput_string = "";
//string * rc_textinput_oldString;
string rc_textinput_char = "";
int rc_textinput_timer = 0;
int rc_textinput_delay = 100;
bool rc_textinput_flag = true;
bool rc_textinput_isActive = false;
int rc_textinput_waitHold = 800;
bool rc_textinput_hold = false;
bool rc_toggleBackspace = true;


static Uint32 baseticks = 0;

uint32_t rc_fps[MAX_WINDOWS];
uint32_t rc_fps_frames[MAX_WINDOWS];
uint32_t rc_fps_timer[MAX_WINDOWS];

#ifdef RC_MOBILE
double rc_mouse_scale_x = 0;
double rc_mouse_scale_y = 0;
#else
double rc_fullscreen_mouse_scale_x[MAX_WINDOWS];
double rc_fullscreen_mouse_scale_y[MAX_WINDOWS];
#endif // RC_MOBILE

typedef struct AudioQueue
{
    const THEORAPLAY_AudioPacket *audio;
    int offset;
    struct AudioQueue *next;
} AudioQueue;

static volatile AudioQueue *audio_queue = NULL;
static volatile AudioQueue *audio_queue_tail = NULL;

THEORAPLAY_Decoder *decoder = NULL;
const THEORAPLAY_VideoFrame *video = NULL;
const THEORAPLAY_AudioPacket *audio = NULL;
SDL_Texture * overlay = NULL;
void * overlay_pixels;
int pitch;
SDL_Event event;
Uint32 framems = 0;
int initfailed = 0;
int quit = 0;
bool rc_video_isPlaying = false;
Uint32 rc_video_position = 0;
bool rc_video_reset = false;
int rc_video_loops = 0;
const THEORAPLAY_AudioPacket * first_audio = NULL;
const THEORAPLAY_VideoFrame * first_video = NULL;
bool rc_audio_isOpen = false;
bool rc_video_isLoaded = false;
string rc_video_file = "";
bool rc_video_isPaused = false;
Uint32 rc_video_pauseTicks = 0;
bool rc_video_end = false;
SDL_Rect rc_video_dstrect;
int rc_video_width = 0;
int rc_video_height = 0;
int rc_video_length = 0;
int rc_video_fps = 0;
int rc_video_currentLoop = 0;

bool mobile_active_window_flag = true;

void rc_setTouchFingerEvent(SDL_FingerID fingerID, double x, double y, double pressure)
{
    for(int i = 0; i < MAX_FINGERS; i++)
    {
        if(rc_finger[i].id == -1 || rc_finger[i].id == fingerID)
        {
            rc_finger[i].id = fingerID;
            rc_finger[i].x = x;
            rc_finger[i].y = y;
            rc_finger[i].pressure = pressure;
            if(rc_finger[i].pressure > 0)
            {
                rc_fingers_pressed.insert(i);
            }
            return;
        }
    }
}

int mobile_event_filter(void* userdata, SDL_Event* evt)
{
    SDL_Event event = evt[0];
    switch(evt->type)
    {
        case SDL_APP_WILLENTERBACKGROUND:
            mobile_active_window_flag = false;
            break;
        case SDL_APP_DIDENTERFOREGROUND:
            if(!mobile_active_window_flag)
            {
                //rc_win_renderer[0] = SDL_GetRenderer(rc_win[0]);
            }
            mobile_active_window_flag = true;
            break;

        case SDL_FINGERDOWN:
            rc_touch = 1;
            rc_touchX = event.tfinger.x * rc_win_width[rc_active_window];
            rc_touchY = event.tfinger.y * rc_win_height[rc_active_window];
#ifdef RC_IOS
            rc_pressure = 1; //FIXME: On IOS pressure is always getting reported as 0 on finger down so I am just setting it to 1 until I figure this out
#else
            rc_pressure = event.tfinger.pressure;
#endif
            rc_setTouchFingerEvent(event.tfinger.fingerId, rc_touchX, rc_touchY, rc_pressure);
            break;
        case SDL_FINGERUP:
            rc_touch = 0;
            rc_mt_status = 0;
            rc_touchX = event.tfinger.x * rc_win_width[rc_active_window];
            rc_touchY = event.tfinger.y * rc_win_height[rc_active_window];
            rc_pressure = event.tfinger.pressure;
            rc_setTouchFingerEvent(event.tfinger.fingerId, -1, -1, 0);
            break;
        case SDL_FINGERMOTION:
            rc_touch = 1;
            rc_touchX = event.tfinger.x * rc_win_width[rc_active_window];
            rc_touchY = event.tfinger.y * rc_win_height[rc_active_window];
            rc_motionX = event.tfinger.dx * rc_win_width[rc_active_window];
            rc_motionY = event.tfinger.dy * rc_win_height[rc_active_window];
#ifdef RC_IOS
            rc_pressure = 1;
#else
            rc_pressure = event.tfinger.pressure;
#endif
            rc_setTouchFingerEvent(event.tfinger.fingerId, rc_touchX, rc_touchY, rc_pressure);
            break;
        case SDL_MULTIGESTURE:
            rc_touch = 2;
            rc_mt_status = 1;
            rc_mt_x = event.mgesture.x;
            rc_mt_y = event.mgesture.y;
            rc_mt_numFingers = event.mgesture.numFingers;
            rc_mt_dist = event.mgesture.dDist;
            rc_mt_theta = event.mgesture.dTheta;
#ifdef RC_IOS
            rc_pressure = 1;
#else
            rc_pressure = event.tfinger.pressure;
#endif
            break;

    }
    return 0;
}

bool rc_media_init()
{
    rc_socket_set = SDLNet_AllocSocketSet(MAX_SOCKETS*2); //*2 for udp and tcp

    if(rc_socket_set == NULL)
    {
        cout << "Init Error: " << SDL_GetError() << endl;
    }

    for(int i = 0; i < MAX_SOCKETS; i++)
    {
        rc_socket[i] = NULL;
        rc_udp_socket[i] = NULL;
    }

    for(int i = 0; i < MAX_FONTS; i++)
        rc_draw_font[i] = NULL;

    for(int i = 0; i < MAX_SOUNDS; i++)
        rc_sound[i] = NULL;

    rc_music = NULL;

    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        rc_win[i] = NULL;
        rc_win_surface[i] = NULL;
        rc_win_renderer[i] = NULL;
        rc_win_id[i] = 0;
        rc_hconsole[i] = NULL;
        rc_backBuffer[i] = NULL;
        rc_bb_rect[i].x = 0;
        rc_bb_rect[i].y = 0;
        rc_bb_rect[i].w = 0;
        rc_bb_rect[i].h = 0;

        rc_fps[i] = 0;
        rc_fps_frames[i] = 0;
        rc_fps_timer[i] = 0;

        for(int j = 0; j < MAX_SCREENS; j++)
        {
            rc_hscreen[i][j] = NULL;
            rc_sscreen[i][j] = NULL;
            rc_screen_rect[i][j].x = 0;
            rc_screen_rect[i][j].y = 0;
            rc_screen_rect[i][j].w = 0;
            rc_screen_rect[i][j].h = 0;
            rc_screen_z[i][j] = j;
            rc_screen_zOrder[i][j] = j;
            rc_screen_visible[i][j] = false;
        }
    }
    for(int i = 0; i < MAX_IMAGES; i++)
    {
        for(int w = 0; w < MAX_WINDOWS; w++)
            rc_himage[i][w] = NULL;

        rc_simage[i] = NULL;
        rc_image_rect[i].x = 0;
        rc_image_rect[i].y = 0;
        rc_image_rect[i].w = 0;
        rc_image_rect[i].h = 0;
        rc_image_isLoaded[i] = false;
    }
    rc_ink_color.r = 0;
    rc_ink_color.g = 0;
    rc_ink_color.b = 0;
    rc_ink_color.a = 0;
    #ifdef RC_WEB
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    #else
    if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_SENSOR) < 0)
    #endif
    {
        cout << "Init Error: " << SDL_GetError() << endl;
        //return false;
    }

    #ifdef RC_MOBILE
        SDL_SetEventFilter(mobile_event_filter, NULL);
    #endif // RC_MOBILE

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) < 0)
    {
        cout << "IMG Init Error: " << IMG_GetError() << endl;
        //return false;
    }

    if(TTF_Init() < 0)
    {
        cout << "TTF Init Error: " << TTF_GetError() << endl;
        //return false;
    }

    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "OpenAudio Error: " << Mix_GetError() << endl;
    }

    if (SDLNet_Init() < 0)
	{
		fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

    for(int i = 0; i < MAX_FINGERS; i++)
    {
        rc_finger[i].id = -1;
        rc_finger[i].x = -1;
        rc_finger[i].y = -1;
        rc_finger[i].pressure = 0;
    }

    for(int i = 0; i < SDL_NumSensors(); i++)
    {
        rc_accel[num_accels] =  NULL;
        rc_gyro[num_gyros] =    NULL;
        switch(SDL_SensorGetDeviceType(i))
        {
            case SDL_SENSOR_ACCEL:
                rc_accel[num_accels] = SDL_SensorOpen(i);
                num_accels++;
                break;
            case SDL_SENSOR_GYRO:
                rc_gyro[num_gyros] = SDL_SensorOpen(i);
                num_gyros++;
                break;
        }
    }

	rc_pformat = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);

	//rc_active_font = -1;

	rc_udp_packet = SDLNet_AllocPacket(512);
	rc_packet_size = 512;

    rc_console_pen.r = 255;
    rc_console_pen.g = 255;
    rc_console_pen.b = 255;
    rc_console_pen.a = 0;
    rc_media_isActive = true;

    for(int i = 0; i < MAX_JOYSTICKS; i++)
    {
        if(i < SDL_NumJoysticks())
        {
            rc_joystick[i] = SDL_JoystickOpen(i);
            if(rc_joystick[i]==NULL)
            {
                cout << "Joystick " << i << " could not be opened: " << SDL_GetError() << endl;
            }
            rc_joyID[i] = SDL_JoystickInstanceID(rc_joystick[i]);
            #ifdef RC_WEB
            rc_haptic[i] = NULL;
            #else
            rc_haptic[i] = SDL_HapticOpenFromJoystick(rc_joystick[i]);
            SDL_HapticRumbleInit(rc_haptic[i]);
            #endif
            //if(rc_haptic[i] == NULL){ cout << "HAP NULL: " << SDL_GetError() << endl; }
            rc_numJoysticks++;
        }
        else
        {
            rc_joystick[i] = NULL;
            rc_haptic[i] =  NULL;
            rc_joyID[i] = -1;
        }
    }
    SDL_SetHint("SDL_JOYSTICK_ALLOW_BACKGROUND_EVENTS", "1");

    return true;
}

void rc_media_quit()
{
    for(int i = 0; i < MAX_FONTS; i++)
    {
        if(rc_draw_font[i] != NULL)
            TTF_CloseFont(rc_draw_font[i]);
    }

    //cout << "Font closed" << endl;

    for(int i = 0; i < MAX_SOUNDS; i++)
    {
        if(rc_sound[i] != NULL)
            Mix_FreeChunk(rc_sound[i]);
        rc_sound[i] = NULL;
    }
    if(rc_music != NULL)
        Mix_FreeMusic(rc_music);
    rc_music = NULL;

    for(int i = 0; i < MAX_JOYSTICKS; i++)
    {
        SDL_JoystickClose(rc_joystick[i]);
        SDL_HapticClose(rc_haptic[i]);
    }

    //cout << "Music Closed" << endl;

    for(int i = 0; i < MAX_WINDOWS; i++)
    {

        //cout << "Destroy Canvases" << endl;

        for(int j = 0; j < MAX_SCREENS; j++)
        {
            if(rc_sscreen[i][j] != NULL)
            {
                //cout << "Free Surface rc_sscreen[" << i << "][" << j << "]  -----  ";
                SDL_FreeSurface(rc_sscreen[i][j]);
                //cout << "SUCCESS\n";
                //SDL_DestroyTexture(rc_hscreen[i][j]);
            }
            if(rc_hscreen[i][j] != NULL)
            {
                SDL_DestroyTexture(rc_hscreen[i][j]);
            }
        }

        //cout << "Destroy Images" << endl;

        for(int j = 0; j < MAX_IMAGES; j++)
        {
            if(rc_himage[j][i] != NULL)
                SDL_DestroyTexture(rc_himage[j][i]);
            rc_himage[j][i] = NULL;
        }

        //cout << "Destroy Window #" << i << endl;

        if(rc_win[i] != NULL)
        {
            SDL_DestroyRenderer(rc_win_renderer[i]);
            rc_win_renderer[i] = NULL;
            SDL_DestroyWindow(rc_win[i]);
            rc_win[i] = NULL;
        }
    }

    //cout << "NORMAL BOOTS" << endl;

    if(audio)
    {
        THEORAPLAY_freeAudio(audio);
        audio = NULL;
    }
    if(video)
    {
        THEORAPLAY_freeVideo(video);
        video = NULL;
    }
    if(decoder)
    {
        THEORAPLAY_stopDecode(decoder);
        decoder = NULL;
    }
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    if(rc_socket_set)
    {
        SDLNet_FreeSocketSet(rc_socket_set);
        rc_socket_set = NULL;
    }
    //SDLNet_FreePacket(rc_udp_packet);
	SDLNet_Quit();
    SDL_Quit();
}

int rc_debug_msg(string msg)
{
    const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "no" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        msg.c_str(), /* .title */
        "select a button", /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return 1;
    }
    if (buttonid == -1) {
        SDL_Log("no selection");
    } else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }
    return 0;
}

inline Uint32 rc_media_windowMode(int visible_flag, int fullscreen_flag, int resizable_flag, int borderless_flag, int highDPI_flag)
{
    Uint32 window_mode = ( visible_flag == 0 ? SDL_WINDOW_HIDDEN : SDL_WINDOW_SHOWN ) |
                         ( fullscreen_flag == 0 ? 0 : SDL_WINDOW_FULLSCREEN_DESKTOP ) |
                         ( resizable_flag == 0 ? 0 : SDL_WINDOW_RESIZABLE ) |
                         ( borderless_flag == 0 ? 0 : SDL_WINDOW_BORDERLESS ) |
                         ( highDPI_flag == 0 ? 0 : SDL_WINDOW_ALLOW_HIGHDPI );
    return window_mode;
}

inline Uint32 rc_media_windowFlags(int win_num)
{
    if(win_num < 0 || win_num >= MAX_WINDOWS)
    {
        cout << "Window #" << win_num << " is not an available Window Slot" << endl;
        return 0;
    }
    if(rc_win[win_num] == NULL)
    {
        cout << "Window #" << win_num << " is not currently open" << endl;
        return 0;
    }
    return SDL_GetWindowFlags(rc_win[win_num]);
}

inline bool rc_media_openWindow_hw(int win_num, string caption, int x, int y, int w, int h, Uint32 flags, int vsync_flag)
{
    //cout << "start windowOpen" << endl;
    if(win_num < 0 || win_num >= MAX_WINDOWS)
    {
        cout << "Window #" << win_num << " is not an available Window Slot" << endl;
        return false;
    }
    if(rc_win[win_num] != NULL)
    {
        cout << "Window #" << win_num << " is currently open" << endl;
        return false;
    }

    bool vsync = vsync_flag == 0 ? false : true;
    rc_win_exitOnClose[win_num] = true;

    #ifdef RC_MOBILE
		flags = flags | SDL_WINDOW_FULLSCREEN_DESKTOP;
	#endif // RC_MOBILE

    rc_win[win_num] = SDL_CreateWindow(caption.c_str(), x, y, w, h, flags);
    if(rc_win[win_num] == NULL)
    {
        cout << "Error: " << SDL_GetError() << endl;
        return false;
    }

    if(rc_active_window == -1)
        rc_active_window = win_num;

    //rc_win_surface[win_num] = SDL_GetWindowSurface(rc_win[win_num]);
    rc_win_id[win_num] = SDL_GetWindowID(rc_win[win_num]);

    rc_win_width[win_num] = w;
    rc_win_height[win_num] = h;
    //SDL_SetSurfaceRLE(rc_win_surface[win_num],1);
    //rc_console = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    //SDL_SetColorKey(rc_console, SDL_TRUE, rc_clearColor);
    //cout << "boob physics" << endl;

#ifdef RC_MOBILE
    rc_win_renderer[win_num] = SDL_GetRenderer(rc_win[win_num]);
    if(rc_win_renderer[win_num] != NULL)
    {
        SDL_DestroyRenderer(rc_win_renderer[win_num]);
    }
#endif // RC_MOBILE

    if(vsync)
        rc_win_renderer[win_num] = SDL_CreateRenderer(rc_win[win_num], -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC);
    else
        rc_win_renderer[win_num] = SDL_CreateRenderer(rc_win[win_num], -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);


    if(rc_win_renderer[win_num] == NULL)
    {
#ifdef RC_ANDROID
        //rc_debug_msg("No Renderer");
        __android_log_write(ANDROID_LOG_ERROR, "This is crazy: ", SDL_GetError());
        rc_win_renderer[win_num] = SDL_GetRenderer(rc_win[win_num]);
        if(rc_win_renderer[win_num] == NULL)
        {
            __android_log_write(ANDROID_LOG_ERROR, "Renderer Error: ", SDL_GetError());
            exit(0);
        }
        SDL_DestroyRenderer(rc_win_renderer[win_num]);
        rc_win_renderer[win_num] = NULL;
        if(vsync)
            rc_win_renderer[win_num] = SDL_CreateRenderer(rc_win[win_num], -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
        else
            rc_win_renderer[win_num] = SDL_CreateRenderer(rc_win[win_num], -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

        if(rc_win_renderer[win_num] == NULL)
        {
            __android_log_write(ANDROID_LOG_ERROR, "Renderer Error2: ", SDL_GetError());
            exit(0);
        }
#else
        cout << "WindowOpen Error: " << SDL_GetError() << endl;
        exit(0);
#endif
    }

    SDL_SetRenderDrawBlendMode(rc_win_renderer[win_num], SDL_BLENDMODE_BLEND);

    //cout << "booty" << endl;

#ifndef RC_MOBILE

    for(int i = 0; i < MAX_IMAGES; i++)
    {
        if(rc_image_isLoaded[i])
        {
            for(int w = 0; w < MAX_WINDOWS; w++)
            {
                if(rc_win[w] != NULL && rc_himage[i][w]==NULL)
                {
                    SDL_Surface * tmp_surf = SDL_CreateRGBSurface(0, rc_image_width[i], rc_image_height[i], 32, 0, 0, 0, 0);
                    //cout << "ColorKey = " << (Uint32)rc_image_colorKey_r[i] << ", ";
                    //cout << (Uint32)rc_image_colorKey_g[i] << ", ";
                    //cout << (Uint32)rc_image_colorKey_b[i] << ", ";
                    //cout << (Uint32)rc_image_colorKey_a[i] << endl;
                    SDL_FillRect(tmp_surf, NULL, rc_image_colorKey[i]);
                    SDL_SetRenderTarget(rc_win_renderer[w], NULL);
                    SDL_Rect t_rect;
                    t_rect.x = 0;
                    t_rect.y = 0;
                    t_rect.w = tmp_surf->w;
                    t_rect.h = tmp_surf->h;
                    Uint8 r, g, b, a;
                    SDL_GetRenderDrawColor(rc_win_renderer[w], &r, &g, &b, &a);
                    SDL_SetRenderDrawColor(rc_win_renderer[w], rc_image_colorKey_r[i], rc_image_colorKey_g[i], rc_image_colorKey_b[i], 255);
                    SDL_RenderFillRect(rc_win_renderer[w], NULL);
                    SDL_SetRenderDrawColor(rc_win_renderer[w], r, g, b, a);
                    SDL_RenderCopy(rc_win_renderer[w], rc_himage[i][w], NULL, &t_rect);
                    SDL_RenderReadPixels(rc_win_renderer[w],&t_rect,tmp_surf->format->format,tmp_surf->pixels,tmp_surf->pitch);
                    SDL_SetColorKey(tmp_surf, SDL_TRUE, rc_image_colorKey[i]);
                    rc_himage[i][w] = SDL_CreateTextureFromSurface(rc_win_renderer[w], tmp_surf);
                    SDL_FreeSurface(tmp_surf);
                    break;
                }
            }
        }
    }

#endif // RC_MOBILE

    //SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    //SDL_RenderSetLogicalSize(rc_win_renderer[win_num], w, h);

    //cout << "boobs" << endl;

    rc_backBuffer[win_num] = SDL_CreateTexture(rc_win_renderer[win_num], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, w, h);
    //cout << "dbg 1" << endl;

#ifdef RC_MOBILE

    if(SDL_GetDesktopDisplayMode(0, &rc_displayMode[win_num])<0)
    {
        cout << "Something happend: " << SDL_GetError() << endl;
    }

#else

    if(SDL_GetWindowDisplayMode(rc_win[win_num], &rc_displayMode[win_num])<0)
    {
        cout << "Something happend: " << SDL_GetError() << endl;
    }

#endif // RC_ANDROID
    //cout << "dbg 2" << endl;
    rc_bb_rect[win_num].x = 0;
    rc_bb_rect[win_num].y = 0;
    //cout << "dbg 3" << endl;
    rc_bb_rect[win_num].w = rc_displayMode[win_num].w;
    //cout << "dbg 4" << endl;
    rc_bb_rect[win_num].h = rc_displayMode[win_num].h;

    //cout << "cunt" << endl;

#ifdef RC_MOBILE
    rc_mouse_scale_x = (double)((double)w / (double)rc_displayMode[win_num].w);
    rc_mouse_scale_y = (double)((double)h / (double)rc_displayMode[win_num].h);
#else
    if((flags&SDL_WINDOW_FULLSCREEN_DESKTOP)!=0)
    {
        //cout << "fullscreen" << endl;
        //cout << "W = " << w << endl;
        //cout << "D.W = " << rc_displayMode[win_num].w << endl;
        rc_fullscreen_mouse_scale_x[win_num] = (double)((double)w / (double)rc_displayMode[win_num].w);
        //cout << "fs = " << rc_fullscreen_mouse_scale_x[win_num] << endl;
        rc_fullscreen_mouse_scale_y[win_num] = (double)((double)h / (double)rc_displayMode[win_num].h);
        //cout << "display mode = " << rc_fullscreen_mouse_scale_x[win_num] << ", " << rc_fullscreen_mouse_scale_y[win_num] << endl;
    }
    else
    {
        rc_fullscreen_mouse_scale_x[win_num] = 1;
        rc_fullscreen_mouse_scale_y[win_num] = 1;
    }
#endif // RC_ANDROID

    //#ifndef RC_ANDROID
    rc_hconsole[win_num] = SDL_CreateTexture(rc_win_renderer[win_num],rc_pformat->format,SDL_TEXTUREACCESS_TARGET,w,h);
    SDL_SetTextureBlendMode(rc_hconsole[win_num], SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(rc_win_renderer[win_num], rc_hconsole[win_num]);
    SDL_SetRenderDrawColor(rc_win_renderer[win_num], 0, 0, 0, 0);
    SDL_RenderClear(rc_win_renderer[win_num]);
    SDL_SetRenderTarget(rc_win_renderer[win_num], NULL);
    //#endif // RC_ANDROID

    //cout << "wtf" << endl;

    rc_console_width[win_num] = w/8;
    rc_console_height[win_num] = h/8;
    rc_sConsole_x[win_num] = 0;
    rc_sConsole_y[win_num] = 0;

    //cout << "cdi" << endl;

#ifdef RC_MOBILE
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_backBuffer[rc_active_window]);
    SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], 0, 0, 0, 255);
    SDL_RenderClear(rc_win_renderer[rc_active_window]);
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
    SDL_RenderClear(rc_win_renderer[rc_active_window]);
    rc_win_width[win_num] = w;
    rc_win_height[win_num] = h;
#else
    SDL_SetRenderDrawColor(rc_win_renderer[win_num], 0, 0, 0, 255);
    SDL_RenderClear(rc_win_renderer[win_num]);
#endif // RC_ANDROID

    SDL_RenderPresent(rc_win_renderer[win_num]);

    //cout << "open complete" << endl;

    //rc_debug_msg("Window Creation Successful");

    return true;
}

inline void rc_media_closeWindow_hw(int win_num)
{
    if(win_num < 0 && win_num >= MAX_WINDOWS)
    {
        cout << "Window Index is out of Range" << endl;
        return;
    }
    SDL_DestroyTexture(rc_hconsole[win_num]);
    SDL_DestroyTexture(rc_backBuffer[win_num]);
    SDL_DestroyRenderer(rc_win_renderer[win_num]);
    if(rc_win[win_num]!=NULL)
        SDL_DestroyWindow(rc_win[win_num]);
    rc_win_renderer[win_num] = NULL;
    rc_win[win_num] = NULL;
}

inline int rc_media_setRenderScaleQuality(int n)
{
    stringstream s;
    s << n;

    if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, s.str().c_str()))
       return 1;
    return 0;
}

inline int rc_media_getRenderScaleQuality()
{
    string hint = SDL_GetHint(SDL_HINT_RENDER_SCALE_QUALITY) == NULL ? "" : SDL_GetHint(SDL_HINT_RENDER_SCALE_QUALITY);
    int hint_val = 0;
    if(hint.compare("")!=0)
    {
        #ifdef RC_WINDOWS
        hint_val = atoi(hint.c_str());
        #else
            #ifdef RC_ANDROID
            hint_val = atoi(hint.c_str());
            #else
            hint_val = stoi(hint);
            #endif
        #endif
    }
    return hint_val;
}

inline void rc_media_getDesktopDisplayMode(int index, double * w, double * h, double * freq)
{
    SDL_DisplayMode dm;
    SDL_GetDesktopDisplayMode(index, &dm);
    *w = (double)dm.w;
    *h = (double)dm.h;
    *freq = (double)dm.refresh_rate;
}

inline void rc_media_setActiveWindow(int win_num)
{
    if(win_num < 0 || win_num >= MAX_WINDOWS)
    {
        cout << "Window Index Out of Range" << endl;
        return;
    }
    rc_active_window = win_num;
}

void rc_media_raiseWindow(int win_num)
{
    if(win_num < 0 || win_num >= MAX_WINDOWS)
    {
        cout << "Window Index Out of Range" << endl;
        return;
    }
    if(rc_win[win_num]==NULL)
    {
        //cout << "Window does not Exist" << endl;
        return;
    }
    rc_active_window = win_num;
    SDL_RaiseWindow(rc_win[win_num]);
}

void rc_media_showWindow(int win_num)
{
    if(win_num < 0 || win_num >= MAX_WINDOWS)
    {
        cout << "Window Index Out of Range" << endl;
        return;
    }
    if(rc_win[win_num]==NULL)
    {
        //cout << "Window does not Exist" << endl;
        return;
    }
    SDL_ShowWindow(rc_win[win_num]);
}

void rc_media_hideWindow(int win_num)
{
    if(win_num < 0 || win_num >= MAX_WINDOWS)
    {
        cout << "Window Index Out of Range" << endl;
        return;
    }
    if(rc_win[win_num]==NULL)
    {
        //cout << "Window does not Exist" << endl;
        return;
    }
    SDL_HideWindow(rc_win[win_num]);
}

bool rc_winCheck(int win_num)
{
    if(win_num < 0 || win_num >= MAX_WINDOWS)
    {
        cout << "Window Index Out of Range" << endl;
        return false;
    }
    if(rc_win[win_num]==NULL)
    {
        //cout << "Window does not Exist" << endl;
        return false;
    }
    return true;
}

void rc_media_setWindowTitle(int win_num, string title)
{
    if(rc_winCheck(win_num))
    {
        SDL_SetWindowTitle(rc_win[win_num], title.c_str());
    }
    else
    {
        cout << "SetWindowTitle Error: Window #" << win_num << " is not an active window" << endl;
    }
}

string rc_media_getWindowTitle(int win_num)
{
    if(rc_winCheck(win_num))
    {
        return SDL_GetWindowTitle(rc_win[win_num]);
    }
    else
    {
        cout << "WindowTitle Error: Window #" << win_num << " is not an active window" << endl;
        return "";
    }
}

void rc_media_setWindowPosition(int win_num, int x, int y)
{
    if(rc_winCheck(win_num))
        SDL_SetWindowPosition(rc_win[win_num], x, y);
    else
        cout << "SetWindowPosition Error: Window #" << win_num << " is not an active window" << endl;
}

void rc_media_getWindowPosition(int win_num, double * x, double * y)
{
    int x_data=0, y_data=0;
    if(rc_winCheck(win_num))
        SDL_GetWindowPosition(rc_win[win_num],&x_data,&y_data);
    else
        cout << "GetWindowPosition Error: Window #" << win_num << " is not an active window" << endl;
    *x = x_data;
    *y = y_data;
}


void rc_onResize(int win_num)
{
    SDL_Texture * current_tgt = SDL_GetRenderTarget(rc_win_renderer[win_num]);
    int w = 0;
    int h = 0;
    SDL_DestroyTexture(rc_backBuffer[win_num]);
    rc_backBuffer[win_num] = NULL;
    Uint32 win_flags = SDL_GetWindowFlags(rc_win[win_num]);
    if( (win_flags & SDL_WINDOW_RESIZABLE) && !(win_flags & SDL_WINDOW_FULLSCREEN_DESKTOP) )
        SDL_GetWindowSize(rc_win[win_num], &w, &h);
    else
    {
        w = rc_win_width[win_num];
        h = rc_win_height[win_num];
    }
    rc_win_width[win_num] = w;
    rc_win_height[win_num] = h;
    //cout << "debug1: " << w << ", " << h << endl;
    rc_backBuffer[win_num] = SDL_CreateTexture(rc_win_renderer[win_num], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, w, h);

#ifdef RC_MOBILE

    if(SDL_GetDesktopDisplayMode(0, &rc_displayMode[win_num])<0)
    {
        cout << "Something happend: " << SDL_GetError() << endl;
    }

#else

    if(SDL_GetWindowDisplayMode(rc_win[win_num], &rc_displayMode[win_num])<0)
    {
        cout << "Something happend: " << SDL_GetError() << endl;
    }

#endif // RC_ANDROID

    rc_bb_rect[win_num].x = 0;
    rc_bb_rect[win_num].y = 0;
    rc_bb_rect[win_num].w = rc_displayMode[win_num].w;
    rc_bb_rect[win_num].h = rc_displayMode[win_num].h;

    //cout << "bb_rect = " << rc_bb_rect[win_num].w << ", " << rc_bb_rect[win_num].h << endl;

    Uint32 flags = SDL_GetWindowFlags(rc_win[win_num]);

#ifdef RC_MOBILE
    rc_mouse_scale_x = (double)((double)w / (double)rc_displayMode[win_num].w);
    rc_mouse_scale_y = (double)((double)h / (double)rc_displayMode[win_num].h);
#else
    if((flags & SDL_WINDOW_FULLSCREEN_DESKTOP)!=0)
    {
        rc_fullscreen_mouse_scale_x[win_num] = (double)((double)rc_win_width[win_num] / (double)rc_displayMode[win_num].w);
        rc_fullscreen_mouse_scale_y[win_num] = (double)((double)rc_win_height[win_num] / (double)rc_displayMode[win_num].h);
        //cout << "resize_fullscreen: " << w << " / " << rc_displayMode[win_num].w << endl;
    }
    else
    {
        //cout << "resize window mode" << endl;
        rc_fullscreen_mouse_scale_x[win_num] = 1;
        rc_fullscreen_mouse_scale_y[win_num] = 1;
    }
#endif // RC_ANDROID

    SDL_DestroyTexture(rc_hconsole[win_num]);
    rc_hconsole[win_num] = SDL_CreateTexture(rc_win_renderer[win_num],rc_pformat->format,SDL_TEXTUREACCESS_TARGET,w,h);
    SDL_SetTextureBlendMode(rc_hconsole[win_num], SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(rc_win_renderer[win_num], rc_hconsole[win_num]);
    SDL_SetRenderDrawColor(rc_win_renderer[win_num], 0, 0, 0, 0);
    SDL_RenderClear(rc_win_renderer[win_num]);
    SDL_SetRenderTarget(rc_win_renderer[win_num], current_tgt);

    rc_console_width[win_num] = w/8;
    rc_console_height[win_num] = h/8;
    rc_sConsole_x[win_num] = 0;
    rc_sConsole_y[win_num] = 0;

}


void rc_media_setWindowSize(int win_num, int w, int h)
{
    if(rc_winCheck(win_num))
    {
        SDL_SetWindowSize(rc_win[win_num], w, h);

        rc_win_width[win_num] = w;
        rc_win_height[win_num] = h;

        rc_onResize(win_num);
    }
    else
        cout << "SetWindowSize Error: Window #" << win_num << " is not an active window" << endl;
}

void rc_media_getWindowSize(int win_num, double * w, double * h)
{
    int w_data = -1, h_data = -1;
    if(rc_winCheck(win_num))
        SDL_GetWindowSize(rc_win[win_num], &w_data, &h_data);
    else
        cout << "GetWindowSize Error: Window#" << win_num << " is not an active window" << endl;
    *w = w_data;
    *h = h_data;
}

void rc_media_setWindowMinSize(int win_num, int w, int h)
{
    if(rc_winCheck(win_num))
        SDL_SetWindowMinimumSize(rc_win[win_num], w, h);
    else
        cout << "SetWindowMinSize Error: Window#" << win_num << " is not an active window" << endl;
}

void rc_media_getWindowMinSize(int win_num, double * w, double * h)
{
    int w_data=0, h_data=0;
    if(rc_winCheck(win_num))
        SDL_GetWindowMinimumSize(rc_win[win_num], &w_data, &h_data);
    else
        cout << "GetWindowMinSize Error: Window #" << win_num << " is not an active window" << endl;
    *w = w_data;
    *h = h_data;
}

void rc_media_setWindowMaxSize(int win_num, int w, int h)
{
    if(rc_winCheck(win_num))
        SDL_SetWindowMaximumSize(rc_win[win_num], w, h);
    else
        cout << "SetWindowMaxSize Error: Window #" << win_num << " is not an active window" << endl;
}

void rc_media_getWindowMaxSize(int win_num, double * w, double * h)
{
    int w_data=0, h_data=0;
    if(rc_winCheck(win_num))
        SDL_GetWindowMaximumSize(rc_win[win_num], &w_data, &h_data);
    else
        cout << "GetWindowMaxSize Error: Window #" << win_num << " is not an active window" << endl;
    *w = w_data;
    *h = h_data;
}

bool rc_media_windowIsFullscreen(int win_num)
{
    if(rc_winCheck(win_num))
    {
        Uint32 wflags = SDL_GetWindowFlags(rc_win[win_num]);
        Uint32 wflags_cmp1 = wflags & SDL_WINDOW_FULLSCREEN;
        Uint32 wflags_cmp2 = wflags & SDL_WINDOW_FULLSCREEN_DESKTOP;
        if(wflags_cmp1 || wflags_cmp2)
        {
            //cout << "wflags = " << (int)wflags << endl;
            //cout << "SDL_WIN_FSCREEN = " << (int)SDL_WINDOW_FULLSCREEN << endl;
            //cout << "SDL_WIN_FSCREEN_D = " << (int)SDL_WINDOW_FULLSCREEN_DESKTOP << endl;
            return true;
        }
        else
        {
            //cout << "wflags = " << (int)wflags << endl;
            //cout << "SDL_WIN_FSCREEN = " << (int)SDL_WINDOW_FULLSCREEN << endl;
            //cout << "SDL_WIN_FSCREEN_D = " << (int)SDL_WINDOW_FULLSCREEN_DESKTOP << endl;
            return false;
        }
    }
    else
    {
        cout << "WindowIsFullscreen Error: Window #" << win_num << " is not an active window" << endl;
        return false;
    }
}

bool rc_media_windowIsVisible(int win_num)
{
    if(rc_winCheck(win_num))
    {
        Uint32 wflags = SDL_GetWindowFlags(rc_win[win_num]);
        if(wflags & SDL_WINDOW_SHOWN)
            return true;
        else
            return false;
    }
    else
    {
        cout << "WindowIsVisible Error: Window #" << win_num << " is not an active window" << endl;
        return false;
    }
}

bool rc_media_windowHasMouseFocus(int win_num)
{
    if(rc_winCheck(win_num))
    {
        Uint32 wflags = SDL_GetWindowFlags(rc_win[win_num]);
        if(wflags & SDL_WINDOW_MOUSE_FOCUS)
            return true;
        else
            return false;
    }
    else
    {
        cout << "WindowHasMouseFocus Error: Window #" << win_num << " is not an active window" << endl;
        return false;
    }
}

bool rc_media_windowHasInputFocus(int win_num)
{
    if(rc_winCheck(win_num))
    {
        Uint32 wflags = SDL_GetWindowFlags(rc_win[win_num]);
        if(wflags & SDL_WINDOW_INPUT_FOCUS)
            return true;
        else
            return false;
    }
    else
    {
        cout << "WindowHasInputFocus Error: Window #" << win_num << " is not an active window" << endl;
        return false;
    }
}

bool rc_media_windowIsBordered(int win_num)
{
    if(rc_winCheck(win_num))
    {
        Uint32 wflags = SDL_GetWindowFlags(rc_win[win_num]);
        if(wflags & SDL_WINDOW_BORDERLESS)
            return false;
        else
            return true;
    }
    else
    {
        cout << "WindowIsBordered Error: Window #" << win_num << " is not an active window" << endl;
        return false;
    }
}

bool rc_media_windowIsResizable(int win_num)
{
    if(rc_winCheck(win_num))
    {
        Uint32 wflags = SDL_GetWindowFlags(rc_win[win_num]);
        if(wflags & SDL_WINDOW_RESIZABLE)
            return true;
        else
            return false;
    }
    else
    {
        cout << "WindowIsResizable Error: Window #" << win_num << " is not an active window" << endl;
        return false;
    }
}

bool rc_media_windowIsMinimized(int win_num)
{
    if(rc_winCheck(win_num))
    {
        Uint32 wflags = SDL_GetWindowFlags(rc_win[win_num]);
        if(wflags & SDL_WINDOW_MINIMIZED)
            return true;
        else
            return false;
    }
    else
    {
        cout << "WindowIsMinimized Error: Window #" << win_num << " is not an active window" << endl;
        return false;
    }
}

bool rc_media_windowIsMaximized(int win_num)
{
    if(rc_winCheck(win_num))
    {
        Uint32 wflags = SDL_GetWindowFlags(rc_win[win_num]);
        if(wflags & SDL_WINDOW_MAXIMIZED)
            return true;
        else
            return false;
    }
    else
    {
        cout << "WindowIsMaximized Error: Window #" << win_num << " is not an active window" << endl;
        return false;
    }
}

void rc_media_setWindowFullscreen(int win_num, int flag)
{
    if(rc_winCheck(win_num))
    {
        switch(flag)
        {
            case 0:
                flag = 0;
                break;
            default:
                flag = SDL_WINDOW_FULLSCREEN_DESKTOP;
                break;
        }

        Uint32 wflags_preOp = SDL_GetWindowFlags(rc_win[win_num]);

        if(SDL_SetWindowFullscreen(rc_win[win_num], flag) < 0)
        {
            cout << "SetWindowFullscreen Error: " << SDL_GetError() << endl;
            return;
        }

        rc_win_renderer[win_num] = SDL_GetRenderer(rc_win[win_num]);
        //cout << "debug = " << (rc_win_renderer[win_num] == NULL) << endl;

        Uint32 wflags = SDL_GetWindowFlags(rc_win[win_num]);
        Uint32 wflags_cmp1 = wflags & SDL_WINDOW_FULLSCREEN;
        Uint32 wflags_cmp2 = wflags & SDL_WINDOW_FULLSCREEN_DESKTOP;
        if(!(wflags_cmp1 || wflags_cmp2))
        {
            #ifndef RC_MOBILE
            rc_fullscreen_mouse_scale_x[win_num] = 1;
            rc_fullscreen_mouse_scale_y[win_num] = 1;
            #endif // RC_MOBILE
        }
        else if(SDL_GetWindowDisplayMode(rc_win[win_num], &rc_displayMode[win_num])<0)
        {
            cout << "Something happend: " << SDL_GetError() << endl;
            #ifndef RC_MOBILE
            rc_fullscreen_mouse_scale_x[win_num] = 1;
            rc_fullscreen_mouse_scale_y[win_num] = 1;
            #endif // RC_MOBILE
        }
        else
        {
            #ifndef RC_MOBILE
            rc_fullscreen_mouse_scale_x[win_num] = (double)((double)rc_win_width[win_num] / (double)rc_displayMode[win_num].w);
            rc_fullscreen_mouse_scale_y[win_num] = (double)((double)rc_win_height[win_num] / (double)rc_displayMode[win_num].h);
            #endif // RC_MOBILE
        }

        SDL_PumpEvents();
        SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
        // SDL_GetWindowDisplayMode(rc_win[win_num],&rc_displayMode[win_num]);
        //rc_bb_rect[win_num].w = rc_displayMode[win_num].w;
        //rc_bb_rect[win_num].h = rc_displayMode[win_num].h;
        //rc_win_surface[win_num] = SDL_GetWindowSurface(rc_win[win_num]);
    }
    else
        cout << "SetWindowFullscreen Error: Window #" << win_num << " is not an active window" << endl;
}

void rc_media_maximizeWindow(int win_num)
{
    if(rc_winCheck(win_num))
    {
        SDL_MaximizeWindow(rc_win[win_num]);
        if( (SDL_GetWindowFlags(rc_win[win_num]) & SDL_WINDOW_RESIZABLE) )
            return;
        SDL_GetWindowDisplayMode(rc_win[win_num],&rc_displayMode[win_num]);
        rc_bb_rect[win_num].w = rc_displayMode[win_num].w;
        rc_bb_rect[win_num].h = rc_displayMode[win_num].h;
        rc_win_surface[win_num] = SDL_GetWindowSurface(rc_win[win_num]);
        #ifndef RC_MOBILE
        rc_fullscreen_mouse_scale_x[win_num] = (double)((double)rc_win_width[win_num] / (double)rc_displayMode[win_num].w);
        rc_fullscreen_mouse_scale_y[win_num] = (double)((double)rc_win_height[win_num] / (double)rc_displayMode[win_num].h);
        #endif // RC_MOBILE
    }
    else
        cout << "MaximizeWindow Error: Window #" << win_num << " is not an active window" << endl;
}

void rc_media_minimizeWindow(int win_num)
{
    if(rc_winCheck(win_num))
    {
        SDL_MinimizeWindow(rc_win[win_num]);
        SDL_GetWindowDisplayMode(rc_win[win_num],&rc_displayMode[win_num]);
        rc_bb_rect[win_num].w = rc_displayMode[win_num].w;
        rc_bb_rect[win_num].h = rc_displayMode[win_num].h;
        rc_win_surface[win_num] = SDL_GetWindowSurface(rc_win[win_num]);
        #ifndef RC_MOBILE
        rc_fullscreen_mouse_scale_x[win_num] = (double)((double)rc_win_width[win_num] / (double)rc_displayMode[win_num].w);
        rc_fullscreen_mouse_scale_y[win_num] = (double)((double)rc_win_height[win_num] / (double)rc_displayMode[win_num].h);
        #endif // RC_MOBILE
    }
    else
        cout << "MinimizeWindow Error: Window #" << win_num << " is not an active window" << endl;
}

void rc_media_setWindowBordered(int win_num, bool b)
{
    SDL_bool bswitch = SDL_FALSE;
    if(b)
        bswitch = SDL_TRUE;
    if(rc_winCheck(win_num))
        SDL_SetWindowBordered(rc_win[win_num], bswitch);
    else
        cout << "SetWindowBorder Error: Window #" << win_num << " is not an active window" << endl;
}

void rc_media_setWindowResizable(int win_num, bool b)
{
    SDL_bool bswitch = SDL_FALSE;
    if(b)
        bswitch = SDL_TRUE;
    if(rc_winCheck(win_num))
        SDL_SetWindowResizable(rc_win[win_num], bswitch);
    else
        cout << "SetWindowResizable Error: Window #" << win_num << " is not an active window" << endl;
}

int rc_media_numWindows()
{
    int num = 0;
    for(int i = 0; i < MAX_WINDOWS; i++)
        if(rc_win[i])
            num++;
    return num;
}

bool rc_media_windowExists(int win_num)
{
    if(rc_winCheck(win_num))
    {
        if(rc_win[win_num])
            return true;
        return false;
    }
    return false;
}

void rc_media_restoreWindow(int win_num)
{
    if(rc_winCheck(win_num))
    {
        SDL_RestoreWindow(rc_win[win_num]);
        SDL_GetWindowDisplayMode(rc_win[win_num], &rc_displayMode[win_num]);
        rc_bb_rect[win_num].w = rc_displayMode[win_num].w;
        rc_bb_rect[win_num].h = rc_displayMode[win_num].h;
        rc_win_surface[win_num] = SDL_GetWindowSurface(rc_win[win_num]);
        #ifndef RC_MOBILE
        rc_fullscreen_mouse_scale_x[win_num] = (double)((double)rc_win_width[win_num] / (double)rc_displayMode[win_num].w);
        rc_fullscreen_mouse_scale_y[win_num] = (double)((double)rc_win_height[win_num] / (double)rc_displayMode[win_num].h);
        #endif // RC_MOBILE
    }
    else
        cout << "RestoreWindow Error: Window #" << win_num << " is not an active window" << endl;
}

void rc_media_setWindowIcon(int win_num, int slot)
{
    SDL_Rect img_rect;
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = rc_image_width[slot];
    img_rect.h = rc_image_height[slot];
    if(rc_himage[slot][win_num] != NULL)
    {
        //SDL_RendererFlip rf = (SDL_RendererFlip)(SDL_FLIP_VERTICAL);

        SDL_Surface * tmp_surf = SDL_CreateRGBSurface(0, rc_image_width[slot], rc_image_height[slot], 32, 0, 0, 0, 0);
        SDL_Texture * tmp_tex = SDL_CreateTexture(rc_win_renderer[rc_active_window], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, rc_image_width[slot], rc_image_height[slot]);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window],NULL);
        SDL_RenderCopy(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,&img_rect);
        //SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,NULL,0,NULL,rf);

        SDL_RenderReadPixels(rc_win_renderer[rc_active_window], &img_rect, rc_pformat->format,tmp_surf->pixels,tmp_surf->pitch);

        SDL_SetColorKey(tmp_surf,SDL_TRUE,rc_image_colorKey[slot]);

        SDL_SetWindowIcon(rc_win[rc_active_window], tmp_surf);


        if(rc_active_screen >= 0)
            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);

        SDL_DestroyTexture(tmp_tex);
        SDL_FreeSurface(tmp_surf);
    }
}

string rc_media_getClipboardText()
{
    return (string) SDL_GetClipboardText();
}

void rc_media_setClipboardText(string txt)
{
    SDL_SetClipboardText(txt.c_str());
}

int rc_media_hasClipboardText()
{
    return (int)SDL_HasClipboardText();
}

bool rc_screenCheck(int s_num = -1)
{
    if(s_num == -1)
        s_num = rc_active_screen;
    if(s_num > MAX_SCREENS || s_num < 0)
        return false;
    if(rc_sscreen[rc_active_window][s_num] == NULL && rc_hscreen[rc_active_window][s_num] == NULL)
        return false;
    return true;
}

void rc_media_openScreen_hw(int s_num, int w, int h, int vpx, int vpy, int vpw, int vph, int flag)
{
    //cout << "start CanvasOpen in " << rc_active_window << ", " << s_num << endl;
    if(s_num < 0 || s_num > MAX_SCREENS)
    {
        cout << "Canvas #" << s_num << " is not available" << endl;
        return;
    }
    if(rc_hscreen[rc_active_window][s_num]!=NULL)
    {
        cout << "Canvas #" << s_num << " is already open" << endl;
        return;
    }
    //cout << "got to this point" << endl;
    rc_hscreen[rc_active_window][s_num] = SDL_CreateTexture(rc_win_renderer[rc_active_window], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, w, h);
    //cout << "hscreen texture created" << endl;
    rc_screen_transparent[rc_active_window][s_num] = 0;

    //cout << "Canvas is created" << endl;

    switch(flag)
    {
        case 0:
            //solid screen
            break;
        case 1:
            rc_screen_transparent[rc_active_window][s_num] = 1;
            SDL_SetTextureBlendMode(rc_hscreen[rc_active_window][s_num], SDL_BLENDMODE_BLEND);
            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][s_num]);
            SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], 0, 0, 0, 0);
            SDL_RenderClear(rc_win_renderer[rc_active_window]);
            //cout << "screen opened\n";
            break;
    }

    //cout << "Flags are set" << endl;

    rc_screen_rect[rc_active_window][s_num].x = vpx;
    rc_screen_rect[rc_active_window][s_num].y = vpy;
    rc_screen_rect[rc_active_window][s_num].w = vpw;
    rc_screen_rect[rc_active_window][s_num].h = vph;
    rc_screen_width[rc_active_window][s_num] = w;
    rc_screen_height[rc_active_window][s_num] = h;
    rc_screenview[rc_active_window][s_num].x = 0;
    rc_screenview[rc_active_window][s_num].y = 0;
    rc_screenview[rc_active_window][s_num].w = vpw;
    rc_screenview[rc_active_window][s_num].h = vph;
    rc_screen_visible[rc_active_window][s_num] = true;
    if(rc_active_screen == -1)
        rc_active_screen = s_num;

    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);

    //cout << "Canvas is open" << endl;
}

void rc_media_closeScreen_hw(int s_num)
{
    if(rc_screenCheck(s_num))
    {
        SDL_DestroyTexture(rc_hscreen[rc_active_window][s_num]);
        rc_hscreen[rc_active_window][s_num] = NULL;
        rc_screen_visible[rc_active_window][s_num] = false;
    }
}

void rc_media_screen_hw(int s_num)
{
    if(rc_screenCheck(s_num))
    {
        rc_active_screen = s_num;
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][s_num]);
        //cout << "active screen = hscreen[" << rc_active_window << "][" << s_num << "]\n";
    }
}

void rc_media_setScreenVisible(int s_num, int flag)
{
    if(rc_screenCheck(s_num) && flag == 0)
    {
        rc_screen_visible[rc_active_window][s_num] = false;
        return;
    }
    rc_screen_visible[rc_active_window][s_num] = true;
}

bool rc_media_screenIsVisible(int s_num)
{
    return rc_screen_visible[rc_active_window][s_num];
}

void rc_media_setScreenViewport(int s_num, int x, int y, int w, int h)
{
    if(rc_screenCheck(s_num))
    {
        rc_screen_rect[rc_active_window][s_num].x = x;
        rc_screen_rect[rc_active_window][s_num].y = y;
        rc_screen_rect[rc_active_window][s_num].w = w;
        rc_screen_rect[rc_active_window][s_num].h = h;
    }
}

void rc_media_getScreenViewport(int s_num, double * x, double * y, double * w, double * h)
{
    if(rc_screenCheck(s_num))
    {
        *x = rc_screen_rect[rc_active_window][s_num].x;
        *y = rc_screen_rect[rc_active_window][s_num].y;
        *w = rc_screen_rect[rc_active_window][s_num].w;
        *h = rc_screen_rect[rc_active_window][s_num].h;
    }
    else
        cout << "GetScreenViewport Error: Screen #" << s_num << " is not accessible" << endl;
}

void rc_media_screenOffset(int s_num, int x, int y)
{
    if(rc_screenCheck(s_num))
    {
        //removed error checks because you only live once
        rc_screenview[rc_active_window][s_num].x = x;
        rc_screenview[rc_active_window][s_num].y = y;
        rc_screenview[rc_active_window][s_num].w = rc_screen_rect[rc_active_window][s_num].w;
        rc_screenview[rc_active_window][s_num].h = rc_screen_rect[rc_active_window][s_num].h;
        //SDL_SetClipRect(rc_sscreen[rc_active_window][rc_active_screen], &rc_screenview[rc_active_window][rc_active_screen]);
    }
}

void rc_media_getScreenOffset(int s_num, double * x, double * y)
{
    if(rc_screenCheck(s_num))
    {
        *x = rc_screenview[rc_active_window][s_num].x;
        *y = rc_screenview[rc_active_window][s_num].y;
    }
}

void rc_media_getScreenSize(int s_num, double * w, double * h)
{
    if(rc_screenCheck(s_num))
    {
        *w = rc_screen_width[rc_active_window][s_num];
        *h = rc_screen_height[rc_active_window][s_num];
    }
}

void rc_media_clearScreen_hw()
{
    if(rc_screenCheck())
    {
        //cout << "Clear screen\n";
        //SDL_LockSurface(rc_sscreen[rc_active_window][rc_active_screen]);
        //SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor>>16, rc_clearColor>>8, rc_clearColor, rc_clearColor>>24);
        SDL_RenderClear(rc_win_renderer[rc_active_window]);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
        //SDL_RenderFillRect(rc_win_renderer[rc_active_window], &rc_screen_rect[rc_active_window][rc_active_screen]);
        //SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
    }
}

void rc_media_setScreenAlpha_hw(int s_num, Uint8 alpha)
{
    if(rc_screenCheck(s_num))
    {
        SDL_SetTextureAlphaMod(rc_hscreen[rc_active_window][s_num], alpha);
    }
}

Uint32 rc_media_ScreenAlpha_hw(int s_num)
{
    Uint8 alpha = 0;
    if(rc_screenCheck(s_num))
    {
        SDL_GetTextureAlphaMod(rc_hscreen[rc_active_window][s_num], &alpha);
    }
    return (Uint32)alpha;
}

int rc_media_setScreenBlendMode_hw(int s_num, int blend_mode)
{
    if(!rc_screenCheck(s_num))
    {
        return -1;
    }
    int rslt = -1;
    SDL_BlendMode b = SDL_BLENDMODE_NONE;
    switch(blend_mode)
    {
    case 0: //SDL_BLENDMODE_NONE
        b = SDL_BLENDMODE_NONE;
        break;
    case 1: //SDL_BLENDMODE_BLEND
        b = SDL_BLENDMODE_BLEND;
        break;
    case 2: //SDL_BLENDMODE_ADD
        b = SDL_BLENDMODE_ADD;
        break;
    case 4: //SDL_BLENDMODE_MOD
        b = SDL_BLENDMODE_MOD;
        break;
    default:
        return rslt;
    }
    rslt = SDL_SetTextureBlendMode(rc_hscreen[rc_active_window][s_num], b);

    return rslt;
}

int rc_media_screenBlendMode_hw(int s_num)
{
    if(!rc_screenCheck(s_num))
    {
        return -1;
    }
    SDL_BlendMode blend_mode = SDL_BLENDMODE_NONE;
    int rslt = SDL_GetTextureBlendMode(rc_hscreen[rc_active_window][s_num], &blend_mode);
    if(rslt < 0)
    {
        cout << "CanvasBlendMode Error: " << SDL_GetError() << endl;
        return rslt;
    }
    return blend_mode;
}

int rc_media_setScreenColorMod_hw(int s_num, Uint32 c)
{
    if(!rc_screenCheck(s_num))
    {
        return -1;
    }
    int rslt = -1;

    Uint8 r = c>>16;
    Uint8 g = c>>8;
    Uint8 b = c;

    //cout << "C = " << c << endl;
    //cout << "RGB = " << (Uint32)r << ", " << (Uint32)g << ", " << (Uint32)b << endl;

    rslt = SDL_SetTextureColorMod(rc_hscreen[rc_active_window][s_num], r, g, b);
    return rslt;
}

int rc_media_screenColorMod_hw(int s_num)
{
    if(!rc_screenCheck(s_num))
    {
        return -1;
    }

    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    int rslt = SDL_GetTextureColorMod(rc_hscreen[rc_active_window][s_num], &r, &g, &b);

    if(rslt < 0)
    {
        cout << "CanvasColorMode Error: " << SDL_GetError() << endl;
        return rslt;
    }

    Uint32 c_mod = (Uint32)SDL_MapRGBA(rc_pformat,r,g,b,255);

    //cout << "-RGB = " << (int)r << ", " << (int)g << ", " << (int)b << endl;

    return c_mod;
}
//----------------


void rc_media_copyScreen_hw(int src_screen, int sx, int sy, int sw, int sh, int dst_screen, int dx, int dy)
{
    if(rc_screenCheck(src_screen) && rc_screenCheck(dst_screen))
    {
        SDL_Rect src_rect, dst_rect;
        src_rect.x = sx;
        src_rect.y = sy;
        src_rect.w = sw;
        src_rect.h = sh;
        dst_rect.x = dx;
        dst_rect.y = dy;
        dst_rect.w = sw;
        dst_rect.h = sh;
        //SDL_BlitSurface(rc_sscreen[rc_active_window][src_screen], &src_rect, rc_sscreen[rc_active_window][dst_screen], &dst_rect);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][dst_screen]);
        SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][src_screen], &src_rect, &dst_rect);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
    }
}

void rc_media_getScreenClip_hw(int slot, int sx, int sy, int sw, int sh)
{
    if(rc_screenCheck(rc_active_screen))
    {
        SDL_RendererFlip rf = (SDL_RendererFlip)SDL_FLIP_NONE;
        int w = 0;
        int h = 0;
        SDL_QueryTexture(rc_hscreen[rc_active_window][rc_active_screen], NULL, NULL, &w, &h);
        SDL_Texture * tmp_tex = SDL_CreateTexture(rc_win_renderer[rc_active_window], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, w, h);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], tmp_tex);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor>>16, rc_clearColor>>8, rc_clearColor, rc_clearColor>>24);
        SDL_RenderClear(rc_win_renderer[rc_active_window]);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
        SDL_Point center;
        center.x = w/2;
        center.y = h/2;
        SDL_RenderCopyEx(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen], NULL, NULL, 0, &center,rf);
        SDL_Surface * img_surf = SDL_CreateRGBSurface(0, sw, sh, 32, 0, 0, 0, 0);
        SDL_Rect src_rect;
        src_rect.x = sx;
        src_rect.y = sy;
        src_rect.w = sw;
        src_rect.h = sh;
        //SDL_BlitSurface(rc_sscreen[rc_active_window][src_screen], &src_rect, rc_sscreen[rc_active_window][dst_screen], &dst_rect);
        SDL_RenderReadPixels(rc_win_renderer[rc_active_window], &src_rect, rc_pformat->format, img_surf->pixels, img_surf->pitch);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
        SDL_DestroyTexture(tmp_tex);

        for(int i = 0; i < MAX_WINDOWS; i++)
        {
            if(rc_win_renderer[i]!=NULL)
            {
                if(rc_himage[slot][i]!=NULL)
                {
                    SDL_DestroyTexture(rc_himage[slot][i]);
                    rc_himage[slot][i] = NULL;
                }
                rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], img_surf);
                rc_himage_rect[slot].x = 0;
                rc_himage_rect[slot].y = 0;
                rc_himage_rect[slot].w = img_surf->w;
                rc_himage_rect[slot].h = img_surf->h;
                rc_image_width[slot] = img_surf->w;
                rc_image_height[slot] = img_surf->h;
                rc_image_isLoaded[slot] = true;
            }
        }

        SDL_FreeSurface(img_surf);
    }
}

void rc_media_getScreenClip2_hw(int slot, int sx, int sy, int sw, int sh, bool flag)
{
    if(!flag)
    {
        rc_media_getScreenClip_hw(slot, sx, sy, sw, sh);
    }
    else if(rc_screenCheck(rc_active_screen))
    {
        if(rc_himage[slot][rc_active_window] != NULL)
        {
            cout << "CanvasClip_Ex Error: Image slot is already occupied" << endl;
            return;
        }
        SDL_Rect src, dst;
        rc_himage[slot][rc_active_window] = SDL_CreateTexture(rc_win_renderer[rc_active_window], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, sw, sh);
        src.x = sx;
        src.y = sy;
        src.w = sw;
        src.h = sh;
        dst.x = 0;
        dst.y = 0;
        dst.w = sw;
        dst.h = sh;
        rc_himage_rect[slot] = dst;
        rc_image_width[slot] = sw;
        rc_image_height[slot] = sh;
        rc_image_isLoaded[slot] = true;
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_himage[slot][rc_active_window]);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], 0, 0, 0, 0);
        SDL_RenderClear(rc_win_renderer[rc_active_window]);
        SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen], &src, &dst);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
    }
}



void rc_media_getWindowClip_hw(int slot, int sx, int sy, int sw, int sh)
{
    SDL_Surface * img_surf = SDL_CreateRGBSurface(0, sw, sh, 32, 0, 0, 0, 0);
    SDL_Rect src_rect;
    src_rect.x = sx;
    src_rect.y = sy;
    src_rect.w = sw;
    src_rect.h = sh;
    //SDL_BlitSurface(rc_sscreen[rc_active_window][src_screen], &src_rect, rc_sscreen[rc_active_window][dst_screen], &dst_rect);
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
    SDL_RenderReadPixels(rc_win_renderer[rc_active_window], &src_rect, rc_pformat->format, img_surf->pixels, img_surf->pitch);

    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        if(rc_win_renderer[i]!=NULL)
        {
            if(rc_himage[slot][i]!=NULL)
            {
                SDL_DestroyTexture(rc_himage[slot][i]);
                rc_himage[slot][i] = NULL;
            }
            rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], img_surf);
            rc_himage_rect[slot].x = 0;
            rc_himage_rect[slot].y = 0;
            rc_himage_rect[slot].w = img_surf->w;
            rc_himage_rect[slot].h = img_surf->h;
            rc_image_width[slot] = img_surf->w;
            rc_image_height[slot] = img_surf->h;
            rc_image_isLoaded[slot] = true;
        }
    }

    SDL_FreeSurface(img_surf);
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
}

void rc_media_cloneScreen_hw(int src_screen, int dst_screen)
{
    if(rc_screenCheck(src_screen) && (dst_screen >= 0 && dst_screen < MAX_SCREENS))
    {
        if(rc_hscreen[rc_active_window][dst_screen] == NULL)
        {
            rc_hscreen[rc_active_window][dst_screen] = rc_hscreen[rc_active_window][src_screen];
            rc_screen_width[rc_active_window][dst_screen] = rc_screen_width[rc_active_window][src_screen];
            rc_screen_height[rc_active_window][dst_screen] = rc_screen_height[rc_active_window][src_screen];
            rc_screen_rect[rc_active_window][dst_screen] = rc_screen_rect[rc_active_window][src_screen];
            rc_screenview[rc_active_window][dst_screen] = rc_screenview[rc_active_window][src_screen];
            rc_screen_visible[rc_active_window][dst_screen] = rc_screen_visible[rc_active_window][src_screen];
        }
    }
}

void rc_sortZ(int priority_screen)
{
    int aw  = rc_active_window;
    int draw_order = 0;
    for(int z = 0; z < MAX_SCREENS; z++)
    {
        if(rc_screen_z[aw][priority_screen] == z)
        {
            rc_screen_zOrder[aw][draw_order] = priority_screen;
            draw_order++;
        }
        for(int n = 0; n < MAX_SCREENS; n++)
        {
			if(rc_screen_z[aw][n] == z && n != priority_screen)
			{
				rc_screen_zOrder[aw][draw_order] = n;
				draw_order++;
			}
		}
    }
}

void rc_media_setScreenZ(int s_num, int z)
{
    if(rc_screenCheck(s_num))
    {
        if(z < 0 || z >= MAX_SCREENS)
        {
            cout << "SetScreenZ Error: Z Order must be a value from 0 to " << MAX_SCREENS-1 << endl;
            return;
        }
        //int tmp_z = 0;
        //int tmp_order[MAX_SCREENS];
        //cout << "z_start: " << rc_screen_zOrder[rc_active_window][rc_active_screen] << endl;

        rc_screen_z[rc_active_window][s_num] = z;

        rc_sortZ(s_num);

        //for(int i = 0; i < MAX_SCREENS; i++)
            //cout << "z: " << rc_screen_zOrder[rc_active_window][i] << endl;
    }
}

int rc_media_screenZ(int s_num)
{
    if(rc_screenCheck(s_num))
    {
        return rc_screen_z[rc_active_window][s_num];
    }
    return -1;
}

void rc_media_box_hw(int x1, int y1, int x2, int y2)
{
	Sint16 vx[4], vy[4];

    vx[0] = (Sint16)x1;
    vy[0] = (Sint16)y1;

    vx[1] = (Sint16)x2;
    vy[1] = (Sint16)y1;

    vx[2] = (Sint16)x2;
    vy[2] = (Sint16)y2;

    vx[3] = (Sint16)x1;
    vy[3] = (Sint16)y2;

    polygonRGBA(rc_win_renderer[rc_active_window], vx, vy, 4, rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
}

void rc_media_boxFill_hw(int x1, int y1, int x2, int y2)
{
	Sint16 vx[4], vy[4];

    vx[0] = (Sint16)x1;
    vy[0] = (Sint16)y1;

    vx[1] = (Sint16)x2;
    vy[1] = (Sint16)y1;

    vx[2] = (Sint16)x2;
    vy[2] = (Sint16)y2;

    vx[3] = (Sint16)x1;
    vy[3] = (Sint16)y2;

    filledPolygonRGBA(rc_win_renderer[rc_active_window], vx, vy, 4, rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
}

void rc_media_rectangle(int x, int y, int w, int h)
{
	SDL_Rect rect_dim;
    rect_dim.x = x;
    rect_dim.y = y;
    rect_dim.w = w;
    rect_dim.h = h;

    SDL_RenderDrawRect(rc_win_renderer[rc_active_window], &rect_dim);
}

void rc_media_rectangleFill(int x, int y, int w, int h)
{
    SDL_Rect rect_dim;
    rect_dim.x = x;
    rect_dim.y = y;
    rect_dim.w = w;
    rect_dim.h = h;

    SDL_RenderFillRect(rc_win_renderer[rc_active_window], &rect_dim);
}

void rc_media_roundRect(int x, int y, int w, int h, int r)
{
    roundedRectangleRGBA(rc_win_renderer[rc_active_window], x, y, x+(w-1), y+(h-1), r, rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
}

void rc_media_roundRectFill(int x, int y, int w, int h, int r)
{
    roundedBoxRGBA(rc_win_renderer[rc_active_window], x, y, x+(w-1), y+(h-1), r, rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
}

void rc_media_circle_hw(int xc, int yc, int r)
{
    circleRGBA(rc_win_renderer[rc_active_window], xc, yc, r, rc_ink >> 16, rc_ink >> 8, rc_ink, rc_ink >> 24);
}

void rc_media_circleFill_hw(int xc, int yc, int r)
{
    filledCircleRGBA(rc_win_renderer[rc_active_window], xc, yc, r, rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
}

void rc_media_ellipse_hw(int xc, int yc, int width, int height)
{
    ellipseRGBA(rc_win_renderer[rc_active_window], xc, yc, width, height, rc_ink >> 16, rc_ink >> 8, rc_ink, rc_ink>>24);
}

void rc_media_ellipseFill_hw(int xc, int yc, int width, int height)
{
    filledEllipseRGBA(rc_win_renderer[rc_active_window], xc, yc, width, height, rc_ink >> 16, rc_ink >> 8, rc_ink, rc_ink>>24);
}

Uint32 rc_media_getPixel_hw(int x, int y)
{
    //Uint32 * s_pixels = (Uint32*) rc_win_surface[rc_active_window]->pixels;
    #ifdef RC_MOBILE
    SDL_Texture * tmp_buf = SDL_CreateTexture(rc_win_renderer[rc_active_window], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, rc_win_width[rc_active_window], rc_win_height[rc_active_window]);
    if(tmp_buf==NULL)
        return 0;
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], tmp_buf);
    SDL_RendererFlip rf = SDL_FLIP_NONE;
    SDL_RenderCopyEx(rc_win_renderer[rc_active_window], rc_backBuffer[rc_active_window], NULL, NULL, 0, NULL, rf);
    #else
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
    #endif // RC_MOBILE

    //cout << "surface = ( " << rc_win_surface[rc_active_window]->w << ", " << rc_win_surface[rc_active_window]->h << " ) " << endl;
    //int w = 0;
    //int h = 0;
    //SDL_GetWindowSize(rc_win[rc_active_window], &w, &h);
    //w = rc_displayMode[rc_active_window].w;
    //h = rc_displayMode[rc_active_window].h;
    Uint32 * s_pixels = (Uint32*)SDL_malloc(sizeof(Uint32));
    SDL_Rect p_rect;
    #ifdef RC_MOBILE
    p_rect.x = x;
    p_rect.y = y;
    #else
    p_rect.x = x / rc_fullscreen_mouse_scale_x[rc_active_window];
    p_rect.y = y / rc_fullscreen_mouse_scale_y[rc_active_window];
    #endif // RC_MOBILE
    p_rect.w = 1;
    p_rect.h = 1;
    SDL_RenderReadPixels(rc_win_renderer[rc_active_window], &p_rect, rc_pformat->format, (void*)s_pixels, 4);

    Uint32 p_color =  s_pixels[0];

    #ifdef RC_MOBILE
    SDL_DestroyTexture(tmp_buf);
    int r = p_color & 255;
    int g = (p_color >> 8) & 255;
    int b = (p_color >> 16) & 255;
    int a = (p_color >> 24) & 255;
    //p_color = SDL_MapRGBA(rc_pformat, r, g, b, a);
    #endif // RC_MOBILE

    //cout << "color = " << p_color << endl;
    SDL_free(s_pixels);
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
    return p_color;
}

void rc_media_ink(Uint32 ink_color)
{
    //cout << "ink = " << ink_color << endl;
    rc_ink = ink_color;
    rc_ink_color.a = ink_color>>24;//ink_color >> 24;
    //cout << "alpha = " << (int)rc_ink_color.a << endl;
    rc_ink_color.r = ink_color >> 16;
    rc_ink_color.g = ink_color >> 8;
    rc_ink_color.b = ink_color;
    SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
}

void rc_media_setClearColor(Uint32 c_color)
{
    rc_clearColor = c_color;
}

Uint32 rc_media_rgb(Uint8 r, Uint8 g, Uint8 b)
{
    //cout << "r = " << (int)  r << "   g = " << (int) g << "   b = " << (int)b << endl;
    Uint32 rgba_map = (Uint32)SDL_MapRGBA(rc_pformat,r,g,b,255);
    //Uint32 rgba_map = (r << 16) + (g << 8) + b + (255 << 24);// + (255<<24);
    //cout << "rgb_out = " << rgba_map << endl;
    return rgba_map;
}

Uint32 rc_media_rgba(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    Uint32 rgba_map = (Uint32)SDL_MapRGBA(rc_pformat,r,g,b,a);
    //rgba_map = rgba_map + (a<<24);
    return rgba_map;
}

void rc_media_line_hw(int x1, int y1, int x2, int y2)
{
    lineRGBA(rc_win_renderer[rc_active_window], x1, y1, x2, y2, rc_ink >> 16, rc_ink >> 8, rc_ink, rc_ink >> 24);
}

void rc_getPrevColor(int x, int y)
{
    //cout << "PCOLOR #1" << endl;
    Uint32 * s_pixels = (Uint32*)rc_sscreen[rc_active_window][rc_active_screen]->pixels;
    //cout << "PCOLOR #2: " << y << " , " << rc_active_window << " , " << rc_active_screen << " , " << x << endl;
    prev_color = s_pixels[y*rc_sscreen[rc_active_window][rc_active_screen]->w+x];
    //cout << "PCOLOR #3" << endl;
}

void rc_media_floodFill_sw(int x, int y, Uint32* s_pixels, int pitch, int w)
{
    int s_lock = 0;
    //cout << "u1" << endl;
    if(SDL_MUSTLOCK(rc_sscreen[rc_active_window][rc_active_screen]))
    {
        //cout << "u2" << endl;
        s_lock = 1;
        SDL_LockSurface(rc_sscreen[rc_active_window][rc_active_screen]);
    }
    //cout << "u3" << endl;
    //Uint32 * s_pixels = (Uint32*) rc_sscreen[rc_active_window][rc_active_screen]->pixels;
    //cout << "u4" << endl;
    //int pitch = rc_sscreen[rc_active_window][rc_active_screen]->pitch;
    //cout << "u5" << endl;
    //int w = rc_sscreen[rc_active_window][rc_active_screen]->pitch/4;
    //cout << "u6" << endl;

    // Base cases
    if (x < 0 || x >= rc_screen_width[rc_active_window][rc_active_screen] || y < 0 || y >= rc_screen_height[rc_active_window][rc_active_screen])
        return;
    //cout << "u7" << endl;
    if (s_pixels[y*w+x] != prev_color)
        return;
    //cout << "u8" << endl;

    // Replace the color at (x, y)
    s_pixels[y*w+x] = rc_ink;

    //cout << "u8-1" << endl; cout << "x = " << x << "; y = " << y << endl;

    // Recur for north, east, south and west
    rc_media_floodFill_sw(x+1, y, s_pixels, pitch, w);
    rc_media_floodFill_sw(x-1, y, s_pixels, pitch, w);
    rc_media_floodFill_sw(x, y+1, s_pixels, pitch, w);
    rc_media_floodFill_sw(x, y-1, s_pixels, pitch, w);

    //cout << "u8-2" << endl;

    if(s_lock == 1)
    {
        //cout << "u9" << endl;
        SDL_UnlockSurface(rc_sscreen[rc_active_window][rc_active_screen]);
        //cout << "u10" << endl;
    }
}

void rc_media_floodFill_hw(int x, int y)
{
    rc_sscreen[rc_active_window][rc_active_screen] = SDL_CreateRGBSurface(0, rc_screen_width[rc_active_window][rc_active_screen], rc_screen_height[rc_active_window][rc_active_screen], 32, 0, 0, 0, 0);
    SDL_Rect c_screen;
    c_screen.x = 0;
    c_screen.y = 0;
    c_screen.w = rc_screen_width[rc_active_window][rc_active_screen];
    c_screen.h = rc_screen_height[rc_active_window][rc_active_screen];
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window],NULL);
    SDL_RenderCopy(rc_win_renderer[rc_active_window],rc_hscreen[rc_active_window][rc_active_screen],NULL,&c_screen);
    //SDL_RendererFlip rf = (SDL_RendererFlip)SDL_FLIP_VERTICAL;
    //SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_hscreen[rc_active_window][rc_active_screen],NULL,NULL,0,NULL,rf);

    //cout << "DEBUG_FLOOD CP 1" << endl;

    if(SDL_RenderReadPixels(rc_win_renderer[rc_active_window], &c_screen, rc_pformat->format,rc_sscreen[rc_active_window][rc_active_screen]->pixels,rc_sscreen[rc_active_window][rc_active_screen]->pitch) < 0)
    {
        cout << "ReadPixel Error: " << SDL_GetError() << endl;
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);

    }
    else
    {
        //cout << "DEBUG_FLOOD CP 2" << endl;
        rc_getPrevColor(x, y);
        //cout << "DEBUG_FLOOD CP 3" << endl;
        Uint32 * s_pixels = (Uint32*) rc_sscreen[rc_active_window][rc_active_screen]->pixels;
        int pitch = rc_sscreen[rc_active_window][rc_active_screen]->pitch;
        int w = rc_sscreen[rc_active_window][rc_active_screen]->pitch/4;
        //cout << "pitch = " << pitch << endl;
        //cout << "w = " << w << endl;
        //string bs=""; cin>>bs;
        if(s_pixels[y*w+x] != rc_ink)
            rc_media_floodFill_sw(x,y,s_pixels, pitch, w);
        //cout << "DEBUG_FLOOD CP 4" << endl;
        SDL_Texture * tmp_tex = SDL_CreateTextureFromSurface(rc_win_renderer[rc_active_window], rc_sscreen[rc_active_window][rc_active_screen]);
        //cout << "DEBUG_FLOOD CP 5" << endl;

        if(tmp_tex==NULL)
        {
            cout << "FloodFill Error: Canvas Buffer could not be created" << endl;
            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);

        }
        else
        {
            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
            SDL_RenderCopy(rc_win_renderer[rc_active_window],tmp_tex,NULL,NULL);
        }
        SDL_DestroyTexture(tmp_tex);
    }

    SDL_FreeSurface(rc_sscreen[rc_active_window][rc_active_screen]);
    rc_sscreen[rc_active_window][rc_active_screen] = NULL;

}

void rc_media_drawPixel_hw(int x, int y)
{
    pixelRGBA(rc_win_renderer[rc_active_window], x, y, rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
}

void rc_media_poly(unsigned int n, double* vx_d, double* vy_d)
{
    Sint16 vx[n], vy[n];
    for(int i = 0; i < n; i++)
    {
        vx[i] = (Sint16)vx_d[i];
        vy[i] = (Sint16)vy_d[i];
    }
    polygonRGBA(rc_win_renderer[rc_active_window], vx, vy, n, rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
}

void rc_media_polyfill(unsigned int n, double* vx_d, double* vy_d)
{
    Sint16 vx[n], vy[n];
    for(int i = 0; i < n; i++)
    {
        vx[i] = (Sint16)vx_d[i];
        vy[i] = (Sint16)vy_d[i];
    }
    filledPolygonRGBA(rc_win_renderer[rc_active_window], vx, vy, n, rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
}

void rc_media_loadImage_hw(int slot, string img_file)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "LoadImage Error: Image Slot must be in the range of 0 to " << MAX_IMAGES << endl;
        return;
    }
    if(rc_himage[slot][rc_active_window]!=NULL)
    {
        cout << "LoadImage Error: Image " << slot << " is already in use" << endl;
        return;
    }
    //mariocircuit-1.png
    SDL_Surface * image = IMG_Load(img_file.c_str());
    if(image == NULL)
    {
        cout << "~Image: " << img_file.c_str() << endl;
        cout << "LoadImage Error: " << IMG_GetError() << endl;
        return;
    }
    #ifdef RC_MOBILE
        SDL_Surface * image_cv = SDL_ConvertSurfaceFormat(image, rc_pformat->format, 0);
    #else
        SDL_Surface * image_cv = SDL_ConvertSurface(image, rc_pformat,0);
    #endif // RC_MOBILE
    rc_image_width[slot] = image_cv->w;
    rc_image_height[slot] = image_cv->h;
    rc_image_isLoaded[slot] = true;
    if(image_cv == NULL)
    {
        cout << "LoadImage Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(image);
        return;
    }

    #ifdef RC_MOBILE
    if(rc_himage[slot][rc_active_window] != NULL)
        SDL_DestroyTexture(rc_himage[slot][rc_active_window]);
    rc_himage[slot][rc_active_window] = SDL_CreateTextureFromSurface(rc_win_renderer[rc_active_window], image_cv);
    SDL_SetTextureBlendMode(rc_himage[slot][rc_active_window], SDL_BLENDMODE_BLEND);
    #else

    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        if(rc_himage[slot][i] != NULL)
            SDL_DestroyTexture(rc_himage[slot][i]);
        rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], image_cv);
        SDL_SetTextureBlendMode(rc_himage[slot][i], SDL_BLENDMODE_BLEND);
        if(i == rc_active_window && rc_himage[slot][rc_active_window] == NULL)
        {
            cout << "#LoadImage Error: " << SDL_GetError() << endl;
            SDL_FreeSurface(image);
            SDL_FreeSurface(image_cv);
            for(int j = 0; j < i; j++)
                SDL_DestroyTexture(rc_himage[slot][j]);
            return;
        }
    }

    #endif // RC_MOBILE
    SDL_FreeSurface(image);
    SDL_FreeSurface(image_cv);
}

void rc_media_loadImage_ex_hw(int slot, string img_file, double color)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "LoadImage_Ex Error: Image Slot must be in the range of 0 to " << MAX_IMAGES << endl;
        return;
    }
    if(rc_himage[slot][rc_active_window]!=NULL)
    {
        cout << "LoadImage_Ex Error: Image Slot is already in use" << endl;
        return;
    }
    SDL_Surface * image = IMG_Load(img_file.c_str());
    if(image == NULL)
    {
        cout << "LoadImage_Ex Error: " << SDL_GetError() << endl;
        return;
    }

    if(color < 0)
    {
        Uint32 * c = (Uint32*)image->pixels;
        SDL_SetColorKey(image, SDL_TRUE, c[0]);
    }
    else
        SDL_SetColorKey(image, SDL_TRUE, (Uint32)color);

    #ifdef RC_MOBILE
    SDL_Surface * image_cv = SDL_ConvertSurfaceFormat(image, rc_pformat->format, 0);
    #else
    SDL_Surface * image_cv = SDL_ConvertSurface(image, rc_pformat,0);
    #endif // RC_MOBILE
    rc_image_width[slot] = image_cv->w;
    rc_image_height[slot] = image_cv->h;
    rc_image_isLoaded[slot] = true;
    if(image_cv == NULL)
    {
        cout << "LoadImage_Ex Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(image);
        return;
    }

    #ifdef RC_MOBILE
    if(rc_himage[slot][rc_active_window] != NULL)
        SDL_DestroyTexture(rc_himage[slot][rc_active_window]);
    rc_himage[slot][rc_active_window] = SDL_CreateTextureFromSurface(rc_win_renderer[rc_active_window], image_cv);
    SDL_SetTextureBlendMode(rc_himage[slot][rc_active_window], SDL_BLENDMODE_BLEND);
    #else

    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        if(rc_himage[slot][i] != NULL)
            SDL_DestroyTexture(rc_himage[slot][i]);
        rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], image_cv);
        SDL_SetTextureBlendMode(rc_himage[slot][i], SDL_BLENDMODE_BLEND);
        if(i == rc_active_window && rc_himage[slot][rc_active_window] == NULL)
        {
            cout << "#LoadImage_Ex Error: " << SDL_GetError() << endl;
            SDL_FreeSurface(image);
            SDL_FreeSurface(image_cv);
            for(int j = 0; j < i; j++)
                SDL_DestroyTexture(rc_himage[slot][j]);
            return;
        }
    }

    #endif // RC_MOBILE

    SDL_FreeSurface(image);
    SDL_FreeSurface(image_cv);
}

void rc_media_createImage_hw(int slot, int w, int h, double * pdata)
{
    if(rc_himage[slot][rc_active_window] != NULL)
    {
        cout << "CreateImage Error: Image already exist" << endl;
        return;
    }

    SDL_Surface * img_surf = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    Uint32 * img_pixels = (Uint32*)img_surf->pixels;
    for(int i = 0; i < (w*h); i++)
    {
        img_pixels[i] = (Uint32)pdata[i];
    }
    #ifdef RC_MOBILE
    SDL_DestroyTexture(rc_himage[slot][rc_active_window]);
    rc_himage[slot][rc_active_window] = SDL_CreateTextureFromSurface(rc_win_renderer[rc_active_window], img_surf);
    SDL_SetTextureBlendMode(rc_himage[slot][rc_active_window], SDL_BLENDMODE_BLEND);

    if(rc_himage[slot][rc_active_window] == NULL)
    {
        cout << "#CreateImage Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(img_surf);
        SDL_DestroyTexture(rc_himage[slot][rc_active_window]);
        return;
    }
    #else
    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        SDL_DestroyTexture(rc_himage[slot][i]);
        rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], img_surf);
        SDL_SetTextureBlendMode(rc_himage[slot][i], SDL_BLENDMODE_BLEND);
    }
    if(rc_himage[slot][rc_active_window] == NULL)
    {
        cout << "#CreateImage Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(img_surf);
        for(int j = 0; j < MAX_WINDOWS; j++)
        {
            SDL_DestroyTexture(rc_himage[slot][j]);
            rc_himage[slot][j] = NULL;
        }
        return;
    }
    #endif // RC_MOBILE
    rc_image_width[slot] = img_surf->w;
    rc_image_height[slot] = img_surf->h;
    rc_image_isLoaded[slot] = true;
    SDL_FreeSurface(img_surf);
}

void rc_media_createImage_Ex_hw(int slot, int w, int h, double * pdata, double color)
{
    if(rc_himage[slot][rc_active_window] != NULL)
    {
        cout << "CreateImage_Ex Error: Image already exist" << endl;
        return;
    }

    SDL_Surface * img_surf = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
    Uint32 * img_pixels = (Uint32*)img_surf->pixels;
    for(int i = 0; i < (w*h); i++)
    {
        img_pixels[i] = (Uint32)pdata[i];
    }
    #ifdef RC_MOBILE
    SDL_Surface * image_cv = SDL_ConvertSurfaceFormat(img_surf, rc_pformat->format,0);
    #else
    SDL_Surface * image_cv = SDL_ConvertSurface(img_surf, rc_pformat,0);
    #endif // RC_MOBILE
    if(image_cv == NULL)
    {
        cout << "CreateImage_Ex Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(img_surf);
        return;
    }
    if((Uint32)color<0)
        SDL_SetColorKey(image_cv, SDL_TRUE, img_pixels[0]);
    else
        SDL_SetColorKey(image_cv, SDL_TRUE, (Uint32)color);

    #ifdef RC_MOBILE
    SDL_DestroyTexture(rc_himage[slot][rc_active_window]);
    rc_himage[slot][rc_active_window] = SDL_CreateTextureFromSurface(rc_win_renderer[rc_active_window], image_cv);
    SDL_SetTextureBlendMode(rc_himage[slot][rc_active_window], SDL_BLENDMODE_BLEND);

    if(rc_himage[slot][rc_active_window] == NULL)
    {
        cout << "#CreateImage_Ex Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(img_surf);
        SDL_FreeSurface(image_cv);
        SDL_DestroyTexture(rc_himage[slot][rc_active_window]);
        rc_himage[slot][rc_active_window] = NULL;
        return;
    }
    #else
    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        SDL_DestroyTexture(rc_himage[slot][i]);
        rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], image_cv);
        SDL_SetTextureBlendMode(rc_himage[slot][i], SDL_BLENDMODE_BLEND);
    }
    if(rc_himage[slot][rc_active_window] == NULL)
    {
        cout << "#CreateImage_Ex Error: " << SDL_GetError() << endl;
        SDL_FreeSurface(img_surf);
        SDL_FreeSurface(image_cv);
        for(int j = 0; j < MAX_WINDOWS; j++)
        {
            SDL_DestroyTexture(rc_himage[slot][j]);
            rc_himage[slot][j] = NULL;
        }
        return;
    }
    #endif // RC_MOBILE
    rc_image_width[slot] = image_cv->w;
    rc_image_height[slot] = image_cv->h;
    rc_image_isLoaded[slot] = true;
    SDL_FreeSurface(img_surf);
    SDL_FreeSurface(image_cv);
}

void rc_media_bufferFromImage(int slot, double * pdata)
{
    SDL_Rect img_rect;
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = rc_image_width[slot];
    img_rect.h = rc_image_height[slot];

    //cout << "Debug data: " << img_rect.w << ", " << img_rect.h << endl;


    //SDL_RendererFlip rf = (SDL_RendererFlip)(SDL_FLIP_VERTICAL);

    SDL_Surface * tmp_surf = SDL_CreateRGBSurface(0, rc_image_width[slot], rc_image_height[slot], 32, 0, 0, 0, 0);
    SDL_Texture * tmp_tex = SDL_CreateTexture(rc_win_renderer[rc_active_window], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, rc_image_width[slot], rc_image_height[slot]);
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window],NULL);
    SDL_RenderCopy(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,&img_rect);
    //SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,NULL,0,NULL,rf);

    SDL_RenderReadPixels(rc_win_renderer[rc_active_window], &img_rect, rc_pformat->format,tmp_surf->pixels,tmp_surf->pitch);
    //cout << "Colorkey = " << (Uint32)r << ", " << (Uint32)g << ", " << (Uint32)b << ", " << (Uint32)a << endl;
    Uint32 * pxl = (Uint32*)tmp_surf->pixels;

    for(int y = 0; y < img_rect.h; y ++)
    {
        for(int x = 0; x < img_rect.w; x++)
        {
            pdata[y*img_rect.w+x] = pxl[y*img_rect.w+x];
        }
    }

    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
    SDL_DestroyTexture(tmp_tex);
    SDL_FreeSurface(tmp_surf);

}

#ifdef RC_IOS
void rc_media_colorKey_hw(int slot, double color)
{
    Uint32 c = (Uint32) color;
    //Uint8 r = c >> 16;
    //Uint8 g = c >> 8;
    //Uint8 b = c;
    //Uint8 a = c >> 24;
    //c = SDL_MapRGBA(rc_win_surface[0]->format,r,g,b,255);
    if(color > 0)
    {
        //return;
        SDL_RendererFlip rf = (SDL_RendererFlip)(SDL_FLIP_NONE);

        SDL_Surface * tmp_surf = SDL_CreateRGBSurface(0, rc_image_width[slot], rc_image_height[slot], 32, 0, 0, 0, 0);
        SDL_Texture * tmp_tex = SDL_CreateTexture(rc_win_renderer[rc_active_window], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, rc_image_width[slot], rc_image_height[slot]);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window],tmp_tex);
        //SDL_RenderCopy(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,NULL);
        SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,NULL,0,NULL,rf);

        SDL_RenderReadPixels(rc_win_renderer[rc_active_window], NULL, rc_pformat->format,tmp_surf->pixels,tmp_surf->pitch);
        //cout << "Colorkey = " << (Uint32)r << ", " << (Uint32)g << ", " << (Uint32)b << ", " << (Uint32)a << endl;
        SDL_SetColorKey(tmp_surf,SDL_TRUE,c);

        for(int i = 0; i < MAX_WINDOWS; i++)
        {
            SDL_DestroyTexture(rc_himage[slot][i]);
            rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], tmp_surf);
        }
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
        SDL_DestroyTexture(tmp_tex);
        SDL_FreeSurface(tmp_surf);
    }
    else
    {
        SDL_RendererFlip rf = (SDL_RendererFlip)(SDL_FLIP_NONE);

        SDL_Surface * tmp_surf = SDL_CreateRGBSurface(0, rc_image_width[slot], rc_image_height[slot], 32, 0, 0, 0, 0);
        //SDL_Surface * tmp_surf = SDL_ConvertSurfaceFormat(tmp_psurf, rc_pformat->format, 0);
        //SDL_FreeSurface(tmp_psurf);
        SDL_Texture * tmp_tex = SDL_CreateTexture(rc_win_renderer[rc_active_window], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, rc_image_width[slot], rc_image_height[slot]);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window],tmp_tex);
        //SDL_RenderCopy(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,NULL);
        SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,NULL,0,NULL,rf);

        SDL_RenderReadPixels(rc_win_renderer[rc_active_window], NULL, rc_pformat->format,tmp_surf->pixels,tmp_surf->pitch);
        //cout << "Colorkey = " << (Uint32)r << ", " << (Uint32)g << ", " << (Uint32)b << ", " << (Uint32)a << endl;
        Uint32 * gcolor = (Uint32*)tmp_surf->pixels;
        c = gcolor[0];
        SDL_SetColorKey(tmp_surf,SDL_TRUE,c);

        for(int i = 0; i < MAX_WINDOWS; i++)
        {
            SDL_DestroyTexture(rc_himage[slot][i]);
            rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], tmp_surf);
        }
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
        SDL_DestroyTexture(tmp_tex);
        SDL_FreeSurface(tmp_surf);
    }
}
#else
void rc_media_colorKey_hw(int slot, double color)
{
    Uint32 c = (Uint32) color;
    //Uint8 r = c >> 16;
    //Uint8 g = c >> 8;
    //Uint8 b = c;
    //Uint8 a = c >> 24;
    //c = SDL_MapRGBA(rc_win_surface[0]->format,r,g,b,255);
    SDL_Rect img_rect;
    img_rect.x = 0;
    img_rect.y = 0;
    img_rect.w = rc_image_width[slot];
    img_rect.h = rc_image_height[slot];
    if(color >= 0)
    {
        //return;
        //SDL_RendererFlip rf = (SDL_RendererFlip)(SDL_FLIP_VERTICAL);

        SDL_Surface * tmp_surf = SDL_CreateRGBSurface(0, rc_image_width[slot], rc_image_height[slot], 32, 0, 0, 0, 0);
        SDL_Texture * tmp_tex = SDL_CreateTexture(rc_win_renderer[rc_active_window], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, rc_image_width[slot], rc_image_height[slot]);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window],NULL);
        SDL_RenderCopy(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,&img_rect);
        //SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,NULL,0,NULL,rf);

        SDL_RenderReadPixels(rc_win_renderer[rc_active_window], &img_rect, rc_pformat->format,tmp_surf->pixels,tmp_surf->pitch);
        //cout << "Colorkey = " << (Uint32)r << ", " << (Uint32)g << ", " << (Uint32)b << ", " << (Uint32)a << endl;
        rc_image_colorKey[slot] = c;
        rc_image_colorKey_r[slot] = c >> 16;
        rc_image_colorKey_g[slot] = c >> 8;
        rc_image_colorKey_b[slot] = c;
        rc_image_colorKey_a[slot] = c >> 24;

        SDL_SetColorKey(tmp_surf,SDL_TRUE,c);

        for(int i = 0; i < MAX_WINDOWS; i++)
        {
            SDL_DestroyTexture(rc_himage[slot][i]);
            rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], tmp_surf);
        }
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
        SDL_DestroyTexture(tmp_tex);
        SDL_FreeSurface(tmp_surf);
    }
    else
    {
        //SDL_RendererFlip rf = (SDL_RendererFlip)(SDL_FLIP_VERTICAL);

        SDL_Surface * tmp_surf = SDL_CreateRGBSurface(0, rc_image_width[slot], rc_image_height[slot], 32, 0, 0, 0, 0);
        SDL_Texture * tmp_tex = SDL_CreateTexture(rc_win_renderer[rc_active_window], rc_pformat->format, SDL_TEXTUREACCESS_TARGET, rc_image_width[slot], rc_image_height[slot]);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window],NULL);
        SDL_RenderCopy(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,&img_rect);
        //SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,NULL,0,NULL,rf);

        SDL_RenderReadPixels(rc_win_renderer[rc_active_window], &img_rect, rc_pformat->format,tmp_surf->pixels,tmp_surf->pitch);
        //cout << "Colorkey = " << (Uint32)r << ", " << (Uint32)g << ", " << (Uint32)b << ", " << (Uint32)a << endl;
        Uint32 * pxl = (Uint32*)tmp_surf->pixels;
        c = pxl[0];
        rc_image_colorKey[slot] = c;
        rc_image_colorKey_r[slot] = c >> 16;
        rc_image_colorKey_g[slot] = c >> 8;
        rc_image_colorKey_b[slot] = c;
        rc_image_colorKey_a[slot] = c >> 24;
        SDL_SetColorKey(tmp_surf,SDL_TRUE,c);

        for(int i = 0; i < MAX_WINDOWS; i++)
        {
            SDL_DestroyTexture(rc_himage[slot][i]);
            rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], tmp_surf);
        }
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
        SDL_DestroyTexture(tmp_tex);
        SDL_FreeSurface(tmp_surf);
    }
}
#endif //RC_IOS

void rc_media_deleteImage_hw(int slot)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "DeleteImage Error: Image Slot must be in the range of 0 to " << MAX_IMAGES-1 << endl;
        return;
    }
    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        if(rc_himage[slot][i] == NULL)
            continue;
        SDL_DestroyTexture(rc_himage[slot][i]);
        rc_himage[slot][i] = NULL;
    }
    rc_image_isLoaded[slot] = false;
    rc_image_width[slot] = 0;
    rc_image_height[slot] = 0;
}

void rc_media_setImageAlpha_hw(int slot, Uint8 alpha)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "SetImageAlpha Error: Image Slot must be in the range of 0 to " << MAX_IMAGES-1 << endl;
        return;
    }
    if(rc_himage[slot][rc_active_window]==NULL)
    {
        cout << "SetImageAlpha Error: Image Slot is empty" << endl;
        return;
    }
    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        if(rc_himage[slot][i] != NULL)
        {
            SDL_SetTextureAlphaMod(rc_himage[slot][i],alpha);
        }
    }
}

int rc_media_getImageAlpha_hw(int slot)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "GetImageAlpha Error: Image Slot must be in the range of 0 to " << MAX_IMAGES-1 << endl;
        return -1;
    }
    if(rc_himage[slot][rc_active_window]==NULL)
    {
        cout << "GetImageAlpha Error: Image Slot is empty" << endl;
        return -1;
    }
    Uint8 a = 0;
    SDL_GetTextureAlphaMod(rc_himage[slot][rc_active_window], &a);
    return a;
}

void rc_media_getImageSize_hw(int slot, double * w, double * h)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "GetImageSize Error: Image Slot must be in the range of 0 to " << MAX_IMAGES-1 << endl;
        return;
    }
    if(rc_himage[slot][rc_active_window]==NULL)
    {
        cout << "GetImageSize Error: Image Slot is empty" << endl;
        *w = 0;
        *h = 0;
        return;
    }
    Uint32 format = 0;
    int access = 0, width = 0, height = 0;
    SDL_QueryTexture(rc_himage[slot][rc_active_window], &format, &access, &width, &height);
    *w = width;
    *h = height;
}

int rc_media_setImageBlendMode_hw(int slot, int blend_mode)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "SetImageBlendMode Error: Image Slot must be in the range of 0 to " << MAX_IMAGES-1 << endl;
        return -1;
    }
    if(rc_himage[slot][rc_active_window]==NULL)
    {
        cout << "SetImageBlendMode Error: Image Slot is empty" << endl;
        return -1;
    }
    int rslt = -1;
    SDL_BlendMode b = SDL_BLENDMODE_NONE;
    switch(blend_mode)
    {
    case 0: //SDL_BLENDMODE_NONE
        b = SDL_BLENDMODE_NONE;
        break;
    case 1: //SDL_BLENDMODE_BLEND
        b = SDL_BLENDMODE_BLEND;
        break;
    case 2: //SDL_BLENDMODE_ADD
        b = SDL_BLENDMODE_ADD;
        break;
    case 4: //SDL_BLENDMODE_MOD
        b = SDL_BLENDMODE_MOD;
        break;
    default:
        return rslt;
    }
    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        if(rc_himage[slot][i] != NULL)
        {

            rslt = SDL_SetTextureBlendMode(rc_himage[slot][i], b);
        }
    }
    return rslt;
}

int rc_media_imageBlendMode_hw(int slot)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "ImageBlendMode Error: Image Slot must be in the range of 0 to " << MAX_IMAGES-1 << endl;
        return -1;
    }
    if(rc_himage[slot][rc_active_window]==NULL)
    {
        cout << "ImageBlendMode Error: Image Slot is empty" << endl;
        return -1;
    }
    SDL_BlendMode blend_mode = SDL_BLENDMODE_NONE;
    int rslt = SDL_GetTextureBlendMode(rc_himage[slot][rc_active_window], &blend_mode);
    if(rslt < 0)
    {
        cout << "ImageBlendMode Error: " << SDL_GetError() << endl;
        return rslt;
    }
    return blend_mode;
}

int rc_media_setImageColorMod_hw(int slot, Uint32 c)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "SetImageColorMod Error: Image Slot must be in the range of 0 to " << MAX_IMAGES-1 << endl;
        return -1;
    }
    if(rc_himage[slot][rc_active_window]==NULL)
    {
        cout << "SetImageColorMod Error: Image Slot is empty" << endl;
        return -1;
    }
    int rslt = -1;

    Uint8 r = c>>16;
    Uint8 g = c>>8;
    Uint8 b = c;

    //cout << "C = " << c << endl;
    //cout << "RGB = " << (Uint32)r << ", " << (Uint32)g << ", " << (Uint32)b << endl;

    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        if(rc_himage[slot][i] != NULL)
        {

            rslt = SDL_SetTextureColorMod(rc_himage[slot][i], r, g, b);
        }
    }
    return rslt;
}

int rc_media_imageColorMod_hw(int slot)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "ImageColorMod Error: Image Slot must be in the range of 0 to " << MAX_IMAGES-1 << endl;
        return -1;
    }
    if(rc_himage[slot][rc_active_window]==NULL)
    {
        cout << "ImageColorMod Error: Image Slot is empty" << endl;
        return -1;
    }

    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    int rslt = SDL_GetTextureColorMod(rc_himage[slot][rc_active_window], &r, &g, &b);

    if(rslt < 0)
    {
        cout << "ImageColorMode Error: " << SDL_GetError() << endl;
        return rslt;
    }

    Uint32 c_mod = (Uint32)SDL_MapRGBA(rc_pformat,r,g,b,255);

    //cout << "-RGB = " << (int)r << ", " << (int)g << ", " << (int)b << endl;

    return c_mod;
}

void rc_media_copyImage_hw(int src_slot, int dst_slot)
{
    //return;
    if(src_slot < 0 || src_slot >= MAX_IMAGES || dst_slot < 0 || dst_slot >= MAX_IMAGES)
    {
        cout << "CopyImage Error: Image Slot should be in the range of 0 to " << MAX_IMAGES-1 << endl;
        return;
    }
    if(rc_himage[src_slot][rc_active_window]!=NULL && rc_himage[dst_slot][rc_active_window]==NULL)
    {
        //rc_simage[dst_slot] = SDL_ConvertSurface(rc_simage[src_slot], rc_simage[src_slot]->format, 0);
        SDL_Surface * tmp_surf = SDL_CreateRGBSurface(0, rc_image_width[src_slot], rc_image_height[src_slot], 32, 0, 0, 0, 0);
        SDL_Texture * tmp_tex = SDL_CreateTexture(rc_win_renderer[rc_active_window], tmp_surf->format->format, SDL_TEXTUREACCESS_TARGET, tmp_surf->w, tmp_surf->h);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], tmp_tex);
        SDL_RendererFlip rf = SDL_FLIP_NONE;
        SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[src_slot][rc_active_window],NULL,NULL,0,NULL,rf);
        SDL_RenderReadPixels(rc_win_renderer[rc_active_window],NULL,tmp_surf->format->format,tmp_surf->pixels,tmp_surf->pitch);
        for(int i = 0; i < MAX_WINDOWS; i++)
        {
            if(rc_himage[dst_slot][i] != NULL)
            {
                //cout << "slot " << dst_slot << "   win " << i << endl;
                SDL_DestroyTexture(rc_himage[dst_slot][i]);
                rc_himage[dst_slot][i] = NULL;
            }
            rc_himage[dst_slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[rc_active_window],tmp_surf);
        }
        rc_image_width[dst_slot] = tmp_surf->w;
        rc_image_height[dst_slot] = tmp_surf->h;
        SDL_FreeSurface(tmp_surf);
        SDL_DestroyTexture(tmp_tex);
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window],rc_hscreen[rc_active_window][rc_active_screen]);
        rc_image_isLoaded[dst_slot] = true;
    }
    else
    {
        cout << "CopyImage Error: Image slot could not be used" << endl;
        return;
    }
}

void rc_media_rotateImage_hw(int slot, int x, int y, double degrees)
{
    //double PI = 3.14159265359;
    //double angle = degrees * PI/180;
    //double theta = SDL_acos(rc_simage[0]->w/2+angle);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = rc_image_width[slot];
    dst.h = rc_image_height[slot];
    SDL_RendererFlip rf = SDL_FLIP_NONE;
    SDL_RenderCopyEx(rc_win_renderer[rc_active_window], rc_himage[slot][rc_active_window], NULL, &dst, degrees, NULL, rf);
}

void rc_media_rotateImageEX_hw(int slot, int x, int y, int src_x, int src_y, int src_w, int src_h, double degrees)
{
    //double PI = 3.14159265359;
    //double angle = degrees * PI/180;
    //double theta = SDL_acos(rc_simage[0]->w/2+angle);
    SDL_RendererFlip rf = SDL_FLIP_NONE;
    SDL_Rect c_rect;
    c_rect.x = src_x;
    c_rect.y = src_y;
    c_rect.w = src_w;
    c_rect.h = src_h;
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = src_w;
    dst.h = src_h;
    SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],&c_rect, &dst,degrees,NULL,rf);
}


void rc_media_zoomImage_hw(int slot, int x, int y, double zoom_x, double zoom_y)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = rc_image_width[slot] * zoom_x;
    dst.h = rc_image_height[slot] * zoom_y;
    SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_himage[slot][rc_active_window], NULL, &dst);
}

void rc_media_zoomImageEX_hw(int slot, int x, int y, int src_x, int src_y, int src_w, int src_h, double zoom_x, double zoom_y)
{
    int zw = src_w * zoom_x;
    int zh = src_h * zoom_y;
    int ax = src_w/2 - zw/2, ay = src_h/2 - zh/2;
    SDL_Rect r;
    r.x = x+ax; r.y = y+ay;
    r.w = zw; r.h = zh;
    SDL_Rect s_rect;
    s_rect.x = src_x;
    s_rect.y = src_y;
    s_rect.w = src_w;
    s_rect.h = src_h;
    SDL_RendererFlip rf = SDL_FLIP_NONE;
    SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],&s_rect,&r,0,NULL,rf);
}

void rc_media_rotozoomImage_hw(int slot, int x, int y, float degrees, float zoom_x, float zoom_y)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = rc_image_width[slot] * zoom_x;
    dst.h = rc_image_height[slot] * zoom_y;
    SDL_RendererFlip rf = SDL_FLIP_NONE;
    SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,&dst,degrees,NULL,rf);
}

void rc_media_rotozoomImageEX_hw(int slot, int x, int y, int src_x, int src_y, int src_w, int src_h, float degrees, float zoom_x, float zoom_y)
{
    //cout << "src w,h = " << src_w << ", " << src_h << endl;
    SDL_Rect src, dst;
    src.x = src_x;
    src.y = src_y;
    src.w = src_w;
    src.h = src_h;
    dst.x = x;
    dst.y = y;
    dst.w = src_w * zoom_x;
    dst.h = src_h * zoom_y;
    SDL_RendererFlip rf = SDL_FLIP_NONE;
    SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],&src,&dst,degrees,NULL,rf);
}

void rc_media_MirrorImage_hw(int slot, Uint8 flipH, Uint8 flipV)
{
    SDL_RendererFlip rf = SDL_FLIP_NONE;
    if(flipH!=0)
        rf = (SDL_RendererFlip)(rf | SDL_FLIP_HORIZONTAL);
    if(flipV!=0)
        rf = (SDL_RendererFlip)(rf | SDL_FLIP_VERTICAL);
    SDL_Surface * m_surf = SDL_CreateRGBSurface(0, rc_image_width[slot], rc_image_height[slot], 32, 0, 0, 0, 0);
    SDL_Texture * m_tex = SDL_CreateTexture(rc_win_renderer[rc_active_window], m_surf->format->format,SDL_TEXTUREACCESS_TARGET,rc_image_width[slot],rc_image_height[slot]);
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window],m_tex);
    SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,NULL,0,NULL,rf);
    SDL_RenderReadPixels(rc_win_renderer[rc_active_window],NULL,m_surf->format->format,m_surf->pixels,m_surf->pitch);
    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        if(rc_win[i]!=NULL)
        {
            SDL_DestroyTexture(rc_himage[slot][i]);
            rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i],m_surf);
        }
    }
    SDL_DestroyTexture(m_tex);
    SDL_FreeSurface(m_surf);
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window],rc_hscreen[rc_active_window][rc_active_screen]);
}

void rc_media_drawImage_hw(int slot, int x, int y)
{
    if(slot >= 0 && slot < MAX_IMAGES)
    {
        if(rc_hscreen[rc_active_window][rc_active_screen] ==  NULL)
        {
            cout << "DrawImage Error: Canvas #" << slot << " does not exist" << endl;
            return;
        }
        SDL_Rect img_pos;
        img_pos.x = x;
        img_pos.y = y;
        img_pos.w = rc_image_width[slot];
        img_pos.h = rc_image_height[slot];

        if(SDL_RenderCopy(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window],NULL,&img_pos) < 0)
            cout << "DrawImage error: " << SDL_GetError() << endl;

    }
}

void rc_media_drawImage_Flip(int slot, int x, int y, int flipH, int flipV)
{
    SDL_RendererFlip rf = SDL_FLIP_NONE;
    if(flipH!=0)
        rf = (SDL_RendererFlip)(rf | SDL_FLIP_HORIZONTAL);
    if(flipV!=0)
        rf = (SDL_RendererFlip)(rf | SDL_FLIP_VERTICAL);

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = rc_image_width[slot];
    dst.h = rc_image_height[slot];

    SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window], NULL, &dst, 0, NULL, rf);
}

void rc_media_drawImage_Flip_Ex(int slot, int x, int y, int src_x, int src_y, int src_w, int src_h, int flipH, int flipV)
{
    SDL_RendererFlip rf = SDL_FLIP_NONE;
    if(flipH!=0)
        rf = (SDL_RendererFlip)(rf | SDL_FLIP_HORIZONTAL);
    if(flipV!=0)
        rf = (SDL_RendererFlip)(rf | SDL_FLIP_VERTICAL);

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = rc_image_width[slot];
    dst.h = rc_image_height[slot];

    SDL_Rect src;
    src.x = src_x;
    src.y = src_y;
    src.w = src_w;
    src.h = src_h;

    SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window], &src, &dst, 0, NULL, rf);
}

void rc_media_drawImage_Clip_hw(int slot, int x, int y, int src_x, int src_y, int src_w, int src_h)
{
    SDL_Rect src, dst;
    src.x = src_x;
    src.y = src_y;
    src.w = src_w;
    src.h = src_h;
    dst.x = x;
    dst.y = y;
    dst.w = src_w;
    dst.h = src_h;
    SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_himage[slot][rc_active_window], &src, &dst);
}

void rc_media_drawImage_Blit_hw(int slot, int screen_x, int screen_y, int scale_w, int scale_h, int src_x, int src_y, int src_w, int src_h)
{
    SDL_Rect src, dst;
    src.x = src_x;
    src.y = src_y;
    src.w = src_w;
    src.h = src_h;
    dst.x = screen_x;
    dst.y = screen_y;
    dst.w = scale_w;
    dst.h = scale_h;
    SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_himage[slot][rc_active_window], &src, &dst);
}

void rc_media_drawImage_Transform(int slot, int x, int y, int w, int h, int src_x, int src_y, int src_w, int src_h, double angle, int center_x, int center_y, int flipH, int flipV)
{
    SDL_RendererFlip rf = SDL_FLIP_NONE;
    if(flipH!=0)
        rf = (SDL_RendererFlip)(rf | SDL_FLIP_HORIZONTAL);
    if(flipV!=0)
        rf = (SDL_RendererFlip)(rf | SDL_FLIP_VERTICAL);

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w;
    dst.h = h;

    SDL_Rect src;
    src.x = src_x;
    src.y = src_y;
    src.w = src_w;
    src.h = src_h;

    SDL_Point center;
    center.x = center_x;
    center.y = center_y;

    SDL_RenderCopyEx(rc_win_renderer[rc_active_window],rc_himage[slot][rc_active_window], &src, &dst, angle, &center, rf);
}

void rc_media_getCursor(double * x, double * y)
{
    *x = rc_sConsole_x[rc_active_window];
    *y = rc_sConsole_y[rc_active_window];
}

void rc_media_showCursor()
{
    rc_cursor_visible = 1;
}

void rc_media_hideCursor()
{
    rc_cursor_visible = 0;
}

void rc_media_locate(int x, int y)
{
    rc_sConsole_x[rc_active_window] = x;
    rc_sConsole_y[rc_active_window] = y;
}

string rc_fillSpace(int n)
{
    string s = "";
    for(int i = 0; i < n; i++)
        s.append(" ");
    return s;
}

void rc_append_sConsole(string txt)
{
    string tc = txt;
    string t_out[rc_console_height[rc_active_window]];

    int i = 0;

    if(rc_sConsole_x[rc_active_window] >= rc_console_width[rc_active_window])
        rc_sConsole_x[rc_active_window] = 0;

    while(tc.compare("")!=0)
    {
        if(tc.substr(i).length() > ( rc_console_width[rc_active_window] - rc_sConsole_x[rc_active_window]) )
        {
            t_out[i] = rc_fillSpace(rc_sConsole_x[rc_active_window]) + tc.substr(i, rc_console_width[rc_active_window] - rc_sConsole_x[rc_active_window]);
            rc_sConsole_x[rc_active_window] = 0;
            tc = tc.substr( (rc_console_width[rc_active_window] - rc_sConsole_x[rc_active_window]) );
            i++;
        }
        else
        {
            t_out[i] = rc_fillSpace(rc_sConsole_x[rc_active_window]) + tc;
            rc_sConsole_x[rc_active_window] = 0;
            i++;
            break;
        }
    }

    rc_sConsole_y[rc_active_window] += i;
}

#ifdef RC_MOBILE
void rc_media_cls()
{
    if(rc_winCheck(rc_active_window))
    {
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_backBuffer[rc_active_window]);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor>>16, rc_clearColor>>8, rc_clearColor, rc_clearColor>>24);
        SDL_RenderClear(rc_win_renderer[rc_active_window]);

        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], 0, 0, 0, 0);
        SDL_RenderClear(rc_win_renderer[rc_active_window]);

        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor>>16, rc_clearColor>>8, rc_clearColor, rc_clearColor>>24);
        SDL_RenderClear(rc_win_renderer[rc_active_window]);

        if(rc_active_screen >= 0)
            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
        rc_media_ink(rc_ink);
    }
}

void rc_media_printS_hw(string txt)
{
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);

    string tc = txt;
    string t_out[rc_console_height[rc_active_window]];

    int i = 0;

    if(rc_sConsole_x[rc_active_window] >= rc_console_width[rc_active_window])
        rc_sConsole_x[rc_active_window] = 0;

    while(tc.compare("")!=0)
    {
        if(tc.substr(i).length() > ( rc_console_width[rc_active_window] - rc_sConsole_x[rc_active_window]) )
        {
            t_out[i] = rc_fillSpace(rc_sConsole_x[rc_active_window]) + tc.substr(i, rc_console_width[rc_active_window] - rc_sConsole_x[rc_active_window]);
            rc_sConsole_x[rc_active_window] = 0;
            tc = tc.substr( (rc_console_width[rc_active_window] - rc_sConsole_x[rc_active_window]) );
            i++;
        }
        else
        {
            t_out[i] = rc_fillSpace(rc_sConsole_x[rc_active_window]) + tc;
            rc_sConsole_x[rc_active_window] = 0;
            i++;
            break;
        }
    }

    for(int n = 0; n < i; n++)
        stringRGBA(rc_win_renderer[rc_active_window], 0, (rc_sConsole_y[rc_active_window] + n) * 8, t_out[n].c_str(), rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);

    rc_sConsole_y[rc_active_window] += i;

    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
    SDL_RenderCopy(rc_win_renderer[rc_active_window],rc_hconsole[rc_active_window],NULL,NULL);

    SDL_RenderPresent(rc_win_renderer[rc_active_window]);

    if(rc_active_screen >= 0)
    	SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
    return;
}

string rc_media_inputS_hw(string prompt)
{
    SDL_Surface * input_surface = NULL;
    SDL_Texture * input_texture = NULL;
    bool loop = true;
    SDL_Event in_evt;
    string in_buf = prompt;
    string rtn_string = "";
    string tc = in_buf;
    string t_out[rc_console_height[rc_active_window]];
    int i = 0;
    SDL_Rect first_line, sub_line;
    first_line.x = (rc_sConsole_x[rc_active_window] * 8) + (prompt.length()*8);
    first_line.y = rc_sConsole_y[rc_active_window] * 8;
    first_line.w = 0;
    first_line.h = 8;
    sub_line.x = 0;
    sub_line.y = (rc_sConsole_y[rc_active_window]+1) * 8;
    sub_line.w = 0;
    sub_line.h = 8;
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);
    SDL_Rect txt_rect;
    txt_rect = first_line;
    txt_rect.w = 128;
    txt_rect.h = 128;
    //SDL_SetTextInputRect(&txt_rect);

    SDL_StartTextInput();

    while(loop)
    {
        while(SDL_PollEvent(&in_evt))
        {
            switch(in_evt.type)
            {
                case SDL_TEXTINPUT:
                    in_buf += in_evt.text.text;
                    break;
                case SDL_KEYDOWN:
                    switch(in_evt.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            loop = false;
                            break;
                        case SDLK_BACKSPACE:
                            if(in_buf.length()-1 >= prompt.length() && in_buf.length()-1 >= 0)
                                in_buf = in_buf.substr(0, in_buf.length()-1);
                            break;
                    }
            }
        }
        if(in_buf.length()>0)
        {
        	SDL_SetRenderTarget(rc_win_renderer[rc_active_window],rc_hconsole[rc_active_window]);
            tc = in_buf;
            i = 0;
            int x = rc_sConsole_x[rc_active_window];
            if(x >= rc_console_width[rc_active_window])
                x = 0;

            while(tc.compare("")!=0)
            {
                if(tc.length() > ( rc_console_width[rc_active_window] - x) )
                {
                    t_out[i] = rc_fillSpace(x) + tc.substr(0, rc_console_width[rc_active_window] - x);
                    if(i == 0 && ((t_out[i].length() - prompt.length() - x)*8) > first_line.w)
                    {
                        first_line.w = (t_out[i].length() - prompt.length() - x) * 8;
                    }
                    else if(i != 0 && (t_out[i].length() * 8) > sub_line.w)
                    {
                        sub_line.w = t_out[i].length() * 8;
                    }
                    tc = tc.substr( (rc_console_width[rc_active_window] - x) );
                    x = 0;
                    i++;
                }
                else
                {
                    t_out[i] = rc_fillSpace(x) + tc;
                    if(i == 0 && ((t_out[i].length() - prompt.length() - x)*8) > first_line.w)
                    {
                        first_line.w = (t_out[i].length() - prompt.length() - x) * 8;
                    }
                    else if(i != 0 && (t_out[i].length() * 8) > sub_line.w)
                    {
                        sub_line.w = t_out[i].length() * 8;
                    }
                    x = 0;
                    i++;
                    break;
                }
                if(i >= rc_console_height[rc_active_window])
                    break;
            }

            SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor>>16, rc_clearColor>>8, rc_clearColor, 255);
            SDL_RenderFillRect(rc_win_renderer[rc_active_window], &first_line);

            if(((i-1)*8) > sub_line.h)
                sub_line.h = i*8;

            if(sub_line.h > 0)
                SDL_RenderFillRect(rc_win_renderer[rc_active_window], &sub_line);

            SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);

            for(int n = 0; n < i; n++)
            {
                stringRGBA(rc_win_renderer[rc_active_window], 0, (rc_sConsole_y[rc_active_window] + n) * 8, t_out[n].c_str(), rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, 255);//rc_ink_color.a);
            }
            SDL_SetRenderTarget(rc_win_renderer[rc_active_window],NULL);
            SDL_RenderCopy(rc_win_renderer[rc_active_window],rc_hconsole[rc_active_window],NULL,NULL);
            SDL_RenderPresent(rc_win_renderer[rc_active_window]);
        }
    }
    SDL_StopTextInput();
    rc_sConsole_y[rc_active_window] += i;
    rc_sConsole_x[rc_active_window] = 0;
    if(rc_active_screen >= 0)
    	SDL_SetRenderTarget(rc_win_renderer[rc_active_window],rc_hscreen[rc_active_window][rc_active_screen]);
    return in_buf.substr(prompt.length());
}

string rc_media_ZoneInputS_hw(int x, int y, int w, int h)
{
    SDL_Surface * input_surface = NULL;
    SDL_Texture * input_texture = NULL;
    bool loop = true;
    SDL_Event in_evt;
    string in_buf = "";
    string rtn_string = "";
    string tc = "";
    string t_out[rc_console_height[rc_active_window]];
    int i = 0;
    SDL_Rect zone;
    zone.x = x;
    zone.y = y;
    zone.w = w;
    zone.h = h;
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);
    SDL_StartTextInput();
    while(loop)
    {
        if(SDL_PollEvent(&in_evt))
        {
            switch(in_evt.type)
            {
                case SDL_TEXTINPUT:
                    in_buf += in_evt.text.text;
                    break;
                case SDL_KEYDOWN:
                    switch(in_evt.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            loop = false;
                            break;
                        case SDLK_BACKSPACE:
                            if(in_buf.length()-1 >= 0)
                                in_buf = in_buf.substr(0, in_buf.length()-1);
                            break;
                    }
            }
        }
        if(in_buf.length()>=0)
        {
            tc = in_buf;
            i = 0;

            while(tc.compare("")!=0)
            {
                if(tc.length() > (w/8) )
                {
                    t_out[i] = tc.substr(0, (w/8) );
                    tc = tc.substr( w/8 );
                    i++;
                }
                else
                {
                    t_out[i] = tc;
                    i++;
                    break;
                }

                if(i >= rc_console_height[rc_active_window])
                    break;
            }

            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);
            SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor>>16, rc_clearColor>>8, rc_clearColor, rc_clearColor>>24);
            SDL_RenderFillRect(rc_win_renderer[rc_active_window], &zone);

            //cout << "zone txt color = " << (int)rc_ink_color.r << ", " << (int)rc_ink_color.g << ", " << (int)rc_ink_color.b << ", " << (int)rc_ink_color.a << endl;

            SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);

            //cout << "n < " << (int) (h/8) << endl;

            for(int n = 0; n < (h/8) && n < i; n++)
            {
                stringRGBA(rc_win_renderer[rc_active_window], x, y + (n * 8), t_out[n].c_str(), rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
            }

            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
            SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window], NULL, NULL);
            SDL_RenderPresent(rc_win_renderer[rc_active_window]);
        }
    }
    SDL_StopTextInput();
    if(rc_active_screen >= 0)
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window],rc_hscreen[rc_active_window][rc_active_screen]);
    return in_buf;
}
#else

void rc_media_cls()
{
    if(rc_winCheck(rc_active_window))
    {
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], 0, 0, 0, 0);
        SDL_RenderClear(rc_win_renderer[rc_active_window]);

        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor>>16, rc_clearColor>>8, rc_clearColor, rc_clearColor>>24);
        SDL_RenderClear(rc_win_renderer[rc_active_window]);

        if(rc_active_screen >= 0)
            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
        rc_media_ink(rc_ink);
    }
}

void rc_media_printS_hw(string txt)
{
    if(rc_active_window < 0)
        return;

    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);

    string tc = txt;
    string t_out[rc_console_height[rc_active_window]];

    int i = 0;

    if(rc_sConsole_x[rc_active_window] >= rc_console_width[rc_active_window])
        rc_sConsole_x[rc_active_window] = 0;

    while(tc.compare("")!=0)
    {
        if(tc.substr(i).length() > ( rc_console_width[rc_active_window] - rc_sConsole_x[rc_active_window]) )
        {
            t_out[i] = rc_fillSpace(rc_sConsole_x[rc_active_window]) + tc.substr(i, rc_console_width[rc_active_window] - rc_sConsole_x[rc_active_window]);
            rc_sConsole_x[rc_active_window] = 0;
            tc = tc.substr( (rc_console_width[rc_active_window] - rc_sConsole_x[rc_active_window]) );
            i++;
        }
        else
        {
            t_out[i] = rc_fillSpace(rc_sConsole_x[rc_active_window]) + tc;
            rc_sConsole_x[rc_active_window] = 0;
            i++;
            break;
        }
    }

    for(int n = 0; n < i; n++)
        stringRGBA(rc_win_renderer[rc_active_window], 0, (rc_sConsole_y[rc_active_window] + n) * 8, t_out[n].c_str(), rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);

    rc_sConsole_y[rc_active_window] += i;

    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
    SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window], NULL, NULL);

    SDL_RenderPresent(rc_win_renderer[rc_active_window]);
    if(rc_active_screen>=0)
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
    return;
}

string rc_media_inputS_hw(string prompt)
{
    //SDL_Surface * input_surface = NULL;
    //SDL_Texture * input_texture = NULL;
    bool loop = true;
    SDL_Event in_evt;
    string in_buf = prompt;
    string rtn_string = "";
    string tc = in_buf;
    string t_out[rc_console_height[rc_active_window]];
    int i = 0;
    SDL_Rect first_line, sub_line;
    first_line.x = (rc_sConsole_x[rc_active_window] * 8) + (prompt.length()*8);
    first_line.y = rc_sConsole_y[rc_active_window] * 8;
    first_line.w = 0;
    first_line.h = 8;
    sub_line.x = 0;
    sub_line.y = (rc_sConsole_y[rc_active_window]+1) * 8;
    sub_line.w = 0;
    sub_line.h = 8;
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);

    if(in_buf.length()>0)
    {
        tc = in_buf;
        i = 0;
        int x = rc_sConsole_x[rc_active_window];
        if(x >= rc_console_width[rc_active_window])
            x = 0;

        while(tc.compare("")!=0)
        {
            if(tc.length() > ( rc_console_width[rc_active_window] - x) )
            {
                t_out[i] = rc_fillSpace(x) + tc.substr(0, rc_console_width[rc_active_window] - x);
                if(i == 0 && ((t_out[i].length() - prompt.length() - x)*8) > first_line.w)
                {
                    first_line.w = (t_out[i].length() - prompt.length() - x) * 8;
                }
                else if(i != 0 && (t_out[i].length() * 8) > sub_line.w)
                {
                    sub_line.w = t_out[i].length() * 8;
                }
                tc = tc.substr( (rc_console_width[rc_active_window] - x) );
                x = 0;
                i++;
            }
            else
            {
                t_out[i] = rc_fillSpace(x) + tc;
                if(i == 0 && ((t_out[i].length() - prompt.length() - x)*8) > first_line.w)
                {
                    first_line.w = (t_out[i].length() - prompt.length() - x) * 8;
                }
                else if(i != 0 && (t_out[i].length() * 8) > sub_line.w)
                {
                    sub_line.w = t_out[i].length() * 8;
                }
                x = 0;
                i++;
                break;
            }
            if(i >= rc_console_height[rc_active_window])
                break;
        }

        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor>>16, rc_clearColor>>8, rc_clearColor, rc_clearColor>>24);
        SDL_RenderFillRect(rc_win_renderer[rc_active_window], &first_line);

        if(((i-1)*8) > sub_line.h)
            sub_line.h = i*8;

        if(sub_line.h > 0)
            SDL_RenderFillRect(rc_win_renderer[rc_active_window], &sub_line);

        SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);

        for(int n = 0; n < i; n++)
        {
            stringRGBA(rc_win_renderer[rc_active_window], 0, (rc_sConsole_y[rc_active_window] + n) * 8, t_out[n].c_str(), rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
        }
        SDL_RenderPresent(rc_win_renderer[rc_active_window]);
    }

    while(loop)
    {
        if(SDL_WaitEvent(&in_evt))
        {
            switch(in_evt.type)
            {
                case SDL_TEXTINPUT:
                    in_buf += in_evt.text.text;
                    break;
                case SDL_KEYDOWN:
                    switch(in_evt.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            loop = false;
                            break;
                        case SDLK_BACKSPACE:
                            if(in_buf.length()-1 >= prompt.length() && in_buf.length()-1 >= 0)
                                in_buf = in_buf.substr(0, in_buf.length()-1);
                            break;
                    }
            }
        }
        if(in_buf.length()>0)
        {
            tc = in_buf;
            i = 0;
            int x = rc_sConsole_x[rc_active_window];
            if(x >= rc_console_width[rc_active_window])
                x = 0;

            while(tc.compare("")!=0)
            {
                if(tc.length() > ( rc_console_width[rc_active_window] - x) )
                {
                    t_out[i] = rc_fillSpace(x) + tc.substr(0, rc_console_width[rc_active_window] - x);
                    if(i == 0 && ((t_out[i].length() - prompt.length() - x)*8) > first_line.w)
                    {
                        first_line.w = (t_out[i].length() - prompt.length() - x) * 8;
                    }
                    else if(i != 0 && (t_out[i].length() * 8) > sub_line.w)
                    {
                        sub_line.w = t_out[i].length() * 8;
                    }
                    tc = tc.substr( (rc_console_width[rc_active_window] - x) );
                    x = 0;
                    i++;
                }
                else
                {
                    t_out[i] = rc_fillSpace(x) + tc;
                    if(i == 0 && ((t_out[i].length() - prompt.length() - x)*8) > first_line.w)
                    {
                        first_line.w = (t_out[i].length() - prompt.length() - x) * 8;
                    }
                    else if(i != 0 && (t_out[i].length() * 8) > sub_line.w)
                    {
                        sub_line.w = t_out[i].length() * 8;
                    }
                    x = 0;
                    i++;
                    break;
                }
                if(i >= rc_console_height[rc_active_window])
                    break;
            }

            SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor>>16, rc_clearColor>>8, rc_clearColor, rc_clearColor>>24);
            SDL_RenderFillRect(rc_win_renderer[rc_active_window], &first_line);

            if(((i-1)*8) > sub_line.h)
                sub_line.h = i*8;

            if(sub_line.h > 0)
                SDL_RenderFillRect(rc_win_renderer[rc_active_window], &sub_line);

            SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);

            for(int n = 0; n < i; n++)
            {
                stringRGBA(rc_win_renderer[rc_active_window], 0, (rc_sConsole_y[rc_active_window] + n) * 8, t_out[n].c_str(), rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
            }

            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
            SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window], NULL, NULL);

            SDL_RenderPresent(rc_win_renderer[rc_active_window]);

            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);
        }
    }
    rc_sConsole_y[rc_active_window] += i;
    rc_sConsole_x[rc_active_window] = 0;
    if(rc_active_screen >= 0)
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window],rc_hscreen[rc_active_window][rc_active_screen]);
    return in_buf.substr(prompt.length());
}

string rc_media_ZoneInputS_hw(int x, int y, int w, int h)
{
    //SDL_Surface * input_surface = NULL;
    //SDL_Texture * input_texture = NULL;
    bool loop = true;
    SDL_Event in_evt;
    string in_buf = "";
    string rtn_string = "";
    string tc = "";
    string t_out[rc_console_height[rc_active_window]];
    int i = 0;
    SDL_Rect zone;
    zone.x = x;
    zone.y = y;
    zone.w = w;
    zone.h = h;
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);
    while(loop)
    {
        if(SDL_WaitEvent(&in_evt))
        {
            switch(in_evt.type)
            {
                case SDL_TEXTINPUT:
                    in_buf += in_evt.text.text;
                    break;
                case SDL_KEYDOWN:
                    switch(in_evt.key.keysym.sym)
                    {
                        case SDLK_RETURN:
                            loop = false;
                            break;
                        case SDLK_BACKSPACE:
                            if(in_buf.length()-1 >= 0)
                                in_buf = in_buf.substr(0, in_buf.length()-1);
                            break;
                    }
            }
        }
        if(in_buf.length()>=0)
        {
            tc = in_buf;
            i = 0;

            while(tc.compare("")!=0)
            {
                if(tc.length() > (w/8) )
                {
                    t_out[i] = tc.substr(0, (w/8) );
                    tc = tc.substr( w/8 );
                    i++;
                }
                else
                {
                    t_out[i] = tc;
                    i++;
                    break;
                }

                if(i >= rc_console_height[rc_active_window])
                    break;
            }

            SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor>>16, rc_clearColor>>8, rc_clearColor, rc_clearColor>>24);
            SDL_RenderFillRect(rc_win_renderer[rc_active_window], &zone);

            //cout << "zone txt color = " << (int)rc_ink_color.r << ", " << (int)rc_ink_color.g << ", " << (int)rc_ink_color.b << ", " << (int)rc_ink_color.a << endl;

            SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);

            //cout << "n < " << (int) (h/8) << endl;

            for(int n = 0; n < (h/8) && n < i; n++)
            {
                stringRGBA(rc_win_renderer[rc_active_window], x, y + (n * 8), t_out[n].c_str(), rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);
            }

            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
            SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window], NULL, NULL);

            SDL_RenderPresent(rc_win_renderer[rc_active_window]);

            SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window]);
        }
    }
    if(rc_active_screen >= 0)
        SDL_SetRenderTarget(rc_win_renderer[rc_active_window],rc_hscreen[rc_active_window][rc_active_screen]);
    return in_buf;
}

#endif // RC_MOBILE

bool rc_media_fontIsLoaded(int slot)
{
    if(rc_draw_font[slot]!=NULL)
        return true;
    return false;
}

void rc_media_font(int slot)
{
    if(rc_draw_font[slot]!= NULL)
        rc_active_font = slot;
}

void rc_media_setFontStyle(int f_slot, int style)
{
    TTF_SetFontStyle(rc_draw_font[f_slot], style);
}

void rc_media_LoadFont(int slot, string font_path, int font_size)
{
    if(rc_draw_font[slot] != NULL)
        TTF_CloseFont(rc_draw_font[slot]);
    rc_draw_font[slot] = TTF_OpenFont(font_path.c_str(), font_size);
    if(rc_active_font == -1)
        rc_active_font = slot;
}

void rc_media_DeleteFont(int slot)
{
    if(rc_draw_font[slot] != NULL)
        TTF_CloseFont(rc_draw_font[slot]);
    rc_draw_font[slot] = NULL;
}

void rc_media_drawText_hw(string text, int x, int y)
{
    if(rc_draw_font[rc_active_font] == NULL)
    {
        cout << "DrawTextError: Could not load font at " << rc_active_font << endl;
        return;
    }
    SDL_Surface * rendered_text = TTF_RenderText_Solid(rc_draw_font[rc_active_font], text.c_str(), rc_ink_color);
    //cout << "debug 1\n";
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = rendered_text->w;
    pos.h = rendered_text->h;
    SDL_Texture * txt_image = SDL_CreateTextureFromSurface(rc_win_renderer[rc_active_window],rendered_text);
    //SDL_BlitSurface(rendered_text, NULL, rc_sscreen[rc_active_window][rc_active_screen], &pos);
    SDL_FreeSurface(rendered_text);
    SDL_RenderCopy(rc_win_renderer[rc_active_window],txt_image,NULL,&pos);
    SDL_DestroyTexture(txt_image);
}

void rc_media_drawText_shaded_hw(string text, int x, int y, Uint32 fg_color, Uint32 bg_color)
{
    if(rc_draw_font[rc_active_font] == NULL)
    {
        cout << "DrawTextError: Could not load font at " << rc_active_font << endl;
        return;
    }
    SDL_Color fg, bg;
    fg.a = fg_color >> 24;
    fg.r = fg_color >> 16;
    fg.g = fg_color >> 8;
    fg.b = fg_color;
    bg.a = bg_color >> 24;
    bg.r = bg_color >> 16;
    bg.g = bg_color >> 8;
    bg.b = bg_color;
    SDL_Surface * rendered_text = TTF_RenderText_Shaded(rc_draw_font[rc_active_font], text.c_str(), fg, bg);
    //cout << "debug 1\n";
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = rendered_text->w;
    pos.h = rendered_text->h;
    SDL_Texture * txt_image = SDL_CreateTextureFromSurface(rc_win_renderer[rc_active_window],rendered_text);
    //SDL_BlitSurface(rendered_text, NULL, rc_sscreen[rc_active_window][rc_active_screen], &pos);
    SDL_FreeSurface(rendered_text);
    SDL_RenderCopy(rc_win_renderer[rc_active_window],txt_image,NULL,&pos);
    SDL_DestroyTexture(txt_image);
}

void rc_media_drawText_blended_hw(string text, int x, int y)
{
    if(rc_draw_font[rc_active_font] == NULL)
    {
        cout << "DrawTextError: Could not load font at " << rc_active_font << endl;
        return;
    }
    SDL_Surface * rendered_text = TTF_RenderText_Blended(rc_draw_font[rc_active_font], text.c_str(), rc_ink_color);
    //cout << "debug 1\n";
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = rendered_text->w;
    pos.h = rendered_text->h;
    SDL_Texture * txt_image = SDL_CreateTextureFromSurface(rc_win_renderer[rc_active_window],rendered_text);
    //SDL_BlitSurface(rendered_text, NULL, rc_sscreen[rc_active_window][rc_active_screen], &pos);
    SDL_FreeSurface(rendered_text);
    SDL_RenderCopy(rc_win_renderer[rc_active_window],txt_image,NULL,&pos);
    SDL_DestroyTexture(txt_image);
}

void rc_media_getTextSize(int f_slot, string txt, double * w, double * h)
{
    if(rc_draw_font[f_slot] == NULL)
    {
        cout << "GetTextSize Error: No font at " << f_slot << endl;
        return;
    }
    int txt_w = 0, txt_h = 0;
    TTF_SizeText(rc_draw_font[f_slot], txt.c_str(), &txt_w, &txt_h);
    *w = txt_w;
    *h = txt_h;
}

void rc_media_GetRenderedText_hw(int slot, string text)
{
    if(slot < 0 || slot >= MAX_IMAGES)
    {
        cout << "GetRenderedText Error: Image must be in the range of 0 to " << MAX_IMAGES-1 << endl;
        return;
    }
    if(rc_draw_font[rc_active_font] == NULL)
    {
        cout << "GetRenderedText Error: Could not load font at " << rc_active_font << endl;
        return;
    }
    SDL_Surface * rendered_text = TTF_RenderText_Solid(rc_draw_font[rc_active_font], text.c_str(), rc_ink_color);

    for(int i = 0; i < MAX_WINDOWS; i++)
    {
        if(rc_himage[slot][i] != NULL)
        {
            SDL_DestroyTexture(rc_himage[slot][i]);
            rc_himage[slot][i] = NULL;
        }
        if(rc_win[i] != NULL)
        {
            rc_himage[slot][i] = SDL_CreateTextureFromSurface(rc_win_renderer[i], rendered_text);
            rc_himage_rect[slot].x = 0;
            rc_himage_rect[slot].y = 0;
            rc_himage_rect[slot].w = rendered_text->w;
            rc_himage_rect[slot].h = rendered_text->h;
            rc_image_width[slot] = rendered_text->w;
            rc_image_height[slot] = rendered_text->h;
            rc_image_isLoaded[slot] = true;
        }
    }

    SDL_FreeSurface(rendered_text);
}

int rc_getEvents()
{
    SDL_Event event;
    int g_events = SDL_PollEvent(&event);
    //int g_events = SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
            SDL_PumpEvents();
            //rc_media_quit();
            exit(0);
            break;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                for(int i = 0; i < MAX_WINDOWS; i++)
                {
                    if(rc_win_id[i] == event.window.windowID)
                    {
                        rc_active_window = i;
                        rc_win_event[i] = 4;
                        rc_onResize(rc_active_window);
                        break;
                    }
                }
            }
            else if(event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                Uint32 win_id = -1;
                for(int i = 0; i < MAX_WINDOWS; i++)
                {
                    if(rc_win[i])
                    {
                        win_id = SDL_GetWindowID(rc_win[i]);
                        if(win_id == event.window.windowID)
                        {
                            rc_win_event[i] = 1;
                            if(SDL_QuitRequested() != 0)
                            {
                                //SDL_PumpEvents();
                                SDL_FlushEvent(SDL_QUIT);
                            }
                            if(rc_win_exitOnClose[i])
                            {
                                rc_media_closeWindow_hw(i);
                                return 0;
                                //rc_win_event[i] = 0;
                            }
                            break;
                        }
                        win_id = -1;
                    }
                }
            }
            else if(event.window.event == SDL_WINDOWEVENT_MINIMIZED)
            {
                Uint32 win_id = -1;
                for(int i = 0; i < MAX_WINDOWS; i++)
                {
                    if(rc_win[i])
                    {
                        win_id = SDL_GetWindowID(rc_win[i]);
                        if(win_id == event.window.windowID)
                        {
                            rc_win_event[i] = 2;
                            //rc_media_closeWindow_hw(i);
                            break;
                        }
                        win_id = -1;
                    }
                }
            }
            else if(event.window.event == SDL_WINDOWEVENT_MAXIMIZED)
            {
                Uint32 win_id = -1;
                for(int i = 0; i < MAX_WINDOWS; i++)
                {
                    if(rc_win[i])
                    {
                        win_id = SDL_GetWindowID(rc_win[i]);
                        if(win_id == event.window.windowID)
                        {
                            rc_win_event[i] = 3;

                            //rc_media_closeWindow_hw(i);
                            break;
                        }
                        win_id = -1;
                    }
                }
            }
            break;
        case SDL_TEXTINPUT:
            if(rc_textinput_flag == true)
            {
                rc_textinput_string += event.text.text;
                rc_textinput_flag = true;
                //cout << "TEXT = " << rc_textinput_string << endl;
            }
            rc_textinput_flag = true;
            break;
        case SDL_KEYUP:
            rc_textinput_flag = true;
            break;
        case SDL_KEYDOWN:
            if(rc_textinput_isActive && event.key.keysym.sym == SDLK_BACKSPACE && rc_textinput_string.length() > 0
               && !rc_textinput_flag && rc_toggleBackspace)
            {
                rc_textinput_string = rc_textinput_string.substr(0, rc_textinput_string.length()-1);
                //rc_textinput_timer = clock() / (double)(CLOCKS_PER_SEC / 1000);
                rc_textinput_hold = false;
                rc_textinput_flag = true;
            }

            rc_inkey = event.key.keysym.sym;
            break;
        //case SDL_MOUSEMOTION:
            //SDL_GetMouseState(&rc_mouseX, &rc_mouseY);
            //break;
        case SDL_MOUSEBUTTONUP:
            //SDL_GetMouseState(&rc_mouseX, &rc_mouseY);
            rc_mbutton1 = 0;
            rc_mbutton2 = 0;
            rc_mbutton3 = 0;
            //break;
            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT:
                    rc_mbutton1 = 0;
                    break;
                case SDL_BUTTON_MIDDLE:
                    rc_mbutton2 = 0;
                    break;
                case SDL_BUTTON_RIGHT:
                    rc_mbutton3 = 0;
                    break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            //SDL_GetMouseState(&rc_mouseX, &rc_mouseY);
            //rc_mbutton1 = 0;
            //rc_mbutton2 = 0;
            //rc_mbutton3 = 0;
            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT:
                    rc_mbutton1 = 1;
                    break;
                case SDL_BUTTON_MIDDLE:
                    rc_mbutton2 = 1;
                    break;
                case SDL_BUTTON_RIGHT:
                    rc_mbutton3 = 1;
                    break;
            }
            break;
        case SDL_MOUSEWHEEL:
            rc_mwheelx = event.wheel.x;
            rc_mwheely = event.wheel.y;
            break;
//        case SDL_JOYBUTTONDOWN:
//            rc_joybutton[event.jbutton.which][event.jbutton.button] = 1;
//            break;
//        case SDL_JOYBUTTONUP:
//            rc_joybutton[event.jbutton.which][event.jbutton.button] = 0;
//            break;
//        case SDL_JOYAXISMOTION:
//            rc_joy_axis[event.jaxis.which][event.jaxis.axis] = event.jaxis.value;
//            break;
        case SDL_JOYDEVICEREMOVED:
            //cout << "Joystick Removed: Instance " << event.jdevice.which << endl;
            for(int i = 0; i < 8; i++)
            {
                if(event.jdevice.which == rc_joyID[i] && rc_joystick[i])
                {
                    //cout << "Joystick [" << i << "] was removed" << endl;
                    SDL_HapticClose(rc_haptic[i]);
                    SDL_JoystickClose(rc_joystick[i]);
                    rc_joystick[i] = NULL;
                    rc_haptic[i] = NULL;
                    rc_joyID[i] = -1;
                    rc_numJoysticks--;
                    break;
                }
            }
            break;
        case SDL_JOYDEVICEADDED:
            //cout << "Joystick Added: " << event.jdevice.which << endl;
            tmp_joy = SDL_JoystickOpen(event.jdevice.which);
            tmp_joy_id = SDL_JoystickInstanceID(tmp_joy);
            tmp_joy_flag = 0;

            for(int i = 0; i < 8; i++)
            {
                if(tmp_joy_id == rc_joyID[i])
                {
                    tmp_joy_flag = 1;
                    break;
                }
            }

            if(event.jdevice.which >= 0 && tmp_joy_flag == 0)
            {
                for(int i = 0; i < 8; i++)
                {
                    if(rc_joystick[i] == NULL)
                    {
                        //cout << "Assigned " << i << endl;
                        rc_joystick[i] = tmp_joy;
                        rc_haptic[i] = SDL_HapticOpenFromJoystick(rc_joystick[i]);
                        SDL_HapticRumbleInit(rc_haptic[i]);
                        rc_joyID[i] = tmp_joy_id;
                        rc_numJoysticks++;
                        break;
                    }
                }
            }
            break;
#ifndef RC_MOBILE
        case SDL_FINGERDOWN:
            rc_touch = 1;
            rc_touchX = event.tfinger.x * rc_win_width[rc_active_window];
            rc_touchY = event.tfinger.y * rc_win_height[rc_active_window];
#ifdef RC_IOS
            rc_pressure = 1; //FIXME: On IOS pressure is always getting reported as 0 on finger down so I am just setting it to 1 until I figure this out
#else
            rc_pressure = event.tfinger.pressure;
#endif
            rc_setTouchFingerEvent(event.tfinger.fingerId, rc_touchX, rc_touchY, rc_pressure);
            break;
        case SDL_FINGERUP:
            rc_touch = 0;
            rc_mt_status = 0;
            rc_touchX = event.tfinger.x * rc_win_width[rc_active_window];
            rc_touchY = event.tfinger.y * rc_win_height[rc_active_window];
            rc_pressure = event.tfinger.pressure;
            rc_setTouchFingerEvent(event.tfinger.fingerId, -1, -1, 0);
            break;
        case SDL_FINGERMOTION:
            rc_touch = 1;
            rc_touchX = event.tfinger.x * rc_win_width[rc_active_window];
            rc_touchY = event.tfinger.y * rc_win_height[rc_active_window];
            rc_motionX = event.tfinger.dx * rc_win_width[rc_active_window];
            rc_motionY = event.tfinger.dy * rc_win_height[rc_active_window];
#ifdef RC_IOS
            rc_pressure = 1;
#else
            rc_pressure = event.tfinger.pressure;
#endif
            rc_setTouchFingerEvent(event.tfinger.fingerId, rc_touchX, rc_touchY, rc_pressure);
            break;
        case SDL_MULTIGESTURE:
            rc_touch = 2;
            rc_mt_status = 1;
            rc_mt_x = event.mgesture.x;
            rc_mt_y = event.mgesture.y;
            rc_mt_numFingers = event.mgesture.numFingers;
            rc_mt_dist = event.mgesture.dDist;
            rc_mt_theta = event.mgesture.dTheta;
#ifdef RC_IOS
            rc_pressure = 1;
#else
            rc_pressure = event.tfinger.pressure;
#endif
            break;
#endif
    }
    //cout << "end_event" << endl;
    return g_events;
}

bool rc_media_windowEvent_Close(int win_num)
{
    if(rc_winCheck(win_num))
    {
        if(rc_win_event[win_num]==1)
        {
            //cout << "Window #" << win_num << " Close_Event" << endl;
            return true;
        }
        else
            return false;
    }
    return false;
}

bool rc_media_windowEvent_Minimize(int win_num)
{
    if(rc_winCheck(win_num))
    {
        if(rc_win_event[win_num]==2)
            return true;
        else
            return false;
    }
    return false;
}

bool rc_media_windowEvent_Maximize(int win_num)
{
    if(rc_winCheck(win_num))
    {
        if(rc_win_event[win_num]==3)
            return true;
        else
            return false;
    }
    return false;
}

bool rc_media_windowEvent_Resize(int win_num)
{
    if(rc_winCheck(win_num))
    {
        if(rc_win_event[win_num]==4)
            return true;
        else
            return false;
    }
    return false;
}

void rc_media_windowEvent_setExitOnClose(int win_num, int exitOnClose)
{
    rc_win_exitOnClose[win_num] = (exitOnClose != 0) ? true : false;
}

void rc_media_getTouchFinger(int finger, double * x, double * y, double * pressure)
{
    if(finger < MAX_FINGERS)
    {
        *x = rc_finger[finger].x;
        *y = rc_finger[finger].y;
        *pressure = rc_finger[finger].pressure;
    }
}

int rc_media_numFingers()
{
    return rc_fingers_pressed.size();
    //if(rc_touchDevice)
    //    return SDL_GetNumTouchFingers(rc_touchDevice);
    //return 0;
}

double rc_media_touchPressure()
{
    return rc_pressure;
}

void rc_media_getTouch(double * status, double * x, double * y, double * distX, double * distY)
{
    *status = (double)rc_touch;
    *x = (double)rc_touchX;
    *y = (double)rc_touchY;
    *distX = (double)rc_motionX;
    *distY = (double)rc_motionY;
    return;
}

void rc_media_getMultiTouch(double * status, double * x, double * y, double * numFingers, double * dist, double * theta)
{
    *status = (double)rc_mt_status;
    *x = (double)rc_mt_x;
    *y = (double)rc_mt_y;
    *numFingers = (double)rc_mt_numFingers;
    *dist = rc_mt_dist;
    *theta = rc_mt_theta;
    return;
}

void rc_media_getAccel(uint32_t accel_num, double * x, double * y, double * z)
{
    float sensor_data[4];
    if(accel_num < num_accels)
        SDL_SensorGetData(rc_accel[accel_num], &sensor_data[0], 3);
    *x = sensor_data[0];
    *y = sensor_data[1];
    *z = sensor_data[2];
}

string rc_media_accelName(uint32_t accel_num)
{
    if(accel_num < num_accels)
        return (string)SDL_SensorGetName(rc_accel[accel_num]);
    return "";
}

int rc_media_numAccels()
{
    return num_accels;
}

void rc_media_getGyro(uint32_t gyro_num, double * x, double * y, double * z)
{
    float sensor_data[4];
    if(gyro_num < num_gyros)
        SDL_SensorGetData(rc_gyro[gyro_num], &sensor_data[0], 3);
    *x = sensor_data[0];
    *y = sensor_data[1];
    *z = sensor_data[2];
}

string rc_media_gyroName(uint32_t gyro_num)
{
    if(gyro_num < num_gyros)
        return (string)SDL_SensorGetName(rc_gyro[gyro_num]);
    return "";
}

int rc_media_numGyros()
{
    return num_gyros;
}

void rc_media_ReadInput_Start()
{
    SDL_StartTextInput();
    rc_textinput_isActive = true;
    rc_textinput_string = "";
    rc_textinput_timer = clock() / (double)(CLOCKS_PER_SEC / 1000);
}

void rc_media_ReadInput_Stop()
{
    rc_textinput_isActive = false;
    rc_textinput_timer = 0;
    rc_textinput_string = "";
    SDL_StopTextInput();
}

string rc_media_ReadInput_Text()
{
    return rc_textinput_string;
}

void rc_media_ReadInput_SetText(string txt)
{
    rc_textinput_string = txt;
}

void rc_media_ReadInput_ToggleBackspace(bool flag)
{
    rc_toggleBackspace = flag;
}

int rc_media_inkey()
{
    int k = rc_inkey;
    return k;
}

int rc_media_key(int check_Key)
{
    if(keyState == NULL)
        keyState = SDL_GetKeyboardState(NULL);
    return keyState[SDL_GetScancodeFromKey(check_Key)];
}

int rc_media_waitKey()
{
    bool wk_loop = true;
    SDL_Event e;
    while(wk_loop)
    {
        while(SDL_WaitEvent(&e))
        {
            if(e.type == SDL_KEYDOWN)
                return (int)e.key.keysym.sym;
        }
    }
    return 0;
}

void rc_media_wait(Uint32 ms)
{
    SDL_Delay(ms);
}

void rc_media_hideMouse()
{
    SDL_ShowCursor(0);
    rc_cursor_visible = 0;
}

void rc_media_showMouse()
{
    SDL_ShowCursor(1);
    rc_cursor_visible = 1;
}

bool rc_media_mouseIsVisible()
{
    return rc_cursor_visible;
}

int rc_media_mouseX()
{
    SDL_GetMouseState(&rc_mouseX,&rc_mouseY);
    //cout << "debug: " << rc_fullscreen_mouse_scale_x[rc_active_window] << endl;
    #ifdef RC_MOBILE
    return rc_mouseX;
    #else
    return rc_mouseX * rc_fullscreen_mouse_scale_x[rc_active_window];
    #endif // RC_MOBILE
}

int rc_media_mouseY()
{
    SDL_GetMouseState(&rc_mouseX,&rc_mouseY);
    #ifdef RC_MOBILE
    return rc_mouseY;
    #else
    return rc_mouseY * rc_fullscreen_mouse_scale_y[rc_active_window];
    #endif // RC_MOBILE
}

int rc_media_mouseButton(int m)
{
    switch(m)
    {
        case 0:
            return rc_mbutton1;
        case 1:
            return rc_mbutton2;
        case 2:
            return rc_mbutton3;
    }
    return -1;
}

void rc_media_getMouse(double * x, double * y, double * mb1, double * mb2, double * mb3)
{
    SDL_GetMouseState(&rc_mouseX,&rc_mouseY);
    //SDL_PumpEvents();
    *mb1 = rc_mbutton1;
    *mb2 = rc_mbutton2;
    *mb3 = rc_mbutton3;
    #ifdef RC_MOBILE
    *x = rc_mouseX;
    *y = rc_mouseY;
    #else
    *x = (int)(rc_mouseX * rc_fullscreen_mouse_scale_x[rc_active_window]);
    *y = (int)(rc_mouseY * rc_fullscreen_mouse_scale_y[rc_active_window]);
    //cout << "debug getMouse = " << rc_mouseX << " * " << rc_fullscreen_mouse_scale_x[rc_active_window] << endl;
    #endif // RC_MOBILE
    return;
}

int rc_media_globalMouseX()
{
    SDL_GetGlobalMouseState(&rc_mouseX,&rc_mouseY);
    return rc_mouseX;
}

int rc_media_globalMouseY()
{
    SDL_GetGlobalMouseState(&rc_mouseX,&rc_mouseY);
    return rc_mouseY;
}

void rc_media_getGlobalMouse(double * x, double * y, double * mb1, double * mb2, double * mb3)
{
    SDL_GetGlobalMouseState(&rc_mouseX,&rc_mouseY);
    //SDL_PumpEvents();
    *mb1 = rc_mbutton1;
    *mb2 = rc_mbutton2;
    *mb3 = rc_mbutton3;
    *x = rc_mouseX;
    *y = rc_mouseY;
    return;
}

int rc_media_mouseWheelX()
{
    return rc_mwheelx;
}

int rc_media_mouseWheelY()
{
    return rc_mwheely;
}

void rc_media_getMouseWheel(double * x_axis, double * y_axis)
{
    *x_axis = rc_mwheelx;
    *y_axis = rc_mwheely;
    return;
}

void rc_media_updateWindow_hw()
{
    if(!rc_win[rc_active_window])
        return;
    int s_num = 0;
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_backBuffer[rc_active_window]);
    SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_clearColor >> 16, rc_clearColor >> 8, rc_clearColor, 255);
    //SDL_RenderFillRect(rc_win_renderer[rc_active_window], NULL);
    SDL_RenderClear(rc_win_renderer[rc_active_window]);
    for(int i = MAX_SCREENS-1; i >= 0; i--)
    {
        s_num = rc_screen_zOrder[rc_active_window][i];
        //cout << "DRAW SCREEN: " << s_num << endl;
        if(rc_hscreen[rc_active_window][s_num] != NULL && rc_screen_visible[rc_active_window][s_num])
        {
            //cout << "draw canvas " << s_num << endl;
            #ifdef RC_WEB
            SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][s_num], &rc_screenview[rc_active_window][s_num], &rc_screen_rect[rc_active_window][s_num]);
            #else
            SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][s_num], &rc_screenview[rc_active_window][s_num], &rc_screen_rect[rc_active_window][s_num]);
            #endif
        }
    }
    //#ifndef RC_ANDROID
        SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_hconsole[rc_active_window], NULL, NULL);
    //#endif // RC_ANDROID
    //cout << endl;
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], NULL);
    #if defined(RC_MOBILE) || defined(RC_WEB)
    SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_backBuffer[rc_active_window], NULL, NULL);
    #else
    SDL_RenderCopy(rc_win_renderer[rc_active_window], rc_backBuffer[rc_active_window], &rc_bb_rect[rc_active_window], NULL);
    #endif // RC_ANDROID
    SDL_RenderPresent(rc_win_renderer[rc_active_window]);
    SDL_SetRenderTarget(rc_win_renderer[rc_active_window], rc_hscreen[rc_active_window][rc_active_screen]);
    SDL_SetRenderDrawColor(rc_win_renderer[rc_active_window], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);

    rc_fps_frames[rc_active_window]++;

    uint32_t t = SDL_GetTicks();

    if( (t - rc_fps_timer[rc_active_window]) >= 1000 )
    {
        rc_fps_timer[rc_active_window] = t;
        rc_fps[rc_active_window] = rc_fps_frames[rc_active_window];
        rc_fps_frames[rc_active_window] = 0;
    }
}

void rc_media_updateAllWindow_hw()
{
    for(int win_num = 0; win_num < MAX_WINDOWS; win_num++)
    {
        if(!rc_win[win_num])
            continue;
        int s_num = 0;
        SDL_SetRenderTarget(rc_win_renderer[win_num], rc_backBuffer[win_num]);
        SDL_SetRenderDrawColor(rc_win_renderer[win_num], rc_clearColor >> 16, rc_clearColor >> 8, rc_clearColor, 255);
        //SDL_RenderFillRect(rc_win_renderer[win_num], NULL);
        SDL_RenderClear(rc_win_renderer[win_num]);
        for(int i = MAX_SCREENS-1; i >= 0; i--)
        {
            s_num = rc_screen_zOrder[win_num][i];
            //cout << "DRAW SCREEN: " << s_num << endl;
            if(rc_hscreen[win_num][s_num] != NULL && rc_screen_visible[win_num][s_num])
            {
                //cout << "draw canvas " << s_num << endl;
                #ifdef RC_WEB
                SDL_RenderCopy(rc_win_renderer[win_num], rc_hscreen[win_num][s_num], &rc_screenview[win_num][s_num], &rc_screen_rect[win_num][s_num]);
                #else
                SDL_RenderCopy(rc_win_renderer[win_num], rc_hscreen[win_num][s_num], &rc_screenview[win_num][s_num], &rc_screen_rect[win_num][s_num]);
                #endif
            }
        }
        //#ifndef RC_ANDROID
            SDL_RenderCopy(rc_win_renderer[win_num], rc_hconsole[win_num], NULL, NULL);
        //#endif // RC_ANDROID
        //cout << endl;
        SDL_SetRenderTarget(rc_win_renderer[win_num], NULL);
        #if defined(RC_MOBILE) || defined(RC_WEB)
        SDL_RenderCopy(rc_win_renderer[win_num], rc_backBuffer[win_num], NULL, NULL);
        #else
        SDL_RenderCopy(rc_win_renderer[win_num], rc_backBuffer[win_num], &rc_bb_rect[win_num], NULL);
        #endif // RC_ANDROID
        SDL_RenderPresent(rc_win_renderer[win_num]);
        SDL_SetRenderTarget(rc_win_renderer[win_num], rc_hscreen[win_num][rc_active_screen]);
        SDL_SetRenderDrawColor(rc_win_renderer[win_num], rc_ink_color.r, rc_ink_color.g, rc_ink_color.b, rc_ink_color.a);

        rc_fps_frames[win_num]++;

        uint32_t t = SDL_GetTicks();

        if( (t - rc_fps_timer[win_num]) >= 1000 )
        {
            rc_fps_timer[win_num] = t;
            rc_fps[win_num] = rc_fps_frames[win_num];
            rc_fps_frames[win_num] = 0;
        }
    }
}

bool rc_media_imageExist_hw(int slot)
{
    return rc_image_isLoaded[slot];
}

int rc_media_numJoysticks()
{
    return SDL_NumJoysticks();
}

int rc_media_joyAxis(int joy_num, int axis)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickGetAxis(rc_joystick[joy_num], axis);
    return 0;
}

int rc_media_joyButton(int joy_num, int jbutton)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickGetButton(rc_joystick[joy_num], jbutton);
    return 0;
}

string rc_media_joystickName(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return (string)SDL_JoystickName(rc_joystick[joy_num]);
    return "";
}

int rc_media_numJoyButtons(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickNumButtons(rc_joystick[joy_num]);
    return 0;
}

int rc_media_numJoyAxes(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickNumAxes(rc_joystick[joy_num]);
    return 0;
}

int rc_media_numJoyHats(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickNumHats(rc_joystick[joy_num]);
    return 0;
}

int rc_media_joyHat(int joy_num, int hat)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickGetHat(rc_joystick[joy_num], hat);
    return 0;
}

int rc_media_numJoyTrackBalls(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        return SDL_JoystickNumBalls(rc_joystick[joy_num]);
    return 0;
}

void rc_media_getJoyTrackBall(int joy_num, int ball, double * dx, double * dy)
{
    int x = 0;
    int y = 0;
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        SDL_JoystickGetBall(rc_joystick[joy_num], ball, &x, &y);
    *dx = x;
    *dy = y;
}

bool rc_media_joystickIsConnected( int joy_num )
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
    {
        if(rc_joystick[joy_num])
            return true;
        return false;
    }
    return false;
}

void rc_media_joyRumblePlay(int joy_num, double strength, double duration)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
    {
        SDL_HapticRumblePlay(rc_haptic[joy_num], strength, (Uint32)duration);
    }
}

void rc_media_joyRumbleStop(int joy_num)
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
        SDL_HapticRumbleStop(rc_haptic[joy_num]);
}

int rc_media_joystickIsHaptic( int joy_num )
{
    if(joy_num >= 0 && joy_num < MAX_JOYSTICKS)
    {
        if(rc_haptic[joy_num])
            return 1;
    }
    return 0;
}

int rc_media_queryAudioSpec(double * freq, double * format, double * channels)
{
    //need to do something here
    int qa_freq = 0;
    Uint16 qa_format = 0;
    int qa_channels = 0;
    int result = Mix_QuerySpec(&qa_freq, &qa_format, &qa_channels);
    *freq = (double)qa_freq;
    *format = (double)qa_format;
    *channels = (double)qa_channels;
    return result;
}

void rc_media_loadSound(int slot, string fname)
{
    if(rc_sound[slot] != NULL)
    {
        Mix_FreeChunk(rc_sound[slot]);
    }
    rc_sound[slot] = Mix_LoadWAV(fname.c_str());
    if(rc_sound[slot] == NULL)
    {
        cout << "Could not load sound: " << Mix_GetError() << endl;
        return;
    }
}

void rc_media_createSound(int slot, double * abuf, Uint32 alen, Uint8 volume)
{
    if(!rc_sound[slot])
    {
        rc_sound[slot] = (Mix_Chunk*)SDL_malloc(sizeof(Mix_Chunk));
        //cout << "sound dbg 0" << endl;
        rc_sound[slot]->allocated = 1;
        //cout << "GOOD START" << endl;
        rc_sound[slot]->abuf = (Uint8*)SDL_malloc(sizeof(Uint8)*alen);
        //cout << "sound dbg 1" << endl;
        for(int i = 0; i < alen; i++)
            rc_sound[slot]->abuf[i] = (Uint8)abuf[i];
        //cout << "sound dbg 2" << endl;
        rc_sound[slot]->alen = alen;
        rc_sound[slot]->volume = volume;
    }
}

void rc_media_loadMusic(string fname)
{
    if(rc_music != NULL)
    {
        Mix_FreeMusic(rc_music);
    }
    rc_music = Mix_LoadMUS(fname.c_str());
    if(rc_music == NULL)
    {
        cout << "Could not load music: " << Mix_GetError() << endl;
        return;
    }
}

void rc_media_deleteMusic()
{
    if(rc_music)
    {
        Mix_FreeMusic(rc_music);
        rc_music = NULL;
    }
}

void rc_media_playSound(int slot, int channel, int loops)
{
    if(rc_sound[slot] != NULL)
    {
        Mix_PlayChannel(channel, rc_sound[slot], loops);
    }
}

void rc_media_playSoundTimed(int slot, int channel, int loops, int ms)
{
    if(rc_sound[slot] != NULL)
    {
        Mix_PlayChannelTimed(channel, rc_sound[slot], loops, ms);
    }
}

void rc_media_playMusic(int loops)
{
    if(rc_music != NULL)
    {
        Mix_PlayMusic(rc_music, loops);
    }
}

void rc_media_pauseSound(int channel)
{
    if(Mix_Playing(channel))
    {
        Mix_Pause(channel);
    }
}

void rc_media_resumeSound(int channel)
{
    if(!Mix_Playing(channel))
    {
        Mix_Resume(channel);
    }
}

void rc_media_pauseMusic()
{
    if(Mix_PlayingMusic())
    {
        Mix_PauseMusic();
    }
}

void rc_media_resumeMusic()
{
    if(!Mix_PlayingMusic())
    {
        Mix_ResumeMusic();
    }
}

void rc_media_deleteSound(int slot)
{
    if(rc_sound[slot] != NULL)
    {
        Mix_FreeChunk(rc_sound[slot]);
        rc_sound[slot] = NULL;
    }
}

void rc_media_fadeMusicIn(int time, int loops)
{
    Mix_FadeInMusic(rc_music, loops, time);
}

void rc_media_fadeMusicOut(int time)
{
    Mix_FadeOutMusic(time);
}

bool rc_media_musicExists()
{
    if(rc_music != NULL)
        return true;
    return false;
}

void rc_media_setMusicVolume(int volume)
{
    Mix_VolumeMusic(volume);
}

int rc_media_getMusicVolume()
{
    return Mix_VolumeMusic(-1);
}

void rc_media_setMusicPosition(double position)
{
    Mix_SetMusicPosition(position);
}

double rc_media_getMusicPosition()
{
    return Mix_SetMusicPosition(-1);
}

void rc_media_rewindMusic()
{
    Mix_RewindMusic();
}

void rc_media_setSoundChannels(int max_channels)
{
    Mix_AllocateChannels(max_channels);
}

int rc_media_getSoundChannels()
{
    return Mix_AllocateChannels(-1);
}

bool rc_media_soundIsEnabled()
{
    return (bool) Mix_Init(0);
}

bool rc_media_soundExists(int slot)
{
    if(rc_sound[slot] != NULL)
        return true;
    return false;
}

void rc_media_setChannelVolume(int channel, int volume)
{
    Mix_Volume(channel, volume);
}

int rc_media_getChannelVolume(int channel)
{
    return Mix_Volume(channel, -1);
}

void rc_media_setSoundVolume(int slot, int volume)
{
    Mix_VolumeChunk(rc_sound[slot], volume);
}

int rc_media_getSoundVolume(int slot)
{
    return Mix_VolumeChunk(rc_sound[slot], -1);
}

void rc_media_stopMusic()
{
    Mix_HaltMusic();
}

void rc_media_stopSound(int channel)
{
    Mix_HaltChannel(channel);
}

int rc_media_channelIsPlaying(int channel)
{
    return Mix_Playing(channel);
}

int rc_media_channelIsPaused(int channel)
{
    return Mix_Paused(channel);
}

int rc_media_setChannelDistance(int channel, Uint8 dist)
{
    return Mix_SetDistance(channel, dist);
}

int rc_media_setChannelPanning(int channel, Uint8 l, Uint8 r)
{
    return Mix_SetPanning(channel, l, r);
}

//NETWORKING

//TCPsocket rc_socket[5];
//UDPsocket rc_udp_socket[5];
//UDPpacket * rc_udp_packet;
//int rc_udp_channel;
//string rc_udp_data;
//int rc_udp_len;
//int rc_udp_maxlen;
//string rc_udp_host;
//Uint16 rc_udp_port;

int rc_net_tcp_openSocket(int _socket, string host, Uint16 port)
{
    if(_socket >= MAX_SOCKETS)
    {
        cout << "TCP_SocketOpen Error: Maximum number of sockets available is " << MAX_SOCKETS << endl;
        return 0;
    }
    IPaddress ip;
    if(host.compare("") == 0)
    {
        //exit(0);
        SDLNet_ResolveHost(&ip, NULL, port);
    }
    else
    {
        //exit(0);
        SDLNet_ResolveHost(&ip, host.c_str(), port);
    }
    rc_socket[_socket] = SDLNet_TCP_Open(&ip);
    if(rc_socket[_socket])
    {
        //cout << "Add socket to socket_set" << endl;
        SDLNet_TCP_AddSocket(rc_socket_set, rc_socket[_socket]);
        return 1;
    }
    return 0;
}

void rc_net_tcp_closeSocket(int _socket)
{
    if( _socket >= MAX_SOCKETS)
    {
        cout << "TCP_SocketClose Error: Maximum number of sockets available is " << MAX_SOCKETS << endl;
        return;
    }
    SDLNet_TCP_DelSocket(rc_socket_set, rc_socket[_socket]);
    SDLNet_TCP_Close(rc_socket[_socket]);
    rc_socket[_socket] = NULL;
}

Uint32 rc_net_tcp_remoteHost(int _socket)
{
    IPaddress * ip =  SDLNet_TCP_GetPeerAddress(rc_socket[_socket]);
    return ip->host;
}

Uint32 rc_net_tcp_remotePort(int _socket)
{
    IPaddress * ip = SDLNet_TCP_GetPeerAddress(rc_socket[_socket]);
    return ip->port;
}

int rc_net_checkSockets(Uint32 m)
{
    return SDLNet_CheckSockets(rc_socket_set, m);
}

int rc_net_tcp_socketReady(int _socket)
{
    return SDLNet_SocketReady(rc_socket[_socket]);
}

int rc_net_tcp_getData(int socket, void * dst, int numBytes)
{
    int rtn = SDLNet_TCP_Recv(rc_socket[socket], dst, numBytes);
    return rtn;
}

int rc_net_tcp_getData_str(int socket, string * dst, int numBytes)
{
    char c[numBytes+1];
    int rtn = rc_net_tcp_getData(socket, c, numBytes);
    c[numBytes] = '\0';
    dst[0] = c;
    return rtn;
}

int rc_net_tcp_getData_dbl(int socket, double * dst, int numBytes)
{
    int i[numBytes];
    int rtn = rc_net_tcp_getData(socket, i, numBytes);
    for(int n = 0; n < numBytes; n++)
    {
        dst[n] = i[n];
    }
    return rtn;
}

void rc_net_tcp_sendData(int socket, const char * data, int numBytes)
{
    SDLNet_TCP_Send(rc_socket[socket], data, numBytes);
}

bool rc_net_tcp_acceptSocket(int socket_server, int socket_client)
{
    //cout << "\n\nthis is a test\n\n";
    if(rc_socket[socket_server] == NULL)
    {
        //cout << "no server" << endl;
        return false;
    }
    bool val = (rc_socket[socket_client] = SDLNet_TCP_Accept(rc_socket[socket_server]));
    if(val)
        SDLNet_TCP_AddSocket(rc_socket_set, rc_socket[socket_client]);
    //cout << "cp1\n";
    return val;
}

bool rc_net_udp_openSocket(int socket, Uint16 port)
{
    bool rtn = (bool)(rc_udp_socket[socket] = SDLNet_UDP_Open(port));
    if(rtn)
        SDLNet_UDP_AddSocket(rc_socket_set, rc_udp_socket[socket]);
	return rtn;
}

int rc_net_udp_socketReady(int socket)
{
    return SDLNet_SocketReady(rc_udp_socket[socket]);
}

int rc_net_udp_readStream(int socket, string * dst, string * host, double * port)
{
    //cout << "DEBUG READSTREAM\n";
    //UDPsocket sd;       /* Socket descriptor */
	//UDPpacket *p;       /* Pointer to packet memory */
	//int quit = 0;

    /* Make space for the packet */
	//if (!(rc_udp_packet = SDLNet_AllocPacket(512)))
	//{
	//	fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
	//	exit(EXIT_FAILURE);
	//}

	/* Main loop */

    /* Wait a packet. UDP_Recv returns != 0 if a packet is coming */
    //while(!quit)
    //{
        if (SDLNet_UDP_Recv(rc_udp_socket[socket], rc_udp_packet))
        {
            //printf("UDP Packet incoming\n");
            //printf("\tChan:    %d\n", rc_udp_packet->channel);
            rc_udp_channel = rc_udp_packet->channel;
            //printf("\tData:    %s\n", (char *)rc_udp_packet->data);
            const char * c = (const char *)rc_udp_packet->data;
            //rc_udp_data = (string)c;
            *dst = (string)c;
            //printf("\tLen:     %d\n", rc_udp_packet->len);
            rc_udp_len = rc_udp_packet->len;
            //printf("\tMaxlen:  %d\n", rc_udp_packet->maxlen);
            rc_udp_maxlen = rc_udp_packet->maxlen;
            //printf("\tStatus:  %d\n", rc_udp_packet->status);
            //printf("\tAddress: %x %x\n", rc_udp_packet->address.host, rc_udp_packet->address.port);
            //rc_udp_host = SDLNet_ResolveIP(&rc_udp_packet->address);
            *host = SDLNet_ResolveIP(&rc_udp_packet->address);
            //rc_udp_port = rc_udp_packet->address.port;
            *port = rc_udp_packet->address.port;
            return 1;
            //quit = 1;
        }
        else
        {
            rc_udp_channel = 0;
            //rc_udp_data = "";
            *dst = "";
            rc_udp_len = 0;
            rc_udp_maxlen = rc_udp_packet->maxlen;
            //rc_udp_host = SDLNet_ResolveIP(&rc_udp_packet->address);
            *host = SDLNet_ResolveIP(&rc_udp_packet->address);
            //rc_udp_port = rc_udp_packet->address.port;
            *port = rc_udp_packet->address.port;
            return 0;
        }

    //}

    //SDLNet_FreePacket(rc_udp_packet);
}

Uint32 rc_net_udp_len()
{
    return rc_udp_len;
}

Uint32 rc_net_udp_maxlen()
{
    return rc_udp_maxlen;
}

string rc_net_udp_getRemoteHost(int socket)
{
    IPaddress * ip = SDLNet_UDP_GetPeerAddress(rc_udp_socket[socket],0);
    //
    return SDLNet_ResolveIP(ip);
}

Uint32 rc_net_udp_getRemotePort(int socket)
{
    IPaddress * ip = SDLNet_UDP_GetPeerAddress(rc_udp_socket[socket],0);
    return ip->port;
}

int rc_net_udp_closeSocket(int socket)
{
    SDLNet_UDP_DelSocket(rc_socket_set, rc_udp_socket[socket]);
    SDLNet_UDP_Close(rc_udp_socket[socket]);
    rc_udp_socket[socket] = NULL;
    return 0;
}

int rc_net_udp_sendData(int slot, string host, Uint16 port, string s_data)
{
    IPaddress srvadd;

    if(s_data.length()+1 > rc_packet_size)
    {
        rc_packet_size = SDLNet_ResizePacket(rc_udp_packet, s_data.length()+1);
        if(rc_packet_size < s_data.length())
        {
            cout << "UDP_SendData Error: " << SDLNet_GetError() << endl;
            return 0;
        }
    }


    if(rc_udp_packet == NULL)
        return 0;


    if (SDLNet_ResolveHost(&srvadd, host.c_str(), port) == -1)
	{
		std::cout << "UDP_SendData Error: " << SDLNet_GetError() << "\n";
		//exit(EXIT_FAILURE);
		return 0;
	}

	rc_udp_packet->address.host = srvadd.host;
    rc_udp_packet->address.port = srvadd.port;
	rc_udp_packet->data = (Uint8*)s_data.c_str();


	rc_udp_packet->len = s_data.length()+1;
	//cout << "#Data = " << (char*)rc_udp_packet->data << endl;
	//cout << "#Length = " << rc_udp_packet->len << endl;
	SDLNet_UDP_Send(rc_udp_socket[slot], -1, rc_udp_packet);

    return 1;
}

string rc_byteToString(Uint8 n)
{
    stringstream s;
    s << (Uint32)n;
    return s.str();
}

string rc_net_myLocalIP()
{
    //cout << "MYLOCALIP" << endl;
    IPaddress myIP;
    myIP.host = 0;
    myIP.port = 0;
    string net_name = SDLNet_ResolveIP(&myIP);
    SDLNet_ResolveHost(&myIP,net_name.c_str(),0);
    string ip = "";
    ip += rc_byteToString((Uint8)myIP.host) + ".";
    ip += rc_byteToString((Uint8)(myIP.host >> 8)) + ".";
    ip += rc_byteToString((Uint8)(myIP.host >> 16)) + ".";
    ip += rc_byteToString((Uint8)(myIP.host >> 24));
    //cout << "vagina: " << myIP.host << endl;
    return ip;
}

//#################VIDEO PLAYBACK#####################################################################

#ifdef RC_USE_TREMOR
void videoPlayer_audio_callback(void *userdata, Uint8 *stream, int len)
{
    // !!! FIXME: this should refuse to play if item->playms is in the future.
    //const Uint32 now = SDL_GetTicks() - baseticks;
    Sint16 *dst = (Sint16 *) stream;

    while (audio_queue && (len > 0))
    {
        volatile AudioQueue *item = audio_queue;
        AudioQueue *next = item->next;
        const int channels = item->audio->channels;

        const Sint32 *src = (Sint32 *) (item->audio->samples + (item->offset * channels));

        int cpy = (item->audio->frames - item->offset) * channels;
        int i;

        if (cpy > (len / sizeof (Sint16)))
            cpy = len / sizeof (Sint16);

        for (i = 0; i < cpy; i++)
        {
            const Sint32 val = *(src++);

            if (val < -32768)
                *(dst++) = -32768;
            else if (val > 32767)
                *(dst++) = 32767;
            else
            {
                *(dst++) = (Sint16) (val);
            }
        } // for

        item->offset += (cpy / channels);
        len -= cpy * sizeof (Sint16);

        if (item->offset >= item->audio->frames)
        {
            THEORAPLAY_freeAudio(item->audio);
            free((void *) item);
            audio_queue = next;
        } // if
    } // while

    if (!audio_queue)
        audio_queue_tail = NULL;

    if (len > 0)
        memset(dst, '\0', len);
} // audio_callback
#else
void videoPlayer_audio_callback(void *userdata, Uint8 *stream, int len)
{
    // !!! FIXME: this should refuse to play if item->playms is in the future.
    //const Uint32 now = SDL_GetTicks() - baseticks;
    Sint16 *dst = (Sint16 *) stream;

    while (audio_queue && (len > 0))
    {
        volatile AudioQueue *item = audio_queue;
        AudioQueue *next = item->next;
        const int channels = item->audio->channels;

        const float *src = item->audio->samples + (item->offset * channels);
        int cpy = (item->audio->frames - item->offset) * channels;
        int i;

        if (cpy > (len / sizeof (Sint16)))
            cpy = len / sizeof (Sint16);

        for (i = 0; i < cpy; i++)
        {
            const float val = *(src++);
            if (val < -1.0f)
                *(dst++) = -32768;
            else if (val > 1.0f)
                *(dst++) = 32767;
            else
                *(dst++) = (Sint16) (val * 32767.0f);
        } // for

        item->offset += (cpy / channels);
        len -= cpy * sizeof (Sint16);

        if (item->offset >= item->audio->frames)
        {
            THEORAPLAY_freeAudio(item->audio);
            free((void *) item);
            audio_queue = next;
        } // if
    } // while

    if (!audio_queue)
        audio_queue_tail = NULL;

    if (len > 0)
        memset(dst, '\0', len);
} // audio_callback
#endif

static void videoPlayer_queue_audio(const THEORAPLAY_AudioPacket *audio)
{
    AudioQueue *item = (AudioQueue *) malloc(sizeof (AudioQueue));
    if (!item)
    {
        THEORAPLAY_freeAudio(audio);
        return;  // oh well.
    } // if

    item->audio = audio;
    item->offset = 0;
    item->next = NULL;

    //SDL_LockAudio();
    if (audio_queue_tail)
        audio_queue_tail->next = item;
    else
        audio_queue = item;
    audio_queue_tail = item;
    //SDL_UnlockAudio();
} // queue_audio

void rc_media_loadVideo(string fname)
{
    //cout << "CRAP" << endl;
    decoder = THEORAPLAY_startDecodeFile(fname.c_str(), 30, THEORAPLAY_VIDFMT_RGBA);
    if(!decoder)
    {
        decoder = NULL;
        cout << "Failed to load video: " << fname << endl;
        return;
    }

    rc_video_file = fname;
    while (!audio || !video)
    {
        if (!audio) audio = THEORAPLAY_getAudio(decoder);
        if (!video) video = THEORAPLAY_getVideo(decoder);
        SDL_Delay(10);
    } // if
    overlay = SDL_CreateTexture(rc_win_renderer[rc_active_window], SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, video->width, video->height);
    SDL_SetTextureBlendMode(overlay, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(overlay, 255);
    framems = (video->fps == 0.0) ? 0 : ((Uint32) (1000.0 / video->fps));
    rc_video_dstrect.x = 0;
    rc_video_dstrect.y = 0;
    rc_video_dstrect.w = video->width;
    rc_video_dstrect.h = video->height;
    rc_video_width = video->width;
    rc_video_height = video->height;

    if (!overlay)
    {
        fprintf(stderr, "Video failed: %s\n", SDL_GetError());
        return;
    }
    //} // else

    initfailed = quit = (!overlay);
    rc_video_end = false;


    //fprintf(stderr, "b_debug 3.5\n");
}

int rc_media_getVideoStats(string fname, double * v_len, double * v_fps, double * v_width, double * v_height)
{
    //cout << "CRAP" << endl;
    if(decoder)
        return 0;
    decoder = THEORAPLAY_startDecodeFile(fname.c_str(), 30, THEORAPLAY_VIDFMT_RGBA);
    if(!decoder)
    {
        decoder = NULL;
        cout << "Failed to load video: " << fname << endl;
        return 0;
    }

    while(THEORAPLAY_isDecoding(decoder))
    {
        if(!video)
            video = THEORAPLAY_getVideo(decoder);
        if(video)
        {
            rc_video_length = video->playms;
            rc_video_fps = video->fps;
            rc_video_width = video->width;
            rc_video_height = video->height;
            THEORAPLAY_freeVideo(video);
            video = NULL;
        }

        if(!audio)
            audio = THEORAPLAY_getAudio(decoder);
        if(audio)
        {
            THEORAPLAY_freeAudio(audio);
            audio = NULL;
        }

        //SDL_Delay(1);
    }

    THEORAPLAY_stopDecode(decoder);
    decoder = NULL;

    *v_len = rc_video_length;
    *v_fps = rc_video_fps;
    *v_width = rc_video_width;
    *v_height = rc_video_height;
    rc_video_length = 0;
    rc_video_fps = 0;
    rc_video_width = 0;
    rc_video_height = 0;
    return 1;
}

void rc_media_getVideoSize(double * w, double * h)
{
    *w = rc_video_width;
    *h = rc_video_height;
}

void rc_media_setVideoDrawRect(int x, int y, int w, int h)
{
    rc_video_dstrect.x = x;
    rc_video_dstrect.y = y;
    rc_video_dstrect.w = w;
    rc_video_dstrect.h = h;
}

void rc_media_getVideoDrawRect(double * x, double * y, double * w, double * h)
{
    *x = rc_video_dstrect.x;
    *y = rc_video_dstrect.y;
    *w = rc_video_dstrect.w;
    *h = rc_video_dstrect.h;
}

int rc_media_videoLength()
{
    return rc_video_length;
}

void rc_cleanResume()
{
    //cout << "tat" << endl;
    //if (overlay) SDL_DestroyTexture(overlay);
    if (video) THEORAPLAY_freeVideo(video);
    if (audio) THEORAPLAY_freeAudio(audio);
    if (decoder) THEORAPLAY_stopDecode(decoder);
    //cout  << "bubble wrap" << endl;
    //SDL_ClearQueuedAudio(0);
    //while(SDL_GetQueuedAudioSize(0)>0){}

    rc_video_isPlaying = false;
    video = NULL;
    audio = NULL;
    decoder = NULL;
    decoder = THEORAPLAY_startDecodeFile(rc_video_file.c_str(), 30, THEORAPLAY_VIDFMT_RGBA);
    while(!audio && !video && THEORAPLAY_isDecoding(decoder))
    {
        audio = THEORAPLAY_getAudio(decoder);
        video = THEORAPLAY_getVideo(decoder);
        if(audio)
        {
            if(audio->playms <= rc_video_pauseTicks)
            {
                THEORAPLAY_freeAudio(audio);
                audio = NULL;
            }
        }

        if(video)
        {
            if(video->playms <= rc_video_pauseTicks)
            {
                THEORAPLAY_freeVideo(video);
                video = NULL;
            }
        }
    }
    //cout << "bankai" << endl;
}

void rc_media_playVideo(int loops)
{
    if(rc_video_isPlaying)
        return;
    if(rc_video_reset)
    {
        //cout << "RESET" << endl;
        decoder = THEORAPLAY_startDecodeFile(rc_video_file.c_str(), 30, THEORAPLAY_VIDFMT_RGBA);
        if(!decoder)
        {
            cout << "Video Reset Error: " << SDL_GetError() << endl;
        }
        while(!audio || !video)
        {
            if(!audio) audio = THEORAPLAY_getAudio(decoder);
            if(!video) video = THEORAPLAY_getVideo(decoder);
            SDL_Delay(10);
        }
        rc_video_reset = false;
    }

    Mix_CloseAudio();
    rc_video_currentLoop = 0;
    rc_video_loops = loops;
    rc_video_isPlaying = true;

    if(Mix_OpenAudio(audio->freq, AUDIO_S16SYS, audio->channels, 2048) < 0)
    {
        rc_audio_isOpen = false;
        cout << "Open Audio Error: " << Mix_GetError() <<endl;
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            cout << "Open Audio Error: " << Mix_GetError() << endl;
        }
        quit = 1;
        return;
    }

    Mix_HookMusic(videoPlayer_audio_callback, NULL);

    rc_audio_isOpen = true;

    if(!rc_video_isLoaded)
    {
        while (audio)
        {
            videoPlayer_queue_audio(audio);
            audio = THEORAPLAY_getAudio(decoder);
        } // while
    }

    baseticks = SDL_GetTicks();
    rc_video_isLoaded = true;

    if (!quit)
        Mix_Pause(-1);
}

void rc_media_stopVideo()
{
    //if(!rc_video_isPlaying)
    //    return;

    //cout << "baking soda" << endl;
    //if (overlay) SDL_DestroyTexture(overlay);
    if (video) THEORAPLAY_freeVideo(video);
    if (audio) THEORAPLAY_freeAudio(audio);
    if (decoder) THEORAPLAY_stopDecode(decoder);
    //cout  << "bubble wrap" << endl;
    //SDL_ClearQueuedAudio(0);
    //while(SDL_GetQueuedAudioSize(0)>0){}
    SDL_Delay(1500);
    if(rc_audio_isOpen)
    {
        Mix_CloseAudio();
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            cout << "OpenAudio Error: " << Mix_GetError() << endl;
        }
        Mix_HookMusic(NULL, NULL);
        rc_audio_isOpen = false;
    }
    rc_video_isPlaying = false;
    rc_video_loops = 0;
    rc_video_currentLoop = 0;
    rc_video_position = 0;
    rc_video_reset = true;
    rc_video_end = false;
    video = NULL;
    audio = NULL;
    decoder = NULL;
    //cout << "mini" << endl;
}

static bool cycleVideo()
{
    //cout << "video_start" << endl;
    if(!rc_video_isPlaying)
        return false;
    //cout << "never print this" << endl;
    //int q = !quit;
    //int tp = THEORAPLAY_isDecoding(decoder);
    //cout << "VARS = " << q << " & " << tp << endl;
    int isDecode = THEORAPLAY_isDecoding(decoder);
    if(isDecode)
        rc_video_end = false;
    else
    {
        rc_video_currentLoop++;
        if((rc_video_currentLoop <= rc_video_loops) || (rc_video_loops < 0))
        {
            rc_media_stopVideo();
            rc_media_playVideo(rc_video_loops);
            return true;
        }
        rc_video_end = true;
        rc_video_isPlaying = false;
    }

    if (!quit && isDecode)
    {
        const Uint32 now = SDL_GetTicks() - baseticks;
        rc_video_pauseTicks = now;
        rc_video_position = now;

        if (!video)
            video = THEORAPLAY_getVideo(decoder);

        //fprintf(stderr, "b_debug A\n");

        // Play video frames when it's time.
        if (video && (video->playms <= now))
        {
            //fprintf(stderr, "b_debug B\n");
            //printf("Play video frame (%u ms)!\n", video->playms);
            if ( framems && ((now - video->playms) >= framems) )
            {
                //fprintf(stderr, "b_debug C\n");
                // Skip frames to catch up, but keep track of the last one
                //  in case we catch up to a series of dupe frames, which
                //  means we'd have to draw that final frame and then wait for
                //  more.
                const THEORAPLAY_VideoFrame *last = video;
                while ((video = THEORAPLAY_getVideo(decoder)) != NULL)
                {
                    THEORAPLAY_freeVideo(last);
                    last = video;
                    if ((now - video->playms) < framems)
                        break;
                } // while

                //fprintf(stderr, "b_debug D\n");

                if (!video)
                    video = last;
            } // if

            //fprintf(stderr, "b_debug B.1\n");
            int lock_tex = SDL_LockTexture(overlay, NULL, &overlay_pixels, &pitch);
            //fprintf(stderr, "b_debug B.1.2\n");

            if (!video)  // do nothing; we're far behind and out of options.
            {
                static int warned = 0;
                if (!warned)
                {
                    warned = 1;
                    fprintf(stderr, "WARNING: Playback can't keep up!\n");
                } // if
            } // if
            else if (lock_tex<0)
            {
                //fprintf(stderr, "b_debug E\n");
                static int warned = 0;
                if (!warned)
                {
                    warned = 1;
                    fprintf(stderr, "Couldn't lock video frame: %s\n", SDL_GetError());
                } // if
            } // else if
            else
            {
                //fprintf(stderr, "b_debug 4\n");
                //SDL_Rect dstrec = { 0, 0, video->width, video->height };
                const int w = video->width;
                const int h = video->height;
                Uint8 *dst;

                const Uint8 * vbuf = (const Uint8*)video->pixels;

                dst = (Uint8*)overlay_pixels;

                SDL_memcpy(dst, vbuf, w*h*4);

                //fprintf(stderr, "b_debug 7\n");

                SDL_UnlockTexture(overlay);

                //if (SDL_DisplayYUVOverlay(overlay, &dstrect) != 0)
                if(SDL_RenderCopy(rc_win_renderer[rc_active_window], overlay, NULL, &rc_video_dstrect) < 0)
                {
                    static int warned = 0;
                    if (!warned)
                    {
                        warned = 1;
                        fprintf(stderr, "Couldn't display video frame: %s\n", SDL_GetError());
                    } // if
                } // if
                else
                {
                    //SDL_RenderPresent(rc_win_renderer[rc_active_window]);
                    //cout << "window drawn" << endl;
                }
            } // else
            //fprintf(stderr, "b_debug B.5\n");

            THEORAPLAY_freeVideo(video);
            video = NULL;
        } // if
        else  // no new video frame? Give up some CPU.
        {
            SDL_Delay(10);
        } // else

        //fprintf(stderr, "b_debug F\n");
        while ((audio = THEORAPLAY_getAudio(decoder)) != NULL)
            videoPlayer_queue_audio(audio);

        return true;
    } // while
    return false;

} // playfile

void rc_media_deleteVideo()
{
    //cout << "cream soda" << endl;
    if (overlay) SDL_DestroyTexture(overlay);
    overlay = NULL;
    if (video) THEORAPLAY_freeVideo(video);
    video = NULL;
    if (audio) THEORAPLAY_freeAudio(audio);
    audio = NULL;
    if (decoder) THEORAPLAY_stopDecode(decoder);
    decoder = NULL;
    //cout  << "bubble wrap" << endl;
    if(rc_audio_isOpen)
    {
        Mix_CloseAudio();
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            cout << "OpenAudio Error: " << Mix_GetError() << endl;
        }
        rc_audio_isOpen = false;
        Mix_HookMusic(NULL, NULL);
    }
    rc_video_file = "";
    rc_video_isLoaded = false;
    rc_video_isPlaying = false;
    rc_video_loops = 0;
    rc_video_position = 0;
    rc_video_length = 0;
    rc_video_width = 0;
    rc_video_height = 0;
    rc_video_dstrect.x = 0;
    rc_video_dstrect.y = 0;
    rc_video_dstrect.w = 0;
    rc_video_dstrect.h = 0;
    //cout << "mini" << endl;
}

void rc_media_pauseVideo()
{
    //if(rc_video_isPaused)
    //    return;
    rc_video_isPlaying = false;
    if (video) THEORAPLAY_freeVideo(video);
    if (audio) THEORAPLAY_freeAudio(audio);
    Mix_Pause(-1);
    SDL_Delay(1500);
    if(rc_audio_isOpen)
    {
        Mix_CloseAudio();
        if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            cout << "OpenAudio Error: " << Mix_GetError() << endl;
        }
        rc_audio_isOpen = false;
    }
    video = NULL;
    audio = NULL;
    rc_video_isPaused = true;
}

void rc_media_resumeVideo()
{
    if(!rc_video_isPaused)
        return;

    //fprintf(stderr, "RESUME\n" );

    int dec_cycle = 0;

    while(!audio || !video)
    {
        if(!audio) audio = THEORAPLAY_getAudio(decoder);
        if(!video) video = THEORAPLAY_getVideo(decoder);
        SDL_Delay(10);
        dec_cycle++;
        if(dec_cycle == 100)
            rc_cleanResume();
        if(dec_cycle >= 200)
        {
            rc_video_isPaused = false;
            rc_media_stopVideo();
            return;
        }
        //fprintf(stderr,"working\n");
    }

    //fprintf(stderr,"debug 1\n");
    if(!rc_audio_isOpen)
        Mix_CloseAudio();
    rc_video_isPlaying = true;
    //fprintf(stderr,"debug 2\n");

    if(!rc_audio_isOpen)
    {
        if(Mix_OpenAudio(audio->freq, AUDIO_S16SYS, audio->channels, 2048) < 0)
        {
            cout << "Open Audio Error: " << Mix_GetError() <<endl;
            if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                cout << "OpenAudio Error: " << Mix_GetError() << endl;
            }
            quit = 1;
            return;
        }
        rc_audio_isOpen = true;
    }
    //fprintf(stderr,"debug 4\n");

    if(!rc_video_isLoaded)
    {
        //cout << "GILLITEEN" <<endl;
        while (audio)
        {
            videoPlayer_queue_audio(audio);
            audio = THEORAPLAY_getAudio(decoder);
        } // while
    }

    baseticks = SDL_GetTicks() - rc_video_pauseTicks;
    rc_video_isLoaded = true;
    rc_video_isPaused = false;

    //fprintf(stderr, "b_debug x\n");

    if (!quit)
        Mix_Pause(-1);

}

Uint32 rc_media_videoPosition()
{
    return rc_video_position;
}

void rc_media_setVideoPosition(Uint32 vpos)
{
    bool is_playing = rc_video_isPlaying;
    if(is_playing) rc_media_pauseVideo();
    rc_video_pauseTicks = vpos;
    rc_video_position = vpos;
    if(is_playing) rc_media_resumeVideo();
}

bool rc_media_videoIsPlaying()
{
    return rc_video_isPlaying;
}

bool rc_media_videoEnd()
{
    return rc_video_end;
}

bool rc_media_videoExists()
{
    if(decoder)
        return true;
    return false;
}

void rc_media_setVideoAlpha(Uint8 alpha)
{
    if(overlay)
        SDL_SetTextureAlphaMod(overlay, alpha);
}
