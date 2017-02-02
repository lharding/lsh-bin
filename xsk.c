/* Adapted from https://www.cs.bgu.ac.il/~orlovm/code/realkey.C */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

int cont = 1;             // flag for while loop
int result = 0;

int check = 0;
const char *const *checkChord;

Display *display = 0;         // X server connection

const char* key_map[32768];       // key names

void quitter(int sig) {
    cont = 0;
}

int main(int argc, const char *const *argv) {
  if(signal(SIGINT, &quitter) == SIG_ERR || signal(SIGTERM, &quitter) == SIG_ERR) {
     fprintf(stderr, "Could not register signal handlers.");
     exit(1);
  }

  if(argc > 1) {
    check = 1;
    checkChord = argv;
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
  #define KEYS_LEN 32
  char keys[KEYS_LEN];                  // buffer for reading keys in
  char lastkeys[KEYS_LEN];              // previous keys state  

  memset(lastkeys, 0, KEYS_LEN);
		
  while (cont) {
    int check_success = 0;

    usleep(10000);
    
    XQueryKeymap(display, keys);

    // print changed keys
    for (unsigned int i = 0; i < KEYS_LEN; ++i) {
      // check which key got changed
      for (unsigned int j = 0, test = 1; j < 8; ++j, test <<= 1) {
        int code = i*8+j;

        if(code < min_key_code || code > max_key_code) continue;

        const char*  key = key_map[code];
        int key_down = keys[i] & test ? 1 : 0;

        if(check) {
          for(int i=1; i<argc; i++) {
            if(key_down && !strcmp(key, argv[i])) check_success = 1;
          }
        }
        else if ((keys[i] & test) != (lastkeys[i] & test)) {
          printf("%s %d\n", key, key_down);
          fflush(stdout);
        }
      }
      
      lastkeys[i] = keys[i];
    }

    if(check) {
        result = !check_success;
        cont = 0;
    }
  }

  XCloseDisplay(display);
  exit(result);
}
