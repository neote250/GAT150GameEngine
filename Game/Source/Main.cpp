#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>


int main(int argc, char* argv[]) {

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	// create texture, using shared_ptr so texture can be shared
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->Load("spr_rock.png", engine->GetRenderer());
	{
		//Resources
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("spr_rock.png", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("AlphabetFantasie.ttf", 12);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Hello!", { 1, 1, 0 });

		Transform t{ Vector2{30,30} };
		std::unique_ptr<Actor> actor = std::make_unique<Actor>(t);
		std::unique_ptr<TextureComponent> component = std::make_unique<TextureComponent>();
		component->texture = texture;
		actor->AddComponent(std::move(component));

		while (!engine->IsQuit())
		{
			engine->Update();

			actor->Update(engine->GetTime().GetDeltaTime());

			engine->GetRenderer().SetColor(0, 0, 0);
			engine->GetRenderer().BeginFrame();

			engine->GetRenderer().DrawTexture(texture.get(), 30, 30);
			text->Draw(engine->GetRenderer(), 200, 200);
			actor->Draw(engine->GetRenderer());

			engine->GetRenderer().EndFrame();

		}
	}
	ResourceManager::Instance().Clear();
	engine->Shutdown();

	return 0;
}