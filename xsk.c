/* Adapted from https://www.cs.bgu.ac.il/~orlovm/code/realkey.C */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

int cont = 1;             // flag for while loop

Display *display = 0;         // X server connection

const char* key_map[256];       // key names
const char* key_map_upper[256]; // key names, upper case

void quitter(int sig) {
    cont = 0;
}

int main(int argc, const char *const *argv) {
  if(signal(SIGINT, &quitter) == SIG_ERR ||
     signal(SIGTERM, &quitter) == SIG_ERR) {
      fprintf(stderr, "Could not register signal handlers.");
      exit(1);
  }

  /*
   * open the display
   */
  if (! (display = XOpenDisplay(getenv("DISPLAY")))) {
    fprintf(stderr, "Can't open DISPLAY=%s", getenv("DISPLAY"));
    exit(1);
  }
    
  /*
   * fill up keyboard mapping
   */
  int min_key_code, max_key_code; // key codes range

  XDisplayKeycodes(display, &min_key_code, &max_key_code);

  for (int code = min_key_code; code <= max_key_code; ++code) {
    const char *keysym  = XKeysymToString(XKeycodeToKeysym(display, code, 0));
    key_map[code]       = keysym ? keysym : "NoSymbol";
  }

  /*
   * fill relevant key buffers
   */
  char keys[32];                  // buffer for reading keys in
  char lastkeys[32];              // previous keys state  

  memset(lastkeys, 0, 32);
		
  while (cont) {
    usleep(10000);
    
    XQueryKeymap(display, keys);

    // print changed keys
    for (unsigned int i = 0; i < sizeof(keys); ++i) {
      if (keys[i] != lastkeys[i]) {
        // check which key got changed
        for (unsigned int j = 0, test = 1; j < 8; ++j, test *= 2)
          // if the changed  print this
          if ((keys[i] & test) != (lastkeys[i] & test)) {
            int code = i*8+j;
            const char*  key = key_map[code];

            if (strlen(key)) { 
              printf("%s %d\n", key, keys[i] & test ? 1 : 0);
              fflush(stdout);
            }
          }
      
        lastkeys[i] = keys[i];
      }
    }
  }

  XCloseDisplay(display);
}
