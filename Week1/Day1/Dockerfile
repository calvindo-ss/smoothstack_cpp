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
RUN yum -y install wget
RUN yum -y install curl
#RUN yum -y install sudo
RUN yum -y install zsh
RUN yum -y install xterm
RUN dnf -y group install "Development Tools"
ENV HOME=/home/calvin
RUN useradd -ms /bin/bash calvin
USER calvin
WORKDIR /home/calvin

#ENV COLORTERM=truecolor
#ENV TERM=xterm-256color

RUN export COLORTERM=truecolor
RUN export TERM=xterm-256color

RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.2/zsh-in-docker.sh)" -- \
    -p git \
    -p https://github.com/zsh-users/zsh-autosuggestions \
    -p https://github.com/zsh-users/zsh-completions \
    -p https://github.com/marlonrichert/zsh-autocomplete \
    -p https://github.com/zsh-users/zsh-syntax-highlighting

#COPY .p10k.zsh $HOME
#COPY .zshrc $HOME

#RUN echo "autoload -U colors && colors" >> $HOME/.zshrc
#RUN echo "PS1='%{$fg[red]%}%n%{$reset_color%}@%{$fg[blue]%}%m %{$fg[yellow]%}%~ %{$reset_color%}%% '" >> $HOME/.zshrc
RUN echo "source ~/.oh-my-zsh/custom/plugins/zsh-autocomplete/zsh-autocomplete.plugin.zsh" >> $HOME/.zshrc
RUN echo "source ~/.oh-my-zsh/custom/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh" >> $HOME/.zshrc