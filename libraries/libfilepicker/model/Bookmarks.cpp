#include <libjson/Json.h>
#include <libsystem/io_new/File.h>

#include <libfilepicker/model/Bookmarks.h>

namespace filepicker
{

const Vector<Bookmark> &Bookmarks::all() const
{
    return _bookmarks;
}

void Bookmarks::add(Bookmark &&bookmark)
{
    _bookmarks.push_back(bookmark);
    did_update();
}

void Bookmarks::remove(const System::Path &path)
{
    for (size_t i = 0; i < _bookmarks.count(); i++)
    {
        if (_bookmarks[i].path() == path)
        {
            _bookmarks.remove_index(i);
            did_update();
            return;
        }
    }
}

bool Bookmarks::has(const System::Path &path) const
{
    for (size_t i = 0; i < _bookmarks.count(); i++)
    {
        if (_bookmarks[i].path() == path)
        {
            return true;
        }
    }

    return false;
}

RefPtr<Bookmarks> Bookmarks::load()
{
    System::File config_file{"/Configs/file-manager/booksmark.json", OPEN_READ};
    IO::Scanner scan{config_file};

    auto raw_bookmarks = Json::parse(scan);

    auto bookmarks = make<Bookmarks>();

    if (!raw_bookmarks.is(Json::ARRAY))
    {
        return bookmarks;
    }

    for (size_t i = 0; i < raw_bookmarks.length(); i++)
    {
        bookmarks->add(raw_bookmarks.get(i));
    }

    return bookmarks;
}

void Bookmarks::save()
{
    Json::Value::Array array;

    for (size_t i = 0; i < _bookmarks.count(); i++)
    {
        array.push_back(_bookmarks[i].serialize());
    }

    System::File file{"/Configs/file-manager/booksmark.json", OPEN_WRITE | OPEN_CREATE};

    IO::Prettifier pretty{file};
    Json::prettify(pretty, move(array));
}

} // namespace filepicker