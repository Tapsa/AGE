/* AGE_ScrolledWindow.cpp */

#include "AGE_ScrolledWindow.h"

void AGE_ScrolledWindow::OnSize(wxSizeEvent& Event)
{
	wxScrolledWindow::HandleOnSize(Event);
	SetAutoLayout(false);
	GetSizer()->SetDimension(0, 0, GetSize().GetWidth() - 15, 1), Scroll(0, 0), FitInside();
}

AGE_ScrolledWindow::AGE_ScrolledWindow(wxWindow * parent, long style)
: wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, style)
{
	Connect(this->GetId(), wxEVT_SIZE, wxSizeEventHandler(AGE_ScrolledWindow::OnSize));
}
