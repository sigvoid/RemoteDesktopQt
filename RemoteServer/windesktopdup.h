#ifndef WINDESKTOPDUP_H
#define WINDESKTOPDUP_H

#pragma once
#define WIN32_LEAN_AND_MEAN

#include <QObject>
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdint.h>

#include <string>
#include <functional>
#include <vector>

#include <d3d11.h>
#include <dxgi1_2.h>

#include "mousearray.h"

typedef std::string Error;

// BGRA U8 Bitmap
struct Bitmap {
    int                  Width  = 0;
    int                  Height = 0;
    std::vector<uint8_t> Buf;
};

class WinDesktopDup
{
public:
    Bitmap Latest;
    int    OutputNumber = 0;

    WinDesktopDup();
    ~WinDesktopDup();
    Error Initialize();
    void  Close();
    Error  CaptureNext();
private:
    ID3D11Device*           D3DDevice        = nullptr;
    ID3D11DeviceContext*    D3DDeviceContext = nullptr;
    IDXGIOutputDuplication* DeskDupl         = nullptr;
    DXGI_OUTPUT_DESC        OutputDesc;
    bool                    HaveFrameLock = false;

    POINT cursorPos;
};

#endif // WINDESKTOPDUP_H
