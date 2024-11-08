#pragma once
#include "PanelCommon.h"


class IPanel : public wxScrolledWindow
{
  public:
    IPanel(
        wxWindow* parent,
        wxWindowID id,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL | wxNO_BORDER,
        const wxString& name = wxASCII_STR(wxPanelNameStr));
    ~IPanel();

  private:
    void OnPaint(wxPaintEvent& event);

    wxDECLARE_EVENT_TABLE();
};