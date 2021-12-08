FROM centos:latest

#RUN /bin/bash -c 'source $HOME/.bashrc; echo $HOME'
RUN yum update -y
RUN yum -y install git
RUN yum -y install gdb
RUN yum -y install vim
RUN yum -y install nano
RUN yum -y install cscope
RUN yum -y install zip
RUN yum -y install curl
RUN yum -y install iotop
RUN yum -y install tree
RUN yum -y install clang
RUN yum -y install epel-release
RUN yum -y install htop
RUN yum -y install iftop
RUN yum -y install iotop
RUN dnf -y group install "Development Tools"
ENV HOME /home/calvin
RUN useradd -ms /bin/bash calvin
USER calvin
WORKDIR /home/calvin
