!/bin/bash

#adaugare useri
useradd -u 20021 -g 100 -d /home/examen/surse/Utiliz1 -m -s /bin/bash Utiliz1
useradd -u 20022 -g 100 -d /home/examen/surse/Utiliz2 -m -s /bin/bash Utiliz2
useradd -u 20023 -g 100 -d /home/examen/surse/Utiliz3 -m -s /bin/bash Utiliz3
useradd -u 20024 -g 100 -d /home/examen/surse/Utiliz4 -m -s /bin/bash Utiliz4
useradd -u 20025 -g 100 -d /home/examen/surse/Utiliz5 -m -s /bin/bash Utiliz5
useradd -u 20026 -g 100 -d /home/examen/surse/Utiliz6 -m -s /bin/bash Utiliz6
useradd -u 20027 -g 100 -d /home/examen/surse/Utiliz7 -m -s /bin/bash Utiliz7
useradd -u 20028 -g 100 -d /home/examen/surse/Utiliz8 -m -s /bin/bash Utiliz8
useradd -u 20029 -g 100 -d /home/examen/surse/Utiliz9 -m -s /bin/bash Utiliz9
useradd -u 200210 -g 100 -d /home/examen/surse/Utiliz10 -m -s /bin/bash Utiliz10

#creare grupuri
groupadd -g 200201 users
groupadd -g 200202 management
groupadd -g 200203 resurseumane
groupadd -g 200204 localnet
groupadd -g 200205 itnet

#asignare utilizatori
usermod -aG users Utiliz*

usermod -aG management Utiliz1
usermod -aG management Utiliz2
usermod -aG management Utiliz3

usermod -aG resurseumane Utiliz4
usermod -aG resurseumane Utiliz5
usermod -aG resurseumane Utiliz6

usermod -aG localnet Utiliz7
usermod -aG localnet Utiliz8
usermod -aG localnet Utiliz9

usermod -aG itnet Utiliz10

#creare dir COMMON
mkdir /home/examen/surse/COMMON
chown root:users /home/examen/surse/COMMON
chmod 770 /home/examen/surse/COMMON

#creare dir DIRECTORAT
mkdir /home/examen/surse/DIRECTORAT
chown root:management /home/examen/surse/DIRECTORAT
chmod 750 /home/examen/surse/DIRECTORAT

#creare dir RESURSEUMANE
mkdir /home/examen/surse/RESURSEUMANE
chown root:resurseumane /home/examen/surse/RESURSEUMANE
chmod 770 /home/examen/surse/RESURSEUMANE

#nu sunt sigur ----------------------------------------- partea 2.3 ex 2
#chown root:management /home/examen/surse/RESURSEUMANE
#chmod 750 /home/examen/surse/RESURSEUMANE

#creare subdirectoare
mkdir /home/examen/surse/RESURSEUMANE/Utiliz1
chown Utiliz1 /home/examen/surse/RESURSEUMANE/Utiliz1
chmod 700 /home/examen/surse/RESURSEUMANE/Utiliz1

mkdir /home/examen/surse/RESURSEUMANE/Utiliz2
chown Utiliz2 /home/examen/surse/RESURSEUMANE/Utiliz2
chmod 700 /home/examen/surse/RESURSEUMANE/Utiliz2

mkdir /home/examen/surse/RESURSEUMANE/Utiliz3
chown Utiliz3/home/examen/surse/RESURSEUMANE/Utiliz3
chmod 700 /home/examen/surse/RESURSEUMANE/Utiliz3

mkdir /home/examen/surse/RESURSEUMANE/Utiliz4
chown Utiliz4 /home/examen/surse/RESURSEUMANE/Utiliz4
chmod 700 /home/examen/surse/RESURSEUMANE/Utiliz4

mkdir /home/examen/surse/RESURSEUMANE/Utiliz5
chown Utiliz5 /home/examen/surse/RESURSEUMANE/Utiliz5
chmod 700 /home/examen/surse/RESURSEUMANE/Utiliz5

mkdir /home/examen/surse/RESURSEUMANE/Utiliz6
chown Utiliz6 /home/examen/surse/RESURSEUMANE/Utiliz6
chmod 700 /home/examen/surse/RESURSEUMANE/Utiliz6

mkdir /home/examen/surse/RESURSEUMANE/Utiliz7
chown Utiliz7 /home/examen/surse/RESURSEUMANE/Utiliz7
chmod 700 /home/examen/surse/RESURSEUMANE/Utiliz7

mkdir /home/examen/surse/RESURSEUMANE/Utiliz8
chown Utiliz8 /home/examen/surse/RESURSEUMANE/Utiliz8
chmod 700 /home/examen/surse/RESURSEUMANE/Utiliz8

mkdir /home/examen/surse/RESURSEUMANE/Utiliz9
chown Utiliz9 /home/examen/surse/RESURSEUMANE/Utiliz9
chmod 700 /home/examen/surse/RESURSEUMANE/Utiliz9

mkdir /home/examen/surse/RESURSEUMANE/Utiliz10
chown Utiliz10 /home/examen/surse/RESURSEUMANE/Utiliz10
chmod 700 /home/examen/surse/RESURSEUMANE/Utiliz10

#creare dir LOCALNET & ITNET

mkdir /home/examen/surse/LOCALNET
chown root:localnet /home/examen/surse/LOCALNET
chmod 770 /home/examen/surse/LOCALNET

mkdir /home/examen/surse/ITNET
chown root:itnet /home/examen/surse/ITNET
chmod 770 /home/examen/surse/ITNET
 
 
#sfarsit script





