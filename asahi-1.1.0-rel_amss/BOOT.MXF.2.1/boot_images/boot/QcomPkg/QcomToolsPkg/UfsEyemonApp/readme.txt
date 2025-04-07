Before running the tool for the first time, install the following Python packages: 
pip install pandas
pip install seaborn 

To collect the data for the device eye, run: 
start UfsEyemonApp "-device"

To collect the data for the host eye, run:
start UfsEyemonApp "-host"

If target count needs to be adjusted (default value 93), add -count <target count>
example command to change target count to 100 for device eye: start UfsEyemon "-device -count 100"

For SLT screening where the eye width is determined, run: 
start UfsEyemonApp "-slt"

For plotting, create a file with the timing/voltage/error count data. Then run: 
python ufs-eye-monitor-plot.py <file>

