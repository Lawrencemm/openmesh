
# This script just creates compressed files of OpenMesh sources

# Create Build directory and Build documentation
mkdir build

cd build
cmake ..
make doc
cd ..

# Extract Version Information
VERSION=OpenMesh-$(cat VERSION | grep VERSION | tr -d "VERSION=")

# Create Publishing directory
mkdir OpenMesh-$VERSION

# Move all files into Publishing directory
mv CHANGELOG.md   $VERSION/
mv cmake          $VERSION/
mv CMakeLists.txt $VERSION/
mv debian         $VERSION/
mv Doc            $VERSION/
mv LICENSE        $VERSION/
mv README.md      $VERSION/
mv src            $VERSION/
mv VERSION        $VERSION/ 

mv build/Build/share/OpenMesh/Doc/html/  OpenMesh-$VERSION/Documentation

tar 

tar cjf $VERSION.tar.bz2 $VERSION &
tar czf $VERSION.tar.gz $VERSION &
zip -9 -q -r $VERSION.zip $VERSION &

