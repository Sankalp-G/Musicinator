#include <memory>                   // for allocator

#include <ftxui/dom/elements.hpp>   // for filler, text, hbox, vbox
#include <ftxui/screen/screen.hpp>  // for Full, Screen
#include "ftxui/dom/node.hpp"       // for Render
#include "ftxui/screen/color.hpp"
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"           // for Menu
#include "ftxui/component/component_options.hpp"   // for MenuOption
#include "ftxui/component/screen_interactive.hpp"  // for ScreenInteractive

#include "./title.h"

MenuOption AnimatedMenuOptions() {
  auto option = MenuOption::Vertical();
  option.entries.animated_colors.foreground.Set(Color::CadetBlueBis, Color::White,
                                                std::chrono::milliseconds(500));
  return option;
}

int CustomMenu(std::vector<std::string> entries) {
  using namespace ftxui;
  auto screen = ScreenInteractive::Fullscreen();

  int selected = 0;
 
  MenuOption option = AnimatedMenuOptions();
  option.on_enter = screen.ExitLoopClosure();
  auto menu = Menu(&entries, &selected, &option);

  auto container = Container::Horizontal({
    menu,
  });

  auto renderer = Renderer(container, [&] {
    return
      vbox({
        filler(),

        TITLE_COMPONENT,
        separator(),
        menu ->Render() | frame | border,

        filler(),
      }) | center | border;
  });

  screen.Loop(renderer);
  return selected;
}
