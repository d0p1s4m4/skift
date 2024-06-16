#pragma once

#include <karm-kira/radio.h>
#include <karm-ui/layout.h>

#include "model.h"

namespace Hideo::Zoo {

static inline Page PAGE_RADIO{
    Mdi::RADIOBOX_MARKED,
    "Radio",
    "A set of checkable buttons—known as radio buttons—where no more than one of the buttons can be checked at a time.",
    [] {
        return Ui::vflow(
            16,
            Math::Align::CENTER,
            Kr::radio(
                true,
                NONE
            )
        );
    },
};

} // namespace Hideo::Zoo
