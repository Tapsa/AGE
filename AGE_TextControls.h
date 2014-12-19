#include "Common.h"

//	The purpose of these custom text controls is that you get specified error messages
//	when your mouse cursor focus gets off from a data edit box.

#ifndef AGE_TextControls_h
#define AGE_TextControls_h

class AGELinkedBox
{
public:
	virtual void Update(int)=0;
};

class AGETextCtrl: public wxTextCtrl
{
public:
	AGETextCtrl(wxWindow *parent, wxString value):
	wxTextCtrl(parent, wxID_ANY, value, wxDefaultPosition, wxSize(0, 20)){}

	void OnKillFocus(wxFocusEvent &Event){SaveEdits(); Event.Skip();}
	virtual int SaveEdits()=0;
	virtual void Update()=0;
	void resize(int size){container.resize(size);}
	bool BatchCheck(wxString &value, short &batchMode)
	{
		if(value.size() < 3) return false;
		switch((char)value[1])
		{
			case '+': batchMode = 1; value = value.substr(2); return true;
			case '-': batchMode = 2; value = value.substr(2); return true;
			case '*': batchMode = 3; value = value.substr(2); return true;
			case '/': batchMode = 4; value = value.substr(2); return true;
			case '%': batchMode = 5; value = value.substr(2); return true;
			default: return false;
		}
	}

	AGELinkedBox *LinkedBox; // These are for check and combo boxes.
	static const wxString BATCHWARNING, BWTITLE, IETITLE;
	static bool editable, hexMode, accurateFloats;
	vector<void*> container;
};

class TextCtrl_DLL: public wxTextCtrl
{
public:
	TextCtrl_DLL(wxWindow *parent, wxSize dimensions):
	wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, dimensions, wxTE_MULTILINE | wxTE_PROCESS_ENTER){}

	int index;
};

class TextCtrl_Byte: public AGETextCtrl
{
public:
	TextCtrl_Byte(wxWindow *parent):
	AGETextCtrl(parent, "")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(255, 235, 215));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));	// Must-have
	}
	int SaveEdits();
	void Update();
};

class TextCtrl_UByte: public AGETextCtrl
{
public:
	TextCtrl_UByte(wxWindow *parent):
	AGETextCtrl(parent, "")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(255, 235, 215));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UByte::OnKillFocus));
	}
	int SaveEdits();
	void Update();
};

class TextCtrl_Float: public AGETextCtrl
{
public:
	TextCtrl_Float(wxWindow *parent):
	AGETextCtrl(parent, "")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(255, 225, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
	}
	int SaveEdits();
	void Update();
};

class TextCtrl_Long: public AGETextCtrl
{
public:
	TextCtrl_Long(wxWindow *parent):
	AGETextCtrl(parent, "")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(215, 255, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
	}
	int SaveEdits();
	void Update();
};

class TextCtrl_Short: public AGETextCtrl
{
public:
	TextCtrl_Short(wxWindow *parent):
	AGETextCtrl(parent, "")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(210, 230, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
	}
	int SaveEdits();
	void Update();
};

class TextCtrl_UShort: public AGETextCtrl
{
public:
	TextCtrl_UShort(wxWindow *parent):
	AGETextCtrl(parent, "")
	{
		LinkedBox = NULL;
		SetBackgroundColour(wxColour(210, 230, 255));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UShort::OnKillFocus));
	}
	int SaveEdits();
	void Update();
};

class TextCtrl_String: public AGETextCtrl
{
public:
	TextCtrl_String(wxWindow *parent, unsigned short CLength = 0):
	AGETextCtrl(parent, "")
	{
		MaxSize = CLength;
		SetBackgroundColour(wxColour(220, 255, 220));
		Connect(GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_String::OnKillFocus));
	}
	int SaveEdits();
	void Update();
	void SetMaxSize(unsigned short Size){MaxSize = Size;}
	unsigned short MaxSize;
};

#endif
