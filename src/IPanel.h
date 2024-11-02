#pragma once
#include "PanelCommon.h"

//class NavCanvas;
//class NavSidebar;
//class NavSidebarItem;

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

  public:
    void RefreshAndUpdate();

  private:
    void ConstructContextMenuReplace();
    void OnPaint(wxPaintEvent& event);
    void OnMouseEvents(wxMouseEvent& event);
    void OnSize(wxSizeEvent& event);
    void OnMouseLeftDown(wxMouseEvent& event);
    void OnMouseLeftUp(wxMouseEvent& event);
    void OnMouseDragging(wxMouseEvent& event);
    void OnMouseRightDown(wxMouseEvent& event);
    void OnTimer(wxTimerEvent& event);

    void SortFloatingItems();
    void ShowSelectItemDialog();

    void TryMoveSidebar(wxTimerEvent& event, long span);
    void RefreshSidebarRect();

    //void ShowContextMenuAdd(wxMouseEvent& event);
    //void ShowContextMenuReplace(wxMouseEvent& event, SidebarItemType type);
    //void ConnectContextMenuReplaceItemSelected(wxMenuItem* item);
    //void OnContextMenuReplaceItemSelected(wxCommandEvent& event);
    //void OnContextMenuAddItemSelected(wxCommandEvent& event);
    //SidebarItemType ConvertTextToItemType(const wxString& text);

  private:
    wxTimer m_timer;
    wxDateTime m_now;

    // wrap generic class instances with smart pointers

    wxDECLARE_EVENT_TABLE();
};