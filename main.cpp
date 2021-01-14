
#include "Line.cpp"
#include "Circle.cpp"
#include "Ellipsee.cpp"
#include "Rectanglee.cpp"
#include <iostream>

#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <winuser.h>
#include <fstream>

int const N = 1e5;
using namespace std;
#define OpenFile 1
#define SaveFile 2
#define MyClear 3
#define EllipseDirect 4
#define EllipsePolar 23
#define Line_Mid 6
#define Line_DDA 7
#define Circle_Direct 8
#define Circle_Polar 9
#define Circlemidpoint 10
#define Circlemidpointmod 11
#define line 17
#define circle 18
#define Line_Clliping 21
#define ellipse 22
#define rectangle 24

void addMnue(HWND hwnd);


Shape *Screen[N];
int Shape::xx1 = 0, Shape::yy1 = 0, Shape::xx2 = 1e9, Shape::yy2 = 1e9;
int size = 0;
HMENU hMenu;

bool showColorDialog(HWND hwnd, COLORREF &ret) {

    CHOOSECOLOR ColorDiag = {};
    static COLORREF CustClr[16];


    ColorDiag.lStructSize = sizeof(ColorDiag);
    ColorDiag.hwndOwner = hwnd;
    ColorDiag.lpCustColors = (LPDWORD) CustClr;
    ColorDiag.rgbResult = ret;
    ColorDiag.Flags = CC_FULLOPEN | CC_RGBINIT;
// choosecolor is a function that take var of choosecolor
    if (!ChooseColor(&ColorDiag)) return false;
    ret = ColorDiag.rgbResult;

    return true;
}

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszArgument,
                   int nCmdShow) {
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_HAND); // the second paramter is the shape
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */

    //CHANGE THE COLOR FROM HERE
    wincl.hbrBackground = reinterpret_cast<HBRUSH>(CTLCOLOR_STATIC);
    COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
            0,                   /* Extended possibilites for variation */
            szClassName,         /* Classname */
            _T("Code::Blocks Template Windows App"),       /* Title Text */
            WS_OVERLAPPEDWINDOW, /* default window */
            CW_USEDEFAULT,       /* Windows decides the position */
            CW_USEDEFAULT,       /* where the window ends up on the screen */
            600,                 /* The programs width */
            375,                 /* and height in pixels */
            HWND_DESKTOP,        /* The window is a child-window to desktop */
            NULL,                /* No menu */
            hThisInstance,       /* Program Instance handler */
            NULL                 /* No Window Creation data */
    );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0)) {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
int x, x2, y, y2;

COLORREF CurColor = RGB(0, 0, 0);

void clear() {
    for (int i = 0; i < size; i++)
        delete Screen[i];
    size = 0;
}

void Save_File(string &file_name) {
    // object related to files
    ofstream file_obj;
    // byrouh yaft7 el file el asmo paramter
    file_obj.open(file_name);
    // akno by3ml file mn n shapes el 3ala screen
    int sz = size;
    file_obj.write((char *) &sz, sizeof sz);
    for (int i = 0; i < size; i++) {
        Shape *shape = Screen[i];
        int type;
        // type shyla no3 el haga el rasmnha
        Line *LINE = dynamic_cast<Line *>(shape);
        Circle *CIRCLE = dynamic_cast<Circle *>(shape);
        Ellipsee *ELLIPSE = dynamic_cast<class Ellipsee *>(shape);
        Rectanglee *RECTANGLE = dynamic_cast<class Rectanglee *>(shape);
        if (LINE) {
            type = line;
            file_obj.write((char *) &type, sizeof type);
            file_obj.write((char *) shape, sizeof(Line));
        }
        if (CIRCLE) {
            type = circle;
            file_obj.write((char *) &type, sizeof type);
            file_obj.write((char *) shape, sizeof(Circle));
        }
        if (ELLIPSE) {
            type = ellipse;
            file_obj.write((char *) &type, sizeof type);
            file_obj.write((char *) shape, sizeof(class Ellipsee));
        }
        if (RECTANGLE) {
            type = rectangle;
            file_obj.write((char *) &type, sizeof type);
            file_obj.write((char *) shape, sizeof(class Ellipsee));
        }
    }
}

void Open_File(string &file_name) {

    ifstream FILE;
    FILE.open(file_name);
    int Size = 0;
    FILE.read((char *) &Size, sizeof Size);
    size=Size;
    for (int i = 0; i < Size; i++) {
        int type = 0;
        FILE.read((char *) &type, sizeof type);
        Shape *shape;
        switch (type) {
            case line: {
                shape = new Line();
                FILE.read((char *) shape, sizeof(Line));
                break;
            }
            case circle: {
                shape = new Circle();
                FILE.read((char *) shape, sizeof(Circle));
                break;
            }
            case ellipse: {
                shape = new Ellipsee();
                FILE.read((char *) shape, sizeof(Ellipsee));
                break;
            }
            case rectangle: {
                shape = new Rectanglee();
                FILE.read((char *) shape, sizeof(Rectanglee));
                break;

            }

        }

        Screen[i] = shape;
    }
}

int quarter;

int x3, y3;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wp, LPARAM lp) {
    HDC hdc = GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {

        case WM_RBUTTONUP: {
            x = LOWORD(lp);
            y = HIWORD(lp);
            break;

        }
        case WM_LBUTTONDOWN: {
            x2 = LOWORD(lp);
            y2 = HIWORD(lp);
            break;
        }
        case WM_RBUTTONDBLCLK : {
            x3 = LOWORD(lp);
            y3 = HIWORD(lp);
        }
            break;
        case WM_COMMAND : {
            switch (LOWORD(wp)) {
                case SaveFile: {
                    OPENFILENAME FILE;
                    char szFileName[N] = "";
                    // 3lshan n-save el file ma7tgen nt2kd anu msh byktbha fo2 haga fa bn3ml zero memory
                    ZeroMemory(&FILE, sizeof(FILE));

                    FILE.lStructSize = sizeof(FILE);
                    FILE.hwndOwner = NULL;
                    FILE.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
                    FILE.lpstrFile = szFileName;
                    FILE.nMaxFile = N;
                    FILE.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
                    FILE.lpstrDefExt = "txt";
                    // by3ml save le file taken it's name
                    GetSaveFileName(&FILE);

                    string file_name = FILE.lpstrFile;
                    // bykktb fe el file el 3amltlu save
                    Save_File(file_name);
                    break;
                }
                case OpenFile: {
                    clear();
                    OPENFILENAME FILE;
                    char szFileName[N] = "";
                    ZeroMemory(&FILE, sizeof(FILE));
                    FILE.lStructSize = sizeof(FILE);
                    FILE.hwndOwner = NULL;
                    FILE.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
                    FILE.lpstrFile = szFileName;
                    FILE.nMaxFile = N;
                    FILE.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
                    FILE.lpstrDefExt = "txt";
                    GetOpenFileName(&FILE);
                    string file_name = FILE.lpstrFile;
                    Open_File(file_name);
                    InvalidateRect(hwnd, NULL, true);
                    break;

                }
                case MyClear: {
                    clear();
                    Shape::xx1 = 0, Shape::yy1 = 0, Shape::xx2 = 1e9, Shape::yy2 = 1e9;
                    InvalidateRect(hwnd, NULL, true);
                    break;
                }
                case Line_Mid: {
                    Screen[size++] = (new Line(x, y, x2, y2, hdc, CurColor, 1));
                    InvalidateRect(hwnd, NULL, true);
                    break;
                }
                case Line_DDA: {
                    Screen[size++] = (new Line(x, y, x2, y2, hdc, CurColor, 0));
                    InvalidateRect(hwnd, NULL, true);
                    break;

                }
                case Line_Clliping: {
                    Screen[size++] = (new Line(x, y, x2, y2, hdc, CurColor, 2));
                    InvalidateRect(hwnd, NULL, true);
                    break;
                }
                case Circle_Direct : {
                    cin >> quarter;
                    Screen[size++] = (new Circle(x, y, x2, y2, hdc, CurColor, 0, quarter));
                    InvalidateRect(hwnd, NULL, true);
                    break;
                }
                case Circle_Polar: {
                    cin >> quarter;
                    Screen[size++] = (new Circle(x, y, x2, y2, hdc, CurColor, 1, quarter));
                    InvalidateRect(hwnd, NULL, true);
                    break;
                }
                case Circlemidpoint: {
                    cin >> quarter;
                    Screen[size++] = (new Circle(x, y, x2, y2, hdc, CurColor, 2, quarter));
                    InvalidateRect(hwnd, NULL, true);
                    break;
                }
                case Circlemidpointmod: {
                    cin >> quarter;
                    Screen[size++] = (new Circle(x, y, x2, y2, hdc, CurColor, 3, quarter));
                    InvalidateRect(hwnd, NULL, true);
                    break;
                }
                case COLOR_WINDOW: {
                    showColorDialog(hwnd, CurColor);
                    break;
                }
                case rectangle: {
                    clear();
                    Screen[size++] = (new Rectanglee(x, y, x2, y2, CurColor, hdc));
                    Shape::xx1 = min(x, x2), Shape::xx2 = max(x, x2);
                    Shape::yy1 = min(y, y2), Shape::yy2 = max(y2, y);
                    InvalidateRect(hwnd, NULL, true);
                    break;

                }
                case EllipsePolar: {
                    int dx1 = abs(x - x2), dx2 = abs(x - x3), dy1 = abs(y - y2), dy2 = abs(y - y3);
                    Screen[size++] = new Ellipsee(x, y, max(dx1, dx2), max(dy2, dy1), hdc, CurColor, 1);
                    InvalidateRect(hwnd, NULL, true);
                    break;

                }

                case EllipseDirect: {
                    int dx1 = abs(x - x2), dx2 = abs(x - x3), dy1 = abs(y - y2), dy2 = abs(y - y3);
                    Screen[size++] = new Ellipsee(x, y, max(dx1, dx2), max(dy2, dy1), hdc, CurColor, 0);
                    InvalidateRect(hwnd, NULL, true);
                    break;

                }

            }

        }

        case WM_CREATE: {
            addMnue(hwnd);
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;

            for (int i = 0; i < size; i++)
                Screen[i]->Draw();
            EndPaint(hwnd, &ps);
        }
        case WM_KEYUP: {
            switch (wp) {
                case VK_ESCAPE: {
                    PostQuitMessage(0);
                }
                    break;
            }
        }



    }
    return DefWindowProc(hwnd, message, wp, lp);

}

