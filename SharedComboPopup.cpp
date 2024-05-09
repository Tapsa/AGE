/////////////////////////////////////////////////////////////////////////////
// Author:      Jaakko Salli
// Modified by: Mikko P
// Created:     Apr-30-2006
// Copyright:   Jaakko Salli, Mikko P
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "Common.h"
#include "SharedComboPopup.h"
#include "wx/log.h"
#include "wx/combobox.h"
#include "wx/dcclient.h"
#include "wx/settings.h"
#include "wx/dialog.h"
#include "wx/textctrl.h"
#include "wx/combo.h"

// ============================================================================
// implementation
// ============================================================================

// time in milliseconds before partial completion buffer drops
#define SCB_PARTIAL_COMPLETION_TIME 1000

// If used, control itself is not custom paint using callback.
// Even if this is not used, writable combo is never custom paint
// until SetCustomPaintWidth is called
#define SCB_STD_CONTROL_PAINT 0x1000

// ----------------------------------------------------------------------------
// Callback flags (see wxOwnerDrawnComboBox::OnDrawItem)
// ----------------------------------------------------------------------------

// when set, we are painting the selected item in control,
// not in the popup
#define SCB_PAINTING_CONTROL 0x0001

// when set, we are painting an item which should have
// focus rectangle painted in the background. Text colour
// and clipping region are then appropriately set in
// the default OnDrawBackground implementation.
#define SCB_PAINTING_SELECTED 0x0002

// ----------------------------------------------------------------------------
// SharedComboPopup is a wxVListBox customized to act as a popup control
// ----------------------------------------------------------------------------

wxBEGIN_EVENT_TABLE(SharedComboPopup, wxVListBox)
    EVT_MOTION(SharedComboPopup::OnMouseMove)
    EVT_KEY_DOWN(SharedComboPopup::OnKey)
    EVT_CHAR(SharedComboPopup::OnChar)
    EVT_LEFT_UP(SharedComboPopup::OnLeftClick)
wxEND_EVENT_TABLE()

void SharedComboPopup::Init()
{
    m_widestWidth = 0;
    m_widestItem = -1;
    m_widthsDirty = false;
    m_findWidest = false;
    m_itemHeight = 0;
    m_value = -1;
    m_itemHover = -1;
    m_partialCompletionString = wxEmptyString;
}

bool SharedComboPopup::Create(wxWindow *parent)
{
    if(!wxVListBox::Create(parent,
                             wxID_ANY,
                             wxDefaultPosition,
                             wxDefaultSize,
                             wxBORDER_SIMPLE | wxLB_INT_HEIGHT | wxWANTS_CHARS))
        return false;

    wxVListBox::SetItemCount(s_strings->GetCount());

    // TODO: Move this to SetFont
    m_itemHeight = GetCharHeight();

    return true;
}

SharedComboPopup::~SharedComboPopup()
{
    Clear();
}

void SharedComboPopup::SetFocus()
{
    // Suppress SetFocus() warning by simply not calling it. This combo popup
    // has already been designed with the assumption that SetFocus() may not
    // do anything useful, so it really doesn't need to be called.
#ifdef __WXMSW__
    //
#else
    wxVListBox::SetFocus();
#endif
}

bool SharedComboPopup::LazyCreate()
{
    // NB: There is a bug with wxVListBox that can be avoided by creating
    //     it later (bug causes empty space to be shown if initial selection
    //     is at the end of a list longer than the control can show at once).
    return true;
}

// paint the control itself
void SharedComboPopup::PaintComboControl(wxDC &dc, const wxRect &rect)
{
    if(!(m_combo->GetWindowStyle() & SCB_STD_CONTROL_PAINT))
    {
        int flags = SCB_PAINTING_CONTROL;

        if(m_combo->ShouldDrawFocus())
            flags |= SCB_PAINTING_SELECTED;

        OnDrawBg(dc, rect, m_value, flags);

        if(m_value >= 0)
        {
            OnDrawItem(dc, rect, m_value, flags);
            return;
        }
    }

    wxComboPopup::PaintComboControl(dc, rect);
}

void SharedComboPopup::OnDrawItem(wxDC &dc, const wxRect &rect, size_t n) const
{
    int flags = 0;

    // Set correct text colour for selected items
    if(wxVListBox::GetSelection() == (int)n)
    {
        dc.SetTextForeground(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
        flags |= SCB_PAINTING_SELECTED;
    }
    else
    {
        dc.SetTextForeground(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT));
    }

    OnDrawItem(dc, rect, n, flags);
}

wxCoord SharedComboPopup::OnMeasureItemWidth(size_t) const
{
    return -1;
}

