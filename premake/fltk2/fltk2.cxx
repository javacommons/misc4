// generated by Fast Light User Interface Designer (fluid) version 1.0305

#include "fltk2.h"

static Fl_Button *m_button_01=(Fl_Button *)0;

Fl_Table *m_table_01=(Fl_Table *)0;

int main(int argc, char **argv) {
  Fl_Double_Window* w;
  printf("Hello, World!\n");
  fl_cancel = "エフエルキャンセル";
  { Fl_Double_Window* o = new Fl_Double_Window(365, 100);
    w = o; if (w) {/* empty */}
    { m_button_01 = new Fl_Button(10, 10, 110, 30, "m_button_01");
      m_button_01->callback((Fl_Callback*)cb_button_01, (void*)("b#01"));
      m_button_01->label(fl_cancel);
    } // Fl_Button* m_button_01
    { m_table_01 = new Fl_Table(25, 25, 340, 75);
      m_table_01->end();
    } // Fl_Table* m_table_01
    o->end();
  } // Fl_Double_Window* o
  w->show(argc, argv);
  return Fl::run();
}

void cb_button_01(Fl_Widget *, void *vp) {
  const char* name = (const char *)vp;
  printf("Hello, Button(%s)!\n", vp);
}

Fl_Double_Window* MyUI::make_window() {
  Fl_Double_Window* w;
  printf("Hello, World!\n");
  { Fl_Double_Window* o = new Fl_Double_Window(120, 100);
    w = o; if (w) {/* empty */}
    o->user_data((void*)(this));
    { m_button_02 = new Fl_Button(10, 25, 90, 25, "m_button_02");
    } // Fl_Button* m_button_02
    o->end();
  } // Fl_Double_Window* o
  return w;
}

UI::UI() {
  { m_win = new Fl_Window(800, 600);
    m_win->user_data((void*)(this));
    { m_button = new Fl_Button(25, 25, 25, 25);
      m_button->callback((Fl_Callback*)cb_button);
    } // Fl_Button* m_button
    m_win->end();
  } // Fl_Window* m_win
}

void UI::show(int argc, char **argv) {
  m_win->show(argc, argv);
}

void UI::cb_button(Fl_Widget *, void *vp) {
  printf("Hello, World!\n");
}
