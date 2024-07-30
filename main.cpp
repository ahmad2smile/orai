#include "src/UI/App.h"
#include <clocale>

int main() {
    std::locale::global(std::locale("en_US.UTF-8"));
    setlocale(LC_ALL, "");

    auto app = UI::App();
    const auto window = app.initialize(800, 600, "orai");

    app.run(*window);

    return 0;
}
