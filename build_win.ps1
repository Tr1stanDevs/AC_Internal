$BuildType = "Debug"

cmake -S . -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake -S . -B win-build
& cmake --build win-build --config $BuildType
Write-Output -
Write-Output ----------------------------------------------------------
Write-Output ----------------------------------------------------------
Write-Output ----------------------------------------------------------
Write-Output -    
& .\win-build\$BuildType\AC_Internal.exe