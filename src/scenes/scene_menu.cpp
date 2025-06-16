#include "../scene.h"
#include "../texts.h"
#include "../ui.h"

SceneMenu sceneMenu;

void SceneMenu::init()
{
    SM_TRACE("init Menu")
}

void SceneMenu::update(float dt) 
{ 
    int buttonID = line_id(1);
    Vec4 color = COLOR_WHITE;

    if(is_hot(buttonID))
    {
        color = COLOR_GREEN;
    }

    DrawData drawData = {};
    drawData.material.color = color;
    drawData.layer = get_layer(LAYER_UI, 10.0f);

    if(do_button(SPRITE_BUTTON_PLAY, IVec2{WORLD_WIDTH/2, WORLD_HEIGHT/2}, 
                buttonID, drawData))
    {
        gameState->state = GAME_STATE_IN_LEVEL;
    }

    TextData textData = {};
    textData.material.color = COLOR_BLACK;
    textData.fontSize = 2.0f;
    textData.layer = get_layer(LAYER_UI, 10.0f);

    do_ui_text(_(STRING_CELESTE_CLONE), {56, 20}, textData);

    // Fullscreen White quad for the menu
    DrawData bgDrawData = {};
    bgDrawData.material.color = {79.0f / 255.0f, 140.0f / 255.0f, 235.0f / 255.0f, 1.0f};
    bgDrawData.layer = get_layer(LAYER_UI, 0.0f);

    do_ui_quad(
        {(float)WORLD_WIDTH / 2, (float)WORLD_HEIGHT / 2},
        {(float)WORLD_WIDTH, (float)WORLD_HEIGHT},
        bgDrawData);
}

void SceneMenu::render(float interp) 
{ 
    // Draw UI
    {
        for(int uiElementIdx = 0; uiElementIdx < uiState->uiElements.count; uiElementIdx++)
        {
        UIElement& uiElement = uiState->uiElements[uiElementIdx];
        draw_ui_sprite(uiElement.spriteID, uiElement.pos, uiElement.size, uiElement.drawData);
        }

        for(int uiTextIdx = 0; uiTextIdx < uiState->uiTexts.count; uiTextIdx++)
        {
        UIText& uiText = uiState->uiTexts[uiTextIdx];
        draw_ui_text(uiText.text, uiText.pos, uiText.textData);
        }
    }
}
void SceneMenu::cleanup() 
{ 
    SM_TRACE("Menu limpo\n"); 
}