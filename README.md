# NoScript
The one and only NoScript programming language repository. Of course.

## Generate project using CMake

```bash
  git clone git@github.com:eddsanity/NoScript.git
  cd NoScript
  mkdir build
  cd build
  cmake ..
```

## Build using cmake

```bash
  cmake --build .
```

## Run tests
As of right now, I haven't managed to add CMake integration for doctest yet. Tests will have to be manually compiled and run.
Until then, copy and paste this from the project's root directory, and substitute `clang++` for your compiler of choice.
```bash
cd tests/
clang++ -std=c++17 -I../include/ ..\source\AST.cpp ..\source\Error.cpp ..\source\ErrorLogger.cpp
..\source\InfixParseFiles.cpp ..\source\Lexer.cpp ..\source\Parser.cpp ..\source\ParserHelpers.cpp 
..\source\PrefixParseFunctions.cpp ..\source\Token.cpp ..\source\utility.cpp
..\source\PrecedenceTable.cpp ParseLetStatementTest.cpp
ParseRetStatementTest.cpp ParsePrefixExpressionTest.cpp ParseInfixExpressionTest.cpp -o test
```
