#include <iostream>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/fl_ask.H>
#include <FL/filename.H>
#include<FL/fl_string_functions.h>

#include <Windows.h>
#include <gdiplus.h>
#include <objidl.h>
#pragma comment(lib,"gdiplus.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "comctl32.lib")


Fl_Double_Window* app_window = NULL;


void test_window()
{
	app_window = new Fl_Double_Window(640, 480, "Title");
}


int main()
{
	test_window();
	app_window->show();
	return Fl::run();
}