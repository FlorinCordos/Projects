!/bin/bash

echo "Numar 1: "
read numar1
echo "Numar 2: "
read numar2

suma=$((numar1+numar2))
diferenta=$((numar1-numar2))
produs=$((numar1*numar2))
cat=$((numar1/numar2))

echo "Numerele alese sunt: $numar1 si $numar2"

echo "Suma este $suma"
echo "Diferenta este $diferenta"
echo "Produsul este $produs"
echo "Catul este $cat"
