pushd rtow\libs\jsoncpp

mkdir -p build
cd build
cmake -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF ..
cmake --build . --config Release
cmake --build . --config Debug

popd