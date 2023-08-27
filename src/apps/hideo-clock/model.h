#pragma once

#include <karm-ui/reducer.h>

namespace Clock {

enum struct Page {
    CLOCK,
    STOPWATCH,
    TIMER,
    ALARM,

    _DEFAULT = ALARM,
};

static inline Str toStr(Page page) {
    switch (page) {
    case Page::CLOCK:
        return "Clock";
    case Page::STOPWATCH:
        return "Stopwatch";
    case Page::TIMER:
        return "Timer";
    case Page::ALARM:
        return "Alarm";
    default:
        return "Unknown";
    }
}

struct State {
    Page page = Page::_DEFAULT;
};

using Actions = Var<Page>;

State reduce(State state, Actions action);

using Model = Ui::Model<State, Actions, reduce>;

} // namespace Clock
