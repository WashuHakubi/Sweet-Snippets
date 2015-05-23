#include <windows.h>
#include "..\DllProject\SomeWindow.h"

#pragma comment(lib, "DllProject.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR cmdLine, int showCmd)
{
    ISomeWindow * window = CreateWindowInterface();

    window->Create(800, 600, TEXT("I LIKE COOKIES"));

    window->Run();

    window->Release();
    return 0;
}