#pragma once

#ifdef DLLPROJECT_EXPORTS
#define DLLINT __declspec(dllexport)
#else
#define DLLINT __declspec(dllimport)
#endif

extern "C" {
    struct ISomeWindow {
        virtual void Release() = 0;
        virtual void Create (int width, int height, LPCTSTR title) = 0;
        virtual void Run() = 0;
    };

    DLLINT ISomeWindow * CreateWindowInterface ();
}