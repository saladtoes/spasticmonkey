#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <time.h>
#include <stdbool.h>
#include <X11/XF86keysym.h>
// get info about display and make it useable variable (i think). 
Display *dpy; 
Window root;
XEvent e;
static int scr;
static const char TERM[] = "st";

void handleConfigureRequest(XEvent e, Display *dpy){
  unsigned long value_mask = CWX | CWY | CWWidth | CWHeight | CWBorderWidth | CWSibling | CWStackMode;
  XWindowChanges cha;
  cha.x = e.xconfigurerequest.x;
  cha.y = e.xconfigurerequest.y;
  cha.width = e.xconfigurerequest.width;
  cha.height = e.xconfigurerequest.height;
  cha.border_width = e.xconfigurerequest.border_width;
  cha.sibling = e.xconfigurerequest.above;
  cha.stack_mode = e.xconfigurerequest.detail;

  printf("Configuring window\n");
  XConfigureWindow(dpy, e.xconfigurerequest.window, value_mask, &cha);
}












void handleMapRequests(XEvent e, Display *dpy, int scr){
  XWindowAttributes at;
  XGetWindowAttributes(dpy, e.xmaprequest.window, &at);

  if (at.override_redirect){
    printf("Override Redirect skipping");
    return;
  }

  unsigned long value_mask = CWX | CWY | CWWidth | CWHeight;
  XWindowChanges cha;
  cha.x = 0;
  cha.y = 0;
  cha.width = DisplayWidth(dpy, scr);
  cha.height = DisplayHeight(dpy, scr);

  printf("Window going full screen");
  XConfigureWindow(dpy, e.xmaprequest.window, value_mask, &cha);

  printf("mapping window");
  XMapWindow(dpy, e.xmaprequest.window);
}

static int errorOccurred = 0;
int handleXError(Display *dpy, XErrorEvent *errorEvent){
  if (errorEvent->error_code == BadAccess){
    errorOccurred = 1;
  } return 0;
}


int main() {
  if (!(dpy = XOpenDisplay(NULL)))
    printf("spasticmonkey cannot open display");
  else printf("good");

  scr = DefaultScreen(dpy);
  root = RootWindow(dpy, scr);

  XSetErrorHandler(handleXError);
  errorOccurred = 0;
  XSelectInput(dpy, root, SubstructureRedirectMask | SubstructureNotifyMask | KeyPressMask);

  XSync(dpy, False);
  if (errorOccurred) {
    errx(1, "Another Window Manager is Running");
  }

  for (;;){
    XNextEvent(dpy, &e);
    switch (e.type) {
      case MapRequest:
        handleMapRequests(e, dpy, scr);
        break;

      case ConfigureRequest:
      handleConfigureRequest(e, dpy);
      default:
        printf("event type %d\n", e.type);
        break;
    }
  }
  XCloseDisplay(dpy);
}
