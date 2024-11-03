/******************************************************************************
 *
 * Project:  OpenCPN
* Purpose:  Deeprey Plugin
* Author:   Dave Register
 *
 ***************************************************************************
 *   Copyright (C) 2024 Dave Register                                      *
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

#ifndef _DEEPREYPI_H_
#define _DEEPREYPI_H_

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include <wx/fileconf.h>
#include <wx/filepicker.h>
#include <wx/file.h>
#include <wx/aui/aui.h>

#include "PanelCommon.h"
#include "IPanel.h"
#include "FPanel.h"

#include "ocpn_plugin.h"
#include "config.h"
#include "pidc.h"


extern wxString _svg_deeprey_play;
extern wxString _svg_deeprey_toggled;
extern wxString _svg_deeprey_rollover;

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------


class deeprey_hello_pi : public opencpn_plugin_117, wxTimer
{
public:
    deeprey_hello_pi( void *ppimgr );

//    The required PlugIn Methods
      int Init( void );
      bool DeInit( void );

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();
      void LateInit(void);

      bool RenderGLOverlayMultiCanvas(wxGLContext *pcontext,
                                      PlugIn_ViewPort *vp, int canvasIndex);

      void Notify();
      void SetInterval( int interval );

//    The optional method overrides
      void SetColorScheme( PI_ColorScheme cs );
      void UpdateAuiStatus(void);

private:
      bool LoadConfig( void );
      bool SaveConfig( void );

      int               m_tb_item_id_record;
      int               m_tb_item_id_play;

      wxFileConfig     *m_pconfig;
      wxAuiManager     *m_pauimgr;
      int               m_interval;
      wxBitmap          m_panelBitmap;

      IPanel*        m_ipanel;
      FPanel*        m_fpanel;
      piDC*          m_pidc;
      wxFont*        m_Font_DC;

};


#endif
