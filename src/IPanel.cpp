#include "IPanel.h"

#include "wx/dcbuffer.h"
#include "wx/dcgraph.h"
#include "wx/graphics.h"

wxBEGIN_EVENT_TABLE(IPanel, wxScrolledWindow)
    EVT_PAINT(IPanel::OnPaint)
wxEND_EVENT_TABLE()

IPanel::IPanel(
    wxWindow* parent,
    wxWindowID id,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name)
    : wxScrolledWindow(parent, id, pos, size, style, name), m_timer(this, wxID_ANY)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);


}

IPanel::~IPanel() {}


void IPanel::OnPaint(wxPaintEvent& event)
{
    // Just use this class instead of wxPaintDC and make sure
    // wxWindow::SetBackgroundStyle() is called with wxBG_STYLE_PAINT somewhere in the class
    // initialization code, and that's all you have to do to (mostly) avoid flicker.
    wxBufferedPaintDC pdc(this);

#if wxUSE_GRAPHICS_CONTEXT
    wxGCDC gdc;
    wxGraphicsContext* context = wxGraphicsRenderer::GetDefaultRenderer()->CreateContext(pdc);
    context->SetAntialiasMode(wxANTIALIAS_DEFAULT);
    gdc.SetBackground(GetBackgroundColour());
    gdc.SetGraphicsContext(context);
    wxDC& dc = static_cast<wxDC&>(gdc);
#else
    wxDC& dc = pdc;
#endif

    PrepareDC(dc);
    dc.SetBackground(*wxBLACK_BRUSH);
    dc.Clear();

    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawRectangle(10,10,200,150);

    dc.SetTextForeground(*wxWHITE);
    dc.DrawText("Hello, MFD world", 13, 20);
    dc.DrawText("2 column docked pane", 15, 40);
    dc.DrawText("wxAUI managed", 15, 55);
    dc.DrawText("Generic wxWindow API", 15, 70);
    dc.DrawText("Generic wxDC rendering", 15, 85);


}




void IPanel::OnTimer(wxTimerEvent& event)
{
}








