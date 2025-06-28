#include "src/UI/App.h"
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    std::locale::global(std::locale("en_US.UTF-8"));
    setlocale(LC_ALL, "");

#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    auto app = UI::App();
    const auto window = app.initialize(800, 600, "orai");

    app.run(*window);

    return 0;
}
