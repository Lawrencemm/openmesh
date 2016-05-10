#!/bin/bash

# Run cppcheck and output into file
cppcheck --enable=all . -I src -i Doc/ --force --suppress=unusedFunction --quiet vi src/OpenMesh/Tools/Utils/Timer.hh -Umin -Umax -UBMPOSTFIX -DOPENMESHDLLEXPORT="" &> cppcheck.log

# Echo output to command line for simple analysis via gitlab
cat cppcheck.log

COUNT=$(wc -l < cppcheck.log )

if [ $COUNT -gt 1 ]; then
  echo "Error Count is $COUNT which is too High! CPPCHECK Run failed";
  exit 1;
else
  echo "Error Count is $COUNT ... OK"
fi

 
