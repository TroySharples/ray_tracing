#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/56252444/config.o \
	${OBJECTDIR}/_ext/b8fdb47f/fundamental_object.o \
	${OBJECTDIR}/_ext/b8fdb47f/parallelogram.o \
	${OBJECTDIR}/_ext/b8fdb47f/sphere.o \
	${OBJECTDIR}/_ext/b8fdb47f/triangle.o \
	${OBJECTDIR}/_ext/1259a249/parallelepiped.o \
	${OBJECTDIR}/_ext/1259a249/polygon.o \
	${OBJECTDIR}/_ext/1259a249/scene.o \
	${OBJECTDIR}/_ext/a8ea4a81/render.o \
	${OBJECTDIR}/_ext/2abcb726/timer.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-Wall -std=c++20 -ffast-math
CXXFLAGS=-Wall -std=c++20 -ffast-math

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ray_tracing

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ray_tracing: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ray_tracing ${OBJECTFILES} ${LDLIBSOPTIONS} -lpthread

${OBJECTDIR}/_ext/56252444/config.o: ../../src/config.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/56252444
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/56252444/config.o ../../src/config.cpp

${OBJECTDIR}/_ext/b8fdb47f/fundamental_object.o: ../../src/objects/fundamental/fundamental_object.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b8fdb47f
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b8fdb47f/fundamental_object.o ../../src/objects/fundamental/fundamental_object.cpp

${OBJECTDIR}/_ext/b8fdb47f/parallelogram.o: ../../src/objects/fundamental/parallelogram.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b8fdb47f
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b8fdb47f/parallelogram.o ../../src/objects/fundamental/parallelogram.cpp

${OBJECTDIR}/_ext/b8fdb47f/sphere.o: ../../src/objects/fundamental/sphere.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b8fdb47f
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b8fdb47f/sphere.o ../../src/objects/fundamental/sphere.cpp

${OBJECTDIR}/_ext/b8fdb47f/triangle.o: ../../src/objects/fundamental/triangle.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/b8fdb47f
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/b8fdb47f/triangle.o ../../src/objects/fundamental/triangle.cpp

${OBJECTDIR}/_ext/1259a249/parallelepiped.o: ../../src/objects/parallelepiped.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1259a249
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1259a249/parallelepiped.o ../../src/objects/parallelepiped.cpp

${OBJECTDIR}/_ext/1259a249/polygon.o: ../../src/objects/polygon.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1259a249
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1259a249/polygon.o ../../src/objects/polygon.cpp

${OBJECTDIR}/_ext/1259a249/scene.o: ../../src/objects/scene.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/1259a249
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/1259a249/scene.o ../../src/objects/scene.cpp

${OBJECTDIR}/_ext/a8ea4a81/render.o: ../../src/rendering/render.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a8ea4a81
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a8ea4a81/render.o ../../src/rendering/render.cpp

${OBJECTDIR}/_ext/2abcb726/timer.o: ../../src/utils/timer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/2abcb726
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/2abcb726/timer.o ../../src/utils/timer.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O3 -I../../src -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
