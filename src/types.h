#ifndef TYPES_H
#define TYPES_H

#ifdef JUST_MILLIONS
using coord_t = uint32_t;
#else
using coord_t = uint64_t;
#endif

#endif  // TYPES_H