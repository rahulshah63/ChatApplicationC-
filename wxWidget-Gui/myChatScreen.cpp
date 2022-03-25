#include "myChatScreen.h"
#include<string>

// Add the event handler to the event table. As you can see we use
// the window ID to link the event handler to the wxSplitterWindow we created.
wxBEGIN_EVENT_TABLE(myChatScreen, wxFrame)
	EVT_MENU(SplitMenuID, myChatScreen::OnMenuSplit)
	EVT_MENU(wxID_EXIT, myChatScreen::OnLogOut)
	EVT_SPLITTER_UNSPLIT(SplitterWindowID, myChatScreen::OnUnsplit)
	EVT_BUTTON(wxID_SEND, myChatScreen::OnSend)
	EVT_BUTTON(wxID_GLOBALSEND, myChatScreen::OnGlobalSend)
	//EVT_BUTTON(wxID_BUTCONN, myChatScreen::FunConnect)
	EVT_SOCKET(wxID_SOCKET, myChatScreen::OnSocketEvent)
wxEND_EVENT_TABLE()

myChatScreen::myChatScreen(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition)

{
	wxFont font(10, wxFONTFAMILY_MODERN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false);   //Increasing font
	wxFont font2(15, wxFONTFAMILY_MODERN, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_BOLD, false);

	// Create a menu with a checkable item to
	// toggle between the split and unsplit states
	menuBar = new wxMenuBar;
	viewMenu = new wxMenu;
	menuBar->Append(viewMenu, "&View");
	viewMenu->AppendCheckItem(SplitMenuID, "Split");
	viewMenu->Check(SplitMenuID, true);
	quit = new wxMenuItem(viewMenu, wxID_EXIT, "&Log Out   \tCtrl-Q");
	viewMenu->AppendSeparator();
	viewMenu->Append(quit);
	SetMenuBar(menuBar);

	// Create the wxSplitterWindow window
	splitterWindow = new wxSplitterWindow(this, SplitterWindowID);

	// Create the left panel
	panel1 = new wxPanel(splitterWindow, wxID_ANY);
	panel1Sizer1 = new wxBoxSizer(wxHORIZONTAL);
	info = new wxStaticText(panel1, wxID_ANY, wxT("Direct Message Room (DM)"));
	panel1Sizer1->Add(info, 1, wxALIGN_CENTER, 20);
	panel1Sizer2 = new wxBoxSizer(wxHORIZONTAL);
	send = new wxStaticText(panel1, wxID_ANY, wxT("Request for TIC TAC TOE : "));
	panel1Sizer2->Add(send, 1, wxALIGN_CENTER, 20);
	for (int i = 0; i < 3; i++)
	{
		btn[i] = new wxButton(panel1, 10000+i, wxT("User"));
		//btn[i]->SetLabel();
		btn[i]->SetFont(font);
		panel1Sizer2->Add(btn[i], 1, wxALIGN_CENTER, 10000+i);
		Connect(10000+i, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(myChatScreen::OnGame));  //Binding event on clicking a button
	}

	panel1Sizer3 = new wxBoxSizer(wxHORIZONTAL);
	textCtrl1 = new wxTextCtrl(panel1, wxID_ANY, wxT("Write Messages"), wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);   //, wxSize(150, 150)
	panel1Sizer3->Add(textCtrl1, 1, wxEXPAND, 50);
	//panel1Sizer3->SetMinSize(600, 50);
	panel1Sizer4 = new wxBoxSizer(wxHORIZONTAL);
	sendto = new wxStaticText(panel1, wxID_ANY, wxT("Send TO : "));
	panel1Sizer4->Add(sendto, 0, wxALIGN_CENTER, 20);
	cb = new wxComboBox(panel1, wxID_ANY, wxT("Select user",), wxDefaultPosition, wxSize(50,20));
	panel1Sizer4->Add(cb, 1, wxALIGN_CENTER, 20);
	sendbtn = new wxButton(panel1, wxID_SEND, wxT("Send"));
	panel1Sizer4->Add(sendbtn, 1, wxALIGN_CENTER, 50);

	panel1Sizer5 = new wxBoxSizer(wxHORIZONTAL);
	lb = new wxListBox(panel1, wxID_ANY, wxDefaultPosition);   //wxPoint(-1, -1), wxSize(-1, 50), wxTE_MULTILINE

	panel1Sizer5->Add(lb, 1, wxEXPAND, 50);
	panel1Sizer5->SetMinSize(400, 300);

	panel1Sizer6 = new wxBoxSizer(wxVERTICAL);
	panel1Sizer6->Add(panel1Sizer1, 0, wxALIGN_CENTER, 10);
	panel1Sizer6->Add(panel1Sizer2, 0, wxALIGN_CENTER, 5);
	panel1Sizer6->Add(panel1Sizer3, 0.5, wxEXPAND | wxALL, 5);
	panel1Sizer6->Add(panel1Sizer4, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 20);
	panel1Sizer6->Add(panel1Sizer5, 2, wxEXPAND | wxALL, 10);   //wxALIGN_CENTER    wxLEFT | wxRIGHT | 
	panel1->SetSizer(panel1Sizer6);

	// Create the right panel
	panel2 = new wxPanel(splitterWindow, wxID_ANY);

	panel2Sizer1 = new wxBoxSizer(wxHORIZONTAL);
	info2 = new wxStaticText(panel2, wxID_ANY, wxT("World Chat Room"));
	panel2Sizer1->Add(info2, 1, wxALIGN_CENTER, 20);

	panel2Sizer2 = new wxBoxSizer(wxHORIZONTAL);
	lb1 = new wxListBox(panel2, wxID_ANY, wxDefaultPosition); 
	panel2Sizer2->Add(lb1, 1, wxEXPAND);

	panel2Sizer3 = new wxBoxSizer(wxHORIZONTAL);
	textCtrl2 = new wxTextCtrl(panel2, wxID_ANY, wxT("Write Messages"), wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);
	panel2Sizer3->Add(textCtrl2, 1, wxEXPAND, 50);

	panel2Sizer4 = new wxBoxSizer(wxHORIZONTAL);
	btn2 = new wxButton(panel2, wxID_GLOBALSEND, wxT("Send Globally"));
	panel2Sizer4->Add(btn2);

	panel2Sizer5 = new wxBoxSizer(wxVERTICAL);
	panel2Sizer5->Add(panel2Sizer1, 0, wxALIGN_CENTER, 25);
	panel2Sizer5->Add(panel2Sizer2, 2, wxLEFT | wxRIGHT | wxEXPAND, 20);
	panel2Sizer5->Add(panel2Sizer3, 1, wxEXPAND | wxALL, 20);
	panel2Sizer5->Add(panel2Sizer4, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 20);
	panel2->SetSizer(panel2Sizer5);

	panel1->SetBackgroundColour(wxColour(wxT("#ECBB54")));
	panel2->SetBackgroundColour(wxColour(wxT("#2AA1C9")));
	info2->SetFont(font2);
	info->SetFont(font2);
	send->SetFont(font);
	sendto->SetFont(font);
	sendbtn->SetFont(font);
	btn2->SetFont(font);
	textCtrl1->SetFont(font);
	textCtrl2->SetFont(font);
	cb->SetFont(font);
	lb->SetFont(font); 

	//Connecting to the server
	wxIPV4address adr;
	adr.Hostname(_T("localhost"));
	adr.Service(3000);

	//Create the socket
	Socket = new wxSocketClient();

	Socket->SetEventHandler(*this, wxID_SOCKET);
	Socket->SetNotify(wxSOCKET_CONNECTION_FLAG | wxSOCKET_OUTPUT_FLAG | wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
	Socket->Notify(TRUE);

	Socket->Connect(adr, false);

	lb->AppendString(_T("Connecting to the server...\n"));
	lb->AppendString(_T("Connecting...\n"));

	lb1->SetFont(font);
	lb1->AppendString(_T("Connecting to the server...\n"));
	lb1->AppendString(_T("Connecting...\n"));

		// Split the window vertically and set the left and right panes
	splitterWindow->SplitVertically(panel1, panel2, 400);

	// Set up the sizer for the frame and resize the frame
	// according to its contents
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->Add(splitterWindow, 1, wxEXPAND);
	SetSizerAndFit(topSizer);
}

// Split or unsplit the window when the "Split" menu item
// is activated
void myChatScreen::OnMenuSplit(wxCommandEvent& evt)
{
	if (!splitterWindow || !panel1 || !panel2)
	{
		return;
	}

	if (evt.IsChecked())
	{
		splitterWindow->SplitVertically(panel1, panel2, 400);
	}
	else
	{
		splitterWindow->Unsplit();
	}
}

// When the window becomes unsplit this event handler
// ensures the checkable menu item gets unchecked
void myChatScreen::OnUnsplit(wxSplitterEvent& evt)
{
	if (viewMenu)
	{
		viewMenu->Check(SplitMenuID, false);
	}

	evt.Skip();
}



void myChatScreen::OnGame(wxCommandEvent& event)
{
	frame = new myGame(wxT("TIC TAC TOE"));
	frame->Show(true);
	event.Skip();
}


void myChatScreen::OnSend(wxCommandEvent& event)
{
	//wxStaticLine *sl2 = new wxStaticLine(lb, wxID_ANY);
	sendmsg = true;
	lb->Append(wxT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------"));
	textCtrl1->SetValue(wxT(""));
	event.Skip();
}
void myChatScreen::OnGlobalSend(wxCommandEvent& event)
{
	Gsendmsg = true;
	lb1->Append(wxT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------"));
	textCtrl2->SetValue(wxT(""));
	event.Skip();
}

void myChatScreen::OnLogOut(wxCommandEvent& event)
{
	Close();
	Close(true);
	//login = false;
	event.Skip();
}

void myChatScreen::OnSocketEvent(wxSocketEvent &evt)
{
	wxString str, Gstr;
	wxSocketBase *Sock = evt.GetSocket();
	switch (evt.GetSocketEvent())
	{
	case wxSOCKET_CONNECTION:
	{
		lb->AppendString(_T("OnSocketEvent(wxSOCKET_CONNECTION) Connection successful\n"));
		lb->Append(wxT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"));
		lb->Append("Privately Sent Messages");
		lb->Append(wxT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"));
		lb1->Append(wxT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"));
		lb1->Append(wxT("Globally Sent Messages"));
		lb1->Append(wxT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"));
		break;
	}

	case wxSOCKET_OUTPUT:
	{
		 str = (textCtrl1->GetValue());
		 Gstr = (textCtrl2->GetValue());
		if (sendmsg == true && str.length() > 0)
		{
			for (int i = 0; i < str.length(); ++i)
			{
				buffer[i] = str[i];
			}
			Sock->Write(buffer, sizeof(buffer));

			lb->AppendString(wxString("Sent To Client 1  :   ") + buffer + "\n");
			ZeroMemory(buffer, 4096);
			lb->Append(wxT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"));
			sendmsg = false;
		}

		if (Gsendmsg == true && Gstr.length() > 0)
		{
			for (int i = 0; i < Gstr.length(); ++i)
			{
				buffer[i] = Gstr[i];
			}
			Sock->Write(buffer, sizeof(buffer));

			lb1->AppendString(wxString("Sent To Client 1  :   ") + buffer + "\n");
			ZeroMemory(buffer, 4096);
			lb1->Append(wxT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"));
			Gsendmsg = false;
		}
			break;
	}

	case wxSOCKET_INPUT:
	{
		Sock->Read(buffer, sizeof(buffer));
		if (sizeof(buffer)>0)
		{
			if (recmsg)
			{
				lb->AppendString(wxString("Received From Client 1   ") + buffer + "\n");
				ZeroMemory(buffer, 4096);
				lb->Append(wxT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"));
			}
			if (Grecmsg)
			{
				lb1->AppendString(wxString("Received From Client 1   ") + buffer + "\n");
				ZeroMemory(buffer, 4096);
				lb1->Append(wxT("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n"));
			}
			evt.Skip();
		}
		break;
	}

	case wxSOCKET_LOST:
	{
		lb->AppendString(_T("OnSocketEvent(wxSOCKET_LOST)\n"));
		lb1->AppendString(_T("OnSocketEvent(wxSOCKET_LOST)\n"));
		Sock->Destroy();
		wxMessageBox(wxT("Server Down!!!"), wxT("Warning!"), wxICON_WARNING);
		break;
	}

	default:
	{
		lb->AppendString(_T("OnSocketEvent : unknown socket event\n"));
		break;
	}
	}
}

/*
string myChatScreen::drawline()
{
	return	cstring("------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}*/