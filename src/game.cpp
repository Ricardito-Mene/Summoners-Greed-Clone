#include "game.h"

#include "texts.h"

#include "scene.h"

// #############################################################################
//                           Game Constants
// #############################################################################

// #############################################################################
//                           Game Structs
// #############################################################################
Scene* currentScene = nullptr;

// #############################################################################
//                           Game Functions
// #############################################################################
bool just_pressed(GameInputType type)
{
  KeyMapping mapping = gameState->keyMappings[type];
  for(int idx = 0; idx < mapping.keys.count; idx++)
  {
    if(input->keys[mapping.keys[idx]].justPressed)
    {
      return true;
    }
  }

  return false;
}

bool is_down(GameInputType type)
{
  KeyMapping mapping = gameState->keyMappings[type];
  for(int idx = 0; idx < mapping.keys.count; idx++)
  {
    if(input->keys[mapping.keys[idx]].isDown)
    {
      return true;
    }
  }

  return false;
}

IVec2 get_grid_pos(IVec2 worldPos)
{
  return {worldPos.x / TILESIZE, worldPos.y / TILESIZE};
}

Tile* get_tile(int x, int y)
{
  Tile* tile = nullptr;

  if(x >= 0  && x < WORLD_GRID.x && y >= 0 && y < WORLD_GRID.y)
  {
    tile = &gameState->worldGrid[x][y];
  }

  return tile;
}

Tile* get_tile(IVec2 worldPos)
{
  IVec2 gridPos = get_grid_pos(worldPos);
  return get_tile(gridPos.x, gridPos.y);
}

IRect get_player_rect()
{  
  return 
  {
    gameState->player.pos.x - 4, 
    gameState->player.pos.y - 8, 
    8, 
    16
  };
}

IVec2 get_tile_pos(int x, int y)
{
  return {x * TILESIZE, y * TILESIZE};
}

IRect get_tile_rect(int x, int y)
{
  return {get_tile_pos(x, y), 8, 8};
}

IRect get_solid_rect(Solid solid)
{
  Sprite sprite = get_sprite(solid.spriteID);
  return {solid.pos - sprite.size / 2, sprite.size};
}

void simulate()
{
  float dt = UPDATE_DELAY;

  switch(gameState->state)
  {
    case GAME_STATE_MAIN_MENU:
      if(!currentScene || dynamic_cast<SceneMenu*>(currentScene) == nullptr)
      {
        if(currentScene)
        {
          currentScene->cleanup();
          delete currentScene;
        }
        currentScene = new SceneMenu();
        currentScene->init();
      }
       break;

    case GAME_STATE_IN_LEVEL:
      if(!currentScene || dynamic_cast<SceneGame*>(currentScene) == nullptr)
      {
        if(currentScene)
        {
          currentScene->cleanup();
          delete currentScene;
        }
        currentScene = new SceneGame();
        currentScene->init();
      }
       break;

    default:
      break;
  }
}

// #############################################################################
//                           Game Functions(exposed)
// #############################################################################
EXPORT_FN void update_game(GameState* gameStateIn, 
                           RenderData* renderDataIn, 
                           Input* inputIn, 
                           SoundState* soundStateIn,
                           UIState* uiStateIn,
                           float dt)
{
  if(renderData != renderDataIn)
  {
    gameState = gameStateIn;
    renderData = renderDataIn;
    input = inputIn;
    soundState = soundStateIn;
    uiState = uiStateIn;
  }

  if(!gameState->initialized)
  {
    play_sound("First Steps", SOUND_OPTION_LOOP);
    init_strings();
    renderData->gameCamera.dimensions = {WORLD_WIDTH, WORLD_HEIGHT};
    renderData->gameCamera.position.x = 160;
    renderData->gameCamera.position.y = -90;

    renderData->uiCamera.dimensions = {WORLD_WIDTH, WORLD_HEIGHT};
    renderData->uiCamera.position.x = 160;
    renderData->uiCamera.position.y = -90;

    // Key Mappings
    {
      gameState->keyMappings[MOVE_UP].keys.add(KEY_W);
      gameState->keyMappings[MOVE_UP].keys.add(KEY_UP);
      gameState->keyMappings[MOVE_LEFT].keys.add(KEY_A);
      gameState->keyMappings[MOVE_LEFT].keys.add(KEY_LEFT);
      gameState->keyMappings[MOVE_DOWN].keys.add(KEY_S);
      gameState->keyMappings[MOVE_DOWN].keys.add(KEY_DOWN);
      gameState->keyMappings[MOVE_RIGHT].keys.add(KEY_D);
      gameState->keyMappings[MOVE_RIGHT].keys.add(KEY_RIGHT);
      gameState->keyMappings[MOUSE_LEFT].keys.add(KEY_MOUSE_LEFT);
      gameState->keyMappings[MOUSE_RIGHT].keys.add(KEY_MOUSE_RIGHT);
      gameState->keyMappings[JUMP].keys.add(KEY_SPACE);
      gameState->keyMappings[PAUSE].keys.add(KEY_ESCAPE);
    }

    gameState->state = GAME_STATE_MAIN_MENU;

    gameState->initialized = true;
  }

  // Fixed Update Loop
  {
    gameState->updateTimer += dt;
    while(gameState->updateTimer >= UPDATE_DELAY)
    {

      gameState->updateTimer -= UPDATE_DELAY;
      update_ui();
      simulate();

      currentScene->update(UPDATE_DELAY);
      if(input)
      {
      // Relative Mouse here, because more frames than simulations
      input->relMouse = input->mousePos - input->prevMousePos;
      input->prevMousePos = input->mousePos;
      }
      // Clear the transitionCount for every key
      {
        for (int keyCode = 0; keyCode < KEY_COUNT; keyCode++)
        {
          input->keys[keyCode].justReleased = false;
          input->keys[keyCode].justPressed = false;
          input->keys[keyCode].halfTransitionCount = 0;
        }
      }
    }
  }

  float interpolatedDT = (float)(gameState->updateTimer / UPDATE_DELAY);


  // Draw
  currentScene->render(interpolatedDT);
}