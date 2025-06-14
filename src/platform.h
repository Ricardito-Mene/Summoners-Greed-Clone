#pragma once

//######################################################################
//                    Plataform Globals
//######################################################################

static bool running = true;
static float musicVolume = 0.25f;

//######################################################################
//                    Plataform Functions
//######################################################################

bool platform_create_window(int width, int height, char* title);
void platform_update_window();
void* platform_load_gl_function(const char* funName);
void platform_swap_buffers();
void platform_set_vsync(bool vSync);
void* platform_load_dynamic_library(char* dll);
void* platform_load_dynamic_function(void* dll, char* funName);
bool platform_free_dynamic_library(void* dll);
void platform_fill_keycode_lookup_table();
bool platform_init_audio();
void platform_update_audio(float dt);