#include <Cherry.h>
#include <vector>
#include <Math/Vector.h>
#include <Math/Algorithm.h>

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
		float aspect = 600 / 400;
		m_Shader = Shader::Create("assets/Shader.glsl");

		m_Mesh = Mesh(
			{
				{ Vector2f(-0.5f, -0.5f), Vector2f(0.0f, 0.0f) },
				{ Vector2f( 0.5f, -0.5f), Vector2f(1.0f, 0.0f) },
				{ Vector2f( 0.5f,  0.5f), Vector2f(1.0f, 1.0f) },
				{ Vector2f(-0.5f,  0.5f), Vector2f(0.0f, 1.0f) },
			},
			{
				0, 1, 2,
				0, 2, 3
			},
			new Material(m_Shader)
		);

		m_Matrix = TransformationMatrix(0, 0);

		m_Camera = new Camera({ 0.2, 0.2 }, -1.1, 1.1, 0.8, -0.8, 10, 0, { 0, 1, 0 });
		m_Controller = CameraController(m_Camera, 0.5);

		m_Texture = Texture::Create("assets/Smile.png");
	}

	virtual void OnUpdate(Timestep delta) override
	{
		m_Controller.Update(delta.GetSeconds());

		{
			RenderCommand::Clear();

			Renderer::Begin(*m_Camera);

			Renderer::Submit(m_Mesh, m_Matrix);

			Renderer::End();
		}
	}

	virtual void OnDetach() override
	{
		
	}

private:
	Mesh m_Mesh;
	Shader* m_Shader;
	TransformationMatrix m_Matrix;
	Camera* m_Camera;
	CameraController m_Controller;
	Texture* m_Texture;
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