void SharedComboPopup::OnDrawBg(wxDC &dc, const wxRect &rect, int item, int flags) const
{
    // We need only to explicitly draw background for items
    // that should have selected background. Also, call PrepareBackground
    // always when painting the control so that clipping is done properly.

    if((flags & SCB_PAINTING_SELECTED) || IsCurrent(item))
    {
        int bgFlags = wxCONTROL_SELECTED;

        if(!(flags & SCB_PAINTING_CONTROL))
            bgFlags |= wxCONTROL_ISSUBMENU;

        m_combo->PrepareBackground(dc, rect, bgFlags);
    }
}

void SharedComboPopup::OnDrawBackground(wxDC &dc, const wxRect &rect, size_t n) const
{
    OnDrawBg(dc, rect, n, 0);
}

// This is called from SharedComboPopup::OnDrawItem, with text colour and font prepared
void SharedComboPopup::OnDrawItem(wxDC &dc, const wxRect &rect, int item, int flags) const
{
    if(flags & SCB_PAINTING_CONTROL)
    {
        dc.DrawText(m_combo->GetValue(), rect.x + m_combo->GetMargins().x, (rect.height-dc.GetCharHeight())/2 + rect.y);
    }
    else
    {
        dc.DrawText(GetString(item), rect.x + 2, rect.y);
    }
}

void SharedComboPopup::DismissWithEvent()
{
    StopPartialCompletion();

    int selection = wxVListBox::GetSelection();

    Dismiss();

    if(selection != wxNOT_FOUND)
        m_stringValue = (*s_strings)[selection];
    else
        m_stringValue = wxEmptyString;

    if(m_stringValue != m_combo->GetValue())
        m_combo->SetValueByUser(m_stringValue);

    m_value = selection;

    SendComboBoxEvent(selection);
}

void SharedComboPopup::SendComboBoxEvent(int selection)
{
    wxCommandEvent evt(wxEVT_COMBOBOX,m_combo->GetId());

    evt.SetEventObject(m_combo);

    evt.SetInt(selection);

    m_combo->GetEventHandler()->AddPendingEvent(evt);
}

// returns true if key was consumed
bool SharedComboPopup::HandleKey(int keycode, bool saturate, wxChar keychar)
{
    const int itemCount = GetCount();

    // keys do nothing in the empty control and returning immediately avoids
    // using invalid indices below
    if(!itemCount)
        return false;

    int value = m_value;
    int comboStyle = m_combo->GetWindowStyle();

    if(keychar > 0)
    {
        // we have character equivalent of the keycode; filter out these that
        // are not printable characters
        if(!wxIsprint(keychar))
            keychar = 0;
    }

    const bool readOnly = (comboStyle & wxCB_READONLY) != 0;

    if(keycode == WXK_DOWN || keycode == WXK_NUMPAD_DOWN || (keycode == WXK_RIGHT && readOnly))
    {
        ++value;
        StopPartialCompletion();
    }
    else if(keycode == WXK_UP || keycode == WXK_NUMPAD_UP || (keycode == WXK_LEFT && readOnly))
    {
        --value;
        StopPartialCompletion();
    }
    else if(keycode == WXK_PAGEDOWN || keycode == WXK_NUMPAD_PAGEDOWN)
    {
        value+=10;
        StopPartialCompletion();
    }
    else if(keycode == WXK_PAGEUP || keycode == WXK_NUMPAD_PAGEUP)
    {
        value-=10;
        StopPartialCompletion();
    }
    else if((keycode == WXK_HOME || keycode == WXK_NUMPAD_HOME) && readOnly)
    {
        value=0;
        StopPartialCompletion();
    }
    else if((keycode == WXK_END || keycode == WXK_NUMPAD_END) && readOnly)
    {
        value=itemCount-1;
        StopPartialCompletion();
    }
    else if(keychar && readOnly)
    {
        // Try partial completion

        // find the new partial completion string
#if wxUSE_TIMER
        if(m_partialCompletionTimer.IsRunning())
            m_partialCompletionString+=wxString(keychar);
        else
#endif// wxUSE_TIMER
            m_partialCompletionString=wxString(keychar);

        // now search through the values to see if this is found
        int i, found = -1;
        unsigned int length=m_partialCompletionString.length();
        for(i=0; i<itemCount; ++i)
        {
            wxString item=GetString(i);
            if((item.length() >= length) && (!m_partialCompletionString.CmpNoCase(item.Left(length))))
            {
                found=i;
                break;
            }
        }

        if(found<0)
        {
            StopPartialCompletion();
            ::wxBell();
            return true; // to stop the first value being set
        }
        else
        {
            value=i;
#if wxUSE_TIMER
            m_partialCompletionTimer.Start(SCB_PARTIAL_COMPLETION_TIME, true);
#endif// wxUSE_TIMER
        }
    }
    else
        return false;

    if(saturate)
    {
        if(value >= itemCount)
            value = itemCount - 1;
        else if(value < 0)
            value = 0;
    }
    else
    {
        if(value >= itemCount)
            value -= itemCount;
        else if(value < 0)
            value += itemCount;
    }

    if(value == m_value)
        // Even if value was same, don't skip the event
        // (good for consistency)
        return true;

    if(value >= 0)
        m_combo->ChangeValue((*s_strings)[value]);

    // The m_combo->SetValue() call above sets m_value to the index of this
    // string. But if there are more identical string, the index is of the
    // first occurrence, which may be wrong, so set the index explicitly here,
    // _after_ the SetValue() call.
    m_value = value;

    SendComboBoxEvent(m_value);

    return true;
}

