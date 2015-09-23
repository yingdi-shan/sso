
for port in `cat port.list` 
do
ssh -t -t root@zhaoshang -p $port "
cd /home/sso ;
ps -ef | grep firefox | awk '{print $2}' | xargs kill -9 kill;
git pull
make clean;
make server;
./server &
" 
done

