#include <windows.h>
#include "SomeWindow.h"

class SomeWindow : public ISomeWindow
{
public:
    virtual void Create (int width, int height, LPCTSTR title) override;
    virtual void Release () override;
    virtual void Run() override;

public:
    LRESULT ProcessMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:
    HWND windowHandle;
};

LRESULT CALLBACK WndProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_NCCREATE: {
        auto cs = reinterpret_cast<CREATESTRUCT *>(lparam);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(cs->lpCreateParams));
        return TRUE;
    }
    default:
        auto ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
        if (ptr)
        {
            return reinterpret_cast<SomeWindow *>(ptr)->ProcessMessage(hwnd, msg, wparam, lparam);
        }
    }

    return DefWindowProc(hwnd, msg, wparam, lparam);
}

LRESULT SomeWindow::ProcessMessage (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

void SomeWindow::Create (int width, int height, LPCTSTR title)
{
    WNDCLASSEX wndClass = {
        sizeof(WNDCLASSEX),
        CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
        WndProc,
        0, 0,
        GetModuleHandle(nullptr),
        nullptr,
        nullptr,
        0,
        nullptr,
        TEXT("SomeWindow"),
    };

    RegisterClassEx(&wndClass);

    windowHandle = CreateWindowEx(0, TEXT("SomeWindow"), TEXT("I'm a window"), WS_OVERLAPPEDWINDOW, 0, 0, width, height, nullptr, nullptr, GetModuleHandle(nullptr), this);

    ShowWindow(windowHandle, SW_SHOW);
    UpdateWindow(windowHandle);
}

void SomeWindow::Release ()
{
    delete this;
}

void SomeWindow::Run ()
{
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

ISomeWindow * CreateWindowInterface ()
{
    return new SomeWindow();
}
