
#include "EnemyShip.h"


EnemyShip::EnemyShip()
{
	SetMaxHitPoints(1);
	SetCollisionRadius(20);
}


void EnemyShip::Update(const GameTime& gameTime)
{
	if (m_delaySeconds > 0)
	{
		m_delaySeconds -= gameTime.GetElapsedTime();

		if (m_delaySeconds <= 0)
		{
			GameObject::Activate();
		}
	}

	if (IsActive())
	{
		m_activationSeconds += gameTime.GetElapsedTime();
		if (m_activationSeconds > 2 && !IsOnScreen()) Deactivate();
	}

	Ship::Update(gameTime);
}


void EnemyShip::Initialize(const Vector2 position, const double delaySeconds)
{
	SetPosition(position);
	m_delaySeconds = delaySeconds;

	Ship::Initialize();
}


void EnemyShip::Hit(const float damage)
{
	Ship::Hit(damage);

	//Track number of enemy ships destroyed.
	static int count = 0;
	//Increments the counter and displays to console
	count++;
	std::cout << count << " ships destroyed.\n";
	
}

