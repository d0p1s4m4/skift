#include <libfilepicker/model/Navigation.h>

namespace filepicker
{

Navigation::Navigation() : _current(Path::parse(""))
{
}

bool Navigation::can_go_up()
{
    return _current.length() > 0;
}

void Navigation::go_up()
{
    if (can_go_up())
    {
        clear_forward();
        navigate(_current.dirpath(), BACKWARD);
    }
}

bool Navigation::can_go_backward()
{
    return _backward.any();
}

void Navigation::go_backward()
{
    if (can_go_backward())
    {
        navigate(_backward.pop_back(), FORWARD);
    }
}

bool Navigation::can_go_forward()
{
    return _forward.any();
}

void Navigation::go_forward()
{
    if (can_go_forward())
    {
        navigate(_forward.pop_back(), BACKWARD);
    }
}

void Navigation::go_home()
{
    clear_forward();
    navigate(Path::parse("/User"), BACKWARD);
}

void Navigation::go_home_dont_record_history()
{
    clear_forward();
    navigate(Path::parse("/User"), NONE);
}

void Navigation::refresh()
{
    did_update();
}

void Navigation::navigate(String directory)
{
    navigate(Path::parse(directory));
}

void Navigation::navigate(Path path)
{
    clear_forward();
    navigate(path, BACKWARD);
}

void Navigation::navigate(Path path, Direction record_history)
{
    if (path.relative())
    {
        path = Path::join(_current, path);
        path = path.normalized();
    }

    if (_current == path)
    {
        return;
    }

    if (record_history == BACKWARD)
    {
        _backward.push_back(_current);
    }
    else if (record_history == FORWARD)
    {
        _forward.push_back(_current);
    }

    _current = path;

    process_set_directory(_current.string().cstring());

    did_update();
}

void Navigation::clear_forward()
{
    _forward.clear();
}

} // namespace filepicker