pathName=$1
for s in {0..9};
do ./pathSim -p 500k.txt -i samplePaths/$pathName.txt -o data/$pathName.$s -d $s;
done;
./analysis data/$pathName > data/summary/$pathName.summary;
python graphing.py data/$pathName;
open graphs/$pathName.png;
