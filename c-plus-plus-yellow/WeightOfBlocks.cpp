#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  int N = 0, R = 0;
  cin >> N >> R;
  uint64_t summaryVolume = 0;
  for (int i = 0; i < N; i++) {
    uint64_t W = 0, H = 0, D = 0;
    cin >> W >> H >> D;
    uint64_t volume = W * H * D;
    summaryVolume += volume;
  }
  cout << summaryVolume * R;
  return 0;
}
