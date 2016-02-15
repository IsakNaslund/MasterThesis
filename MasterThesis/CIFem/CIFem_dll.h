#pragma once

//#define CIFEM_EXPORTS

#ifdef CIFEM_EXPORTS
#define CIFEM_API __declspec(dllexport) 
#else
#define CIFEM_API __declspec(dllimport) 
#endif