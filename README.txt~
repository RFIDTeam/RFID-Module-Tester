   ____ _               _    __  __       ____  _____ ___ ____    ____            _           _   
  / ___| |__   ___  ___| | _|  \/  |_   _|  _ \|  ___|_ _|  _ \  |  _ \ _ __ ___ (_) ___  ___| |_ 
 | |   | '_ \ / _ \/ __| |/ / |\/| | | | | |_) | |_   | || | | | | |_) | '__/ _ \| |/ _ \/ __| __|
 | |___| | | |  __/ (__|   <| |  | | |_| |  _ <|  _|  | || |_| | |  __/| | | (_) | |  __/ (__| |_ 
  \____|_| |_|\___|\___|_|\_\_|  |_|\__, |_| \_\_|   |___|____/  |_|   |_|  \___// |\___|\___|\__|
  _____ _____ _____ _____ _____ ____|___/__ _____ _____ _____ _____ _____ _____|__/__ _____ _____ 
 |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|


OS Required : Linux 32 bits

+------------------------+
| Use of GitHub on Linux |
+------------------------+

# Installation
	$ sudo apt-get install git-core
# Switch to your new directory
	$ cd ~/Project-RFID
# Initialize the Git repository for the current directory
	$ git init 
# Download the project
	$ git clone <URL>

# Write in the ~/.gitconfig  file :
[user]
	name = your name here
	email = your adress here

# Pull of the files before doing modifications
	$ git pull
# Update if changes occur
	$ git update

# Adding all files to git repository
	$ git add .
# Commit files with a comment (needed)
	$ git commit -m "My comment"
# Push the commit
	$ git push

# Other options
# Show the log file with the commits
	$ git log 
# Checking current status
	$ git status

# For more information, please visit
http://www.kernel.org/pub/software/scm/git/docs/user-manual.html#telling-git-your-name


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


+------------------------------+
| Use of RFID testing software |
+------------------------------+

Installer drivers du lecteur

dependences GTK ????????
libxml2
git-core cmake build-essential libpcsclite1 libpcsclite-dev pcscd

mode operatoire/explication de chaque bouton 


Changer le nom du logiciel

To be completed ...



Authors : ALLAIN Charlie, BELGHITI Sarah, LORANT Allan, PAUL Baptiste, SALLOUH Sabrina
