/* AGE_TextControls.h */

#include "wx/wx.h"
#include <string>
using std::string;
#include "boost/lexical_cast.hpp"
using boost::lexical_cast;
using boost::bad_lexical_cast;

//	The purpose of these custom text controls is that you get specified error messages
//	when your mouse cursor focus gets off from a data edit box.

#ifndef TextCtrl_Bool_h
#define TextCtrl_Bool_h

class TextCtrl_Bool : public wxTextCtrl
{
	public:

	TextCtrl_Bool(wxWindow * parent, string InitValue, bool * Pointer)
	: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(255, 255, 205));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Bool::OnKillFocus));	// Must-have
	}

//	Events

	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	bool * Container;
	void * ParentContainer;
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_Byte_h
#define TextCtrl_Byte_h

class TextCtrl_Byte : public wxTextCtrl
{
	public:

	TextCtrl_Byte(wxWindow * parent, string InitValue, char * Pointer)
	: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(255, 235, 215));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Byte::OnKillFocus));	// Must-have
	}

//	Events

	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	char * Container;
	void * ParentContainer;	//	These are for check and combo boxes.
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_Float_h
#define TextCtrl_Float_h

class TextCtrl_Float : public wxTextCtrl
{
	public:

	TextCtrl_Float(wxWindow * parent, string InitValue, float * Pointer)
	: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(255, 225, 255));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Float::OnKillFocus));
	}

//	Events

	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	float * Container;
	void * ParentContainer;
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_Long_h
#define TextCtrl_Long_h

class TextCtrl_Long : public wxTextCtrl
{
	public:

	TextCtrl_Long(wxWindow * parent, string InitValue, int32_t * Pointer)
	: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(215, 255, 255));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Long::OnKillFocus));
	}

//	Events

	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	int32_t * Container;
	void * ParentContainer;
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_Short_h
#define TextCtrl_Short_h

class TextCtrl_Short : public wxTextCtrl
{
	public:

	TextCtrl_Short(wxWindow * parent, string InitValue, int16_t * Pointer)
	: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(210, 230, 255));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_Short::OnKillFocus));
	}

//	Events

	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	int16_t * Container;
	void * ParentContainer;
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_UnShort_h
#define TextCtrl_UnShort_h

class TextCtrl_UnShort : public wxTextCtrl
{
	public:

	TextCtrl_UnShort(wxWindow * parent, string InitValue, uint16_t * Pointer)
	: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
	{
		Container = Pointer;
		this->SetBackgroundColour(wxColour(210, 230, 255));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_UnShort::OnKillFocus));
	}

//	Events

	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	uint16_t * Container;
	void * ParentContainer;
	bool NoLoadList;
};

#endif

#ifndef TextCtrl_String_h
#define TextCtrl_String_h

class TextCtrl_String : public wxTextCtrl
{
	public:

	TextCtrl_String(wxWindow * parent, string InitValue, void * Pointer, short CLength = -1)
	: wxTextCtrl(parent, wxID_ANY, InitValue, wxDefaultPosition, wxSize(0, 20), 0, wxDefaultValidator)
	{
		Container = Pointer;
		Length = CLength;
		this->SetBackgroundColour(wxColour(220, 255, 220));
		Connect(this->GetId(), wxEVT_KILL_FOCUS, wxFocusEventHandler(TextCtrl_String::OnKillFocus));
	}

//	Events

	void OnKillFocus(wxFocusEvent& Event);

//	Member Variables

	short Length;
	void * Container;
	bool NoLoadList;
};

#endif
