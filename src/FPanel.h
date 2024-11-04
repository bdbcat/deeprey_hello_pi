#pragma once
#include "PanelCommon.h"
#include <wx/glcanvas.h>
#include "pidc.h"

class wxGLCanvasSubClass;

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

    wxGLCanvasSubClass* m_GLCanvas;
    wxGLContext* m_pGLcontext;

    wxDECLARE_EVENT_TABLE();
};

class wxGLCanvasSubClass: public wxGLCanvas {
    void Render();
  public:
    wxGLCanvasSubClass(wxWindow* parent);
    void Paintit(wxPaintEvent& event);
    void SetContext(wxGLContext *pcontext) { m_pcontext = pcontext; }
  protected:
  private:
    wxGLContext* m_pcontext;
    piDC* m_pidc;
    wxFont* m_Font_DC;

    DECLARE_EVENT_TABLE()
};
