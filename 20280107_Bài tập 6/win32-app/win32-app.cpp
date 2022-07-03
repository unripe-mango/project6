// win32-app.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "win32-app.h"
#include "my_project.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <cstring>
#include <atlstr.h>

#ifdef UNICODE
typedef std::wostringstream tstringstream;
#else
typedef std::ostringstream tstringstream;
#endif

//#include <objidl.h>

//#pragma comment (lib,"Gdiplus.lib")


//VOID OnPaint(HDC hdc)
//{
//    Pen      pen(Color(255, 0, 0, 255));
// tutorial/Screenshot 2022-06-24 003807.jpgtutorial/Screenshot 2022-06-24 003807.jpg
//    graphics.DrawLine(&pen, 100, 100, 500, 500);
//}

#define MAX_LOADSTRING 100
TCHAR vl[20], vt[20], vr[20], vb[20], vd[20], ve[20];
vector<myFigure*> figure;
myLine line = myLine(0, 0, 0, 0);
 
PAINTSTRUCT ps;
HBRUSH hbrush;
HPEN hpen;
HPEN rpen;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
void addMenu(HWND hwnd);

INT_PTR CALLBACK Input_R(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Input_C(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Input_E(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Input_S(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Input_P(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Input_T(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK Input_L(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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
    /*static Ellipse e(500, 300, 200, 100);
    static Circle c(500, 300, 200);
    static Point t(400, 300);
    WCHAR msg[][50] = { L"Outside",L"Inside" };*/
    switch (message)
    {
    case WM_CREATE:
        addMenu(hWnd);
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            ////Square - Rectangle - Circle - Semi-Circle - Ellipse - Polygon - Triangle - Line 
            case 551:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX1), hWnd, Input_R);
                InvalidateRect(hWnd, NULL, TRUE);
            break; 
            case 552:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Input_R);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case 553:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Input_C);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case 554:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, Input_S);
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            case 555:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG5), hWnd, Input_E);
                InvalidateRect(hWnd, NULL, TRUE);
                break; 
            case 556:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG6), hWnd, Input_P);
                InvalidateRect(hWnd, NULL, TRUE);
                break; 
            case 557:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG7), hWnd, Input_T);
                InvalidateRect(hWnd, NULL, TRUE);
            break; 
            case 558:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG8), hWnd, Input_L);
                InvalidateRect(hWnd, NULL, TRUE);
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
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            hpen = CreatePen(PS_SOLID, 4, RGB(0, 0, 255));
            rpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));

            int count = 0;

            SelectObject(hdc, GetStockObject(NULL_BRUSH));

            for (int i = 0; i < figure.size(); i++) {
                SelectObject(hdc, hpen);
                figure[i]->Draw(hdc);
            }

            if (line.e.getX() != 0 || line.s.getY() != 0 || line.e.getX() != 0|| line.e.getY() != 0) {
                for (int i = 0; i < figure.size(); i++) {
                    if (figure[i]->isCutByLine(line) == true) {
                        SelectObject(hdc, rpen);
                        figure[i]->Draw(hdc);
                        count++;
                    }
                }
            }
                               
            line.Draw(hdc);

            FILE* stream;
            freopen_s(&stream, "check.txt", "w", stdout);
            cout << "The number of shapes is cut by line: " << count;

            SetTextColor(hdc, RGB(0, 100, 0));

            tstringstream stros;
            stros << "The number of shapes is cut by line : " << count;
            //::MessageBox(hWnd, stros.str().c_str(), L"", MB_OK);
            TextOut(hdc, 1100, 20, stros.str().c_str(), 40);
            count = 0;
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

