#include "Object.h"

void Object::InitRed(const Vec2& pos_in, const Vec2& vel_in)
{
	pos = pos_in;
	vel = vel_in;
}

void Object::InitBlue(const Vec2& pos_in)
{
	pos = pos_in;
}

void Object::BorderCheck()
{
	if (!destroyed)
	{
		if (pos.x <= float(GeneralGame::offset))
		{
			pos.x = float(GeneralGame::offset);
			vel.x = -vel.x;
		}
		if (pos.y <= float(GeneralGame::yOffset))
		{
			pos.y = float(GeneralGame::yOffset);
			vel.y = -vel.y;
		}
		if (pos.x >= float(Graphics::ScreenWidth - GeneralGame::offset) - width)
		{
			pos.x = float(Graphics::ScreenWidth - GeneralGame::offset) - width;
			vel.x = -vel.x;
		}
		if (pos.y >= float(Graphics::ScreenHeight - GeneralGame::offset) - height)
		{
			pos.y = float(Graphics::ScreenHeight - GeneralGame::offset) - height;
			vel.y = -vel.y;
		}
	}
}


void Object::DrawRed(Graphics& gfx) const
{
	gfx.DrawImage(pos,s);
	//gfx.DrawRect(pos, width, height, Colors::Red);
	//gfx.DrawRect(pos + Vec2(inOff, inOff), width - 2*inOff, height - 2* inOff, Colors::White);
	//gfx.DrawRect(pos, width * float(lives) / float(maxLives), height, Colors::Red);
}

void Object::DrawBlue(Graphics& gfx) const
{
	gfx.DrawRect(pos, width, height, Colors::Blue);
}

void Object::Update(float dt)
{
	pos += vel * dt;

	BorderCheck();
}

bool Object::Colliding(Jaz& jaz)
{
	const float right0 = jaz.GetPos().x + jaz.GetWidth();
	const float bottom0 = jaz.GetPos().y + jaz.GetHeight();
	const float right1 = pos.x + width;
	const float bottom1 = pos.y + height;

	return
		right0 >= pos.x &&
		bottom0 >= pos.y &&
		right1 >= jaz.GetPos().x &&
		bottom1 >= jaz.GetPos().y;
}

bool Object::Colliding(Bullet& bul)
{
	const float right0 = bul.GetPos().x + bul.GetDim();
	const float bottom0 = bul.GetPos().y + bul.GetDim();
	const float right1 = pos.x + width;
	const float bottom1 = pos.y + height;

	return
		right0 >= pos.x &&
		bottom0 >= pos.y &&
		right1 >= bul.GetPos().x &&
		bottom1 >= bul.GetPos().y;
}

void Object::Destroyed()
{
	InitRed(Vec2(-100.0f, -100.0f), Vec2(0.0f, 0.0f));
	destroyed = true;
}

void Object::Respawn()
{
	lives = maxLives;
	destroyed = false;
}

bool Object::DestroyedStatus()
{
	return destroyed;
}

void Object::Damaged()
{
	lives--;
	if (lives <= 0)
	{
		Destroyed();
	}
}
