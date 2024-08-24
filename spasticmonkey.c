#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <time.h>
#include <stdbool.h>
// get info about display and make it useable variable (i think). 
Display *dpy; 
Window root;
XEvent e;
static int scr;

static const char TERM[] = "st";


int main() {
  if (!(dpy = XOpenDisplay(NULL)))
    printf("spasticmonkey cannot open display");
  else printf("good");
  
  scr = DefaultScreen(dpy);
  root = RootWindow(dpy, scr);

  XGrabKey(dpy, XKeysymToKeycode(dpy, XStringToKeysym("t")), Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);
  

  for (;;){
    XNextEvent(dpy, &e);
    switch (e.type) {
    case KeyPress:
        //openterminal as place holder
      system(TERM);
      break;
  }
  }
  XCloseDisplay(dpy);
}
