#ifndef _UNICODE
#define _UNICODE
#endif
#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include "gl/gl.h"
#include "engine/Engine.h"
#include "engine/utils/MyPolygon.h"
#include "engine/object/ObjectLoader.h"

const SIZE MIN_WINDOW_SIZE = SIZE{900, 900};
const SIZE FIRST_WINDOW_SIZE = SIZE{900, 900};
const COLORREF BACKGROUND_COLOR = RGB(255, 255, 255);

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

void EnableOpenGL(HWND hwnd, HDC *, HGLRC *);

void DisableOpenGL(HWND, HDC, HGLRC);

Engine engine = Engine();


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {

    const wchar_t WINDOW_CLASS[] = L"MAIN_WINDOW_CLASS";
    const wchar_t WINDOW_TITLE[] = L"V-3D ^_^";

    HDC hDC;
    HGLRC hRC;
    MSG msg;
    WNDCLASSEXW wc;
    HWND hwnd;

    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(BACKGROUND_COLOR);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = WINDOW_CLASS;
    wc.hIconSm = LoadIconW(nullptr, IDI_APPLICATION);

    if (!RegisterClassExW(&wc)) {
        MessageBoxW(nullptr, L"Error registering window class", L"Attention", MB_OK);
        return 0;
    }

    hwnd = CreateWindowExW(
            // Optional window styles.
            0x0,
            // Window class
            WINDOW_CLASS,
            // Window text
            WINDOW_TITLE,
            // Window style
            WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, FIRST_WINDOW_SIZE.cx, FIRST_WINDOW_SIZE.cy,
            // Parent window
            nullptr,
            // Menu
            nullptr,
            // Instance handle
            hInstance,
            // Additional application data
            nullptr
    );

    if (hwnd == nullptr) {
        MessageBoxW(nullptr, L"Error creating window", L"Attention", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.1, 0.1, -0.1, 0.1, 0.2f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    bool bQuit = false;
    /* program main loop */
    while (!bQuit) {
        /* check for messages */
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT) {
                bQuit = true;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
            /* OpenGL animation code goes here */
            engine.handleKeys(); // Faster than handling messages
            engine.draw(hDC);
            SetWindowTextA(hwnd, engine.description().data());
            Sleep(1000 / engine.fps);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_CLOSE: {
            PostQuitMessage(0);
            break;
        }
        case WM_DESTROY: {
            return 0;
        }
        case WM_KEYDOWN: {
            switch (wParam) {
                case 0x4F: { // O
                    OPENFILENAME ofn;
                    TCHAR szFile[260] = {0};

                    ZeroMemory(&ofn, sizeof(ofn));
                    ofn.lStructSize = sizeof(ofn);
                    ofn.hwndOwner = hwnd;
                    ofn.lpstrFile = szFile;
                    ofn.nMaxFile = sizeof(szFile);
                    ofn.lpstrFilter = _T("obj\0*.obj\0");
                    ofn.nFilterIndex = 1;
                    ofn.lpstrFileTitle = nullptr;
                    ofn.nMaxFileTitle = 0;
                    ofn.lpstrInitialDir = nullptr;
                    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                    if (GetOpenFileName(&ofn) == TRUE) {
                        std::wstring wpath = ofn.lpstrFile;
                        std::string path(wpath.begin(), wpath.end());

                        Object obj = ObjectLoader::LoadObjModel(path);
                        obj.centerPolygonVertices();
                        obj.resizeToHeight(10);
                        engine.scene.add(obj);
                    }

                    break;
                }
                case 0x51: { // Q
                    switch (engine.renderMode) {
                        case Engine::RenderMode::SOLID:
                            engine.renderMode = Engine::RenderMode::WIREFRAME;
                            break;
                        case Engine::RenderMode::WIREFRAME:
                            engine.renderMode = Engine::RenderMode::SOLID;
                            break;
                    }
                    break;
                }
                case 0x52: { // R
                    engine.scene = Scene();
                    break;
                }
                case 0x46: { // F
                    engine.scene.resetCamera();
                    break;
                }
                case 0x45: { // E
                    engine.scene.light.nextPosition();
                    break;
                }
                case VK_ESCAPE: {
                    PostQuitMessage(0);
                    break;
                }
                default: {
                    break;
                }
            }
            break;
        }
        case WM_GETMINMAXINFO: {
            auto lpMMI = (LPMINMAXINFO) lParam;
            lpMMI->ptMinTrackSize.x = MIN_WINDOW_SIZE.cx;
            lpMMI->ptMinTrackSize.y = MIN_WINDOW_SIZE.cy;
            break;
        }
        default: {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC *hDC, HGLRC *hRC) {
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC) {
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

