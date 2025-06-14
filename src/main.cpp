#include <iostream>


#define DEBUG

#include "imports/globals.h"
#include "imports/platform_specific.h"
RenderContext* renderContext;
Uniforms* uniforms;
GameState* gameState;


#include "imports/logger.h"
#include "imports/display.h"
#include "imports/memo.h"
#include "imports/shaders.h"
#include "imports/texture.h"
#include "imports/rendering.h"
#include "imports/game.h"


typedef decltype(update_game) update_game_type;
static update_game_type* update_game_ptr;

typedef decltype(update_game_events) update_game_events_type;
static update_game_events_type* update_game_events_ptr;



void hot_reload(BumpAllocator* transientStorage);
void update_all_events(Display& display);

int main() {

    BumpAllocator transientStorage = make_bump_allocator(MB(50));
    BumpAllocator persistentStorage = make_bump_allocator(MB(50));

    renderContext = (RenderContext*)allocate_bump(sizeof(RenderContext), &persistentStorage);
    if(!renderContext) {
        SM_ASSERT(false, "Failed to allocate memory for renderContext");
        return 1;
    }
    uniforms = (Uniforms*)allocate_bump(sizeof(Uniforms), &persistentStorage);
    if(!uniforms) {
        SM_ASSERT(false, "Failed to allocate memory for uniforms");
        return 1;
    }
    gameState = (GameState*)allocate_bump(sizeof(GameState), &persistentStorage);
    if(!gameState) {
        SM_ASSERT(false, "Failed to allocate memory for gameState");
        return 1;
    }

    Display display(800, 600, "Celeste");

    Shaders shaders(&transientStorage);
    Texture texture;

    display.init_uniforms(shaders.get_program());
    shaders.bind();
    while(!display.isClosed()) {
        #ifdef DEBUG
        hot_reload(&transientStorage);
        #endif


        update_all_events(display);

        display.clear(1, 0.3, 0.3, 1);
        update_game(renderContext, gameState);
        display.update();


        // std::string debug_width = "width =\t" + std::to_string(display.width);
        // std::string debug_height = "height =\t" + std::to_string(display.height);
        // SM_TRACE(debug_width.c_str());
        // SM_TRACE(debug_height.c_str());


        transientStorage.used = 0;
    }

    return 0;
}


void update_game(RenderContext* renderContextIn, GameState* gameStateIn) {
    update_game_ptr(renderContextIn, gameStateIn);
}
void update_game_events(const SDL_Event& e, GameState* gameStateIn) {
    update_game_events_ptr(e, gameStateIn);
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

        // dlerror();
        game_dll = platform_load_lib("./game_load.so");
        // char* err = dlerror();
        // SM_ASSERT(game_dll, "Failed to load game library: %s", err);
        update_game_ptr = (update_game_type*)platform_load_func(game_dll, "update_game");
        SM_ASSERT(update_game_ptr, "Failed to reload function update_game");
        update_game_events_ptr = (update_game_events_type*)platform_load_func(game_dll, "update_game_events");
        SM_ASSERT(update_game_events_ptr, "Failed to reload function update_game_events");
        last_timestamp_dll = cur_timestamp_dll;
    }

}



void update_all_events(Display& display) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        display.update_events(e);
        update_game_events(e, gameState);
    }
}

