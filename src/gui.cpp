#include "sys.h"

namespace gui {



    void init() {
        render::font::createFont("gui_font", "data/font/font.ttf", 20);
    }

    void release() {
        // Not real sure...
    }

}