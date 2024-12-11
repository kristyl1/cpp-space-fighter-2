#pragma once

#include "KatanaEngine.h"

using namespace KatanaEngine;

/** @brief The main menu screen for the game. */
class YouLoseScreen : public MenuScreen
{

public:

	/** @brief Instantiate a main menu screen object. */
	YouLoseScreen();
	virtual ~YouLoseScreen() { }

	/** @brief Load the content for the screen.
		@param resourceManager A reference to the game's resource manager,
		used for loading and managing game assets (resources). */
	virtual void LoadContent(ResourceManager& resourceManager);
	
	/** @brief Unload the content for the screen. */
	virtual void Update(const GameTime& gameTime);

	/** @brief Render the screen.
		@param spriteBatch A reference to the game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch& spriteBatch);

	/** @brief Set the flag to quit the game, so the game will exit when screen fades out. */
	virtual void SetQuittingGame() { m_isQuittingGame = true; }

	/** @brief Check if the game is quitting.
		@return True if the game is quitting. */
	virtual bool IsQuittingGame() { return m_isQuittingGame; }


private:
	
	Texture *m_pTexture = nullptr;

	Vector2 m_texturePosition;

	bool m_isQuittingGame = false;

};