INT_PTR CALLBACK Input_R(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
            
            GetDlgItemText(hDlg, IDC_EDIT1, vl, sizeof(vl));
            r1 = _ttoi(vl);
            GetDlgItemText(hDlg, IDC_EDIT2, vt, sizeof(vt));
            r2 = _ttoi(vt);
            GetDlgItemText(hDlg, IDC_EDIT3, vr, sizeof(vr));
            r3 = _ttoi(vr);
            GetDlgItemText(hDlg, IDC_EDIT4, vb, sizeof(vb));
            r4 = _ttoi(vb);

            //if (r1 != NULL && r2 != NULL && r3 != NULL && r4 != NULL) {
                myFigure* f = new myRectangle(r3, r4, r1, r2);
                figure.push_back(f);
            //}

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Input_C(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            int c1 = 0, c2 = 0, c3 = 0;

            GetDlgItemText(hDlg, IDC_EDIT1, vl, sizeof(vl));
            c1 = _ttoi(vl);
            //OutputDebugString(vl);
            GetDlgItemText(hDlg, IDC_EDIT2, vt, sizeof(vt));
            c2 = _ttoi(vt);
            GetDlgItemText(hDlg, IDC_EDIT3, vr, sizeof(vr));
            c3 = _ttoi(vr);

            //if (c1 != NULL && c2 != NULL && c3 != NULL) {
                myFigure* f = new myCircle(c1, c2, c3);
                figure.push_back(f);          
            //}

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Input_E(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            int e1 = 0, e2 = 0, e3 = 0, e4 = 0;

            GetDlgItemText(hDlg, IDC_EDIT1, vl, sizeof(vl));
            e1 = _ttoi(vl);
            //OutputDebugString(vl);
            GetDlgItemText(hDlg, IDC_EDIT2, vt, sizeof(vt));
            e2 = _ttoi(vt);
            GetDlgItemText(hDlg, IDC_EDIT3, vr, sizeof(vr));
            e3 = _ttoi(vr);
            GetDlgItemText(hDlg, IDC_EDIT4, vb, sizeof(vb));
            e4 = _ttoi(vb);

            //if (e1 != NULL && e2 != NULL && e3 != NULL && e4 != NULL) {
                myFigure* f = new myEllipse(e1, e2, e3, e4);
                figure.push_back(f);
            //}

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Input_S(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            int s1 = 0, s2 = 0, s3 = 0, s4 = 0, s5 = 0;

            GetDlgItemText(hDlg, IDC_EDIT1, vl, sizeof(vl));
            s1 = _ttoi(vl);
            //OutputDebugString(vl);
            GetDlgItemText(hDlg, IDC_EDIT2, vt, sizeof(vt));
            s2 = _ttoi(vt);
            GetDlgItemText(hDlg, IDC_EDIT3, vr, sizeof(vr));
            s3 = _ttoi(vr);
            GetDlgItemText(hDlg, IDC_EDIT4, vb, sizeof(vb));
            s4 = _ttoi(vb);
            GetDlgItemText(hDlg, IDC_EDIT5, vd, sizeof(vd));
            s5 = _ttoi(vd);

            //if (s1 != NULL && s2 != NULL && s3 != NULL && s4 != NULL && s5 != NULL) {
                myFigure* f = new mySemiCircle(s1, s2, s3, s4, s5);
                figure.push_back(f);
            //}

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

vector <int> extractIntegerWords(string str)
{
    stringstream ss;
    ss << str;
    std::vector<int> a;
    string temp;
    int found;
    while (!ss.eof()) {
        ss >> temp;
        if (stringstream(temp) >> found)
            a.push_back(found);
        temp = "";
    }
    return a;
}

INT_PTR CALLBACK Input_P(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {

            GetDlgItemText(hDlg, IDC_EDIT3, vl, sizeof(vl));

            if (vl != L"") {
                vector<int> p2;
                wstring t(&vl[0]);
                string s(t.begin(), t.end());
                p2 = extractIntegerWords(s);

                vector<myPoint> mp;

                for (int i = 0; i < p2.size(); i += 2) {
                    myPoint p = myPoint(p2[i], p2[i + 1]);
                    mp.push_back(p);
                    cout << p.getX() << " " << p.getY();
                }

                myFigure* f = new myPolygon(mp);
                figure.push_back(f);
            }

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Input_T(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            int t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0;

            GetDlgItemText(hDlg, IDC_EDIT1, vl, sizeof(vl));
            t1 = _ttoi(vl);
            //OutputDebugString(vl);
            GetDlgItemText(hDlg, IDC_EDIT2, vt, sizeof(vt));
            t2 = _ttoi(vt);
            GetDlgItemText(hDlg, IDC_EDIT3, vr, sizeof(vr));
            t3 = _ttoi(vr);
            GetDlgItemText(hDlg, IDC_EDIT4, vb, sizeof(vb));
            t4 = _ttoi(vb);
            GetDlgItemText(hDlg, IDC_EDIT5, vd, sizeof(vd));
            t5 = _ttoi(vd);
            GetDlgItemText(hDlg, IDC_EDIT6, ve, sizeof(ve));
            t6 = _ttoi(ve);

            //if (t1 != NULL && t2 != NULL && t3 != NULL && t4 != NULL && t5 != NULL && t6 != NULL) {
                myFigure* f = new myTriangle(t1, t2, t3, t4, t5, t6);
                figure.push_back(f);
            //}

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Input_L(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            int l1 = 0, l2 = 0, l3 = 0, l4 = 0;

            GetDlgItemText(hDlg, IDC_EDIT7, vl, sizeof(vl));
            l1 = _ttoi(vl);
            GetDlgItemText(hDlg, IDC_EDIT8, vt, sizeof(vt));
            l2 = _ttoi(vt);
            GetDlgItemText(hDlg, IDC_EDIT9, vr, sizeof(vr));
            l3 = _ttoi(vr);
            GetDlgItemText(hDlg, IDC_EDIT10, vb, sizeof(vb));
            l4 = _ttoi(vb);

            line = myLine(l1, l2, l3, l4);

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

// Square: 100 100 250 250
// Rectangle: 100 350 500 450
// Circle: 800 500 150
// Semi-Circle: 1200 600 150 150 1
// Ellipse: 1000 200 200 100
// Polygon: 150 450 250 520 200 620 110 620 65 520
// Triangle: 500 50 650 300 350 300
// Line: 0 0 1400 650