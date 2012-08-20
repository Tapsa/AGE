/* AGE_SFML.h */

#include <SFML/Graphics.hpp>
#include <wx/wx.h>

#ifndef SFML_Canvas_h
#define SFML_Canvas_h

class SFML_Canvas : public wxControl, public sf::RenderWindow
{
public:

	sf::Sprite SLP_Sprite;

    SFML_Canvas(wxWindow * Parent, sf::Sprite Pic)
	: wxControl(Parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
	{
		SLP_Sprite = Pic;
		sf::RenderWindow::Create(GetHandle());
	}
	~SFML_Canvas(){};

private:

	DECLARE_EVENT_TABLE()

	void OnUpdate();
	{
		// Clear the view
		Clear(sf::Color(0, 128, 128));

		// Display the sprite in the view
		Draw(SLP_Sprite);
	}
	void OnIdle(wxIdleEvent&)
	{
		// Send a paint message when the control is idle, to ensure maximum framerate
		Refresh(); // There is no reason to do this.
	}
	void OnPaint(wxPaintEvent&)
	{
		// Prepare the control to be repainted
		wxPaintDC Dc(this);

		// Let the derived class do its specific stuff
		OnUpdate();

		// Display on screen
		Display();
	}
	void OnEraseBackground(wxEraseEvent&){};
};

#endif
