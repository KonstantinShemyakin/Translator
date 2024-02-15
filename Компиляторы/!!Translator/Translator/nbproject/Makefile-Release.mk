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
	${OBJECTDIR}/_ext/a3a2c9e9/GBuilder.o \
	${OBJECTDIR}/_ext/a3a2c9e9/GSyntax.o \
	${OBJECTDIR}/_ext/a3a2c9e9/GrammarStock.o \
	${OBJECTDIR}/_ext/a3a2c9e9/MSyntax.o \
	${OBJECTDIR}/_ext/a3a2c9e9/PSyntax.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Parse.o \
	${OBJECTDIR}/_ext/a3a2c9e9/RSyntax.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Rules.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Syntax.o \
	${OBJECTDIR}/_ext/a3a2c9e9/TSyntax.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Tables.o \
	${OBJECTDIR}/_ext/a3a2c9e9/Translator.o \
	${OBJECTDIR}/C99_Lexer.o \
	${OBJECTDIR}/FSyntax.o \
	${OBJECTDIR}/FYaccParse.o \
	${OBJECTDIR}/KBuilder.o \
	${OBJECTDIR}/LRBuilder.o \
	${OBJECTDIR}/SQLSyntax.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/translator.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/translator.exe: ../TreeNodeCode/dist/Release/MinGW-Windows/libTreeNodeCode.dll

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/translator.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/translator ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/a3a2c9e9/CSyntax.o: ../Translator/CSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/CSyntax.o ../Translator/CSyntax.cpp

${OBJECTDIR}/_ext/a3a2c9e9/GBuilder.o: ../Translator/GBuilder.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/GBuilder.o ../Translator/GBuilder.cpp

${OBJECTDIR}/_ext/a3a2c9e9/GSyntax.o: ../Translator/GSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/GSyntax.o ../Translator/GSyntax.cpp

${OBJECTDIR}/_ext/a3a2c9e9/GrammarStock.o: ../Translator/GrammarStock.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/GrammarStock.o ../Translator/GrammarStock.cpp

${OBJECTDIR}/_ext/a3a2c9e9/MSyntax.o: ../Translator/MSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/MSyntax.o ../Translator/MSyntax.cpp

${OBJECTDIR}/_ext/a3a2c9e9/PSyntax.o: ../Translator/PSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/PSyntax.o ../Translator/PSyntax.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Parse.o: ../Translator/Parse.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Parse.o ../Translator/Parse.cpp

${OBJECTDIR}/_ext/a3a2c9e9/RSyntax.o: ../Translator/RSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/RSyntax.o ../Translator/RSyntax.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Rules.o: ../Translator/Rules.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Rules.o ../Translator/Rules.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Syntax.o: ../Translator/Syntax.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Syntax.o ../Translator/Syntax.cpp

${OBJECTDIR}/_ext/a3a2c9e9/TSyntax.o: ../Translator/TSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/TSyntax.o ../Translator/TSyntax.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Tables.o: ../Translator/Tables.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Tables.o ../Translator/Tables.cpp

${OBJECTDIR}/_ext/a3a2c9e9/Translator.o: ../Translator/Translator.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/a3a2c9e9
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/a3a2c9e9/Translator.o ../Translator/Translator.cpp

${OBJECTDIR}/C99_Lexer.o: C99_Lexer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/C99_Lexer.o C99_Lexer.cpp

${OBJECTDIR}/FSyntax.o: FSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FSyntax.o FSyntax.cpp

${OBJECTDIR}/FYaccParse.o: FYaccParse.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FYaccParse.o FYaccParse.cpp

${OBJECTDIR}/KBuilder.o: KBuilder.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/KBuilder.o KBuilder.cpp

${OBJECTDIR}/LRBuilder.o: LRBuilder.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/LRBuilder.o LRBuilder.cpp

${OBJECTDIR}/SQLSyntax.o: SQLSyntax.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../Generated -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/SQLSyntax.o SQLSyntax.cpp

# Subprojects
.build-subprojects:
	cd ../TreeNodeCode && ${MAKE}  -f Makefile CONF=Release

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libTreeNodeCode.dll
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/translator.exe

# Subprojects
.clean-subprojects:
	cd ../TreeNodeCode && ${MAKE}  -f Makefile CONF=Release clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
