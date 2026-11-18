#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <cjson/cJSON.h>

#include "shared_types.h"
#include "assets/model/model.h"

#define SDL_WINDOW_WIDTH 1920
#define SDL_WINDOW_HEIGHT 1080

static SDL_Joystick *joystick = NULL;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    
} AppState;

static AppState state;

static SDL_AppResult handle_key_event_(SDL_Scancode key_code)
{
    switch (key_code) {
    /* Quit. */
        case SDL_SCANCODE_ESCAPE:
        case SDL_SCANCODE_Q:
            return SDL_APP_SUCCESS;
        case SDL_SCANCODE_R:
            break;
        case SDL_SCANCODE_RIGHT:
            break;
        case SDL_SCANCODE_UP:
            break;
        case SDL_SCANCODE_LEFT:
            break;
        case SDL_SCANCODE_DOWN:
            break;
        default:
            break;
    }
    return SDL_APP_CONTINUE;
}

// Update
SDL_AppResult SDL_AppIterate(void *appstate)
{
    const Uint64 now = SDL_GetTicks();

    SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderPresent(state.renderer);

    return SDL_APP_CONTINUE;
}

static const struct
{
    const char *key;
    const char *value;
} extended_metadata[] =
{
    { SDL_PROP_APP_METADATA_URL_STRING, "" },
    { SDL_PROP_APP_METADATA_CREATOR_STRING, "Simon Ogorek" },
    { SDL_PROP_APP_METADATA_COPYRIGHT_STRING, "MIT" },
    { SDL_PROP_APP_METADATA_TYPE_STRING, "game" }
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    size_t i;

    if (!SDL_SetAppMetadata("Sage", "0.1a", "com.simon.minecraftopengl"))
        return SDL_APP_FAILURE;

    for (i = 0; i < SDL_arraysize(extended_metadata); i++) 
    {
        if (!SDL_SetAppMetadataProperty(extended_metadata[i].key, extended_metadata[i].value))
            return SDL_APP_FAILURE;
    }

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) 
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Sage", SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN, &state.window, &state.renderer)) {
        return SDL_APP_FAILURE;
    }
    
    SDL_SetRenderLogicalPresentation(state.renderer, SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // CALL INIT
    if (IS_FAILURE(Initialize_Models()))
    {
        printf("Failed to Initialize Models");
        SDL_AppQuit(appstate, SDL_APP_FAILURE);
    }
    Model_Create("../assets/cube.obj");
    // ESTABLISH A TIMER
    // as->last_step = SDL_GetTicks();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type) 
    {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_JOYSTICK_ADDED:
            if (joystick == NULL) 
            {
                joystick = SDL_OpenJoystick(event->jdevice.which);
                if (!joystick) {
                    SDL_Log("Failed to open joystick ID %u: %s", (unsigned int) event->jdevice.which, SDL_GetError());
                }
            }
            break;
        case SDL_EVENT_JOYSTICK_REMOVED:
            if (joystick && (SDL_GetJoystickID(joystick) == event->jdevice.which)) 
            {
                SDL_CloseJoystick(joystick);
                joystick = NULL;
            }
            break;
        case SDL_EVENT_JOYSTICK_HAT_MOTION:
        case SDL_EVENT_KEY_DOWN:
        default:
            break;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appsate, SDL_AppResult result)
{
    if (joystick) 
        SDL_CloseJoystick(joystick);

    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
}

