#include <memory>

namespace RAII
{
template <typename T>
class Booking
{
public:
  Booking(T* provider, int counter) : _provider(provider)
  {
    
  }
  ~Booking()
  {
    if (_provider)
      _provider->CancelOrComplete(*this);
  }
  Booking(const Booking&) = delete;
  Booking& operator=(const Booking&) = delete;
  
  Booking(Booking&& iOther)
  {
    _provider = std::move(iOther._provider);
    iOther._provider = nullptr;
  }
  Booking& operator=(Booking&& iOther)
  {
    _provider = std::move(iOther._provider);
    iOther._provider = nullptr;
    return *this;
  }
private:
  T* _provider;
};
}