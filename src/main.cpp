//
// Created by Kyle on 12/8/2016.
//

#include <engine.hpp>
using namespace Aurora;
#undef main
#ifdef _DEBUG
#pragma comment(linker, "/subsystem:console")
int main(char** argv, int argc)
#else
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#pragma comment(linker, "/subsystem:windows")
int CALLBACK WinMain(
	_In_		HINSTANCE hInstance,
	_In_opt_	HINSTANCE hPrevInstance,
	_In_		LPSTR     lpCmdLine,
	_In_		int       nCmdShow
)
#endif
{
	auto arguments = __argv;
	auto num_args = __argc;

	Engine e(1024, 768, "AFPS");
	e.start("test.xml");
	return 0;
}

