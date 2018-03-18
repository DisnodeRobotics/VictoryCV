echo "Deploying to PI"
sshpass -p "raspberry" scp -r /home/alex/FRC/Projects/VictoryCV/src pi@pi4056.local:/home/pi/projects/FRC/VictoryCV
sshpass -p "raspberry" ssh pi@pi4056.local "sudo pm2 kill -a"
sshpass -p "raspberry" ssh pi@pi4056.local "cd /home/pi/projects/FRC/VictoryCV && cmake . && make"
sshpass -p "raspberry" ssh pi@pi4056.local "sudo systemctl restart victory"