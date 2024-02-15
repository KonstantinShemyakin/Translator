xcopy *.* /EXCLUDE:!!x.xcl /S /Y D:\!!Translator\
xcopy Translator\SQLSyntax.cpp /S /Y D:\!!Translator\Translator\
xcopy Translator\SQLReserv.h /S /Y D:\!!Translator\Translator\
xcopy Translator\SQLReserv.cpp /S /Y D:\!!Translator\Translator\

del /Q /S D:\!!Translator\Code\*.*
del /Q /S D:\!!Translator\Table\*.*
del /Q /S D:\!!Translator\Compiler.sdf
del /Q /S D:\!!Translator\Release\*.iobj
del /Q /S D:\!!Translator\Release\*.pdb
del /Q /S D:\!!Translator\Release\*.ipdb
del /Q /S D:\!!Translator\Release\Auto\*.*

cd D:\!!Translator\
mkdir Code
cd D:\!!Translator\Release\
mkdir Auto
