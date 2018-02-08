echo "Deploying to PI"
sshpass -p "raspberry" scp -r /home/alex/Projects/FRC/VictoryCV/src pi@pi3-01.local:/home/pi/projects/FRC/VictoryCV
sshpass -p "raspberry" ssh pi@pi3-01.local "cd /home/pi/projects/FRC/VictoryCV && make"