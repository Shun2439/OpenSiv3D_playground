#pragma once

void Main()
{
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 }.removeSRGBCurve());

	// 画像ファイルからテクスチャを作成する | Create a texture from an image file
	const Texture floorTexture{ U"example/particle.png" };

	Cources cource;

	MeshData meshDataFront = MeshData::Grid(Vec2{ 20, 20 }, 20, 20);

	DynamicMesh meshFront{ meshDataFront };

	const PixelShader ps = HLSL{ U"example/shader/hlsl/forward_triplanar.hlsl", U"PS" }
	| GLSL{ U"example/shader/glsl/forward_triplanar.frag",{ { U"PSPerFrame", 0 },{ U"PSPerView", 1 },{ U"PSPerMaterial", 3 } } };
	const MSRenderTexture renderTexture{ Scene::Size(), TextureFormat::R8G8B8A8_Unorm_SRGB, HasDepth::Yes };
	DebugCamera3D camera{ renderTexture.size(), 30_deg, Vec3{ 16, 12, -24 } };

	/* 音声ファイルからオーディオを作成する */
	const Audio audio(U"example/test.mp3");

	if (not audio) { return; }

	// 絵文字からテクスチャを作成する | Create a texture from an emoji
	const Texture emoji{ U"🦖"_emoji };

	// 太文字のフォントを作成する | Create a bold font with MSDF method
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// テキストに含まれる絵文字のためのフォントを作成し、font に追加する | Create a font for emojis in text and add it to font as a fallback
	const Font emojiFont{ 48, Typeface::ColorEmoji };
	font.addFallback(emojiFont);

	// ボタンを押した回数 | Number of button presses
	int32 count = 0;

	// チェックボックスの状態 | Checkbox state
	bool checked = false;

	// プレイヤーの移動スピード | Player's movement speed
	double speed = 200.0;

	// プレイヤーの X 座標 | Player's X position
	double playerPosX = 400;

	// プレイヤーが右を向いているか | Whether player is facing right
	bool isPlayerFacingRight = true;

	/* オーディオを再生する */
	audio.play();

	while (System::Update())
	{
		camera.update(2.0);

		Graphics3D::SetCameraTransform(camera);

		// 3D
		{
			const ScopedRenderTarget3D target{ renderTexture.clear(ColorF{ 0.4, 0.6, 0.8 }.removeSRGBCurve()) };
			const ScopedCustomShader3D shader{ ps };
			//meshFront.draw(floorTexture);
			// meshBack.draw(floorTexture);

			for (auto i : cource.map[0]) {
				if (i != 2) {
					Plane{ Vec3{ Max(i, 1) * 2 - 5, 1, 1 }, 2 }.draw(Palette::Red);
				}
				else {
					Plane{ Vec3{ Max(i, 1) * 2 - 5, 1, 1 }, 2 }.draw(Palette::White);
				}
			}
		}

		// 3D シーンを 2D シーンに描画
		{
			// renderTexture を resolve する前に 3D 描画を実行する
			Graphics3D::Flush();

			// マルチサンプル・テクスチャのリゾルブ
			renderTexture.resolve();

			// リニアレンダリングされた renderTexture をシーンに転送
			Shader::LinearToScreen(renderTexture);
		}

		// テクスチャを描く | Draw the texture
		// floorTexture.draw(20, 20);

		// テキストを描く | Draw text
		// font(U"Hello, Siv3D!🎮").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });

		// 指定した範囲内にテキストを描く | Draw text within a specified area
		// font(U"Siv3D (シブスリーディー) は、ゲームやアプリを楽しく簡単な C++ コードで開発できるフレームワークです。").draw(18, Rect{ 20, 430, 480, 200 }, Palette::Black);

		// 長方形を描く | Draw a rectangle
		//Rect{ 540, 20, 80, 80 }.draw();

		// 角丸長方形を描く | Draw a rounded rectangle
		//RoundRect{ 680, 20, 80, 200, 20 }.draw(ColorF{ 0.0, 0.4, 0.6 });

		// 円を描く | Draw a circle
		//Circle{ 580, 180, 40 }.draw(Palette::Seagreen);

		// 矢印を描く | Draw an arrow
		//Line{ 540, 330, 760, 260 }.drawArrow(8, SizeF{ 20, 20 }, ColorF{ 0.4 });

		// 半透明の円を描く | Draw a semi-transparent circle
		//Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1.0, 0.0, 0.0, 0.5 });

		// ボタン | Button
		//if (SimpleGUI::Button(U"count: {}"_fmt(count), Vec2{ 520, 370 }, 120, (checked == false)))
		//{
		//	// カウントを増やす | Increase the count
		//	++count;
		//}

		// チェックボックス | Checkbox
		//SimpleGUI::CheckBox(checked, U"Lock \U000F033E", Vec2{ 660, 370 }, 120);

		// スライダー | Slider
		//SimpleGUI::Slider(U"speed: {:.1f}"_fmt(speed), speed, 100, 400, Vec2{ 520, 420 }, 140, 120);

		// 左キーが押されていたら | If left key is pressed
		//if (KeyLeft.pressed())
		//{
		//	// プレイヤーが左に移動する | Player moves left
		//	playerPosX = Max((playerPosX - speed * Scene::DeltaTime()), 60.0);
		//	isPlayerFacingRight = false;
		//}

		// 右キーが押されていたら | If right key is pressed
		//if (KeyRight.pressed())
		//{
		//	// プレイヤーが右に移動する | Player moves right
		//	playerPosX = Min((playerPosX + speed * Scene::DeltaTime()), 740.0);
		//	isPlayerFacingRight = true;
		//}

		// プレイヤーを描く | Draw the player
		//emoji.scaled(0.75).mirrored(isPlayerFacingRight).drawAt(playerPosX, 540);
	}
}
