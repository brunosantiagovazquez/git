#!/bin/bash

cat > "insert-data.sh" << \EOF
sqlite3 ../../.git/gitpro.db -batch < test-data.sql
exit 0
EOF

chmod +x init-test-user.sh
./init-test-user.sh

mkdir test_input
mkdir test_output

echo '***********************************'
echo '   Starting task creation tests'
echo '***********************************'
./gp-tcreate.sh
./clean-db.sh
echo '***********************************'
echo '   Starting task reading tests'
echo '***********************************'
./gp-tread.sh
./clean-db.sh
echo '***********************************'
echo 'Starting assist task reading tests'
echo '***********************************'
./gp-tread-assist.sh
./clean-db.sh
echo '***********************************'
echo '   Starting task deletion tests'
echo '***********************************'
./gp-tdelete.sh
./clean-db.sh
echo '***********************************'
echo 'Starting assist task delete tests'
echo '***********************************'
./gp-tdelete-assist.sh
./clean-db.sh
echo '***********************************'
echo '   Starting task update tests'
echo '***********************************'
./gp-tupdate.sh
./clean-db.sh
echo '***********************************'
echo '   Starting task assign tests'
echo '***********************************'
./gp-tassign.sh
./clean-db.sh
echo '***********************************'
echo '   Starting task link tests'
echo '***********************************'
./gp-tlink.sh
./clean-db.sh
echo '***********************************'
echo 'Starting show types/prior/state tests'
echo '***********************************'
./gp-tshow.sh
./clean-db.sh
echo '***********************************'
echo '  Starting show pending tasks tests'
echo '***********************************'
./gp-tpending.sh
./clean-db.sh
echo '***********************************'
echo '    Starting switch tasks tests'
echo '***********************************'
./gp-tswitch.sh
./clean-db.sh
echo '***********************************'
echo '    Starting stat tasks tests'
echo '***********************************'
./gp-tstat.sh
./clean-db.sh
echo '***********************************'
echo '    Starting export tasks tests'
echo '***********************************'
./gp-texport.sh
./clean-db.sh
echo '***********************************'
echo '   Starting rolecheck task tests'
echo '***********************************'
./gp-trolecheck.sh
./clean-db.sh


echo 'Your username has been changed to run this tests...'
echo 'Use git config --global to update your username'

chmod +x end-test-user.sh
./end-test-user.sh

rm test-data.sql
rm insert-data.sh
rm -rf test_input
rm -rf test_output
