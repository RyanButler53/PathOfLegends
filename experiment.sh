pathStrategy=$1
for s in {0..9};
do ./pathSim -p 500k.txt -i samplePaths/$pathStrategy.txt -o data/$pathStrategy.$s -d $s;
echo $s done;
done;
./analysis data/$pathStrategy > data/summary/$pathStrategy.summary
python graphing.py data/$pathStrategy
