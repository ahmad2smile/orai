#include "src/UI/App.h"

int main() {
    auto app = UI::App();
    const auto window = app.initialize(800, 600, "orai");

    app.run(window);

    return 0;
}
