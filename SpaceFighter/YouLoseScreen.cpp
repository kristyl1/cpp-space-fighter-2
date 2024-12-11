
#include "YouLoseScreen.h"
#include "GameplayScreen.h"


YouLoseScreen::YouLoseScreen()
{
	// when the screen is removed, quit the game
	SetOnRemove([this](){ GetGame()->Quit(); });

	SetTransitionInTime(1);
	SetTransitionOutTime(0.5f);

	Show();
}

void YouLoseScreen::LoadContent(ResourceManager& resourceManager)
{
	//Display the "You Lose" image 
	m_pTexture = resourceManager.Load<Texture>("Textures\\Youlose.png");
	
	//Center the screen
	m_texturePosition = Game::GetScreenCenter() - Vector2::UNIT_Y * 150;

	// Create the menu items and set the font 
	const int COUNT = 2;
	MenuItem *pItem;
	Font::SetLoadSize(20, true);
	Font *pFont = resourceManager.Load<Font>("Fonts\\arial.ttf");

	SetDisplayCount(COUNT);

	//Button to display Restart Game and Quit
	enum Items { Restart_Game, QUIT };
	std::string text[COUNT] = { "Restart", "Quit" };

	for (int i = 0; i < COUNT; i++)
	{
		pItem = new MenuItem(text[i]);
		pItem->SetPosition(Vector2(100, 100 + 50 * i));
		pItem->SetFont(pFont);
		pItem->SetColor(Color::BLUE);
		pItem->SetSelected(i == 0);
		AddMenuItem(pItem);
	}

	GetMenuItem(Restart_Game)->SetOnSelect([this](){
		//Move to the GameplayScreen - when game is restarted 
		SetOnRemove([this](){ AddScreen(new GameplayScreen()); });
		Exit();
	});

	//Connect the exit button 
	GetMenuItem(QUIT)->SetOnSelect(std::bind(&YouLoseScreen::Exit, this));
}

void YouLoseScreen::Update(const GameTime& gameTime)
{
	bool isSelected = false;
	float alpha = GetAlpha();
	float offset = sinf(gameTime.GetTotalTime() * 10) * 5 + 5;

	//Get the menu items and set the color 
	for (MenuItem* pItem : GetMenuItems())
	{
		pItem->SetAlpha(alpha);
		isSelected = pItem->IsSelected();
		pItem->SetColor(isSelected ? Color::WHITE : Color::BLUE);
		pItem->SetTextOffset(isSelected ? Vector2::UNIT_X * offset : Vector2::ZERO);
	}

	MenuScreen::Update(gameTime);
}

void YouLoseScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();
	spriteBatch.Draw(m_pTexture, m_texturePosition, Color::WHITE * GetAlpha(), m_pTexture->GetCenter());
	MenuScreen::Draw(spriteBatch);
	spriteBatch.End();
}
