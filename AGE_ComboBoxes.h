#include "AGE_TextControls.h"

#ifndef AGE_ComboBoxes_h
#define AGE_ComboBoxes_h

class AGEListCtrl: public wxListCtrl
{
	public:
	AGEListCtrl(wxWindow *parent, const wxSize &size):
	wxListCtrl(parent, wxID_ANY, wxDefaultPosition, size, wxLC_VIRTUAL | wxLC_REPORT | wxLC_NO_HEADER){}
	
	void PackItems(wxArrayString &items)
	{
		SetItemCount(items.GetCount());
		labels = items;
	}

	wxArrayString labels;

	protected:
	virtual wxString OnGetItemText(long item, long column) const
	{
		return labels[item];
	}
};

class AGEComboBox: public wxOwnerDrawnComboBox, public AGELinkedBox
{
	public:
	AGEComboBox(wxWindow *parent):
	wxOwnerDrawnComboBox(parent, wxID_ANY, "", wxDefaultPosition, wxSize(0, 20), 0, NULL, wxCB_READONLY){}

	virtual void OnUpdate(wxCommandEvent&)=0;

	AGETextCtrl *TextBox;
};

class ComboBox_Plus1: public AGEComboBox
{
	public:
	ComboBox_Plus1(wxWindow *parent, AGETextCtrl *Pointer):
	AGEComboBox(parent)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_Plus1::OnUpdate));
	}

	void OnUpdate(wxCommandEvent &Event);
	void Update(long value);
};

class ComboBox_EffectType: public AGEComboBox
{
	public:
	ComboBox_EffectType(wxWindow *parent, AGETextCtrl *Pointer):
	AGEComboBox(parent)
	{
		TextBox = Pointer;
		TextBox->LinkedBox = this;
		Connect(GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(ComboBox_EffectType::OnUpdate));
	}

	void OnUpdate(wxCommandEvent &Event);
	void Update(long value);
};

#endif
