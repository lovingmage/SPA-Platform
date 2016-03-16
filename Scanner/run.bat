echo Automatic Test Suite Running Start
echo Rebuild Project
devenv Project1.sln /rebuild debug
cd ./Debug
TestExecutive.exe ../../TestFile *.cpp *.h
echo Automatic Test Finish
pause