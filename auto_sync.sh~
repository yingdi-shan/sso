ssh root@zhaoshang -p 2211 "
cd /home/sso;
for ip in {cat ip.list}
do
    ssh root@$ip && (ps -ef | grep server | awk '{print $2}'| xargs kill -9) && (git pull &&make server) &&(./server &)

done"
