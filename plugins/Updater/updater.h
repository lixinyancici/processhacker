#ifndef __UPDATER_H__
#define __UPDATER_H__

#pragma comment(lib, "Winhttp.lib")

#include <phdk.h>
#include <phappresource.h>
#include <mxml.h>
#define CINTERFACE
#define COBJMACROS
#include <windowsx.h>
#include <netlistmgr.h>
#include <winhttp.h>

#include "resource.h"

#define Control_Visible(hWnd, visible) \
    ShowWindow(hWnd, visible ? SW_SHOW : SW_HIDE);

#define UPDATE_MENUITEM 101
#define SETTING_AUTO_CHECK L"ProcessHacker.Updater.PromptStart"
#define MAKEDLLVERULL(major, minor, build, sp) \
    (((ULONGLONG)(major) << 48) | \
    ((ULONGLONG)(minor) << 32) | \
    ((ULONGLONG)(build) << 16) | \
    ((ULONGLONG)(sp) <<  0))

extern PPH_PLUGIN PluginInstance;

typedef enum _PH_UPDATER_STATE
{
    PhUpdateDefault = 0,
    PhUpdateDownload = 1,
    PhUpdateInstall = 2,
    PhUpdateMaximum = 3
} PH_UPDATER_STATE;

typedef struct _UPDATER_XML_DATA
{
    BOOLEAN HaveData;
    ULONG MinorVersion;
    ULONG MajorVersion;
    ULONG RevisionVersion;
    ULONG CurrentMinorVersion;
    ULONG CurrentMajorVersion;
    ULONG CurrentRevisionVersion;
    PPH_STRING Version;
    PPH_STRING RevVersion;
    PPH_STRING RelDate;
    PPH_STRING Size;
    PPH_STRING Hash;
    PPH_STRING ReleaseNotesUrl;
    PPH_STRING SetupFilePath;
    PH_UPDATER_STATE UpdaterState;
    HINTERNET HttpSessionHandle;
    HBITMAP SourceforgeBitmap;
} UPDATER_XML_DATA, *PUPDATER_XML_DATA;

VOID ShowUpdateDialog(
    __in PUPDATER_XML_DATA Context
    );

VOID StartInitialCheck(
    VOID
    );

PPH_STRING PhGetOpaqueXmlNodeText(
    __in mxml_node_t *xmlNode
    );

BOOL PhInstalledUsingSetup(
    VOID
    );

BOOL ConnectionAvailable(
    VOID
    );

INT_PTR CALLBACK UpdaterWndProc(
    __in HWND hwndDlg,
    __in UINT uMsg,
    __in WPARAM wParam,
    __in LPARAM lParam
    );

INT_PTR CALLBACK OptionsDlgProc(
    __in HWND hwndDlg,
    __in UINT uMsg,
    __in WPARAM wParam,
    __in LPARAM lParam
    );

typedef BOOL (WINAPI *_InternetGetConnectedState)(
    __out LPDWORD lpdwFlags,
    __reserved DWORD dwReserved
    );

#endif