#pragma once
#include <vector>
#include <wx/panel.h>
#include <wx/scrolwin.h>
#include <wx/stattext.h>
#include <wx/vlbox.h>

class ProperList : public wxVListBox
{
public:
    ProperList(wxWindow *parent, const wxSize &size);
    void EnsureVisible(size_t n);
    inline void Sweep() { names.clear(); indexes.clear(); }
    //inline void Add(const wxString &name, size_t i);

    wxArrayString names;
    std::vector<size_t> indexes;

private:
    inline wxCoord OnMeasureItem(size_t) const override { return row_height; }
    void OnDrawItem(wxDC &dc, const wxRect &rect, size_t n) const override;
    void OnDrawBackground(wxDC &dc, const wxRect &rect, size_t n) const override;

    int row_height = 0;
};

class SolidText : public wxStaticText
{
public:
    SolidText(wxWindow *parent, const wxString &label, long style = 0, const wxSize &size = wxDefaultSize);
};

class APanel : public wxPanel
{
public:
    APanel();
    APanel(wxWindow *parent, const wxSize &size = wxDefaultSize);

private:
    void DisableAutoScroll(void);
};

class ATabPage : public APanel
{
public:
    ATabPage(wxWindow *parent, const wxSize &size = wxDefaultSize);

    bool Show(bool show = true) override;

private:
    wxWindow *parent;
};

class AScrolled : public wxScrolled<APanel>
{
public:
    AScrolled(wxWindow *parent);

    static float rate;

private:
    float remainder;
};
