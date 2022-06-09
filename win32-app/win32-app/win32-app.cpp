// win32-app.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "win32-app.h"
#include "draw.cpp"


#define MAX_LOADSTRING 100
TCHAR vl[20], vt[20], vr[20], vb[20];
int top = 0, left = 0, right = 0, bottom = 0;

PAINTSTRUCT ps;
HBRUSH hbrush;
HPEN hpen;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
void addMenu(HWND hwnd);
INT_PTR CALLBACK Input(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Input1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32APP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32APP));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32APP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32APP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        addMenu(hWnd);
    case WM_COMMAND:
        {
            hpen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
            HDC hdc = BeginPaint(hWnd, &ps);
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case 551:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX1), hWnd, Input);
                InvalidateRect(hWnd, NULL, TRUE);
                SelectObject(hdc, hpen);
                Rectangle(hdc, left, top, right, bottom);
                break;
            case 552:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Input);
                InvalidateRect(hWnd, NULL, TRUE);
                hpen = CreatePen(PS_SOLID, 2, RGB(140, 0, 0));
                SelectObject(hdc, hpen); 
                Ellipse(hdc, left, top, right, bottom);
                break;
            case 553:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Input1);
                InvalidateRect(hWnd, NULL, TRUE);
                SelectObject(hdc, hpen);
                Ellipse(hdc, left, top, top, bottom);
                break;
            case 554:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, Input1);
                InvalidateRect(hWnd, NULL, TRUE);
                SelectObject(hdc, hpen);
                Ellipse(hdc, left, top, top, bottom);
                break;
            case 555:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG5), hWnd, Input1);
                InvalidateRect(hWnd, NULL, TRUE);
                SelectObject(hdc, hpen);
                Ellipse(hdc, left, top, top, bottom);
                break; 
            case 556:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6), hWnd, Input1);
                InvalidateRect(hWnd, NULL, TRUE);
                SelectObject(hdc, hpen);
                Ellipse(hdc, left, top, top, bottom);
                break;
            case 557:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG7), hWnd, Input1);
                InvalidateRect(hWnd, NULL, TRUE);
                SelectObject(hdc, hpen);
                Ellipse(hdc, left, top, top, bottom);
                break;
            case 558:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG8), hWnd, Input1);
                InvalidateRect(hWnd, NULL, TRUE);
                SelectObject(hdc, hpen);
                Ellipse(hdc, left, top, top, bottom);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            hpen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
            HDC hdc = BeginPaint(hWnd, &ps);
            int wmId = LOWORD(wParam);
            //draw a rectangle with color blue               
            SelectObject(hdc, hpen);
            Rectangle(hdc, right, top, left, bottom);
            //break;
            //draw a ellipse
            /*hpen = CreatePen(PS_SOLID, 2, RGB(140, 0, 0));
            SelectObject(hdc, hpen);
            Ellipse(hdc, left, top, right, bottom);*/
            //break;
            //Ellipse(hdc, 500, 100, 100, 500);
            //draw a circle
            hpen = CreatePen(PS_SOLID, 2, RGB(140, 0, 0));
            SelectObject(hdc, hpen);
            //Ellipse(hdc, left - right, top + right, right + left, top - right);
            break;
            
                    
            DeleteObject(hpen);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Input(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            GetDlgItemText(hDlg, IDC_EDIT1, vl, sizeof(vl));
            left = _ttoi(vl);
            GetDlgItemText(hDlg, IDC_EDIT2, vt, sizeof(vt));
            top = _ttoi(vt);
            GetDlgItemText(hDlg, IDC_EDIT3, vr, sizeof(vr));
            right = _ttoi(vr);
            GetDlgItemText(hDlg, IDC_EDIT4, vb, sizeof(vb));
            bottom = _ttoi(vb);

            /*OutputDebugString(vl);
            OutputDebugString(vt);
            OutputDebugString(vr);
            OutputDebugString(vb);*/

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Input1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            GetDlgItemText(hDlg, IDC_EDIT1, vl, sizeof(vl));
            left = _ttoi(vl);
            GetDlgItemText(hDlg, IDC_EDIT2, vt, sizeof(vt));
            top = _ttoi(vt);
            GetDlgItemText(hDlg, IDC_EDIT3, vr, sizeof(vr));
            right = _ttoi(vr);

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

HMENU hMenu;
void addMenu(HWND hwnd) {
    hMenu = CreateMenu();
    HMENU miniMenu = CreateMenu();

    AppendMenu(hMenu, MF_STRING, 551, L"Square");
    AppendMenu(hMenu, MF_STRING, 552, L"Rectangle");
    AppendMenu(hMenu, MF_STRING, 553, L"Circle");
    AppendMenu(hMenu, MF_STRING, 554, L"Semi-Circle");
    AppendMenu(hMenu, MF_STRING, 555, L"Ellipse");
    AppendMenu(hMenu, MF_STRING, 556, L"Polygon");
    AppendMenu(hMenu, MF_STRING, 557, L"Triangle");
    AppendMenu(hMenu, MF_STRING, 558, L"Line");
    SetMenu(hwnd, hMenu);
}

void drawSquare() {

}