void addMnue(HWND hwnd) {
    hMenu = CreateMenu();
    HMENU fileMnue = CreateMenu();
    HMENU LineMnue = CreateMenu();
    HMENU CircleMnue = CreateMenu();
    HMENU EllipseMnue = CreateMenu();


    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) fileMnue, "File");
    AppendMenu(fileMnue, MF_STRING, OpenFile, "Open");
    AppendMenu(fileMnue, MF_STRING, SaveFile, "Save");


    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) LineMnue, "Line ");
    AppendMenu(LineMnue, MF_STRING, Line_DDA, "Line DDA");
    AppendMenu(LineMnue, MF_STRING, Line_Mid, "Line MID");
    AppendMenu(LineMnue, MF_STRING, Line_Clliping, "Line Clipping");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) CircleMnue, "Circle ");
    AppendMenu(CircleMnue, MF_STRING, Circle_Direct, "Circle Direct");
    AppendMenu(CircleMnue, MF_STRING, Circle_Polar, "Circle Polar");
    AppendMenu(CircleMnue, MF_STRING, Circlemidpoint, "Circle mid point");
    AppendMenu(CircleMnue, MF_STRING, Circlemidpointmod, "Circle mid point modifeded");


    AppendMenu(hMenu, MF_POPUP, (UINT_PTR) EllipseMnue, "Ellipsee ");
    AppendMenu(EllipseMnue, MF_STRING, EllipsePolar, "Ellipsee Polar");
    AppendMenu(EllipseMnue, MF_STRING, EllipseDirect, "Ellipsee Direct");

    AppendMenu(hMenu, MF_STRING, COLOR_WINDOW, "Color");
    AppendMenu(hMenu, MF_STRING, rectangle, "Rectangle");

    AppendMenu(hMenu, MF_STRING, MyClear, "Clear");
    SetMenu(hwnd, hMenu);


}

