/****************************************************************************************************** 
This Framework is Cloned and modified from PlanetChili - chili_framework <http://www.planetchili.net> 
*******************************************************************************************************/	

#include "MainWindow.h"
#include "App.h"
#include "MyException.h"
#include "Client.h"
#include <memory>

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR pArgs, INT)
{
	try
	{
		MainWindow wnd(hInst, pArgs);
		try
		{
			auto client = std::make_unique<Client>();

			App theApp(wnd, client->GetUsername());
			while (wnd.ProcessMessage() && client->Exists())
			{
				theApp.Go();
			}
		}
		catch (const MyException& e)
		{
			const std::wstring eMsg = e.GetFullMessage() +
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox(e.GetExceptionType(), eMsg, MB_ICONERROR);
		}
		catch (const std::exception& e)
		{
			// need to convert std::exception what() string from narrow to wide string
			const std::string whatStr(e.what());
			const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) +
				L"\n\nException caught at Windows message loop.";
			wnd.ShowMessageBox(L"Unhandled STL Exception", eMsg, MB_ICONERROR);
		}
		catch (...)
		{
			wnd.ShowMessageBox(L"Unhandled Non-STL Exception",
				L"\n\nException caught at Windows message loop.", MB_ICONERROR);
		}
	}
	catch (const MyException& e)
	{
		const std::wstring eMsg = e.GetFullMessage() +
			L"\n\nException caught at main window creation.";
		MessageBox(nullptr, eMsg.c_str(), e.GetExceptionType().c_str(), MB_ICONERROR);
	}
	catch (const std::exception& e)
	{
		// need to convert std::exception what() string from narrow to wide string
		const std::string whatStr(e.what());
		const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) +
			L"\n\nException caught at main window creation.";
		MessageBox(nullptr, eMsg.c_str(), L"Unhandled STL Exception", MB_ICONERROR);
	}
	catch (...)
	{
		MessageBox(nullptr, L"\n\nException caught at main window creation.",
			L"Unhandled Non-STL Exception", MB_ICONERROR);
	}

	return 0;
}