#pragma once
#include <string>
#include <direct.h>
#include <iostream>
#include <fstream>

class Security {

protected:

	std::string m_username;
	bool m_loggedIn;

public:

	Security();

	bool GetLogInStatus() const;

	void LogIn();
	void LogOut();
	void ChangePassword();
	void ResetAccount();
	

};