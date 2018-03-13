for f in batch_101_*; do cp $f b$f; done
for f in bbatch_101_*; do rename bbatch_101_ batch_$1_ $f; done
for f in batch_$1_*; do sed -i "s/101/$1/" $f; done
for f in batch_$1_*; do bsub -q 8nh $f; done
