#include "FPanel.h"

#include "wx/dcbuffer.h"
#include "wx/dcgraph.h"
#include "wx/graphics.h"

wxBEGIN_EVENT_TABLE(FPanel, wxScrolledWindow)
    EVT_PAINT(FPanel::OnPaint)
wxEND_EVENT_TABLE()

FPanel::FPanel(
    wxWindow* parent,
    wxWindowID id,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name)
    : wxScrolledWindow(parent, id, pos, size, style, name)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);


}

FPanel::~FPanel() {}


void FPanel::OnPaint(wxPaintEvent& event)
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
    dc.SetBackground(*wxGREY_BRUSH);
    dc.Clear();

    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawRectangle(10,10,200,150);

    dc.SetTextForeground(*wxWHITE);
    dc.DrawText("Hello, MFD world", 13, 20);
    dc.DrawText("3 column floating pane", 15, 40);
    dc.DrawText("wxAUI managed", 15, 55);
    dc.DrawText("Generic wxWindow API", 15, 70);
    dc.DrawText("Generic wxDC rendering", 15, 85);


}








