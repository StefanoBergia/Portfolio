find / -name "*.exe" -size +1024c -executable

find / -name "*.c" -size +100c

find /home/stefano/ -name "(*a*A*)|(*A*a*)" -type f -user stefano -exec tail -n 3

sudo find /home/stefano/ -mindepth 3 -maxdepth 5 -size +250c -name "\w{4}" -user stefano | wc -m
sudo find /home/stefano/ -mindepth 3 -maxdepth 5 -size +250c -name "\w{4}" -user stefano | wc -l

sudo find / -name "*zzz*.\w{3}" | zip name.zip -@

sudo find / -regex "*//bin//*" 

find / -name "*.c" ! -user stefano -group stefano

find / -maxdepth 1 -user stefano -exec chmod -700 {} \
