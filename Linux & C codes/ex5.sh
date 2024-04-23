!/bin/bash

nume_familie="NumeFamilie"
prenume1="Prenume1"

mkdir /home/examen/surse/LOLZA.txt

echo "Sper sa fie bine LA SO" >> /home/examen/surse/LOLZA.txt

cp /home/examen/surse/LOLZA.txt /home/examen/surse/LOLZA2.txt

sha512sum -n "$nume_familie" | tee NumeFamilie

ln -s LOLZA.txt NumeFamilie

sha512sum -n "$prenume1" | tee Prenume1

ln LOLZA.txt Prenume1

ls -al >> output.txt

ls -li >> output.txt
