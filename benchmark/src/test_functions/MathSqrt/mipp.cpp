#include <benchmark/benchmark.h>
#include "../../../include/core/mipp_core.h"
using ElemType = float;
const size_t Len = 256;

static void BM_mippSqrt(benchmark::State& state) {
  ElemType Arr[Len]{3.1384f};
  mipp_t_v_native<ElemType> v;
  details::Load_Unaligned<mipp_t_v_native<ElemType>, ElemType>(v, Arr);
  for (auto _ : state)
    details::Sqrt<ElemType>(v);
}
BENCHMARK(BM_mippSqrt)->Arg(1);