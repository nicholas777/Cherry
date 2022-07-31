#include <Cherry.h>

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
		
		m_Camera = new Camera({ 0.2, 0.2 }, -1.1, 1.1, 0.8, -0.8, 10, 0, { 0, 1, 0 });
		m_Controller = new CameraController(m_Camera.Get(), 0.5);
		
	}

	virtual void OnUpdate(const Timestep& delta) override
	{
		m_Controller->Update(delta.GetSeconds());

		{
			RenderCommand::Clear();

			Renderer2D::Begin(m_Camera.Get());



			Renderer2D::End();
		}
	}

	virtual void OnDetach() override
	{
		
	}

private:
	Scoped<Mesh> m_Mesh;
	Scoped<TransformationMatrix> m_Matrix;
	Scoped<Camera> m_Camera;
	Scoped<CameraController> m_Controller;
	Scoped<Texture> m_Texture;
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
