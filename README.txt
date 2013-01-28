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


+---------------------------------+
| Use of CheckMyPassport software |
+---------------------------------+

# Verify wzmrtd is well installed (see part below)

# Install dependencies
	$ sudo apt-get install libxml2-dev libxslt-dev git-core cmake build-essential 
	                       libpcsclite1 libpcsclite-dev pcscd apt-get install libgtk2.0-dev

1) First, onpen a new terminal and launch the pcscd daemon.
	$ sudo /etc/init.d/pcscd stop
	$ sudo pcscd -afd

2) Then, launch the software, which is ready to use.

3) Put a passport on the reader, and entre the MRZ in the corresponding field.

4) Push the button "Check" to start reading passport.
	4-1] If it is a new passport, the data will be displayed on the left side and registered 
	     in 2 files in the ./Database directory :
		[MRZ].xml corresponding to the data.
		[MRZ]_fac_0.jp2 corresponding to the picture at JPEG2000 format.
	     The message "Passport added to data base" will appear. The entered MRZ is registered 
	     in the MRZ.txt file to allow you to copy&paste it at
	     at the next reading.
	4-2] If the passport is already in the database, the software will read the data and 
	     compare them with the data in the database, and then display them on the left 
	     side. If the data are corresponding, you get the message "Passport data matched,
	     operational RFID reader". If not, the message "Error : passport data not matched, 
	     non-operational RFID reader" appears.

5) The test is over, you can change the reader or put a new passport to test it.

Note that you can see more in details the execution of the reading in the opened terminal.

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

Download the the driver of the card reader and install it
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

# In terminal 2 :

	# Launch the reading with
		$ ./wzmrtd-tool -r "#1" -z "$(echo -e 'MRZ\r\nMRZ')" -f -pfx test -d -v
		# Replace "MRZ" by the passport mrz
	# The option -f save the data in a xml file named test.xml here.

# Help
	$ ./wzmrtd-tool -h



Authorss : ALLAIN Charlie, BELGHITI Sarah, LORANT Allan, PAUL Baptiste, SALLOUH Sabrina
