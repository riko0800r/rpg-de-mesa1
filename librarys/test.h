#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <locale.h>

#include <windows.h>
#include <winuser.h>
#include <windef.h>

double PI = 3.14;

float G_CaQuad(float L)
{
  float area = L * L;
  printf("%f\n", area);
  return area;
}

float G_CaRect(float b, float h)
{
  float area = b * h;
  printf("%f\n", area);
  return area;
}

float G_CaCircle(double R)
{
  float area = PI * (R * R);
  printf("%f\n", area);
  return area;
}

float G_CaCube(float a1)
{
  float area = a1 * a1 * a1;
  printf("%f\n", area);
  return area;
}

float G_CaTriangleT1(float b, float h)
{
  float area = b * h / 2;
  printf("%f\n", area);
  return area;
}

#endif