   ____ _               _    __  __       ____  _____ ___ ____    ____            _           _   
  / ___| |__   ___  ___| | _|  \/  |_   _|  _ \|  ___|_ _|  _ \  |  _ \ _ __ ___ (_) ___  ___| |_ 
 | |   | '_ \ / _ \/ __| |/ / |\/| | | | | |_) | |_   | || | | | | |_) | '__/ _ \| |/ _ \/ __| __|
 | |___| | | |  __/ (__|   <| |  | | |_| |  _ <|  _|  | || |_| | |  __/| | | (_) | |  __/ (__| |_ 
  \____|_| |_|\___|\___|_|\_\_|  |_|\__, |_| \_\_|   |___|____/  |_|   |_|  \___// |\___|\___|\__|
  _____ _____ _____ _____ _____ ____|___/__ _____ _____ _____ _____ _____ _____|__/__ _____ _____ 
 |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|


+-------------------------+
| Use of GitHub on Ubuntu |
+-------------------------+

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


+------------------------------+
| Use of RFID testing software |
+------------------------------+

To be completed


Authors : ALLAIN Charlie, BELGHITI Sarah, LORANT Allan, PAUL Baptiste, SALLOUH Sabrina




