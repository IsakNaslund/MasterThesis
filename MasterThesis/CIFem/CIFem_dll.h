#pragma once

// Uncomment this when building CIFem
// Keep it commented out when building wrapper
#define CIFEM_EXPORTS

#ifdef CIFEM_EXPORTS
#define CIFEM_API __declspec(dllexport) 
#else
#define CIFEM_API __declspec(dllimport) 
#endif