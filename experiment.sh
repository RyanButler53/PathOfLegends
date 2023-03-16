pathStrategy=$1
for s in {0..9};
do ./pathSim -p 500k.txt -i samplePaths/$pathStrategy -o data/$pathStrategy.$s -d $s;
echo $s done;
done;
