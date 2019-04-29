#include "stats.h"
#include <algorithm>

Stats::Stats()
{
  methodsCount["GET"] = 0;
  methodsCount["POST"] = 0;
  methodsCount["PUT"] = 0;
  methodsCount["DELETE"] = 0;
  methodsCount["UNKNOWN"] = 0;
  uriCount["/"] = 0;
  uriCount["/order"] = 0;
  uriCount["/product"] = 0;
  uriCount["/basket"] = 0;
  uriCount["/help"] = 0;
  uriCount["unknown"] = 0;
}

void Stats::AddMethod(string_view method)
{
  if (method.compare("GET") == 0) {
    ++methodsCount["GET"];
  }
  else if (method.compare("POST") == 0) {
    ++methodsCount["POST"];
  }
  else if (method.compare("PUT") == 0) {
    ++methodsCount["PUT"];
  }
  else if (method.compare("DELETE") == 0) {
    ++methodsCount["DELETE"];
  }
  else {
    ++methodsCount["UNKNOWN"];
  }
}

void Stats::AddUri(string_view uri)
{
  if (uri.compare("/") == 0) {
    ++uriCount["/"];
  }
  else if (uri.compare("/order") == 0) {
    ++uriCount["/order"];
  }
  else if (uri.compare("/product") == 0) {
    ++uriCount["/product"];
  }
  else if (uri.compare("/basket") == 0) {
    ++uriCount["/basket"];
  }
  else if (uri.compare("/help") == 0) {
    ++uriCount["/help"];
  }
  else {
    ++uriCount["unknown"];
  }
}

const map<string_view, int>& Stats::GetMethodStats() const
{
  return methodsCount;
}

const map<string_view, int>& Stats::GetUriStats() const
{
  return uriCount;
}

vector <string_view > SplitIntoWordsView(string_view str) {
  vector <string_view > result;
  str.remove_prefix(std::min(str.find_first_not_of(" "), str.size()));
  while (true) {
    size_t space = str.find(' ');
    result.push_back(str.substr(0, space));
    if (space == str.npos) {
      break;
    }
    else {
      str.remove_prefix(space + 1);
    }
  }
  return result;
}
HttpRequest ParseRequest(string_view line)
{
  auto splittedQuery = SplitIntoWordsView(line);
  return { splittedQuery[0], splittedQuery[1], splittedQuery[2] };
}
