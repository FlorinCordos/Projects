!/bin/bash
#creare directoare

mkdir /home/examen/surse/dir1
mkdir /home/examen/surse/dir2
mkdir /home/examen/surse/dir3

#creare starship.txt
touch /home/examen/surse/dir1/starship.txt
touch /home/examen/surse/dir2/starship.txt
touch /home/examen/surse/dir3/starship.txt

#generare numar aleator intre 500-700
echo $((500+RANDOM%201)) > /home/examen/surse/dir1/starship.txt
echo $((500+RANDOM%201)) > /home/examen/surse/dir2/starship.txt
echo $((500+RANDOM%201)) > /home/examen/surse/dir3/starship.txt

#creare director tmpwsd & copiere

mkdir /home/examen/surse/tmpswd
cp /home/examen/surse/dir1/starship.txt /home/examen/surse/tmpwsd/starship_device_unit_1_alpha.txt
cp /home/examen/surse/dir1/starship.txt /home/examen/surse/tmpwsd/starship_device_unit_2_beta.txt
cp /home/examen/surse/dir1/starship.txt /home/examen/surse/tmpwsd/starship_device_unit_3_gamma.txt

#redenumire

mv /home/examen/surse/tmpwsd/starship_device_unit_1_alpha.txt /home/examen/surse/tmpwsd/dev_unit_1_alpha.txt
mv /home/examen/surse/tmpwsd/starship_device_unit_1_beta.txt /home/examen/surse/tmpwsd/dev_unit_2_beta.txt
mv /home/examen/surse/tmpwsd/starship_device_unit_1_gamma.txt /home/examen/surse/tmpwsd/dev_unit_1_gamma.txt

#stergere tmpwsd

rm -r tmpwsd
