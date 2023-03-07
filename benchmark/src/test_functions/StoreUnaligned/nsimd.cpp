#include <benchmark/benchmark.h>
#include "../../../include/core/nsimd_core.h"
using ElemType = float;
const size_t Len = 256;

static void BM_nsimdStoreU(benchmark::State& state) {
  ElemType Arr[Len]{0};
  ElemType Arr1[Len]{0};
  nsimd_t_v_native<ElemType> v;
  details::Load_Unaligned<nsimd_t_v_native<ElemType>, ElemType>(v, Arr);
  for (auto _ : state)
    details::Store_Unaligned<nsimd_t_v_native<ElemType>, ElemType>(v, Arr1);
}
BENCHMARK(BM_nsimdStoreU)->Arg(1);