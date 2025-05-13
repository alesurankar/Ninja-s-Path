/****************************************************************************************************** 
This Framework is Cloned and modified from PlanetChili - chili_framework <http://www.planetchili.net> 
*******************************************************************************************************/	
#include "MainWindow.h"
#include "App.h"
#include "MyException.h"

#include "TCP_Client.h"
#include <fstream>
#include <thread>
#include <atomic>
#include <chrono>

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR pArgs, INT)
{
	try
	{
		MainWindow wnd(hInst, pArgs);
		std::atomic<bool> running{ true };
		std::shared_ptr<MessageHandler> msgHandler = std::make_shared<MessageHandler>();
		try
		{
			App theApp(wnd, running, msgHandler);
			boost::asio::io_context io;
			auto client = std::make_shared<TCP_Client>(io, "127.0.0.1", 1234, "username", msgHandler);
			boost::asio::post(io, [client]()
				{
					client->Start();
				});
			std::thread networking([&]()
				{
					io.run();
				});


			while (wnd.ProcessMessage() && running)
			{
				theApp.Go();
			}
			running = false;
			networking.join();
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