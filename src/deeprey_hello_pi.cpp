/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Deeprey Plugin
 * Author:   Dave Register
 *
 ***************************************************************************
 *   Copyright (C) 2024 by Dave Register                                   *
 *   $EMAIL$   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 */


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include <typeinfo>
#include "deeprey_hello_pi.h"

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new deeprey_hello_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}




//---------------------------------------------------------------------------------------------------------
//
//    Deeprey PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

deeprey_hello_pi::deeprey_hello_pi(void *ppimgr)
      :opencpn_plugin_117(ppimgr), wxTimer(this)
{

    wxFileName fn;

    auto path = GetPluginDataDir("deeprey_hello_pi");
    fn.SetPath(path);
    fn.AppendDir("data");
    fn.SetFullName("deeprey_panel_icon.png");
    path = fn.GetFullPath();

    wxInitAllImageHandlers();

    wxLogDebug(wxString("Using icon path: ") + path);
    if (!wxImage::CanRead(path)) {
        wxLogDebug("Initiating image handlers.");
        wxInitAllImageHandlers();
    }
    wxImage panelIcon(path);
    if (panelIcon.IsOk())
        m_panelBitmap = wxBitmap(panelIcon);
    else
        wxLogWarning("DEEPREY panel icon has NOT been loaded");

}

int deeprey_hello_pi::Init(void)
{
  AddLocaleCatalog( _T("opencpn-deeprey_pi") );

  m_pauimgr = GetFrameAuiManager();
  m_pidc = NULL;

  // Setup the pi_ocpnDC
  if (!m_pidc ) {
        m_pidc = new piDC();
  }
  wxFont fo = *OCPNGetFont(_("Dialog"), 10);
  m_Font_DC = new wxFont(fo);
  m_pidc->SetFont(*m_Font_DC);

      //    And load the configuration items
  m_pconfig = GetOCPNConfigObject();
  LoadConfig();

  m_pauimgr->SetDockSizeConstraint( 2.0/12.0, 1.0);
  m_pauimgr->Update();

  wxSize size = GetOCPNCanvasWindow()->GetClientSize();
  wxSize IPSize;

  IPSize.x = size.x * 2 / 12;
  IPSize.y = size.y;
  m_ipanel = new IPanel(GetOCPNCanvasWindow(), wxID_ANY,
                              wxDefaultPosition, IPSize);

  wxAuiPaneInfo p = wxAuiPaneInfo()
                             .Name("InstrumentPanel")
                             .Caption("Caption")
                             .CaptionVisible(true)
                             .TopDockable(false)
                             .BottomDockable(false)
                             .LeftDockable(false)
                             .RightDockable(true)
                             .MinSize(IPSize)
                             .BestSize(IPSize)
                             .FloatingSize(wxSize(IPSize.x,400))
                             .FloatingPosition(200, 200)
                             .Direction(wxAUI_DOCK_RIGHT)
                             .Float()
                             .Show( false)
                             .Gripper(false);

       m_pauimgr->AddPane(m_ipanel, p);
       m_pauimgr->Update();



      return (
           WANTS_CONFIG              |
           WANTS_LATE_INIT           |
           USES_AUI_MANAGER          |
           WANTS_OPENGL_OVERLAY_CALLBACK
            );
}

bool deeprey_hello_pi::DeInit(void)
{
    SaveConfig();
    m_pauimgr->DetachPane(m_ipanel);
    m_ipanel->Close();
    m_ipanel->Destroy();

      return true;
}

void deeprey_hello_pi::LateInit(void)
{
    wxAuiPaneInfo &pane = m_pauimgr->GetPane(m_ipanel);
    pane.Dock();
    pane.Show();
    m_pauimgr->Update();

    m_ipanel->Show(true);
    m_ipanel->Refresh();
    m_ipanel->Update();
}


int deeprey_hello_pi::GetAPIVersionMajor()
{
      return atoi(API_VERSION);
}

int deeprey_hello_pi::GetAPIVersionMinor()
{
    std::string v(API_VERSION);
    size_t dotpos = v.find('.');
    return atoi(v.substr(dotpos + 1).c_str());
}

int deeprey_hello_pi::GetPlugInVersionMajor()
{
     return PLUGIN_VERSION_MAJOR;
}

int deeprey_hello_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

int GetPlugInVersionPatch()
{ 
      return PLUGIN_VERSION_PATCH; 
}

int GetPlugInVersionPost() 
{ 
      return PLUGIN_VERSION_TWEAK; 
}

const char *GetPlugInVersionPre() 
{
      return PKG_PRERELEASE; 
}

const char *GetPlugInVersionBuild()
{
       return PKG_BUILD_INFO; 
}

wxBitmap *deeprey_hello_pi::GetPlugInBitmap()
{
       return &m_panelBitmap;
}

wxString deeprey_hello_pi::GetCommonName()
{
      return _("Deeprey_Hello");
}

wxString deeprey_hello_pi::GetShortDescription()
{
      return _("Deeprey HELLO plugin for OpenCPN");
}

wxString deeprey_hello_pi::GetLongDescription()
{
      return _("Enhanced HELLO for OpenCPN.");
}


void deeprey_hello_pi::Notify()
{
}

void deeprey_hello_pi::SetInterval( int interval )
{
      m_interval = interval;
      if ( IsRunning() ) // Timer started?
            Start( m_interval, wxTIMER_CONTINUOUS ); // restart timer with new interval
}



void deeprey_hello_pi::SetColorScheme(PI_ColorScheme cs)
{
}

bool deeprey_hello_pi::LoadConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath( _T("/PlugIns/Deeprey") );
            return true;
      }
      else
            return false;
}

bool deeprey_hello_pi::SaveConfig(void)
{
      wxFileConfig *pConf = (wxFileConfig *)m_pconfig;

      if(pConf)
      {
            pConf->SetPath( _T("/PlugIns/Deeprey") );
            return true;
            return true;
      }
      else
            return false;
}

void deeprey_hello_pi::UpdateAuiStatus(void) {
      //    This method is called after the PlugIn is initialized
      //    and the frame has done its initial layout, possibly from a saved
      //    wxAuiManager "Perspective" It is a chance for the PlugIn to syncronize
      //    itself internally with the state of any Panes that were added to the
      //    frame in the PlugIn ctor.
}


bool deeprey_hello_pi::RenderGLOverlayMultiCanvas(wxGLContext *pcontext,
                                         PlugIn_ViewPort *vp, int canvasIndex) {

    m_pidc->SetVP(vp);
    m_pidc->SetDC(NULL);

    // Do a simple object render as a chart overlay

    m_pidc->SetBrush(wxColour(243, 229, 47));
    m_pidc->DrawRoundedRectangle(100, 100, 400, 150, 15);
    //m_pidc->DrawRectangle(100, 100, 200, 300);
    int yp = 100;
    int pitch = 20;
    m_pidc->DrawText("Hello MFD World!", 120, yp);
    yp += pitch;
    yp += pitch;
    m_pidc->DrawText("GL Overlay drawn graphics", 120, yp);
    yp += pitch;
    m_pidc->DrawText("Rendered using OpenCPN core context", 120, yp);
    yp += pitch;
    m_pidc->DrawText("API method: RenderGLOverlayMultiCanvas(...)", 120, yp);


    return true;
}

