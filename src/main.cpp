#include <iostream>


#define DEBUG

#include "platform_specific.h"

#include "logger.h"
#include "display.h"
#include "memo.h"
#include "shaders.h"
#include "texture.h"
#include "sprite.h"
#include "game.h"


typedef decltype(update_game) update_game_type;
static update_game_type* update_game_ptr;



void hot_reload(BumpAllocator* transientStorage);


int main() {

    BumpAllocator transientStorage = make_bump_allocator(MB(50));
    BumpAllocator persistentStorage = make_bump_allocator(MB(50));

    renderContext = (RenderContext*)allocate_bump(sizeof(RenderContext), &persistentStorage);
    if(!renderContext) {
        SM_ASSERT(false, "Failed to allocate memory for renderContext");
        return 1;
    }

    Display display(800, 600, "Celeste");

    Shaders shaders(&transientStorage);
    Texture texture;

    shaders.bind();
    while(!display.isClosed()) {
        #ifdef DEBUG
        hot_reload(&transientStorage);
        #endif

        display.clear(1, 0.3, 0.3, 1);
        update_game(renderContext);
        display.update(&shaders);


        // std::string debug_width = "width =\t" + std::to_string(display.width);
        // std::string debug_height = "height =\t" + std::to_string(display.height);
        // SM_TRACE(debug_width.c_str());
        // SM_TRACE(debug_height.c_str());


        transientStorage.used = 0;
    }

    return 0;
}


void update_game(RenderContext* renderContext) {
    update_game_ptr(renderContext);
}


void hot_reload(BumpAllocator* transientStorage) {
    static void* game_dll;
    static long long last_timestamp_dll;

    long long cur_timestamp_dll = get_timestamp(GAME_LIB_PATH);
    if(cur_timestamp_dll > last_timestamp_dll) {
        if(game_dll) {
            // 0 if good, 1 if error
            bool free_lib = platform_free_lib(game_dll);
            SM_ASSERT(!free_lib, "Failed freeing dll library");
            game_dll = nullptr;
            SM_TRACE("Freed dll library");
        }
        while(!copy_file(GAME_LIB_PATH, GAME_RELOAD_LIB_PATH, transientStorage)) {
            SM_WARN("Retrying to copy dll");
            SDL_Delay(50);
        }
        SM_TRACE("Successfully copied dll");

        game_dll = platform_load_lib("./game_load.so");
        SM_ASSERT(game_dll, "Failed to load game library");
        update_game_ptr = (update_game_type*)platform_load_func(game_dll, "update_game");
        SM_ASSERT(update_game_ptr, "Failed to load symbol 'update_game'");
        SM_ASSERT(update_game_ptr, "Failed to reload function");
        last_timestamp_dll = cur_timestamp_dll;
    }

}