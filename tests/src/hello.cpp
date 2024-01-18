#include <cherry.h>

using namespace Cherry;

class WorldLayer : public Layer
{
public:
	WorldLayer()
		: Layer("World")
	{
	}

	virtual void OnAttach() override
	{
		m_Atlas = new TextureAtlas("assets/tilemap_packed.png", 16, 16, 16 * 17, 128, 17, 8);
		m_Camera = new Camera({ 0.0, 0.0 }, -1.1, 1.1, 0.8, -0.8, 10, 0, { 0, 1, 0 });
		m_Controller = new CameraController(m_Camera.Get(), 0.5);
		m_Texture = Texture::Create("assets/Smile.png");
	}

	virtual void OnUpdate(const Timestep& delta) override
	{
		m_Controller->Update(delta.GetSeconds());
		
		CH_INFO("FPS: " + std::to_string(1000 / delta.GetMilliseconds()));
		{
			RenderCommand::Clear();

			Renderer2D::Begin(m_Camera.Get());


			Renderer2D::DrawRect({ 0, 0 }, { 1, 1 }, m_Atlas->GetSubTexture(0, 0));

			

			Renderer2D::End();
		}
		rotation += 0.5f;
	}

	virtual void OnDetach() override
	{

	}

private:
	Scoped<Camera> m_Camera;
	Scoped<CameraController> m_Controller;
	Scoped<Texture> m_Texture;
	Scoped<TextureAtlas> m_Atlas;

	float rotation = 0.0f;
};

class Tests : public Application
{
public:
	Tests()
	{
		Configuration.WindowWidth = 600;
		Configuration.WindowHeight = 400;
		Configuration.WindowTitle = "Tests Project";
		Configuration.IsVSync = true;

		Configuration.Name = "Game";

		PushLayer(new WorldLayer());
	}

	~Tests()
	{

	}
};

Application* Cherry::CreateApplication()
{
	return new Tests();
}
