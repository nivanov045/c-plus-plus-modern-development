#include <string>
#include "test_runner.h"
#include <algorithm>
#include <list>
using namespace std;

class Editor {
public:
  // –еализуйте конструктор по умолчанию и объ€вленные методы
  Editor() : coursPosition(text.end()) {}
  void Left()
  {
    if (coursPosition != text.begin())
      --coursPosition;
  }
  void Right()
  {
    if (coursPosition != text.end())
      ++coursPosition;
  }
  void Insert(char token)
  {
    coursPosition = text.insert(coursPosition, token);
    ++coursPosition;
  }
  void Cut(size_t tokens = 1)
  {
    buffer.clear();
    auto lastIt = coursPosition;
    while (lastIt != text.end() && tokens > 0) {
      lastIt = next(lastIt);
      --tokens;
    }
    buffer = string(coursPosition, lastIt);
    text.erase(coursPosition, lastIt);
    coursPosition = lastIt;
  }
  void Copy(size_t tokens = 1)
  {
    buffer.clear();
    auto lastIt = coursPosition;
    while (lastIt != text.end() && tokens > 0) {
      lastIt = next(lastIt);
      --tokens;
    }
    buffer = string(coursPosition, lastIt);
  }
  void Paste()
  {
    text.insert(coursPosition, buffer.begin(), buffer.end());
  }
  string GetText() const
  {
    string result;
    for (auto c : text)
      result += c;
    return result;
  }

private:
  list<char> text;
  list<char>::iterator coursPosition;
  string buffer;
};

void TypeText(Editor& editor, const string& text) {
  for (char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for (size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for (size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for (char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}