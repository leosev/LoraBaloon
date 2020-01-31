 #!/bin/bash
APPDIR='LoraApp'
ROOTDIR='/var/www/html/'$APPDIR
if [ $(whoami) != "root" ]; then
	echo "Please run as root";
	exit -1;
fi
PhpHandler=$(head -c 20 /dev/urandom | base32)".php"
apt update
Auth=$(head -c 20 /dev/urandom | base32)

apt install apache2 php7.2 curl gawk
cp -r Data/LoraApp $ROOTDIR
printf '<?php\n$authorization="%s";\n$rootdir="%s";\n' $Auth $ROOTDIR > $ROOTDIR/$PhpHandler
cat Data/backend >> $ROOTDIR/$PhpHandler
mkdir $ROOTDIR/json
chown -R www-data $ROOTDIR
chmod +rw $ROOTDIR/json
echo -n "Insert the application ID "
read APPID
echo -n "Insert the application Key "
read APPKey
printf "#!/bin/bash\nAPPID='%s'\nAPPKey='%s'\n" $APPID $APPKey > /usr/bin/startloraapp.sh
cat Data/startloraapp >> /usr/bin/startloraapp.sh
chmod 755 /usr/bin/startloraapp.sh
printf "#!/usr/bin/awk\nBEGIN{\nAUTHORIZATION=\"%s\"\nBACKEND_PATH=\"%s\"\n}\n" $Auth $APPDIR/$PhpHandler > /usr/bin/LoraParse0.awk
cat Data/temp.awk >> /usr/bin/LoraParse0.awk
chmod 755 /usr/bin/LoraParse0.awk
printf "#!/bin/bash\nROOTDIR=\"%s\"\n" $ROOTDIR > /usr/bin/uninstallloraapp.sh
cat Data/uninstallloraapp >> /usr/bin/uninstallloraapp.sh
chmod 755 /usr/bin/uninstallloraapp.sh
printf 'backend: %s\n authorization: %s\n startloraapp.sh to begin' $PhpHandler $Auth
