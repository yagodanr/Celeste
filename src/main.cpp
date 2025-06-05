#include <iostream>


#define DEBUG


#include "logger.h"
#include "display.h"
#include "memo.h"
#include "shaders.h"
#include "texture.h"
#include "sprite.h"
#include "game.h"

int main() {

    BumpAllocator transientStorage = make_bump_allocator(MB(50));

    Display display(800, 600, "Celeste");

    Shaders shaders(&transientStorage);
    Texture texture;

    shaders.bind();
    while(!display.isClosed()) {
        display.clear(1, 0.3, 0.3, 1);
        update_game();
        display.update(&shaders);


        // std::string debug_width = "width =\t" + std::to_string(display.width);
        // std::string debug_height = "height =\t" + std::to_string(display.height);
        // SM_TRACE(debug_width.c_str());
        // SM_TRACE(debug_height.c_str());
    }

    return 0;
}


