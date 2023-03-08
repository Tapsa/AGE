#include "Common.h"
#include "CustomWidgets.h"

float AScrolled::rate;

ProperList::ProperList(wxWindow *parent, const wxSize &size) :
    wxVListBox(parent, wxID_ANY, wxDefaultPosition, size, wxLB_INT_HEIGHT | wxLB_MULTIPLE)//wxLB_EXTENDED)
{
    SetItemCount(0);
    row_height = GetCharHeight();
}

void ProperList::OnDrawItem(wxDC &dc, const wxRect &rect, size_t n) const
{
    dc.SetTextForeground(wxSystemSettings::GetColour(IsSelected(n) ?
        wxSYS_COLOUR_HIGHLIGHTTEXT : wxSYS_COLOUR_WINDOWTEXT));
    dc.DrawText(names[n], rect.x + 2, rect.y);
}

void ProperList::OnDrawBackground(wxDC &dc, const wxRect &rect, size_t n) const
{
    if (IsSelected(n))
    {
        dc.SetBrush(static wxBrush(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT), wxBRUSHSTYLE_SOLID));
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.DrawRectangle(rect);
    }
}

void ProperList::EnsureVisible(size_t n)
{
    if (!IsRowVisible(n))
    {
        size_t ve = GetVisibleRowsEnd();
        if (n > ve)
        {
            ScrollRows(n - ve);
        }
        else
        {
            ScrollToRow(n);
        }
    }
}

SolidText::SolidText(wxWindow *parent, const wxString &label, long style, const wxSize &size) :
    wxStaticText(parent, wxID_ANY, label, wxDefaultPosition, size, style)
{
    Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent &) {});
}

APanel::APanel() : wxPanel()
{
    DisableAutoScroll();
}

APanel::APanel(wxWindow *parent, const wxSize &size) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, size)
{
    DisableAutoScroll();
}

// Prevent jumping back to last focused child or sibling
void APanel::DisableAutoScroll(void)
{
    Bind(wxEVT_CHILD_FOCUS, [](wxChildFocusEvent &) {}); // No scrolling
    Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent &)
    {
        SetFocusIgnoringChildren();
    });
}

ATabPage::ATabPage(wxWindow *parent, const wxSize &size) :
    APanel(parent, size), parent(parent)
{
}

bool ATabPage::Show(bool show)
{
    // Reduced window move lag
    if (show)
    {
        Reparent(parent);
        return APanel::Show(true);
    }
    bool result = APanel::Show(false);
    Reparent(nullptr);
    return result;
}

AScrolled::AScrolled(wxWindow *parent) :
    wxScrolled<APanel>(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxTAB_TRAVERSAL),
    remainder(0)
{
    // Smooth scrolling
    Bind(wxEVT_MOUSEWHEEL, [this](wxMouseEvent &event)
    {
        float rotation = static_cast<float>(event.GetWheelRotation());
        if (remainder != 0 && (remainder < 0) ^ (rotation < 0))
        {
            remainder = 0;
        }
        float scaled = rate * rotation + remainder;
        int lines = static_cast<int>(scaled);
        if (lines != 0)
        {
            int pos;
            remainder = scaled - static_cast<float>(lines);
            GetViewStart(&pos, &pos);
            Scroll(0, std::max(pos - lines, 0));
        }
    });

    // Pixel perfect scroll rate.
    SetScrollRate(0, 1);
}
