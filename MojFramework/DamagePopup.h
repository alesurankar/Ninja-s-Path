#include "Graphics.h"
#include "Camera.h"
#include "Fonts.h"
#include "Vec2.h"
#include <string>
#include <memory>

class DamagePopup
{
public:
	DamagePopup(int damage_in, Vei2 pos_in);
	void Draw(const Camera& cam, Graphics& gfx);
public:
	float timeLeft = 0.2f;
private:
	int damage;
	Vei2 pos;
	inline static Fonts bigFont = Fonts("Images\\Fonts16x28.bmp");
	inline static Fonts smallFont = Fonts("Images\\Fonts8x14.bmp");
};