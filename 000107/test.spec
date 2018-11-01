Name:           test
Version:        1650373
Release:        1%{?dist}
Summary:        this is a rpm of test-1650373

License:        GPL #自由
#URL:            
Source0:        %{name}-%{version}.tar.gz 

BuildRoot:	%{_tmppath}/%{name}-%{version}-root
BuildRequires:  gcc,make
#Requires:       gcc rpm

%description
test-1650373

#构建前
%prep
%setup -q #解包源tar文件

#构建
%build
make

%install
rm -rf $RPM_BUILD_ROOT
%{__install} -d $RPM_BUILD_ROOT/usr/sbin
%{__install} -d $RPM_BUILD_ROOT/usr/lib64
%{__install} -d $RPM_BUILD_ROOT/etc
%{__install} -d $RPM_BUILD_ROOT/usr/1650373
%{__install} -D test-1650373.service $RPM_BUILD_ROOT/usr/lib/systemd/system/test-1650373.service
make install DESTDIR=$RPM_BUILD_ROOT

%pre
echo "准备安装test-1650373"
%post
echo "完成安装test-1650373"
%preun
echo "准备卸载test-1650373"
%postun
echo "完成卸载test-1650373"

%clean
rm -rf $RPM_BUILD_ROOT

%files
/etc/1650373.conf
%attr(0777,root,root) /usr/sbin/test-1650373
/usr/lib64/lib1650373.so
/usr/1650373/1650373.dat
/usr/lib/systemd/system/test-1650373.service
