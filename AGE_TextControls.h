#include "Common.h"
using std::string;
using boost::lexical_cast;
using boost::bad_lexical_cast;

//	The purpose of these custom text controls is that you get specified error messages
//	when your mouse cursor focus gets off from a data edit box.

#ifndef AGE_TextControls_h
#define AGE_TextControls_h

class TextCtrl_Bool: public wxTextCtrl
{
	public:

	TextCtrl_Bool(wxWindow *parent, string InitValue, bool *Pointer):
	wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(255, 255, 205));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Bool::OnKillFocus));	// Must-have
	}

//	Events

	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	bool *Container;
	void *ParentContainer;
	bool NoLoadList;
};

class TextCtrl_Byte: public wxTextCtrl
{
	public:

	TextCtrl_Byte(wxWindow *parent, string InitValue, char *Pointer):
	wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(255, 235, 215));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));	// Must-have
	}

//	Events

	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	char *Container;
	void *ParentContainer;	//	These are for check and combo boxes.
	bool NoLoadList;
};

class TextCtrl_UByte: public wxTextCtrl
{
	public:

	TextCtrl_UByte(wxWindow *parent, string InitValue, unsigned char *Pointer):
	wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(255, 235, 215));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UByte::OnKillFocus));	// Must-have
	}

//	Events

	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	unsigned char *Container;
	void *ParentContainer;	//	These are for check and combo boxes.
	bool NoLoadList;
};

class TextCtrl_Float: public wxTextCtrl
{
	public:

	TextCtrl_Float(wxWindow *parent, string InitValue, float *Pointer):
	wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(255, 225, 255));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
	}

//	Events

	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	float *Container;
	void *ParentContainer;
	bool NoLoadList;
};

class TextCtrl_Long: public wxTextCtrl
{
	public:

	TextCtrl_Long(wxWindow *parent, string InitValue, int32_t *Pointer):
	wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(215, 255, 255));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
	}

//	Events

	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	int32_t *Container;
	void *ParentContainer;
	bool NoLoadList;
};

class TextCtrl_Short: public wxTextCtrl
{
	public:

	TextCtrl_Short(wxWindow *parent, string InitValue, int16_t *Pointer):
	wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(210, 230, 255));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
	}

//	Events

	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	int16_t *Container;
	void *ParentContainer;
	bool NoLoadList;
};

class TextCtrl_UShort: public wxTextCtrl
{
	public:

	TextCtrl_UShort(wxWindow *parent, string InitValue, uint16_t *Pointer):
	wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(210, 230, 255));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UShort::OnKillFocus));
	}

//	Events

	void OnKillFocus(wxFocusEvent &Event);

//	Member Variables

	uint16_t *Container;
	void *ParentContainer;
	bool NoLoadList;
};

class TextCtrl_String: public wxTextCtrl
{
	public:

	TextCtrl_String(wxWindow *parent, string InitValue, string *Pointer, int16_t CLength = -1):
	wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20))
	{
		Container = Pointer;
		MaxSize = CLength;
		this->SetBackgroundColour(wxColour(220, 255, 220));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_String::OnKillFocus));
	}

//	Events

	void OnKillFocus(wxFocusEvent &Event);
	void SetMaxSize(int16_t Size){MaxSize = Size;}

//	Member Variables

	int16_t MaxSize;
	string *Container;
	bool NoLoadList;
};

#endif
