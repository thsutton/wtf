/** @file
 * Macros and other code for debugging.
 *
 * @author Thomas Sutton <me@thomas-sutton.id.au>
 * @created 2010-03-26
 */

#ifdef DEBUG

#include <stdio.h>
#define WHERESTR  "[%s:%d] "
#define WHEREARG  __FILE__, __LINE__
#define DEBUGPRINT2(...)       fprintf(stderr, __VA_ARGS__)
#define DEBUGPRINT(_fmt, ...)  DEBUGPRINT2(WHERESTR _fmt "\n", WHEREARG, __VA_ARGS__)

#else

#define DEBUGPRINT(_fmt, ...)  {}

#endif

#define LOG(_fmt, ...)  DEBUGPRINT(_fmt, __VA_ARGS__)