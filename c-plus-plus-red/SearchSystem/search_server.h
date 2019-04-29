#pragma once
#include "Synchronized.cpp"

#include <istream>
#include <vector>
#include <map>
#include <string>
#include <future>
#include <deque>
using namespace std;

class InvertedIndex
{
public:
  InvertedIndex() = default;
  explicit InvertedIndex(istream& document_input);

  const vector<pair<size_t, size_t>>& Lookup(const string& word) const;
  size_t GetNumOfDocs() const { return numOfDocs; }
private:
  size_t numOfDocs{};
  map<string, vector<pair<size_t, size_t>>> index;
};

class SearchServer
{
public:
  SearchServer() = default;

  explicit SearchServer(istream& document_input)
    : index(InvertedIndex(document_input))
  {
  }

  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  Synchronized<InvertedIndex> index;
  vector<future<void>> async_tasks;
};
