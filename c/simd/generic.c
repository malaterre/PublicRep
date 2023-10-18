#include <stdint.h>
int HASMATCH(uint16_t needle, const uint16_t haystack[4]) {
    int found = 0;
    for (int i = 0; i < 4; ++i) {
        if (needle== haystack[i]) {
		found = 1;
        }
    }
    return found;
}
