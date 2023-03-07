#include <benchmark/benchmark.h>
#include "../../../include/core/nsimd_core.h"
using ElemType = float;
const size_t Len = 256;

static void BM_nsimdLen(benchmark::State& state) {
  for (auto _ : state)
    details::Len<nsimd_t_v_native<ElemType>, ElemType>();
}
BENCHMARK(BM_nsimdLen)->Arg(1);