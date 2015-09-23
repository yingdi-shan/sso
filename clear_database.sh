for port in `cat port.list` 
do
ssh -t -t root@zhaoshang -p $port "
cd /home/sso ;
mysql -h localhost -u root -ptest < drop.sql
" 
done

