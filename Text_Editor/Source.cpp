#include <iostream>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/fl_ask.H>
#include <FL/filename.H>
#include<FL/fl_string_functions.h>

/*
* Text Editor widgets
*/
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Editor.H>

#include <Windows.h>
#include <gdiplus.h>
#include <objidl.h>
#pragma comment(lib,"gdiplus.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "comctl32.lib")


Fl_Double_Window* app_window = NULL;
Fl_Menu_Bar* app_menu_bar = NULL;
bool text_changed = false;
char app_filename[FL_PATH_MAX] = "";

/*
* For editor widget
*/

Fl_Text_Buffer* app_text_buffer = NULL;
Fl_Text_Editor* app_editor = NULL;
Fl_Text_Editor* app_split_editor = NULL;


void build_window()
{
	app_window = new Fl_Double_Window(640, 480, "Title");
}

//Update the title if the text changes
void update_title()
{
	const char* fname = NULL;
	if (app_filename[0])
	{
		fname = fl_filename_name(app_filename);
	}
	if (fname)
	{
		char buf[FL_PATH_MAX + 3];

		if (text_changed)
		{
			snprintf(buf, FL_PATH_MAX + 2, "%s *", fname);
		}
		else
		{
			snprintf(buf, FL_PATH_MAX + 2, "%s", fname);
		}

		app_window->copy_label(buf);
	}
	else
	{
		app_window->label("Custom Editor");
	}
}

// Sets the text_changed flag and updates title
void set_changed(bool v)
{
	if (v != text_changed)
	{
		text_changed = v;
		update_title();
	}
}

//Sets new filename and updates title
void set_filename(const char* new_filename)
{
	if (new_filename)
	{
		fl_strlcpy(app_filename, new_filename, FL_PATH_MAX);
	}
	else
	{
		app_filename[0] = 0;
	}
	update_title();
}

void menu_quit_callback(Fl_Widget*, void*)
{
	if (text_changed)
	{
		int c = fl_choice("YOur changes have not been saved.\n"
			"Do you still want to quit?",
			"Quit", "Cancel", NULL);

		if (c == 1) { return; }
	}
	Fl::hide_all_windows();
}

void build_menu_bar()
{
	app_window->begin();
	app_menu_bar = new Fl_Menu_Bar(0, 0, app_window->w(), 25);
	app_menu_bar->add("File/Quit Editor", FL_COMMAND + 'q', menu_quit_callback);
	app_window->callback(menu_quit_callback);
	app_window->end();
}

void text_changed_callback(int, int n_inserted, int n_deleted, int, const char*, void*)
{
	if (n_inserted || n_deleted)
	{
		set_changed(true);
	}
}

void menu_new_callback(Fl_Widget*, void*)
{
	app_text_buffer->text("");
	set_changed(false);
}

void build_editor()
{
	app_window->begin();
	app_text_buffer = new Fl_Text_Buffer();
	app_text_buffer->add_modify_callback(text_changed_callback, NULL);
	app_editor = new Fl_Text_Editor(0, app_menu_bar->h(), app_window->w(), 
		app_window->h() - app_menu_bar->h());
	app_editor->buffer(app_text_buffer);
	app_editor->textfont(FL_COURIER);
	app_window->resizable(app_editor);
	
	//add the 'New' menu element
	int ix = app_menu_bar->find_index(menu_quit_callback);
	app_menu_bar->insert(ix, "New", FL_COMMAND + 'n', menu_quit_callback);

	app_window->end();

}

int main()
{
	build_window();
	build_menu_bar();
	build_editor();
	app_window->show();
	return Fl::run();
}

