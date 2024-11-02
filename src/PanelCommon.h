#pragma once
#include <array>
#include <memory>
#include <wx/graphics.h>
#include <wx/wx.h>
#include <wx/filename.h>
#include "ocpn_plugin.h"



struct TimerSmooth
{
    static const int INTERVAL = 10;
    static const int YMOVEMENT = 20;
    static const int XMOVEMENT = 20;
    static const int XOFFSET = 2;
};

inline wxBitmap LoadSVG(const wxString& filename, int width, int height)
{
    auto bb = wxBitmapBundle::FromSVGFile(filename, wxSize(width, height));
    return bb.GetBitmap(wxSize(width, height));
}