
for port in `cat port.list` 
do
ssh -t -t root@zhaoshang -p $port "
cd /home/sso ;
#ps -ef | grep server | awk '{print $2}' | xargs kill -9;
git pull
make clean;
make server;
./server &
" 
done

for port in `cat port_python.list` 
do
ssh -t -t root@zhaoshang -p $port "
cd /root/sso ;
#ps -ef | grep python | awk '{print $2}' | xargs kill -9;
git pull;
cd flask-proxy/project;
python runserver.py runserver;
" 
done
