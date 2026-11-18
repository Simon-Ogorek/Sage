#include "shared_types.h"
#include "graphics/vulkan/vulkan.h"
#include "vulkan/vulkan.h"
#include "vulkan/vulkan_core.h"
#include <SDL3/SDL_vulkan.h>

struct Vulkan_Manager
{
    VkInstance instance;
    VkApplicationInfo app_info;
    VkInstanceCreateInfo create_info;
    VkSurfaceKHR main_surface;
}
Vulkan_Manager;

static struct Vulkan_Manager vulkan_manager;

Function_Status Vulkan_Init()
{
    vulkan_manager.app_info.pApplicationName = "Sage";
    vulkan_manager.app_info.pEngineName = "Sage";

    vulkan_manager.create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    
    vulkan_manager.create_info.ppEnabledExtensionNames = SDL_Vulkan_GetInstanceExtensions(
        &vulkan_manager.create_info.enabledExtensionCount
    );

    vkCreateInstance(&vulkan_manager.create_info, NULL, &vulkan_manager.instance);

    SDL_Vulkan_CreateSurface(NULL, vulkan_manager.instance, NULL, &vulkan_manager.main_surface);
}

Function_Status Vulkan_Next_Frame()
{

}

Function_Status Vulkan_Free()
{

}