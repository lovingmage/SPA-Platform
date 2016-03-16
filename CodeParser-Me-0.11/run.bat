echo Automatic Test Suite Running Start
echo Rebuild Project
devenv CodeParser.sln /rebuild debug
cd ./x64/Debug
MetricExecutive.exe ../../TestFile/ *.cpp *.h
echo Automatic Test Finish
pause