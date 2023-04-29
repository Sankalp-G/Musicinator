#include <ftxui/dom/elements.hpp>   // for filler, text, hbox
using namespace ftxui;

#define TITLE_TOP    "█▀▄▀█ █░█ █▀ █ █▀▀   █▀▄▀█ ▄▀█ █▄░█ ▄▀█ █▀▀ █▀▀ █▀█"
#define TITLE_BOTTOM "█░▀░█ █▄█ ▄█ █ █▄▄   █░▀░█ █▀█ █░▀█ █▀█ █▄█ ██▄ █▀▄"

auto title_component =
  hbox({
      filler(),
      vbox({
        text(TITLE_TOP),
        text(TITLE_BOTTOM)
      }),
      filler(),
    });

#define TITLE_COMPONENT title_component
