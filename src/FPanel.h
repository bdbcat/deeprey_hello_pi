#pragma once
#include "PanelCommon.h"


class FPanel : public wxScrolledWindow
{
  public:
    FPanel(
        wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL | wxNO_BORDER,
        const wxString& name = wxASCII_STR(wxPanelNameStr));
    ~FPanel();

  private:
    void OnPaint(wxPaintEvent& event);

    wxDECLARE_EVENT_TABLE();
};