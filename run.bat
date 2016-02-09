echo Automatic Test Suite Running Start
echo Rebuild Project
devenv Project1.sln /rebuild debug
cd ./Debug
TestExecutive.exe
echo Automatic Test Finish
pause