# Build nauty and copy CLI dreadnaut
# Used for finding canonical labelings
mkdir -p third-party/nauty

echo "Building nauty"
rm -fr tmp-third-build
cp -r nauty tmp-third-build
cd tmp-third-build
./configure
make
cp dreadnaut ../third-party/nauty
cd ..

# Build tamaki and copy class files
# Used for creating tree decompositions
mkdir -p third-party/tamaki/tw/exact/

echo "Building Tamaki"
rm -fr tmp-third-build
mkdir tmp-third-build
cd tmp-third-build
cp ../utilities/TamakiRunner.java .
cp -r ../PACE2017-TrackA/tw .
javac *.java
cp tw/exact/*.class ../third-party/tamaki/tw/exact/
cp TamakiRunner.class ../third-party/tamaki/
cd ..

echo "Removing temporary folder"
rm -fr tmp-third-build
