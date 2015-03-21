wine ~/.wine/drive_c/Keil_v5/UV4/UV4.exe -b ./kl05test.uvproj -j0 -o KEILOUTPUT.log
local status=$?
cat KEILOUTPUT.log|sed 's/\\/\//g'
