/* File: RuleScene.h
 * -----------------
 * This file contains the prototype of a class
 * called RuleScene which displays a scene with instruction
 * manual of this game. Including how to control
 * the player sprite, and some basic introduction
 * of the enemy (stone monster).
 */
#ifndef RULESSCENE_H
#define RULESSCENE_H

#include "cocos2d.h"
#include "RulesScene2.h"

/* Class: RulesScene
 * -----------------
 * This class displays a scene with instruction
 * manual of this game. Including how to control
 * the player sprite, and some basic introduction
 * of the enemy (stone monster).
 * It just displays the first page of the rules
 * because transition animation needs class Scene instead
 * of class Layer.
 */
class RulesScene : public cocos2d::Scene {
public:

    /* Constructor: createScene
     * Usage: RulesScene::createScene();
     * --------------------------------
     * Creates the Rule 1 Scene to be shown.
     */
	static cocos2d::Scene* createScene();

	/* Method: init
	 * Usage: if (!Scene::init()) do ...
	 * ---------------------------------
	 * Returns true if RuleScene has been
	 * initialized.
	 */
	virtual bool init();

	/* Callback Method: menuPopBack
	 * Usage: menu_selector(RulesScene::menuPopBack);
	 * ----------------------------------------------
	 * PopBack to the home scene when it is passed
	 * to menu_selector.
	 */
	void menuPopBack(cocos2d::Ref* pSender);

    /* Callback Method: menuNextPage
     * Usage: menu_selector(RulesScene::menuNextPage);
     * ----------------------------------------------
     * Switch to the next scene when it is passed
     * to menu_selector.
     */
	void menuNextPage(cocos2d::Ref* pSender);

	/* Macro: initialize a static create function to create RulesScene  */
	CREATE_FUNC(RulesScene);
};

#endif
