#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dspl.h"

#define N 18

int main()
{
  void* handle;           // DSPL handle
  handle = dspl_load();   // Загрузка DSPL 

  complex_t x[N];         // массив входного сигнала
  complex_t y[N];         // массив результата БПФ
  complex_t z[N];         // массив результата ОБПФ
  fft_t pfft;             // FFT объект
  int k;
  
  memset(&pfft, 0, sizeof(fft_t)); // Заполняем FFT структуру нулями
  
  fft_create(&pfft, N);            // Создаем FFT структуру для длины N
  
  // заполняем массив входного сигнала
  for(k = 0; k < N; k++)
  {
    RE(x[k]) = (double)cos((double)k);
    IM(x[k]) = (double)sin((double)k);
  }
  
  fft_cmplx(x, N, &pfft, y);        // FFT

  ifft_cmplx(y, N, &pfft, z);       // IFFT
  // Печать результата
  for(k = 0; k < N; k++)
  {  
    printf("| x[%2d] = %9.3f%9.3f ",    k, RE(x[k]), IM(x[k]));
    printf("| y[%2d] = %9.3f%9.3f ",    k, RE(y[k]), IM(y[k]));
    printf("| z[%2d] = %9.3f%9.3f |\n", k, RE(z[k]), IM(z[k]));
  }
  fft_free(&pfft);        // Очищаем структуру fft_t
  dspl_free(handle);      // Очищаем dspl handle
  return 0;
}


