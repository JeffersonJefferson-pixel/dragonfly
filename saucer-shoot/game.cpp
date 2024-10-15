//
// game.cpp
//

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "Saucer.h"
#include "Hero.h"
#include "Points.h"
#include "Star.h"

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
}

void populateWorld(void) {
    // add saucer to world.
    for (int i = 0; i < 16; i++) {
        new Saucer;
    }
    // add hero to world.
    new Hero;
    // create some stars.
    for (int i = 0; i < 16; i++) {
        new Star;
    }
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

  // set up heads-up display
  new Points;
  df::ViewObject* p_vo = new df::ViewObject;
  p_vo->setLocation(df::TOP_LEFT);
  p_vo->setViewString("Nukes");
  p_vo->setValue(1);
  p_vo->setColor(df::YELLOW);

  GM.run();

  return 0;
}

