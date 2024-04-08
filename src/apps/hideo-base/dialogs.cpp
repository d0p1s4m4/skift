#include <karm-ui/box.h>
#include <karm-ui/dialog.h>
#include <karm-ui/drag.h>
#include <karm-ui/scroll.h>

#include "dialogs.h"

namespace Hideo {

/* --- Dialogs Scaffolding -------------------------------------------------- */

Ui::Child dialogScafold(Layout::Align a, Ui::Child inner) {
    Ui::BoxStyle const boxStyle = {
        .borderRadius = 4,
        .borderWidth = 1,
        .borderPaint = Ui::GRAY800,
        .backgroundPaint = Ui::GRAY900,
        .shadowStyle = Gfx::BoxShadow::elevated(16)
    };

    return inner |
           box(boxStyle) |
           Ui::dragRegion() |
           Ui::align(a) |
           Ui::spacing(16);
}

Ui::Child dialogScafold(Layout::Align a, Ui::Child content, Ui::Children actions) {
    auto layout =
        Ui::vflow(
            8,
            content | Ui::grow(),
            hflow(8, actions)
        ) |
        Ui::spacing(16);

    return dialogScafold(a, layout);
}

Ui::Child dialogCloseButton() {
    return button(
        Ui::closeDialog,
        Ui::ButtonStyle::primary(),
        "Close"
    );
}

/* --- Dialogs -------------------------------------------------------------- */

Ui::Child versionBadge() {
    Ui::Children badges = {};
    badges.pushBack(Ui::badge(
        Ui::BadgeStyle::INFO,
        stringify$(__ck_version_value)
    ));
#ifdef __ck_branch_nightly__
    badges.pushBack(Ui::badge(Gfx::INDIGO400, "Nightly"));
#elif defined(__ck_branch_stable__)
    // No badge for stable
#else
    badges.pushBack(Ui::badge(Gfx::EMERALD, "Dev"));
#endif
    return Ui::hflow(4, badges);
}

static constexpr Str LICENSE = R"(Copyright © 2018-2024, the skiftOS Developers

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.)";

Ui::Child licenseDialog() {
    return dialogScafold(
        Layout::Align::CLAMP |
            Layout::Align::CENTER |
            Layout::Align::TOP_START,
        Ui::vflow(
            8,
            Ui::titleLarge("License"),
            Ui::bodySmall(LICENSE) |
                Ui::vscroll() |
                Ui::maxSize({480, Ui::UNCONSTRAINED}) |
                Ui::grow()
        ),
        {Ui::grow(NONE), dialogCloseButton()}
    );
}

Ui::Child aboutDialog(Mdi::Icon i, String name) {
    auto content = Ui::vflow(
        Ui::vflow(
            8,
            Layout::Align::CENTER,
            spacing(8, Ui::icon(i, 56)),
            Ui::titleLarge(name),
            versionBadge()
        ),
        Ui::text(
            Ui::TextStyles::bodySmall()
                .withAlign(Gfx::TextAlign::CENTER)
                .withColor(Ui::GRAY400),
            "Copyright © 2018-2024\nThe skiftOS Developers\nAll rights reserved."
        ) |
            Ui::spacing(16)
    );

    Ui::Children actions = {
        button(
            [](auto &n) {
                showDialog(n, licenseDialog());
            },
            Ui::ButtonStyle::subtle(), Mdi::LICENSE, "License"
        ),
        Ui::grow(NONE),
        dialogCloseButton(),
    };

    return dialogScafold(
        Layout::Align::CENTER | Layout::Align::CLAMP,
        content | Ui::minSize({280, Ui::UNCONSTRAINED}),
        actions
    );
}

void showAboutDialog(Ui::Node &n, Mdi::Icon icon, String name) {
    showDialog(n, aboutDialog(icon, name));
}

Ui::Child msgDialog(String title, String msg) {
    auto titleLbl = Ui::titleMedium(title);
    auto msgLbl = Ui::text(msg);
    Ui::Children actions = {
        Ui::grow(NONE),
        button(
            Ui::closeDialog,
            Ui::ButtonStyle::primary(), "Ok"
        ),
    };

    return dialogScafold(
        Layout::Align::CENTER,
        vflow(16, titleLbl, msgLbl),
        actions
    );
}

void showMsgDialog(Ui::Node &n, String title, String msg) {
    showDialog(n, msgDialog(title, msg));
}

void showMsgDialog(Ui::Node &n, String msg) {
    showDialog(n, msgDialog("Message", msg));
}

} // namespace Hideo