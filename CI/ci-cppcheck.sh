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
cppcheck --enable=all . -I src -i Doc/ --force --suppress=unusedFunction --suppress=missingIncludeSystem --quiet -Umin -Umax -UBMPOSTFIX -DOPENMESHDLLEXPORT="" &> cppcheck.log

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

if [ $COUNT -gt 0 ]; then
  echo -e ${WARNING}
  echo "Total CPPCHECK error Count is $COUNT, which is too High! CPPCHECK Run failed";
  echo -e "${NC}"
  exit 1;
else
  echo "Total CPPCHECK error Count is $COUNT ... OK"
fi

 
