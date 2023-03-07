#include <benchmark/benchmark.h>
#include "../../../include/core/eve_core.h"
using ElemType = float;
const size_t Len = 256;

static void BM_eveDiv(benchmark::State& state) {
  alignas(32) ElemType Arr[Len]{3.142f};
  eve_t_v_native<ElemType> rval, lval;
  details::Load_Aligned<eve_t_v_native<ElemType>, ElemType>(rval, Arr);
  details::Load_Aligned<eve_t_v_native<ElemType>, ElemType>(lval, Arr);
  for (auto _ : state)
    rval / lval;
}
BENCHMARK(BM_eveDiv)->Arg(1);