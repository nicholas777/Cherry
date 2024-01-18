#pragma once

#include "application.h"

extern Cherry::Application* Cherry::CreateApplication();

int main(int argc, char** argv) {
	auto app = Cherry::CreateApplication();

	app->Run();

	delete app;
}

