#include "myLoginScreen.h"

BEGIN_EVENT_TABLE(myLoginScreen, wxFrame)
EVT_BUTTON(wxID_EXIT, myLoginScreen::OnQuit)
EVT_BUTTON(BUTTON_Login, myLoginScreen::OnLogin)
EVT_PAINT(myLoginScreen::OnPaint)
END_EVENT_TABLE()


myLoginScreen::myLoginScreen(const wxString& title) : wxFrame((wxFrame *)NULL, wxID_ANY, title, wxPoint(wxID_ANY, wxID_ANY), wxSize(750, 450),
	wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN)
{
	wxColour col1,col2;
	col1.Set(wxT("#ffffff"));
	col2.Set(wxT("#1b4960"));
	SetBackgroundColour(col1);
	SetForegroundColour(col2);
	wxFont font1(11, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	wxFont font2(13, wxFONTFAMILY_SCRIPT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	wxFont font3(15, wxFONTFAMILY_ROMAN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false);   //Increasing font
	wxFont font4(25, wxFONTFAMILY_ROMAN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false);

	info = new wxStaticText(this, wxID_ANY, wxT("Member Login"), wxPoint(140, 80));
	usernameLabel = new wxStaticText(this, wxID_ANY, wxT("Username: "), wxPoint(90,170));
	usernameEntry = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(200, 170), wxSize(180, 30));
	passwordLabel = new wxStaticText(this, wxID_ANY, wxT("Password: "), wxPoint(90,210));
	passwordEntry = new wxTextCtrl(this, wxID_ANY, wxString(""), wxPoint(200, 210), wxSize(180, 30), wxTE_PASSWORD);
	buttonLogin = new wxButton(this, BUTTON_Login, wxT("Login"), wxPoint(200, 290), wxSize(90, 35));
	buttonQuit = new wxButton(this, wxID_EXIT, ("Quit"),wxPoint(650,-1));
	cb = new wxCheckBox(this, ID_CHECKBOX, wxT("Remember Me"),wxPoint(180, 260), wxSize(200,25));
	cb->SetValue(true);

	info->SetFont(font4);
	usernameLabel->SetFont(font3);
	passwordLabel->SetFont(font3);
	cb->SetFont(font2);
	buttonLogin->SetFont(font1);
	buttonLogin->SetForegroundColour(col2);
	buttonQuit->SetFont(font1);
	buttonQuit->SetForegroundColour(col2);
	usernameEntry->SetFont(font1);
	usernameEntry->SetForegroundColour(col2);
	passwordEntry->SetFont(font1);

	Center();
}

void myLoginScreen::OnPaint(wxPaintEvent& event)  //DC Design event handelling for board
{
	wxBitmap mybitmap(wxT("image.jpg"), wxBITMAP_TYPE_ANY);
	wxPaintDC dc(this);
	wxColour col2;
	col2.Set(wxT("#1b4960"));
	dc.SetPen(wxPen(wxColor(col2),3));   //for bold black boundary
	dc.DrawRoundedRectangle(35, 50, 400, 310, 5);
	dc.DrawLine(130, 120, 350, 120);
	dc.DrawBitmap(mybitmap, wxPoint(480, 80));
}

void myLoginScreen::OnQuit(wxCommandEvent& event)
{
	Close(true);
}

void myLoginScreen::OnLogin(wxCommandEvent& event)
{
	wxString username = usernameEntry->GetValue();
	wxString password = passwordEntry->GetValue();

	if (username.empty() || password.empty())
	{
		wxMessageBox(wxT("Username or password must not empty"), wxT("Warning!"), wxICON_WARNING);
	}
	else
	{
		//login = true;
		wxMessageBox(wxT("Welcome"), wxT("Message!"), wxICON_INFORMATION);
		if (cb->GetValue())
		{
			passwordEntry->SetValue(wxT(""));
		}
		else
		{
			passwordEntry->SetValue(wxT(""));
			usernameEntry->SetValue(wxT(""));
		}
		frame = new myChatScreen(wxT("CHAT ROOM APP"));  //Creation of Chat window
		frame->Show(true);
		
	}
}


/*  image
wxInitAllImageHandlers()
wxImageHandler* jpgLoader = new wxPNGHandler();
wxImage::AddHandler(jpgLoader);
wxImage* image = new wxImage;
image.LoadFile("image.jpg");
//wxBitmap bitmap("image");
bitmap.LoadFile("image", wxBITMAP_TYPE_JPEG);
*/


//Center alignMent with sizer

/*   Layout 2
wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
vbox->SetMinSize(600, 500);
wxPanel *midPan = new wxPanel(this, -1);

wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
wxPanel* expandpanel1 = new wxPanel(midPan, -1);
hbox1->Add(expandpanel1);
hbox1->SetMinSize(600, 200);
vbox->Add(hbox1, 1, wxEXPAND);

wxStaticText* info1 = new wxStaticText(midPan, wxID_ANY, wxT("Member LogIn"));
wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
hbox2->Add(info1);
vbox -> Add(hbox2, 1, wxALIGN_CENTER , 50);

wxStaticText* name = new wxStaticText(midPan, wxID_ANY, wxT("USERNAME : "));
wxTextCtrl* nametext = new wxTextCtrl(midPan, 1000, wxEmptyString);
wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
hbox3->Add(name);
hbox3->Add(nametext);
wxBoxSizer* vbox9 = new wxBoxSizer(wxVERTICAL);
vbox9->Add(hbox3, 1, wxALIGN_CENTER, 10);

wxStaticText* password = new wxStaticText(midPan, wxID_ANY, wxT("PASSWORD : "));
wxTextCtrl* passwordtext = new wxTextCtrl(midPan, 1001, wxEmptyString);
wxBoxSizer* hbox4 = new wxBoxSizer(wxHORIZONTAL);
hbox4->Add(password);
hbox4->Add(passwordtext);

vbox9->Add(hbox4, 1, wxALIGN_CENTER, 10);
vbox->Add(vbox9, 1, wxALIGN_CENTER, 80);


wxBoxSizer* vbox5 = new wxBoxSizer(wxVERTICAL);
vbox5->Add(cb, 1, wxALIGN_CENTER, 40);

wxButton* connect = new wxButton(midPan, 10001, "LOG IN");
vbox5->Add(connect, 0, wxALIGN_CENTER, 40);
vbox->Add(vbox5, 1, wxALIGN_CENTER, 80);


wxBoxSizer* hbox7 = new wxBoxSizer(wxHORIZONTAL);
wxPanel* expandpanel = new wxPanel(midPan, -1);
expandpanel->SetBackgroundColour(col1);
hbox7->Add(expandpanel);
hbox7->SetMinSize(600, 20);
vbox->Add(hbox7, 1, wxEXPAND);

midPan->SetSizer(vbox);

connect->SetFont(font);
password->SetFont(font);
name->SetFont(font);
info1->SetFont(font2);
*/

//Left lignment with expandable sizer

/*   Layout 3
wxPanel *panel = new wxPanel(this, -1);
panel->SetBackgroundColour(col1);
wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
wxBoxSizer *Hbox = new wxBoxSizer(wxHORIZONTAL);
wxStaticText* info = new wxStaticText(panel, wxID_ANY, wxT("WELCOME TO AWASOME CHATROOM."));
info->SetForegroundColour(col2);
Hbox->Add(info);
vbox->Add(Hbox, 0, wxALIGN_LEFT | wxLEFT | wxEXPAND, 5);

wxPanel *midPan = new wxPanel(panel, -1, wxPoint(400, 100), wxSize(350, 520));  //
midPan->SetBackgroundColour(col2);
wxStaticText* info1 = new wxStaticText(midPan, wxID_ANY, wxT("Member LogIn"), wxPoint(200, 90));
wxStaticText* name = new wxStaticText(midPan, wxID_ANY, wxT("USERNAME : "), wxPoint(110, 164));
wxTextCtrl* nametext = new wxTextCtrl(midPan, 1000, wxEmptyString, wxPoint(220, 160), wxSize(250, 30));
wxStaticText* password = new wxStaticText(midPan, wxID_ANY, wxT("PASSWORD : "), wxPoint(110, 214));
wxTextCtrl* passwordtext = new wxTextCtrl(midPan, 1001, wxEmptyString, wxPoint(220, 210), wxSize(250, 30));


wxButton* connect = new wxButton(midPan, 10001, "LOG IN", wxPoint(200, 290), wxSize(80, 35));

vbox->Add(midPan, 0, wxEXPAND);

//wxImage image(wxT("image.jpg"));
//wxBitmap bitmap(image);

panel->SetSizer(vbox);

cb->SetFont(font3);
connect->SetFont(font);
password->SetFont(font);
name->SetFont(font);
info->SetFont(font2);
info1->SetFont(font2);


Connect(10001, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(myLoginScreen::OnButtonClicked));

*/