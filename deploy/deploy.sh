yum -y install mysql mysql-server mysql-devel git 

service mysqld start
export LD_LIBRARY_PATH=/opt/rh/devtoolset-2/root/usr/lib:/usr/local/lib:$LD_LIBRARY_PATH

git clone https://github.com/srssyd/sso.git /home

cd /opt

rpm -ivh ./mysql-connector-c++-1.1.6-linux-el6-x86-64bit.rpm

scp -P 2214 mysql-connector-c++-1.1.6-linux-el6-x86-64bit.rpm root@121.201.58.189:/opt

yum install devtoolset-2-gcc-4.8.2 devtoolset-2-gcc-c++-4.8.2

scp -P 2214 boost_1_59_0.tar.gz root@121.201.58.189:/opt
tar -xvzf boost_1_59_0.tar.gz
cd boost_1_59_0/
./bootstrap.sh --with-libraries=atomic,date_time,exception,filesystem,iostreams,locale,program_options,regex,signals,system,test,thread,timer,log
./b2 install

ln -s /opt/rh/devtoolset-2/root/usr/bin/* /usr/local/bin/


wget http://people.centos.org/tru/devtools-2/devtools-2.repo -O /etc/yum.repos.d/devtools-2.repo
yum install devtoolset-2-gcc devtoolset-2-binutils devtoolset-2-gcc-c++

scp -P 2214 tbb44.tgz root@121.201.58.189:/opt
tar -xvzf tbb44.tgz
cd tbb44_20150728oss
make
cd build
chmod +x *.sh
./generate_tbbvars.sh
chmod +x *.sh
./tbbvars.sh


cd linux_intel64_gcc_cc4.8.2_libc2.12_kernel2.6.32_release/
cp *.so /opt/rh/devtoolset-2/root/usr/lib
cp *.so.2 /opt/rh/devtoolset-2/root/usr/lib
/sbin/ldconfig
cd ../../include/tbb


export CC=/opt/rh/devtoolset-2.0/root/usr/bin/gcc  
export CPP=/opt/rh/devtoolset-2.0/root/usr/bin/cpp
export CXX=/opt/rh/devtoolset-2.0/root/usr/bin/c++
