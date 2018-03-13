root -l -b <<EOF
.x bGetError.C+($1)
.q
EOF
root -l -b -q "genPlot.C($1)"
