//
// game.cpp
//

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Star.h"
#include "GameStart.h"

void loadResources(void) {
    // load saucer sprite.
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
    // load ship sprite.
    RM.loadSprite("sprites/ship-spr.txt", "ship");
    // load bullet sprite.
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    // load explosion sprite.
    RM.loadSprite("sprites/explosion-spr.txt", "explosion");
    // load gameover sprite.
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
}

void populateWorld(void) {
    // create some stars.
    for (int i = 0; i < 16; i++) {
        new Star;
    }
    // game start
    new GameStart();
}

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 1;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  // Show splash screen.
  df::splash();

  // Load game resources.
  loadResources();

  // populare game world with some objects.
  populateWorld();

  GM.run();

  return 0;
}

