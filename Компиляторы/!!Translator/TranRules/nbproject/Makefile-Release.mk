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
	${OBJECTDIR}/_ext/a3a2c9e9/CSyntax.o \
	${OBJECTDIR}/_ext/a3a2c9e9/GrammarStock.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Parse.o \
	${OBJECTDIR}/_ext/a3a2c9e9/RSyntax.o \
	${OBJECTDIR}/_ext/a3a2c9e9/TranRules.o


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
LDLIBSOPTIONS=-L../TreeNodeCode/dist/Release/MinGW-Windows -lTreeNodeCode

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tranrules.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tranrules.exe: ../TreeNodeCode/dist/Release/MinGW-Windows/libTreeNodeCode.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tranrules.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tranrules ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/a3a2c9e9/CSyntax.o: ../Translator/CSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/CSyntax.o ../Translator/CSyntax.cpp

${OBJECTDIR}/_ext/a3a2c9e9/GrammarStock.o: ../Translator/GrammarStock.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/GrammarStock.o ../Translator/GrammarStock.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Parse.o: ../Translator/Parse.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Parse.o ../Translator/Parse.cpp

${OBJECTDIR}/_ext/a3a2c9e9/RSyntax.o: ../Translator/RSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/RSyntax.o ../Translator/RSyntax.cpp

${OBJECTDIR}/_ext/a3a2c9e9/TranRules.o: ../Translator/TranRules.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/TranRules.o ../Translator/TranRules.cpp

# Subprojects
.build-subprojects:
	cd ../TreeNodeCode && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libTreeNodeCode.dll
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/tranrules.exe

# Subprojects
.clean-subprojects:
	cd ../TreeNodeCode && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
