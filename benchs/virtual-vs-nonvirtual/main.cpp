#include <benchmark/benchmark.h>
#include <set>

#define ARGS RangeMultiplier(10)->Range(10, 1e6)

const long long N = 100;

class Base {
 public:
  virtual long long MakeJob(const long long) = 0;
  virtual ~Base();
};

Base::~Base() = default;

class Deriv : public Base {
 private:
  std::set<long long> data;

 public:
  virtual long long MakeJob(const long long n) override {
    //    long long sum = 0;
    for (long long i = 0; i < n; ++i) {
      data.insert(i);
      //      sum += i;
    }
    return 0;
  }

  virtual ~Deriv() override;
};

Deriv::~Deriv() = default;

class Base_NVI {
 private:
  virtual long long DoMakeJob(const long long) = 0;

 public:
  inline long long MakeJob(const long long n = 100) { return DoMakeJob(n); }

  virtual ~Base_NVI();
};

Base_NVI::~Base_NVI() = default;

class Deriv_NVI : public Base_NVI {
 private:
  std::set<long long> data;
  virtual long long DoMakeJob(const long long n) override {
    //    long long sum = 0;
    for (long long i = 0; i < n; ++i) {
      data.insert(i);
      //      sum += i;
    }
    return 0;
  }

 public:
  virtual ~Deriv_NVI() override;
};

Deriv_NVI::~Deriv_NVI() = default;

static void BM_NVI(benchmark::State &state) {
  Deriv_NVI d = Deriv_NVI();
  const long long n = state.range(0);
  for (auto _ : state) {
    for (int i = 0; i < n; ++i) {
      d.MakeJob();
    }
  }
  benchmark::DoNotOptimize(d);
}

BENCHMARK(BM_NVI)->ARGS;

static void BM_Pointer(benchmark::State &state) {
  Deriv *d = new Deriv();
  const long long n = state.range(0);
  for (auto _ : state) {
    for (int i = 0; i < n; ++i) {
      d->MakeJob(N);
    }
  }
  benchmark::DoNotOptimize(d);
}

BENCHMARK(BM_Pointer)->ARGS;

static void BM_Obj(benchmark::State &state) {
  Deriv d = Deriv();
  const long long n = state.range(0);
  for (auto _ : state) {
    for (int i = 0; i < n; ++i) {
      d.MakeJob(N);
    }
  }
  benchmark::DoNotOptimize(d);
}

BENCHMARK(BM_Obj)->ARGS;

BENCHMARK_MAIN();
