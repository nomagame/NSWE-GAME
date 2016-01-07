//
//  GameManager.cpp
//  NSWNGAME
//
//  Created by nancai on 14/12/25.
//
//

#include "GameManager.h"

GameManager * GameManager::instance;

GameManager* GameManager::getInstance()
{
        if(instance==NULL)
            instance = new GameManager();
    return instance;
}

void GameManager::clear()
{
    
}