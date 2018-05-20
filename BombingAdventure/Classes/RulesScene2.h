/* File: RuleScene2.h
 * ------------------
 * This file contains the prototype of a class
 * called RuleScene2 which displays a scene with instruction
 * manual of this game. Including the introduction
 * of items which can improve the ability of the player.
 */
#ifndef BOMBING_ADVENTURE_RULESCENE2_H
#define BOMBING_ADVENTURE_RULESCENE2_H

#include "cocos2d.h"

/* Class: RulesScene2
 * -----------------
 * This class displays a scene with instruction
 * manual of this game. Including the introduction
 * of items which can improve the ability of the player.
 * It just displays the second page of the rules
 * because transition animation needs class Scene instead
 * of class Layer.
 */
class RulesScene2 : public cocos2d::Scene {
public:

    /* Constructor: createScene
     * Usage: RulesScene::createScene();
     * --------------------------------
     * Creates the Rule 2 Scene to be shown.
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

    /* Callback Method: menuPrevPage
     * Usage: menu_selector(RulesScene::menuPrevPage);
     * ----------------------------------------------
     * Switch to the previous scene when it is passed
     * to menu_selector.
     */
    void menuPrevPage(cocos2d::Ref* pSender);

    /* Macro: initialize a static create function to create RulesScene2  */
    CREATE_FUNC(RulesScene2);
};

#endif //BOMBING_ADVENTURE_RULESCENE2_H
