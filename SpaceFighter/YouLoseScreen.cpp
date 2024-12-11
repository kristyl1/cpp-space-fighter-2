
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
	// Logo
	m_pTexture = resourceManager.Load<Texture>("Textures\\Youlose.png");
	m_texturePosition = Game::GetScreenCenter() - Vector2::UNIT_Y * 150;

	// Create the menu items
	const int COUNT = 2;
	MenuItem *pItem;
	Font::SetLoadSize(20, true);
	Font *pFont = resourceManager.Load<Font>("Fonts\\arial.ttf");

	SetDisplayCount(COUNT);

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
		SetOnRemove([this](){ AddScreen(new GameplayScreen()); });
		Exit();
	});

	// bind the Exit method to the quit menu item
	GetMenuItem(QUIT)->SetOnSelect(std::bind(&YouLoseScreen::Exit, this));
}

void YouLoseScreen::Update(const GameTime& gameTime)
{
	bool isSelected = false;
	float alpha = GetAlpha();
	float offset = sinf(gameTime.GetTotalTime() * 10) * 5 + 5;

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
