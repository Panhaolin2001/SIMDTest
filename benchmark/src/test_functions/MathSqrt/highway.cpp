#include <benchmark/benchmark.h>
#include "../../../include/core/highway_core.h"
using ElemType = float;
const size_t Len = 256;

static void BM_highwaySqrt(benchmark::State& state) {
  ElemType Arr[Len]{3.1384f};
  highway_t_v_native<ElemType> v;
  details::Load_Unaligned<highway_t_v_native<ElemType>, ElemType>(v, Arr);
  for (auto _ : state)
    details::Sqrt<ElemType>(v);
}
BENCHMARK(BM_highwaySqrt)->Arg(1);