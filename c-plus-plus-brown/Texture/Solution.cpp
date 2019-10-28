#include "Common.h"
#include <iostream>

using namespace std;

// Этот файл сдаётся на проверку
// Здесь напишите реализацию необходимых классов-потомков `IShape`

// Напишите реализацию функции
class Shape: public IShape
{
public:
  Shape() = default;
  Shape(Point iPosition, Size iSize, shared_ptr<ITexture> iTexture)
    : _position(iPosition)
    , _size(iSize)
    , _TexturePtr(iTexture) {}
  void SetPosition(Point iPos) override
  {
    _position = iPos;
  }
  Point GetPosition() const override
  {
    return _position;
  }
  void SetSize(Size iSize) override
  {
    _size = iSize;
  }
  Size GetSize() const override
  {
    return _size;
  }
  ITexture* GetTexture() const override
  {
    return _TexturePtr.get();
  }
  void SetTexture(shared_ptr<ITexture> iTexturePtr) override
  {
    _TexturePtr = iTexturePtr;
  }
  void Draw(Image& iImage) const override
  {
    for (int j = _position.y; j < _position.y + _size.height; ++j) {
      for (int i = _position.x; i < _position.x + _size.width; ++i) {
        Point p = { i, j };
        if (p.y < 0 || p.y >= iImage.size() || p.x >= iImage[j].size() || p.x < 0)
          continue;
        if (!isInsideShape(p))
          continue;
        auto posInLocalX = p.x - _position.x;
        auto posInLocalY = p.y - _position.y;
        if (_TexturePtr && posInLocalX < _TexturePtr->GetSize().width && posInLocalY < _TexturePtr->GetSize().height) {
          iImage[p.y][p.x] = _TexturePtr->GetImage()[posInLocalY][posInLocalX];
        }
        else
          iImage[p.y][p.x] = '.';
      }
    }
  }

  virtual bool isInsideShape(Point iPoint) const = 0;

protected:
  Point _position;
  Size _size;
  shared_ptr<ITexture> _TexturePtr;
};

class RectangleShape : public Shape
{
public:
  RectangleShape() = default;
  RectangleShape(Point iPosition, Size iSize, shared_ptr<ITexture> iTexture) : Shape(iPosition, iSize, iTexture) {}
  unique_ptr<IShape> Clone() const override
  {
    return make_unique<RectangleShape>(RectangleShape(_position, _size, _TexturePtr));
  }
  bool isInsideShape(Point iPoint) const override
  {
    Point p = { iPoint.x - _position.x, iPoint.y - _position.y };
    return p.x < _size.width && p.x >= 0 && p.y >= 0 && p.y < _size.height;
  }
};

class EllipseShape : public Shape
{
public:
  EllipseShape() = default;
  EllipseShape(Point iPosition, Size iSize, shared_ptr<ITexture> iTexture) : Shape(iPosition, iSize, iTexture) {}
  unique_ptr<IShape> Clone() const override
  {
    return make_unique<EllipseShape>(EllipseShape(_position, _size, _TexturePtr));
  }
  bool isInsideShape(Point iPoint) const override
  {
    Point p = { iPoint.x - _position.x, iPoint.y - _position.y};
    return IsPointInEllipse(p, _size);
  };
};

unique_ptr<IShape> MakeShape(ShapeType shape_type) {
  if (shape_type == ShapeType::Rectangle)
    return make_unique<RectangleShape>(RectangleShape());
  return make_unique<EllipseShape>(EllipseShape());
}
