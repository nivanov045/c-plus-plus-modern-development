#include "ini.h"

#include <sstream>

namespace Ini {

Section& Document::AddSection(string name)
{
  return sections[name];
}

const Section& Document::GetSection(const string& name) const
{
  return sections.at(name);
}
size_t Document::SectionCount() const
{
  return sections.size();
}

  Document Load(istream& input)
{
  Document result;
  Section* lastAddedSection = nullptr;
  for (string line; getline(input, line);) {
    if (line.empty())
      continue;
    stringstream ss(line);
    if (ss.peek() == '[') {
      ss.ignore(1);
      string sectionName;
      getline(ss, sectionName, ']');
      lastAddedSection = &result.AddSection(sectionName);
    }
    else {
      string key, value;
      getline(ss, key, '=');
      getline(ss, value);
      lastAddedSection->insert({ key, value });
    }
  }
  return result;
}
}
