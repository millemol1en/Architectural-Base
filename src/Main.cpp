#include <iostream>
#include "./Application.h"


int main(int argc, char* args[])
{
    Application app;

    app.Setup();

    while (app.IsRunning()) {
        // We could disperse all of these and simply perform tail-call for each function.
        app.Input();
        app.Update();
        //app.Render();
    }

    app.Destroy();

    return 0;
}