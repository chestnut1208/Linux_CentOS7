#调用动态链接库
LIB := lib1650373.so
#编译器
CC := gcc
OBJS := test.o

#link
$(LIB): readconfig.c
	$(CC) -shared -fPIC readconfig.c -o $(LIB)
#compile
	$(CC) -c test.c -o test.o
	$(CC) test.o -o test -L/usr/lib64 lib1650373.so
	$(CC) test.o -o test-1650373 -L/usr/lib64 lib1650373.so

.PHONY : clean install rpm uninstall
install :
	mkdir /usr/1650373
	cp -u test /usr/sbin/test-1650373
	cp -u lib1650373.so /usr/lib64/lib1650373.so
	cp -u 1650373.dat /usr/1650373/1650373.dat
	cp -u 1650373.conf /etc/1650373.conf
rpm :
	cp -u test-1650373.service /usr/lib/systemd/system/test-1650373.service
	cp -u test-1650373.spec /root/rpmbuild/SPECS/test-1650373.spec
	tar jcvf test-1650373.tar.gz *
	cp -u test-1650373.tar.gz /root/rpmbuild/SOURCES/test-1650373.tar.gz
	rpmbuild -bb /root/rpmbuild/SPECS/test-1650373.spec
	cp /root/rpmbuild/RPMS/x86_64/test-1650373.rpm test-1650373.rpm

uninstall :
	rm -rf /usr/sbin/test-1650373
	rm -rf /usr/lib64/lib1650373.so
	rm -rf /etc/1650373.conf
	rm -rf /usr/1650373
	rm -rf /usr/lib/systemd/system/test-1650373.service
	rm -rf test-1650373.tar.gz
	
clean :
	rm -rf *.o *.so test test-1650373 *.tar.gz

