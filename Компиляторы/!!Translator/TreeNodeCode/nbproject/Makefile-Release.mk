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
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/a3a2c9e9/ASemantic.o \
	${OBJECTDIR}/_ext/a3a2c9e9/ASyntax.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Grammar.o \
	${OBJECTDIR}/_ext/a3a2c9e9/GrammarStock.o \
	${OBJECTDIR}/_ext/a3a2c9e9/InHelp.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Maker.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Parse.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Rules.o \
	${OBJECTDIR}/_ext/a3a2c9e9/SNodes.o \
	${OBJECTDIR}/_ext/a3a2c9e9/TNodes.o \
	${OBJECTDIR}/_ext/a3a2c9e9/TSemantic.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Tables.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Variables.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libTreeNodeCode.${CND_DLIB_EXT}

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libTreeNodeCode.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libTreeNodeCode.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared

${OBJECTDIR}/_ext/a3a2c9e9/ASemantic.o: ../Translator/ASemantic.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/ASemantic.o ../Translator/ASemantic.cpp

${OBJECTDIR}/_ext/a3a2c9e9/ASyntax.o: ../Translator/ASyntax.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/ASyntax.o ../Translator/ASyntax.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Grammar.o: ../Translator/Grammar.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Grammar.o ../Translator/Grammar.cpp

${OBJECTDIR}/_ext/a3a2c9e9/GrammarStock.o: ../Translator/GrammarStock.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/GrammarStock.o ../Translator/GrammarStock.cpp

${OBJECTDIR}/_ext/a3a2c9e9/InHelp.o: ../Translator/InHelp.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/InHelp.o ../Translator/InHelp.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Maker.o: ../Translator/Maker.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Maker.o ../Translator/Maker.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Parse.o: ../Translator/Parse.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Parse.o ../Translator/Parse.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Rules.o: ../Translator/Rules.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Rules.o ../Translator/Rules.cpp

${OBJECTDIR}/_ext/a3a2c9e9/SNodes.o: ../Translator/SNodes.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/SNodes.o ../Translator/SNodes.cpp

${OBJECTDIR}/_ext/a3a2c9e9/TNodes.o: ../Translator/TNodes.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/TNodes.o ../Translator/TNodes.cpp

${OBJECTDIR}/_ext/a3a2c9e9/TSemantic.o: ../Translator/TSemantic.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/TSemantic.o ../Translator/TSemantic.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Tables.o: ../Translator/Tables.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Tables.o ../Translator/Tables.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Variables.o: ../Translator/Variables.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2  -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Variables.o ../Translator/Variables.cpp

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
