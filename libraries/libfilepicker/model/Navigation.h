#pragma once

#include <libutils/Observable.h>
#include <libutils/Vector.h>

#include <libsystem/Path.h>
#include <libsystem/process/Process.h>

namespace filepicker
{

class Navigation :
    public Observable<Navigation>,
    public RefCounted<Navigation>
{
private:
    Vector<System::Path> _backward{};
    System::Path _current{};
    Vector<System::Path> _forward{};

public:
    enum Direction
    {
        NONE,
        BACKWARD,
        FORWARD
    };

    const System::Path &current() const { return _current; }

    Navigation();

    bool can_go_up();

    void go_up();

    bool can_go_backward();

    void go_backward();

    bool can_go_forward();

    void go_forward();

    void go_home();

    void go_home_dont_record_history();

    void refresh();

    void navigate(String directory);

    void navigate(System::Path path);

    void navigate(System::Path path, Direction record_history);

    void clear_forward();
};

} // namespace filepicker