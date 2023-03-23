#include <karm-main/main.h>
#include <karm-ui/app.h>
#include <karm-ui/dialog.h>
#include <karm-ui/drag.h>
#include <karm-ui/input.h>
#include <karm-ui/layout.h>
#include <karm-ui/scafold.h>
#include <karm-ui/scroll.h>
#include <karm-ui/view.h>

Res<> entryPoint(CliArgs args) {
    auto logo = Ui::icon(Mdi::SNOWFLAKE, 64) |
                Ui::center() |
                Ui::bound() |
                Ui::box({
                    .padding = 32,
                    .backgroundPaint = Gfx::WHITE,
                    .foregroundPaint = Gfx::BLACK,
                });

    auto licenseBtn = Ui::button(
        NONE,
        Ui::ButtonStyle::subtle().withRadius(999),
        Mdi::LICENSE,
        "LICENSE");

    auto closeBtn = Ui::button(
        [](Ui::Node &n) {
            Events::ExitEvent e{Ok()};
            n.bubble(e);
        },
        Ui::ButtonStyle::primary(),
        "OK");

    auto content = Ui::spacing(
        16,
        Ui::vflow(
            8,
            Ui::hflow(8,
                      Ui::text(Ui::TextStyle::titleLarge(), "skiftOS"),
                      Ui::badge(Ui::BadgeStyle::INFO, "v0.1.0") | Ui::center()),
            Ui::empty(),
            Ui::text("Copyright © 2018-2022"),
            Ui::text("SMNX & contributors."),
            Ui::grow(NONE),
            Ui::hflow(
                8,
                licenseBtn,
                Ui::grow(NONE),
                closeBtn)));

    auto titlebar = Ui::titlebar(
        Mdi::INFORMATION,
        "About",
        Ui::TitlebarStyle::DIALOG);

    auto wrapper =
        Ui::vflow(titlebar, logo, content | Ui::grow()) |
        Ui::pinSize({350, 400}) |
        Ui::dialogLayer();

    return Ui::runApp(args, wrapper);
}