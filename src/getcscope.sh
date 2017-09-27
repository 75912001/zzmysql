#!/bin/sh

src=$PWD
cd ../include
inclue=$PWD
cd -

cd ~/endless-lib/include
endin=$PWD
cd -

cd ~/endless-lib/src
endsrc=$PWD
cd -

#cd ../../../share/trunk
#share=$PWD
#cd -
#cd ../../../proto/trunk
#proto=$PWD
#cd -

#find $share -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" >.cscope.files
find $include -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" >.cscope.files
find $endin -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" >>.cscope.files
find $endsrc -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" >>.cscope.files
find $src -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" >>.cscope.files
#find . -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" >>.cscope.files
#find $proto -name "*.cpp" -o -name "*.c" -o -name "*.h" -o -name "*.hpp" >>.cscope.files
cscope -bqk -i .cscope.files
ctags -L .cscope.files -R --c++-kinds=+p --fields=+iaS --extra=+q 
