//#include <iostream>
//#include <fstream>
//#include <stdexcept>
//#include <vector>
//
//using namespace std;
//
//class Matrix
//{
//public:
//  Matrix() = default;
//  ~Matrix() = default;
//  Matrix(const int iNumRows, const int iNumCols)
//  {
//    if (iNumRows < 0 || iNumCols < 0)
//      throw out_of_range("Out of range");
//    _matrix.resize(iNumRows);
//    for (auto& c : _matrix)
//      c.resize(iNumCols);
//  }
//
//  void Reset(const int iNumRows, const int iNumCols)
//  {
//    if (iNumRows < 0 || iNumCols < 0)
//      throw out_of_range("Out of range");
//    _matrix.resize(iNumRows);
//    for (auto& c : _matrix)
//      c.resize(iNumCols);
//    for (int i = 0; i < iNumRows; i++)
//      for (int j = 0; j < iNumCols; j++)
//        _matrix.at(i).at(j) = 0;
//  }
//  int At(const int iNumRows, const int iNumCols) const
//  {
//    if (iNumRows < 0 || iNumCols < 0 || iNumRows >= GetNumRows() || iNumCols >= GetNumColumns())
//      throw out_of_range("Out of range");
//    return _matrix.at(iNumRows).at(iNumCols);
//  }
//  int& At(const int iNumRows, const int iNumCols)
//  {
//    return _matrix.at(iNumRows).at(iNumCols);
//  }
//  void Set(const int iNumRows, const int iNumCols, const int iValue)
//  {
//    _matrix.at(iNumRows).at(iNumCols) = iValue;
//  }
//  int GetNumRows() const { return _matrix.size(); }
//  int GetNumColumns() const
//  {
//    if (!_matrix.empty())
//      return _matrix.at(0).size();
//    return 0;
//  }
//private:
//  vector<vector<int>> _matrix;
//};
//
//istream& operator>>(istream& stream, Matrix& matrix)
//{
//  int numOfRows = 0, numOfCols = 0;
//  stream >> numOfRows >> numOfCols;
//  matrix.Reset(numOfRows, numOfCols);
//  for (int i = 0; i < numOfRows; i++)
//    for (int j = 0; j < numOfCols; j++) {
//      int value = 0;
//      stream >> value;
//      matrix.Set(i, j, value);
//    }
//  return stream;
//}
//
//ostream& operator<<(ostream& stream, Matrix matrix)
//{
//  stream << matrix.GetNumRows() <<' ' << matrix.GetNumColumns() << endl;
//  for (int i = 0; i < matrix.GetNumRows(); i++) {
//    for (int j = 0; j < matrix.GetNumColumns(); j++) {
//      stream << matrix.At(i, j) << ' ';
//    }
//    stream << endl;
//  }
//  return stream;
//}
//
//bool operator==(const Matrix& lhs, const Matrix& rhs)
//{
//  if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
//    return false;
//  for (int i = 0; i < lhs.GetNumRows(); i++)
//    for (int j = 0; j < lhs.GetNumColumns(); j++)
//      if (lhs.At(i, j) != rhs.At(i, j))
//        return false;
//  return true;
//}
//
//Matrix operator+(const Matrix& lhs, const Matrix& rhs)
//{
//  if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns())
//    throw invalid_argument("Invalid argument");
//  Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());
//  for (int i = 0; i < lhs.GetNumRows(); i++)
//    for (int j = 0; j < lhs.GetNumColumns(); j++)
//      result.Set(i, j, lhs.At(i, j) + rhs.At(i, j));
//  return result;
//}
//
//int main() {
//  Matrix one;
//  Matrix two;
//
//  cin >> one >> two;
//  cout << one + two << endl;
//  return 0;
//}
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
private:
  int num_rows_;
  int num_columns_;

  vector<vector<int>> elements_;

public:
  Matrix() {
    num_rows_ = 0;
    num_columns_ = 0;
  }

  Matrix(int num_rows, int num_columns) {
    Reset(num_rows, num_columns);
  }

  void Reset(int num_rows, int num_columns) {
    if (num_rows < 0) {
      throw out_of_range("num_rows must be >= 0");
    }
    if (num_columns < 0) {
      throw out_of_range("num_columns must be >= 0");
    }

    num_rows_ = num_rows;
    num_columns_ = num_columns;
    elements_.assign(num_rows, vector<int>(num_columns));
  }

  int& At(int row, int column) {
    return elements_.at(row).at(column);
  }

  int At(int row, int column) const {
    return elements_.at(row).at(column);
  }

  int GetNumRows() const {
    return num_rows_;
  }

  int GetNumColumns() const {
    return num_columns_;
  }
};

bool operator==(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    return false;
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    return false;
  }

  for (int row = 0; row < one.GetNumRows(); ++row) {
    for (int column = 0; column < one.GetNumColumns(); ++column) {
      if (one.At(row, column) != two.At(row, column)) {
        return false;
      }
    }
  }

  return true;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    throw invalid_argument("Mismatched number of rows");
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    throw invalid_argument("Mismatched number of columns");
  }

  Matrix result(one.GetNumRows(), one.GetNumColumns());
  for (int row = 0; row < result.GetNumRows(); ++row) {
    for (int column = 0; column < result.GetNumColumns(); ++column) {
      result.At(row, column) = one.At(row, column) + two.At(row, column);
    }
  }

  return result;
}

istream& operator>>(istream& in, Matrix& matrix) {
  int num_rows, num_columns;
  in >> num_rows >> num_columns;

  matrix.Reset(num_rows, num_columns);
  for (int row = 0; row < num_rows; ++row) {
    for (int column = 0; column < num_columns; ++column) {
      in >> matrix.At(row, column);
    }
  }

  return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
  out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
  for (int row = 0; row < matrix.GetNumRows(); ++row) {
    for (int column = 0; column < matrix.GetNumColumns(); ++column) {
      if (column > 0) {
        out << " ";
      }
      out << matrix.At(row, column);
    }
    out << endl;
  }

  return out;
}

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}
