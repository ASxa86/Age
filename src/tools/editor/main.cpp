#include <tools/editor/Application.h>
#include <tools/editor/MainWindow.h>

int main(int argc, char** argv)
{
	age::Application app(argc, argv);

	age::MainWindow window;
	window.show();
	return app.exec();
}
