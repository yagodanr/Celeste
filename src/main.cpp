#include <iostream>
#include "logger.h"
#include "display.h"
#include "memo.h"

using namespace std;


int main() {

    Display display(800, 600, "Celeste");

    while(!display.isClosed()) {
        display.update();
        display.clear(1, 0.3, 0.3, 1);
        // SM_ASSERT(false, "test");
        std::string debug_width = "width =\t" + std::to_string(display.width);
        std::string debug_height = "height =\t" + std::to_string(display.height);
        SM_TRACE(debug_width.c_str());
        SM_TRACE(debug_height.c_str());
        SM_WARN("Test");
        SM_ERROR("Test");
    }

    return 0;
}


