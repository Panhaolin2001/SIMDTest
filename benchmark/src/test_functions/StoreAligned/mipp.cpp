#include <benchmark/benchmark.h>
#include "../../../include/core/mipp_core.h"
using ElemType = float;
const size_t Len = 256;

static void BM_mippStore(benchmark::State& state) {
  alignas(32) ElemType Arr[Len]{0};
  alignas(32) ElemType Arr1[Len]{0};
  mipp_t_v_native<ElemType> v;
  details::Load_Aligned<mipp_t_v_native<ElemType>, ElemType>(v, Arr);
  for (auto _ : state)
    details::Store_Aligned<mipp_t_v_native<ElemType>, ElemType>(v, Arr1);
}
BENCHMARK(BM_mippStore)->Arg(1);