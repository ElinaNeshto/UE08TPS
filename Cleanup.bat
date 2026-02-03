SET BASE_DEST=%~dp0..\
cd %BASE_DEST%

del /S *.pdb
del /S *-DebugGame*
del /S *-Shipping*
del /S *.VC.db

del *.sln
rmdir /S /q .\DerivedDataCache
rmdir /S /q .\Intermediate
rmdir /S /q .\Saved
rmdir /S /q .\.vs
rmdir /S /q .\.idea

pause