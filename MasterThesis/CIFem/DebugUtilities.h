#pragma once

#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

class DebugUtilities
{
public:
	DebugUtilities();
	~DebugUtilities();

	static int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
};

