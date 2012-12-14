
INCLUDES = -I$(top_builddir)

LDADD = libintervality.a

bin_PROGRAMS = minimumIntervality massIntervality

minimumIntervality_SOURCES = minimum-intervality.cpp
massIntervality_SOURCES = mass-intervality.cpp

noinst_LIBRARIES = libintervality.a
libintervality_a_SOURCES = node.hpp node.cpp network.hpp network.cpp	\
			   intervality_tools.hpp intervality_tools.cpp	\
			   intervality.cpp intervality_run_functions.cpp \
			   bodysizes.cpp \
			   option_parser.hpp option_parser.cpp
