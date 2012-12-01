INCLUDES = -I$(top_builddir)

LDADD = libintervality.a

bin_PROGRAMS = minimum_intervality

minimum_intervality_SOURCES = minimum-intervality.cpp

noinst_LIBRARIES = libintervality.a
libintervality_a_SOURCES = node.hpp node.cpp network.hpp network.cpp	\
			   intervality_tools.hpp intervality_tools.cpp	\
			   intervality.cpp intervality-run-functions.cpp
