mkdir %1
mkdir %1\Release
mkdir %1\Example
mkdir %1\Example\Code
mkdir %1\Example\Table
mkdir %1\Release\Error
mkdir %1\Grammar
mkdir %1\Generated
mkdir %1\Code
mkdir %1\ETF
mkdir %1\Table
mkdir %1\Doc
xcopy Release\*.exe /S /Y %1\Release\*.exe
xcopy Example*.* /S /Y %1\*.*
xcopy Release\Parse.bat /S /Y %1\Release\*.*
xcopy Release\Rules.bat /S /Y %1\Release\*.*
xcopy Release\TestETF.bat  /S /Y %1\Release\*.*
xcopy Release\ETF.bat  /S /Y %1\Release\*.*
xcopy Release\ETFTest.cpp  /S /Y %1\Release\*.*
xcopy Release\Error\*.* /S /Y %1\Release\Error\*.*
xcopy Grammar\*.y /S /Y %1\Grammar\*.y
xcopy Grammar\*.yacc /S /Y %1\Grammar\*.yacc
xcopy Grammar\*.bnf /S /Y %1\Grammar\*.bnf
xcopy Grammar\*.bif /S /Y %1\Grammar\*.bif
xcopy Grammar\*.grammar /S /Y %1\Grammar\*.grammar
xcopy Generated\*.* %1\Generated\*.*
xcopy Doc\TranBuilder.pdf /S /Y %1\Doc\
xcopy Doc\Translator.pdf /S /Y %1\Doc\
copy  !Translator.bat %1\