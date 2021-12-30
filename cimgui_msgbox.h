/* --------------------------------------------------------------------- */
/*  Microsoft MessageBox compatible message box replacement for cimgui   */
/* --------------------------------------------------------------------- */

#ifndef _CIMGUI_MSGBOX_INCLUDED
#define _CIMGUI_MSGBOX_INCLUDED

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

#ifndef _WIN32
#ifndef NOMB

/*
 * MessageBox() Flags
 */
enum mb_flags 
{
	/* button style flags */
	MB_OK                      = 0x00000000,
	MB_OKCANCEL                = 0x00000001,
	MB_ABORTRETRYIGNORE        = 0x00000002,
	MB_YESNOCANCEL             = 0x00000003,
	MB_YESNO                   = 0x00000004,
	MB_RETRYCANCEL             = 0x00000005,
	MB_CANCELTRYCONTINUE       = 0x00000006,
	/* icon style flags */
	MB_ICONNONE                = 0x00000000,
	MB_ICONHAND                = 0x00000010,
	MB_ICONQUESTION            = 0x00000020,
	MB_ICONEXCLAMATION         = 0x00000030,
	MB_ICONASTERISK            = 0x00000040,
	MB_USERICON                = 0x00000080,
	MB_ICONWARNING             = MB_ICONEXCLAMATION,
	MB_ICONERROR               = MB_ICONHAND,
	MB_ICONINFORMATION         = MB_ICONASTERISK,
	MB_ICONSTOP                = MB_ICONHAND,
	/* default button flags */
	MB_DEFBUTTON1              = 0x00000000,
	MB_DEFBUTTON2              = 0x00000100,
	MB_DEFBUTTON3              = 0x00000200,
	MB_DEFBUTTON4              = 0x00000300,
	/* modal flags */
	MB_APPLMODAL               = 0x00000000,
	MB_SYSTEMMODAL             = 0x00001000,
	MB_TASKMODAL               = 0x00002000,
	MB_HELP                    = 0x00004000, // Help Button

	MB_NOFOCUS                 = 0x00008000L,

	MB_SETFOREGROUND           = 0x00010000L,
	MB_DEFAULT_DESKTOP_ONLY    = 0x00020000L,
	MB_TOPMOST                 = 0x00040000L,
	MB_RIGHT                   = 0x00080000L,
	MB_RTLREADING              = 0x00100000L,
#ifdef _WIN32_WINNT
#if (_WIN32_WINNT >= 0x0400)
	MB_SERVICE_NOTIFICATION        = 0x00200000,
#else
	MB_SERVICE_NOTIFICATION        = 0x00040000,
#endif
	MB_SERVICE_NOTIFICATION_NT3X   = 0x00040000,
#endif
};

#define MB_TYPEMASK                 0x0000000FL
#define MB_ICONMASK                 0x000000F0L
#define MB_DEFMASK                  0x00000F00L
#define MB_MODEMASK                 0x00003000L
#define MB_MISCMASK                 0x0000C000L
#define MB_BUTTON_SIZE

#endif

#define HWND ImGuiWindow*

#endif

#define MB_NUM_BUTTONS 4
#define MB_TYPE_SIZE MB_TYPEMASK     >> 0
#define MB_ICON_SIZE MB_ICONMASK     >> 1
#define MB_DEFA_SIZE MB_NUM_BUTTONS
#define MB_MODE_SIZE MB_MODEMASK     >> 3

uint8_t MB_TYPE_NUM_BUTTONS[MB_TYPE_SIZE] =
{
	1,
	2,
	3,
	3,
	2,
	2,
	3,
	0,
};

const char* MB_TYPE[MB_TYPE_SIZE][MB_NUM_BUTTONS] =
{
	{ "Ok",        NULL,       NULL, NULL, },
	{ "Ok",    "Cancel",       NULL, NULL, },
	{ "Abort",  "Retry",   "Ignore", NULL, },
	{ "Yes",       "No",   "Cancel", NULL, },
	{ "Yes",       "No",       NULL, NULL, },
	{ "Retry", "Cancel",       NULL, NULL, },
	{ "Cancel",   "Try", "Continue", NULL, },
	{ NULL,        NULL,       NULL, NULL, },
};

const char* MB_DEFAULT[MB_NUM_BUTTONS] =
{
	"Default1",
	"Default2",
	"Default3",
	"Default4",
};

const char* MB_MODE[MB_MODE_SIZE] =
{
	"Application",
	"System", 
	"Task",
	NULL,
	"Help",
	NULL,
	NULL,
	NULL,
};

struct mb_icon 
{
	const char* name;
	ImTextureID data;
	ImVec2 size;
	int channels;
};

struct mb_icon MB_ICON[MB_ICON_SIZE] =
{
	{ NULL,              },
	{ "hand.ico",        },
	{ "question.ico",    },
	{ "exclamation.ico", },
	{ "asterisk.ico",    },
	{ NULL,              },
	{ NULL,              },
	{ NULL,              },
	{ "user.ico",        },
	{ NULL,              },
	{ NULL,              },
	{ NULL,              },
	{ NULL,              },
	{ NULL,              },
	{ NULL,              },
	{ NULL,              },
};

CIMGUI_API int MessageBox( HWND hWnd, const char* text, const char* caption, unsigned int type);

#endif
