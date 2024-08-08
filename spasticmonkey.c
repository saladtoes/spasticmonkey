#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <time.h>

// get info about display and make it useable variable (i think). 
Display *dpy; 


int main() {
  if (!(dpy = XOpenDisplay(NULL))){
    fprintf(stdout, "failed to connect");
  } else {
    fprintf(stdout, "good");
  }

  

  for (;;){

  }
}
