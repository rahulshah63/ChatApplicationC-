#include "myApp.h"
wxIMPLEMENT_APP(myApp);

bool myApp::OnInit()  //Defination of OnInit Function
{
	wxInitAllImageHandlers();
	frame = new myLoginScreen(wxT("CHAT ROOM APP"));  //Creation of wxwidget window
	frame->Show(true);    //Display Window named "TIC TAC TOE"
	
	/*for( ; ; )
	{
		if (login == false)
			frame->Show(true);
		else
			frame->Show(false);
	}*/
	return true;
}


