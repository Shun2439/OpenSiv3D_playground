#pragma once

# include <Siv3D.hpp>

struct Cources {

	// 画像ファイルからテクスチャを作成する | Create a texture from an image file
	//const Texture floorTexture{ U"example/texture/rock.png", TextureDesc::MippedSRGB };

	/* スタートは0、穴（ゴール)は2、道は1*/
	std::vector<std::vector<uint8>> map = {
		{0, 1, 1, 2},
	};

	/* ブロックの大きさは2 */

	Cources() {}//if (not floorTexture) { return; }

void draw(int32 selectedMap) {
	int32 j = 0;

	for (auto i : map[selectedMap]) {
		if (i != 2) {
			Plane{ Vec3{j * 2, 0, 0}, 2 }.draw(Palette::White);
		}
		else {
			Plane{ Vec3{j * 2, 0, 0 }, 2 }.draw(Palette::Red);
		}

		j++;
	}
}

};
