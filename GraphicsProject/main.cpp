#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>

#include "Lines/LineClipper.h"
#include "utils/UtilityFunctions.cpp"

using namespace std;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[ ] = _T("WindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance,
                    LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;                      /* This is the handle for our window */
    MSG messages{};                 /* Here messages to the application are saved */
    WNDCLASSEX wincl{};             /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (nullptr, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (nullptr, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (nullptr, IDC_ARROW);
    wincl.lpszMenuName = nullptr;              /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("20150239::MahmoudRedaFarouq"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            600,                 /* The programs width */
            600,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            nullptr,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            nullptr                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, nullptr, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*
 * Global Variables to store Values needed for Computation
 */
Shape* currentShape;    // hold current selected shape
Point points[10]; // hold the entered points
int neededNumOfPoints;  // hold the needed number of points to draw current shape
int numOfEnteredPoints;

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps{};
    HDC hdc;
    switch (message) /* handle the messages */
    {
        case WM_CREATE:
        {
            HMENU hmenu = CreateMenu();
            UtilityFunctions::createMenus(hmenu);
            SetMenu(hwnd,hmenu);

            // Init global variables
            currentShape = nullptr;
            for (auto &point : points) {
                point.set(0,0);
            }
            neededNumOfPoints = 0;
            numOfEnteredPoints = 0;
            break;
        }
        case WM_LBUTTONDOWN:
        {
            if(numOfEnteredPoints < neededNumOfPoints)
            {
                points[numOfEnteredPoints].set(LOWORD(lParam), HIWORD(lParam));
                numOfEnteredPoints++;
            }
            if(numOfEnteredPoints >= neededNumOfPoints)
            {
                BeginPaint(hwnd, &ps);
                hdc = GetDC(hwnd);
                if(neededNumOfPoints == 1){
                    UtilityFunctions::GeneralFill(hdc,LOWORD(lParam),HIWORD(lParam),RGB(0,0,255));
                    numOfEnteredPoints = 0;
                    return 0;
                }
                if(currentShape == nullptr) {
                    cout << "currentShape is nullptr" << endl;
                    break;
                }
                currentShape->draw(hdc, points);
                EndPaint(hwnd, &ps);
                numOfEnteredPoints = 0;
            }
            break;
        }
        case WM_COMMAND:
            // on selecting an element from any menu
            BeginPaint(hwnd, &ps);
            hdc = GetDC(hwnd);
            UtilityFunctions::selectionResult(hdc, wParam, currentShape, neededNumOfPoints);
            EndPaint(hwnd, &ps);
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}