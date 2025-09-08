#include "Graphics.h"
#include "Camera.h"
#include "Fonts.h"
#include "Vec2.h"
#include <string>

class DamagePopup
{
public:
	void Draw(const Camera& cam, Graphics& gfx);
	int damage;
	Vei2 pos;
	float timeLeft = 0.2f;
	Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	Fonts smallFont = Fonts("Images\\Fonts8x14.bmp");
};