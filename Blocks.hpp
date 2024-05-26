#pragma once
# include <Siv3D.hpp>

struct Blocks {
	Vec3 pos = Vec3{ 0, 1, 0 };

	bool flag = true;

	Vec3 shape = Vec3{ 2, 4, 2, };

	void move() {
		shape = flag ? Vec3{ 2, 4, 2 } : Vec3{ 4, 2, 2 };

		if (KeyUp.pressed()) {}
		if (KeyRight.down()) {
			Vec3 tmp = Vec3{ pos };

			if (flag) {
				pos.x = (tmp.x + 1) * cos(-90_deg) - (tmp.y - 2) * sin(-90_deg);
				pos.y = (tmp.x + 1) * sin(-90_deg) + (tmp.y - 2) * cos(-90_deg);
			}
			else {
				pos.x = (tmp.x + 2) * cos(-90_deg) - (tmp.y - 1) * sin(-90_deg);
				pos.y = (tmp.x + 2) * sin(-90_deg) + (tmp.y - 1) * cos(-90_deg);
			}
			Console << pos;
			flag^=1;
		}
		if (KeyDown.pressed()) {}
		if (KeyLeft.pressed()) {}

		Box{ pos.x, pos.y + 1, pos.z, shape }.draw(Palette::Green);
		//Box::FromPoints(Vec3{ pos.x, pos.y, pos.z }, Vec3{ pos.x + 2, pos.y + 2, pos.z + 2 }).draw(Palette::Green);
	}
};
