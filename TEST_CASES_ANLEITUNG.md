# Creating Test Cases for Rosalinde Utils

## Overview

Rosalinde has several utility modules with test cases. This guide shows how to create test cases for the utility modules.

## Implemented Test Cases

### Working Tests (5):
- **tt_strg.c** - String functions (strg_db_in, strg_db_out)
- **tt_hash.c** - Hash table (hash_new, hash_delete, hash_count)
- **tt_list.c** - List operations (list_new, list_append, list_clear)
- **tt_log.c** - Logging (LOG, LOG_OPEN, LOG_CLOSE)
- **tt_misc.c** - Conversions (intg_db_in/out, long_db_in/out)

### Additional Tests:
- **tt_mmgr.c** - Memory Manager (26 lines, minimal)

## Structure of a Test Case

A typical test case for Rosalinde follows this pattern:

### 1. File Header and Includes
```c
#include "rosa.h"           // Base header
#include "xyz.h"            // Component to test
#include "except.h"         // Exception handling
#include "stdio.h"
#include "stdlib.h"

ENABLE_ERROR_HANDLING;      // Initialize exception handling variables

#define HEAD(fnkname) printf("\n\nFUNCTION:\t%s\n",#fnkname);
#define BESCHR(b) printf("DESCRIPTION:\t%s\n",b);
```

### 2. Makefile Entry (make/tt_xyz.mak)
```makefile
# Test executable for component XYZ
tt_xyz : $(ROSA)/src/util/xyz/tt_xyz.o
tt_$(CC) $(CFLAGS) -L$(LIBDIR) $(ROSA)/src/util/xyz/tt_xyz.o -lutil $(LIBS) $(LDLIBS)
tt_mv a.out ../exe/$@

$(ROSA)/src/util/xyz/tt_xyz.o : $(ROSA)/src/util/xyz/tt_xyz.c
tt_$(CC) $(CFLAGS) -DLOCAL -I$(INCLUDE) -I$(ROSA)/include $< -c -o $@
```

### 3. Main Makefile Update (make/Makefile)
Two changes needed:
1. Include at the beginning: `include tt_xyz.mak`
2. Extend tt target: `tt : ... tt_xyz ...`

## Exception Handling Details

### The ENABLE_ERROR_HANDLING Macro

The libutil.a library was compiled with exception handling code. The `ENABLE_ERROR_HANDLING` macro from `include/except.h` automatically defines the required global variables:

```c
jmp_buf _err_environment[MAX_ENVIRONMENT];
int _env_counter = 0;
int _exception_handling_rc = 0;
int catched = 0;
```

This macro **must** be placed at the beginning of each test file (after the includes) so that the tests can be linked.

### Why is this necessary?

The Assert() macros and exception handling code in libutil.a (e.g., in list.c) reference these symbols. Without the global variables, the tests cannot be linked.

## Detailed Test Descriptions

### 1. tt_strg - String Tests
- **File:** src/util/strg/tt_strg.c
- **Tests:** 3 functions
- **Tested APIs:** strg_new(), strg_in(), strg_db_out(), strg_db_in(), strg_print(), strg_cmp(), strg_delete()
- **Status:** ✓ Compiles and works
- **Output:** OK for all 3 test scenarios

### 2. tt_hash - Hash Table Tests
- **File:** src/util/hash/tt_hash.c
- **Tests:** 2 functions
- **Tested APIs:** hash_new(), hash_delete(), hash_count()
- **Status:** ✓ Compiles and works
- **Output:** OK - Hash created, sizes correct

### 3. tt_list - List Tests
- **File:** src/util/list/tt_list.c
- **Tests:** 3 functions
- **Tested APIs:** list_new(), list_append(), list_nbr_of_el(), list_clear(), list_delete()
- **Status:** ✓ Compiles and works
- **Output:** OK - List created, size verified

### 4. tt_log - Logging Tests
- **File:** src/util/log/tt_log.c
- **Tests:** 2 functions
- **Tested APIs:** LOG(), LOG_OPEN(), LOG_CLOSE()
- **Status:** ✓ Compiles and works
- **Features:** STDERR output and log file redirection

### 5. tt_misc - Misc Conversions Tests
- **File:** src/util/misc/tt_misc.c
- **Tests:** 2 functions
- **Tested APIs:** intg_db_out/in(), long_db_out/in()
- **Status:** ✓ Compiles and works
- **Output:** Integer and long conversions verified

## Running the Tests

### Individual Tests:
```bash
cd /home/johannes/Programieren/Rosalinde2026/exe
./tt_strg
./tt_hash
./tt_list
./tt_log
./tt_misc
```

### Compile All Tests:
```bash
cd /home/johannes/Programieren/Rosalinde2026/make
make tt_strg tt_hash tt_list tt_log tt_misc
```

### Recompile After Clean:
```bash
cd /home/johannes/Programieren/Rosalinde2026/make
make clean
make libs              # Rebuild libraries first!
make tt_strg tt_hash tt_list tt_log tt_misc
```

**Important:** After `make clean`, libraries must be rebuilt with `make libs` first, since the tests are linked against libutil.a.

## Checklist for New Utility Tests

To create a new test for component XYZ, follow this checklist:

1. ✓ Create file `src/util/xyz/tt_xyz.c` with:
   - Header and documentation
   - All necessary includes (`except.h` is important!)
   - `ENABLE_ERROR_HANDLING;` after the includes
   - HEAD/BESCHR macros for output
   - main() function with test cases
   
2. ✓ Create makefile `make/tt_xyz.mak` with standard pattern
   
3. ✓ Update `make/Makefile`:
   - Add `include tt_xyz.mak`
   - Add test to `tt :` target
   
4. ✓ Test: `make tt_xyz` and `./exe/tt_xyz`

## Status: COMPLETED ✓

- All 5 utility tests (strg, hash, list, log, misc) are implemented
- All tests compile without errors
- All tests run successfully
- Documentation is updated and consistent

