#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([food-web-intervality], [0.11], [daniel.stouffer@canterbury.ac.nz])
AC_PREREQ(2.61)
AM_INIT_AUTOMAKE([foreign])

AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LN_S
AC_PROG_RANLIB

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_FUNC_STRTOD
AC_CHECK_FUNCS([pow sqrt strtol])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