// stop partial completion
void SharedComboPopup::StopPartialCompletion()
{
    m_partialCompletionString = wxEmptyString;
#if wxUSE_TIMER
    m_partialCompletionTimer.Stop();
#endif// wxUSE_TIMER
}

void SharedComboPopup::OnComboDoubleClick()
{
    // Cycle on dclick (disable saturation to allow true cycling).
    if(!::wxGetKeyState(WXK_SHIFT))
        HandleKey(WXK_DOWN,false);
    else
        HandleKey(WXK_UP,false);
}

void SharedComboPopup::OnComboKeyEvent(wxKeyEvent &event)
{
    // Saturated key movement on
    if(!HandleKey(event.GetKeyCode(), true))
        event.Skip();
}

void SharedComboPopup::OnComboCharEvent(wxKeyEvent &event)
{
    // unlike in OnComboKeyEvent, wxEVT_CHAR contains meaningful
    // printable character information, so pass it
#if wxUSE_UNICODE
    const wxChar charcode = event.GetUnicodeKey();
#else
    const wxChar charcode = (wxChar)event.GetKeyCode();
#endif

    if(!HandleKey(event.GetKeyCode(), true, charcode))
        event.Skip();
}

void SharedComboPopup::OnPopup()
{
    // *must* set value after size is set (this is because of a vlbox bug)
    wxVListBox::SetSelection(m_value);
}

void SharedComboPopup::OnMouseMove(wxMouseEvent &event)
{
    event.Skip();

    // Move selection to cursor if it is inside the popup

    int y = event.GetPosition().y;
    int fromBottom = GetClientSize().y - y;

    // Since in any case we need to find out if the last item is only
    // partially visible, we might just as well replicate the HitTest
    // loop here.
    const size_t lineMax = GetVisibleEnd();
    for(size_t line = GetVisibleBegin(); line < lineMax; ++line)
    {
        y -= OnGetRowHeight(line);
        if(y < 0)
        {
            // Only change selection if item is fully visible
            if((y + fromBottom) >= 0)
            {
                wxVListBox::SetSelection((int)line);
                return;
            }
        }
    }
}

void SharedComboPopup::OnKey(wxKeyEvent &event)
{
    // Hide popup if certain key or key combination was pressed
    if(m_combo->IsKeyPopupToggle(event))
    {
        StopPartialCompletion();
        Dismiss();
    }
    else if(event.AltDown())
    {
        // On both wxGTK and wxMSW, pressing Alt down seems to
        // completely freeze things in popup (ie. arrow keys and
        // enter won't work).
        return;
    }
    // Select item if ENTER is pressed
    else if(event.GetKeyCode() == WXK_RETURN || event.GetKeyCode() == WXK_NUMPAD_ENTER)
    {
        DismissWithEvent();
    }
    else
    {
        // completion is handled in OnChar() below
        event.Skip();
    }
}

void SharedComboPopup::OnChar(wxKeyEvent &event)
{
    if(m_combo->GetWindowStyle() & wxCB_READONLY)
    {
        // Process partial completion key codes here, but not the arrow keys as
        // the base class will do that for us
#if wxUSE_UNICODE
        const wxChar charcode = event.GetUnicodeKey();
#else
        const wxChar charcode = (wxChar)event.GetKeyCode();
#endif
        if(wxIsprint(charcode))
        {
            OnComboCharEvent(event);
            SetSelection(m_value); // ensure the highlight bar moves
            return; // don't skip the event
        }
    }

    event.Skip();
}

