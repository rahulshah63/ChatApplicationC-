#include "wx/wx.h"
#include"myChatScreen.h"
#include"wx/dcbuffer.h"
class myLoginScreen : public wxFrame
{
public:
	myLoginScreen(const wxString& title);
	myChatScreen* frame;
private:
	wxStaticText* usernameLabel;
	wxStaticText* info;
	wxStaticText* passwordLabel;
	wxTextCtrl* usernameEntry;
	wxTextCtrl* passwordEntry;
	wxButton* buttonLogin;
	wxButton* buttonQuit;
	wxCheckBox* cb;
private:
	void OnQuit(wxCommandEvent& event);
	void OnLogin(wxCommandEvent& event);
	void OnPaint(wxPaintEvent& event);
private:
	DECLARE_EVENT_TABLE()

	enum
	{
		BUTTON_Login = wxID_HIGHEST + 1
	};
};

const int ID_CHECKBOX = 100;