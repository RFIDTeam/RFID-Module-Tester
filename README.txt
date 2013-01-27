++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
++   _____ _               _    __  __       _____                               _    ++
++  / ____| |             | |  |  \/  |     |  __ \                             | |   ++
++ | |    | |__   ___  ___| | _| \  / |_   _| |__) |_ _ ___ ___ _ __   ___  _ __| |_  ++
++ | |    | '_ \ / _ \/ __| |/ / |\/| | | | |  ___/ _` / __/ __| '_ \ / _ \| '__| __| ++
++ | |____| | | |  __/ (__|   <| |  | | |_| | |  | (_| \__ \__ \ |_) | (_) | |  | |_  ++
++  \_____|_| |_|\___|\___|_|\_\_|  |_|\__, |_|   \__,_|___/___/ .__/ \___/|_|   \__| ++
++                                      __/ |                  | |                    ++
++                                     |___/                   |_|                    ++
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

OS Required : Linux 32 bits

+------------------------------+
| Use of RFID testing software |
+------------------------------+

# Install the reader drivers

# Dependencies
	$ sudo apt-get install libxml2-dev libxslt-dev git-core cmake build-essential libpcsclite1 libpcsclite-dev pcscd

??????????????????dependences GTK ????????


??????????????mode operatoire/explication de chaque bouton ?????????????


To be completed ...


+-------------------------------+
| Use of wzmrtd on Linux 32 bits|
+-------------------------------+

# Installation
# Installation of the dependances
	$ sudo apt-get install git-core cmake build-essential libpcsclite1 libpcsclite-dev pcscd
# Clonage of the repository
	$ git clone git://github.com/ariadnext/wzmrtd.git
 	$ cd wzmrtd
# Generate the makefiles
	$ ccmake .
# compilation
	$ make	
# Push "c" until the apparition of "g", then push it to generate.

Download the the driver of the card reader
	http://www.hidglobal.com/driverDownloads.php?techCat=19&prod_id=171#

       --------------

# To read a passport

# In terminal 1 :
	# Stop the deamon PCSCD
		$ sudo /etc/init.d/pcscd stop
	# Launch PCSCD with traces
		$ sudo pcscd -afd
	# Plug the RFID reader (some lines appear)
	# Put the passport on the reader (light flashing)


# Dans le terminal 2 :

	# Launch the reading with
		$ ./wzmrtd-tool -r "#1" -z "$(echo -e 'MRZ\r\nMRZ')" -f -pfx test -d -v
		# Replace "MRZ" by the passport mrz
	# The option -f save the data in a xml file named test.xml here.

# Help
	$ ./wzmrtd-tool -h

Authors : ALLAIN Charlie, BELGHITI Sarah, LORANT Allan, PAUL Baptiste, SALLOUH Sabrina
