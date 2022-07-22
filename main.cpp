#include <Windows.h>

LRESULT WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT paintStruct;
    HDC hDC;

    switch (message)
    {
    case WM_PAINT:
        hDC = BeginPaint(handle, &paintStruct);
        EndPaint(handle, &paintStruct);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(handle, message, wParam, lParam);
    }

    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
                    LPWSTR cmdLine, int cmdShow)
{

    UNREFERENCED_PARAMETER(prevInstance);
    UNREFERENCED_PARAMETER(cmdLine);

    WNDCLASSEX windowClass = { 0 };
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpfnWndProc = WndProc;
    windowClass.hInstance = hInstance;
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    windowClass.lpszClassName = TEXT("WindowClass");

    if (!RegisterClassEx(&windowClass))
    {
        return -1;
    }

    RECT rc = { 0, 0, 640, 480 };

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    int w = rc.right - rc.left;
    int h = rc.bottom - rc.top;
    

    HWND hwnd = CreateWindow(TEXT("WindowClass"), TEXT("Behiri window"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, hInstance, NULL);

    if (!hwnd) return - 1;

    ShowWindow(hwnd, cmdShow);

    // Demo initilize

    MSG msg = { 0 };

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // Update
            // Draw
        }

    }

    return static_cast<int>(msg.wParam);
}
