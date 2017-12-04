#include "stdafx.h"
#include "DrawToProject2.h"
#include <windows.h>
#include <string> 
#include <Commctrl.h>
#include <iostream>
#include <stdlib.h>
#include <Shellapi.h>
#define ID_TRACKBAR 41231
#pragma comment(lib, "comctl32.lib")


LRESULT CALLBACK windowprocessforwindow1(HWND handleforwindow1, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow2(HWND handleforwindow2, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK windowprocessforwindow3(HWND handleforwindow3, UINT message, WPARAM wParam, LPARAM lParam);
HWND hwndTrack1;
HWND hwndTrack2;
HWND hwndTrack3;
HWND hwndTrack4;
HWND hwndTrack5;
HWND hwndButton1;

//declare Veriables******************************************************************************************************************************
//for windows
bool window1closed = false;
bool window2closed = false;
//for mouse drawing
double LastX, LastY, NowX, NowY;	//GLOBAL VARIABLES used in drawing.
double bottomWin1 = 1;
double rightWin1 = 1;

bool DrawCallibration = false;
bool Draw = false;
//Pen Color
bool RedPen = true;
bool BluePen = false;
bool GreenPen = false;
//add trnsparincy slider and interger, only go from 40%-100%
int transp = 70;
//add button for opening child window
bool childwindow1 = false;
// bool update
bool eraseWindow1 = false;
bool updateWindow2 = false;
bool eraseWindow2 = false;
bool canDraw = false;
//slider multipliers
double slider1 = 75; //make this the same as the start of the slider
double slider1Dev = 10;  // this should match or be reliant to the noches in the slider so like a presentage
double slider2 = 0;
double slider2Dev = 10;  // this should match or be reliant to the noches in the slider so like a presentage
double slider3 = 0;
double slider3Dev = 10;  // this should match or be reliant to the noches in the slider so like a presentage
double slider4 = 0;
double slider4Dev = 10;  // this should match or be reliant to the noches in the slider so like a presentage
double slider5 = 0;
double slider5Dev = 10;  // this should match or be reliant to the noches in the slider so like a presentage



////////////////////////////////////////////////////////////////////////////////////TESTGLOBALVAR
/*
char * buf = 0;
int decimal;
int sign;
int err;

buf = (char*)malloc(_CVTBUFSIZE);
err = _ecvt_s(buf, _CVTBUFSIZE, 1.2, 5, &decimal, &sign);

if (err != 0)
{
	printf("_ecvt_s failed with error code %d\n", err);
	exit(1);
}

printf("Converted value: %s\n", buf);
*/
////////////////////////////////////////////////////////////////////////////////////TESTGLOBALVAR




int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	bool endprogram = false;

	//create window 1

	WNDCLASSEX windowclassforwindow1;
	ZeroMemory(&windowclassforwindow1, sizeof(WNDCLASSEX));
	windowclassforwindow1.cbClsExtra = NULL;
	windowclassforwindow1.cbSize = sizeof(WNDCLASSEX);
	windowclassforwindow1.cbWndExtra = NULL;
	windowclassforwindow1.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclassforwindow1.hCursor = LoadCursor(NULL, IDC_CROSS);
	windowclassforwindow1.hIcon = NULL;
	windowclassforwindow1.hIconSm = NULL;
	windowclassforwindow1.hInstance = hInst;
	windowclassforwindow1.lpfnWndProc = (WNDPROC)windowprocessforwindow1;
	windowclassforwindow1.lpszClassName = L"windowclass 1";
	windowclassforwindow1.lpszMenuName = NULL;
	windowclassforwindow1.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&windowclassforwindow1))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			L"Window class creation failed",
			L"Window Class Failed",
			MB_ICONERROR);
	}

	HWND handleforwindow1 = CreateWindowEx(NULL,
		windowclassforwindow1.lpszClassName,
		L"Draw Window",
		WS_OVERLAPPEDWINDOW,
		350,
		10,
		1080,
		1000,
		NULL,
		NULL,
		hInst,
		NULL                /* No Window Creation data */
		);

	if (!handleforwindow1)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			L"Window creation failed",
			L"Window Creation Failed",
			MB_ICONERROR);
	}

	ShowWindow(handleforwindow1, nShowCmd);
	SetWindowLong(handleforwindow1, GWL_EXSTYLE, GetWindowLong(handleforwindow1, GWL_EXSTYLE) | WS_EX_LAYERED);
	// Make this window 70% alpha
	SetLayeredWindowAttributes(handleforwindow1, 0, (255 * transp) / 100, LWA_ALPHA);
	UpdateWindow(handleforwindow1);

	// create window 2
	
	WNDCLASSEX windowclassforwindow2;
	ZeroMemory(&windowclassforwindow2, sizeof(WNDCLASSEX));
	windowclassforwindow2.cbClsExtra = NULL;
	windowclassforwindow2.cbSize = sizeof(WNDCLASSEX);
	windowclassforwindow2.cbWndExtra = NULL;
	windowclassforwindow2.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclassforwindow2.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowclassforwindow2.hIcon = NULL;
	windowclassforwindow2.hIconSm = NULL;
	windowclassforwindow2.hInstance = hInst;
	windowclassforwindow2.lpfnWndProc = (WNDPROC)windowprocessforwindow2;
	windowclassforwindow2.lpszClassName = L"window class2";
	windowclassforwindow2.lpszMenuName = NULL;
	windowclassforwindow2.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&windowclassforwindow2))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			L"Window class creation failed for window 2",
			L"Window Class Failed",
			MB_ICONERROR);
	}

	HWND handleforwindow2 = CreateWindowEx(NULL,
		windowclassforwindow2.lpszClassName,
		L"Projector Window",
		WS_OVERLAPPEDWINDOW,
		1000,
		150,
		640,
		480,
		NULL,
		NULL,
		hInst,
		NULL); 

	if (!handleforwindow2)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			L"Window creation failed",
			L"Window Creation Failed",
			MB_ICONERROR);
	}

	ShowWindow(handleforwindow2, nShowCmd);
	//SetWindowLong(ChildhWnd, GWL_EXSTYLE, GetWindowLong(ChildhWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	//SetLayeredWindowAttributes(ChildhWnd, OPAQUE, 100, ULW_OPAQUE);
	HBRUSH brush2 = CreateSolidBrush(OPAQUE);
	SetClassLongPtr(handleforwindow2, GCLP_HBRBACKGROUND, (LONG)brush2);
	InvalidateRect(handleforwindow2, 0, TRUE);
	UpdateWindow(handleforwindow2);


	//create window 3

	WNDCLASSEX windowclassforwindow3;
	ZeroMemory(&windowclassforwindow3, sizeof(WNDCLASSEX));
	windowclassforwindow3.cbClsExtra = NULL;
	windowclassforwindow3.cbSize = sizeof(WNDCLASSEX);
	windowclassforwindow3.cbWndExtra = NULL;
	windowclassforwindow3.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowclassforwindow3.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowclassforwindow3.hIcon = NULL;
	windowclassforwindow3.hIconSm = NULL;
	windowclassforwindow3.hInstance = hInst;
	windowclassforwindow3.lpfnWndProc = (WNDPROC)windowprocessforwindow3;
	windowclassforwindow3.lpszClassName = L"window class3";
	windowclassforwindow3.lpszMenuName = MAKEINTRESOURCEW(IDC_DRAWTOPROJECT2);
	windowclassforwindow3.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&windowclassforwindow3))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			L"Window class creation failed for window 3",
			L"Window Class Failed",
			MB_ICONERROR);
	}

	HWND handleforwindow3 = CreateWindowEx(NULL,
		windowclassforwindow3.lpszClassName,
		L"Calibration Settings",
		WS_OVERLAPPEDWINDOW,
		30,
		150,
		320,
		600,
		NULL,
		NULL,
		hInst,
		NULL);

	if (!handleforwindow3)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			L"Window creation failed",
			L"Window Creation Failed",
			MB_ICONERROR);
	}

	ShowWindow(handleforwindow3, nShowCmd);
	UpdateWindow(handleforwindow3);
	

	
	//(handleforwindow2, handleforwindow1);
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (endprogram == false) {
		if (GetMessage(&msg, NULL, 0, 0));
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			
		}
		// have an if veriable = 1 then update the other window... and change that veriable in the first window
		if (updateWindow2 == true)
		{
			InvalidateRect(handleforwindow2, 0, FALSE);
			
		} else {}
		if (eraseWindow2 == true)
		{
			InvalidateRect(handleforwindow2, 0, TRUE);

		} else {}
		if (eraseWindow1 == true)
		{
			InvalidateRect(handleforwindow1, 0, TRUE);

		}
		else {}

		if (window1closed == true)    //&& window2closed == true) { //has an or statment
		{
			endprogram = true;
		}



		//this probalbly makes it crash more
		//updateWindow = true;
		// why do you crash after a certian amount of line i drawn? maybe redo lines to be more stable.
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////TRACKBAR STUFF
//Scaling
HWND WINAPI CreateTrackbar1(
	HWND hwndDlg,  // handle of dialog box (parent window) 
	UINT iMin,     // minimum value in trackbar range 
	UINT iMax,     // maximum value in trackbar range 
	UINT iSelMin,  // minimum value in trackbar selection 
	UINT iSelMax, // maximum value in trackbar selection 
	UINT XPOS,    // x position
	UINT YPOS,    // y position
	UINT XSIZE,   // x size
	UINT YSIZE,   // y size
	UINT style1,		 // orientation TBS_VERT or TBS_HORZ
	UINT variable   //what variable a 32 int
	)
{ 

	InitCommonControls(); // loads common control's DLL 

	hwndTrack1 = CreateWindowEx(
		NULL,                               // no extended styles 
		TRACKBAR_CLASS,                  // class name 
		L"Trackbar Control",              // title (caption) 
		WS_CHILD |
		WS_VISIBLE |
		TBS_AUTOTICKS |
		TBS_TOOLTIPS |
		TBS_BOTH |
		style1,                  // style 
		XPOS, YPOS,                          // position 
		XSIZE, YSIZE,                         // size 
		hwndDlg,                         // parent window 
		(HMENU)ID_TRACKBAR,                     // control identifier 
		GetModuleHandle(NULL),               // instance 
		NULL                             // no WM_CREATE parameter 
		);
	DWORD dwPos;     // current position of slider 
	//dwPos = SendMessage(hwndTrack, TBM_GETPOS, 0, 0);
	SendMessage(hwndTrack1, TBM_SETRANGE,
		(WPARAM)TRUE,                   // redraw flag 
		(LPARAM)MAKELONG(iMin, iMax));  // min. & max. positions

	SendMessage(hwndTrack1, TBM_SETPAGESIZE,
		0, (LPARAM)4);                  // new page size 

	SendMessage(hwndTrack1, TBM_SETSEL,
		(WPARAM)FALSE,                  // redraw flag 
		(LPARAM)MAKELONG(iSelMin, iSelMax));

	SendMessage(hwndTrack1, TBM_SETPOS,
		(WPARAM)TRUE,                   // redraw flag 
		(LPARAM)iSelMin);
	SendMessage(hwndTrack1, TBM_SETTICFREQ, 25, 0);
	SetFocus(hwndTrack1);
	return hwndTrack1;
}
//X position
HWND WINAPI CreateTrackbar2(
	HWND hwndDlg,  // handle of dialog box (parent window) 
	UINT iMin,     // minimum value in trackbar range 
	UINT iMax,     // maximum value in trackbar range 
	UINT iSelMin,  // minimum value in trackbar selection 
	UINT iSelMax, // maximum value in trackbar selection 
	UINT XPOS,    // x position
	UINT YPOS,    // y position
	UINT XSIZE,   // x size
	UINT YSIZE,   // y size
	UINT style1,		 // orientation TBS_VERT or TBS_HORZ
	UINT variable   //what variable a 32 int
)
{

	InitCommonControls(); // loads common control's DLL 

	hwndTrack2 = CreateWindowEx(
		NULL,                               // no extended styles 
		TRACKBAR_CLASS,                  // class name 
		L"Trackbar Control",              // title (caption) 
		WS_CHILD |
		WS_VISIBLE |
		TBS_AUTOTICKS |
		TBS_TOOLTIPS |
		TBS_BOTH |
		style1,                  // style 
		XPOS, YPOS,                          // position 
		XSIZE, YSIZE,                         // size 
		hwndDlg,                         // parent window 
		(HMENU)ID_TRACKBAR,                     // control identifier 
		GetModuleHandle(NULL),               // instance 
		NULL                             // no WM_CREATE parameter 
	);
	DWORD dwPos;     // current position of slider 
					 //dwPos = SendMessage(hwndTrack, TBM_GETPOS, 0, 0);
	SendMessage(hwndTrack2, TBM_SETRANGE,
		(WPARAM)TRUE,                   // redraw flag 
		(LPARAM)MAKELONG(iMin, iMax));  // min. & max. positions

	SendMessage(hwndTrack2, TBM_SETPAGESIZE,
		0, (LPARAM)4);                  // new page size 

	SendMessage(hwndTrack2, TBM_SETSEL,
		(WPARAM)FALSE,                  // redraw flag 
		(LPARAM)MAKELONG(iSelMin, iSelMax));

	SendMessage(hwndTrack2, TBM_SETPOS,
		(WPARAM)TRUE,                   // redraw flag 
		(LPARAM)iSelMin);
	SendMessage(hwndTrack2, TBM_SETTICFREQ, 25, 0);
	SetFocus(hwndTrack2);
	return hwndTrack2;
}
// Y position
HWND WINAPI CreateTrackbar3(
	HWND hwndDlg,  // handle of dialog box (parent window) 
	UINT iMin,     // minimum value in trackbar range 
	UINT iMax,     // maximum value in trackbar range 
	UINT iSelMin,  // minimum value in trackbar selection 
	UINT iSelMax, // maximum value in trackbar selection 
	UINT XPOS,    // x position
	UINT YPOS,    // y position
	UINT XSIZE,   // x size
	UINT YSIZE,   // y size
	UINT style1,		 // orientation TBS_VERT or TBS_HORZ
	UINT variable   //what variable a 32 int
)
{

	InitCommonControls(); // loads common control's DLL 

	hwndTrack3 = CreateWindowEx(
		NULL,                               // no extended styles 
		TRACKBAR_CLASS,                  // class name 
		L"Trackbar Control",              // title (caption) 
		WS_CHILD |
		WS_VISIBLE |
		TBS_AUTOTICKS |
		TBS_TOOLTIPS |
		TBS_BOTH |
		style1,                  // style 
		XPOS, YPOS,                          // position 
		XSIZE, YSIZE,                         // size 
		hwndDlg,                         // parent window 
		(HMENU)ID_TRACKBAR,                     // control identifier 
		GetModuleHandle(NULL),               // instance 
		NULL                             // no WM_CREATE parameter 
	);
	DWORD dwPos;     // current position of slider 
					 //dwPos = SendMessage(hwndTrack, TBM_GETPOS, 0, 0);
	SendMessage(hwndTrack3, TBM_SETRANGE,
		(WPARAM)TRUE,                   // redraw flag 
		(LPARAM)MAKELONG(iMin, iMax));  // min. & max. positions

	SendMessage(hwndTrack3, TBM_SETPAGESIZE,
		0, (LPARAM)4);                  // new page size 

	SendMessage(hwndTrack3, TBM_SETSEL,
		(WPARAM)FALSE,                  // redraw flag 
		(LPARAM)MAKELONG(iSelMin, iSelMax));

	SendMessage(hwndTrack3, TBM_SETPOS,
		(WPARAM)TRUE,                   // redraw flag 
		(LPARAM)iSelMin);
	SendMessage(hwndTrack3, TBM_SETTICFREQ, 25, 0); //sets the tick frequiency
	SetFocus(hwndTrack3);
	return hwndTrack3;
}
//keystone Top
HWND WINAPI CreateTrackbar4(
	HWND hwndDlg,  // handle of dialog box (parent window) 
	UINT iMin,     // minimum value in trackbar range 
	UINT iMax,     // maximum value in trackbar range 
	UINT iSelMin,  // minimum value in trackbar selection 
	UINT iSelMax, // maximum value in trackbar selection 
	UINT XPOS,    // x position
	UINT YPOS,    // y position
	UINT XSIZE,   // x size
	UINT YSIZE,   // y size
	UINT style1,		 // orientation TBS_VERT or TBS_HORZ
	UINT variable   //what variable a 32 int
)
{

	InitCommonControls(); // loads common control's DLL 

	hwndTrack4 = CreateWindowEx(
		NULL,                               // no extended styles 
		TRACKBAR_CLASS,                  // class name 
		L"Trackbar Control",              // title (caption) 
		WS_CHILD |
		WS_VISIBLE |
		TBS_AUTOTICKS |
		TBS_TOOLTIPS |
		TBS_BOTH |
		style1,                  // style 
		XPOS, YPOS,                          // position 
		XSIZE, YSIZE,                         // size 
		hwndDlg,                         // parent window 
		(HMENU)ID_TRACKBAR,                     // control identifier 
		GetModuleHandle(NULL),               // instance 
		NULL                             // no WM_CREATE parameter 
	);
	DWORD dwPos;     // current position of slider 
					 //dwPos = SendMessage(hwndTrack, TBM_GETPOS, 0, 0);
	SendMessage(hwndTrack4, TBM_SETRANGE,
		(WPARAM)TRUE,                   // redraw flag 
		(LPARAM)MAKELONG(iMin, iMax));  // min. & max. positions

	SendMessage(hwndTrack4, TBM_SETPAGESIZE,
		0, (LPARAM)4);                  // new page size 

	SendMessage(hwndTrack4, TBM_SETSEL,
		(WPARAM)FALSE,                  // redraw flag 
		(LPARAM)MAKELONG(iSelMin, iSelMax));

	SendMessage(hwndTrack4, TBM_SETPOS,
		(WPARAM)TRUE,                   // redraw flag 
		(LPARAM)iSelMin);
	SendMessage(hwndTrack4, TBM_SETTICFREQ, 25, 0); //sets the tick frequiency
	SetFocus(hwndTrack4);
	return hwndTrack4;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////TRACKBAR END
//////////////////////////////////////////////////////////////////////////////////////////////////////////////Button Stuff

HWND WINAPI CreateButton1(
	HWND hwndDlg,  // handle of dialog box (parent window) 
	UINT XPOS,    // x position
	UINT YPOS,    // y position
	UINT XSIZE,   // x size
	UINT YSIZE   // y size
	)
{
	hwndButton1 = CreateWindow(
		L"BUTTON",  // Predefined class; Unicode assumed 
		L"Toggle Calibration",      // Button text 
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // Styles 
		XPOS,         // x position 
		YPOS,         // y position 
		XSIZE,        // Button width
		YSIZE,        // Button height
		hwndDlg,     // Parent window
		NULL,       // No menu.
		(HINSTANCE)GetWindowLong(hwndDlg, GWLP_HINSTANCE),
		NULL);      // Pointer not needed.
	
	return hwndButton1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////Button End

LRESULT CALLBACK windowprocessforwindow1(HWND handleforwindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	/*if (eraseWindow2 == true)
	{
		//UpdateWindow(handleforwindow2);
		InvalidateRect(handleforwindow, 0, TRUE);
	}
	else
	{

	}*/
	//get the dimentions of each window to use the aspect ratio
	RECT rectwind;
	GetClientRect(handleforwindow, &rectwind);    //GetWindowRect-gets the window of the desktop, not client area, use GetClientrect
	double Left = rectwind.left;
	double Right = rectwind.right;
	double Top = rectwind.top;
	double Bottom = rectwind.bottom;
	//make the right and bottom equal to global veriables

	bottomWin1 = Bottom;
	rightWin1 = Right; // multiplied by someting in the sliders in the sliders of window 3


	switch (msg)
	{
	case WM_CREATE:
	{
		
	}
	break;
	case WM_SIZING:
	{
		eraseWindow2 = true;
	}
	break;
	//mouse move
	case WM_MOUSEMOVE:
	{
		
		// change to a veriable
		if (canDraw == true){
		//if (GetKeyState(VK_LBUTTON) != 0) {
			updateWindow2 = true;
			//use LastX diferently
			//LastX = LOWORD(lParam);
			//LastY = HIWORD(lParam);
			NowX = LOWORD(lParam);
			NowY = HIWORD(lParam);
			InvalidateRect(handleforwindow, 0, FALSE);
			

		}
		else
		{
			NowX == NowX;
			NowY == NowY;
			updateWindow2 = false;
		}
	}
	break;
	//left mouse button
	case WM_LBUTTONDOWN:
	{
		if (canDraw == true) {
			canDraw = false;
			break;
		}
		else
		{}
		if (canDraw == false) {
			canDraw = true;
			break;
		}
		else
		{}
	}
	break;
	//right mouse button
	case WM_RBUTTONDOWN:
	{
		LastX = -10;  //needed because the last line drawn is kept, so draw last line off screen
		LastY = -10;
		NowX = -10;
		NowY = -10;
		InvalidateRect(handleforwindow, 0, TRUE); // gets rid of al lines except last drawn
		eraseWindow2 = true;

		//invalidare is left out because what if user accidentily clicks before maker is done????
		//InvalidateRect(ChildhWnd, 0, TRUE); // gets rid of al lines except last drawn
		//SendMessage(wind2,InvalidateRect(handleforwindow, 0, TRUE), wParam, lParam);
	}
	break;
	//use slide wheel or up and down arrows to set transparency
	case WM_MOUSEWHEEL:
	{
		transp += GET_WHEEL_DELTA_WPARAM(wParam);
		SetLayeredWindowAttributes(handleforwindow, 0, (255 * transp) / 100, LWA_ALPHA);
		UpdateWindow(handleforwindow);
	}
	break;
	//use arrow keys to do transparensy

	case WM_KEYDOWN:
	{
		if (VK_UP)
		{
			transp += 10;
			SetLayeredWindowAttributes(handleforwindow, 0, (255 * transp) / 100, LWA_ALPHA);
			UpdateWindow(handleforwindow);
		}
		//for some strange reason dosent work
		/*if (VK_DOWN)
		{
			transp -= 10;
			SetLayeredWindowAttributes(handleforwindow, 0, (255 * transp) / 100, LWA_ALPHA);
			UpdateWindow(handleforwindow);
		}*/
		
	}
	break;

	//menu options
	case WM_COMMAND:
	{
		
	}
	break;

	//DrawStuff
	case WM_PAINT:
	{
		//Paint stuff
		HDC     hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(handleforwindow, &ps);
		HPEN hPenOld;
		HPEN hLinePen;
		COLORREF qLineColor;
		//conneded to chose color
		if (RedPen) { qLineColor = RGB(255, 0, 0); }
		if (BluePen) { qLineColor = RGB(0, 0, 225); }
		if (GreenPen) { qLineColor = RGB(0, 225, 0); }

		hLinePen = CreatePen(PS_SOLID, 5, qLineColor);
		hPenOld = (HPEN)SelectObject(hDC, hLinePen);

		// Paint
		MoveToEx(hDC, NowX, NowY, NULL);
		LineTo(hDC, NowX, NowY);


		//after dwawing save the LastX as the NowX and noxt time the finction is un draw line from the lastX to the now.

		if (DrawCallibration) {
			// Draw a blue ellipse
			HPEN hEllipsePen;
			COLORREF qEllipseColor;
			qEllipseColor = RGB(0, 255, 0);
			hEllipsePen = CreatePen(PS_SOLID, 3, qEllipseColor);
			hPenOld = (HPEN)SelectObject(hDC, hEllipsePen);

			//upper left cross
			MoveToEx(hDC, Right * 1 /8, Bottom * 1/4, NULL);
			LineTo(hDC, Right * 3/8, Bottom *1 / 4);
			MoveToEx(hDC, Right * 1 / 4, Bottom * 1 / 8, NULL);
			LineTo(hDC, Right * 1 / 4, Bottom * 3 / 8);
			//upper right cross
			MoveToEx(hDC, Right * 5 / 8, Bottom * 1 / 4, NULL);
			LineTo(hDC, Right * 7 / 8, Bottom * 1 / 4);
			MoveToEx(hDC, Right * 3 / 4, Bottom * 1 / 8, NULL);
			LineTo(hDC, Right * 3 / 4, Bottom * 3 / 8);
			//lower left cross
			MoveToEx(hDC, Right * 1 / 8, Bottom * 3 / 4, NULL);
			LineTo(hDC, Right * 3 / 8, Bottom * 3 / 4);
			MoveToEx(hDC, Right * 1 / 4, Bottom * 5 / 8, NULL);
			LineTo(hDC, Right * 1 / 4, Bottom * 7 / 8);
			//lower right cross
			MoveToEx(hDC, Right * 5 / 8, Bottom * 3 / 4, NULL);
			LineTo(hDC, Right * 7 / 8, Bottom * 3 / 4);
			MoveToEx(hDC, Right * 3 / 4, Bottom * 5 / 8, NULL);
			LineTo(hDC, Right * 3 / 4, Bottom * 7 / 8);
			//middle clircles
			Arc(hDC, Right * 1/3, Bottom * 1/3, Right * 2/3, Bottom * 2/3, 0, 0, 0, 0);
			Arc(hDC, Right * 15/32, Bottom * 15/32, Right * 17/32, Bottom * 17/32, 0, 0, 0, 0); 
			MoveToEx(hDC, Right * 1/2, Bottom * 1 / 4, NULL);
			LineTo(hDC, Right * 1/2, Bottom * 3 / 4);
			MoveToEx(hDC, Right * 1/4, Bottom *1/2, NULL);
			LineTo(hDC, Right * 3/4 , Bottom * 1/2);

			SelectObject(hDC, hPenOld);
			DeleteObject(hEllipsePen);
		}


		EndPaint(handleforwindow, &ps);
		eraseWindow1 = false;
		return 0;
	}
	break;
	case WM_CLOSE:
		if (MessageBox(handleforwindow, L"Close all windows of application?", L"Quit", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(handleforwindow);
		}
		// Else: User canceled. Do nothing.
		return 0;
	case WM_DESTROY: {
		window2closed = true;
		window1closed = true;
		return 0;
	}
					 break;
	}
	return DefWindowProc(handleforwindow, msg, wParam, lParam);
}
//Window2*ChildWindow*********************************************************************************************************************************
LRESULT CALLBACK windowprocessforwindow2(HWND handleforwindow2, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//get the window one ratio of width to height, say 1/3 x/y and then apply that height to the second window???
	
	/*if (updateWindow2 == true)
	{
		//UpdateWindow(handleforwindow2);
		InvalidateRect(handleforwindow2, 0, FALSE);
	}
	else
	{

	}
	if (eraseWindow2 == true)
	{
		//UpdateWindow(handleforwindow2);
		InvalidateRect(handleforwindow2, 0, TRUE);
	}
	else
	{

	}*/

	//get the dimentions of each window to use the aspect ratio
	RECT rectwind;
	GetClientRect(handleforwindow2, &rectwind);    //GetWindowRect-gets the window of the desktop, not client area, use GetClientrect
	double Left = rectwind.left;
	double Right = rectwind.right;
	double Top = rectwind.top;
	double Bottom = rectwind.bottom;

	
	
	//scale
	double win2ScaleX = (slider1 / 100)* (Bottom / bottomWin1) ; //(Bottom / bottomWin1) <- do after to scale to window, since height is usualy shorter that width on monitor?
	double win2ScaleY =  (slider1 / 100)* (Bottom / bottomWin1); //^^^
	//offset
	double offsetX = slider2 * Right/100;  // this value should be double what the slider has
	double offsetY = slider3 * Bottom/100;  //^^^

	//center it
	double centerX = (Right / 2 - rightWin1 / 2 * (slider1 / 100) * (Bottom / bottomWin1)); //remember to also scale to the window like win2ScaleY
	double centerY = (Bottom / 2 - bottomWin1 / 2 * (slider1 / 100) * (Bottom / bottomWin1));
	//keystone for pen
	double keystoneY = (slider4/50 * (NowY) / bottomWin1); //used in scale
	double keystoneYY = -(slider4 / 50 * (NowY)) * (Bottom / bottomWin1);



	switch (msg)
	{


	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(handleforwindow2, &ps);
		HPEN hPen;
		HPEN linePen2;
		COLORREF qLineColor;
		qLineColor = RGB(0, 0, 255);
				
		if (RedPen) { qLineColor = RGB(255, 0, 0); }
		if (BluePen) { qLineColor = RGB(0, 0, 225); }
		if (GreenPen) { qLineColor = RGB(0, 225, 0); }

		//TextOut(hdc, LastX, 10, _T("Test"), 6); //to test if LastX works

		// Paint
		linePen2 = CreatePen(PS_SOLID, 5, qLineColor);
		hPen = (HPEN)SelectObject(hdc, linePen2);
		
		//it works but is not ratioed
		//MoveToEx(hdc, LastX, LastY, NULL);
		//LineTo(hdc, LastX , LastY);

		// maybe set a global veriable for the win2ScaleX, and win2ScaleY


		//use floats or doubles
		MoveToEx(hdc, (NowX  * win2ScaleX + offsetX + centerX) + NowY/slider4  , NowY * win2ScaleY + offsetY + centerY, NULL); // rightWin1 * Right  // bottomWin1 *Bottom  // win2ScaleY + offsetY
		LineTo(hdc, (NowX  * win2ScaleX + offsetX + centerX) + NowY/slider4 , NowY * win2ScaleY + offsetY + centerY);
		//the 10 could be the slider devider and be subtracted from the slider in the first place to end up at 1
		
		if (DrawCallibration) {
			// Draw a blue ellipse
			// the picture's height 0-7.25
			// the pictures width 0-7.25
			// dots from bottom are 1.85
			// dots from left and right are 2.5


			HPEN hEllipsePen;
			COLORREF qEllipseColor;
			qEllipseColor = RGB(0, 255, 0);
			hEllipsePen = CreatePen(PS_SOLID, 3/slider1, qEllipseColor);
			hPen = (HPEN)SelectObject(hdc, hEllipsePen);

			//upper left cross
			//upper right cross
			//lower left cross
			//lower right cross
			

			// ((line dementions) * scale + offset + center )
			//upper left cross
			MoveToEx(hdc, rightWin1 * 1 / 8 * win2ScaleX + offsetX + centerX, bottomWin1 * 1 / 4 * win2ScaleY + offsetY + centerY, NULL);
			LineTo(hdc, rightWin1 * 3 / 8 * win2ScaleX + offsetX + centerX, bottomWin1 * 1 / 4 * win2ScaleY + offsetY + centerY);
			MoveToEx(hdc, rightWin1 * 1 / 4 * win2ScaleX + offsetX + centerX, bottomWin1 * 1 / 8 * win2ScaleY + offsetY + centerY, NULL);
			LineTo(hdc, rightWin1 * 1 / 4 * win2ScaleX + offsetX + centerX, bottomWin1 * 3 / 8 * win2ScaleY + offsetY + centerY);
			//upper right cross
			MoveToEx(hdc, rightWin1 * 5 / 8 * win2ScaleX + offsetX + centerX, bottomWin1 * 1 / 4 * win2ScaleY + offsetY + centerY, NULL);
			LineTo(hdc, rightWin1 * 7 / 8 * win2ScaleX + offsetX + centerX, bottomWin1 * 1 / 4 * win2ScaleY + offsetY + centerY);
			MoveToEx(hdc, rightWin1 * 3 / 4 * win2ScaleX + offsetX + centerX, bottomWin1 * 1 / 8 * win2ScaleY + offsetY + centerY, NULL);
			LineTo(hdc, rightWin1 * 3 / 4 * win2ScaleX + offsetX + centerX, bottomWin1 * 3 / 8 * win2ScaleY + offsetY + centerY);
			//lower left cross
			MoveToEx(hdc, rightWin1 * 1 / 8 * win2ScaleX + offsetX + centerX, bottomWin1 * 3 / 4 * win2ScaleY + offsetY + centerY, NULL);
			LineTo(hdc, rightWin1 * 3 / 8 * win2ScaleX + offsetX + centerX, bottomWin1 * 3 / 4 * win2ScaleY + offsetY + centerY);
			MoveToEx(hdc, rightWin1 * 1 / 4 * win2ScaleX + offsetX + centerX, bottomWin1 * 5 / 8 * win2ScaleY + offsetY + centerY, NULL);
			LineTo(hdc, rightWin1 * 1 / 4 * win2ScaleX + offsetX + centerX, bottomWin1 * 7 / 8 * win2ScaleY + offsetY + centerY);
			//lower left cross
			MoveToEx(hdc, rightWin1 * 5 / 8 * win2ScaleX + offsetX + centerX, bottomWin1 * 3 / 4 * win2ScaleY + offsetY + centerY, NULL);
			LineTo(hdc, rightWin1 * 7 / 8 * win2ScaleX + offsetX + centerX, bottomWin1 * 3 / 4 * win2ScaleY + offsetY + centerY);
			MoveToEx(hdc, rightWin1 * 3 / 4 * win2ScaleX + offsetX + centerX, bottomWin1 * 5 / 8 * win2ScaleY + offsetY + centerY, NULL);
			LineTo(hdc, rightWin1 * 3 / 4 * win2ScaleX + offsetX + centerX, bottomWin1 * 7 / 8 * win2ScaleY + offsetY + centerY);
			//middle circle and cross
			Arc(hdc, rightWin1 * 1 / 3 * win2ScaleX + offsetX + centerX, bottomWin1 * 1 / 3 * win2ScaleY + offsetY + centerY,
				rightWin1 * 2 / 3 * win2ScaleX + offsetX + centerX, bottomWin1 * 2 / 3 * win2ScaleY + offsetY + centerY, 0, 0, 0, 0);
			Arc(hdc, rightWin1 * 15 / 32 * win2ScaleX + offsetX + centerX, bottomWin1 * 15 / 32 * win2ScaleY + offsetY + centerY,
				rightWin1 * 17 / 32 * win2ScaleX + offsetX + centerX, bottomWin1 * 17 / 32 * win2ScaleY + offsetY + centerY, 0, 0, 0, 0);
			MoveToEx(hdc, rightWin1 * 1 / 2 * win2ScaleX + offsetX + centerX, bottomWin1 * 1 / 4 * win2ScaleY + offsetY + centerY, NULL);
			LineTo(hdc, rightWin1 * 1 / 2 * win2ScaleX + offsetX + centerX, bottomWin1 * 3 / 4 * win2ScaleY + offsetY + centerY);
			MoveToEx(hdc, rightWin1 * 1 / 4 * win2ScaleX + offsetX + centerX, bottomWin1 * 1 / 2 * win2ScaleY + offsetY + centerY, NULL);
			LineTo(hdc, rightWin1 * 3 / 4 * win2ScaleX + offsetX + centerX, bottomWin1 * 1 / 2 * win2ScaleY + offsetY + centerY);
			//make the box make brush transparent so box does not fill
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Rectangle(hdc, (0)* win2ScaleX + offsetX + centerX
				, 0 * win2ScaleY + offsetY + centerY
				, (rightWin1)* win2ScaleX + offsetX + centerX
				, bottomWin1 * win2ScaleY + offsetY + centerY
				);


			//MoveToEx(hdc, 100 + slider1 * 10 ,slider1Dev, NULL);
			//LineTo(hdc, 200 + slider1, slider1Dev *0.75);
			

			SelectObject(hdc, hPen);
			DeleteObject(hEllipsePen);
			
		}

		EndPaint(handleforwindow2, &ps);
		updateWindow2 = false;
		eraseWindow2 = false;
		return 0;
	}
	break;
	case WM_CLOSE:
		if (MessageBox(handleforwindow2, L"Close all windows of application?", L"Quit", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(handleforwindow2);
		}
		// Else: User canceled. Do nothing.
		return 0;
	case WM_DESTROY: {
		window2closed = true;
		window1closed = true;
		return 0;
	}
					 break;
	}

	return DefWindowProc(handleforwindow2, msg, wParam, lParam);
}

//Window3*CalibrationSettings*********************************************************************************************************************************
LRESULT CALLBACK windowprocessforwindow3(HWND handleforwindow3, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	/*HWND hwndDlg,  // handle of dialog box (parent window) 
	HWND hwndDlg,  // handle of dialog box (parent window) 
	UINT iMin,     // minimum value in trackbar range        
	UINT iMax,     // maximum value in trackbar range         //make relivant to the slider_Dev global veriable
	UINT iSelMin,  // minimum value in trackbar selection 
	UINT iSelMax, // maximum value in trackbar selection 
	UINT XPOS,    // x position
	UINT YPOS,    // y position
	UINT XSIZE,   // x size
	UINT YSIZE,   // y size
	UINT style1,	 // orientation TBS_VERT or TBS_HORZ
	UINT startPos,  //the starting position usualy 0
	UINT variable   //what variable a 32 int
	*/

	

	switch (msg)
	{
	case WM_CREATE:
	{
		//maybe makt the pen really wide to compensate for the shear?

		//now just create trackbars to make values and do things
		//make slider from 0-1000 not 100
		CreateTrackbar1(handleforwindow3, 1, 100, slider1, 0, 10, 30, 250, 50, TBS_HORZ, slider1); //for laser scaling
		CreateTrackbar2(handleforwindow3, -50, 50, 0, 0, 10, 150, 150, 50, TBS_HORZ, slider2); //for laser X position
		CreateTrackbar3(handleforwindow3, -50, 50, 0, 0, 230, 90, 50, 150, TBS_VERT, slider3); //for laser Y position
		CreateTrackbar4(handleforwindow3, -50, 50, 0, 0, 10, 280, 250, 50, TBS_HORZ, slider4); //for keystone top
		//CreateTrackbar5(handleforwindow3, -50, 50, 0, 0, 10, 330, 250, 50, TBS_HORZ, slider5); //for keystone bottom
		
		//Cheakbox for calibration
		CreateButton1(handleforwindow3, 10, 420, 160,50);

		return 0;
	}
	break;
	case WM_HSCROLL:
	{ 
		slider1 = SendMessage(hwndTrack1, TBM_GETPOS, 0, 0); //Used to total scaling
		slider2 = SendMessage(hwndTrack2, TBM_GETPOS, 0, 0); //Used to X offset
		slider4 = SendMessage(hwndTrack4, TBM_GETPOS, 0, 0); //Keystoning
		
		eraseWindow2 = true; //updates the 2nd window

		
	}
	break;
	case WM_VSCROLL:
	{
		slider3 = SendMessage(hwndTrack3, TBM_GETPOS, 0, 0); //Used to Y offset
		eraseWindow2 = true; //updates the 2nd window
	}
	
	break;
	case WM_COMMAND:
	{
		if (GetFocus() == hwndButton1 ) {
			DrawCallibration = !DrawCallibration;
			eraseWindow2 = true;
			eraseWindow1 = true;
			SetFocus(handleforwindow3);
		}
	//	button1State = SendMessage(hwndButton1, BM_GETSTATE, 0, 0);
		//DrawCallibration = button1State;
		
		//SendMessage(hwndButton1, BM_SETSTATE, DrawCallibration, 0);   // use only for cheackboxes
		  // BST_PUSHED
		/*
		if (BN_PUSHED)
		{
			if (hwndButton1) {
				DrawCallibration = !DrawCallibration;
				//SendMessage(hwndButton1, BM_SETSTATE, !DrawCallibration, 0);   // use only for cheackboxes
				//DrawCallibration = SendMessage(hwndButton1, BM_GETSTATE, 0, 0);  // BST_PUSHED
				eraseWindow2 = true;
				eraseWindow1 = true;
				break;
			}
					
		}
		return 0;
		*/


		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
			
		case IDM_RED:
			RedPen = true;
			GreenPen = false;
			BluePen = false;
			break;
		case IDM_BLUE:
			RedPen = false;
			GreenPen = false;
			BluePen = true;
			break;
		case IDM_GREEN:
			RedPen = false;
			GreenPen = true;
			BluePen = false;
			break;
			//MENU stuff
		case IDM_EXIT:
			DestroyWindow(handleforwindow3);
			break;
		case IDM_OPENIMAGE:
			ShellExecute(NULL, L"open", L"C:", NULL, NULL, SW_SHOWDEFAULT); //have this open and import the bitmap, or use a commaned to directly open it
			break;
		case IDM_ELLIPSE:
			eraseWindow2 = true;
			eraseWindow1 = true;
			DrawCallibration = !DrawCallibration;
			//InvalidateRect(handleforwindow3, 0, TRUE); //might be set to false depending 
													  //updateWindow = false;
			break;
		case IDM_HOWTO:
			::MessageBox(NULL, _T("Move the black window onto the projector and maximize. \n Do claibrations. \n'Right-Click' and release to Draw. \n 'Right-Click' again to Stop Drawing. \n 'Left-Click to Erase All. \n Scroll 'Mouse Wheel' or use 'up' arrow to set Transparency.\n (Pen Color) to set Pen Color. \n(File -> Exit) to Exit"), _T("How To:"), MB_OK | MB_ICONQUESTION);
			break;
		case IDM_HOWTOCAL:
			::MessageBox(NULL, _T("(Calibrate -> Calibration Ellipse) \n Using the Transparent window: \n 1) Resize the window to fit the image capure from camera and overlay. \n \n Using Calibration Tools: \n 1) Line up screen image with projector image over the live camera capture."), _T("How To Calibrate:"), MB_OK | MB_ICONQUESTION);
			break;
		default:
			return DefWindowProc(handleforwindow3, msg, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(handleforwindow3, &ps);
		HPEN hPen;
		COLORREF qLineColor;
		qLineColor = RGB(0, 0, 255);
		SetBkColor(hdc, RGB(221, 231, 255));   // the color of the background of the text
		//text that goes on the screen
		TextOut(hdc, 10, 10, _T("Step 1: Scale"), 13);
		TextOut(hdc, 10, 90, _T("Step 2: Offset Position"), 23);
		TextOut(hdc, 10, 260, _T("Step 3: Keystone coming soon"), 29); //33 ''Trapezoiding''

		TextOut(hdc, 10, 350, _T("Quick How To:"), 13); 
		TextOut(hdc, 10, 370, _T("1) click to toggle draw"), 23); 
		TextOut(hdc, 10, 390, _T("2) Move black screen to projector"), 33); 
		//lines that devide the bars
		MoveToEx(hdc, 0 , 80, NULL);
		LineTo(hdc, 10000, 80);
		MoveToEx(hdc, 0, 250, NULL);
		LineTo(hdc, 10000, 250);
		MoveToEx(hdc, 0, 345, NULL);
		LineTo(hdc, 10000, 345);
		MoveToEx(hdc, 0, 415, NULL);
		LineTo(hdc, 10000, 415);
		
		return 0;
	}
	break;
	case WM_CLOSE:
		if (MessageBox(handleforwindow3, L"Close all windows of application?", L"Quit", MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(handleforwindow3);
		}
		// Else: User canceled. Do nothing.
		return 0;
	case WM_DESTROY: {
		window2closed = true;
		window1closed = true;
		return 0;
	}
					 break;
}

return DefWindowProc(handleforwindow3, msg, wParam, lParam);
}

