#pragma once

#include "KatanaEngine.h"

using namespace KatanaEngine;

//Connect the you lose screen back to the main menu
class YouLoseScreen : public MenuScreen
{

public:

	//Instantiate the lose screen
	YouLoseScreen();
	virtual ~YouLoseScreen() { }

	//Load the game and it's content
	virtual void LoadContent(ResourceManager& resourceManager);
	
	//Update the game screen
	virtual void Update(const GameTime& gameTime);

	
	virtual void Draw(SpriteBatch& spriteBatch);

	//Set the game and quit
	virtual void SetQuittingGame() { m_isQuittingGame = true; }

	//Return to the game if the game is quitting
	virtual bool IsQuittingGame() { return m_isQuittingGame; }


private:
	
	Texture *m_pTexture = nullptr;

	Vector2 m_texturePosition;

	bool m_isQuittingGame = false;

};