
# 
EXEC="./sim"

# check for exec
if [ ! -f "$EXEC" ]; then
    echo "Executable not found. Run 'make' first."
    exit 1
fi

echo "=== Running simulation with step = 0.1 ==="
echo "Inputs: Rho start = 0.0, end = 1.0, step = 0.1, mu = 20"

$EXEC <<EOF
0.0
1.0
0.1
20
EOF

echo "=== Output files generated ==="
ls -1 NvsRho_*.txt QvsRho_*.txt RTvsRho_*.txt
