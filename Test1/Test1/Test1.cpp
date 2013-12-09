// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <sstream>

using namespace std;
typedef int ciccio;
typedef void(*InitializeModel)(bool t);
typedef void(*StepModel)(void);
typedef void(*TerminateModel)(void);


void ManageError(void * Method, string methodName)
{
	if (Method == nullptr)
	{
		DWORD error = GetLastError();
		wstringstream ss;
		ss << "Errore " << error << " chiamando il metodo " << methodName.c_str() << endl;
		OutputDebugString(ss.str().c_str());

	}
}

int _tmain(int argc, _TCHAR* argv[])
{


	std::wstring path = L"C:\\Users\\guido\\Documents\\MATLAB\\";
	std::wstring dllName = L"ToBeCompiled_win32.dll";
	std::wstring fullPath = path + dllName;

	SetDllDirectory(path.c_str());
	auto handle = LoadLibrary(fullPath.c_str());

	if (handle != nullptr)
		OutputDebugString(L"tutto ok");

	string methodName = "_ToBeCompiled_initialize";
	InitializeModel initModel;		
	initModel = (InitializeModel)GetProcAddress(handle, methodName.c_str());
	ManageError(initModel, methodName);
	
	methodName = "_ToBeCompiled_step";
	StepModel stepModel;	
	stepModel = (StepModel)GetProcAddress(handle, methodName.c_str());
	ManageError(stepModel, methodName);

	methodName = "_ToBeCompiled_terminate";
	TerminateModel terminateModel;
	terminateModel = (TerminateModel)GetProcAddress(handle, methodName.c_str());
	ManageError(terminateModel, methodName);
	

	initModel(true);
	for (int i = 0; i < 100; i++)
		stepModel();
	terminateModel();

	SetDllDirectory(nullptr);
	while (FreeLibrary(handle));
}

