#include "Engine.h"

#include <iostream>
#include <cstdlib>
#include <vector>


int main(int argc, char* argv[]) {

	Factory::Instance().Register<Actor>(Actor::GetTypeName());
	Factory::Instance().Register<TextureComponent>(TextureComponent::GetTypeName());
	//auto a = Factory::Instance().Create("Actor");

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();
	engine->Initialize();

	File::SetFilePath("Assets");
	std::cout << File::GetFilePath() << std::endl;

	// create texture, using shared_ptr so texture can be shared
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();
	texture->Load("spr_rock.png", engine->GetRenderer());

	// !! this code is not neccessary, it just shows the contents of the file !!
	std::string buffer;
	File::ReadFile("json.txt", buffer);
	// show the contents of the json file
	std::cout << buffer << std::endl;

	// create json document from the json file contents
	rapidjson::Document document;
	Json::Load("json.txt", document);

	// read the name data from the json
	// read the data from the json
	std::string name;
	int age;
	float speed;
	bool isAwake;
	Vector2 position;
	Color color;

	READ_DATA(document, name);
	READ_DATA(document, age);
	READ_DATA(document, speed);
	READ_DATA(document, isAwake);
	READ_DATA(document, position);
	READ_DATA(document, color);
	// show the data
	std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
	std::cout << position.x << " " << position.y << std::endl;
	std::cout << color.r << " " << color.g << " " << color.b << " " << color.a << std::endl;




	{
		//Resources
		res_t<Texture> texture = ResourceManager::Instance().Get<Texture>("spr_rock.png", engine->GetRenderer());
		res_t<Font> font = ResourceManager::Instance().Get<Font>("AlphabetFantasie.ttf", 12);
		std::unique_ptr<Text> text = std::make_unique<Text>(font);
		text->Create(engine->GetRenderer(), "Hello!", { 1, 1, 0 });

		Transform t{ Vector2{30,30} };
		auto actor = Factory::Instance().Create<Actor>(Actor::GetTypeName());
		actor->SetTransform(t);
		auto component = Factory::Instance().Create<TextureComponent>(TextureComponent::GetTypeName());
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