void SharedComboPopup::Clear()
{
    wxASSERT(m_combo);

    m_widths.Empty();

    m_widestWidth = 0;
    m_widestItem = -1;

    m_value = wxNOT_FOUND;

    if(IsCreated())
        wxVListBox::SetItemCount(0);
}

bool SharedComboPopup::FindItem(const wxString &item, wxString *trueItem)
{
    int idx = s_strings->Index(item, false);
    if(idx == wxNOT_FOUND)
        return false;
    if(trueItem != NULL)
        *trueItem = (*s_strings)[idx];
    return true;
}

void SharedComboPopup::SetSelection(int item)
{
    wxCHECK_RET(item == wxNOT_FOUND || ((unsigned int)item < GetCount()),
                 wxT("invalid index in SharedComboPopup::SetSelection"));

    m_value = item;

    if(item >= 0)
        m_stringValue = (*s_strings)[item];
    else
        m_stringValue = wxEmptyString;

    if(IsCreated())
        wxVListBox::SetSelection(item);
}

void SharedComboPopup::SetStringValue(const wxString &value)
{
    int index = s_strings->Index(value);

    m_stringValue = value;

    if(index >= 0 && index < (int)wxVListBox::GetItemCount())
    {
        wxVListBox::SetSelection(index);
        m_value = index;
    }
}

void SharedComboPopup::CalcWidths()
{
    bool doFindWidest = m_findWidest;

    // Measure items with dirty width.
    if(m_widthsDirty)
    {
        unsigned int n = s_strings->GetCount();
        int dirtyHandled = 0;
        wxArrayInt &widths = m_widths;

        // I think using wxDC::GetTextExtent is faster than
        // wxWindow::GetTextExtent (assuming same dc is used
        // for all calls, as we do here).
        wxClientDC dc(m_combo);

        for(unsigned int i=0; i<n; ++i)
        {
            if(widths[i] < 0)
            {
                wxCoord x = OnMeasureItemWidth(i);

                if(x < 0)
                {
                    const wxString &text = (*s_strings)[i];

                    // To make sure performance won't suck in extreme scenarios,
                    // we'll estimate length after some arbitrary number of items
                    // have been checked precily.
                    if(dirtyHandled < 1024)
                    {
                        wxCoord y;
                        dc.GetTextExtent(text, &x, &y, 0, 0);
                        x += 4;
                    }
                    else
                    {
                        x = text.length() * (dc.GetCharWidth()+1);
                    }
                }

                widths[i] = x;

                if(x >= m_widestWidth)
                {
                    m_widestWidth = x;
                    m_widestItem = (int)i;
                }
                else if((int)i == m_widestItem)
                {
                    // Width of previously widest item has been decreased, so
                    // we'll have to check all to find current widest item.
                    doFindWidest = true;
                }

                ++dirtyHandled;
            }
        }

        m_widthsDirty = false;
    }

    if(doFindWidest)
    {
        unsigned int n = s_strings->GetCount();

        int bestWidth = -1;
        int bestIndex = -1;

        for(unsigned int i=0; i<n; ++i)
        {
            int w = m_widths[i];
            if(w > bestWidth)
            {
                bestIndex = (int)i;
                bestWidth = w;
            }
        }

        m_widestWidth = bestWidth;
        m_widestItem = bestIndex;

        m_findWidest = false;
    }
}

wxSize SharedComboPopup::GetAdjustedSize(int minWidth, int prefHeight, int maxHeight)
{
    int height = 250;

    maxHeight -= 2;  // Must take borders into account

    if(s_strings->GetCount())
    {
        if(prefHeight > 0)
            height = prefHeight;

        if(height > maxHeight)
            height = maxHeight;

        int totalHeight = GetTotalHeight(); // + 3;

        if(height >= totalHeight)
        {
            height = totalHeight;
        }
        else
        {
            // Adjust height to a multiple of the height of the first item
            // NB: Calculations that take variable height into account
            //     are unnecessary.
            int fih = GetLineHeight(0);
            height -= height % fih;
        }
    }
    else
        height = 50;

    CalcWidths();

    // Take scrollbar into account in width calculations
    int widestWidth = m_widestWidth + wxSystemSettings::GetMetric(wxSYS_VSCROLL_X);
    return wxSize(minWidth > widestWidth ? minWidth : widestWidth, height+2);
}

void SharedComboPopup::Imbue(wxArrayString *choices)
{
    s_strings = choices;

    Flash();
}

void SharedComboPopup::Flash()
{
    int n = s_strings->GetCount();

    m_widths.SetCount(n, -1);
    m_widthsDirty = true;

    if(IsCreated()) wxVListBox::SetItemCount(n);
}
