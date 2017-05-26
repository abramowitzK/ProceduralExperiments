//
// Created by Kyle on 12/8/2016.
//
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <engine.hpp>
using namespace Aurora;
#undef main
#ifdef _DEBUG
#pragma comment(linker, "/subsystem:console")
int main(char** argv, int argc)
#else
#pragma comment(linker, "/subsystem:windows")
int CALLBACK WinMain(
	 HINSTANCE hInstance,
	 HINSTANCE hPrevInstance,
	 LPSTR     lpCmdLine,
	 int       nCmdShow
)
#endif
{
	auto arguments = __argv;
	auto num_args = __argc;

	Engine e(1024,768,"AFPS");
	e.start("test.xml");
	return 0;
}

