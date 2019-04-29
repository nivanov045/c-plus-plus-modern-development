#include "search_server.h"
#include "parse.h"
#include "iterator_range.h"

#include <numeric>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <future>

vector<string> SplitIntoWords(const string& line)
{
  istringstream wordsInput(line);
  return { istream_iterator<string>(wordsInput), istream_iterator<string>() };
}

InvertedIndex::InvertedIndex(istream& document_input)
{
  for (string current_document; getline(document_input, current_document);) {
    ++numOfDocs;
    size_t docIdx = numOfDocs - 1;
    for (const string& word : SplitIntoWords(current_document)) {
      auto& docIdxs = index[word];
      if (!docIdxs.empty() && docIdxs.back().first == docIdx) {
        ++docIdxs.back().second;
      }
      else {
        docIdxs.emplace_back(docIdx, 1);
      }
    }
  }
}

const vector<pair<size_t, size_t>>& InvertedIndex::Lookup(const string& word) const
{
  static const vector<pair<size_t, size_t>> result;
  if (const auto it = index.find(word); it != index.end()) {
    return it->second;
  }
  return result;
}

void UpdateDocumentBaseInner(istream& document_input, Synchronized<InvertedIndex>& index)
{
  InvertedIndex new_index(document_input);
  swap(index.GetAccess().ref_to_value, new_index);
}

void AddQueriesStreamInner(
  istream& query_input,
  ostream& search_results_output,
  Synchronized<InvertedIndex>& index_handle
)
{
  vector<size_t> NumDocIdx;
  vector<int64_t> docIdxs;

  for (string current_query; getline(query_input, current_query);) {
    const auto words = SplitIntoWords(current_query);
    {
      auto access = index_handle.GetAccess();
      const size_t numOfDocs = access.ref_to_value.GetNumOfDocs();
      NumDocIdx.assign(numOfDocs, 0);
      docIdxs.resize(numOfDocs);

      auto& index = access.ref_to_value;
      for (const auto& word : words) {
        for (const auto& [docid, hit_count] : index.Lookup(word)) {
          NumDocIdx[docid] += hit_count;
        }
      }
    }

    iota(docIdxs.begin(), docIdxs.end(), 0);
    {
      partial_sort(
        begin(docIdxs),
        Head(docIdxs, 5).end(),
        end(docIdxs),
        [&NumDocIdx](int64_t lhs, int64_t rhs)
        {
          return pair(NumDocIdx[lhs], -lhs) > pair(NumDocIdx[rhs], -rhs);
        }
      );
    }

    search_results_output << current_query << ':';
    for (size_t docid : Head(docIdxs, 5)) {
      const size_t hit_count = NumDocIdx[docid];
      if (hit_count == 0) {
        break;
      }

      search_results_output << " {"
        << "docid: " << docid << ", "
        << "hitcount: " << hit_count << '}';
    }
    search_results_output << '\n';
  }
}

void SearchServer::UpdateDocumentBase(istream& document_input)
{
  async_tasks.push_back(async(UpdateDocumentBaseInner, ref(document_input), ref(index)));
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
)
{
  async_tasks.push_back(
    async(
      AddQueriesStreamInner, ref(query_input), ref(search_results_output), ref(index)
    )
  );
}
