#pragma once
#include "myLoginScreen.h"


class myApp : public wxApp   //Inheriting wxApp
{
private:
	myLoginScreen* frame = nullptr;
public:
	virtual bool OnInit();
};

