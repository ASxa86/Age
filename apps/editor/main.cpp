#include <Application.h>
#include <MainWindow.h>

int main(int argc, char** argv)
{
	azule::Application app(argc, argv);

	azule::MainWindow window;
	window.show();
	return app.exec();
}
