#! env sh

for i in tests/songs/*.wav;
do
    echo $i >> tests/test.log;
    ./BPMDetector --display $i >> tests/test.log;
    echo "---------------------------" >> tests/test.log;
    echo "" >> tests/test.log;
done
