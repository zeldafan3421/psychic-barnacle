#include "raylib.h"
#include "log.h"

#include <cstring>
#include <memory>

#include "application.h"

int main()
{
	SetTraceLogCallback(CustomLog<LogMode::Dual>);

	Application app;
	app.loop();
}
