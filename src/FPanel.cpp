#include "FPanel.h"

#include "wx/dcbuffer.h"
#include "wx/dcgraph.h"
#include "wx/graphics.h"

#include "pidc.h"

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

    m_GLCanvas = new wxGLCanvasSubClass(this);
    wxGLContext *pctx = new wxGLContext(m_GLCanvas);
    m_GLCanvas->SetContext(pctx);
    m_pGLcontext = pctx;  // Save a copy of the common context
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

    m_GLCanvas->Refresh(true);
    m_GLCanvas->Update();

}

BEGIN_EVENT_TABLE(wxGLCanvasSubClass, wxGLCanvas)
EVT_PAINT    (wxGLCanvasSubClass::Paintit)
END_EVENT_TABLE()

wxGLCanvasSubClass::wxGLCanvasSubClass(wxWindow *parent)
    :wxGLCanvas(parent, wxID_ANY,  NULL, wxDefaultPosition, wxSize(400, 400), 0, wxT("GLCanvas")){

    m_pidc= new piDC();
    wxFont fo = *OCPNGetFont(_("Dialog"), 10);
    m_Font_DC = new wxFont(fo);
    m_pidc->SetFont(*m_Font_DC);

}


void wxGLCanvasSubClass::Paintit(wxPaintEvent& WXUNUSED(event)){
    Show( true );
    SetCurrent(*m_pcontext);
    Render();
}

void wxGLCanvasSubClass::Render()
{
    wxPaintDC(this);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, (GLint)GetSize().x, (GLint)GetSize().y, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    m_pidc->SetBrush(wxBrush(wxColour(150, 0, 0)));
    m_pidc->SetPen(wxPen(*wxWHITE));
    m_pidc->DrawRoundedRectangle(5,5,300, 120, 15);

    m_pidc->SetTextForeground(*wxWHITE);
    m_pidc->DrawText("Hello, MFD world", 15, 10);
    m_pidc->DrawText("3 column floating pane", 15, 40);
    m_pidc->DrawText("wxAUI managed", 15, 55);
    m_pidc->DrawText("wxGLCanvas window", 15, 70);
    m_pidc->DrawText("Combined piDC and native OpenGL rendering", 15, 85);
    m_pidc->DrawText("Class:  FPanel", 15, 100);

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0); glVertex3f(10, 330, 0.5);
    glColor3f(0, 1, 0); glVertex3f(210, 330, 0);
    glColor3f(0, 0, 1); glVertex3f(110, 150, 0);
    glEnd();

    glFlush();
    SwapBuffers();
}







