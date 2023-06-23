#include "pch.h"

#include "Image.h"
#include "Scene.h"

#include "utils.h"
#include "Timer.h"

#define LOOPS 1000000000

int main()
{
	Scene scene("scenes\\Test.json");
	scene.Render();
}
