#include <benchmark/benchmark.h>
#include "../../../include/core/vc_core.h"
using ElemType = float;
const size_t Len = 256;

static void BM_vcMul(benchmark::State& state) {
  alignas(32) ElemType Arr[Len]{3.142f};
  vc_t_v_native<ElemType> rval, lval;
  details::Load_Aligned<vc_t_v_native<ElemType>, ElemType>(rval, Arr);
  details::Load_Aligned<vc_t_v_native<ElemType>, ElemType>(lval, Arr);
  for (auto _ : state)
    rval * lval;
}
BENCHMARK(BM_vcMul)->Arg(1);