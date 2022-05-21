#include "../../simd_libraries/version2/vectorclass.h"
#include <iostream>
#include <complex>
#include <numeric>
#include <chrono>   
#include "Mandelbrot_scalar.cpp"
using namespace std;
using namespace chrono;
#define _Tpb _Tp##b


double average(double *x, int len)
{
    double sum = 0;
    for (int i = 0; i < len; i++) 
        sum += x[i];
    return sum / len; 
}

template <typename _Tp,typename _Tpb>
    inline void mandel_VCL(const _Tpb& _active,
                                   const _Tp& c_re,
                                   const _Tp& c_im,
                                   int maxIters)
    {

        std::size_t N = _Tp().size();

        _Tp z_re = c_re;
        _Tp z_im = c_im;

        for (int i = 0; i < maxIters; ++i)
        {
            auto active = _active & ((z_re * z_re + z_im * z_im) <= _Tp(4.f));
            if (!horizontal_max(active))//全是false就break，就看最大值是不是false
            {
                break;
            }

            _Tp new_re = z_re * z_re - z_im * z_im;
            _Tp new_im = 2.f * z_re * z_im;

            z_re = c_re + new_re;
            z_im = c_im + new_im;
        }
    }

    template <typename _Tp>
    void mandelbrot_VCL(float x0,
                    float y0,
                    float x1,
                    float y1,
                    int width,
                    int height,
                    int maxIters)
    {
        
        std::size_t N = _Tp().size();
        float dx = (x1 - x0) / width;
        float dy = (y1 - y0) / height;

        float arange[N];
        std::iota(&arange[0], &arange[N], 0.f);
        auto programIndex = _Tp().load(arange);
        

        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i += N)
            {
                _Tp x(x0 + (i + programIndex) * dx);
                _Tp y(y0 + j * dy);

                auto active = x < _Tp(width);
                mandel_VCL<_Tp>(active, x, y, maxIters);
            }
        }
    }

 
template<typename _Tp, int Times>
inline void printTimeAndSpeedup(float x0, float y0, float x1, float y1, int width, int height, int maxIterations){

    double VCL_time[Times] = {0}, scalar_time[Times] = {0}, speedup[Times] = {0};
    for(int i = 0; i < Times; ++i){
        auto start_simd = std::chrono::system_clock::now();
        mandelbrot_VCL<_Tp>(x0,y0,x1,y1,width,height,maxIterations);
        auto end_simd   = std::chrono::system_clock::now();
        auto duration_simd = std::chrono::duration_cast<std::chrono::microseconds>(end_simd - start_simd);
        VCL_time[i] = double(duration_simd.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den / _Tp().size();

        auto start_scalar = std::chrono::system_clock::now();
        mandelbrot_scalar(x0,y0,x1,y1,width,height,maxIterations);
        auto end_scalar   = std::chrono::system_clock::now();
        auto duration_scalar = std::chrono::duration_cast<std::chrono::microseconds>(end_scalar - start_scalar);
        scalar_time[i] = double(duration_scalar.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den;

        speedup[i] = scalar_time[i] / VCL_time[i];
    }

    printf(" \n scalar average time = %lf\n VCL average time = %lf\n average speedup = %lf\n", average(scalar_time, Times),average(VCL_time, Times),average(speedup, Times));

}

int main(void)
{
    const unsigned int width = 1024;
    const unsigned int height = 768;
    const float x0 = -2;
    const float x1 = 1;
    const float y0 = -1;
    const float y1 = 1;
    const int maxIters = 256;
    printTimeAndSpeedup<Vec4f,20>(x0,y0,x1,y1,width,height,maxIters);// the first parameter is vector type, the second is times of loop
    return 0;
}