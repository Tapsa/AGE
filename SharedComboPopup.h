/////////////////////////////////////////////////////////////////////////////
// Author:      Jaakko Salli
// Modified by: Mikko P
// Created:     Apr-30-2006
// Copyright:   Jaakko Salli, Mikko P
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _SHAREDCOMBO_H_
#define _SHAREDCOMBO_H_

#include "wx/defs.h"

#include "wx/combo.h"
#include "wx/vlbox.h"
#include "wx/timer.h"

// ----------------------------------------------------------------------------
// SharedComboPopup is a wxVListBox customized to act as a popup control.
// ----------------------------------------------------------------------------

class SharedComboPopup: public wxVListBox, public wxComboPopup
{
public:

    // init and dtor
    SharedComboPopup(): wxVListBox(), wxComboPopup() {}
    virtual ~SharedComboPopup();

    // required virtuals
    virtual void Init() wxOVERRIDE;
    virtual bool Create(wxWindow *parent) wxOVERRIDE;
    virtual void SetFocus() wxOVERRIDE;
    virtual wxWindow *GetControl() wxOVERRIDE {return this;}
    virtual void SetStringValue(const wxString &value) wxOVERRIDE;
    virtual wxString GetStringValue() const wxOVERRIDE;

    // more customization
    virtual void OnPopup() wxOVERRIDE;
    virtual wxSize GetAdjustedSize(int minWidth, int prefHeight, int maxHeight) wxOVERRIDE;
    virtual void PaintComboControl(wxDC &dc, const wxRect &rect) wxOVERRIDE;
    virtual void OnComboKeyEvent(wxKeyEvent &event) wxOVERRIDE;
    virtual void OnComboCharEvent(wxKeyEvent &event) wxOVERRIDE;
    virtual void OnComboDoubleClick() wxOVERRIDE;
    virtual bool LazyCreate() wxOVERRIDE;
    virtual bool FindItem(const wxString &item, wxString *trueItem) wxOVERRIDE;

    // Item management
    void SetSelection(int item);
    void Clear();
    wxString GetString(int item) const;
    unsigned int GetCount() const;
    int FindString(const wxString &s, bool bCase = false) const;
    int GetSelection() const;

    void Imbue(wxArrayString *choices);
    void Flash();

    // helpers
    wxCoord GetTotalHeight() const {return EstimateTotalHeight();}
    wxCoord GetLineHeight(int line) const {return OnGetRowHeight(line);}

protected:

    // Called by OnComboDoubleClick and OnCombo{Key,Char}Event
    bool HandleKey(int keycode, bool saturate, wxChar keychar = 0);

    // sends combobox select event from the parent combo control
    void SendComboBoxEvent(int selection);

    // gets value, sends event and dismisses
    void DismissWithEvent();

    // OnMeasureItemWidth will be called on next GetAdjustedSize.
    void ItemWidthChanged(unsigned int item)
    {
        m_widths[item] = -1;
        m_widthsDirty = true;
    }

    // Callbacks for drawing and measuring items. Override in a derived class for
    // owner-drawnness. Font, background and text colour have been prepared according
    // to selection, focus and such.
    //
    // item: item index to be drawn, may be wxNOT_FOUND when painting combo control itself
    //       and there is no valid selection
    // flags: SCB_PAINTING_CONTROL is set if painting to combo control instead of list
    //
    // NOTE: If SharedComboPopup is used with a wxComboCtrl class not derived from
    //       wxOwnerDrawnComboBox, this method must be overridden.
    virtual void OnDrawItem(wxDC &dc, const wxRect &rect, int item, int flags) const;

    // This is same as in wxVListBox
    virtual wxCoord OnMeasureItem(size_t item) const wxOVERRIDE;

    // Return item width, or -1 for calculating from text extent (default)
    virtual wxCoord OnMeasureItemWidth(size_t item) const;

    // Draw item and combo control background. Flags are same as with OnDrawItem.
    // NB: Can't use name OnDrawBackground because of virtual function hiding warnings.
    virtual void OnDrawBg(wxDC &dc, const wxRect &rect, int item, int flags) const;

    // Additional wxVListBox implementation (no need to override in derived classes)
    virtual void OnDrawItem(wxDC &dc, const wxRect &rect, size_t n) const wxOVERRIDE;
    void OnDrawBackground(wxDC &dc, const wxRect &rect, size_t n) const wxOVERRIDE;

    // filter mouse move events happening outside the list box
    // move selection with cursor
    void OnMouseMove(wxMouseEvent &event);
    void OnKey(wxKeyEvent &event);
    void OnChar(wxKeyEvent &event);
    void OnLeftClick(wxMouseEvent &event);

    // Return the widest item width (recalculating it if necessary)
    int GetWidestItemWidth() {CalcWidths(); return m_widestWidth;}

    // Return the index of the widest item (recalculating it if necessary)
    int GetWidestItem() {CalcWidths(); return m_widestItem;}

    // Stop partial completion (when some other event occurs)
    void StopPartialCompletion();

    wxArrayString           *s_strings;

    wxFont                  m_useFont;

    //wxString                m_stringValue; // displayed text (may be different than (*s_strings)[m_value])
    int                     m_value; // selection
    int                     m_itemHover; // on which item the cursor is
    int                     m_itemHeight; // default item height (calculate from font size
                                          // and used in the absence of callback)

private:

    // Cached item widths (in pixels).
    wxArrayInt              m_widths;

    // Width of currently widest item.
    int                     m_widestWidth;

    // Index of currently widest item.
    int                     m_widestItem;

    // Measure some items in next GetAdjustedSize?
    bool                    m_widthsDirty;

    // Find widest item in next GetAdjustedSize?
    bool                    m_findWidest;

    // has the mouse been released on this control?
    bool                    m_clicked;

    // Recalculate widths if they are dirty
    void CalcWidths();

    // Partial completion string
    wxString                m_partialCompletionString;

    wxString                m_stringValue;

#if wxUSE_TIMER
    // Partial completion timer
    wxTimer                 m_partialCompletionTimer;
#endif// wxUSE_TIMER

    wxDECLARE_EVENT_TABLE();
};

#endif// _SHAREDCOMBO_H_
