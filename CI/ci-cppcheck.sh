#!/bin/bash

# Exit script on any error
set -e 

#=====================================
# Color Settings:
#=====================================
NC='\033[0m'
OUTPUT='\033[0;32m'
WARNING='\033[0;93m'

echo -e "${OUTPUT}"
echo "=============================================================================="
echo "Running cppcheck"
echo "=============================================================================="
echo -e "${NC}"
echo "Please Wait ..."

# Run cppcheck and output into file
cppcheck --enable=all . --force --suppress=unusedFunction --suppress=missingIncludeSystem --quiet -Umin -Umax -UCTIME -UBMPOSTFIX -DOPENMESHDLLEXPORT="" -UPRIVATE_NODE_TYPESYSTEM_SOURCE -USO_NODE_ABSTRACT_SOURCE -USO_NODE_SOURCE -UCLOCK_REALTIME_HR -i src/OpenMesh/Apps/Unsupported/ -i Doc/  &> cppcheck.log

echo -e "${OUTPUT}"
echo "=============================================================================="
echo "CPPCHECK Messages"
echo "=============================================================================="
echo -e "${NC}"


# Echo output to command line for simple analysis via gitlab
cat cppcheck.log

COUNT=$(wc -l < cppcheck.log )

echo -e "${OUTPUT}"
echo "=============================================================================="
echo "CPPCHECK Summary"
echo "=============================================================================="
echo -e "${NC}"

MAX_COUNT=0

if [ $COUNT -gt $MAX_COUNT ]; then
  echo -e ${WARNING}
  echo "Total CPPCHECK error Count is $COUNT, which is too High (max is $MAX_COUNT)! CPPCHECK Run failed";
  echo -e "${NC}"
  exit 1;
else
  echo "Total CPPCHECK error Count is $COUNT ... OK"
fi

 
