#include "Common.h"
#include <deque>
#include <algorithm>
#include <mutex>

using namespace std;

class LruCache : public ICache {
public:
  LruCache(
      shared_ptr<IBooksUnpacker> books_unpacker,
      const Settings& settings
  ) : _settings(settings), _books_unpacker(books_unpacker) {}

  BookPtr GetBook(const string& book_name) override {
    lock_guard<std::mutex> g(m);
    auto findedBookIter = std::find_if(_storage.begin(), _storage.end(),
      [&](const shared_ptr<IBook>& iBook) { return iBook->GetName() == book_name; });
    if (findedBookIter != _storage.end()) {
      auto book = *findedBookIter;
      _storage.erase(findedBookIter);
      _storage.push_front(book);
    }
    else {
      auto book = _books_unpacker->UnpackBook(book_name);
      const auto bookSize = book->GetContent().size();
      while (!_storage.empty() && _settings.max_memory < bookSize + _current_memory) {
        auto lastBookSize = _storage.back()->GetContent().size();
        _current_memory -= lastBookSize;
        _storage.pop_back();
      }
      if (_settings.max_memory < bookSize + _current_memory)
        return nullptr;
      _current_memory += bookSize;
      _storage.push_front(std::move(book));
    }
    return _storage.front();
  }
private:
  std::deque<shared_ptr<IBook>> _storage;
  Settings _settings;
  shared_ptr<IBooksUnpacker> _books_unpacker;
  size_t _current_memory = 0;
  std::mutex m;
};


unique_ptr<ICache> MakeCache(
    shared_ptr<IBooksUnpacker> books_unpacker,
    const ICache::Settings& settings
) {
  return make_unique<LruCache>(books_unpacker, settings);
}
