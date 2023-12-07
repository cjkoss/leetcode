FROM ubuntu:24.04

RUN apt-get update 
RUN apt-get install -y --no-install-recommends \
          python3-neovim=0.4.* \
          python3.11-minimal=3.11.* \
	  python3.11-venv=3.11.* \
	  git=1:2.40.* \
	  curl \
    ripgrep \
    pip \
    gcc \ 
    make \
    npm

RUN curl -LO https://github.com/neovim/neovim/releases/latest/download/nvim.appimage && \
   chmod u+x nvim.appimage && \
   ./nvim.appimage --appimage-extract && \
   ln -s /squashfs-root/AppRun /usr/bin/nvim

RUN git clone https://github.com/NvChad/NvChad ~/.config/nvim --depth 1
RUN git clone https://github.com/dreamsofcode-io/neovim-python.git ~/.config/nvim/lua/custom

# M.ui = { theme = 'one_light' }

RUN apt-get install -y --no-install-recommends \
     libc-dev=2.38*

