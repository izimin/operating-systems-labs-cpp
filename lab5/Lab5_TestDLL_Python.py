from ctypes import*
# give location of dll
mydll = cdll.LoadLibrary("C:\\Users\\Ilya\\Documents\\Visual Studio 2012\\Projects\\CppClassDll\\Debug\\CppClassDll.dll")
res1 = mydll.Rev(3434222)
res2 = mydll.CountDivsNumber(56)
print(res1)
print(res2)
