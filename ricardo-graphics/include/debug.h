#ifndef RCRD_DEBUG_H
#define RCRD_DEBUG_H

#include <iostream>

#ifdef RCRD_ENABLE_DEBUG
#define RCRD_DEBUG(x) std::clog << x << std::endl
#else
#define RCRD_DEBUG(x) do {} while (0)
#endif

#endif