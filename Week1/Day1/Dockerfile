FROM centos:latest

RUN yum update -y
#RUN yum makecache --refresh
RUN yum -y install dnf
RUN dnf -y --enablerepo=powertools install gtest-devel
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
RUN yum -y install wget
RUN yum -y install curl
#RUN yum -y install sudo
RUN yum -y install zsh
RUN yum -y install xterm
RUN yum -y install cmake
RUN yum -y install autoconf
RUN yum -y install automake
RUN yum -y install libtool
RUN yum -y install unzip
RUN dnf -y group install "Development Tools"
ENV HOME=/home/calvin
RUN useradd -ms /bin/bash calvin
USER calvin
WORKDIR /home/calvin

#RUN cd /tmp && \
#    git clone https://github.com/protocolbuffers/protobuf.git && \
#    cd protobuf && \
#    git submodule update --init --recursive && \
#    ./autogen.sh && \
#    ./configure && \
#    make -j${NUM_JOBS} && \
#    make check -j${NUM_JOBS} && \
#    make install -j${NUM_JOBS} && \
#    ldconfig

# installs zsh
RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.2/zsh-in-docker.sh)" -- \
    -p git \
    -p https://github.com/zsh-users/zsh-autosuggestions \
    -p https://github.com/zsh-users/zsh-completions \
    -p https://github.com/marlonrichert/zsh-autocomplete \
    -p https://github.com/zsh-users/zsh-syntax-highlighting

# copy over p10k settings
#COPY .p10k.zsh $HOME
#COPY .zshrc $HOME

# set environmental variables for zsh
RUN echo "TERM=xterm-256color" >> $HOME/.zshrc
ENV COLORTERM=truecolor
RUN echo "autoload -U colors && colors" >> $HOME/.zshrc
RUN echo "PS1='%{$fg[red]%}%n%{$reset_color%}@%{$fg[blue]%}%m %{$fg[yellow]%}%~ %{$reset_color%}%% '" >> $HOME/.zshrc
RUN echo "source ~/.oh-my-zsh/custom/plugins/zsh-autocomplete/zsh-autocomplete.plugin.zsh" >> $HOME/.zshrc
RUN echo "source ~/.oh-my-zsh/custom/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh" >> $HOME/.zshrc
