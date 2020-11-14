// generated by Fast Light User Interface Designer (fluid) version 1.0305

#ifndef fltk2_h
#define fltk2_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
void cb_button_01(Fl_Widget *, void *vp);

class MyUI {
public:
  Fl_Double_Window* make_window();
  Fl_Button *m_button_02;
};
#include <FL/Fl_Window.H>

class UI {
public:
  UI();
  Fl_Window *m_win;
  Fl_Button *m_button;
  void show(int argc, char **argv);
  static void cb_button(Fl_Widget *, void *vp);
};
#include <FL/fl_ask.H>
#endif
