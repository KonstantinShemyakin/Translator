cmake_minimum_required(VERSION 2.8)
project(Translator CXX)
#install(FILES $<TARGET_PDB_FILE:${PROJECT_NAME}> DESTINATION bin OPTIONAL)
set(CMAKE_BUILD_DIRECTORY  Project)
set(CMAKE_PDB_OUTPUT_DIRECTORY  Project)
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY  Project)
set(CMAKE_PDB_OUTPUT_DIRECTORY_DEBUG  Project)
set(CMAKE_COMPILE_PDB_OUTPUT_DIRECTORY_DEBUG  Project)
set(TARGET_PDB_FILE_DIR_DEBUG  Project)
set(TARGET_PDB_FILE_DIR  Project)
set(CMAKE_BINARY_DIR  Project)
SET(EXECUTABLE_OUTPUT_PATH  Project)
SET(LIBRARY_OUTPUT_PATH  Project)

include_directories(Translator)

#set(CC clang-cl)
set(CMAKE_CXX_COMPILER "C:/Program Files/LLVM/bin/clang-cl")
set(CMAKE_INSTAL_PREFIX C:/Translator/Project)
set(CMAKE_LINKER "C:/Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/VC/Tools/MSVC/14.15.26726/bin/Hostx86/x86/link" )
set (CMAKE_CXX_STANDARD 17)

add_executable(Translator   
    Translator/CSyntax.cpp 
    Translator/GBuilder.cpp
    Translator/KBuilder.cpp
    Translator/LRBuilder.cpp
    Translator/GSyntax.cpp
    Translator/MSyntax.cpp
    Translator/PSyntax.cpp
    Translator/RSyntax.cpp
    Translator/Rules.cpp  
    Translator/Parse.cpp  
    Translator/Syntax.cpp 
    Translator/Tables.cpp 
    Translator/TSyntax.cpp
    Translator/Translator.cpp
)
target_link_libraries(Translator TreeNodeCode)

add_executable(TranParse    
    Translator/C99_Lexer.cpp
    Translator/TranParse.cpp 
)
target_link_libraries(TranParse TreeNodeCode)

add_executable(TranSyntax   
    Translator/CSyntax.cpp
    Translator/MSyntax.cpp
    Translator/Parse.cpp  
    Translator/Syntax.cpp 
    Translator/TSyntax.cpp
    Translator/TranSyntax.cpp
)
target_link_libraries(TranSyntax TreeNodeCode)

add_executable(TranGrammar  
    Translator/C99_Lexer.cpp
    Translator/CGrammar.cpp
    Translator/CSyntax.cpp 
    Translator/GSyntax.cpp 
    Translator/Parse.cpp   
    Translator/Rules.cpp   
    Translator/Tables.cpp  
    Translator/TranGrammar.cpp
)
target_link_libraries(TranGrammar TreeNodeCode)

add_executable(TranRules    
    Translator/CSyntax.cpp
    Translator/Parse.cpp  
    Translator/RSyntax.cpp
    Translator/Rules.cpp  
    Translator/Tables.cpp 
    Translator/TranRules.cpp
)
target_link_libraries(TranRules  TreeNodeCode)

add_executable(TranYACC     
    Translator/CGrammar.cpp
    Translator/CSyntax.cpp
    Translator/GSyntax.cpp
    Translator/Parse.cpp  
    Translator/PSyntax.cpp
    Translator/Rules.cpp  
    Translator/Tables.cpp 
    Translator/YSyntax.cpp
    Translator/TranYACC.cpp
)
target_link_libraries(TranYACC TreeNodeCode)

add_executable(TableBuilder 
    Translator/FYaccParse.cpp
    Translator/C99_Lexer.cpp
    Translator/FSyntax.cpp 
    Translator/GBuilder.cpp
    Translator/KBuilder.cpp
    Translator/LRBuilder.cpp
    Translator/GSyntax.cpp
    Translator/RSyntax.cpp
    Translator/TableBuilder.cpp
)
target_link_libraries(TableBuilder TreeNodeCode)

add_library(TreeNodeCode STATIC 
    Translator/ASyntax.cpp
    Translator/InHelp.cpp    
    Translator/GrammarStock.cpp
    Translator/Maker.cpp     
    Translator/SNodes.cpp    
    Translator/TNodes.cpp    
    Translator/TSemantic.cpp 
    Translator/Variables.cpp 
    Translator/Grammar.cpp
    Translator/Parse.cpp
    Translator/Rules.cpp
    Translator/Tables.cpp
)

